#include "cpprest/asyncrt_utils.h"
#include "cpprest/http_listener.h"
#include "cpprest/json.h"
#include "cpprest/uri.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "src/HttpServer.h"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

std::unique_ptr<HttpServer> g_httpServer;

void on_initialize(const string_t& address)
{
    uri_builder uri(address);
  
    string_t addr = uri.to_uri().to_string();
    g_httpServer = std::unique_ptr<HttpServer>(new HttpServer(addr));
    g_httpServer->open().wait();

    ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;

    return;
}

void on_shutdown()
{
    g_httpServer->close().wait();
    return;
}

int main(int argc, char *argv[])
{
    utility::string_t address = U("http://127.0.0.1:");
    utility::string_t port = U("34567");

    address.append(port);

    on_initialize(address);
    
    cout << "Press ENTER to exit." << endl;
    std::string line;
    std::getline(std::cin, line);

    on_shutdown();
    return 0;
}