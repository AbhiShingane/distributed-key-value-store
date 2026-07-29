#include<iostream>
#include "ConfigParser.h"

#include<fstream>
#include<sstream>
#include<stdexcept>
#include<algorithm>

bool ConfigParser::parse(const std::string& filename)
{
    std::ifstream inputfile(filename);

    try
    {
        if(!inputfile.is_open())
        {
            throw std::runtime_error("unable to open the configuration file: "+ filename);
        }

        std::string line;

        while(std::getline(inputfile, line))
        {
            line = trim(line);

            if(line.empty())
                continue;

            if(line[0] == '#')
                continue;

            if(line.rfind("nodes=", 0) == 0)
            {
                parseNodes(line);
            }
            else if(line.rfind("field=", 0) == 0)
            {
                parseField(line);
            }
            else
            {
                std::cerr << "Invalid config entry: "<< line<<'\n';
            }
        }

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    if (numberOfNodes == 0)
    {
        throw std::runtime_error(
            "Cluster configuration missing 'nodes=' entry.");
    }

    return true;
     
}
    
void ConfigParser::parseNodes(const std::string& line)
{
    std::string value = line.substr(6);

    try
    {
        numberOfNodes = std::stoul(value);

        if (numberOfNodes == 0)
        {
            throw std::runtime_error(
                "Number of nodes must be greater than zero.");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }


   return; 
}

void ConfigParser::parseField(const std::string& line)
{
    std::string def = line.substr(6);

    std::stringstream ss(def);

    std::string fname;
    std::string ftype;
    
    try
    {
        if(!std::getline(ss, fname, ','))
        {
             throw std::runtime_error(
            "Invalid schema definition : " + line);
        }

        if (!std::getline(ss, ftype))
        {
            throw std::runtime_error(
                "Invalid schema definition : " + line);
        }

        fname = trim(fname);
        ftype = trim(ftype);
        
        /*std::cout << "Definition: [" << def << "]\n";
        std::cout << "Field Name: [" << fname << "]\n";
        std::cout << "Field Type: [" << ftype << "]\n";
        std::cout << "Length: " << ftype.length() << std::endl;*/

        DataType type = DataTypeUtils::fromString(ftype);
        

        std::cout<<"fname: "<<fname<<" ftype: "<<ftype<<std::endl; 
        if(!schemaconfig.addField(fname, type))
        {
            throw std::runtime_error(
                "Duplicate schema field : " + fname);
        }


    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
}

size_t ConfigParser::getNumberOfNodes() const
{
    return numberOfNodes;
}

const SchemaConfig& ConfigParser::getSchemaConfig() const
{
    return schemaconfig;
}

std::string ConfigParser::trim(const std::string& str)
{
    const auto begin =
        str.find_first_not_of(" \t\r\n");

    if (begin == std::string::npos)
    {
        return "";
    }

    const auto end =
        str.find_last_not_of(" \t\r\n");

    return str.substr(begin, end - begin + 1);
}