#pragma once

#include <string>

#include "gameboy.h"
#include "memory.h"

struct ExtendedInstruction
{
  std::string name;
  uint8_t ticks;
  void (*execute)(GameBoy &) = NULL;
};

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

void sla(GameBoy &gameboy, uint8_t &value)
{
  gameboy.cpu.registrers.f.c = value >> 7 & 0x01;
  value = value << 1;
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

void rr_a(GameBoy &gameboy)
{
  rr(gameboy, gameboy.cpu.registrers.a);
}

void rr_b(GameBoy &gameboy)
{
  rr(gameboy, gameboy.cpu.registrers.b);
}

void rr_c(GameBoy &gameboy)
{
  rr(gameboy, gameboy.cpu.registrers.c);
}

void rr_d(GameBoy &gameboy)
{
  rr(gameboy, gameboy.cpu.registrers.d);
}

void rr_e(GameBoy &gameboy)
{
  rr(gameboy, gameboy.cpu.registrers.e);
}

void rr_h(GameBoy &gameboy)
{
  rr(gameboy, gameboy.cpu.registrers.h);
}

void rr_l(GameBoy &gameboy)
{
  rr(gameboy, gameboy.cpu.registrers.l);
}

void rr_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  rr(gameboy, value);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void sla_a(GameBoy &gameboy)
{
  sla(gameboy, gameboy.cpu.registrers.a);
}

void sla_b(GameBoy &gameboy)
{
  sla(gameboy, gameboy.cpu.registrers.b);
}

void sla_c(GameBoy &gameboy)
{
  sla(gameboy, gameboy.cpu.registrers.c);
}

void sla_d(GameBoy &gameboy)
{
  sla(gameboy, gameboy.cpu.registrers.d);
}

void sla_e(GameBoy &gameboy)
{
  sla(gameboy, gameboy.cpu.registrers.e);
}

void sla_h(GameBoy &gameboy)
{
  sla(gameboy, gameboy.cpu.registrers.h);
}

void sla_l(GameBoy &gameboy)
{
  sla(gameboy, gameboy.cpu.registrers.l);
}

void sla_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  sla(gameboy, value);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void sra(GameBoy &gameboy, uint8_t &value)
{
  uint8_t old_7_bit_data = value & 0b10000000;
  gameboy.cpu.registrers.f.c = value & 0x01;
  value = value >> 1;
  value |= old_7_bit_data;
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

void sra_a(GameBoy &gameboy)
{
  sra(gameboy, gameboy.cpu.registrers.a);
}

void sra_b(GameBoy &gameboy)
{
  sra(gameboy, gameboy.cpu.registrers.b);
}

void sra_c(GameBoy &gameboy)
{
  sra(gameboy, gameboy.cpu.registrers.c);
}

void sra_d(GameBoy &gameboy)
{
  sra(gameboy, gameboy.cpu.registrers.d);
}

void sra_e(GameBoy &gameboy)
{
  sra(gameboy, gameboy.cpu.registrers.e);
}

void sra_h(GameBoy &gameboy)
{
  sra(gameboy, gameboy.cpu.registrers.h);
}

void sra_l(GameBoy &gameboy)
{
  sra(gameboy, gameboy.cpu.registrers.l);
}

void sra_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  sra(gameboy, value);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void srl(GameBoy &gameboy, uint8_t &value)
{
  gameboy.cpu.registrers.f.c = value & 0x01;
  value = value >> 1;
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

void srl_a(GameBoy &gameboy)
{
  srl(gameboy, gameboy.cpu.registrers.a);
}

void srl_b(GameBoy &gameboy)
{
  srl(gameboy, gameboy.cpu.registrers.b);
}

void srl_c(GameBoy &gameboy)
{
  srl(gameboy, gameboy.cpu.registrers.c);
}

void srl_d(GameBoy &gameboy)
{
  srl(gameboy, gameboy.cpu.registrers.d);
}

void srl_e(GameBoy &gameboy)
{
  srl(gameboy, gameboy.cpu.registrers.e);
}

void srl_h(GameBoy &gameboy)
{
  srl(gameboy, gameboy.cpu.registrers.h);
}

void srl_l(GameBoy &gameboy)
{
  srl(gameboy, gameboy.cpu.registrers.l);
}

void srl_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  srl(gameboy, value);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void swap(GameBoy &gameboy, uint8_t &value)
{
  value = ((value & 0x0F) << 4) | ((value & 0xF0) >> 4);
  if (value == 0)
  {
    gameboy.cpu.registrers.f.z = 1;
  }
  else
  {
    gameboy.cpu.registrers.f.z = 0;
  }
  gameboy.cpu.registrers.f.c = 0;
  gameboy.cpu.registrers.f.n = 0;
  gameboy.cpu.registrers.f.h = 0;
}

void swap_a(GameBoy &gameboy)
{
  swap(gameboy, gameboy.cpu.registrers.a);
}

void swap_b(GameBoy &gameboy)
{
  swap(gameboy, gameboy.cpu.registrers.b);
}

void swap_c(GameBoy &gameboy)
{
  swap(gameboy, gameboy.cpu.registrers.c);
}

void swap_d(GameBoy &gameboy)
{
  swap(gameboy, gameboy.cpu.registrers.d);
}

void swap_e(GameBoy &gameboy)
{
  swap(gameboy, gameboy.cpu.registrers.e);
}

void swap_h(GameBoy &gameboy)
{
  swap(gameboy, gameboy.cpu.registrers.h);
}

void swap_l(GameBoy &gameboy)
{
  swap(gameboy, gameboy.cpu.registrers.l);
}

void swap_hl(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  swap(gameboy, value);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void bit(GameBoy &gameboy, uint8_t value, uint8_t bit)
{
  gameboy.cpu.registrers.f.z = (value >> bit & 0x01) == 0;
  gameboy.cpu.registrers.f.n = 0;
  gameboy.cpu.registrers.f.h = 1;
}

void bit_0_a(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.a, 0);
}

void bit_0_b(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.b, 0);
}

void bit_0_c(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.c, 0);
}

void bit_0_d(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.d, 0);
}

void bit_0_e(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.e, 0);
}

void bit_0_h(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.h, 0);
}

void bit_0_l(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.l, 0);
}

void bit_0_hlp(GameBoy &gameboy)
{
  bit(gameboy, gameboy.memory.read_byte(gameboy.cpu.registrers.hl), 0);
}

void bit_1_a(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.a, 1);
}

void bit_1_b(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.b, 1);
}

void bit_1_c(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.c, 1);
}

void bit_1_d(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.d, 1);
}

void bit_1_e(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.e, 1);
}

void bit_1_h(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.h, 1);
}

void bit_1_l(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.l, 1);
}

void bit_1_hlp(GameBoy &gameboy)
{
  bit(gameboy, gameboy.memory.read_byte(gameboy.cpu.registrers.hl), 1);
}

void bit_2_a(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.a, 2);
}

void bit_2_b(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.b, 2);
}

void bit_2_c(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.c, 2);
}

void bit_2_d(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.d, 2);
}

void bit_2_e(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.e, 2);
}

void bit_2_h(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.h, 2);
}

void bit_2_l(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.l, 2);
}

void bit_2_hlp(GameBoy &gameboy)
{
  bit(gameboy, gameboy.memory.read_byte(gameboy.cpu.registrers.hl), 2);
}

void bit_3_a(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.a, 3);
}

void bit_3_b(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.b, 3);
}

void bit_3_c(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.c, 3);
}

void bit_3_d(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.d, 3);
}

void bit_3_e(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.e, 3);
}

void bit_3_h(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.h, 3);
}

void bit_3_l(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.l, 3);
}

void bit_3_hlp(GameBoy &gameboy)
{
  bit(gameboy, gameboy.memory.read_byte(gameboy.cpu.registrers.hl), 3);
}

void bit_4_a(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.a, 4);
}

void bit_4_b(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.b, 4);
}

void bit_4_c(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.c, 4);
}

void bit_4_d(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.d, 4);
}

void bit_4_e(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.e, 4);
}

void bit_4_h(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.h, 4);
}

void bit_4_l(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.l, 4);
}

void bit_4_hlp(GameBoy &gameboy)
{
  bit(gameboy, gameboy.memory.read_byte(gameboy.cpu.registrers.hl), 4);
}

void bit_5_a(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.a, 5);
}

void bit_5_b(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.b, 5);
}

void bit_5_c(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.c, 5);
}

void bit_5_d(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.d, 5);
}

void bit_5_e(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.e, 5);
}

void bit_5_h(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.h, 5);
}

void bit_5_l(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.l, 5);
}

void bit_5_hlp(GameBoy &gameboy)
{
  bit(gameboy, gameboy.memory.read_byte(gameboy.cpu.registrers.hl), 5);
}

void bit_6_a(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.a, 6);
}

void bit_6_b(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.b, 6);
}

void bit_6_c(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.c, 6);
}

void bit_6_d(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.d, 6);
}

void bit_6_e(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.e, 6);
}

void bit_6_h(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.h, 6);
}

void bit_6_l(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.l, 6);
}

void bit_6_hlp(GameBoy &gameboy)
{
  bit(gameboy, gameboy.memory.read_byte(gameboy.cpu.registrers.hl), 6);
}

void bit_7_a(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.a, 7);
}

void bit_7_b(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.b, 7);
}

void bit_7_c(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.c, 7);
}

void bit_7_d(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.d, 7);
}

void bit_7_e(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.e, 7);
}

void bit_7_h(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.h, 7);
}

void bit_7_l(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.l, 7);
}

void bit_7_hlp(GameBoy &gameboy)
{
  bit(gameboy, gameboy.memory.read_byte(gameboy.cpu.registrers.hl), 7);
}

void set(uint8_t &value, uint8_t bit)
{
  value |= 1 << bit;
}

void set_0_a(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.a, 0);
}

void set_0_b(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.b, 0);
}

void set_0_c(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.c, 0);
}

void set_0_d(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.d, 0);
}

void set_0_e(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.e, 0);
}

void set_0_h(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.h, 0);
}

void set_0_l(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.l, 0);
}

void set_0_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  set(value, 0);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void set_1_a(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.a, 1);
}

void set_1_b(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.b, 1);
}

void set_1_c(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.c, 1);
}

void set_1_d(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.d, 1);
}

void set_1_e(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.e, 1);
}

void set_1_h(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.h, 1);
}

void set_1_l(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.l, 1);
}

void set_1_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  set(value, 1);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void set_2_a(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.a, 2);
}

void set_2_b(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.b, 2);
}

void set_2_c(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.c, 2);
}

void set_2_d(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.d, 2);
}

void set_2_e(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.e, 2);
}

void set_2_h(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.h, 2);
}

void set_2_l(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.l, 2);
}

void set_2_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  set(value, 2);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void set_3_a(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.a, 3);
}

void set_3_b(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.b, 3);
}

void set_3_c(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.c, 3);
}

void set_3_d(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.d, 3);
}

void set_3_e(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.e, 3);
}

void set_3_h(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.h, 3);
}

void set_3_l(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.l, 3);
}

void set_3_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  set(value, 3);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void set_4_a(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.a, 4);
}

void set_4_b(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.b, 4);
}

void set_4_c(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.c, 4);
}

void set_4_d(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.d, 4);
}

void set_4_e(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.e, 4);
}

void set_4_h(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.h, 4);
}

void set_4_l(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.l, 4);
}

void set_4_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  set(value, 4);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void set_5_a(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.a, 5);
}

void set_5_b(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.b, 5);
}

void set_5_c(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.c, 5);
}

void set_5_d(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.d, 5);
}

void set_5_e(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.e, 5);
}

void set_5_h(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.h, 5);
}

void set_5_l(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.l, 5);
}

void set_5_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  set(value, 5);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void set_6_a(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.a, 6);
}

void set_6_b(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.b, 6);
}

void set_6_c(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.c, 6);
}

void set_6_d(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.d, 6);
}

void set_6_e(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.e, 6);
}

void set_6_h(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.h, 6);
}

void set_6_l(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.l, 6);
}

void set_6_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  set(value, 6);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void set_7_a(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.a, 7);
}

void set_7_b(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.b, 7);
}

void set_7_c(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.c, 7);
}

void set_7_d(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.d, 7);
}

void set_7_e(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.e, 7);
}

void set_7_h(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.h, 7);
}

void set_7_l(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.l, 7);
}

void set_7_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  set(value, 7);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void reset(uint8_t &value, uint8_t bit)
{
  value &= ~(1 << bit);
}

void reset_0_a(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.a, 0);
}

void reset_0_b(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.b, 0);
}

void reset_0_c(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.c, 0);
}

void reset_0_d(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.d, 0);
}

void reset_0_e(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.e, 0);
}

void reset_0_h(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.h, 0);
}

void reset_0_l(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.l, 0);
}

void reset_0_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  reset(value, 0);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void reset_1_a(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.a, 1);
}

void reset_1_b(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.b, 1);
}

void reset_1_c(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.c, 1);
}

void reset_1_d(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.d, 1);
}

void reset_1_e(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.e, 1);
}

void reset_1_h(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.h, 1);
}

void reset_1_l(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.l, 1);
}

void reset_1_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  reset(value, 1);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void reset_2_a(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.a, 2);
}

void reset_2_b(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.b, 2);
}

void reset_2_c(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.c, 2);
}

void reset_2_d(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.d, 2);
}

void reset_2_e(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.e, 2);
}

void reset_2_h(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.h, 2);
}

void reset_2_l(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.l, 2);
}

void reset_2_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  reset(value, 2);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void reset_3_a(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.a, 3);
}

void reset_3_b(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.b, 3);
}

void reset_3_c(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.c, 3);
}

void reset_3_d(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.d, 3);
}

void reset_3_e(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.e, 3);
}

void reset_3_h(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.h, 3);
}

void reset_3_l(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.l, 3);
}

void reset_3_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  reset(value, 3);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void reset_4_a(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.a, 4);
}

void reset_4_b(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.b, 4);
}

void reset_4_c(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.c, 4);
}

void reset_4_d(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.d, 4);
}

void reset_4_e(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.e, 4);
}

void reset_4_h(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.h, 4);
}

void reset_4_l(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.l, 4);
}

void reset_4_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  reset(value, 4);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void reset_5_a(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.a, 5);
}

void reset_5_b(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.b, 5);
}

void reset_5_c(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.c, 5);
}

void reset_5_d(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.d, 5);
}

void reset_5_e(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.e, 5);
}

void reset_5_h(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.h, 5);
}

void reset_5_l(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.l, 5);
}

void reset_5_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  reset(value, 5);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void reset_6_a(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.a, 6);
}

void reset_6_b(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.b, 6);
}

void reset_6_c(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.c, 6);
}

void reset_6_d(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.d, 6);
}

void reset_6_e(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.e, 6);
}

void reset_6_h(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.h, 6);
}

void reset_6_l(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.l, 6);
}

void reset_6_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  reset(value, 6);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void reset_7_a(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.a, 7);
}

void reset_7_b(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.b, 7);
}

void reset_7_c(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.c, 7);
}

void reset_7_d(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.d, 7);
}

void reset_7_e(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.e, 7);
}

void reset_7_h(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.h, 7);
}

void reset_7_l(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.l, 7);
}

void reset_7_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  reset(value, 7);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

const struct ExtendedInstruction extended_instruction_set[256] = {
    {"RLC B", 8, NULL},               // 0x00
    {"RLC C", 8, NULL},               // 0x01
    {"RLC D", 8, NULL},               // 0x02
    {"RLC E", 8, NULL},               // 0x03
    {"RLC H", 8, NULL},               // 0x04
    {"RLC L", 8, NULL},               // 0x05
    {"RLC (HL)", 16, NULL},           // 0x06
    {"RLC A", 8, NULL},               // 0x07
    {"RRC B", 8, NULL},               // 0x08
    {"RRC C", 8, NULL},               // 0x09
    {"RRC D", 8, NULL},               // 0x0a
    {"RRC E", 8, NULL},               // 0x0b
    {"RRC H", 8, NULL},               // 0x0c
    {"RRC L", 8, NULL},               // 0x0d
    {"RRC (HL)", 16, NULL},           // 0x0e
    {"RRC A", 8, NULL},               // 0x0f
    {"RL B", 8, NULL},                // 0x10
    {"RL C", 8, NULL},                // 0x11
    {"RL D", 8, NULL},                // 0x12
    {"RL E", 8, NULL},                // 0x13
    {"RL H", 8, NULL},                // 0x14
    {"RL L", 8, NULL},                // 0x15
    {"RL (HL)", 16, NULL},            // 0x16
    {"RL A", 8, NULL},                // 0x17
    {"RR B", 8, rr_b},                // 0x18
    {"RR C", 8, rr_c},                // 0x19
    {"RR D", 8, rr_d},                // 0x1a
    {"RR E", 8, rr_e},                // 0x1b
    {"RR H", 8, rr_h},                // 0x1c
    {"RR L", 8, rr_l},                // 0x1d
    {"RR (HL)", 16, rr_hlp},          // 0x1e
    {"RR A", 8, rr_a},                // 0x1f
    {"SLA B", 8, sla_b},              // 0x20
    {"SLA C", 8, sla_c},              // 0x21
    {"SLA D", 8, sla_d},              // 0x22
    {"SLA E", 8, sla_e},              // 0x23
    {"SLA H", 8, sla_h},              // 0x24
    {"SLA L", 8, sla_l},              // 0x25
    {"SLA (HL)", 16, sla_hlp},        // 0x26
    {"SLA A", 8, sla_a},              // 0x27
    {"SRA B", 8, sra_b},              // 0x28
    {"SRA C", 8, sra_c},              // 0x29
    {"SRA D", 8, sra_d},              // 0x2a
    {"SRA E", 8, sra_e},              // 0x2b
    {"SRA H", 8, sra_h},              // 0x2c
    {"SRA L", 8, sra_l},              // 0x2d
    {"SRA (HL)", 16, sra_hlp},        // 0x2e
    {"SRA A", 8, sra_a},              // 0x2f
    {"SWAP B", 8, swap_b},            // 0x30
    {"SWAP C", 8, swap_c},            // 0x31
    {"SWAP D", 8, swap_d},            // 0x32
    {"SWAP E", 8, swap_e},            // 0x33
    {"SWAP H", 8, swap_h},            // 0x34
    {"SWAP L", 8, swap_l},            // 0x35
    {"SWAP (HL)", 16, swap_hl},       // 0x36
    {"SWAP A", 8, swap_a},            // 0x37
    {"SRL B", 8, srl_b},              // 0x38
    {"SRL C", 8, srl_c},              // 0x39
    {"SRL D", 8, srl_d},              // 0x3a
    {"SRL E", 8, srl_e},              // 0x3b
    {"SRL H", 8, srl_h},              // 0x3c
    {"SRL L", 8, srl_l},              // 0x3d
    {"SRL (HL)", 16, srl_hlp},        // 0x3e
    {"SRL A", 8, srl_a},              // 0x3f
    {"BIT 0, B", 8, bit_0_b},         // 0x40
    {"BIT 0, C", 8, bit_0_c},         // 0x41
    {"BIT 0, D", 8, bit_0_d},         // 0x42
    {"BIT 0, E", 8, bit_0_e},         // 0x43
    {"BIT 0, H", 8, bit_0_h},         // 0x44
    {"BIT 0, L", 8, bit_0_l},         // 0x45
    {"BIT 0, (HL)", 12, bit_0_hlp},   // 0x46
    {"BIT 0, A", 8, bit_0_a},         // 0x47
    {"BIT 1, B", 8, bit_1_b},         // 0x48
    {"BIT 1, C", 8, bit_1_c},         // 0x49
    {"BIT 1, D", 8, bit_1_d},         // 0x4a
    {"BIT 1, E", 8, bit_1_e},         // 0x4b
    {"BIT 1, H", 8, bit_1_h},         // 0x4c
    {"BIT 1, L", 8, bit_1_l},         // 0x4d
    {"BIT 1, (HL)", 12, bit_1_hlp},   // 0x4e
    {"BIT 1, A", 8, bit_1_a},         // 0x4f
    {"BIT 2, B", 8, bit_2_b},         // 0x50
    {"BIT 2, C", 8, bit_2_c},         // 0x51
    {"BIT 2, D", 8, bit_2_d},         // 0x52
    {"BIT 2, E", 8, bit_2_e},         // 0x53
    {"BIT 2, H", 8, bit_2_h},         // 0x54
    {"BIT 2, L", 8, bit_2_l},         // 0x55
    {"BIT 2, (HL)", 12, bit_2_hlp},   // 0x56
    {"BIT 2, A", 8, bit_2_h},         // 0x57
    {"BIT 3, B", 8, bit_3_b},         // 0x58
    {"BIT 3, C", 8, bit_3_c},         // 0x59
    {"BIT 3, D", 8, bit_3_d},         // 0x5a
    {"BIT 3, E", 8, bit_3_e},         // 0x5b
    {"BIT 3, H", 8, bit_3_h},         // 0x5c
    {"BIT 3, L", 8, bit_3_l},         // 0x5d
    {"BIT 3, (HL)", 12, bit_3_hlp},   // 0x5e
    {"BIT 3, A", 8, bit_3_a},         // 0x5f
    {"BIT 4, B", 8, bit_4_b},         // 0x60
    {"BIT 4, C", 8, bit_4_c},         // 0x61
    {"BIT 4, D", 8, bit_4_d},         // 0x62
    {"BIT 4, E", 8, bit_4_e},         // 0x63
    {"BIT 4, H", 8, bit_4_h},         // 0x64
    {"BIT 4, L", 8, bit_4_l},         // 0x65
    {"BIT 4, (HL)", 12, bit_4_hlp},   // 0x66
    {"BIT 4, A", 8, bit_4_a},         // 0x67
    {"BIT 5, B", 8, bit_5_b},         // 0x68
    {"BIT 5, C", 8, bit_5_c},         // 0x69
    {"BIT 5, D", 8, bit_5_d},         // 0x6a
    {"BIT 5, E", 8, bit_5_e},         // 0x6b
    {"BIT 6, H", 8, bit_5_h},         // 0x6c
    {"BIT 6, L", 8, bit_5_l},         // 0x6d
    {"BIT 5, (HL)", 12, bit_5_hlp},   // 0x6e
    {"BIT 5, A", 8, bit_5_a},         // 0x6f
    {"BIT 6, B", 8, bit_6_b},         // 0x70
    {"BIT 6, C", 8, bit_6_c},         // 0x71
    {"BIT 6, D", 8, bit_6_d},         // 0x72
    {"BIT 6, E", 8, bit_6_e},         // 0x73
    {"BIT 6, H", 8, bit_6_h},         // 0x74
    {"BIT 6, L", 8, bit_6_l},         // 0x75
    {"BIT 6, (HL)", 12, bit_6_hlp},   // 0x76
    {"BIT 6, A", 8, bit_6_a},         // 0x77
    {"BIT 7, B", 8, bit_7_b},         // 0x78
    {"BIT 7, C", 8, bit_7_c},         // 0x79
    {"BIT 7, D", 8, bit_7_d},         // 0x7a
    {"BIT 7, E", 8, bit_7_e},         // 0x7b
    {"BIT 7, H", 8, bit_7_h},         // 0x7c
    {"BIT 7, L", 8, bit_7_l},         // 0x7d
    {"BIT 7, (HL)", 12, bit_7_hlp},   // 0x7e
    {"BIT 7, A", 8, bit_7_a},         // 0x7f
    {"RES 0, B", 8, reset_0_b},       // 0x80
    {"RES 0, C", 8, reset_0_c},       // 0x81
    {"RES 0, D", 8, reset_0_d},       // 0x82
    {"RES 0, E", 8, reset_0_e},       // 0x83
    {"RES 0, H", 8, reset_0_h},       // 0x84
    {"RES 0, L", 8, reset_0_l},       // 0x85
    {"RES 0, (HL)", 12, reset_0_hlp}, // 0x86
    {"RES 0, A", 8, reset_0_a},       // 0x87
    {"RES 1, B", 8, reset_1_b},       // 0x88
    {"RES 1, C", 8, reset_1_c},       // 0x89
    {"RES 1, D", 8, reset_1_d},       // 0x8a
    {"RES 1, E", 8, reset_1_e},       // 0x8b
    {"RES 1, H", 8, reset_1_h},       // 0x8c
    {"RES 1, L", 8, reset_1_l},       // 0x8d
    {"RES 1, (HL)", 12, reset_1_hlp}, // 0x8e
    {"RES 1, A", 8, reset_1_a},       // 0x8f
    {"RES 2, B", 8, reset_2_b},       // 0x90
    {"RES 2, C", 8, reset_2_c},       // 0x91
    {"RES 2, D", 8, reset_2_d},       // 0x92
    {"RES 2, E", 8, reset_2_e},       // 0x93
    {"RES 2, H", 8, reset_2_h},       // 0x94
    {"RES 2, L", 8, reset_2_l},       // 0x95
    {"RES 2, (HL)", 12, reset_2_hlp}, // 0x96
    {"RES 2, A", 8, reset_2_a},       // 0x97
    {"RES 3, B", 8, reset_3_b},       // 0x98
    {"RES 3, C", 8, reset_3_c},       // 0x99
    {"RES 3, D", 8, reset_3_d},       // 0x9a
    {"RES 3, E", 8, reset_3_e},       // 0x9b
    {"RES 3, H", 8, reset_3_h},       // 0x9c
    {"RES 3, L", 8, reset_3_l},       // 0x9d
    {"RES 3, (HL)", 12, reset_3_hlp}, // 0x9e
    {"RES 3, A", 8, reset_3_a},       // 0x9f
    {"RES 4, B", 8, reset_4_b},       // 0xa0
    {"RES 4, C", 8, reset_4_c},       // 0xa1
    {"RES 4, D", 8, reset_4_d},       // 0xa2
    {"RES 4, E", 8, reset_4_e},       // 0xa3
    {"RES 4, H", 8, reset_4_h},       // 0xa4
    {"RES 4, L", 8, reset_4_l},       // 0xa5
    {"RES 4, (HL)", 12, reset_4_hlp}, // 0xa6
    {"RES 4, A", 8, reset_4_a},       // 0xa7
    {"RES 5, B", 8, reset_5_b},       // 0xa8
    {"RES 5, C", 8, reset_5_c},       // 0xa9
    {"RES 5, D", 8, reset_5_d},       // 0xaa
    {"RES 5, E", 8, reset_5_e},       // 0xab
    {"RES 5, H", 8, reset_5_h},       // 0xac
    {"RES 5, L", 8, reset_5_l},       // 0xad
    {"RES 5, (HL)", 12, reset_5_hlp}, // 0xae
    {"RES 5, A", 8, reset_5_a},       // 0xaf
    {"RES 6, B", 8, reset_6_b},       // 0xb0
    {"RES 6, C", 8, reset_6_c},       // 0xb1
    {"RES 6, D", 8, reset_6_d},       // 0xb2
    {"RES 6, E", 8, reset_6_e},       // 0xb3
    {"RES 6, H", 8, reset_6_h},       // 0xb4
    {"RES 6, L", 8, reset_6_l},       // 0xb5
    {"RES 6, (HL)", 12, reset_6_hlp}, // 0xb6
    {"RES 6, A", 8, reset_6_a},       // 0xb7
    {"RES 7, B", 8, reset_7_b},       // 0xb8
    {"RES 7, C", 8, reset_7_c},       // 0xb9
    {"RES 7, D", 8, reset_7_d},       // 0xba
    {"RES 7, E", 8, reset_7_e},       // 0xbb
    {"RES 7, H", 8, reset_7_h},       // 0xbc
    {"RES 7, L", 8, reset_7_l},       // 0xbd
    {"RES 7, (HL)", 12, reset_7_hlp}, // 0xbe
    {"RES 7, A", 8, reset_7_a},       // 0xbf
    {"SET 0, B", 8, set_0_b},         // 0xc0
    {"SET 0, C", 8, set_0_c},         // 0xc1
    {"SET 0, D", 8, set_0_d},         // 0xc2
    {"SET 0, E", 8, set_0_e},         // 0xc3
    {"SET 0, H", 8, set_0_h},         // 0xc4
    {"SET 0, L", 8, set_0_l},         // 0xc5
    {"SET 0, (HL)", 12, set_0_hlp},   // 0xc6
    {"SET 0, A", 8, set_0_a},         // 0xc7
    {"SET 1, B", 8, set_1_b},         // 0xc8
    {"SET 1, C", 8, set_1_c},         // 0xc9
    {"SET 1, D", 8, set_1_d},         // 0xca
    {"SET 1, E", 8, set_1_e},         // 0xcb
    {"SET 1, H", 8, set_1_h},         // 0xcc
    {"SET 1, L", 8, set_1_l},         // 0xcd
    {"SET 1, (HL)", 12, set_2_hlp},   // 0xce
    {"SET 1, A", 8, set_2_a},         // 0xcf
    {"SET 2, B", 8, set_2_b},         // 0xd0
    {"SET 2, C", 8, set_2_c},         // 0xd1
    {"SET 2, D", 8, set_2_d},         // 0xd2
    {"SET 2, E", 8, set_2_e},         // 0xd3
    {"SET 2, H", 8, set_2_h},         // 0xd4
    {"SET 2, L", 8, set_2_l},         // 0xd5
    {"SET 2, (HL)", 12, set_2_hlp},   // 0xd6
    {"SET 2, A", 8, set_2_a},         // 0xd7
    {"SET 3, B", 8, set_3_b},         // 0xd8
    {"SET 3, C", 8, set_3_c},         // 0xd9
    {"SET 3, D", 8, set_3_d},         // 0xda
    {"SET 3, E", 8, set_3_e},         // 0xdb
    {"SET 3, H", 8, set_3_h},         // 0xdc
    {"SET 3, L", 8, set_3_l},         // 0xdd
    {"SET 3, (HL)", 12, set_3_hlp},   // 0xde
    {"SET 3, A", 8, set_3_a},         // 0xdf
    {"SET 4, B", 8, set_4_b},         // 0xe0
    {"SET 4, C", 8, set_4_c},         // 0xe1
    {"SET 4, D", 8, set_4_d},         // 0xe2
    {"SET 4, E", 8, set_4_e},         // 0xe3
    {"SET 4, H", 8, set_4_h},         // 0xe4
    {"SET 4, L", 8, set_4_l},         // 0xe5
    {"SET 4, (HL)", 12, set_4_hlp},   // 0xe6
    {"SET 4, A", 8, set_4_a},         // 0xe7
    {"SET 5, B", 8, set_5_b},         // 0xe8
    {"SET 5, C", 8, set_5_c},         // 0xe9
    {"SET 5, D", 8, set_5_d},         // 0xea
    {"SET 5, E", 8, set_5_e},         // 0xeb
    {"SET 5, H", 8, set_5_h},         // 0xec
    {"SET 5, L", 8, set_5_l},         // 0xed
    {"SET 5, (HL)", 12, set_5_hlp},   // 0xee
    {"SET 5, A", 8, set_5_a},         // 0xef
    {"SET 6, B", 8, set_6_b},         // 0xf0
    {"SET 6, C", 8, set_6_c},         // 0xf1
    {"SET 6, D", 8, set_6_d},         // 0xf2
    {"SET 6, E", 8, set_6_e},         // 0xf3
    {"SET 6, H", 8, set_6_h},         // 0xf4
    {"SET 6, L", 8, set_6_l},         // 0xf5
    {"SET 6, (HL)", 12, set_6_hlp},   // 0xf6
    {"SET 6, A", 8, set_6_a},         // 0xf7
    {"SET 7, B", 8, set_7_b},         // 0xf8
    {"SET 7, C", 8, set_7_c},         // 0xf9
    {"SET 7, D", 8, set_7_d},         // 0xfa
    {"SET 7, E", 8, set_7_e},         // 0xfb
    {"SET 7, H", 8, set_7_h},         // 0xfc
    {"SET 7, L", 8, set_7_l},         // 0xfd
    {"SET 7, (HL)", 12, set_7_hlp},   // 0xfe
    {"SET 7, A", 8, set_7_a},         // 0xff
};
