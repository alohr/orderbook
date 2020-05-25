#include "LobsterOrderBook.h"

#include <iostream>
#include <iomanip>

void PriceLevelVector::insert(const LobsterMessage& message)
{
    auto p = std::lower_bound(levels_.begin(), levels_.end(), message.price, comp_);

    if (p == levels_.end()) {
        levels_.emplace_back(message);
    } else {
        if (message.price == p->price()) {
            p->insertBack(message);
        } else {
            levels_.emplace(p, LobsterOrder(message));
        }
    }
}

void PriceLevelVector::cancelPartial(const LobsterMessage& message)
{
    auto p = std::lower_bound(levels_.begin(), levels_.end(), message.price, comp_);

    if (p != levels_.end() && p->price() == message.price) {
        p->cancelPartial(message);
    }
}

void PriceLevelVector::cancelFull(const LobsterMessage& message)
{
    auto p = std::lower_bound(levels_.begin(), levels_.end(), message.price, comp_);

    if (p != levels_.end() && p->price() == message.price) {
        p->cancelFull(message);
        if (p->size() == 0) {
            levels_.erase(p);
        }
    }
}

void PriceLevelVector::onExecVisible(const LobsterMessage& message) {
    auto p = std::lower_bound(levels_.begin(), levels_.end(), message.price, comp_);

    if (p != levels_.end() && p->price() == message.price) {
        p->onExecVisible(message);
        if (p->size() == 0) {
            levels_.erase(p);
        }
    }
}

void LobsterOrderBook::onNew(const LobsterMessage& message)
{
    PriceLevelVector& priceLevels = priceLevelVector(message.side);
    priceLevels.insert(message);
}

void LobsterOrderBook::onCancelPartial(const LobsterMessage& message)
{
    PriceLevelVector& priceLevels = priceLevelVector(message.side);
    priceLevels.cancelPartial(message);
}

void LobsterOrderBook::onCancelFull(const LobsterMessage& message)
{
    PriceLevelVector& priceLevels = priceLevelVector(message.side);
    priceLevels.cancelFull(message);
}

void LobsterOrderBook::onExecVisible(const LobsterMessage& message)
{
    PriceLevelVector& priceLevels = priceLevelVector(message.side);
    priceLevels.onExecVisible(message);
}

void LobsterOrderBook::onExecHidden(const LobsterMessage&)
{
    // ignore
}

void LobsterOrderBook::onCross(const LobsterMessage&)
{
    // ignore
}

void LobsterOrderBook::onTradingHalt(const LobsterMessage&)
{
    // ignore
}

void LobsterOrderBook::printLevel(size_t i, const PriceLevel& level) const
{
    std::cout << std::setfill(' ')
	      << std::setw(3)
	      << i
	      << " " << std::setw(3) << level.size()
	      << " " << level.price()
	      << std::endl;
}

std::ostream& operator<<(std::ostream& os, const LobsterMessage& message)
{
    os << "LobsterMessage = { time=" << message.second << "." << message.nanosecond
       << ", event=" << message.event
       << ", orderid=" << message.orderid
       << ", size=" << message.size
       << ", price=" << message.price
       << ", side=" << message.side
       << " }";

    return os;
}

void LobsterOrderBook::print() const
{
    std::cout << "Bid levels, size=" << bids_.size() << "\n";
    for (size_t i = 0; i < bids_.size(); ++i) {
        printLevel(i, bids_[i]);
    }

    std::cout << "Ask levels, size=" << asks_.size() << "\n";
    for (size_t i = 0; i < asks_.size(); ++i) {
        printLevel(i, asks_[i]);
    }
}
