#include <gtest/gtest.h>

#include <fstream>

#include "loader.h"
#include "Cluster.h"

class LoaderTest : public ::testing::Test
{
protected:

    Cluster cluster{4};

    SchemaConfig schema;

    Loader* loader;

    void SetUp() override
    {
        schema.addField("id",DataType::String);
        schema.addField("age",DataType::Int32);
        schema.addField("score",DataType::Int32);

        loader=new Loader(cluster,schema);
    }

    void TearDown() override
    {
        delete loader;

        std::remove("loader_test.csv");
    }
};

TEST_F(LoaderTest, LoadSingleFile)
{
    std::ofstream out("loader_test.csv");

    out<<"EMP001,25,500\n";
    out<<"EMP002,30,700\n";

    out.close();

    EXPECT_TRUE(loader->loadFromFile({"loader_test.csv"}));

    cluster.processNetwork();

    EXPECT_TRUE(cluster.contains("EMP001"));
    EXPECT_TRUE(cluster.contains("EMP002"));
}

TEST_F(LoaderTest, InvalidInteger)
{
    std::ofstream out("loader_test.csv");

    out<<"EMP001,ABC,100\n";

    out.close();

    EXPECT_FALSE(loader->loadFromFile({"loader_test.csv"}));
}

TEST_F(LoaderTest, InvalidColumnCount)
{
    std::ofstream out("loader_test.csv");

    out<<"EMP001,25\n";

    out.close();

    EXPECT_FALSE(loader->loadFromFile({"loader_test.csv"}));
}

TEST_F(LoaderTest, EmptyFile)
{
    std::ofstream out("loader_test.csv");

    out.close();

    EXPECT_TRUE(loader->loadFromFile({"loader_test.csv"}));
}

TEST_F(LoaderTest, DuplicateRecords)
{
    std::ofstream out("loader_test.csv");

    out<<"EMP001,25,100\n";
    out<<"EMP001,25,100\n";

    out.close();

    EXPECT_TRUE(loader->loadFromFile({"loader_test.csv"}));

    cluster.processNetwork();

    EXPECT_TRUE(cluster.contains("EMP001"));
}