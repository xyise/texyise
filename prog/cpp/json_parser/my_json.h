#ifndef MY_JSON_H
#define MY_JSON_H

#include <map>
#include <iostream>
#include <string>
#include <variant>

namespace my_json
{
    class MyJson;
    typedef std::variant<int, double, std::string, MyJson> MyJsonValue;

    class MyJson
    {
    private:
        std::map<std::string, MyJsonValue> json;

    public:
        template <typename T>
        T get(std::string key);
        MyJson();
        MyJson(std::ifstream &file);
        MyJson(std::map<std::string, MyJsonValue>);
        template <typename T>
        void add(std::string key, T value);

    friend std::ostream &operator<<(std::ostream &os, const MyJson &my_json);
    };
}

#include "my_json.tcc"

#endif