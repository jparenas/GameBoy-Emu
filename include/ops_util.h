#pragma once

#include <cstring>

#include "gameboy.h"
#include "gpu.h"

int8_t unsigned_8_to_signed(uint8_t x)
{
  return x < 128 ? x : x - 256;
}

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
