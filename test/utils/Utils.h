#ifndef SELECTOR_SRC_TEST_UTILS_UTILS_H
#define SELECTOR_SRC_TEST_UTILS_UTILS_H

#include <../../src/BaseSelector.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdint>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
namespace utils
{
enum
{
    HEADER_LENGTH = sizeof(uint64_t),
    MAX_MESSAGE_LENGTH = UINT64_MAX,
    SERVER_PORT = 8080
};

void setNonBlocking(int fd);
const std::vector<char> encodeMessage(const std::string &message);

class TestClient : private boost::noncopyable
{
  public:
    TestClient(selector::BaseSelector &);
    ~TestClient();
    void sendMessage(const std::string &msg);

  private:
    void onSendMessage(int mask, const std::vector<char> &msg);
    std::string onRecvMessage();
    selector::BaseSelector &selector_;
    int cli_sock, serv_port;
    struct sockaddr_in cli_addr;
    uint64_t current_send, current_recv;
};
}

#endif // SELECTOR_SRC_TEST_UTILS_UTILS_H