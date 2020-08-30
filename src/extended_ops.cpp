#include <cassert>
#include <string>

#include "common_ops.h"
#include "extended_ops.h"
#include "gameboy.h"
#include "ops.h"

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

void rl_a(GameBoy &gameboy)
{
  rl(gameboy, gameboy.cpu.registrers.a);
}

void rl_b(GameBoy &gameboy)
{
  rl(gameboy, gameboy.cpu.registrers.b);
}

void rl_c(GameBoy &gameboy)
{
  rl(gameboy, gameboy.cpu.registrers.c);
}

void rl_d(GameBoy &gameboy)
{
  rl(gameboy, gameboy.cpu.registrers.d);
}

void rl_e(GameBoy &gameboy)
{
  rl(gameboy, gameboy.cpu.registrers.e);
}

void rl_h(GameBoy &gameboy)
{
  rl(gameboy, gameboy.cpu.registrers.h);
}

void rl_l(GameBoy &gameboy)
{
  rl(gameboy, gameboy.cpu.registrers.l);
}

void rl_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  rl(gameboy, value);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void rlc_a(GameBoy &gameboy)
{
  rlc(gameboy, gameboy.cpu.registrers.a);
}

void rlc_b(GameBoy &gameboy)
{
  rlc(gameboy, gameboy.cpu.registrers.b);
}

void rlc_c(GameBoy &gameboy)
{
  rlc(gameboy, gameboy.cpu.registrers.c);
}

void rlc_d(GameBoy &gameboy)
{
  rlc(gameboy, gameboy.cpu.registrers.d);
}

void rlc_e(GameBoy &gameboy)
{
  rlc(gameboy, gameboy.cpu.registrers.e);
}

void rlc_h(GameBoy &gameboy)
{
  rlc(gameboy, gameboy.cpu.registrers.h);
}

void rlc_l(GameBoy &gameboy)
{
  rlc(gameboy, gameboy.cpu.registrers.l);
}

void rlc_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  rlc(gameboy, value);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void rrc_a(GameBoy &gameboy)
{
  rrc(gameboy, gameboy.cpu.registrers.a);
}

void rrc_b(GameBoy &gameboy)
{
  rrc(gameboy, gameboy.cpu.registrers.b);
}

void rrc_c(GameBoy &gameboy)
{
  rrc(gameboy, gameboy.cpu.registrers.c);
}

void rrc_d(GameBoy &gameboy)
{
  rrc(gameboy, gameboy.cpu.registrers.d);
}

void rrc_e(GameBoy &gameboy)
{
  rrc(gameboy, gameboy.cpu.registrers.e);
}

void rrc_h(GameBoy &gameboy)
{
  rrc(gameboy, gameboy.cpu.registrers.h);
}

void rrc_l(GameBoy &gameboy)
{
  rrc(gameboy, gameboy.cpu.registrers.l);
}

void rrc_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  rrc(gameboy, value);
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
  assert(bit >= 0 && bit < 8);
  gameboy.cpu.registrers.f.z = (value >> bit & 0x01) == 0;
  gameboy.cpu.registrers.f.n = 0;
  gameboy.cpu.registrers.f.h = 1;
}

template <uint8_t bit_to_check>
void bit_a(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.a, bit_to_check);
}

template <uint8_t bit_to_check>
void bit_b(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.b, bit_to_check);
}

template <uint8_t bit_to_check>
void bit_c(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.c, bit_to_check);
}

template <uint8_t bit_to_check>
void bit_d(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.d, bit_to_check);
}

template <uint8_t bit_to_check>
void bit_e(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.e, bit_to_check);
}

template <uint8_t bit_to_check>
void bit_h(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.h, bit_to_check);
}

template <uint8_t bit_to_check>
void bit_l(GameBoy &gameboy)
{
  bit(gameboy, gameboy.cpu.registrers.l, bit_to_check);
}

template <uint8_t bit_to_check>
void bit_hlp(GameBoy &gameboy)
{
  bit(gameboy, gameboy.memory.read_byte(gameboy.cpu.registrers.hl), bit_to_check);
}

void set(uint8_t &value, uint8_t bit)
{
  assert(bit >= 0 && bit < 8);
  value |= 1 << bit;
}

template <uint8_t bit>
void set_a(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.a, bit);
}

template <uint8_t bit>
void set_b(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.b, bit);
}

template <uint8_t bit>
void set_c(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.c, bit);
}

template <uint8_t bit>
void set_d(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.d, bit);
}

template <uint8_t bit>
void set_e(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.e, bit);
}

template <uint8_t bit>
void set_h(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.h, bit);
}

template <uint8_t bit>
void set_l(GameBoy &gameboy)
{
  set(gameboy.cpu.registrers.l, bit);
}

template <uint8_t bit>
void set_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  set(value, bit);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void reset(uint8_t &value, uint8_t bit)
{
  assert(bit >= 0 && bit < 8);
  value &= ~(1 << bit);
}

template <uint8_t bit>
void reset_a(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.a, bit);
}

template <uint8_t bit>
void reset_b(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.b, bit);
}

template <uint8_t bit>
void reset_c(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.c, bit);
}

template <uint8_t bit>
void reset_d(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.d, bit);
}

template <uint8_t bit>
void reset_e(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.e, bit);
}

template <uint8_t bit>
void reset_h(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.h, bit);
}

template <uint8_t bit>
void reset_l(GameBoy &gameboy)
{
  reset(gameboy.cpu.registrers.l, bit);
}

template <uint8_t bit>
void reset_hlp(GameBoy &gameboy)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  reset(value, bit);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

const struct ExtendedInstruction extended_instruction_set[256] = {
    {"RLC B", 8, rlc_b},               // 0x00
    {"RLC C", 8, rlc_c},               // 0x01
    {"RLC D", 8, rlc_d},               // 0x02
    {"RLC E", 8, rlc_e},               // 0x03
    {"RLC H", 8, rlc_h},               // 0x04
    {"RLC L", 8, rlc_l},               // 0x05
    {"RLC (HL)", 16, rlc_hlp},         // 0x06
    {"RLC A", 8, rlc_a},               // 0x07
    {"RRC B", 8, rrc_b},               // 0x08
    {"RRC C", 8, rrc_c},               // 0x09
    {"RRC D", 8, rrc_d},               // 0x0a
    {"RRC E", 8, rrc_e},               // 0x0b
    {"RRC H", 8, rrc_h},               // 0x0c
    {"RRC L", 8, rrc_l},               // 0x0d
    {"RRC (HL)", 16, rrc_hlp},         // 0x0e
    {"RRC A", 8, rrc_a},               // 0x0f
    {"RL B", 8, rl_b},                 // 0x10
    {"RL C", 8, rl_c},                 // 0x11
    {"RL D", 8, rl_d},                 // 0x12
    {"RL E", 8, rl_e},                 // 0x13
    {"RL H", 8, rl_h},                 // 0x14
    {"RL L", 8, rl_l},                 // 0x15
    {"RL (HL)", 16, rl_hlp},           // 0x16
    {"RL A", 8, rl_a},                 // 0x17
    {"RR B", 8, rr_b},                 // 0x18
    {"RR C", 8, rr_c},                 // 0x19
    {"RR D", 8, rr_d},                 // 0x1a
    {"RR E", 8, rr_e},                 // 0x1b
    {"RR H", 8, rr_h},                 // 0x1c
    {"RR L", 8, rr_l},                 // 0x1d
    {"RR (HL)", 16, rr_hlp},           // 0x1e
    {"RR A", 8, rr_a},                 // 0x1f
    {"SLA B", 8, sla_b},               // 0x20
    {"SLA C", 8, sla_c},               // 0x21
    {"SLA D", 8, sla_d},               // 0x22
    {"SLA E", 8, sla_e},               // 0x23
    {"SLA H", 8, sla_h},               // 0x24
    {"SLA L", 8, sla_l},               // 0x25
    {"SLA (HL)", 16, sla_hlp},         // 0x26
    {"SLA A", 8, sla_a},               // 0x27
    {"SRA B", 8, sra_b},               // 0x28
    {"SRA C", 8, sra_c},               // 0x29
    {"SRA D", 8, sra_d},               // 0x2a
    {"SRA E", 8, sra_e},               // 0x2b
    {"SRA H", 8, sra_h},               // 0x2c
    {"SRA L", 8, sra_l},               // 0x2d
    {"SRA (HL)", 16, sra_hlp},         // 0x2e
    {"SRA A", 8, sra_a},               // 0x2f
    {"SWAP B", 8, swap_b},             // 0x30
    {"SWAP C", 8, swap_c},             // 0x31
    {"SWAP D", 8, swap_d},             // 0x32
    {"SWAP E", 8, swap_e},             // 0x33
    {"SWAP H", 8, swap_h},             // 0x34
    {"SWAP L", 8, swap_l},             // 0x35
    {"SWAP (HL)", 16, swap_hl},        // 0x36
    {"SWAP A", 8, swap_a},             // 0x37
    {"SRL B", 8, srl_b},               // 0x38
    {"SRL C", 8, srl_c},               // 0x39
    {"SRL D", 8, srl_d},               // 0x3a
    {"SRL E", 8, srl_e},               // 0x3b
    {"SRL H", 8, srl_h},               // 0x3c
    {"SRL L", 8, srl_l},               // 0x3d
    {"SRL (HL)", 16, srl_hlp},         // 0x3e
    {"SRL A", 8, srl_a},               // 0x3f
    {"BIT 0, B", 8, bit_b<0>},         // 0x40
    {"BIT 0, C", 8, bit_c<0>},         // 0x41
    {"BIT 0, D", 8, bit_d<0>},         // 0x42
    {"BIT 0, E", 8, bit_e<0>},         // 0x43
    {"BIT 0, H", 8, bit_h<0>},         // 0x44
    {"BIT 0, L", 8, bit_l<0>},         // 0x45
    {"BIT 0, (HL)", 12, bit_hlp<0>},   // 0x46
    {"BIT 0, A", 8, bit_a<0>},         // 0x47
    {"BIT 1, B", 8, bit_b<1>},         // 0x48
    {"BIT 1, C", 8, bit_c<1>},         // 0x49
    {"BIT 1, D", 8, bit_d<1>},         // 0x4a
    {"BIT 1, E", 8, bit_e<1>},         // 0x4b
    {"BIT 1, H", 8, bit_h<1>},         // 0x4c
    {"BIT 1, L", 8, bit_l<1>},         // 0x4d
    {"BIT 1, (HL)", 12, bit_hlp<1>},   // 0x4e
    {"BIT 1, A", 8, bit_a<1>},         // 0x4f
    {"BIT 2, B", 8, bit_b<2>},         // 0x50
    {"BIT 2, C", 8, bit_c<2>},         // 0x51
    {"BIT 2, D", 8, bit_d<2>},         // 0x52
    {"BIT 2, E", 8, bit_e<2>},         // 0x53
    {"BIT 2, H", 8, bit_h<2>},         // 0x54
    {"BIT 2, L", 8, bit_l<2>},         // 0x55
    {"BIT 2, (HL)", 12, bit_hlp<2>},   // 0x56
    {"BIT 2, A", 8, bit_a<2>},         // 0x57
    {"BIT 3, B", 8, bit_b<3>},         // 0x58
    {"BIT 3, C", 8, bit_c<3>},         // 0x59
    {"BIT 3, D", 8, bit_d<3>},         // 0x5a
    {"BIT 3, E", 8, bit_e<3>},         // 0x5b
    {"BIT 3, H", 8, bit_h<3>},         // 0x5c
    {"BIT 3, L", 8, bit_l<3>},         // 0x5d
    {"BIT 3, (HL)", 12, bit_hlp<3>},   // 0x5e
    {"BIT 3, A", 8, bit_a<3>},         // 0x5f
    {"BIT 4, B", 8, bit_b<4>},         // 0x60
    {"BIT 4, C", 8, bit_c<4>},         // 0x61
    {"BIT 4, D", 8, bit_d<4>},         // 0x62
    {"BIT 4, E", 8, bit_e<4>},         // 0x63
    {"BIT 4, H", 8, bit_h<4>},         // 0x64
    {"BIT 4, L", 8, bit_l<4>},         // 0x65
    {"BIT 4, (HL)", 12, bit_hlp<4>},   // 0x66
    {"BIT 4, A", 8, bit_a<4>},         // 0x67
    {"BIT 5, B", 8, bit_b<5>},         // 0x68
    {"BIT 5, C", 8, bit_c<5>},         // 0x69
    {"BIT 5, D", 8, bit_d<5>},         // 0x6a
    {"BIT 5, E", 8, bit_e<5>},         // 0x6b
    {"BIT 6, H", 8, bit_h<5>},         // 0x6c
    {"BIT 6, L", 8, bit_l<5>},         // 0x6d
    {"BIT 5, (HL)", 12, bit_hlp<5>},   // 0x6e
    {"BIT 5, A", 8, bit_a<5>},         // 0x6f
    {"BIT 6, B", 8, bit_b<6>},         // 0x70
    {"BIT 6, C", 8, bit_c<6>},         // 0x71
    {"BIT 6, D", 8, bit_d<6>},         // 0x72
    {"BIT 6, E", 8, bit_e<6>},         // 0x73
    {"BIT 6, H", 8, bit_h<6>},         // 0x74
    {"BIT 6, L", 8, bit_l<6>},         // 0x75
    {"BIT 6, (HL)", 12, bit_hlp<6>},   // 0x76
    {"BIT 6, A", 8, bit_a<6>},         // 0x77
    {"BIT 7, B", 8, bit_b<7>},         // 0x78
    {"BIT 7, C", 8, bit_c<7>},         // 0x79
    {"BIT 7, D", 8, bit_d<7>},         // 0x7a
    {"BIT 7, E", 8, bit_e<7>},         // 0x7b
    {"BIT 7, H", 8, bit_h<7>},         // 0x7c
    {"BIT 7, L", 8, bit_l<7>},         // 0x7d
    {"BIT 7, (HL)", 12, bit_hlp<7>},   // 0x7e
    {"BIT 7, A", 8, bit_a<7>},         // 0x7f
    {"RES 0, B", 8, reset_b<0>},       // 0x80
    {"RES 0, C", 8, reset_c<0>},       // 0x81
    {"RES 0, D", 8, reset_d<0>},       // 0x82
    {"RES 0, E", 8, reset_e<0>},       // 0x83
    {"RES 0, H", 8, reset_h<0>},       // 0x84
    {"RES 0, L", 8, reset_l<0>},       // 0x85
    {"RES 0, (HL)", 12, reset_hlp<0>}, // 0x86
    {"RES 0, A", 8, reset_a<0>},       // 0x87
    {"RES 1, B", 8, reset_b<1>},       // 0x88
    {"RES 1, C", 8, reset_c<1>},       // 0x89
    {"RES 1, D", 8, reset_d<1>},       // 0x8a
    {"RES 1, E", 8, reset_e<1>},       // 0x8b
    {"RES 1, H", 8, reset_h<1>},       // 0x8c
    {"RES 1, L", 8, reset_l<1>},       // 0x8d
    {"RES 1, (HL)", 12, reset_hlp<1>}, // 0x8e
    {"RES 1, A", 8, reset_a<1>},       // 0x8f
    {"RES 2, B", 8, reset_b<2>},       // 0x90
    {"RES 2, C", 8, reset_c<2>},       // 0x91
    {"RES 2, D", 8, reset_d<2>},       // 0x92
    {"RES 2, E", 8, reset_e<2>},       // 0x93
    {"RES 2, H", 8, reset_h<2>},       // 0x94
    {"RES 2, L", 8, reset_l<2>},       // 0x95
    {"RES 2, (HL)", 12, reset_hlp<2>}, // 0x96
    {"RES 2, A", 8, reset_a<2>},       // 0x97
    {"RES 3, B", 8, reset_b<3>},       // 0x98
    {"RES 3, C", 8, reset_c<3>},       // 0x99
    {"RES 3, D", 8, reset_d<3>},       // 0x9a
    {"RES 3, E", 8, reset_e<3>},       // 0x9b
    {"RES 3, H", 8, reset_h<3>},       // 0x9c
    {"RES 3, L", 8, reset_l<3>},       // 0x9d
    {"RES 3, (HL)", 12, reset_hlp<3>}, // 0x9e
    {"RES 3, A", 8, reset_a<3>},       // 0x9f
    {"RES 4, B", 8, reset_b<4>},       // 0xa0
    {"RES 4, C", 8, reset_c<4>},       // 0xa1
    {"RES 4, D", 8, reset_d<4>},       // 0xa2
    {"RES 4, E", 8, reset_e<4>},       // 0xa3
    {"RES 4, H", 8, reset_h<4>},       // 0xa4
    {"RES 4, L", 8, reset_l<4>},       // 0xa5
    {"RES 4, (HL)", 12, reset_hlp<4>}, // 0xa6
    {"RES 4, A", 8, reset_a<4>},       // 0xa7
    {"RES 5, B", 8, reset_b<5>},       // 0xa8
    {"RES 5, C", 8, reset_c<5>},       // 0xa9
    {"RES 5, D", 8, reset_d<5>},       // 0xaa
    {"RES 5, E", 8, reset_e<5>},       // 0xab
    {"RES 5, H", 8, reset_h<5>},       // 0xac
    {"RES 5, L", 8, reset_l<5>},       // 0xad
    {"RES 5, (HL)", 12, reset_hlp<5>}, // 0xae
    {"RES 5, A", 8, reset_a<5>},       // 0xaf
    {"RES 6, B", 8, reset_b<6>},       // 0xb0
    {"RES 6, C", 8, reset_c<6>},       // 0xb1
    {"RES 6, D", 8, reset_d<6>},       // 0xb2
    {"RES 6, E", 8, reset_e<6>},       // 0xb3
    {"RES 6, H", 8, reset_h<6>},       // 0xb4
    {"RES 6, L", 8, reset_l<6>},       // 0xb5
    {"RES 6, (HL)", 12, reset_hlp<6>}, // 0xb6
    {"RES 6, A", 8, reset_a<6>},       // 0xb7
    {"RES 7, B", 8, reset_b<7>},       // 0xb8
    {"RES 7, C", 8, reset_c<7>},       // 0xb9
    {"RES 7, D", 8, reset_d<7>},       // 0xba
    {"RES 7, E", 8, reset_e<7>},       // 0xbb
    {"RES 7, H", 8, reset_h<7>},       // 0xbc
    {"RES 7, L", 8, reset_l<7>},       // 0xbd
    {"RES 7, (HL)", 12, reset_hlp<7>}, // 0xbe
    {"RES 7, A", 8, reset_a<7>},       // 0xbf
    {"SET 0, B", 8, set_b<0>},         // 0xc0
    {"SET 0, C", 8, set_c<0>},         // 0xc1
    {"SET 0, D", 8, set_d<0>},         // 0xc2
    {"SET 0, E", 8, set_e<0>},         // 0xc3
    {"SET 0, H", 8, set_h<0>},         // 0xc4
    {"SET 0, L", 8, set_l<0>},         // 0xc5
    {"SET 0, (HL)", 12, set_hlp<0>},   // 0xc6
    {"SET 0, A", 8, set_a<0>},         // 0xc7
    {"SET 1, B", 8, set_b<1>},         // 0xc8
    {"SET 1, C", 8, set_c<1>},         // 0xc9
    {"SET 1, D", 8, set_d<1>},         // 0xca
    {"SET 1, E", 8, set_e<1>},         // 0xcb
    {"SET 1, H", 8, set_h<1>},         // 0xcc
    {"SET 1, L", 8, set_l<1>},         // 0xcd
    {"SET 1, (HL)", 12, set_hlp<2>},   // 0xce
    {"SET 1, A", 8, set_a<1>},         // 0xcf
    {"SET 2, B", 8, set_b<2>},         // 0xd0
    {"SET 2, C", 8, set_c<2>},         // 0xd1
    {"SET 2, D", 8, set_d<2>},         // 0xd2
    {"SET 2, E", 8, set_e<2>},         // 0xd3
    {"SET 2, H", 8, set_h<2>},         // 0xd4
    {"SET 2, L", 8, set_l<2>},         // 0xd5
    {"SET 2, (HL)", 12, set_hlp<2>},   // 0xd6
    {"SET 2, A", 8, set_a<2>},         // 0xd7
    {"SET 3, B", 8, set_b<3>},         // 0xd8
    {"SET 3, C", 8, set_c<3>},         // 0xd9
    {"SET 3, D", 8, set_d<3>},         // 0xda
    {"SET 3, E", 8, set_e<3>},         // 0xdb
    {"SET 3, H", 8, set_h<3>},         // 0xdc
    {"SET 3, L", 8, set_l<3>},         // 0xdd
    {"SET 3, (HL)", 12, set_hlp<3>},   // 0xde
    {"SET 3, A", 8, set_a<3>},         // 0xdf
    {"SET 4, B", 8, set_b<4>},         // 0xe0
    {"SET 4, C", 8, set_c<4>},         // 0xe1
    {"SET 4, D", 8, set_d<4>},         // 0xe2
    {"SET 4, E", 8, set_e<4>},         // 0xe3
    {"SET 4, H", 8, set_h<4>},         // 0xe4
    {"SET 4, L", 8, set_l<4>},         // 0xe5
    {"SET 4, (HL)", 12, set_hlp<4>},   // 0xe6
    {"SET 4, A", 8, set_a<4>},         // 0xe7
    {"SET 5, B", 8, set_b<5>},         // 0xe8
    {"SET 5, C", 8, set_c<5>},         // 0xe9
    {"SET 5, D", 8, set_d<5>},         // 0xea
    {"SET 5, E", 8, set_e<5>},         // 0xeb
    {"SET 5, H", 8, set_h<5>},         // 0xec
    {"SET 5, L", 8, set_l<5>},         // 0xed
    {"SET 5, (HL)", 12, set_hlp<5>},   // 0xee
    {"SET 5, A", 8, set_a<5>},         // 0xef
    {"SET 6, B", 8, set_b<6>},         // 0xf0
    {"SET 6, C", 8, set_c<6>},         // 0xf1
    {"SET 6, D", 8, set_d<6>},         // 0xf2
    {"SET 6, E", 8, set_e<6>},         // 0xf3
    {"SET 6, H", 8, set_h<6>},         // 0xf4
    {"SET 6, L", 8, set_l<6>},         // 0xf5
    {"SET 6, (HL)", 12, set_hlp<6>},   // 0xf6
    {"SET 6, A", 8, set_a<6>},         // 0xf7
    {"SET 7, B", 8, set_b<7>},         // 0xf8
    {"SET 7, C", 8, set_c<7>},         // 0xf9
    {"SET 7, D", 8, set_d<7>},         // 0xfa
    {"SET 7, E", 8, set_e<7>},         // 0xfb
    {"SET 7, H", 8, set_h<7>},         // 0xfc
    {"SET 7, L", 8, set_l<7>},         // 0xfd
    {"SET 7, (HL)", 12, set_hlp<7>},   // 0xfe
    {"SET 7, A", 8, set_a<7>},         // 0xff
};
