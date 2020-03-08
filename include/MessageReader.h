#pragma once

#include <string>

class MessageReader {

public:
    virtual void read(const std::string& filename) = 0;
};


// Local variables:
// mode: c++
// End:
