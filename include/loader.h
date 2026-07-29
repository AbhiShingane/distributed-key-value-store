#include<iostream>
#include<string>
#include"Record.h"
#include<vector>

#include "SchemaConfig.h"

class Cluster;

class Loader
{
    private:
        Cluster& clusterobj;
        const SchemaConfig& schemaConfig;
        bool processline(const std::string& line);
        Record parseRecord(const std::string& line);
        
    public:
        explicit Loader(Cluster& cluster, const SchemaConfig& schconfig);


        Loader(const Loader& other) = delete; // Delete copy constructor
        Loader& operator=(const Loader& other) = delete; // Delete copy assignment

        Loader(Loader&& other) = delete; // Delete move constructor

        Loader& operator=(Loader&& other) = delete; // Delete move assignment

        ~Loader() = default;

       bool load(const Record& record);

       bool loadFromFile(const std::vector<std::string>& fileNames);
};