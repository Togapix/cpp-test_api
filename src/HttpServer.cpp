#include "cpprest/http_listener.h"
// #include "cpprest/json.h"
// #include "cpprest/uri.h"
// #include <algorithm>
// #include <fstream>
#include <iostream>
// #include <random>
// #include <sstream>
// #include <string>
// #include <vector>

// using namespace std;
using namespace web;
using namespace http;
// using namespace utility;
// using namespace http::experimental::listener;

#include "HttpServer.h"
#include "Model/TestJson.h"



// public methods
HttpServer::HttpServer(utility::string_t url):m_listener(url)
{
    m_listener.support(methods::GET, std::bind(&HttpServer::handle_get, this, std::placeholders::_1));
    m_listener.support(methods::PUT, std::bind(&HttpServer::handle_put, this, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&HttpServer::handle_post, this, std::placeholders::_1));
    m_listener.support(methods::DEL, std::bind(&HttpServer::handle_delete, this, std::placeholders::_1));
}

HttpServer::~HttpServer()
{
}


// private methods
void HttpServer::handle_error(pplx::task<void>& t)
{
    try
    {
        t.get();
    }
    catch(...)
    {
        // Ignore the error or log it
    }
}

void HttpServer::handle_get(http_request message)
{
    ucout << U("Get request has been received.") << std::endl;
    ucout << U("Detail:") << std::endl;
    ucout <<  message.to_string() << std::endl;
    
    // useless line
    std::vector<utility::string_t> paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));

    TestJson dataManager;

    utility::string_t data = dataManager.GetValues();

    message.reply(status_codes::OK, data);

    return;
};

void HttpServer::handle_post(http_request message)
{
    ucout << U("Post request has been received.") << std::endl;
    ucout << U("Detail:") << std::endl;
    ucout <<  message.to_string() << std::endl;
    

    message.reply(status_codes::OK, U("TEMP JSON POST"));

    return;
};

void HttpServer::handle_put(http_request message)
{
    ucout << U("Put request has been received.") << std::endl;
    ucout << U("Detail:") << std::endl;
    ucout <<  message.to_string() << std::endl;
    

    message.reply(status_codes::OK, U("TEMP JSON PUT"));

    return;
};

void HttpServer::handle_delete(http_request message)
{
    ucout << U("Delete request has been received.") << std::endl;
    ucout << U("Detail:") << std::endl;
    ucout <<  message.to_string() << std::endl;
    

    message.reply(status_codes::OK, U("TEMP JSON DELETE"));

    return;
};