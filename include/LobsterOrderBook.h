#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

#include "LobsterReader.h"

class LobsterOrder {
public:
    LobsterOrder() = delete;

    LobsterOrder(
        uint32_t second,
        uint32_t nanosecond,
        uint32_t orderId,
        uint32_t size,
        uint32_t price,
        int32_t side) :
            second_(second),
            nanosecond_(nanosecond),
            orderId_(orderId),
            size_(size),
            price_(price),
            side_(side) {}

    LobsterOrder(const LobsterMessage& message) :
            second_(message.second),
            nanosecond_(message.nanosecond),
            orderId_(message.orderid),
            size_(message.size),
            price_(message.price),
            side_(message.side) {}

    uint32_t second() const { return second_; }
    uint32_t nanosecond() const { return nanosecond_; }
    uint32_t orderId() const { return orderId_; }
    uint32_t price() const { return price_; }
    uint32_t size() const { return  size_; }
    int32_t side() const { return side_; }

    uint32_t cancelPartial(uint32_t size) {
        size_ -= size;
        return size_;
    }

private:
    uint32_t second_;
    uint32_t nanosecond_;
    uint32_t orderId_;
    uint32_t size_;
    uint32_t price_;
    int32_t side_;
};


class PriceLevel {
public:
    PriceLevel() = delete;

    PriceLevel(const LobsterOrder& order) :
        price_(order.price()),
        size_(order.size()) {
        orders_.push_back(order);
    }

    void insertBack(const LobsterMessage& message) {
        orders_.push_back(LobsterOrder(message));
        size_ += message.size;
    }

    void cancelPartial(const LobsterMessage& message) {
        auto p = std::find_if(orders_.begin(), orders_.end(), [&message](const LobsterOrder& order) {
            return message.orderid == order.orderId();
        });
        if (p != orders_.end()) {
            size_ -= message.size;
            p->cancelPartial(message.size);
        }
    }

    void cancelFull(const LobsterMessage& message) {
        auto p = std::find_if(orders_.begin(), orders_.end(), [&message](const LobsterOrder &order) {
            return message.orderid == order.orderId();
        });
        if (p != orders_.end()) {
            size_ -= p->size();
            orders_.erase(p);
        }
    }

    void onExecVisible(const LobsterMessage& message) {
        auto p = std::find_if(orders_.begin(), orders_.end(), [&message](const LobsterOrder &order) {
            return message.orderid == order.orderId();
        });
        if (p != orders_.end()) {
            size_ -= message.size;
            if (p->cancelPartial(message.size) == 0) {
                orders_.erase(p);
            }
        }
    }

    uint32_t price() const { return price_; }
    uint32_t size() const { return size_; }
    size_t n() const { return orders_.size(); }

    const LobsterOrder& operator[](size_t i) const { return orders_[i]; }

private:
    uint32_t price_;
    uint32_t size_;
    std::vector<LobsterOrder> orders_;
};


typedef bool (*Compare)(const PriceLevel& priceLevel, uint32_t price);

inline bool less(const PriceLevel& priceLevel, uint32_t price) {
    return priceLevel.price() < price;
}

inline bool greater(const PriceLevel& priceLevel, uint32_t price) {
    return priceLevel.price() > price;
}


class PriceLevelVector {
public:
    PriceLevelVector(Compare comp) :
        comp_(comp) {}
    void insert(const LobsterMessage& message);
    void cancelPartial(const LobsterMessage& message);
    void cancelFull(const LobsterMessage& message);
    void onExecVisible(const LobsterMessage& message);
    
    size_t size() const { return levels_.size(); }

    const PriceLevel& operator[](size_t i) const { return levels_[i]; }

private:
    Compare comp_;
    std::vector<PriceLevel> levels_;
};


class LobsterOrderBook : public LobsterMessageHandler {
public:
    LobsterOrderBook() :
        bids_(greater),
        asks_(less) {}

    void onNew(const LobsterMessage& message) override;
    void onCancelPartial(const LobsterMessage& message) override;
    void onCancelFull(const LobsterMessage& message) override;
    void onExecVisible(const LobsterMessage& message) override;
    void onExecHidden(const LobsterMessage& message) override;
    void onCross(const LobsterMessage& message) override;
    void onTradingHalt(const LobsterMessage& message) override;
    
    void print() const;

    /*
    const PriceLevel& bid(size_t i) const { return bids_[i]; }
    const PriceLevel& ask(size_t i) const { return asks_[i]; }

    size_t bidSize() const { return bids_.size(); }
    size_t askSize() const { return asks_.size(); }
     */


private:
    PriceLevelVector& priceLevelVector(int32_t side) {
        return side == LobsterSide::BUY ? bids_ : asks_;
    }

    void printLevel(size_t i, const PriceLevel& level) const;

    PriceLevelVector bids_;
    PriceLevelVector asks_;
};

// Local variables:
// mode: c++
// End:
