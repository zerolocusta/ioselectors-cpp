#include "gtest/gtest.h"
#include "../Utils.h"
#include <cstring>
void testingDecodeMessage(const std::string &str)
{
    auto msg = utils::encodeMessage(str);
    auto be64 = htobe64(str.size());

    ASSERT_EQ(msg.size(), str.size() + utils::HEADER_LENGTH);
    ASSERT_EQ(std::memcmp(msg.data() + utils::HEADER_LENGTH, str.data(), str.size()), 0);
    ASSERT_EQ(std::memcmp(msg.data(), &be64, sizeof(be64)), 0);
}

TEST(utilsUnitTest, TEST_NORMAL_STRING)
{
    std::string str_123("123");
    testingDecodeMessage(str_123);
}

TEST(utilsUnitTest, TEST_EMPTY_STRING)
{
    std::string str_empty;
    testingDecodeMessage(str_empty);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}