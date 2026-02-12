#pragma once

#include <cstdint>
#include <vector>

struct Header {
    uint32_t msg_size;
    uint16_t request_api_key;
    uint16_t request_api_version;
    uint32_t correlation_id;
};

class Parser {
public:
    Header ParseHeader(std::vector<uint8_t>& buffer);
};