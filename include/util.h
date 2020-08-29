#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

uint16_t convert_string_to_hex(std::string s);

bool test_bit(uint8_t byte, uint8_t bit);

std::string bool_to_string(bool value);

template <typename K, typename V>
V &init_if_absent(std::unordered_map<K, V> &map, K key)
{
  typename std::unordered_map<K, V>::const_iterator result = map.find(key);
  if (result == map.end())
  {
    map[key] = V();
  }
  return map[key];
}
