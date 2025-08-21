#include "TestJson.h"


TestJson::TestJson()
{
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

    tempValue2[U("Id")] = json::value::number(2);
    tempValue2[U("LastName")] = json::value::string(U("Kenobi"));
    tempValue2[U("FirstName")] = json::value::string(U("Obi-Wan"));

    json::value contact2 = json::value::object();
    contact2[U("Email")] = json::value::string(U("o.kenobi@starwars.com"));
    contact2[U("PhoneNumber")] = json::value::string(U("07.07.07.07.07"));

    tempValue2[U("Contact")] = contact2;
    #pragma endregion Value2

    data.insert(data.end(), { tempValue1, tempValue2 });
}

utility::string_t TestJson::GetValues()
{
    json::value obj = json::value::object();

    json::value dataJsonArray = json::value::array();

    for (size_t i = 0; i < data.size(); i++)
    {
        dataJsonArray[i] = data[i];
    }

    obj[U("data")] = dataJsonArray;
    return obj.serialize();
};

pplx::task<void> TestJson::AddValue(json::value* newValue)
{
    int lastId { -1 };

    for (size_t i = 0; i < data.size(); i++)
    {
        json::value tempValue = data[i];
        int tempValueId { tempValue[U("Id")].as_integer() };

        if (tempValueId > lastId)
        {
            lastId = tempValueId;
        }
    }
    
    (*newValue)[U("Id")] = json::value::number(lastId + 1);
    data.push_back(*newValue);

    return pplx::task_from_result();
};

pplx::task<void> TestJson::EditValue(json::value* newValue, int* idToEdit)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        json::value* currentValue = &data[i];
        int valueId { (*currentValue)[U("Id")].as_integer() };

        if (valueId == *idToEdit)
        {
            *currentValue = *newValue;
            return pplx::task_from_result();
        }
    }
    throw std::invalid_argument("This value does not exists and then can't be edited.");
};

pplx::task<utility::string_t> TestJson::DeleteValue(int idToDelete)
{
    json::value deletedValue;

    for (size_t i = 0; i < data.size(); i++)
    {
        json::value tempValue;
        tempValue = data[i];
        int tempValueId { tempValue[U("Id")].as_integer() };

        if (tempValueId == idToDelete)
        {
            deletedValue = tempValue;
            data.erase(data.begin() + i);
            return pplx::task_from_result(deletedValue.serialize());
        }
    }
    throw std::invalid_argument("This value does not exists and then can't be deleted.");
}