#pragma once

#include <string>
#include <map>
#include <variant>
#include <memory>

#include <boost/beast/http.hpp>

#include "utils.h"

namespace fcds::network::http {

struct Response {
    beast::http::response<beast::http::dynamic_body> res;
};

using ResponsePtr = std::shared_ptr<Response>;

struct Request {
    std::string host;
    std::string port;
    beast::http::request<beast::http::string_body> req;

    bool SetUrl(std::string const& url);
    void SetMethod(beast::http::verb method);
    void SetHeader(std::string const& name, std::string const& value);
    void SetBody(std::string const& body);
};        

using RequestPtr = std::shared_ptr<Request>;
using Result = std::variant<ResponsePtr, Error>;

Result Perform(RequestPtr const& request);

}  // namespace fcds::network::http