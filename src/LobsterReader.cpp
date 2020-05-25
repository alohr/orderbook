#include "LobsterReader.h"

#include <fstream>
#include <iostream>
#include <iomanip>

void LobsterReader::read(const std::string& filename)
{
    LobsterMessage message;

    std::ifstream in(filename);
    if (in.fail()) {
        std::cerr << "fail " << filename << std::endl;
    }

    while (in >> message.second) {
        in.ignore(1) >> message.nanosecond;
        in.ignore(1) >> message.event;
        in.ignore(1) >> message.orderid;
        in.ignore(1) >> message.size;
        in.ignore(1) >> message.price;
        in.ignore(1) >> message.side;

        std::cout << message << "\n";

        switch (message.event) {
        case LobsterEvent::NEW:
            handler_.onNew(message);
            break;
        case LobsterEvent::CANCEL_PARTIAL:
            handler_.onCancelPartial(message);
            break;
        case LobsterEvent::CANCEL_FULL:
            handler_.onCancelFull(message);
            break;
        case LobsterEvent::EXEC_VISIBLE:
            handler_.onExecVisible(message);
    	    break;
        case LobsterEvent::EXEC_HIDDEN:
            handler_.onExecHidden(message);
            break;
        case LobsterEvent::CROSS:
            handler_.onCross(message);
            break;
        case LobsterEvent::TRADING_HALT:
            handler_.onTradingHalt(message);
            break;
        }
    }
}

