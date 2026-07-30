#pragma once

#include<iostream>
#include<memory>
#include<optional>
#include<string>
#include<vector>

#include "Node.h"
#include "Record.h"
#include "Partitioner.h"

class Cluster
{
    private:
        std::vector<std::unique_ptr<Node>> nodes;
        Partitioner partitioner;

        
        //Node& getOwnerNode(const std::string& key);
        //const Node& getOwnerNode(const std::string& key) const;
        
        
    public:
         explicit Cluster(size_t numNodes);

         Cluster(const Cluster& other) = delete; // Delete copy constructor
         Cluster& operator=(const Cluster& other) = delete; // Delete copy assignment

         Cluster(Cluster&& other) = default; // Default move constructor

         Cluster& operator=(Cluster&& other) = default; // Default move assignment

         ~Cluster() = default;

         bool put(const Record& record);

         std::optional<Record> get(const std::string& key) const;

         bool erase(const std::string& key);

         bool contains(const std::string& key) const;

         void processNetwork();

         size_t numberOfNodes() const;

         void printStatistics() const;

         //Reporting functions

         //void printStatistics() const;

         void printOwnershipReport() const;

         void verifyOwnership() const;

         void printLoadDistribution() const;
};