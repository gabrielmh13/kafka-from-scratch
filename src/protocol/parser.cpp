#include "parser.hpp"

#include <iostream>
#include <arpa/inet.h>
#include <stdexcept>
#include <cstring>

Header Parser::ParseHeader(std::vector<uint8_t>& buffer){
    if(buffer.size() < 12){
        throw std::runtime_error("Header too small");
    }

    Header header;
    size_t offset = 0;
    uint32_t tmp32;
    uint16_t tmp16;

    std::memcpy(&tmp32, buffer.data() + offset, 4);
    header.msg_size = ntohl(tmp32);
    offset += 4;

    std::memcpy(&tmp16, buffer.data() + offset, 2);
    header.request_api_key = ntohs(tmp16);
    offset += 2;

    std::memcpy(&tmp16, buffer.data() + offset, 2);
    header.request_api_version = ntohs(tmp16);
    offset += 2;

    std::memcpy(&tmp32, buffer.data() + offset, 4);
    header.correlation_id = ntohl(tmp32);
    offset += 4;

    return header;
}