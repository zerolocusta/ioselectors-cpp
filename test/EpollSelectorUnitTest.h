#ifndef SELECTOR_SRC_TEST_EPOLLSELECTORUNITTEST_H
#define SELECTOR_SRC_TEST_EPOLLSELECTORUNITTEST_H

#include "gtest/gtest.h"
#include "../src/EpollSelector.h"

using namespace selector;

class EpollSelectorUnitTest : public testing::Test
{
  public:
    EpollSelectorUnitTest();
    ~EpollSelectorUnitTest();

    void SetUp();
    void TearDown();
    void TestBody();
    EpollSelector epollSelector;
    int serv_sock, cli_sock;
};

#endif // SELECTOR_SRC_TEST_EPOLLSELECTORUNITTEST_H