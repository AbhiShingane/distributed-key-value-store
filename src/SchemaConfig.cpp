#include "SchemaConfig.h"
#include <stdexcept>

bool SchemaConfig::addField(const std::string& fieldName, DataType datatype)
{
    if(schema.find(fieldName) != schema.end())
    {
        return false;
    }

    schema[fieldName] = datatype;

    fields.push_back({fieldName, datatype});

    return true;
}

DataType SchemaConfig::getType(const std::string& fieldName) const
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

    //return it->second;
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

        return DataTypeUtils::validate(itr->second, value);

    }
    catch(const std::exception& e)
    {
         std::cerr << "Error occurred: " << e.what() << std::endl;
    }
}


bool SchemaConfig::validateRecord(
        const std::vector<std::string>& values) const
{
    if(values.size() != fields.size())
    {
        throw std::runtime_error(
            "Expected " +
            std::to_string(fields.size()) +
            " fields but received " +
            std::to_string(values.size()));
    }

    for(size_t i = 0; i < fields.size(); ++i)
    {
        if(!DataTypeUtils::validate(fields[i].type,
                                    values[i]))
        {
            throw std::runtime_error(
                "Invalid value '" +
                values[i] +
                "' for field '" +
                fields[i].name + "'");
        }
    }

    return true;
}

const std::vector<FieldDefinition>& SchemaConfig::getFields() const
{
    return fields;
}

void SchemaConfig::printSchema() const
{
    std::cout << "\n================Schema==============\n" << std::endl;
    for (const auto& field : schema) {
        std::cout << "Field Name: " << field.first << ", Datatype: ";
        switch (field.second) {
            case DataType::String:
                std::cout << "String";
                break;
            case DataType::Int32:
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
    return fields.size();
}