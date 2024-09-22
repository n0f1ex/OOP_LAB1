#ifndef ARR_STRING_H // include guard
#define ARR_STRING_H

namespace arrstr
{
    int getArray(std::vector<int>& integers, std::string& str);

    void strToYAML(const std::vector<int>&arr, const std::string&name, std::string&out);

    void strToYAML(const std::vector<int>&arr, const std::string&name, const char*& out);

    void strToYAML(const std::vector<int>&arr, const std::string&name, const char*& out, size_t& len);

    void YAMLToStr(const std::string&YAML, std::vector<int>&integers, std::string&name);

    void YAMLToStr(const char*&YAML, std::vector<int>&integers, std::string&name);

    void YAMLToStr(const char*&YAML, size_t maks, std::vector<int>&integers, std::string&name);
}

#endif /* ARR_STRING_H */