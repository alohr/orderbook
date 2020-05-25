#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <LobsterOrderBook.h>

using ::testing::AtLeast;
using ::testing::AnyNumber;
using ::testing::AllOf;
using ::testing::Field;


class LobsterTest : public ::testing::Test
{
protected:
    PriceLevelVector initialBids()
    {
        PriceLevelVector bids(greater);
        bids.insert(LobsterMessage{0, 0, LobsterEvent::NEW, 1, 100, 10, LobsterSide::BUY});
        bids.insert(LobsterMessage{0, 0, LobsterEvent::NEW, 2, 100,  9, LobsterSide::BUY});
        bids.insert(LobsterMessage{0, 0, LobsterEvent::NEW, 3, 100,  7, LobsterSide::BUY});
        return bids;
    }

    PriceLevelVector initialAsks()
    {
        PriceLevelVector asks(less);
        asks.insert(LobsterMessage{0, 0, LobsterEvent::NEW, 1, 100, 11, LobsterSide::SELL});
        asks.insert(LobsterMessage{0, 0, LobsterEvent::NEW, 2, 100, 12, LobsterSide::SELL});
        asks.insert(LobsterMessage{0, 0, LobsterEvent::NEW, 3, 100, 14, LobsterSide::SELL});
        return asks;
    }
};

TEST_F(LobsterTest, Bids)
{
    PriceLevelVector bids = initialBids();
    EXPECT_EQ(bids.size(), 3);

    EXPECT_EQ(bids[0].price(), 10);
    EXPECT_EQ(bids[0].size(), 100);
    EXPECT_EQ(bids[0].n(), 1);

    EXPECT_EQ(bids[1].price(), 9);
    EXPECT_EQ(bids[1].size(), 100);
    EXPECT_EQ(bids[1].n(), 1);

    EXPECT_EQ(bids[2].price(), 7);
    EXPECT_EQ(bids[2].size(), 100);
    EXPECT_EQ(bids[2].n(), 1);
}

TEST_F(LobsterTest, Asks)
{
    PriceLevelVector asks = initialAsks();
    EXPECT_EQ(asks.size(), 3);

    EXPECT_EQ(asks[0].price(), 11);
    EXPECT_EQ(asks[0].size(), 100);
    EXPECT_EQ(asks[0].n(), 1);
    
    EXPECT_EQ(asks[1].price(), 12);
    EXPECT_EQ(asks[1].size(), 100);
    EXPECT_EQ(asks[1].n(), 1);
    
    EXPECT_EQ(asks[2].price(), 14);
    EXPECT_EQ(asks[2].size(), 100);
    EXPECT_EQ(asks[2].n(), 1);
}

TEST_F(LobsterTest, Book)
{
    LobsterOrderBook book;
    book.onNew(LobsterMessage{0, 0, LobsterEvent::NEW, 1, 100, 10, LobsterSide::BUY});
    book.onNew(LobsterMessage{0, 0, LobsterEvent::NEW, 2, 100,  9, LobsterSide::BUY});
    book.onNew(LobsterMessage{0, 0, LobsterEvent::NEW, 3, 100,  7, LobsterSide::BUY});
}

/*
 * Bid - New Orders
 */

TEST_F(LobsterTest, BidAddFront)
{
    PriceLevelVector bids = initialBids();

    bids.insert(LobsterMessage{0, 0, LobsterEvent::NEW, 4, 100, 11, LobsterSide::BUY});
    EXPECT_EQ(bids.size(), 4);

    EXPECT_EQ(bids[0].price(), 11);
    EXPECT_EQ(bids[0].size(), 100);
    EXPECT_EQ(bids[0].n(), 1);
    
    EXPECT_EQ(bids[1].price(), 10);
    EXPECT_EQ(bids[1].size(), 100);
    EXPECT_EQ(bids[1].n(), 1);
    
    EXPECT_EQ(bids[2].price(), 9);
    EXPECT_EQ(bids[2].size(), 100);
    EXPECT_EQ(bids[2].n(), 1);
    
    EXPECT_EQ(bids[3].price(), 7);
    EXPECT_EQ(bids[3].size(), 100);
    EXPECT_EQ(bids[3].n(), 1);
}

TEST_F(LobsterTest, BidAddMiddle)
{
    PriceLevelVector bids = initialBids();

    bids.insert(LobsterMessage{0, 0, LobsterEvent::NEW, 4, 100, 8, LobsterSide::BUY});
    EXPECT_EQ(bids.size(), 4);

    EXPECT_EQ(bids[0].price(), 10);
    EXPECT_EQ(bids[0].size(), 100);
    EXPECT_EQ(bids[0].n(), 1);
    
    EXPECT_EQ(bids[1].price(), 9);
    EXPECT_EQ(bids[1].size(), 100);
    EXPECT_EQ(bids[1].n(), 1);
    
    EXPECT_EQ(bids[2].price(), 8);
    EXPECT_EQ(bids[2].size(), 100);
    EXPECT_EQ(bids[2].n(), 1);
    
    EXPECT_EQ(bids[3].price(), 7);
    EXPECT_EQ(bids[3].size(), 100);
    EXPECT_EQ(bids[3].n(), 1);
}

TEST_F(LobsterTest, BidAddBack)
{
    PriceLevelVector bids = initialBids();

    bids.insert(LobsterMessage{0, 0, LobsterEvent::NEW, 4, 100, 6, LobsterSide::BUY});
    EXPECT_EQ(bids.size(), 4);

    EXPECT_EQ(bids[0].price(), 10);
    EXPECT_EQ(bids[0].size(), 100);
    EXPECT_EQ(bids[0].n(), 1);
    
    EXPECT_EQ(bids[1].price(), 9);
    EXPECT_EQ(bids[1].size(), 100);
    EXPECT_EQ(bids[1].n(), 1);
    
    EXPECT_EQ(bids[2].price(), 7);
    EXPECT_EQ(bids[2].size(), 100);
    EXPECT_EQ(bids[2].n(), 1);
    
    EXPECT_EQ(bids[3].price(), 6);
    EXPECT_EQ(bids[3].size(), 100);
    EXPECT_EQ(bids[3].n(), 1);
}

TEST_F(LobsterTest, BidAddToLevel)
{
    PriceLevelVector bids = initialBids();

    bids.insert(LobsterMessage{0, 0, LobsterEvent::NEW, 4, 100, 9, LobsterSide::BUY});
    EXPECT_EQ(bids.size(), 3);

    EXPECT_EQ(bids[0].price(), 10);
    EXPECT_EQ(bids[0].size(), 100);
    EXPECT_EQ(bids[0].n(), 1);
    
    EXPECT_EQ(bids[1].price(), 9);
    EXPECT_EQ(bids[1].size(), 200);
    EXPECT_EQ(bids[1].n(), 2);
    
    EXPECT_EQ(bids[2].price(), 7);
    EXPECT_EQ(bids[2].size(), 100);
    EXPECT_EQ(bids[2].n(), 1);
}

/*
 * Bid - Partial Cancel
 */

TEST_F(LobsterTest, BidCancelPartial)
{
    PriceLevelVector bids = initialBids();
    bids.cancelPartial(LobsterMessage{0, 0, LobsterEvent::CANCEL_PARTIAL, 1, 20, 10, LobsterSide::BUY});
    bids.cancelPartial(LobsterMessage{0, 0, LobsterEvent::CANCEL_PARTIAL, 2, 30,  9, LobsterSide::BUY});
    bids.cancelPartial(LobsterMessage{0, 0, LobsterEvent::CANCEL_PARTIAL, 3, 40,  7, LobsterSide::BUY});
    bids.cancelPartial(LobsterMessage{0, 0, LobsterEvent::CANCEL_PARTIAL, 5, 20, 10, LobsterSide::BUY}); // does not exist

    EXPECT_EQ(bids.size(), 3);

    EXPECT_EQ(bids[0].price(), 10);
    EXPECT_EQ(bids[0].size(), 80);
    EXPECT_EQ(bids[0].n(), 1);

    EXPECT_EQ(bids[1].price(), 9);
    EXPECT_EQ(bids[1].size(), 70);
    EXPECT_EQ(bids[1].n(), 1);

    EXPECT_EQ(bids[2].price(), 7);
    EXPECT_EQ(bids[2].size(), 60);
    EXPECT_EQ(bids[2].n(), 1);
}

/*
 * Bid - Full Cancel
 */

TEST_F(LobsterTest, BidCancelFull) {
    PriceLevelVector bids = initialBids();
    bids.cancelFull(LobsterMessage{0, 0, LobsterEvent::CANCEL_FULL, 2, 100, 9, LobsterSide::BUY});

    EXPECT_EQ(bids.size(), 2);

    EXPECT_EQ(bids[0].price(), 10);
    EXPECT_EQ(bids[0].size(), 100);
    EXPECT_EQ(bids[01].n(), 1);

    EXPECT_EQ(bids[1].price(), 7);
    EXPECT_EQ(bids[1].size(), 100);
    EXPECT_EQ(bids[1].n(), 1);
}

TEST_F(LobsterTest, BidCancelFullInLevel) {
    PriceLevelVector bids = initialBids();
    bids.insert(LobsterMessage{0, 0, LobsterEvent::NEW, 4, 10, 9, LobsterSide::BUY});
    bids.insert(LobsterMessage{0, 0, LobsterEvent::NEW, 5, 20, 9, LobsterSide::BUY});

    EXPECT_EQ(bids.size(), 3);

    EXPECT_EQ(bids[0].price(), 10);
    EXPECT_EQ(bids[0].size(), 100);
    EXPECT_EQ(bids[0].n(), 1);

    EXPECT_EQ(bids[1].price(), 9);
    EXPECT_EQ(bids[1].size(),  130);
    EXPECT_EQ(bids[1].n(), 3);
    EXPECT_EQ(bids[1][0].orderId(), 2);
    EXPECT_EQ(bids[1][1].orderId(), 4);
    EXPECT_EQ(bids[1][2].orderId(), 5);

    EXPECT_EQ(bids[2].price(), 7);
    EXPECT_EQ(bids[2].size(), 100);
    EXPECT_EQ(bids[2].n(), 1);

    bids.cancelFull(LobsterMessage{0, 0, LobsterEvent::CANCEL_FULL, 4, 10, 9, LobsterSide::BUY});

    EXPECT_EQ(bids.size(), 3);

    EXPECT_EQ(bids[1].price(), 9);
    EXPECT_EQ(bids[1].size(),  120);
    EXPECT_EQ(bids[1].n(), 2);
    EXPECT_EQ(bids[1][0].orderId(), 2);
    EXPECT_EQ(bids[1][1].orderId(), 5);
}


/*
 * Bid - Partial Executions
 */

TEST_F(LobsterTest, BidPartialExecutions) {
    PriceLevelVector bids(greater);

    bids.insert(
        LobsterMessage{34508, 783609173, LobsterEvent::NEW, 23443871, 100, 5868500, LobsterSide::BUY}
    );
    bids.onExecVisible(
        LobsterMessage{34508, 784367913, LobsterEvent::EXEC_VISIBLE, 23443871, 5, 5868500, LobsterSide::BUY}
    );

    EXPECT_EQ(bids.size(), 1);
    EXPECT_EQ(bids[0].price(), 5868500);
    EXPECT_EQ(bids[0].size(), 95);
    EXPECT_EQ(bids[0].n(), 1);
}

TEST_F(LobsterTest, BidPartialExecutionsUntilGone) {
    PriceLevelVector bids(greater);

    bids.insert(
            LobsterMessage{34508, 783609173, LobsterEvent::NEW, 23443871, 100, 5868500, LobsterSide::BUY}
    );
    bids.onExecVisible(
            LobsterMessage{34508, 784367913, LobsterEvent::EXEC_VISIBLE, 23443871, 5, 5868500, LobsterSide::BUY}
    );
    bids.onExecVisible(
            LobsterMessage{34508, 784611721, LobsterEvent::EXEC_VISIBLE, 23443871, 95, 5868500, LobsterSide::BUY}
    );

    EXPECT_EQ(bids.size(), 0);
}

/*
 * Ask - New Orders
 */

TEST_F(LobsterTest, AskAddFront)
{
    PriceLevelVector asks = initialAsks();

    asks.insert(LobsterMessage{0, 0, LobsterEvent::NEW, 4, 100, 10, LobsterSide::SELL});
    EXPECT_EQ(asks.size(), 4);

    EXPECT_EQ(asks[0].price(), 10);
    EXPECT_EQ(asks[0].size(), 100);
    EXPECT_EQ(asks[0].n(), 1);
    
    EXPECT_EQ(asks[1].price(), 11);
    EXPECT_EQ(asks[1].size(), 100);
    EXPECT_EQ(asks[1].n(), 1);
    
    EXPECT_EQ(asks[2].price(), 12);
    EXPECT_EQ(asks[2].size(), 100);
    EXPECT_EQ(asks[2].n(), 1);
    
    EXPECT_EQ(asks[3].price(), 14);
    EXPECT_EQ(asks[3].size(), 100);
    EXPECT_EQ(asks[3].n(), 1);
}

TEST_F(LobsterTest, AskAddMiddle)
{
    PriceLevelVector asks = initialAsks();

    asks.insert(LobsterMessage{0, 0, LobsterEvent::NEW, 4, 100, 13, LobsterSide::SELL});
    EXPECT_EQ(asks.size(), 4);

    EXPECT_EQ(asks[0].price(), 11);
    EXPECT_EQ(asks[0].size(), 100);
    EXPECT_EQ(asks[0].n(), 1);
    
    EXPECT_EQ(asks[1].price(), 12);
    EXPECT_EQ(asks[1].size(), 100);
    EXPECT_EQ(asks[1].n(), 1);
    
    EXPECT_EQ(asks[2].price(), 13);
    EXPECT_EQ(asks[2].size(), 100);
    EXPECT_EQ(asks[2].n(), 1);
    
    EXPECT_EQ(asks[3].price(), 14);
    EXPECT_EQ(asks[3].size(), 100);
    EXPECT_EQ(asks[3].n(), 1);
}

TEST_F(LobsterTest, AskAddBack)
{
    PriceLevelVector asks = initialAsks();

    asks.insert(LobsterMessage{0, 0, LobsterEvent::NEW, 4, 100, 15, LobsterSide::SELL});
    EXPECT_EQ(asks.size(), 4);

    EXPECT_EQ(asks[0].price(), 11);
    EXPECT_EQ(asks[0].size(), 100);
    EXPECT_EQ(asks[0].n(), 1);
    
    EXPECT_EQ(asks[1].price(), 12);
    EXPECT_EQ(asks[1].size(), 100);
    EXPECT_EQ(asks[1].n(), 1);
    
    EXPECT_EQ(asks[2].price(), 14);
    EXPECT_EQ(asks[2].size(), 100);
    EXPECT_EQ(asks[2].n(), 1);
    
    EXPECT_EQ(asks[3].price(), 15);
    EXPECT_EQ(asks[3].size(), 100);
    EXPECT_EQ(asks[3].n(), 1);
}

TEST_F(LobsterTest, AskAddToLevel)
{
    PriceLevelVector asks = initialAsks();

    asks.insert(LobsterMessage{0, 0, LobsterEvent::NEW, 4, 100, 12, LobsterSide::SELL});
    EXPECT_EQ(asks.size(), 3);

    EXPECT_EQ(asks[0].price(), 11);
    EXPECT_EQ(asks[0].size(), 100);
    EXPECT_EQ(asks[0].n(), 1);
    
    EXPECT_EQ(asks[1].price(), 12);
    EXPECT_EQ(asks[1].size(), 200);
    EXPECT_EQ(asks[1].n(), 2);
    
    EXPECT_EQ(asks[2].price(), 14);
    EXPECT_EQ(asks[2].size(), 100);
    EXPECT_EQ(asks[2].n(), 1);
}

TEST_F(LobsterTest, AskCancelPartial)
{
    PriceLevelVector asks = initialAsks();
    asks.cancelPartial(LobsterMessage{0, 0, LobsterEvent::CANCEL_PARTIAL, 1, 20, 11, LobsterSide::SELL});
    asks.cancelPartial(LobsterMessage{0, 0, LobsterEvent::CANCEL_PARTIAL, 2, 30, 12, LobsterSide::SELL});
    asks.cancelPartial(LobsterMessage{0, 0, LobsterEvent::CANCEL_PARTIAL, 3, 40, 14, LobsterSide::SELL});
    asks.cancelPartial(LobsterMessage{0, 0, LobsterEvent::CANCEL_PARTIAL, 5, 20, 10, LobsterSide::SELL}); // does not exist

    EXPECT_EQ(asks.size(), 3);

    EXPECT_EQ(asks[0].price(), 11);
    EXPECT_EQ(asks[0].size(), 80);
    EXPECT_EQ(asks[0].n(), 1);

    EXPECT_EQ(asks[1].price(), 12);
    EXPECT_EQ(asks[1].size(), 70);
    EXPECT_EQ(asks[1].n(), 1);

    EXPECT_EQ(asks[2].price(), 14);
    EXPECT_EQ(asks[2].size(), 60);
    EXPECT_EQ(asks[2].n(), 1);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
