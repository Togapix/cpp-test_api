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

    utility::string_t data = dataManager.GetValues();

    message.reply(status_codes::OK, data);

    return;
};


void HttpServer::handle_post(http_request message)
{
    ucout << U("Post request has been received.") << std::endl;
    ucout << U("Detail:") << std::endl;
    ucout <<  message.to_string() << std::endl;

    json::value value;
    json::value* value_ptr = &value;
    
    message.extract_json()
        .then([value_ptr](json::value newValue)
        {
            ucout << "First Name : " << newValue[U("FirstName")] << std::endl;
            ucout << "Last Name : " << newValue[U("LastName")] << std::endl;
            *value_ptr = newValue;
        }
    ).wait();

    dataManager.AddValue(value_ptr).wait();

    message.reply(status_codes::OK, (*value_ptr).serialize());

    return;
};


void HttpServer::handle_put(http_request message)
{
    ucout << U("Put request has been received.") << std::endl;
    ucout << U("Detail:") << std::endl;
    ucout <<  message.to_string() << std::endl;
    
    std::vector<utility::string_t> paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));

    int idToEdit;
    int* idToEdit_ptr = &idToEdit;

    if (paths.empty())
    {
        message.reply(status_codes::BadGateway, U("Bad Gateway."));
    }
        
    try
    {
        idToEdit = std::stoi(paths.back());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        message.reply(status_codes::BadRequest, U("Received bad request."));
    }

    json::value value;
    json::value* value_ptr = &value;

    message.extract_json()
        .then([this, message, value_ptr](json::value newValue)
        {
            ucout << "First Name : " << newValue[U("FirstName")] << std::endl;
            ucout << "Last Name : " << newValue[U("LastName")] << std::endl;
            *value_ptr = newValue;
        }
    ).wait();

    try
    {
        dataManager.EditValue(value_ptr, idToEdit_ptr).wait();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        message.reply(status_codes::BadRequest, U("Received bad request."));
    }

    message.reply(status_codes::OK, *value_ptr);
    return;
};


void HttpServer::handle_delete(http_request message)
{
    ucout << U("Delete request has been received.") << std::endl;
    ucout << U("Detail:") << std::endl;
    ucout <<  message.to_string() << std::endl;
    
    std::vector<utility::string_t> paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));

    int idToDelete;

    if (paths.empty())
    {
        message.reply(status_codes::BadGateway, U("Bad Gateway."));
    }
        
    try
    {
        idToDelete = std::stoi(paths.back());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        message.reply(status_codes::BadRequest, U("Received bad request."));
    }

    utility::string_t deletedValue;
    try
    {
        dataManager.DeleteValue(idToDelete)
        .then([&deletedValue](utility::string_t value)
            {
                deletedValue = value;
            }
        )
        .wait();
    }
    catch(const std::invalid_argument& e)
    {
        message.reply(status_codes::BadRequest, e.what());
    }
    
    message.reply(status_codes::OK, deletedValue);

    return;
};