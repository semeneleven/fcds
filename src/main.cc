#include <iostream>

#include "network/http.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "Performing HTTP request..." << std::endl;

    using namespace fcds::network;
    http::RequestPtr request = std::make_shared<http::Request>();
    request->SetUrl("http://www.google.com");
    request->SetMethod(beast::http::verb::get);

    http::Result result = http::Perform(request);
    if (std::holds_alternative<Error>(result)) {
        std::cout << "Error: " << std::get<Error>(result).message << std::endl;
    } else {
        std::cout << "Success!" << std::endl;
        std::cout << "Response: " << std::get<http::ResponsePtr>(result)->res << std::endl;
    }

    return 0;
}