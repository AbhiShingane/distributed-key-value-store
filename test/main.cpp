#include<iostream>
#include "kvstore.h"
#include "InMemoryKVstore.h"
#include "loader.h"
#include "Cluster.h"

#include "ConfigParser.h"
#include "SchemaConfig.h"

using namespace std;

int main() {
    //----------------------------------------------------------
    // Parse Configuration
    //----------------------------------------------------------
        ConfigParser configParser;

        configParser.parse("../config.txt");

        std::cout << "\n========== Configuration ==========\n";

        std::cout << "Nodes : "
                  << configParser.getNumberOfNodes()
                  << std::endl;

        configParser.getSchemaConfig().printSchema();

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
    
    std::cout << "\n========== Load From Multiple Files ==========\n";

    std::vector<std::string> files =
    {
        "../data/node1.csv",
        "../data/node2.csv",
        "../data/node3.csv",
        "../data/node4.csv"
    };

    if(loader.loadFromFile(files))
    {
        std::cout
            << "All records loaded successfully.\n";
    }
    else
    {
        std::cout
            << "Some records failed to load.\n";
    }

    std::cout<< "\n========== Processing Network ==========\n";

    cluster->processNetwork();

    //--------------------------------------------------------
    // Print Cluster Statistics
    //--------------------------------------------------------
    std::cout<< "\n========== Cluster Statistics ==========\n";

    cluster->printStatistics();
    return 0;
}
