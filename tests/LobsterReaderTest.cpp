#include <iostream>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <LobsterReader.h>

using ::testing::AtLeast;
using ::testing::AnyNumber;
using ::testing::AllOf;
using ::testing::Field;

static const char *testdir;

class MockLobsterHandler : public LobsterMessageHandler {
public:
    MOCK_METHOD(void, onNew, (const LobsterMessage& message), (override));
    MOCK_METHOD(void, onCancelPartial, (const LobsterMessage& message), (override));
    MOCK_METHOD(void, onCancelFull, (const LobsterMessage& message), (override));
    MOCK_METHOD(void, onExecVisible, (const LobsterMessage& message), (override));
    MOCK_METHOD(void, onExecHidden, (const LobsterMessage& message), (override));
    MOCK_METHOD(void, onCross, (const LobsterMessage& message), (override));
    MOCK_METHOD(void, onTradingHalt, (const LobsterMessage& message), (override));
};

class LobsterReaderTest : public ::testing::Test {};

MATCHER(IsBuyOrSell, "") { return arg == 1 || arg == -1; }


TEST(LobsterReaderTest, AllCallbacks)
{
    MockLobsterHandler handler;

    EXPECT_CALL(handler,
        onNew(
            AllOf(
                Field(&LobsterMessage::event, LobsterEvent::NEW),
                Field(&LobsterMessage::side, IsBuyOrSell())
            )
        )
    ).Times(AtLeast(1));

    EXPECT_CALL(handler,
        onCancelPartial(
            AllOf(
                Field(&LobsterMessage::event, LobsterEvent::CANCEL_PARTIAL),
                Field(&LobsterMessage::side, IsBuyOrSell())
            )
        )
    ).Times(AtLeast(1));

    EXPECT_CALL(handler,
        onCancelFull(
            AllOf(
                Field(&LobsterMessage::event, LobsterEvent::CANCEL_FULL),
                Field(&LobsterMessage::side, IsBuyOrSell())
            )
        )
    ).Times(AtLeast(1));

    EXPECT_CALL(handler,
        onExecVisible(
            AllOf(
                Field(&LobsterMessage::event, LobsterEvent::EXEC_VISIBLE),
                Field(&LobsterMessage::side, IsBuyOrSell())
            )
        )
    ).Times(AtLeast(1));
    
    EXPECT_CALL(handler,
        onExecHidden(
            AllOf(
                Field(&LobsterMessage::event, LobsterEvent::EXEC_HIDDEN),
                Field(&LobsterMessage::side, IsBuyOrSell())
            )
        )
    ).Times(AtLeast(1));
                    
    EXPECT_CALL(handler, onCross).Times(AnyNumber());
    EXPECT_CALL(handler, onTradingHalt).Times(AnyNumber());

    for (const auto& p : boost::filesystem::directory_iterator(testdir)) {
        const std::string& f = p.path().string();
        if (boost::regex_search(f, boost::regex("SPY.*_message_\\d+\\.csv$"))) {
            LobsterReader reader(handler);
            reader.read(f.c_str());
        }
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    
    assert(argc == 2);
    testdir = argv[1];
    
    return RUN_ALL_TESTS();
}
