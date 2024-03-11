#pragma once

#include <string>
#include <variant>

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast.hpp>

namespace fcds::network {

namespace net = boost::asio;        // from <boost/asio.hpp>
namespace beast = boost::beast;     // from <boost/beast.hpp>
using tcp = net::ip::tcp;

struct UrlParts {
    std::string protocol;
    std::string host;
    std::string port;
    std::string path;
};

UrlParts ParseUrl(std::string url);

struct Error {
    std::string message;
};

using StreamOrError = std::variant<beast::tcp_stream, Error>;

StreamOrError CreateTcpStream(std::string const& host, std::string const& port, net::io_context& ioc);

}  // namespace fcds::network
