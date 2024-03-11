#include "utils.h"

namespace fcds::network {

UrlParts ParseUrl(std::string url) {
    UrlParts result;

    size_t pos = url.find("://");
    if (pos == std::string::npos) {
        return result;
    }
    std::string protocol = url.substr(0, pos);
    url = url.substr(pos + 3);

    pos = url.find(":");
    if (pos != std::string::npos) {
        result.host = url.substr(0, pos);
        url = url.substr(pos + 1);
        pos = url.find("/");
        if (pos != std::string::npos) {
            result.port = url.substr(0, pos);
            result.path = url.substr(pos);
        } else {
            result.port = url;
        }
    } else {
        pos = url.find("/");
        if (pos != std::string::npos) {
            result.host = url.substr(0, pos);
            result.path = url.substr(pos);
        } else {
            result.host = url;
        }
    }

    return result;
}

StreamOrError CreateTcpStream(std::string const& host, std::string const& port, net::io_context& ioc) {
    tcp::resolver resolver(ioc);
    beast::tcp_stream stream(ioc);

    boost::system::error_code ec;
    auto const results = resolver.resolve(host, port, ec);
    if (ec) {
        return Error{ec.message()};
    }

    stream.connect(results, ec);
    if (ec) {
        return Error{ec.message()};
    }

    return stream;
}

} // namespace fcds::network