#include <gtest/gtest.h>

#include "InMemoryKVstore.h"

class KVStoreTest : public ::testing::Test
{
protected:

    InMemoryKVStore store;

    Record createRecord(std::string key)
    {
        Record r;

        r.setKey(key);

        r.addValue("25");
        r.addValue("100");

        return r;
    }
};

TEST_F(KVStoreTest, InsertRecord)
{
    EXPECT_TRUE(store.set(createRecord("EMP001")));

    EXPECT_EQ(store.size(),1);
}

TEST_F(KVStoreTest, DuplicateRecord)
{
    store.set(createRecord("EMP001"));

    store.set(createRecord("EMP001"));

    EXPECT_EQ(store.size(),1);
}

TEST_F(KVStoreTest, Exists)
{
    store.set(createRecord("EMP001"));

    EXPECT_TRUE(store.exists("EMP001"));

    EXPECT_FALSE(store.exists("EMP100"));
}

TEST_F(KVStoreTest, GetRecord)
{
    store.set(createRecord("EMP001"));

    auto result=store.get("EMP001");

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result->getKey(),"EMP001");
}

TEST_F(KVStoreTest, DeleteRecord)
{
    store.set(createRecord("EMP001"));

    EXPECT_TRUE(store.del("EMP001"));

    EXPECT_FALSE(store.exists("EMP001"));
}

TEST_F(KVStoreTest, DeleteUnknownRecord)
{
    EXPECT_FALSE(store.del("EMP500"));
}

TEST_F(KVStoreTest, AllKeys)
{
    store.set(createRecord("EMP001"));
    store.set(createRecord("EMP002"));

    EXPECT_EQ(store.getAllKeys().size(),2);
}

TEST_F(KVStoreTest, AllRecords)
{
    store.set(createRecord("EMP001"));
    store.set(createRecord("EMP002"));

    EXPECT_EQ(store.getAllRecords().size(),2);
}