#include "Serializer.h"

#include<sstream>
#include<stdexcept>
#include<string>


std::vector<uint8_t> Serializer::serialize(const Record& record)
{
    std::ostringstream stream;

    // Write record key
    stream << record.getKey();

    // Write field values
    for (const auto& value : record.getValues())
    {
        stream << "|" << value;
    }

    std::string serialized = stream.str();

    return std::vector<uint8_t>(
        serialized.begin(),
        serialized.end());
}

        
Record Serializer::deserialize(const std::vector<uint8_t>& buffer)
{
    try
    {
        if (buffer.empty())
        {
            throw std::runtime_error(
            "Cannot deserialize an empty packet.");
        }

        std::string data(buffer.begin(), buffer.end());

        std::stringstream stream(data);

        std::string token;

        if (!std::getline(stream, token, '|'))
        {
            throw std::runtime_error(
                "Failed to deserialize record key.");
        }

        Record record;

        record.setKey(token);

        // Read remaining values
        while (std::getline(stream, token, '|'))
        {
            record.addValue(token);
        }

        return record;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}