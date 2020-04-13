#include "LobsterOrderBook.h"



void LobsterOrderBook::onNew(const LobsterMessage& message)
{
    std::cout << message << '\n';
}

void LobsterOrderBook::onCancelPartial(const LobsterMessage& message)
{
}

void LobsterOrderBook::onCancelFull(const LobsterMessage& message)
{
}

void LobsterOrderBook::onExecVisible(const LobsterMessage& message)
{
}

void LobsterOrderBook::onExecHidden(const LobsterMessage& message)
{
}

void LobsterOrderBook::onCross(const LobsterMessage& message)
{
}

void LobsterOrderBook::onTradingHalt(const LobsterMessage& message)
{
}

void LobsterOrderBook::printLevel(size_t i, const LobsterPriceLevel& level) const
{
#if 0
    std::cout << std::setfill(' ')
	      << std::setw(2)
	      << i
	      << " " << std::setw(3) << level.quantity()
	      << " " << level.price()
	      << std::endl;
#endif
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
    std::cout << "Asks" << std::endl;
    for (size_t i = asks_.size(); i != 0; i--)
	printLevel(i, asks_[i - 1]);
    std::cout << "Bids" << std::endl;
    for (size_t i = 1; i <= bids_.size(); i++)
	printLevel(i, bids_[i - 1]);
}
