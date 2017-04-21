#include "Utils.h"
#include <endian.h>
#include <stdexcept>
#include <cstring>
#include <vector>
#include <iostream>
#include <utility>
namespace utils
{

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
}