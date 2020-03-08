#include <iostream>

#include <gtest/gtest.h>

#include <SimpleOrderBook.h>

class SimpleOrderBookTest : public ::testing::Test {
protected:

    virtual void SetUp()
    {
	SimpleMessageReader reader(orderBook_);
	reader.read("data/sample.csv");
    }

    SimpleOrderBook orderBook_;
};

TEST_F(SimpleOrderBookTest, haveTenBids)
{
    EXPECT_EQ(orderBook_.bidSize(), 10);
}

TEST_F(SimpleOrderBookTest, haveTenAsks)
{
    EXPECT_EQ(orderBook_.askSize(), 10);
}

TEST_F(SimpleOrderBookTest, verifyAllBids)
{
    EXPECT_EQ(orderBook_.bid(0).quantity(), 100);
    EXPECT_EQ(orderBook_.bid(0).price(), 239.55);
    EXPECT_EQ(orderBook_.bid(1).quantity(), 280);
    EXPECT_EQ(orderBook_.bid(1).price(), 239.50);
    EXPECT_EQ(orderBook_.bid(2).quantity(), 200);
    EXPECT_EQ(orderBook_.bid(2).price(), 239.45);
    EXPECT_EQ(orderBook_.bid(3).quantity(), 50);
    EXPECT_EQ(orderBook_.bid(3).price(), 239.35);
    EXPECT_EQ(orderBook_.bid(4).quantity(), 200);
    EXPECT_EQ(orderBook_.bid(4).price(), 239.30);
    EXPECT_EQ(orderBook_.bid(5).quantity(), 125);
    EXPECT_EQ(orderBook_.bid(5).price(), 239.25);
    EXPECT_EQ(orderBook_.bid(6).quantity(), 140);
    EXPECT_EQ(orderBook_.bid(6).price(), 239.15);
    EXPECT_EQ(orderBook_.bid(7).quantity(), 250);
    EXPECT_EQ(orderBook_.bid(7).price(), 239.05);
    EXPECT_EQ(orderBook_.bid(8).quantity(), 100);
    EXPECT_EQ(orderBook_.bid(8).price(), 239.00);
    EXPECT_EQ(orderBook_.bid(9).quantity(), 50);
    EXPECT_EQ(orderBook_.bid(9).price(), 238.95);
}

TEST_F(SimpleOrderBookTest, verifyAllAsks)
{
    EXPECT_EQ(orderBook_.ask(9).quantity(), 40);
    EXPECT_EQ(orderBook_.ask(9).price(), 240.10);
    EXPECT_EQ(orderBook_.ask(8).quantity(), 50);
    EXPECT_EQ(orderBook_.ask(8).price(), 240.05);
    EXPECT_EQ(orderBook_.ask(7).quantity(), 180);
    EXPECT_EQ(orderBook_.ask(7).price(), 239.95);
    EXPECT_EQ(orderBook_.ask(6).quantity(), 400);
    EXPECT_EQ(orderBook_.ask(6).price(), 239.90);
    EXPECT_EQ(orderBook_.ask(5).quantity(), 500);
    EXPECT_EQ(orderBook_.ask(5).price(), 239.85);
    EXPECT_EQ(orderBook_.ask(4).quantity(), 150);
    EXPECT_EQ(orderBook_.ask(4).price(), 239.80);
    EXPECT_EQ(orderBook_.ask(3).quantity(), 120);
    EXPECT_EQ(orderBook_.ask(3).price(), 239.75);
    EXPECT_EQ(orderBook_.ask(2).quantity(), 390);
    EXPECT_EQ(orderBook_.ask(2).price(), 239.70);
    EXPECT_EQ(orderBook_.ask(1).quantity(), 300);
    EXPECT_EQ(orderBook_.ask(1).price(), 239.65);
    EXPECT_EQ(orderBook_.ask(0).quantity(), 75);
    EXPECT_EQ(orderBook_.ask(0).price(), 239.60);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
