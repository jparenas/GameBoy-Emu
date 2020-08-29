#pragma once

#define IE_POSITION 0xFFFF
#define IF_POSITION 0xFF0F

#define INTERRUPT_VBLANK (1 << 0)
#define INTERRUPT_STAT (1 << 1)
#define INTERRUPT_TIMER (1 << 2)
#define INTERRUPT_SERIAL (1 << 3)
#define INTERRUPT_JOYPAD (1 << 4)

#define INTERRUPT_VBLANK_INSTRUCTION 0x40
#define INTERRUPT_STAT_INSTRUCTION 0x48
#define INTERRUPT_TIMER_INSTRUCTION 0x50
#define INTERRUPT_SERIAL_INSTRUCTION 0x58
#define INTERRUPT_JOYPAD_INSTRUCTION 0x60

#include <bitset>
#include <cstdint>
#include <string>

#include "controls.h"
#include "memory.h"

struct Flags
{
  uint8_t _0 : 4;
  bool c : 1;
  bool h : 1;
  bool n : 1;
  bool z : 1;
};

struct Registrers
{
  struct
  {
    union {
      struct
      {
        Flags f;
        uint8_t a;
      };
      uint16_t af;
    };
  };

  struct
  {
    union {
      struct
      {
        uint8_t c;
        uint8_t b;
      };
      uint16_t bc;
    };
  };

  struct
  {
    union {
      struct
      {
        uint8_t e;
        uint8_t d;
      };
      uint16_t de;
    };
  };

  struct
  {
    union {
      struct
      {
        uint8_t l;
        uint8_t h;
      };
      uint16_t hl;
    };
  };

  uint16_t sp;
  uint16_t pc;

  bool ime;
};

struct CPU
{
  CPU(Memory *memory, unsigned long *ticks) : memory(memory), ticks(ticks)
  {
    this->registrers.a = 0x01;
    this->registrers.f.z = 1;
    this->registrers.f.h = 1;
    this->registrers.f.c = 1;
    this->registrers.f.n = 0;
    this->registrers.bc = 0x0013;
    this->registrers.de = 0x00D8;
    this->registrers.hl = 0x014D;
    this->registrers.pc = 0x100;
    this->registrers.sp = 0xFFFE;

    this->registrers.ime = 0x0;

    this->interrupt_enable = this->memory->read_raw_byte(IE_POSITION);
    this->interrupt_flags = this->memory->read_raw_byte(IF_POSITION);
  };

  void register_interrupt(uint8_t flag);

  Registrers registrers;
  unsigned long *ticks;

  Memory *memory;

  uint8_t *interrupt_enable;
  uint8_t *interrupt_flags;
};

inline std::ostream &operator<<(std::ostream &o, const Registrers &r)
{
  o << std::hex << "AF: 0x" << r.af << std::endl;
  o << std::hex << "BC: 0x" << r.bc << std::endl;
  o << std::hex << "DE: 0x" << r.de << std::endl;
  o << std::hex << "HL: 0x" << r.hl << std::endl;
  o << std::hex << "PC: 0x" << r.pc << std::endl;
  o << std::hex << "SP: 0x" << r.sp << std::endl;
  o << std::hex << "Z:" << r.f.z << " N:" << r.f.n << " H:" << r.f.h << " C:" << r.f.c << std::endl;
  o << std::hex << "IME: 0x" << (int)r.ime << std::endl;
  return o;
}

inline std::ostream &operator<<(std::ostream &o, const CPU &cpu)
{
  o << cpu.registrers;
  o << std::dec << "IE: 0b" << std::bitset<8>(*(cpu.interrupt_enable)) << std::endl;
  o << std::dec << "IF: 0b" << std::bitset<8>(*(cpu.interrupt_flags)) << std::endl;
  o << std::dec << "Ticks: " << *(cpu.ticks) << std::endl;
  return o;
}
