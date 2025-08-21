#include "cpprest/json.h"

using namespace web;

class TestJson
{
private:
    std::vector<json::value> data;
public:
    TestJson();
    utility::string_t GetValues();
    pplx::task<void> AddValue(json::value* newValue);
    pplx::task<void> EditValue(json::value* newValue, int* idToEdit);
    pplx::task<utility::string_t> DeleteValue(int idToDelete);
};