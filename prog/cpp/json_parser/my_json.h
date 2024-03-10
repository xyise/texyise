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

    typedef std::string::const_iterator sci_t;

    class MyJson
    {
    private:
        std::map<std::string, MyJsonValue> json;

        static MyJson _parse(const std::string& txt, sci_t& it);

    public:
        MyJson();
        MyJson(std::map<std::string, MyJsonValue>);
        template <typename T>
        void add(std::string key, T value);
        template <typename T>
        T get(const std::string& key);
        
        static MyJson parse(const std::string& txt);

    friend std::ostream &operator<<(std::ostream &os, const MyJson &my_json);
    };
}

#include "my_json.tcc"

#endif