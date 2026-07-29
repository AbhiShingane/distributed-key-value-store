#include "SchemaConfig.h"
#include <stdexcept>

bool SchemaConfig::addField(const std::string& fieldName, Datatype datatype)
{
    if(schema.find(fieldName) != schema.end())
    {
        return false;
    }

    return schema.emplace(fieldName, datatype).second;
}

Datatype SchemaConfig::getType(const std::string& fieldName) const
{
    try
    {
        auto it = schema.find(fieldName);

        if(it == schema.end())
        {
            throw std::invalid_argument("Field name not found in schema: " + fieldName);
        }

        return it->second;
    }
    catch(const std::exception& e)
    {
        throw std::invalid_argument("Field name not found in schema: " + fieldName);
    }

    return it->second;
}

bool SchemaConfig::contains(const std::string& fieldName) const
{
    return schema.find(fieldName) != schema.end();
}


bool SchemaConfig::validate(const std::string& fieldName, const std::string& value) const
{
    try
    {
        auto itr = schema.find(fieldName);

        if(itr == schema.end())
        {
            throw std::invalid_argument("Field name not found in schema: " + fieldName);
        }

        return DatatypeUtils::validate(value, itr->second);

    }
    catch(const std::exception& e)
    {
         std::cerr << "Error occurred: " << e.what() << std::endl;
    }
}

void SchemaConfig::printSchema() const
{
    std::cout << "\n================Schema==============\n" << std::endl;
    for (const auto& field : schema) {
        std::cout << "Field Name: " << field.first << ", Datatype: ";
        switch (field.second) {
            case Datatype::String:
                std::cout << "String";
                break;
            case Datatype::int32:
                std::cout << "int32";
                break;
            default:
                std::cout << "Unknown";
                break;
        }

        std::cout << "\n==============================\n" << std::endl;
        std::cout << std::endl;
    }
}

size_t SchemaConfig::size() const
{
    return schema.size();
}