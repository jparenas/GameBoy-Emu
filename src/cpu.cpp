#include <cstdio>
#include <iostream>

#include "cpu.h"

void CPU::register_interrupt(uint8_t flag)
{
  *(this->interrupt_flags) = *(this->interrupt_flags) | flag;
}
