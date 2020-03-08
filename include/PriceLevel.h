#pragma once

#include "SimpleMessageReader.h"

class PriceLevel {
public:
    PriceLevel() :
	price_(0.0),
	quantity_(0) {}
	    
    PriceLevel(const SimpleNewMessage& message) :
	price_(message.price),
	quantity_(message.quantity) {}

    double price() const { return price_; }
    int quantity() const { return quantity_; }

    void modify(int quantity) { quantity_ = quantity; }

private:
    double price_;
    int quantity_;
};

// Local variables:
// mode: c++
// End:
