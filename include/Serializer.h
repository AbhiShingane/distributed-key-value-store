#pragma once

#include<iostream>
#include<cstdint>

#include "Record.h"

class Serializer
{
    public:
        Serializer() = delete;
        ~Serializer() = delete;

        // Serialize a Record into a byte buffer
        static std::vector<uint8_t> serialize(const Record& record);

        // Deserialize a byte buffer back into a Record
        static Record deserialize(const std::vector<uint8_t>& buffer);
};