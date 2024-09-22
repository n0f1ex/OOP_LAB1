#include <iostream>
#include <string>
#include <vector>
#include "arr_string.h"

void ToYAML(std::string& YAML);

void FromYAML(std::string& YAML);

void ToYAML(const char*& YAML);

void FromYAML(const char*& YAML);

void ToYAML(const char*& YAML, size_t& len);

void FromYAML(const char*& YAML, size_t& len);

void dialog();

int main()
{
    dialog();
    return 0;
}

void dialog()
{
    std::string choose;
    std::cout << "Input number: 1)char* + length;  2)char* + \\0;  3)string;" << std::endl;
    std::getline(std::cin, choose);
    if (choose[0] == '1'){
        const char* str = nullptr;
        size_t len = 0;
        try {
            ToYAML(str, len);
        } catch (const std::exception& e) {
            std::cout << "Exception occurred during ToYAML(): " << e.what() << std::endl;
            return;
        }
        if (str) {
            std::cout << "\nYAML:\n" << str << std::endl;
            try {
                FromYAML(str, len);
            } catch (const std::exception& e) {
                std::cout << "Exception occurred during FromYAML(): " << e.what() << std::endl;
            }
            delete str;
        }
    } else if (choose[0] == '2'){
        const char* str = nullptr;
        try {
            ToYAML(str);
        } catch (const std::exception& e) {
            std::cout << "Exception occurred during ToYAML(): " << e.what() << std::endl;
            return;
        }
        if (str) {
            std::cout << "\nYAML:\n"  << str << std::endl;
            try {
                FromYAML(str);
            } catch (const std::exception& e) {
                std::cout << "Exception occurred during FromYAML(): " << e.what() << std::endl;
            }
            delete str;
        }
    } else if (choose[0] == '3'){
        std::string str;
        try {
            ToYAML(str);
        } catch (const std::exception& e) {
            std::cout << "Exception occurred during ToYAML(): " << e.what() << std::endl;
            return;
        }
        std::cout << "\nYAML:\n"  << str << std::endl;
        try {
            FromYAML(str);
        } catch (const std::exception& e) {
            std::cout << "Exception occurred during FromYAML(): " << e.what() << std::endl;
        }
    } else
        std::cout << "Wrong input" << std::endl;
}

void FromYAML(const char*& YAML, size_t& len)
{
    std::string out_name;
    std::vector<int> out_nums;
    arrstr::YAMLToStr(YAML, len, out_nums, out_name);
    std::cout << "\n\nTransformed back: " << out_name <<  std::endl;
    for (size_t i = 0; i < out_nums.size(); i++)
        std::cout << out_nums[i] << " ";
    std::cout << std::endl;
}

void ToYAML(const char*& YAML, size_t& len)
{
    std::string name;
    std::vector<int> nums;
    while(arrstr::getArray(nums, name))
        nums.clear();
    arrstr::strToYAML(nums, name, YAML, len);
}

void FromYAML(const char*& YAML)
{
    std::string out_name;
    std::vector<int> out_nums;
    arrstr::YAMLToStr(YAML, out_nums, out_name);

    std::cout << "\n\nTransformed back: " << out_name <<  std::endl;
    for (size_t i = 0; i < out_nums.size(); i++)
        std::cout << out_nums[i] << " ";
    std::cout << std::endl;
}

void ToYAML(const char*& YAML)
{
    std::string name;
    std::vector<int> nums;
    while(arrstr::getArray(nums, name))
        nums.clear();
    arrstr::strToYAML(nums, name, YAML);
}

void FromYAML(std::string& YAML)
{
    std::string out_name;
    std::vector<int> out_nums;
    arrstr::YAMLToStr(YAML, out_nums, out_name);

    std::cout << "\n\nTransformed back: " << out_name <<  std::endl;
    for (size_t i = 0; i < out_nums.size(); i++)
        std::cout << out_nums[i] << " ";
    std::cout << std::endl;
}

void ToYAML(std::string& YAML)
{
    std::string name;
    std::vector<int> nums;    
    while(arrstr::getArray(nums, name))
        nums.clear();
    arrstr::strToYAML(nums, name, YAML);
}