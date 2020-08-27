#include <iostream>

#include "gameboy.h"
#include "ops.h"

bool GameBoy::executeInstruction()
{
  uint8_t instruction_code = this->memory.read_byte(this->cpu.registrers.pc++);
  Instruction instruction = instruction_set[instruction_code];
#ifdef PRINT_INSTRUCTIONS
  if (this->debugging)
  {
    std::cout << "Tick: " << std::dec << this->ticks << " Executing: 0x" << std::hex << this->cpu.registrers.pc - 1 << " Instruction: 0x" << std::hex << (int)instruction_code << " (" << instruction.name << ") Operands: ";
  }
#endif
  Operands operands(instruction.size);
  if (operands.size > 0)
  {
    for (uint8_t i = 0; i < operands.size; i++)
    {
      operands.values[i] = this->memory.read_byte(this->cpu.registrers.pc++);
    }
#ifdef PRINT_INSTRUCTIONS
    if (this->debugging)
    {
      for (uint8_t i = 0; i < operands.size; i++)
      {
        std::cout << "0x" << std::hex << (int)operands.values[i] << " ";
      }
    }
#endif
  }
#ifdef PRINT_INSTRUCTIONS
  if (this->debugging)
  {
    std::cout << std::endl;
  }
#endif

  if (instruction.execute != NULL)
  {
    if (instruction.ticks == 0 && instruction_code != 0xCB)
    {
      std::cout << "Invalid ticks for instruction 0x" << std::hex << (int)instruction_code << std::endl;
      return false;
    }
    instruction.execute(*this, operands);
    this->ticks += instruction.ticks;
  }
  else
  {
    std::cout << "Unable to execute instruction " << instruction.name << " 0x" << std::hex << (int)instruction_code << std::endl;
    return false;
  }
  this->last_instruction = &(instruction_set[instruction_code]);
  this->last_operands = operands;
  return true;
}

bool GameBoy::executeInterrupts()
{
  if (this->cpu.registrers.ime && *(this->cpu.interrupt_enable) && *(this->cpu.interrupt_flags))
  {
    uint8_t enabled_flags = *(this->cpu.interrupt_enable) & *(this->cpu.interrupt_flags);
    if (enabled_flags)
    {
      this->halted = false;
      if (enabled_flags & INTERRUPT_VBLANK)
      {
        // std::cout << "Calling VBLANK interrupt " << std::endl;
        *(this->cpu.interrupt_flags) &= ~INTERRUPT_VBLANK;
        this->gpu.renderFramebuffer();
        this->cpu.registrers.ime = 0x0;
        write_short_to_stack(*this, this->cpu.registrers.pc);
        this->cpu.registrers.pc = INTERRUPT_VBLANK_INSTRUCTION;
        this->ticks += 12;
      }
      else if (enabled_flags & INTERRUPT_STAT)
      {
        *(this->cpu.interrupt_flags) &= ~INTERRUPT_STAT;
        this->cpu.registrers.ime = 0x0;
        write_short_to_stack(*this, this->cpu.registrers.pc);
        this->cpu.registrers.pc = INTERRUPT_STAT_INSTRUCTION;
        this->ticks += 12;
      }
      else if (enabled_flags & INTERRUPT_TIMER)
      {
        *(this->cpu.interrupt_flags) &= ~INTERRUPT_TIMER;
        this->cpu.registrers.ime = 0x0;
        write_short_to_stack(*this, this->cpu.registrers.pc);
        this->cpu.registrers.pc = INTERRUPT_TIMER_INSTRUCTION;
        this->ticks += 12;
      }
      else if (enabled_flags & INTERRUPT_SERIAL)
      {
        *(this->cpu.interrupt_flags) &= ~INTERRUPT_SERIAL;
        this->cpu.registrers.ime = 0x0;
        write_short_to_stack(*this, this->cpu.registrers.pc);
        this->cpu.registrers.pc = INTERRUPT_SERIAL_INSTRUCTION;
        this->ticks += 12;
      }
      else if (enabled_flags & INTERRUPT_JOYPAD)
      {
        *(this->cpu.interrupt_flags) &= ~INTERRUPT_JOYPAD;
        this->cpu.registrers.ime = 0x0;
        write_short_to_stack(*this, this->cpu.registrers.pc);
        this->cpu.registrers.pc = INTERRUPT_JOYPAD_INSTRUCTION;
        this->ticks += 12;
      }
    }
  }
  return true;
}
