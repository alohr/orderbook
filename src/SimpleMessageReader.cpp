#include "SimpleMessageReader.h"

#include <fstream>
#include <iostream>
#include <iomanip>

void SimpleMessageReader::read(const std::string& filename)
{
    char action = 0;
    
    std::ifstream in(filename);
    while (in >> action) {
	switch (action) {
	case 'N':
        {
		SimpleNewMessage message;
		in.ignore(2) >> message.side;
		in.ignore(2) >> message.level;
		in.ignore(2) >> message.price;
		in.ignore(2) >> message.quantity;
		handler_.onNew(message);
	    }
	    break;
	case 'M':
	    {
		SimpleModifyMessage message;
		in.ignore(2) >> message.side;
		in.ignore(2) >> message.level;
		in.ignore(2) >> message.quantity;
		handler_.onModify(message);
	    }
	    break;
	case 'D':
	    {
		SimpleDeleteMessage message;
		in.ignore(2) >> message.side;
		in.ignore(2) >> message.level;
		handler_.onDelete(message);
	    }
	    break;
	}
    }
}

std::ostream& operator<<(std::ostream& os, const SimpleNewMessage& message)
{
    os << "NewMessage = { side=" << message.side
       << ", level=" << message.level
       << ", price=" << message.price
       << ", quantity=" << message.quantity
       << " }";

    return os;
}

std::ostream& operator<<(std::ostream& os, const SimpleModifyMessage& message)
{
    os << "ModifyMessage = { side=" << message.side
       << ", level=" << message.level
       << ", quantity=" << message.quantity
       << " }";

    return os;
}

std::ostream& operator<<(std::ostream& os, const SimpleDeleteMessage& message)
{
    os << "DeleteMessage = { side=" << message.side
       << ", level=" << message.level
       << " }";

    return os;
}
