#include<iostream>
#include "kvstore.h"
#include "InMemoryKVstore.h"
#include "loader.h"
#include "Cluster.h"
#include "Logger.h"

#include "ConfigParser.h"
#include "SchemaConfig.h"
#include "NetworkMock.h"

using namespace std;

int main(int argc, char* argv[]) {
    //----------------------------------------------------------
    // Parse Configuration
    //----------------------------------------------------------
        ConfigParser configParser;

        configParser.parse("../config.txt");

        if(Logger::isDebugEnabled()){
            std::cout << "\n========== Configuration ==========\n";

        
            std::cout << "Nodes : "
                    << configParser.getNumberOfNodes()
                    << std::endl;
        }

        if(Logger::isDebugEnabled())
        {
            configParser.getSchemaConfig().printSchema();
        }

    //----------------------------------------------------------
    // Create Cluster
    //----------------------------------------------------------

        auto cluster = std::make_shared<Cluster>(
            configParser.getNumberOfNodes());

    //----------------------------------------------------------
    // Create Loader
    //----------------------------------------------------------

        Loader loader(
            *cluster,
            configParser.getSchemaConfig());
    

    std::vector<std::string> files;
    //reading the filenames through command line        
    if (argc < 2)
    {
        std::cerr << "Usage:\n";
        std::cerr << "./kvstore_app <csv-file1> <csv-file2> ...\n";
        return 1;
    }

    for (int i = 1; i < argc; ++i)
    {
        files.emplace_back(argv[i]);
    }

    //std::cout << "\n========== Load From Multiple Files ==========\n";

    if(loader.loadFromFile(files))
    {
        if(Logger::isDebugEnabled()){
        std::cout
            << "All records loaded successfully.\n";
        }
    }
    else
    {
        if(Logger::isDebugEnabled()){
        std::cout
            << "Some records failed to load.\n";
        }
    }

    std::cout<< "\n========== Processing Network ==========\n";

    cluster->processNetwork();

    NetworkMock::printStatistics();

    cluster->printOwnershipReport();

    cluster->verifyOwnership();

    cluster->printLoadDistribution();

    cluster->printStatistics();
    
    return 0;
}
