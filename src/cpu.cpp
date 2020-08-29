#include <cstdio>
#include <iostream>

#include "cpu.h"

void CPU::register_interrupt(uint8_t flag)
{
  if (this->registrers.ime && *(this->interrupt_enable) & flag)
  {
    *(this->interrupt_flags) |= flag;
  }
}
