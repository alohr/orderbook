#pragma once

#include "MessageReader.h"

#include <iostream>

struct SimpleNewMessage {
    char side;
    int level;
    double price;
    int quantity;
};

struct SimpleModifyMessage {
    char side;
    int level;
    int quantity;
};

struct SimpleDeleteMessage {
    char side;
    int level;
};

std::ostream& operator<<(std::ostream& os, const SimpleNewMessage& message);
std::ostream& operator<<(std::ostream& os, const SimpleModifyMessage& message);
std::ostream& operator<<(std::ostream& os, const SimpleDeleteMessage& message);

class SimpleMessageHandler {
public:
    virtual void onNew(const SimpleNewMessage& message) = 0;
    virtual void onModify(const SimpleModifyMessage& message) = 0;
    virtual void onDelete(const SimpleDeleteMessage& message) = 0;
};

class SimpleMessageReader : public MessageReader {
public:
    SimpleMessageReader(SimpleMessageHandler& handler) :
	handler_(handler) {}

    void read(const std::string& filename) override;

private:
    SimpleMessageHandler& handler_;

};

// Local variables:
// mode: c++
// End:
