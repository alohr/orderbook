#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

#include "SimpleMessageReader.h"
#include "SimplePriceLevel.h"

class SimpleOrderBook : public SimpleMessageHandler {
public:
    SimpleOrderBook() {
	bids_.reserve(ORDERBOOK_DEPTH + 1); // avoid realloc during inserts
	asks_.reserve(ORDERBOOK_DEPTH + 1);
    }

    virtual void onNew(const SimpleNewMessage& message) override;
    virtual void onModify(const SimpleModifyMessage& message) override;
    virtual void onDelete(const SimpleDeleteMessage& message) override;

    void print() const;

    const SimplePriceLevel& bid(size_t i) const { return bids_[i]; }
    const SimplePriceLevel& ask(size_t i) const { return asks_[i]; }

    size_t bidSize() const { return bids_.size(); }
    size_t askSize() const { return asks_.size(); }

private:
    static const size_t ORDERBOOK_DEPTH = 10;

    void newLevel(std::vector<SimplePriceLevel>& levels, size_t i, const SimplePriceLevel& priceLevel);
    void modifyLevel(std::vector<SimplePriceLevel>& levels, size_t i, int quantity);
    void deleteLevel(std::vector<SimplePriceLevel>& levels, size_t i);
    void printLevel(size_t i, const SimplePriceLevel& level) const;

    std::vector<SimplePriceLevel> bids_;
    std::vector<SimplePriceLevel> asks_;
};

// Local variables:
// mode: c++
// End:
