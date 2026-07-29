#pragma once

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>

enum class DataType
{
    String,
    Int32
};

class DataTypeUtils
{
public:
    // Convert string to DataType
    DataTypeUtils() = delete;
    ~DataTypeUtils() = delete;

    static std::string trim(const std::string& value)
    {
        const auto begin = value.find_first_not_of(" \t\r\n");

        if (begin == std::string::npos)
        {
            return "";
        }

        const auto end = value.find_last_not_of(" \t\r\n");

        return value.substr(begin, end - begin + 1);
    }

    static DataType fromString(const std::string& type)
    {
        std::string value = trim(type);
        std::transform(value.begin(), value.end(), value.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        if (value == "string")
        {
            return DataType::String;
        }

        if (value == "int32")
        {
            return DataType::Int32;
        }

        throw std::invalid_argument("Unsupported data type: " + type);
    }

    // Convert DataType to string
    static std::string toString(DataType type)
    {
        switch (type)
        {
            case DataType::String:
                return "string";

            case DataType::Int32:
                return "int32";

            default:
                return "unknown";
        }
    }

    // Validate value according to schema type
    static bool validate(DataType type, const std::string& value)
    {
        switch (type)
        {
            case DataType::String:
                return true;

            case DataType::Int32:
                return isValidInt32(value);

            default:
                return false;
        }
    }

private:
    static bool isValidInt32(const std::string& value)
    {
        if (value.empty())
        {
            return false;
        }

        try
        {
            size_t pos = 0;

            long long number = std::stoll(value, &pos);

            if (pos != value.length())
            {
                return false;
            }

            return number >= std::numeric_limits<int32_t>::min() &&
                   number <= std::numeric_limits<int32_t>::max();
        }
        catch (...)
        {
            return false;
        }
    }
};