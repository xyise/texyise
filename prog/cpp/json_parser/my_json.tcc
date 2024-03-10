#ifndef MY_JSON_TPP
#define MY_JSON_TPP

namespace my_json
{

    
    MyJson::MyJson()
    {
        json = {};
    }

    MyJson::MyJson(std::map<std::string, MyJsonValue> input)
    {
        this->json = input;
    }

    template <typename T> void MyJson::add(std::string key, T value)
    {        
        json[key] = value;
    }

    template <typename T> T MyJson::get(std::string key)
    {
        return std::get<T>(json[key]);
    }

    std::ostream &operator<<(std::ostream &os, const MyJson &my_json)
    {
        os << "{";
        for (auto it = my_json.json.begin(); it != my_json.json.end(); ++it)
        {
            os << "\"" << it->first << "\": ";
            std::visit([&os](auto &&arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, int>)
                {
                    os << arg;
                }
                else if constexpr (std::is_same_v<T, double>)
                {
                    os << arg;
                }
                else if constexpr (std::is_same_v<T, std::string>)
                {
                    os << "\"" << arg << "\"";
                }
                else if constexpr (std::is_same_v<T, MyJson>)
                {
                    os << arg;
                }
            },
                       it->second);
            os << ", ";
        }
        os << "}";
        return os;
    }


} // namespace my_json

#endif // MY_JSON_TPP