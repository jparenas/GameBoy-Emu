#include <memory>
#include <string>

#include "common_ops.h"
#include "cpu.h"
#include "extended_ops.h"
#include "gameboy.h"
#include "memory.h"
#include "ops_util.h"

void nop(GameBoy &gameboy, Operands &operands)
{
}

void ld_a(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.a = operands.values[0];
}

void ld_b(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.b = operands.values[0];
}

void ld_c(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.c = operands.values[0];
}

void ld_d(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.d = operands.values[0];
}

void ld_e(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.e = operands.values[0];
}

void ld_h(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.h = operands.values[0];
}

void ld_l(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.l = operands.values[0];
}

void ld_hl(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.hl = convert_uint8_to_uint16(operands.values[1], operands.values[0]);
}

void ld_sp(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.sp = convert_uint8_to_uint16(operands.values[1], operands.values[0]);
}

void ld_a_b(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.a = gameboy.cpu.registrers.b;
}

void ld_a_c(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.a = gameboy.cpu.registrers.c;
}

void ld_a_d(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.a = gameboy.cpu.registrers.d;
}

void ld_a_e(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.a = gameboy.cpu.registrers.e;
}

void ld_a_h(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.a = gameboy.cpu.registrers.h;
}

void ld_a_l(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.a = gameboy.cpu.registrers.l;
}

void ld_a_bcp(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.a = gameboy.memory.read_byte(gameboy.cpu.registrers.bc);
}

void ld_a_dep(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.a = gameboy.memory.read_byte(gameboy.cpu.registrers.de);
}

void ld_a_hlp(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.a = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
}

void ld_a_nn(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.a = gameboy.memory.read_byte(convert_uint8_to_uint16(operands.values[1], operands.values[0]));
}

void ld_b_a(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.b = gameboy.cpu.registrers.a;
}

void ld_b_c(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.b = gameboy.cpu.registrers.c;
}

void ld_b_d(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.b = gameboy.cpu.registrers.d;
}

void ld_b_e(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.b = gameboy.cpu.registrers.e;
}

void ld_b_h(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.b = gameboy.cpu.registrers.h;
}

void ld_b_l(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.b = gameboy.cpu.registrers.l;
}

void ld_b_hlp(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.b = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
}

void ld_bcp_a(GameBoy &gameboy, Operands &operands)
{
  gameboy.memory.write_byte(gameboy.cpu.registrers.bc, gameboy.cpu.registrers.a);
}

void ld_c_a(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.c = gameboy.cpu.registrers.a;
}

void ld_c_b(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.c = gameboy.cpu.registrers.b;
}

void ld_c_d(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.c = gameboy.cpu.registrers.d;
}

void ld_c_e(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.c = gameboy.cpu.registrers.e;
}

void ld_c_h(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.c = gameboy.cpu.registrers.h;
}

void ld_c_l(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.c = gameboy.cpu.registrers.l;
}

void ld_c_hlp(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.c = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
}

void ld_d_a(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.d = gameboy.cpu.registrers.a;
}

void ld_d_b(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.d = gameboy.cpu.registrers.b;
}

void ld_d_c(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.d = gameboy.cpu.registrers.c;
}

void ld_d_e(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.d = gameboy.cpu.registrers.e;
}

void ld_d_h(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.d = gameboy.cpu.registrers.h;
}

void ld_d_l(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.d = gameboy.cpu.registrers.l;
}

void ld_d_hlp(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.d = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
}

void ld_de_nnp(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.de = convert_uint8_to_uint16(operands.values[1], operands.values[0]);
}

void ld_dep_a(GameBoy &gameboy, Operands &operands)
{
  gameboy.memory.write_byte(gameboy.cpu.registrers.de, gameboy.cpu.registrers.a);
}

void ld_e_a(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.e = gameboy.cpu.registrers.a;
}

void ld_e_b(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.e = gameboy.cpu.registrers.b;
}

void ld_e_c(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.e = gameboy.cpu.registrers.c;
}

void ld_e_d(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.e = gameboy.cpu.registrers.d;
}

void ld_e_h(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.e = gameboy.cpu.registrers.h;
}

void ld_e_l(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.e = gameboy.cpu.registrers.l;
}

void ld_e_hlp(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.e = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
}

void ld_h_a(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.h = gameboy.cpu.registrers.a;
}

void ld_h_b(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.h = gameboy.cpu.registrers.b;
}

void ld_h_c(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.h = gameboy.cpu.registrers.c;
}

void ld_h_d(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.h = gameboy.cpu.registrers.d;
}

void ld_h_e(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.h = gameboy.cpu.registrers.e;
}

void ld_h_l(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.h = gameboy.cpu.registrers.l;
}

void ld_h_hlp(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.h = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
}

void ld_l_a(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.l = gameboy.cpu.registrers.a;
}

void ld_l_b(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.l = gameboy.cpu.registrers.b;
}

void ld_l_c(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.l = gameboy.cpu.registrers.c;
}

void ld_l_d(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.l = gameboy.cpu.registrers.d;
}

void ld_l_e(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.l = gameboy.cpu.registrers.e;
}

void ld_l_h(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.l = gameboy.cpu.registrers.h;
}

void ld_l_hlp(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.l = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
}

void ld_hl_sp_n(GameBoy &gameboy, Operands &operands)
{
  int8_t value = unsigned_8_to_signed(operands.values[0]);
  int result = static_cast<int>(gameboy.cpu.registrers.sp + value);

  gameboy.cpu.registrers.f.h = ((gameboy.cpu.registrers.sp ^ value ^ (result & 0xFFFF)) & 0x10) == 0x10;
  gameboy.cpu.registrers.f.c = ((gameboy.cpu.registrers.sp ^ value ^ (result & 0xFFFF)) & 0x100) == 0x100;

  gameboy.cpu.registrers.hl = static_cast<uint16_t>(result);

  gameboy.cpu.registrers.f.z = 0;
  gameboy.cpu.registrers.f.n = 0;
}

void ld_hlp_a(GameBoy &gameboy, Operands &operands)
{
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, gameboy.cpu.registrers.a);
}

void ld_hlp_b(GameBoy &gameboy, Operands &operands)
{
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, gameboy.cpu.registrers.b);
}

void ld_hlp_c(GameBoy &gameboy, Operands &operands)
{
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, gameboy.cpu.registrers.c);
}

void ld_hlp_d(GameBoy &gameboy, Operands &operands)
{
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, gameboy.cpu.registrers.d);
}

void ld_hlp_e(GameBoy &gameboy, Operands &operands)
{
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, gameboy.cpu.registrers.e);
}

void ld_hlp_h(GameBoy &gameboy, Operands &operands)
{
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, gameboy.cpu.registrers.h);
}

void ld_hlp_l(GameBoy &gameboy, Operands &operands)
{
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, gameboy.cpu.registrers.l);
}

void ld_hlp_n(GameBoy &gameboy, Operands &operands)
{
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, operands.values[0]);
}

void ld_sp_hl(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.sp = gameboy.cpu.registrers.hl;
}

void ld_a_ff00_c(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.a = gameboy.memory.read_byte(0xFF00 + gameboy.cpu.registrers.c);
}

void ld_ff00_c_a(GameBoy &gameboy, Operands &operands)
{
  gameboy.memory.write_byte(0xFF00 + gameboy.cpu.registrers.c, gameboy.cpu.registrers.a);
}

void ld_bc_nn(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.bc = convert_uint8_to_uint16(operands.values[1], operands.values[0]);
}

void ld_nnp_a(GameBoy &gameboy, Operands &operands)
{
  gameboy.memory.write_byte(convert_uint8_to_uint16(operands.values[1], operands.values[0]), gameboy.cpu.registrers.a);
}

void ld_nn_sp(GameBoy &gameboy, Operands &operands)
{
  gameboy.memory.write_short(convert_uint8_to_uint16(operands.values[1], operands.values[0]), gameboy.cpu.registrers.sp);
}

void ldh_n_a(GameBoy &gameboy, Operands &operands)
{
  gameboy.memory.write_byte(0xFF00 + operands.values[0], gameboy.cpu.registrers.a);
}

void ldh_a_n(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.a = gameboy.memory.read_byte(0xFF00 + operands.values[0]);
}

void ldd_a_hlp(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.a = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  gameboy.cpu.registrers.hl--;
}

void ldd_hl_a(GameBoy &gameboy, Operands &operands)
{
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, gameboy.cpu.registrers.a);
  gameboy.cpu.registrers.hl--;
}

void ldi_a_hlp(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.a = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  gameboy.cpu.registrers.hl++;
}

void ldi_hl_a(GameBoy &gameboy, Operands &operands)
{
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, gameboy.cpu.registrers.a);
  gameboy.cpu.registrers.hl++;
}

void push_af(GameBoy &gameboy, Operands &operands)
{
  write_short_to_stack(gameboy, gameboy.cpu.registrers.af);
}

void push_bc(GameBoy &gameboy, Operands &operands)
{
  write_short_to_stack(gameboy, gameboy.cpu.registrers.bc);
}

void push_de(GameBoy &gameboy, Operands &operands)
{
  write_short_to_stack(gameboy, gameboy.cpu.registrers.de);
}

void push_hl(GameBoy &gameboy, Operands &operands)
{
  write_short_to_stack(gameboy, gameboy.cpu.registrers.hl);
}

void call(GameBoy &gameboy, Operands &operands)
{
  write_short_to_stack(gameboy, gameboy.cpu.registrers.pc);
  gameboy.cpu.registrers.pc = convert_uint8_to_uint16(operands.values[1], operands.values[0]);
}

void call_nc(GameBoy &gameboy, Operands &operands)
{
  if (gameboy.cpu.registrers.f.c == 0)
  {
    gameboy.ticks += 3;
    write_short_to_stack(gameboy, gameboy.cpu.registrers.pc);
    gameboy.cpu.registrers.pc = convert_uint8_to_uint16(operands.values[1], operands.values[0]);
  }
}

void call_c(GameBoy &gameboy, Operands &operands)
{
  if (gameboy.cpu.registrers.f.c)
  {
    gameboy.ticks += 3;
    write_short_to_stack(gameboy, gameboy.cpu.registrers.pc);
    gameboy.cpu.registrers.pc = convert_uint8_to_uint16(operands.values[1], operands.values[0]);
  }
}

void call_nz(GameBoy &gameboy, Operands &operands)
{
  if (gameboy.cpu.registrers.f.z == 0)
  {
    gameboy.ticks += 3;
    write_short_to_stack(gameboy, gameboy.cpu.registrers.pc);
    gameboy.cpu.registrers.pc = convert_uint8_to_uint16(operands.values[1], operands.values[0]);
  }
}

void call_z(GameBoy &gameboy, Operands &operands)
{
  if (gameboy.cpu.registrers.f.z)
  {
    gameboy.ticks += 3;
    write_short_to_stack(gameboy, gameboy.cpu.registrers.pc);
    gameboy.cpu.registrers.pc = convert_uint8_to_uint16(operands.values[1], operands.values[0]);
  }
}

void ret(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.pc = pop_short_from_stack(gameboy);
}

void reti(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.pc = pop_short_from_stack(gameboy);
  gameboy.cpu.registrers.ime = true;
}

void ret_nz(GameBoy &gameboy, Operands &operands)
{
  if (gameboy.cpu.registrers.f.z == 0)
  {
    gameboy.ticks += 3;
    gameboy.cpu.registrers.pc = pop_short_from_stack(gameboy);
  }
}

void ret_z(GameBoy &gameboy, Operands &operands)
{
  if (gameboy.cpu.registrers.f.z)
  {
    gameboy.ticks += 3;
    gameboy.cpu.registrers.pc = pop_short_from_stack(gameboy);
  }
}

void ret_nc(GameBoy &gameboy, Operands &operands)
{
  if (gameboy.cpu.registrers.f.c == 0)
  {
    gameboy.ticks += 3;
    gameboy.cpu.registrers.pc = pop_short_from_stack(gameboy);
  }
}

void ret_c(GameBoy &gameboy, Operands &operands)
{
  if (gameboy.cpu.registrers.f.c)
  {
    gameboy.ticks += 3;
    gameboy.cpu.registrers.pc = pop_short_from_stack(gameboy);
  }
}

void pop_af(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.af = pop_short_from_stack(gameboy);
  gameboy.cpu.registrers.f._0 = 0; // Zero out unneeded flags from register
}

void pop_bc(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.bc = pop_short_from_stack(gameboy);
}

void pop_de(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.de = pop_short_from_stack(gameboy);
}

void pop_hl(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.hl = pop_short_from_stack(gameboy);
}

void rlca(GameBoy &gameboy, Operands &operands)
{
  rlc(gameboy, gameboy.cpu.registrers.a);
  gameboy.cpu.registrers.f.z = 0;
}

void rla(GameBoy &gameboy, Operands &operands)
{
  rl(gameboy, gameboy.cpu.registrers.a);
  gameboy.cpu.registrers.f.z = 0;
}

void rrca(GameBoy &gameboy, Operands &operands)
{
  rrc(gameboy, gameboy.cpu.registrers.a);
  gameboy.cpu.registrers.f.z = 0;
}

void rra(GameBoy &gameboy, Operands &operands)
{
  rr(gameboy, gameboy.cpu.registrers.a);
  gameboy.cpu.registrers.f.z = 0;
}

void cp_base(GameBoy &gameboy, uint8_t value)
{
  if (gameboy.cpu.registrers.a == value)
  {
    gameboy.cpu.registrers.f.z = 1;
    gameboy.cpu.registrers.f.c = 0;
  }
  else if (gameboy.cpu.registrers.a < value)
  {
    gameboy.cpu.registrers.f.z = 0;
    gameboy.cpu.registrers.f.c = 1;
  }
  else
  {
    gameboy.cpu.registrers.f.z = 0;
    gameboy.cpu.registrers.f.c = 0;
  }

  if ((value & 0x0f) > (gameboy.cpu.registrers.a & 0x0f))
  {
    gameboy.cpu.registrers.f.h = 1;
  }
  else
  {
    gameboy.cpu.registrers.f.h = 0;
  }

  gameboy.cpu.registrers.f.n = 1;
}

void cp_a(GameBoy &gameboy, Operands &operands)
{
  cp_base(gameboy, gameboy.cpu.registrers.a);
}

void cp_b(GameBoy &gameboy, Operands &operands)
{
  cp_base(gameboy, gameboy.cpu.registrers.b);
}

void cp_c(GameBoy &gameboy, Operands &operands)
{
  cp_base(gameboy, gameboy.cpu.registrers.c);
}

void cp_d(GameBoy &gameboy, Operands &operands)
{
  cp_base(gameboy, gameboy.cpu.registrers.d);
}

void cp_e(GameBoy &gameboy, Operands &operands)
{
  cp_base(gameboy, gameboy.cpu.registrers.e);
}

void cp_h(GameBoy &gameboy, Operands &operands)
{
  cp_base(gameboy, gameboy.cpu.registrers.h);
}

void cp_l(GameBoy &gameboy, Operands &operands)
{
  cp_base(gameboy, gameboy.cpu.registrers.l);
}

void cp_hlp(GameBoy &gameboy, Operands &operands)
{
  cp_base(gameboy, gameboy.memory.read_byte(gameboy.cpu.registrers.hl));
}

void cp_n(GameBoy &gameboy, Operands &operands)
{
  cp_base(gameboy, operands.values[0]);
}

void inc_base(GameBoy &gameboy, uint8_t &value)
{
  value++;
  if (value == 0)
  {
    gameboy.cpu.registrers.f.z = 1;
  }
  else
  {
    gameboy.cpu.registrers.f.z = 0;
  }
  if (value & 0x0f) // If (value & 0x0f) == 0, then the bit was carried
  {
    gameboy.cpu.registrers.f.h = 0;
  }
  else
  {
    gameboy.cpu.registrers.f.h = 1;
  }

  gameboy.cpu.registrers.f.n = 0;
}

void inc_a(GameBoy &gameboy, Operands &operands)
{
  inc_base(gameboy, gameboy.cpu.registrers.a);
}

void inc_b(GameBoy &gameboy, Operands &operands)
{
  inc_base(gameboy, gameboy.cpu.registrers.b);
}

void inc_c(GameBoy &gameboy, Operands &operands)
{
  inc_base(gameboy, gameboy.cpu.registrers.c);
}

void inc_d(GameBoy &gameboy, Operands &operands)
{
  inc_base(gameboy, gameboy.cpu.registrers.d);
}

void inc_e(GameBoy &gameboy, Operands &operands)
{
  inc_base(gameboy, gameboy.cpu.registrers.e);
}

void inc_h(GameBoy &gameboy, Operands &operands)
{
  inc_base(gameboy, gameboy.cpu.registrers.h);
}

void inc_l(GameBoy &gameboy, Operands &operands)
{
  inc_base(gameboy, gameboy.cpu.registrers.l);
}

void inc_hlp(GameBoy &gameboy, Operands &operands)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  inc_base(gameboy, value);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void inc_bc(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.bc++;
}

void inc_de(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.de++;
}

void inc_hl(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.hl++;
}

void inc_sp(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.sp++;
}

void dec_base(GameBoy &gameboy, uint8_t &value)
{
  value--;
  if (value == 0)
  {
    gameboy.cpu.registrers.f.z = 1;
  }
  else
  {
    gameboy.cpu.registrers.f.z = 0;
  }

  if ((value & 0x0f) == 0x0f)
  {
    gameboy.cpu.registrers.f.h = 1;
  }
  else
  {
    gameboy.cpu.registrers.f.h = 0;
  }

  gameboy.cpu.registrers.f.n = 1;
}

void dec_a(GameBoy &gameboy, Operands &operands)
{
  dec_base(gameboy, gameboy.cpu.registrers.a);
}

void dec_b(GameBoy &gameboy, Operands &operands)
{
  dec_base(gameboy, gameboy.cpu.registrers.b);
}

void dec_c(GameBoy &gameboy, Operands &operands)
{
  dec_base(gameboy, gameboy.cpu.registrers.c);
}

void dec_d(GameBoy &gameboy, Operands &operands)
{
  dec_base(gameboy, gameboy.cpu.registrers.d);
}

void dec_e(GameBoy &gameboy, Operands &operands)
{
  dec_base(gameboy, gameboy.cpu.registrers.e);
}

void dec_h(GameBoy &gameboy, Operands &operands)
{
  dec_base(gameboy, gameboy.cpu.registrers.h);
}

void dec_l(GameBoy &gameboy, Operands &operands)
{
  dec_base(gameboy, gameboy.cpu.registrers.l);
}

void dec_hlp(GameBoy &gameboy, Operands &operands)
{
  uint8_t value = gameboy.memory.read_byte(gameboy.cpu.registrers.hl);
  dec_base(gameboy, value);
  gameboy.memory.write_byte(gameboy.cpu.registrers.hl, value);
}

void dec_bc(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.bc--;
}

void dec_de(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.de--;
}

void dec_hl(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.hl--;
}

void dec_sp(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.sp--;
}

void add_base(GameBoy &gameboy, uint8_t value)
{
  uint16_t result = static_cast<uint16_t>(static_cast<uint16_t>(gameboy.cpu.registrers.a) + value);

  gameboy.cpu.registrers.f.z = (result & 0xFF) == 0;
  gameboy.cpu.registrers.f.c = result & 0xFF00;
  gameboy.cpu.registrers.f.h = (gameboy.cpu.registrers.a & 0x0F) + (value & 0x0F) > 0x0F;
  gameboy.cpu.registrers.f.n = 0;

  gameboy.cpu.registrers.a = static_cast<uint8_t>(result & 0xFF);
}

void add_a_a(GameBoy &gameboy, Operands &operands)
{
  add_base(gameboy, gameboy.cpu.registrers.a);
}

void add_a_b(GameBoy &gameboy, Operands &operands)
{
  add_base(gameboy, gameboy.cpu.registrers.b);
}

void add_a_c(GameBoy &gameboy, Operands &operands)
{
  add_base(gameboy, gameboy.cpu.registrers.c);
}

void add_a_d(GameBoy &gameboy, Operands &operands)
{
  add_base(gameboy, gameboy.cpu.registrers.d);
}

void add_a_e(GameBoy &gameboy, Operands &operands)
{
  add_base(gameboy, gameboy.cpu.registrers.e);
}

void add_a_h(GameBoy &gameboy, Operands &operands)
{
  add_base(gameboy, gameboy.cpu.registrers.h);
}

void add_a_l(GameBoy &gameboy, Operands &operands)
{
  add_base(gameboy, gameboy.cpu.registrers.l);
}

void add_a_hl(GameBoy &gameboy, Operands &operands)
{
  add_base(gameboy, gameboy.memory.read_byte(gameboy.cpu.registrers.hl));
}

void add_a_n(GameBoy &gameboy, Operands &operands)
{
  add_base(gameboy, operands.values[0]);
}

void add_sp_n(GameBoy &gameboy, Operands &operands)
{
  int8_t value = unsigned_8_to_signed(operands.values[0]);
  int result = static_cast<int>(gameboy.cpu.registrers.sp + value);

  gameboy.cpu.registrers.f.h = ((gameboy.cpu.registrers.sp ^ value ^ (result & 0xFFFF)) & 0x10) == 0x10;
  gameboy.cpu.registrers.f.c = ((gameboy.cpu.registrers.sp ^ value ^ (result & 0xFFFF)) & 0x100) == 0x100;

  gameboy.cpu.registrers.sp = static_cast<uint16_t>(result);

  gameboy.cpu.registrers.f.z = 0;
  gameboy.cpu.registrers.f.n = 0;
}

void add_16bit_base(GameBoy &gameboy, uint16_t &source, uint16_t value)
{
  uint32_t result = (uint32_t)source + value;

  if (result & 0xFFFF0000)
  {
    gameboy.cpu.registrers.f.c = 1;
  }
  else
  {
    gameboy.cpu.registrers.f.c = 0;
  }

  if ((source & 0x0FFF) + (value & 0x0FFF) > 0x0FFF)
  {
    gameboy.cpu.registrers.f.h = 1;
  }
  else
  {
    gameboy.cpu.registrers.f.h = 0;
  }

  source = (uint16_t)result;

  gameboy.cpu.registrers.f.n = 0;
}

void add_hl_hl(GameBoy &gameboy, Operands &operands)
{
  add_16bit_base(gameboy, gameboy.cpu.registrers.hl, gameboy.cpu.registrers.hl);
}

void add_hl_bc(GameBoy &gameboy, Operands &operands)
{
  add_16bit_base(gameboy, gameboy.cpu.registrers.hl, gameboy.cpu.registrers.bc);
}

void add_hl_de(GameBoy &gameboy, Operands &operands)
{
  add_16bit_base(gameboy, gameboy.cpu.registrers.hl, gameboy.cpu.registrers.de);
}

void add_hl_sp(GameBoy &gameboy, Operands &operands)
{
  add_16bit_base(gameboy, gameboy.cpu.registrers.hl, gameboy.cpu.registrers.sp);
}

void adc_base(GameBoy &gameboy, uint8_t value)
{
  bool carry_flag = gameboy.cpu.registrers.f.c;
  uint16_t result = static_cast<uint16_t>(static_cast<uint16_t>(gameboy.cpu.registrers.a) + value + carry_flag);

  gameboy.cpu.registrers.f.z = (result & 0xFF) == 0;
  gameboy.cpu.registrers.f.c = result & 0xFF00;
  gameboy.cpu.registrers.f.h = ((gameboy.cpu.registrers.a & 0x0F) + (value & 0x0F) + carry_flag) > 0x0F;
  gameboy.cpu.registrers.f.n = 0;

  gameboy.cpu.registrers.a = static_cast<uint8_t>(result & 0xFF);
}

void adc_a(GameBoy &gameboy, Operands &operands)
{
  adc_base(gameboy, gameboy.cpu.registrers.a);
}

void adc_b(GameBoy &gameboy, Operands &operands)
{
  adc_base(gameboy, gameboy.cpu.registrers.b);
}

void adc_c(GameBoy &gameboy, Operands &operands)
{
  adc_base(gameboy, gameboy.cpu.registrers.c);
}

void adc_d(GameBoy &gameboy, Operands &operands)
{
  adc_base(gameboy, gameboy.cpu.registrers.d);
}

void adc_e(GameBoy &gameboy, Operands &operands)
{
  adc_base(gameboy, gameboy.cpu.registrers.e);
}

void adc_h(GameBoy &gameboy, Operands &operands)
{
  adc_base(gameboy, gameboy.cpu.registrers.h);
}

void adc_l(GameBoy &gameboy, Operands &operands)
{
  adc_base(gameboy, gameboy.cpu.registrers.l);
}

void adc_hlp(GameBoy &gameboy, Operands &operands)
{
  adc_base(gameboy, gameboy.memory.read_byte(gameboy.cpu.registrers.hl));
}

void adc_n(GameBoy &gameboy, Operands &operands)
{
  adc_base(gameboy, operands.values[0]);
}

void sub_base(GameBoy &gameboy, uint8_t value)
{
  gameboy.cpu.registrers.f.h = (value & 0x0F) > (gameboy.cpu.registrers.a & 0x0F);
  gameboy.cpu.registrers.f.c = value > gameboy.cpu.registrers.a;

  gameboy.cpu.registrers.a -= value;

  gameboy.cpu.registrers.f.z = gameboy.cpu.registrers.a == 0;
  gameboy.cpu.registrers.f.n = 1;
}

void sub_a(GameBoy &gameboy, Operands &operands)
{
  sub_base(gameboy, gameboy.cpu.registrers.a);
}

void sub_b(GameBoy &gameboy, Operands &operands)
{
  sub_base(gameboy, gameboy.cpu.registrers.b);
}

void sub_c(GameBoy &gameboy, Operands &operands)
{
  sub_base(gameboy, gameboy.cpu.registrers.c);
}

void sub_d(GameBoy &gameboy, Operands &operands)
{
  sub_base(gameboy, gameboy.cpu.registrers.d);
}

void sub_e(GameBoy &gameboy, Operands &operands)
{
  sub_base(gameboy, gameboy.cpu.registrers.e);
}

void sub_h(GameBoy &gameboy, Operands &operands)
{
  sub_base(gameboy, gameboy.cpu.registrers.h);
}

void sub_l(GameBoy &gameboy, Operands &operands)
{
  sub_base(gameboy, gameboy.cpu.registrers.l);
}

void sub_hlp(GameBoy &gameboy, Operands &operands)
{
  sub_base(gameboy, gameboy.memory.read_byte(gameboy.cpu.registrers.hl));
}

void sub_n(GameBoy &gameboy, Operands &operands)
{
  sub_base(gameboy, operands.values[0]);
}

void sbc_base(GameBoy &gameboy, uint8_t value)
{
  uint8_t carry_flag = gameboy.cpu.registrers.f.c;
  gameboy.cpu.registrers.f.h = (value & 0x0F) + carry_flag > (gameboy.cpu.registrers.a & 0x0F);
  gameboy.cpu.registrers.f.c = value + carry_flag > gameboy.cpu.registrers.a;

  gameboy.cpu.registrers.a -= value + carry_flag;

  gameboy.cpu.registrers.f.z = gameboy.cpu.registrers.a == 0;
  gameboy.cpu.registrers.f.n = 1;
}

void sbc_a(GameBoy &gameboy, Operands &operands)
{
  sbc_base(gameboy, gameboy.cpu.registrers.a);
}

void sbc_b(GameBoy &gameboy, Operands &operands)
{
  sbc_base(gameboy, gameboy.cpu.registrers.b);
}

void sbc_c(GameBoy &gameboy, Operands &operands)
{
  sbc_base(gameboy, gameboy.cpu.registrers.c);
}

void sbc_d(GameBoy &gameboy, Operands &operands)
{
  sbc_base(gameboy, gameboy.cpu.registrers.d);
}

void sbc_e(GameBoy &gameboy, Operands &operands)
{
  sbc_base(gameboy, gameboy.cpu.registrers.e);
}

void sbc_h(GameBoy &gameboy, Operands &operands)
{
  sbc_base(gameboy, gameboy.cpu.registrers.h);
}

void sbc_l(GameBoy &gameboy, Operands &operands)
{
  sbc_base(gameboy, gameboy.cpu.registrers.l);
}

void sbc_hlp(GameBoy &gameboy, Operands &operands)
{
  sbc_base(gameboy, gameboy.memory.read_byte(gameboy.cpu.registrers.hl));
}

void sbc_n(GameBoy &gameboy, Operands &operands)
{
  sbc_base(gameboy, operands.values[0]);
}

void jr_n(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.pc += unsigned_8_to_signed(operands.values[0]);
}

void jr_nz(GameBoy &gameboy, Operands &operands)
{
  if (gameboy.cpu.registrers.f.z == 0)
  {
    gameboy.ticks += 1;
    gameboy.cpu.registrers.pc += unsigned_8_to_signed(operands.values[0]);
  }
}

void jr_z(GameBoy &gameboy, Operands &operands)
{
  if (gameboy.cpu.registrers.f.z)
  {
    gameboy.ticks += 1;
    gameboy.cpu.registrers.pc += unsigned_8_to_signed(operands.values[0]);
  }
}

void jr_nc(GameBoy &gameboy, Operands &operands)
{
  if (gameboy.cpu.registrers.f.c == 0)
  {
    gameboy.ticks += 1;
    gameboy.cpu.registrers.pc += unsigned_8_to_signed(operands.values[0]);
  }
}

void jr_c(GameBoy &gameboy, Operands &operands)
{
  if (gameboy.cpu.registrers.f.c)
  {
    gameboy.ticks += 1;
    gameboy.cpu.registrers.pc += unsigned_8_to_signed(operands.values[0]);
  }
}

void jp_nn(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.pc = convert_uint8_to_uint16(operands.values[1], operands.values[0]);
}

void jp_hl(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.pc = gameboy.cpu.registrers.hl;
}

void jp_nz(GameBoy &gameboy, Operands &operands)
{
  if (gameboy.cpu.registrers.f.z == 0)
  {
    gameboy.ticks += 1;
    gameboy.cpu.registrers.pc = convert_uint8_to_uint16(operands.values[1], operands.values[0]);
  }
}

void jp_z(GameBoy &gameboy, Operands &operands)
{
  if (gameboy.cpu.registrers.f.z)
  {
    gameboy.ticks += 1;
    gameboy.cpu.registrers.pc = convert_uint8_to_uint16(operands.values[1], operands.values[0]);
  }
}

void jp_nc(GameBoy &gameboy, Operands &operands)
{
  if (gameboy.cpu.registrers.f.c == 0)
  {
    gameboy.ticks += 1;
    gameboy.cpu.registrers.pc = convert_uint8_to_uint16(operands.values[1], operands.values[0]);
  }
}

void and_base(GameBoy &gameboy, uint8_t value)
{
  gameboy.cpu.registrers.a = value & gameboy.cpu.registrers.a;
  if (gameboy.cpu.registrers.a == 0)
  {
    gameboy.cpu.registrers.f.z = 1;
  }
  else
  {
    gameboy.cpu.registrers.f.z = 0;
  }
  gameboy.cpu.registrers.f.n = 0;
  gameboy.cpu.registrers.f.h = 1;
  gameboy.cpu.registrers.f.c = 0;
}

void and_a(GameBoy &gameboy, Operands &operands)
{
  and_base(gameboy, gameboy.cpu.registrers.a);
}

void and_b(GameBoy &gameboy, Operands &operands)
{
  and_base(gameboy, gameboy.cpu.registrers.b);
}

void and_c(GameBoy &gameboy, Operands &operands)
{
  and_base(gameboy, gameboy.cpu.registrers.c);
}

void and_d(GameBoy &gameboy, Operands &operands)
{
  and_base(gameboy, gameboy.cpu.registrers.d);
}

void and_e(GameBoy &gameboy, Operands &operands)
{
  and_base(gameboy, gameboy.cpu.registrers.e);
}

void and_h(GameBoy &gameboy, Operands &operands)
{
  and_base(gameboy, gameboy.cpu.registrers.h);
}

void and_l(GameBoy &gameboy, Operands &operands)
{
  and_base(gameboy, gameboy.cpu.registrers.l);
}

void and_hlp(GameBoy &gameboy, Operands &operands)
{
  and_base(gameboy, gameboy.memory.read_byte(gameboy.cpu.registrers.hl));
}

void and_n(GameBoy &gameboy, Operands &operands)
{
  and_base(gameboy, operands.values[0]);
}

void or_base(GameBoy &gameboy, uint8_t value)
{
  gameboy.cpu.registrers.a = value | gameboy.cpu.registrers.a;
  if (gameboy.cpu.registrers.a == 0)
  {
    gameboy.cpu.registrers.f.z = 1;
  }
  else
  {
    gameboy.cpu.registrers.f.z = 0;
  }
  gameboy.cpu.registrers.f.n = 0;
  gameboy.cpu.registrers.f.h = 0;
  gameboy.cpu.registrers.f.c = 0;
}

void or_a(GameBoy &gameboy, Operands &operands)
{
  or_base(gameboy, gameboy.cpu.registrers.a);
}

void or_b(GameBoy &gameboy, Operands &operands)
{
  or_base(gameboy, gameboy.cpu.registrers.b);
}

void or_c(GameBoy &gameboy, Operands &operands)
{
  or_base(gameboy, gameboy.cpu.registrers.c);
}

void or_d(GameBoy &gameboy, Operands &operands)
{
  or_base(gameboy, gameboy.cpu.registrers.d);
}

void or_e(GameBoy &gameboy, Operands &operands)
{
  or_base(gameboy, gameboy.cpu.registrers.e);
}

void or_h(GameBoy &gameboy, Operands &operands)
{
  or_base(gameboy, gameboy.cpu.registrers.h);
}

void or_l(GameBoy &gameboy, Operands &operands)
{
  or_base(gameboy, gameboy.cpu.registrers.l);
}

void or_hlp(GameBoy &gameboy, Operands &operands)
{
  or_base(gameboy, gameboy.memory.read_byte(gameboy.cpu.registrers.hl));
}

void or_n(GameBoy &gameboy, Operands &operands)
{
  or_base(gameboy, operands.values[0]);
}

void xor_base(GameBoy &gameboy, uint8_t value)
{
  gameboy.cpu.registrers.a = value ^ gameboy.cpu.registrers.a;
  if (gameboy.cpu.registrers.a == 0)
  {
    gameboy.cpu.registrers.f.z = 1;
  }
  else
  {
    gameboy.cpu.registrers.f.z = 0;
  }
  gameboy.cpu.registrers.f.n = 0;
  gameboy.cpu.registrers.f.h = 0;
  gameboy.cpu.registrers.f.c = 0;
}

void xor_a(GameBoy &gameboy, Operands &operands)
{
  xor_base(gameboy, gameboy.cpu.registrers.a);
}

void xor_b(GameBoy &gameboy, Operands &operands)
{
  xor_base(gameboy, gameboy.cpu.registrers.b);
}

void xor_c(GameBoy &gameboy, Operands &operands)
{
  xor_base(gameboy, gameboy.cpu.registrers.c);
}

void xor_d(GameBoy &gameboy, Operands &operands)
{
  xor_base(gameboy, gameboy.cpu.registrers.d);
}

void xor_e(GameBoy &gameboy, Operands &operands)
{
  xor_base(gameboy, gameboy.cpu.registrers.e);
}

void xor_h(GameBoy &gameboy, Operands &operands)
{
  xor_base(gameboy, gameboy.cpu.registrers.h);
}

void xor_l(GameBoy &gameboy, Operands &operands)
{
  xor_base(gameboy, gameboy.cpu.registrers.l);
}

void xor_hlp(GameBoy &gameboy, Operands &operands)
{
  xor_base(gameboy, gameboy.memory.read_byte(gameboy.cpu.registrers.hl));
}

void xor_n(GameBoy &gameboy, Operands &operands)
{
  xor_base(gameboy, operands.values[0]);
}

void ccf(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.f.c = !gameboy.cpu.registrers.f.c;
  gameboy.cpu.registrers.f.n = 0;
  gameboy.cpu.registrers.f.h = 0;
}

void scf(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.f.c = 1;
  gameboy.cpu.registrers.f.n = 0;
  gameboy.cpu.registrers.f.h = 0;
}

void rst_0x00(GameBoy &gameboy, Operands &operands)
{
  write_short_to_stack(gameboy, gameboy.cpu.registrers.pc);
  gameboy.cpu.registrers.pc = 0x00;
}

void rst_0x08(GameBoy &gameboy, Operands &operands)
{
  write_short_to_stack(gameboy, gameboy.cpu.registrers.pc);
  gameboy.cpu.registrers.pc = 0x08;
}

void rst_0x10(GameBoy &gameboy, Operands &operands)
{
  write_short_to_stack(gameboy, gameboy.cpu.registrers.pc);
  gameboy.cpu.registrers.pc = 0x10;
}

void rst_0x18(GameBoy &gameboy, Operands &operands)
{
  write_short_to_stack(gameboy, gameboy.cpu.registrers.pc);
  gameboy.cpu.registrers.pc = 0x18;
}

void rst_0x20(GameBoy &gameboy, Operands &operands)
{
  write_short_to_stack(gameboy, gameboy.cpu.registrers.pc);
  gameboy.cpu.registrers.pc = 0x20;
}

void rst_0x28(GameBoy &gameboy, Operands &operands)
{
  write_short_to_stack(gameboy, gameboy.cpu.registrers.pc);
  gameboy.cpu.registrers.pc = 0x28;
}

void rst_0x30(GameBoy &gameboy, Operands &operands)
{
  write_short_to_stack(gameboy, gameboy.cpu.registrers.pc);
  gameboy.cpu.registrers.pc = 0x30;
}

void rst_0x38(GameBoy &gameboy, Operands &operands)
{
  write_short_to_stack(gameboy, gameboy.cpu.registrers.pc);
  gameboy.cpu.registrers.pc = 0x38;
}

// https://worldofspectrum.org/faq/reference/z80reference.htm#DAA
void daa(GameBoy &gameboy, Operands &operands)
{
  /*
  uint8_t correction_factor = 0x00;
  if (gameboy.cpu.registrers.a > 0x99 || gameboy.cpu.registrers.f.c)
  {
    correction_factor |= 0x60;
    gameboy.cpu.registrers.f.c = 1;
  }
  else
  {
    gameboy.cpu.registrers.f.c = 0;
  }

  if ((gameboy.cpu.registrers.a & 0x0F) > 0x09 || gameboy.cpu.registrers.f.h)
  {
    correction_factor |= 0x06;
  }

  if (!gameboy.cpu.registrers.f.n)
  {
    gameboy.cpu.registrers.a += correction_factor;
  }
  else
  {
    gameboy.cpu.registrers.a -= correction_factor;
  }

  if (gameboy.cpu.registrers.a == 0)
  {
    gameboy.cpu.registrers.f.z = 1;
  }
  else
  {
    gameboy.cpu.registrers.f.z = 0;
  }
  */
  uint16_t value = static_cast<uint16_t>(operands.values[0]);
  if (gameboy.cpu.registrers.f.n)
  {
    if (gameboy.cpu.registrers.f.c || value > 0x99)
    {
      value += 0x60;
      gameboy.cpu.registrers.f.c = true;
    }
    if (gameboy.cpu.registrers.f.h || (value & 0x0F) > 0x09)
    {
      value += 0x06;
    }
  }
  else
  {
    if (gameboy.cpu.registrers.f.h)
    {
      value -= 0x06;
    }
    if (gameboy.cpu.registrers.f.c)
    {
      value -= 0x60;
      gameboy.cpu.registrers.f.c = true;
    }
  }
  gameboy.cpu.registrers.f.z = value == 0;
  gameboy.cpu.registrers.f.h = 0;
  gameboy.cpu.registrers.a = static_cast<uint8_t>(value & 0xFF);
}

void cpl(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.a = ~gameboy.cpu.registrers.a;
  gameboy.cpu.registrers.f.n = 1;
  gameboy.cpu.registrers.f.h = 1;
}

void cb(GameBoy &gameboy, Operands &operands)
{
  ExtendedInstruction instruction = extended_instruction_set[operands.values[0]];
  gameboy.ticks += instruction.ticks;
  if (instruction.execute != NULL)
  {
    instruction.execute(gameboy);
  }
  else
  {
    std::cout << "Unimplemented instruction: " << (int)operands.values[0] << " " << instruction.name << std::endl;
    exit(1);
  }
}

void di(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.ime = false;
}

void ei(GameBoy &gameboy, Operands &operands)
{
  gameboy.cpu.registrers.ime = true;
}

void stop(GameBoy &gameboy, Operands &operands)
{
  gameboy.running = false;
}

void halt(GameBoy &gameboy, Operands &operands)
{
  if (gameboy.cpu.registrers.ime)
  {
    gameboy.halted = true;
  }
  else
  {
    gameboy.cpu.registrers.pc += 1;
  }
}

const Instruction instruction_set[256] = {
    {"NOP", 0, 1, nop},                         // 0x00
    {"LD BC, 0x%04X", 2, 3, ld_bc_nn},          // 0x01
    {"LD (BC), A", 0, 2, ld_bcp_a},             // 0x02
    {"INC BC", 0, 2, inc_bc},                   // 0x03
    {"INC B", 0, 1, inc_b},                     // 0x04
    {"DEC B", 0, 1, dec_b},                     // 0x05
    {"LD B, 0x%02X", 1, 2, ld_b},               // 0x06
    {"RLCA", 0, 1, rlca},                       // 0x07
    {"LD (0x%04X), SP", 2, 5, ld_nn_sp},        // 0x08
    {"ADD HL, BC", 0, 2, add_hl_bc},            // 0x09
    {"LD A, (BC)", 0, 2, ld_a_bcp},             // 0x0a
    {"DEC BC", 0, 2, dec_bc},                   // 0x0b
    {"INC C", 0, 1, inc_c},                     // 0x0c
    {"DEC C", 0, 1, dec_c},                     // 0x0d
    {"LD C, 0x%02X", 1, 2, ld_c},               // 0x0e
    {"RRCA", 0, 1, rrca},                       // 0x0f
    {"STOP", 1, 1, stop},                       // 0x10
    {"LD DE, 0x%04X", 2, 3, ld_de_nnp},         // 0x11
    {"LD (DE), A", 0, 2, ld_dep_a},             // 0x12
    {"INC DE", 0, 2, inc_de},                   // 0x13
    {"INC D", 0, 1, inc_d},                     // 0x14
    {"DEC D", 0, 1, dec_d},                     // 0x15
    {"LD D, 0x%02X", 1, 2, ld_d},               // 0x16
    {"RLA", 0, 1, rla},                         // 0x17
    {"JR %.hhd", 1, 2, jr_n},                   // 0x18
    {"ADD HL, DE", 0, 2, add_hl_de},            // 0x19
    {"LD A, (DE)", 0, 2, ld_a_dep},             // 0x1a
    {"DEC DE", 0, 2, dec_de},                   // 0x1b
    {"INC E", 0, 1, inc_e},                     // 0x1c
    {"DEC E", 0, 1, dec_e},                     // 0x1d
    {"LD E, 0x%02X", 1, 2, ld_e},               // 0x1e
    {"RRA", 0, 1, rra},                         // 0x1f
    {"JR NZ, %.hhd", 1, 2, jr_nz},              // 0x20
    {"LD HL, 0x%04X", 2, 3, ld_hl},             // 0x21
    {"LDI (HL), A", 0, 2, ldi_hl_a},            // 0x22
    {"INC HL", 0, 2, inc_hl},                   // 0x23
    {"INC H", 0, 1, inc_h},                     // 0x24
    {"DEC H", 0, 1, dec_h},                     // 0x25
    {"LD H, 0x%02X", 1, 2, ld_h},               // 0x26
    {"DAA", 0, 1, daa},                         // 0x27
    {"JR Z, %.hhd", 1, 2, jr_z},                // 0x28
    {"ADD HL, HL", 0, 2, add_hl_hl},            // 0x29
    {"LDI A, (HL)", 0, 2, ldi_a_hlp},           // 0x2a
    {"DEC HL", 0, 2, dec_hl},                   // 0x2b
    {"INC L", 0, 1, inc_l},                     // 0x2c
    {"DEC L", 0, 1, dec_l},                     // 0x2d
    {"LD L, 0x%02X", 1, 2, ld_l},               // 0x2e
    {"CPL", 0, 1, cpl},                         // 0x2f
    {"JR NC, %.hhd", 1, 2, jr_nc},              // 0x30
    {"LD SP, 0x%04X", 2, 3, ld_sp},             // 0x31
    {"LDD (HL), A", 0, 2, ldd_hl_a},            // 0x32
    {"INC SP", 0, 2, inc_sp},                   // 0x33
    {"INC (HL)", 0, 3, inc_hlp},                // 0x34
    {"DEC (HL)", 0, 3, dec_hlp},                // 0x35
    {"LD (HL), 0x%02X", 1, 3, ld_hlp_n},        // 0x36
    {"SCF", 0, 1, scf},                         // 0x37
    {"JR C, %.hhd", 1, 2, jr_c},                // 0x38
    {"ADD HL, SP", 0, 2, add_hl_sp},            // 0x39
    {"LDD A, (HL)", 0, 2, ldd_a_hlp},           // 0x3a
    {"DEC SP", 0, 2, dec_sp},                   // 0x3b
    {"INC A", 0, 1, inc_a},                     // 0x3c
    {"DEC A", 0, 1, dec_a},                     // 0x3d
    {"LD A, 0x%02X", 1, 2, ld_a},               // 0x3e
    {"CCF", 0, 1, ccf},                         // 0x3f
    {"LD B, B", 0, 1, nop},                     // 0x40
    {"LD B, C", 0, 1, ld_b_c},                  // 0x41
    {"LD B, D", 0, 1, ld_b_d},                  // 0x42
    {"LD B, E", 0, 1, ld_b_e},                  // 0x43
    {"LD B, H", 0, 1, ld_b_h},                  // 0x44
    {"LD B, L", 0, 1, ld_b_l},                  // 0x45
    {"LD B, (HL)", 0, 2, ld_b_hlp},             // 0x46
    {"LD B, A", 0, 1, ld_b_a},                  // 0x47
    {"LD C, B", 0, 1, ld_c_b},                  // 0x48
    {"LD C, C", 0, 1, nop},                     // 0x49
    {"LD C, D", 0, 1, ld_c_d},                  // 0x4a
    {"LD C, E", 0, 1, ld_c_e},                  // 0x4b
    {"LD C, H", 0, 1, ld_c_h},                  // 0x4c
    {"LD C, L", 0, 1, ld_c_l},                  // 0x4d
    {"LD C, (HL)", 0, 2, ld_c_hlp},             // 0x4e
    {"LD C, A", 0, 1, ld_c_a},                  // 0x4f
    {"LD D, B", 0, 1, ld_d_b},                  // 0x50
    {"LD D, C", 0, 1, ld_d_c},                  // 0x51
    {"LD D, D", 0, 1, nop},                     // 0x52
    {"LD D, E", 0, 1, ld_d_e},                  // 0x53
    {"LD D, H", 0, 1, ld_d_h},                  // 0x54
    {"LD D, L", 0, 1, ld_d_l},                  // 0x55
    {"LD D, (HL)", 0, 2, ld_d_hlp},             // 0x56
    {"LD D, A", 0, 1, ld_d_a},                  // 0x57
    {"LD E, B", 0, 1, ld_e_b},                  // 0x58
    {"LD E, C", 0, 1, ld_e_c},                  // 0x59
    {"LD E, D", 0, 1, ld_e_d},                  // 0x5a
    {"LD E, E", 0, 1, nop},                     // 0x5b
    {"LD E, H", 0, 1, ld_e_h},                  // 0x5c
    {"LD E, L", 0, 1, ld_e_l},                  // 0x5d
    {"LD E, (HL)", 0, 2, ld_e_hlp},             // 0x5e
    {"LD E, A", 0, 1, ld_e_a},                  // 0x5f
    {"LD H, B", 0, 1, ld_h_b},                  // 0x60
    {"LD H, C", 0, 1, ld_h_c},                  // 0x61
    {"LD H, D", 0, 1, ld_h_d},                  // 0x62
    {"LD H, E", 0, 1, ld_h_e},                  // 0x63
    {"LD H, H", 0, 1, nop},                     // 0x64
    {"LD H, L", 0, 1, ld_h_l},                  // 0x65
    {"LD H, (HL)", 0, 2, ld_h_hlp},             // 0x66
    {"LD H, A", 0, 1, ld_h_a},                  // 0x67
    {"LD L, B", 0, 1, ld_l_b},                  // 0x68
    {"LD L, C", 0, 1, ld_l_c},                  // 0x69
    {"LD L, D", 0, 1, ld_l_d},                  // 0x6a
    {"LD L, E", 0, 1, ld_l_e},                  // 0x6b
    {"LD L, H", 0, 1, ld_l_h},                  // 0x6c
    {"LD L, L", 0, 1, nop},                     // 0x6d
    {"LD L, (HL)", 0, 2, ld_l_hlp},             // 0x6e
    {"LD L, A", 0, 1, ld_l_a},                  // 0x6f
    {"LD (HL), B", 0, 2, ld_hlp_b},             // 0x70
    {"LD (HL), C", 0, 2, ld_hlp_c},             // 0x71
    {"LD (HL), D", 0, 2, ld_hlp_d},             // 0x72
    {"LD (HL), E", 0, 2, ld_hlp_e},             // 0x73
    {"LD (HL), H", 0, 2, ld_hlp_h},             // 0x74
    {"LD (HL), L", 0, 2, ld_hlp_l},             // 0x75
    {"HALT", 0, 1, halt},                       // 0x76
    {"LD (HL), A", 0, 2, ld_hlp_a},             // 0x77
    {"LD A, B", 0, 1, ld_a_b},                  // 0x78
    {"LD A, C", 0, 1, ld_a_c},                  // 0x79
    {"LD A, D", 0, 1, ld_a_d},                  // 0x7a
    {"LD A, E", 0, 1, ld_a_e},                  // 0x7b
    {"LD A, H", 0, 1, ld_a_h},                  // 0x7c
    {"LD A, L", 0, 1, ld_a_l},                  // 0x7d
    {"LD A, (HL)", 0, 2, ld_a_hlp},             // 0x7e
    {"LD A, A", 0, 1, nop},                     // 0x7f
    {"ADD A, B", 0, 1, add_a_b},                // 0x80
    {"ADD A, C", 0, 1, add_a_c},                // 0x81
    {"ADD A, D", 0, 1, add_a_d},                // 0x82
    {"ADD A, E", 0, 1, add_a_e},                // 0x83
    {"ADD A, H", 0, 1, add_a_h},                // 0x84
    {"ADD A, L", 0, 1, add_a_l},                // 0x85
    {"ADD A, (HL)", 0, 2, add_a_hl},            // 0x86
    {"ADD A", 0, 1, add_a_a},                   // 0x87
    {"ADC B", 0, 1, adc_b},                     // 0x88
    {"ADC C", 0, 1, adc_c},                     // 0x89
    {"ADC D", 0, 1, adc_d},                     // 0x8a
    {"ADC E", 0, 1, adc_e},                     // 0x8b
    {"ADC H", 0, 1, adc_h},                     // 0x8c
    {"ADC L", 0, 1, adc_l},                     // 0x8d
    {"ADC (HL)", 0, 2, adc_hlp},                // 0x8e
    {"ADC A", 0, 1, adc_a},                     // 0x8f
    {"SUB B", 0, 1, sub_b},                     // 0x90
    {"SUB C", 0, 1, sub_c},                     // 0x91
    {"SUB D", 0, 1, sub_d},                     // 0x92
    {"SUB E", 0, 1, sub_e},                     // 0x93
    {"SUB H", 0, 1, sub_h},                     // 0x94
    {"SUB L", 0, 1, sub_l},                     // 0x95
    {"SUB (HL)", 0, 2, sub_hlp},                // 0x96
    {"SUB A", 0, 1, sub_a},                     // 0x97
    {"SBC B", 0, 1, sbc_b},                     // 0x98
    {"SBC C", 0, 1, sbc_c},                     // 0x99
    {"SBC D", 0, 1, sbc_d},                     // 0x9a
    {"SBC E", 0, 1, sbc_e},                     // 0x9b
    {"SBC H", 0, 1, sbc_h},                     // 0x9c
    {"SBC L", 0, 1, sbc_l},                     // 0x9d
    {"SBC (HL)", 0, 2, sbc_hlp},                // 0x9e
    {"SBC A", 0, 1, sbc_a},                     // 0x9f
    {"AND B", 0, 1, and_b},                     // 0xa0
    {"AND C", 0, 1, and_c},                     // 0xa1
    {"AND D", 0, 1, and_d},                     // 0xa2
    {"AND E", 0, 1, and_e},                     // 0xa3
    {"AND H", 0, 1, and_h},                     // 0xa4
    {"AND L", 0, 1, and_l},                     // 0xa5
    {"AND (HL)", 0, 2, and_hlp},                // 0xa6
    {"AND A", 0, 1, and_a},                     // 0xa7
    {"XOR B", 0, 1, xor_b},                     // 0xa8
    {"XOR C", 0, 1, xor_c},                     // 0xa9
    {"XOR D", 0, 1, xor_d},                     // 0xaa
    {"XOR E", 0, 1, xor_e},                     // 0xab
    {"XOR H", 0, 1, xor_h},                     // 0xac
    {"XOR L", 0, 1, xor_l},                     // 0xad
    {"XOR (HL)", 0, 2, xor_hlp},                // 0xae
    {"XOR A", 0, 1, xor_a},                     // 0xaf
    {"OR B", 0, 1, or_b},                       // 0xb0
    {"OR C", 0, 1, or_c},                       // 0xb1
    {"OR D", 0, 1, or_d},                       // 0xb2
    {"OR E", 0, 1, or_e},                       // 0xb3
    {"OR H", 0, 1, or_h},                       // 0xb4
    {"OR L", 0, 1, or_l},                       // 0xb5
    {"OR (HL)", 0, 2, or_hlp},                  // 0xb6
    {"OR A", 0, 1, or_a},                       // 0xb7
    {"CP B", 0, 1, cp_b},                       // 0xb8
    {"CP C", 0, 1, cp_c},                       // 0xb9
    {"CP D", 0, 1, cp_d},                       // 0xba
    {"CP E", 0, 1, cp_e},                       // 0xbb
    {"CP H", 0, 1, cp_h},                       // 0xbc
    {"CP L", 0, 1, cp_l},                       // 0xbd
    {"CP (HL)", 0, 2, cp_hlp},                  // 0xbe
    {"CP A", 0, 1, cp_a},                       // 0xbf
    {"RET NZ", 0, 2, ret_nz},                   // 0xc0
    {"POP BC", 0, 3, pop_bc},                   // 0xc1
    {"JP NZ, 0x%04X", 2, 3, jp_nz},             // 0xc2
    {"JP 0x%04X", 2, 4, jp_nn},                 // 0xc3
    {"CALL NZ, 0x%04X", 2, 3, call_nz},         // 0xc4
    {"PUSH BC", 0, 4, push_bc},                 // 0xc5
    {"ADD A, 0x%02X", 1, 2, add_a_n},           // 0xc6
    {"RST 0x00", 0, 8, rst_0x00},               // 0xc7
    {"RET Z", 0, 2, ret_z},                     // 0xc8
    {"RET", 0, 4, ret},                         // 0xc9
    {"JP Z, 0x%04X", 2, 3, jp_z},               // 0xca
    {"CB %02X", 1, 0, cb},                      // 0xcb
    {"CALL Z, 0x%04X", 2, 3, call_z},           // 0xcc
    {"CALL 0x%04X", 2, 3, call},                // 0xcd
    {"ADC 0x%02X", 1, 2, adc_n},                // 0xce
    {"RST 0x08", 0, 8, rst_0x08},               // 0xcf
    {"RET NC", 0, 2, ret_nc},                   // 0xd0
    {"POP DE", 0, 3, pop_de},                   // 0xd1
    {"JP NC, 0x%04X", 2, 3, jp_nc},             // 0xd2
    {"UNKNOWN", 0, 0, NULL},                    // 0xd3
    {"CALL NC, 0x%04X", 2, 3, call_nc},         // 0xd4
    {"PUSH DE", 0, 4, push_de},                 // 0xd5
    {"SUB 0x%02X", 1, 2, sub_n},                // 0xd6
    {"RST 0x10", 0, 8, rst_0x10},               // 0xd7
    {"RET C", 0, 2, ret_c},                     // 0xd8
    {"RETI", 0, 4, reti},                       // 0xd9
    {"JP C, 0x%04X", 2, 0, NULL},               // 0xda
    {"UNKNOWN", 0, 0, NULL},                    // 0xdb
    {"CALL C, 0x%04X", 2, 3, call_c},           // 0xdc
    {"UNKNOWN", 0, 0, NULL},                    // 0xdd
    {"SBC 0x%02X", 1, 2, sbc_n},                // 0xde
    {"RST 0x18", 0, 8, rst_0x18},               // 0xdf
    {"LD (0xFF00 + 0x%02X), A", 1, 3, ldh_n_a}, // 0xe0
    {"POP HL", 0, 3, pop_hl},                   // 0xe1
    {"LD (0xFF00 + C), A", 0, 2, ld_ff00_c_a},  // 0xe2
    {"UNKNOWN", 0, 0, NULL},                    // 0xe3
    {"UNKNOWN", 0, 0, NULL},                    // 0xe4
    {"PUSH HL", 0, 4, push_hl},                 // 0xe5
    {"AND 0x%02X", 1, 2, and_n},                // 0xe6
    {"RST 0x20", 0, 8, rst_0x20},               // 0xe7
    {"ADD SP, %.hhd", 1, 4, add_sp_n},          // 0xe8
    {"JP HL", 0, 1, jp_hl},                     // 0xe9
    {"LD (0x%04X), A", 2, 4, ld_nnp_a},         // 0xea
    {"UNKNOWN", 0, 0, NULL},                    // 0xeb
    {"UNKNOWN", 0, 0, NULL},                    // 0xec
    {"UNKNOWN", 0, 0, NULL},                    // 0xed
    {"XOR 0x%02X", 1, 2, xor_n},                // 0xee
    {"RST 0x28", 0, 8, rst_0x28},               // 0xef
    {"LD A, (0xFF00 + 0x%02X)", 1, 3, ldh_a_n}, // 0xf0
    {"POP AF", 0, 3, pop_af},                   // 0xf1
    {"LD A, (0xFF00 + C)", 0, 2, ld_a_ff00_c},  // 0xf2
    {"DI", 0, 1, di},                           // 0xf3
    {"UNKNOWN", 0, 0, NULL},                    // 0xf4
    {"PUSH AF", 0, 4, push_af},                 // 0xf5
    {"OR 0x%02X", 1, 2, or_n},                  // 0xf6
    {"RST 0x30", 0, 8, rst_0x30},               // 0xf7
    {"LD HL, SP+%.hhd", 1, 3, ld_hl_sp_n},      // 0xf8
    {"LD SP, HL", 0, 2, ld_sp_hl},              // 0xf9
    {"LD A, (0x%04X)", 2, 4, ld_a_nn},          // 0xfa
    {"EI", 0, 1, ei},                           // 0xfb
    {"UNKNOWN", 0, 0, NULL},                    // 0xfc
    {"UNKNOWN", 0, 0, NULL},                    // 0xfd
    {"CP 0x%02X", 1, 2, cp_n},                  // 0xfe
    {"RST 0x38", 0, 8, rst_0x38},               // 0xff
};
