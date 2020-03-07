#pragma once

#include "OrderBook.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "MessageReader.h"
#include "PriceLevel.h"

class OrderBook : public MessageHandler {
public:
    OrderBook() {
	bids_.reserve(ORDERBOOK_DEPTH + 1); // avoid realloc during inserts
	asks_.reserve(ORDERBOOK_DEPTH + 1);
    }

    virtual void onNew(const NewMessage& message) override;
    virtual void onModify(const ModifyMessage& message) override;
    virtual void onDelete(const DeleteMessage& message) override;

    void print() const;

    const PriceLevel& bid(size_t i) const { return bids_[i]; }
    const PriceLevel& ask(size_t i) const { return asks_[i]; }

    size_t bidSize() const { return bids_.size(); }
    size_t askSize() const { return asks_.size(); }

private:
    static const size_t ORDERBOOK_DEPTH = 10;

    void newLevel(std::vector<PriceLevel>& levels, size_t i, const PriceLevel& priceLevel);
    void modifyLevel(std::vector<PriceLevel>& levels, size_t i, int quantity);
    void deleteLevel(std::vector<PriceLevel>& levels, size_t i);
    void printLevel(size_t i, const PriceLevel& level) const;

    std::vector<PriceLevel> bids_;
    std::vector<PriceLevel> asks_;
};

// Local variables:
// mode: c++
// End:
