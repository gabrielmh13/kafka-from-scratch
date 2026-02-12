#pragma once

#include <cstdint>
#include <vector>
#include <string>

struct Header {
    uint32_t msg_size;
    uint16_t request_api_key;
    uint16_t request_api_version;
    uint32_t correlation_id;
    std::string client_id;
};

class Parser {
public:
    Header ParseHeader(const std::vector<uint8_t>& buffer);
};