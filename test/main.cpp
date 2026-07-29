#include<iostream>
#include "kvstore.h"
#include "InMemoryKVstore.h"
#include "loader.h"
#include "Cluster.h"

#include "ConfigParser.h"
#include "SchemaConfig.h"

using namespace std;

int main() {
    /*std::cout << "========== Direct Record Loading ==========\n";

    loader.load("Apple", "Fruit");
    loader.load("Dog", "Animal");
    loader.load("Car", "Vehicle");
    loader.load("Tiger", "Wild Animal");
    loader.load("Laptop", "Electronics");

    std::cout << "\n========== Fetch Records ==========\n";

    auto value = cluster.get("Apple");

    if (value.has_value())
        std::cout << "Apple -> " << value.value() << std::endl;

    value = cluster.get("Dog");

    if (value.has_value())
        std::cout << "Dog -> " << value.value() << std::endl;

    std::cout << "\n========== Contains ==========\n";

    std::cout << "Contains Apple : "
              << (cluster.contains("Apple") ? "Yes" : "No")
              << std::endl;

    std::cout << "Contains Phone : "
              << (cluster.contains("Phone") ? "Yes" : "No")
              << std::endl;

    std::cout << "\n========== Delete ==========\n";

    cluster.erase("Dog");

    std::cout << "Contains Dog : "
              << (cluster.contains("Dog") ? "Yes" : "No")
              << std::endl;

    std::cout << "\n========== Cluster Statistics ==========\n";

    cluster.printStatistics();*/

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

    /*auto record = cluster->get("EMP001");

    if(record.has_value())
    {
        std::cout
            << "record present"
            << std::endl;
    }
    else
    {
        std::cout
            << "Record not found.\n";
    }*/
    //----------------------------------------------------------
        // Cluster Statistics
        //----------------------------------------------------------

    /*    std::cout
            << "\n========== Cluster Statistics ==========\n";

        cluster->printStatistics();

        //----------------------------------------------------------
        // GET Test
        //----------------------------------------------------------

        std::cout
            << "\n========== GET ==========\n";

        auto record = cluster->get("EMP001");

        if(record.has_value())
        {
            std::cout
                << record->toString()
                << std::endl;
        }
        else
        {
            std::cout
                << "Record not found.\n";
        }

        //----------------------------------------------------------
        // PUT Test
        //----------------------------------------------------------

        std::cout
            << "\n========== PUT ==========\n";

        Record employee;

        employee.setKey("EMP100");

        employee.addValue("28");

        employee.addValue("91");

        cluster->put(employee);

        std::cout
            << "Inserted EMP100\n";

        //----------------------------------------------------------
        // GET Again
        //----------------------------------------------------------

        auto inserted = cluster->get("EMP100");

        if(inserted.has_value())
        {
            std::cout
                << inserted->toString()
                << std::endl;
        }

        //----------------------------------------------------------
        // DELETE Test
        //----------------------------------------------------------

        std::cout
            << "\n========== DELETE ==========\n";

        if(cluster->erase("EMP100"))
        {
            std::cout
                << "EMP100 deleted successfully.\n";
        }

        //----------------------------------------------------------
        // Verify Delete
        //----------------------------------------------------------

        auto deleted = cluster->get("EMP100");

        if(!deleted.has_value())
        {
            std::cout
                << "Verified deletion.\n";
        }*/

    std::cout << "\n========== Final Statistics ==========\n\n";

    cluster->printStatistics();

    return 0;
}
