#pragma once

#include <memory>
#include <string>

struct GameBoy;

struct Operands
{
  uint8_t values[2];
};

struct Instruction
{
  std::string name;
  uint8_t size;
  uint8_t ticks;
  void (*execute)(GameBoy &, Operands &) = NULL;
};

extern const Instruction instruction_set[];
