#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

#include "LobsterReader.h"
#include "PriceLevel.h"

class LobsterPriceLevel {

};

class LobsterOrderBook : public LobsterMessageHandler {
public:
    void onNew(const LobsterMessage& message) override;
    void onCancelPartial(const LobsterMessage& message) override;
    void onCancelFull(const LobsterMessage& message) override;
    void onExecVisible(const LobsterMessage& message) override;
    void onExecHidden(const LobsterMessage& message) override;
    void onCross(const LobsterMessage& message) override;
    void onTradingHalt(const LobsterMessage& message) override;
    
    void print() const;

    const LobsterPriceLevel& bid(size_t i) const { return bids_[i]; }
    const LobsterPriceLevel& ask(size_t i) const { return asks_[i]; }

    size_t bidSize() const { return bids_.size(); }
    size_t askSize() const { return asks_.size(); }

private:
    // void newLevel(std::vector<PriceLevel>& levels, size_t i, const PriceLevel& priceLevel);
    // void modifyLevel(std::vector<PriceLevel>& levels, size_t i, int quantity);
    // void deleteLevel(std::vector<PriceLevel>& levels, size_t i);

    void printLevel(size_t i, const LobsterPriceLevel& level) const;

    std::vector<LobsterPriceLevel> bids_;
    std::vector<LobsterPriceLevel> asks_;
};

// Local variables:
// mode: c++
// End:
