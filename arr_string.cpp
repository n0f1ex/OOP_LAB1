#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <vector>

namespace arrstr
{

    int getArray(std::vector<int>& numbers, std::string& name)
    {
        std::string input;
        std::cout << "Input numbers: ";
        std::getline(std::cin, input);

        std::istringstream iss(input);
        int num;

        while (iss >> num)
        {
            numbers.push_back(num);
        }

        if (numbers.empty())
        {
            throw std::runtime_error("Exception occurred no integers");
            return 1;
        }

        std::cout << "Input name: ";
        if (!(std::cin >> name))
        {
            throw std::runtime_error("Exception occurred during inputing name");
            return 1;
        }

        return 0;
    }

    void strToYAML(const std::vector<int>&arr, const std::string&name, std::string&out)
    {
        if (name.empty()) {
            throw std::invalid_argument("Name cannot be empty");
        }
        if (arr.empty()) {
            throw std::invalid_argument("Array cannot be empty");
        }
        out += name;
        out += ":";
        for (size_t i = 0; i < arr.size(); i++) {
            out += "\n    - ";

            try {
                out += std::to_string(arr[i]);
            } catch (const std::exception& e) {
                throw std::runtime_error("Failed to convert number to string: " + std::string(e.what()));
            }
        }
    }

    void strToYAML(const std::vector<int>&arr, const std::string&name, const char*& out)
    {
        if (name.empty()) {
            throw std::invalid_argument("Name cannot be empty");
        }
        if (arr.empty()) {
            throw std::invalid_argument("Array cannot be empty");
        }

        size_t nm_length = name.length();
        size_t len = 2 + nm_length;
        for (int num : arr){
            len += std::to_string(num).size() + 7;
        }
        char *YAML;
        try{
            YAML = new char[len + 1]();
        } catch (const std::exception& e) {
            throw std::runtime_error("Exception occurred during array allocation: " + std::string(e.what()));
        }

        try {
            std::copy(name.begin(), name.end(), YAML);
            YAML[nm_length++] = ':';
            YAML[nm_length++] = '\n';

            for (size_t i = 0; i < arr.size(); ++i) {
                std::copy_n("    - ", 4, YAML + nm_length);
                nm_length += 4;

                auto num_str = std::to_string(arr[i]);
                std::copy(num_str.begin(), num_str.end(), YAML + nm_length);
                nm_length += num_str.size();

                YAML[nm_length++] = '\n';
            }
            YAML[nm_length] = '\0';

            out = YAML;
        } catch (const std::exception& e) {
            delete[] YAML;
            throw std::runtime_error("Exception occurred during array to YAML conversion: " + std::string(e.what()));
        }
    }


    void strToYAML(const std::vector<int>&arr, const std::string&name, const char*& out, size_t& len)
    {
        if (name.empty()) {
            throw std::invalid_argument("Name cannot be empty");
        }
        if (arr.empty()) {
            throw std::invalid_argument("Array cannot be empty");
        }

        size_t nm_length = name.length();
        len = 2 + nm_length;
        for (int num : arr){
            len += std::to_string(num).size() + 7;
        }
        char *YAML;
        try{
            YAML = new char[len + 1]();
        } catch (const std::exception& e) {
            throw std::runtime_error("Exception occurred during array allocation: " + std::string(e.what()));
        }

        try {
            std::copy(name.begin(), name.end(), YAML);
            YAML[nm_length++] = ':';
            YAML[nm_length++] = '\n';

            for (size_t i = 0; i < arr.size(); ++i) {
                std::copy_n("    - ", 4, YAML + nm_length);
                nm_length += 4;

                auto num_str = std::to_string(arr[i]);
                std::copy(num_str.begin(), num_str.end(), YAML + nm_length);
                nm_length += num_str.size();

                YAML[nm_length++] = '\n';
            }
            YAML[nm_length] = '\0';

            out = YAML;
        } catch (const std::exception& e) {
            delete[] YAML;
            throw std::runtime_error("Exception occurred during array to YAML conversion: " + std::string(e.what()));
        }
    }

    void add_num(std::vector<int>& result, std::string& num_str, bool& is_minus)
    {
        if (!num_str.empty()) {
            int num;
            try {
                num = std::stoi(num_str);
                if (is_minus)
                    num = -num;
                result.push_back(num);
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("Exception occurred invalid argument: " + std::string(e.what()));
            } catch (const std::out_of_range& e) {
                throw std::runtime_error("Exception occurred out of range: " + std::string(e.what()));
            }
            
            is_minus = false;
            num_str.clear();
        }
    }

    void parse_digits(std::vector<int>& result, const char ch, std::string& num_str, bool& is_minus)
    {
        if (std::isdigit(ch))
            num_str += ch;
        else if (is_minus)
            is_minus = false;
        else if (ch == '-' && num_str.empty())
            is_minus = true;
        else {
            try {
                add_num(result, num_str, is_minus);
            } catch (const std::exception& e) {
                throw std::runtime_error("Exception occurred during array to vector conversation: " + std::string(e.what()));
            }
        }
    }

    std::vector<int> strToVector(const std::string& input, const size_t start) 
    {
        std::vector<int> result;
        size_t n = start;
        std::string num_str;
        bool is_minus = false;
        
        char ch = input[n++];
        while (ch != '\0') {
            try{
                parse_digits(result, ch, num_str, is_minus);
            } catch (const std::exception& e) {
            throw std::runtime_error("Exception occurred during array to vector conversation: " + std::string(e.what()));
            }
            ch = input[n++];
        }
        try {
            add_num(result, num_str, is_minus);
        } catch (const std::exception& e) {
            throw std::runtime_error("Exception occurred during array to vector conversation: " + std::string(e.what()));
        }
        return result;
    }

    std::vector<int> strToVector(const char*& input, const size_t start) 
    {
        std::vector<int> result;
        size_t n = start;
        std::string num_str;
        bool is_minus = false;

        char ch = input[n++];
        while (ch != '\0') {
            try{
                parse_digits(result, ch, num_str, is_minus);
            } catch (const std::exception& e) {
            throw std::runtime_error("Exception occurred during array to vector conversation: " + std::string(e.what()));
            }
            ch = input[n++];
        }
        try {
            add_num(result, num_str, is_minus);
        } catch (const std::exception& e) {
            throw std::runtime_error("Exception occurred during array to vector conversation: " + std::string(e.what()));
        }
        return result;
    }

    std::vector<int> strToVector(const char*& input, const size_t len, const size_t start) 
    {
        std::vector<int> result;
        size_t n = start;
        char ch = 0;
        std::string num_str;
        bool is_minus = false;

        n--;
        while (++n < len){
            try{
                ch = input[n];
                parse_digits(result, ch, num_str, is_minus);
            } catch (const std::exception& e) {
                throw std::runtime_error("Exception occurred during array to vector conversation: " + std::string(e.what()));
            }
        }
        try {
            add_num(result, num_str, is_minus);
        } catch (const std::exception& e) {
            throw std::runtime_error("Exception occurred during array to vector conversation: " + std::string(e.what()));
        }   
        return result;
    }

    void YAMLToStr(const std::string&YAML, std::vector<int>&integers, std::string&name)
    {
        if (YAML.empty()) {
            throw std::invalid_argument("YAML string cannot be empty");
        }

        size_t name_end = YAML.find(":");
        if (name_end == std::string::npos) {
            throw std::invalid_argument("YAML string does not contain a ':'");
        }

        name.assign(YAML, 0, name_end);
        try {
            integers = strToVector(YAML, name_end);
        } catch (const std::exception& e) {
            throw std::runtime_error("Exception occurred during YAML to string conversion: " + std::string(e.what()));
        }
    }

    void YAMLToStr(const char*&YAML, std::vector<int>&integers, std::string&name)
    {
        if (YAML == nullptr) {
            throw std::invalid_argument("YAML string cannot be null");
        }

        size_t cap = 0;
        while (YAML[cap] != ':') {
            if (YAML[cap] == '\0') {
                throw std::out_of_range("Could not find ':' in YAML string");
            }
            cap++;
        }

        if (cap == 0) {
            throw std::invalid_argument("Name cannot be empty");
        }

        char *k;
        try{
            k = new char[cap + 1]();
        }  catch (const std::exception& e) {
            throw std::runtime_error("Exception occurred during memory allocation: " + std::string(e.what()));
        }

        try {
            std::copy_n(YAML, cap, k);
        } catch (const std::exception& e) {
            delete[] k;
            throw std::runtime_error("Exception occurred during YAML name copying: " + std::string(e.what()));
        }

        k[cap] = '\0';
        name = k;
        try {
            integers = strToVector(YAML, cap);
        } catch (const std::exception& e) {
            delete[] k;
            throw std::runtime_error("Exception occurred during YAML to string conversion: " + std::string(e.what()));
        }

        delete[] k;
    }
    
    void YAMLToStr(const char*&YAML, size_t maks, std::vector<int>&integers, std::string&name)
    {
        if (YAML == nullptr) {
            throw std::invalid_argument("YAML string cannot be null");
        }

        size_t cap = 0;
        while (YAML[cap] != ':') {
            if (cap == maks) {
                throw std::out_of_range("Could not find ':' in YAML string");
            }
            cap++;
        }
        char *k;
        try{
            k = new char[cap + 1]();
        }  catch (const std::exception& e) {
            throw std::runtime_error("Exception occurred during memory allocation: " + std::string(e.what()));
        }

        try {
            std::copy_n(YAML, cap, k);
        } catch (const std::exception& e) {
            delete[] k;
            throw std::runtime_error("Exception occurred during YAML name copying: " + std::string(e.what()));
        }
        k[cap + 1] = '\0';

        name = k;

        try {
            integers = strToVector(YAML, maks, cap);
        } catch (const std::exception& e) {
            delete[] k;
            throw std::runtime_error("Exception occurred during YAML to string conversion: " + std::string(e.what()));
        }
    }
}