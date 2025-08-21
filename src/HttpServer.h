#include "cpprest/http_listener.h"
#include "Model/TestJson.h"

using namespace web;
using namespace http;
using namespace http::experimental::listener;

class HttpServer
{
private:
    void handle_get(http_request message);
    void handle_put(http_request message);
    void handle_post(http_request message);
    void handle_delete(http_request message);
    void handle_error(pplx::task<void>& t);
    http_listener m_listener;
    TestJson dataManager;

public:
    HttpServer(utility::string_t url);
    virtual ~HttpServer();
    pplx::task<void>open(){return m_listener.open();}
    pplx::task<void>close(){return m_listener.close();}
};