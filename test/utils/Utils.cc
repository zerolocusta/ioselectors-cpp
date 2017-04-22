#include "Utils.h"
#include <endian.h>
#include <stdexcept>
#include <exception>
#include <cstring>
#include <vector>
#include <iostream>
#include <utility>
#include <unistd.h>
#include <fcntl.h>
#include <functional>
namespace utils
{

void setNonBlocking(int fd)
{
    int mask = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, mask | O_NONBLOCK);
}

const std::vector<char> encodeMessage(const std::string &message)
{
    if (message.size() > utils::MAX_MESSAGE_LENGTH)
    {
        throw std::length_error("Message too big");
    }
    uint64_t total_length = utils::HEADER_LENGTH + message.size();
    char *data = new char[total_length];
    uint64_t be64 = htobe64(message.size());
    ::memcpy(data, &be64, utils::HEADER_LENGTH);
    ::memcpy(data + utils::HEADER_LENGTH, message.data(), message.size());
    std::vector<char> msg(data, data + total_length);
    delete[] data;
    return std::move(msg);
}

TestClient::TestClient(selector::BaseSelector &selector)
    : selector_(selector),
      cli_sock(socket(AF_INET, SOCK_STREAM, 0)),
      current_send(0),
      current_recv(0)
{
    setNonBlocking(cli_sock);

    bzero(&cli_addr, sizeof(cli_addr));
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htobe16(SERVER_PORT);
    cli_addr.sin_addr.s_addr = htonl(INADDR_ANY);
}
TestClient::~TestClient()
{
    close(cli_sock);
}
void TestClient::sendMessage(const std::string &msg)
{
    auto encoded_message = encodeMessage(msg);
    selector_.addEvent(cli_sock, selector::EVENT_WRITE, [this, encoded_message](int mask) { this->onSendMessage(mask, encoded_message); });
}

void TestClient::onSendMessage(int mask, const std::vector<char> &msg)
{
    auto nwrite = write(cli_sock, msg.data(), msg.size());
    // if write(2) return EWOULDBLOCK, then ignore it
    if (nwrite < 0)
    {
        if (errno == EWOULDBLOCK)
            return;
        std::terminate();
    }

    current_send += nwrite;
    if (current_send == msg.size())
    {
        selector_.removeEvent(cli_sock);
        current_send = 0;
    }

}
std::string TestClient::onRecvMessage()
{
    return std::string();
}
}