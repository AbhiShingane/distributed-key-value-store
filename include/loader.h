#include<iostream>
#include<string>
#include"Record.h"
#include<vector>

class Cluster;

class Loader
{
    private:
        Cluster& clusterobj;
    
        bool processline(const std::string& line);

    public:
        explicit Loader(Cluster& cluster);


        Loader(const Loader& other) = delete; // Delete copy constructor
        Loader& operator=(const Loader& other) = delete; // Delete copy assignment

        Loader(Loader&& other) = delete; // Delete move constructor

        Loader& operator=(Loader&& other) = delete; // Delete move assignment

        ~Loader() = default;

       bool load(const std::string& key, const std::string& value);

       bool loadFromFile(const std::vector<std::string>& fileNames);
};