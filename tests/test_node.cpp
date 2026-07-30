#include <gtest/gtest.h>

#include "Node.h"
#include "Record.h"

class NodeTest : public ::testing::Test
{
protected:
    Node node{0};

    Record createRecord(const std::string& key)
    {
        Record record;

        record.setKey(key);

        record.addValue("25");
        record.addValue("500");

        return record;
    }
};

TEST_F(NodeTest, PutRecord)
{
    auto record = createRecord("EMP001");

    EXPECT_TRUE(node.put(record));

    EXPECT_EQ(node.size(), 1);
}

TEST_F(NodeTest, GetRecord)
{
    auto record = createRecord("EMP001");

    node.put(record);

    auto result = node.get("EMP001");

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result->getKey(), "EMP001");
}

TEST_F(NodeTest, DeleteRecord)
{
    auto record = createRecord("EMP001");

    node.put(record);

    EXPECT_TRUE(node.erase("EMP001"));

    EXPECT_EQ(node.size(),0);
}

TEST_F(NodeTest, Contains)
{
    auto record=createRecord("EMP001");

    node.put(record);

    EXPECT_TRUE(node.contains("EMP001"));

    EXPECT_FALSE(node.contains("EMP500"));
}

TEST_F(NodeTest, DuplicateInsert)
{
    auto record=createRecord("EMP001");

    node.put(record);

    node.put(record);

    EXPECT_EQ(node.size(),1);
}

TEST_F(NodeTest, GetStoredKeys)
{
    node.put(createRecord("EMP001"));
    node.put(createRecord("EMP002"));

    auto keys=node.getStoredKeys();

    EXPECT_EQ(keys.size(),2);
}

TEST_F(NodeTest, GetAllRecords)
{
    node.put(createRecord("EMP001"));
    node.put(createRecord("EMP002"));

    auto records=node.getAllRecords();

    EXPECT_EQ(records.size(),2);
}