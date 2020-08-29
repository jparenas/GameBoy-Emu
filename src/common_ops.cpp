#include "common_ops.h"
#include "gameboy.h"

void rlc(GameBoy &gameboy, uint8_t &value)
{
  gameboy.cpu.registrers.f.c = value & 0b10000000 >> 7;
  value = value << 1;
  value |= gameboy.cpu.registrers.f.c;
  if (value == 0)
  {
    gameboy.cpu.registrers.f.z = 1;
  }
  else
  {
    gameboy.cpu.registrers.f.z = 0;
  }
  gameboy.cpu.registrers.f.n = 0;
  gameboy.cpu.registrers.f.h = 0;
}

void rl(GameBoy &gameboy, uint8_t &value)
{
  uint8_t old_carry_bit = gameboy.cpu.registrers.f.c;
  gameboy.cpu.registrers.f.c = value & 0b10000000 >> 7;
  value = value << 1;
  value = value | old_carry_bit;

  if (value == 0)
  {
    gameboy.cpu.registrers.f.z = 1;
  }
  else
  {
    gameboy.cpu.registrers.f.z = 0;
  }
  gameboy.cpu.registrers.f.n = 0;
  gameboy.cpu.registrers.f.h = 0;
}

void rrc(GameBoy &gameboy, uint8_t &value)
{
  gameboy.cpu.registrers.f.c = value & 0x01;
  value = value >> 1;
  value |= gameboy.cpu.registrers.f.c << 7;
  if (value == 0)
  {
    gameboy.cpu.registrers.f.z = 1;
  }
  else
  {
    gameboy.cpu.registrers.f.z = 0;
  }
  gameboy.cpu.registrers.f.n = 0;
  gameboy.cpu.registrers.f.h = 0;
}

void rr(GameBoy &gameboy, uint8_t &value)
{
  uint8_t old_carry_bit = gameboy.cpu.registrers.f.c << 7;
  gameboy.cpu.registrers.f.c = value & 0x01;
  value = value >> 1;
  value = value | old_carry_bit;

  if (value == 0)
  {
    gameboy.cpu.registrers.f.z = 1;
  }
  else
  {
    gameboy.cpu.registrers.f.z = 0;
  }
  gameboy.cpu.registrers.f.n = 0;
  gameboy.cpu.registrers.f.h = 0;
}
