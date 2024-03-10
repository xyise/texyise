#include <iostream>
#include <sstream>
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
    json2.add<std::string>("name", "Johnny");
    json2.add<int>("age", 3);

    MyJson json3;
    json3.add<std::string>("name", "Baby");
    json3.add<int>("age", 1);
    json3.add<double>("weight", 10.5);

    json2.add<MyJson>("grand son", json3);
    json2.add<double>("height", 0.75);
    

    json.add<MyJson>("son", json2);
    json.add<double>("height", 1.75);

    std::cout << json.get<MyJson>("son").get<std::string>("name") << std::endl;

    std::cout << json << std::endl;


    std::stringstream sstrm;
    sstrm << json;
    std::string txt = sstrm.str();


    MyJson json_parsed = MyJson::parse(txt);
    std::cout << "PARSED" << std::endl;
    std::cout << json_parsed << std::endl;
    std::cout << "DONE" << std::endl;
    std::cout << json_parsed.get<MyJson>("son").get<std::string>("name") << std::endl;

    return 0;
}