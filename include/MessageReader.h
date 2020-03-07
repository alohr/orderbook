#pragma once

#include <iostream>

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

// Local variables:
// mode: c++
// End:
