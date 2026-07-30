#include <gtest/gtest.h>

#include "Record.h"

TEST(RecordTest, DefaultConstructor)
{
    Record r;

    EXPECT_TRUE(r.getKey().empty());

    EXPECT_TRUE(r.getValues().empty());
}

TEST(RecordTest, SetKey)
{
    Record r;

    r.setKey("EMP001");

    EXPECT_EQ(r.getKey(), "EMP001");
}

TEST(RecordTest, AddValue)
{
    Record r;

    r.setKey("EMP001");

    r.addValue("25");

    r.addValue("500");

    EXPECT_EQ(r.size(),2);

    EXPECT_EQ(r.getValue(0),"25");

    EXPECT_EQ(r.getValue(1),"500");
}