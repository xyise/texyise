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

    template <typename T>
    void MyJson::add(std::string key, T value)
    {
        json[key] = value;
    }

    template <typename T>
    T MyJson::get(const std::string& key)
    {
        return std::get<T>(json[key]);
    }

    std::ostream &operator<<(std::ostream &os, const MyJson &my_json)
    {
        os << "{";
        for (auto it = my_json.json.begin(); it != my_json.json.end(); ++it)
        {
            os << "\"" << it->first << "\": ";
            std::visit([&os](auto &&arg)
                       {
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
                } },
                       it->second);
            if (std::next(it) != my_json.json.end())
            {
                os << ", ";
            }
        }
        os << "}";
        return os;
    }
    
    void skip_whitespaces(const std::string &txt, sci_t &it, int skip)
    {
        for (int i = 0; i < skip; i++)
        {
            if (it == txt.end()) break;
            it++;
        }
        while (it != txt.end() && std::isspace(*it))
        {
            it++;
        }
    }

    std::string parse_str_val(const std::string &txt, sci_t &it)
    {
        std::string str;

        sci_t str_start, str_end;

        if (*it != '"')
        {
            throw std::invalid_argument("The iterator for a string must point to a double quote");
        }
        
        while (it != str.end())
        {
            it++;
            if (*it != '"')
                str += *it;
            else
                break;
        }
        // if successful, it should be pointing to a double quote
        if (it == str.end())
        {
            throw std::invalid_argument("Invalid JSON. A string must end with a double quote.");
        }
        // move to the character after closing '"'
        skip_whitespaces(txt, it, 1);
        return str;
    }

    void move_to_end_of_value(const std::string &txt, sci_t &it)
    {
        // must check } first to handle '},'.
        while (it != txt.end() && *it != '}' && *it != ',')
        {
            it++;
        }
    }

    MyJson MyJson::_parse(const std::string& txt, sci_t& it)
    {

        std::map<std::string, MyJsonValue> json;

        skip_whitespaces(txt, it, 0);
        if (*it != '{') // outer opening {
        {
            throw std::invalid_argument("Invalid JSON: It must start with '{'");
        }
        skip_whitespaces(txt, it, 1);

        while (it != txt.end())
        {
            // find key
            std::string key = parse_str_val(txt, it);

            if (*it != ':')
            {
                throw std::invalid_argument("Invalid JSON. A key must be followed by ':'.");
            }
            skip_whitespaces(txt, it, 1);

            if (it == txt.end())
            {
                throw std::invalid_argument("Invalid JSON. A key must be followed by a value.");
            }        

            // find value
            if (*it == '{') // inner opening {
            {
                json[key] = MyJson::_parse(txt, it);
                if (*it != '}') // inner closing }
                {
                    throw std::invalid_argument("Invalid JSON. A JSON object must end with a closing brace.");
                }
                skip_whitespaces(txt, it, 1);
            }
            else if (*it == '"')
            {
                json[key] = parse_str_val(txt, it);
                move_to_end_of_value(txt, it);                
            }
            else
            {
                // numbers
                sci_t pos_s = it;
                move_to_end_of_value(txt, it);
                std::string val_str = txt.substr(pos_s - txt.begin(), it - pos_s);

                if (val_str.find('.') != std::string::npos)
                {
                    json[key] = std::stod(val_str);
                }
                else
                {
                    json[key] = std::stoi(val_str);
                }
            }

            if (it == txt.end())
            {
                throw std::invalid_argument("Invalid JSON. A JSON object must end with a closing brace.");
            }   

            if (*it == '}') // outer ending }
            {
                break;
            }
            else // i.e. ',' go to the next pair
            {
                skip_whitespaces(txt, it, 1);
            }
        }

        return json;
    }

    MyJson MyJson::parse(const std::string& txt)
    {
        sci_t it = txt.cbegin();
        return MyJson::_parse(txt, it);
    }

} // namespace my_json

#endif // MY_JSON_TPP