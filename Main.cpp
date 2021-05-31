#include "boost/network/protocol/http/server.hpp"
#include <string>
#include <iostream>

namespace http = boost::network::http;

class hello_world;
typedef boost::network::http::server<hello_world> server;

class hello_world {
    void operator() (server::request const &request,
                     server::response &response) {
        std::string ip = source(request);
        response = server::response::stock_reply(
            server::response::ok, std::string("Hello, ") + ip + "!");
    }
};

int
main(int argc, char * argv[]) {

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " address port" << std::endl;
        return 1;
    }

    try {
        hello_world handler;
        server server_(argv[1], argv[2], handler);
        server_.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
