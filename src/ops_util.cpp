#include "ops_util.h"
#include "extended_ops.h"

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

std::string format_instruction(uint8_t instruction_code, const Operands &operands)
{
  char buffer[20];
  const Instruction instruction = instruction_set[instruction_code];
  if (instruction_code == 0xCB)
  {
    sprintf(buffer, instruction.name.c_str(), extended_instruction_set[operands.values[0]].name.c_str());
  }
  else if (instruction.size == 0)
  {
    sprintf(buffer, "%s", instruction.name.c_str());
  }
  else if (instruction.size == 1)
  {
    sprintf(buffer, instruction.name.c_str(), operands.values[0]);
  }
  else if (instruction.size == 2)
  {
    sprintf(buffer, instruction.name.c_str(), convert_uint8_to_uint16(operands.values[1], operands.values[0]));
  }
  return std::string(buffer);
}
