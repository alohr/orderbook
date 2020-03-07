#include "OrderBook.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

void OrderBook::onNew(const NewMessage& message)
{
    newLevel(message.side == 'B' ? bids_ : asks_, message.level - 1, PriceLevel(message));
}

void OrderBook::onModify(const ModifyMessage& message)
{
    modifyLevel(message.side == 'B' ? bids_ : asks_, message.level - 1, message.quantity);
}

void OrderBook::onDelete(const DeleteMessage& message)
{
    deleteLevel(message.side == 'B' ? bids_ : asks_, message.level - 1);
}

void OrderBook::newLevel(std::vector<PriceLevel>& levels, size_t i, const PriceLevel& priceLevel)
{
    levels.insert(levels.begin() + i, priceLevel);
    levels.resize(ORDERBOOK_DEPTH);
}

void OrderBook::modifyLevel(std::vector<PriceLevel>& levels, size_t i, int quantity)
{
    levels[i].modify(quantity);
}

void OrderBook::deleteLevel(std::vector<PriceLevel>& levels, size_t i)
{
    levels.erase(levels.begin() + i);
}

void OrderBook::printLevel(size_t i, const PriceLevel& level) const
{
    std::cout << std::setfill(' ')
	      << std::setw(2)
	      << i
	      << " " << std::setw(3) << level.quantity()
	      << " " << level.price()
	      << std::endl;
}

void OrderBook::print() const
{
    std::cout << "Asks" << std::endl;
    for (size_t i = asks_.size(); i != 0; i--)
	printLevel(i, asks_[i - 1]);
    std::cout << "Bids" << std::endl;
    for (size_t i = 1; i <= bids_.size(); i++)
	printLevel(i, bids_[i - 1]);
}
