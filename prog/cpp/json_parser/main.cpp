#include <iostream>
#include <string>
#include "my_json.h"

using namespace my_json;

int main()
{

    MyJson json;
    json.add<std::string>("name", "John");
    json.add<int>("age", 25);

    std::cout << json.get<std::string>("name") << std::endl;
    std::cout << json.get<int>("age") << std::endl;

    MyJson json2;
    json2.add<std::string>("name", "Son");
    json2.add<int>("age", 3);

    json.add<MyJson>("son", json2);

    std::cout << json.get<MyJson>("son").get<std::string>("name") << std::endl;

    std::cout << json << std::endl;
    return 0;
}