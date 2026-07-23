#include<iostream>
#include "kvstore.h"
#include "InMemoryKVstore.h"
#include "loader.h"
#include "Cluster.h"

using namespace std;

int main() {
    // Create a cluster with 4 nodes
    Cluster cluster(5);

    // Create loader
    Loader loader(cluster);

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

    
    std::cout << "\n========== Load From Multiple Files ==========\n";

    std::vector<std::string> files =
    {
        "../data/node1.csv",
        "../data/node2.csv",
        "../data/node3.csv",
        "../data/node4.csv"
    };

    loader.loadFromFile(files);

    std::cout << "\n========== Verify Records Loaded From Files ==========\n";

    auto value = cluster.get("india");
    if (value)
        std::cout << "india -> " << *value << std::endl;

    value = cluster.get("banana");
    if (value)
        std::cout << "banana -> " << *value << std::endl;

    value = cluster.get("cpp");
    if (value)
        std::cout << "cpp -> " << *value << std::endl;

    std::cout << "\n========== Final Statistics ==========\n\n";

    cluster.printStatistics();

    return 0;
}
