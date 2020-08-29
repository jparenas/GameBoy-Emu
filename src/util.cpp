#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <unordered_map>

#include "util.h"

uint16_t convert_string_to_hex(std::string s)
{
  assert(s.size() <= 4);
  if (s.size() < 4)
  {
    s.insert(0, 4 - s.size(), '0');
  }
  assert(s.size() == 4);

  std::string byteString = s.substr(0, 2);
  uint16_t byte = (uint8_t)strtol(byteString.c_str(), NULL, 16) << 8;
  byteString = s.substr(2, 2);
  byte |= (uint8_t)strtol(byteString.c_str(), NULL, 16);

  return byte;
}

bool test_bit(uint8_t byte, uint8_t bit)
{
  return ((byte >> bit) & 0x01) == 0x01;
}

std::string bool_to_string(bool value)
{
  return value ? "true" : "false";
}
