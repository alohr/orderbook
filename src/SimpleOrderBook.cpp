#include "SimpleOrderBook.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

void SimpleOrderBook::onNew(const SimpleNewMessage& message)
{
    newLevel(message.side == 'B' ? bids_ : asks_, message.level - 1, SimplePriceLevel(message));
}

void SimpleOrderBook::onModify(const SimpleModifyMessage& message)
{
    modifyLevel(message.side == 'B' ? bids_ : asks_, message.level - 1, message.quantity);
}

void SimpleOrderBook::onDelete(const SimpleDeleteMessage& message)
{
    deleteLevel(message.side == 'B' ? bids_ : asks_, message.level - 1);
}

void SimpleOrderBook::newLevel(std::vector<SimplePriceLevel>& levels, size_t i, const SimplePriceLevel& priceLevel)
{
    levels.insert(levels.begin() + i, priceLevel);
    levels.resize(ORDERBOOK_DEPTH);
}

void SimpleOrderBook::modifyLevel(std::vector<SimplePriceLevel>& levels, size_t i, int quantity)
{
    levels[i].modify(quantity);
}

void SimpleOrderBook::deleteLevel(std::vector<SimplePriceLevel>& levels, size_t i)
{
    levels.erase(levels.begin() + i);
}

void SimpleOrderBook::printLevel(size_t i, const SimplePriceLevel& level) const
{
    std::cout << std::setfill(' ')
	      << std::setw(2)
	      << i
	      << " " << std::setw(3) << level.quantity()
	      << " " << level.price()
	      << std::endl;
}

void SimpleOrderBook::print() const
{
    std::cout << "Asks" << std::endl;
    for (size_t i = asks_.size(); i != 0; i--)
	printLevel(i, asks_[i - 1]);
    std::cout << "Bids" << std::endl;
    for (size_t i = 1; i <= bids_.size(); i++)
	printLevel(i, bids_[i - 1]);
}
