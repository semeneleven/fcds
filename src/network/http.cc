#include "http.h"

#include <tuple>
#include <iostream>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast.hpp>

namespace beast = boost::beast;     // from <boost/beast.hpp>

namespace fcds::network::http {    

bool Request::SetUrl(std::string const& url) {
    UrlParts const url_parts = ParseUrl(url);
    if (url_parts.host.empty()) {
        return false;
    }

    host = url_parts.host;
    port = url_parts.port.empty() ? "80" : url_parts.port;
    std::string const target = url_parts.path.empty() ? "/" : url_parts.path;

    req.target(target);

    return true;
}

void Request::SetMethod(beast::http::verb method) {
    req.method(method);
}

void Request::SetHeader(std::string const& name, std::string const& value) {
    req.set(name, value);
}

void Request::SetBody(std::string const& body) {
    req.body() = body;
    req.prepare_payload();
}

Result Perform(RequestPtr const& request) {
    net::io_context ioc;

    StreamOrError created = CreateTcpStream(request->host, request->port, ioc);
    if (std::holds_alternative<Error>(created)) {
        return std::get<Error>(created);
    }

    auto& stream = std::get<beast::tcp_stream>(created);

    // Send the HTTP request to the remote host
    beast::error_code ec;
    beast::http::write(stream, request->req, ec);
    if (ec) {
        return Error{ec.message()};
    }

    // This buffer is used for reading and must be persisted
    beast::flat_buffer buffer;
    auto response = std::make_shared<Response>();

    // Receive the HTTP response
    beast::http::read(stream, buffer, response->res, ec);
    if (ec) {
        return Error{ec.message()};
    }

    // Gracefully close the socket
    stream.socket().shutdown(tcp::socket::shutdown_both, ec);

    return response;
}

} // namespace fcds::network::http