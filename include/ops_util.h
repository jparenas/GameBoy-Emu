#pragma once

#include <cstring>

#include "gpu.h"
#include "gameboy.h"

uint16_t convert_uint8_to_uint16(uint8_t a, uint8_t b)
{
  return ((uint16_t)a) << 8 | b;
}

void write_short_to_stack(GameBoy &gameboy, uint16_t value)
{
  gameboy.cpu.registrers.sp -= 2;
  gameboy.memory.write_short(gameboy.cpu.registrers.sp, value);
}

uint16_t pop_short_from_stack(GameBoy &gameboy)
{
  uint16_t value = gameboy.memory.read_short(gameboy.cpu.registrers.sp);
  gameboy.cpu.registrers.sp += 2;
  return value;
}
