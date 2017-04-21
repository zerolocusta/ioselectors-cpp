#ifndef SELECTOR_SRC_TEST_UTILS_UTILS_H
#define SELECTOR_SRC_TEST_UTILS_UTILS_H

#include <cstdint>
#include <string>
#include <vector>
namespace utils
{
enum
{
    HEADER_LENGTH = sizeof(uint64_t),
    MAX_MESSAGE_LENGTH = UINT64_MAX
};
const std::vector<char> encodeMessage(const std::string &message);
}

#endif // SELECTOR_SRC_TEST_UTILS_UTILS_H