#include <gtest/gtest.h>

#include "Cluster.h"

class ClusterTest : public ::testing::Test
{
protected:

    Cluster cluster{4};

    Record createRecord(std::string key)
    {
        Record r;

        r.setKey(key);

        r.addValue("20");
        r.addValue("200");

        return r;
    }
};

TEST_F(ClusterTest, PutRecord)
{
    EXPECT_TRUE(cluster.put(createRecord("EMP001")));
}

TEST_F(ClusterTest, ProcessNetwork)
{
    cluster.put(createRecord("EMP001"));

    cluster.processNetwork();

    EXPECT_TRUE(cluster.contains("EMP001"));
}

TEST_F(ClusterTest, GetRecord)
{
    cluster.put(createRecord("EMP001"));

    cluster.processNetwork();

    auto result=cluster.get("EMP001");

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result->getKey(),"EMP001");
}

TEST_F(ClusterTest, DeleteRecord)
{
    cluster.put(createRecord("EMP001"));

    cluster.processNetwork();

    EXPECT_TRUE(cluster.erase("EMP001"));

    EXPECT_FALSE(cluster.contains("EMP001"));
}

TEST_F(ClusterTest, NodeCount)
{
    EXPECT_EQ(cluster.numberOfNodes(),4);
}

TEST_F(ClusterTest, DuplicateRecord)
{
    cluster.put(createRecord("EMP001"));

    cluster.put(createRecord("EMP001"));

    cluster.processNetwork();

    EXPECT_TRUE(cluster.contains("EMP001"));
}

TEST_F(ClusterTest, OwnershipVerification)
{
    cluster.put(createRecord("EMP001"));

    cluster.processNetwork();

    EXPECT_NO_THROW(cluster.verifyOwnership());
}

TEST_F(ClusterTest, PrintStatistics)
{
    EXPECT_NO_THROW(cluster.printStatistics());
}