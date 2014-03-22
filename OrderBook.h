#pragma once

#include <iostream>
#include <vector>

struct NewMessage {
    char side;
    int level;
    double price;
    int quantity;
};

struct ModifyMessage {
    char side;
    int level;
    int quantity;
};

struct DeleteMessage {
    char side;
    int level;
};

std::ostream& operator<<(std::ostream& os, const NewMessage& message);
std::ostream& operator<<(std::ostream& os, const ModifyMessage& message);
std::ostream& operator<<(std::ostream& os, const DeleteMessage& message);


class MessageHandler {
public:
    virtual void onNew(const NewMessage& message) = 0;
    virtual void onModify(const ModifyMessage& message) = 0;
    virtual void onDelete(const DeleteMessage& message) = 0;
};

class MessageReader {
public:
    MessageReader(MessageHandler& handler) :
	handler_(handler) {}

    void read(const std::string& filename);

private:
    MessageHandler& handler_;

};


class PriceLevel {
public:
    PriceLevel() :
	price_(0.0),
	quantity_(0) {}
	    
    PriceLevel(const NewMessage& message) :
	price_(message.price),
	quantity_(message.quantity) {}

    double price() const { return price_; }
    int quantity() const { return quantity_; }

    void modify(int quantity) { quantity_ = quantity; }

private:
    double price_;
    int quantity_;
};


class OrderBook : public MessageHandler {
public:
    OrderBook() {
	bids_.reserve(ORDERBOOK_DEPTH + 1); // avoid realloc during inserts
	asks_.reserve(ORDERBOOK_DEPTH + 1);
    }

    virtual void onNew(const NewMessage& message) override;
    virtual void onModify(const ModifyMessage& message) override;
    virtual void onDelete(const DeleteMessage& message) override;

    void print() const {
	printLevels("Asks", asks_);
	printLevels("Bids", bids_);
    }

    const PriceLevel& bid(size_t i) const { return bids_[i]; }
    const PriceLevel& ask(size_t i) const { return asks_[i]; }

    const std::vector<PriceLevel> bids() const { return bids_; }
    const std::vector<PriceLevel> asks() const { return asks_; }

private:
    static const size_t ORDERBOOK_DEPTH = 10;

    void newLevel(std::vector<PriceLevel>& levels, size_t i, const PriceLevel& priceLevel);
    void modifyLevel(std::vector<PriceLevel>& levels, size_t i, int quantity);
    void deleteLevel(std::vector<PriceLevel>& levels, size_t i);

    void printLevels(const std::string& title, const std::vector<PriceLevel>& levels) const;

    std::vector<PriceLevel> bids_;
    std::vector<PriceLevel> asks_;
};

// Local variables:
// mode: c++
// End:
