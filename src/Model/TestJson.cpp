#include "TestJson.h"


utility::string_t TestJson::GetValues()
{
    json::value obj = json::value::object();

    json::value data = json::value::array();

    // should retrieve data from a DB but for purpose of testing, data are created manually
    #pragma region Value1
    json::value tempValue1 = json::value::object();

    tempValue1[U("Id")] = json::value::number(1);
    tempValue1[U("LastName")] = json::value::string(U("Skywalker"));
    tempValue1[U("FirstName")] = json::value::string(U("Anakin"));

    json::value contact = json::value::object();
    contact[U("Email")] = json::value::string(U("a.skywalker@starwars.com"));
    contact[U("PhoneNumber")] = json::value::string(U("06.06.06.06.06"));

    tempValue1[U("Contact")] = contact;
    #pragma endregion Value1

    #pragma region Value2
    json::value tempValue2 = json::value::object();

    tempValue1[U("Id")] = json::value::number(2);
    tempValue2[U("LastName")] = json::value::string(U("Kenobi"));
    tempValue2[U("FirstName")] = json::value::string(U("Obi-Wan"));

    json::value contact2 = json::value::object();
    contact2[U("Email")] = json::value::string(U("o.kenobi@starwars.com"));
    contact2[U("PhoneNumber")] = json::value::string(U("07.07.07.07.07"));

    tempValue2[U("Contact")] = contact2;
    #pragma endregion Value2
    // -------------------------------------------------------------------------------------

    data[0] = tempValue1;
    data[1] = tempValue2;

    obj[U("data")] = data;
    return obj.serialize();
};