#include "testEpollSelector.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <endian.h>
#include <strings.h>
#include <netinet/in.h>
#include <iostream>

EpollSelectorUnitTest::EpollSelectorUnitTest()
    : serv_sock(socket(AF_INET, SOCK_STREAM, 0))
{
}

EpollSelectorUnitTest::~EpollSelectorUnitTest()
{
}

void EpollSelectorUnitTest::SetUp()
{
    int enable = 1;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htobe16(8080);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(serv_sock, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(serv_sock, 1024);
}

void EpollSelectorUnitTest::TearDown()
{
}

void EpollSelectorUnitTest::TestBody()
{
}

TEST_F(EpollSelectorUnitTest, TEST_ADD_EVENT)
{
    epollSelector.addEvent(serv_sock, selector::EVENT_READ, [](int a) { return; });
    epollSelector.removeEvent(serv_sock);
    try
    {
        epollSelector.removeEvent(serv_sock);
    }
    catch (selector::EpollException &err)
    {
        EXPECT_EQ(ENOENT, err.getErrno());
    }
}

TEST_F(EpollSelectorUnitTest, TEST_ADD_SAME_FD_EVENT_TWICE)
{
    epollSelector.addEvent(serv_sock, selector::EVENT_READ, [](int a) { return; });
    try
    {
        epollSelector.addEvent(serv_sock, selector::EVENT_READ, [](int a) { return; });
    }
    catch (selector::EpollException &err)
    {
        EXPECT_EQ(EEXIST, err.getErrno());
    }
}

TEST_F(EpollSelectorUnitTest, TEST_REMOVE_EVENT)
{
    epollSelector.addEvent(serv_sock,selector::EVENT_READ, [](int a) { return; });
    epollSelector.removeEvent(serv_sock);
}

TEST_F(EpollSelectorUnitTest, TEST_REMOVE_SAME_FD_EVENT_TWICE)
{
    epollSelector.addEvent(serv_sock, selector::EVENT_READ, [](int a) { return; });
    epollSelector.removeEvent(serv_sock);
    try
    {
        epollSelector.removeEvent(serv_sock);
    }
    catch (selector::EpollException &err)
    {
        EXPECT_EQ(ENOENT, err.getErrno());
    }
}