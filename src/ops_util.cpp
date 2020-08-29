#include "ops_util.h"

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

std::string format_instruction(const Instruction &instruction, const Operands &operands)
{
  char buffer[20];
  if (instruction.size == 0)
  {
    sprintf(buffer, "%s", instruction.name.c_str());
  }
  else if (instruction.size == 1)
  {
    sprintf(buffer, "%s 0x%02X", instruction.name.c_str(), operands.values[0]);
  }
  else if (instruction.size == 2)
  {
    sprintf(buffer, "%s 0x%02X%02X", instruction.name.c_str(), operands.values[1], operands.values[0]);
  }
  return std::string(buffer);
}
