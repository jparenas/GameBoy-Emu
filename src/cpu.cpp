#include <cstdio>
#include <iostream>

#include "cpu.h"

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
