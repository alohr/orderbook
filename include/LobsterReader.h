#pragma once

#include "MessageReader.h"

#include <iostream>

enum LobsterEvent {
    NULL_EVENT     = 0,
    NEW            = 1,
    CANCEL_PARTIAL = 2,
    CANCEL_FULL    = 3,
    EXEC_VISIBLE   = 4,
    EXEC_HIDDEN    = 5,
    CROSS          = 6,
    TRADING_HALT   = 7,
};

struct LobsterMessage {
    uint32_t second;
    uint32_t nanosecond;
    uint32_t event;
    uint32_t orderid;
    uint32_t size;
    uint32_t price;
    int32_t side;
};


class LobsterMessageHandler {
public:
    virtual void onNew(const LobsterMessage& message) = 0;
    virtual void onCancelPartial(const LobsterMessage& message) = 0;
    virtual void onCancelFull(const LobsterMessage& message) = 0;
    virtual void onExecVisible(const LobsterMessage& message) = 0;
    virtual void onExecHidden(const LobsterMessage& message) = 0;
    virtual void onCross(const LobsterMessage& message) = 0;
    virtual void onTradingHalt(const LobsterMessage& message) = 0;
};

class LobsterReader : public MessageReader {
public:
    LobsterReader(LobsterMessageHandler& handler) :
	handler_(handler) {}

    void read(const std::string& filename) override;

private:
    LobsterMessageHandler& handler_;

};

// Local variables:
// mode: c++
// End:
