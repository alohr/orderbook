#include "OrderBook.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

static bool debug = false;

std::ostream& operator<<(std::ostream& os, const NewMessage& message)
{
    os << "NewMessage = { side=" << message.side
       << ", level=" << message.level
       << ", price=" << message.price
       << ", quantity=" << message.quantity
       << " }";

    return os;
}

std::ostream& operator<<(std::ostream& os, const ModifyMessage& message)
{
    os << "ModifyMessage = { side=" << message.side
       << ", level=" << message.level
       << ", quantity=" << message.quantity
       << " }";

    return os;
}

std::ostream& operator<<(std::ostream& os, const DeleteMessage& message)
{
    os << "DeleteMessage = { side=" << message.side
       << ", level=" << message.level
       << " }";

    return os;
}

void OrderBook::onNew(const NewMessage& message)
{
    if (debug)
	std::cout << message << std::endl;
    newLevel(message.side == 'B' ? bids_ : asks_, message.level - 1, PriceLevel(message));
}

void OrderBook::onModify(const ModifyMessage& message)
{
    if (debug)
	std::cout << message << std::endl;
    modifyLevel(message.side == 'B' ? bids_ : asks_, message.level - 1, message.quantity);
}

void OrderBook::onDelete(const DeleteMessage& message)
{
    if (debug)
	std::cout << message << std::endl;
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

void MessageReader::read(const std::string& filename)
{
    char action = 0;

    std::ifstream in(filename);
    while (in >> action) {
	switch (action) {
	case 'N':
	    {
		NewMessage message;
		in.ignore(2) >> message.side;
		in.ignore(2) >> message.level;
		in.ignore(2) >> message.price;
		in.ignore(2) >> message.quantity;
		handler_.onNew(message);
	    }
	    break;
	case 'M':
	    {
		ModifyMessage message;
		in.ignore(2) >> message.side;
		in.ignore(2) >> message.level;
		in.ignore(2) >> message.quantity;
		handler_.onModify(message);
	    }
	    break;
	case 'D':
	    {
		DeleteMessage message;
		in.ignore(2) >> message.side;
		in.ignore(2) >> message.level;
		handler_.onDelete(message);
	    }
	    break;
	}
    }
}

#ifdef MAIN
int main(int argc, char *argv[])
{
    OrderBook orderBook;
    MessageReader reader(orderBook);

    reader.read("data/sample.csv");
    orderBook.print();
}
#endif
