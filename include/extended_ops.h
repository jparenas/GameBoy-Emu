#pragma once

#include <cassert>
#include <string>

struct GameBoy;

struct ExtendedInstruction
{
  std::string name;
  uint8_t ticks;
  void (*execute)(GameBoy &) = NULL;
};

extern const struct ExtendedInstruction extended_instruction_set[];
