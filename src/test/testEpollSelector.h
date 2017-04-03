#ifndef SELECTOR_SRC_TEST_TESTEPOLLSELECTOR_H
#define SELECTOR_SRC_TEST_TESTEPOLLSELECTOR_H

#include "gtest/gtest.h"
#include "../EpollSelector.h"

using namespace selector;

class EpollSelectorUnitTest : public testing::Test
{
public:
    EpollSelectorUnitTest();
    ~EpollSelectorUnitTest();

    void SetUp();
    void TearDown();

private:
    EpollSelector epollSelector;
};


#endif // SELECTOR_SRC_TEST_TESTEPOLLSELECTOR_H