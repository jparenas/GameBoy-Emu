#pragma once

#define OPS_PER_SEC 1050000

#define DIV_REGISTER_LOCATION 0xFF04
#define DIV_REGISTER_UPDATE_FREQUENCY 16384
#define DIV_REGISTER_UPDATE_TICKS OPS_PER_SEC / DIV_REGISTER_UPDATE_FREQUENCY

// #define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
#define PRINT_INSTRUCTIONS
#define PRINT_CPU_REGISTRERS
//#define PRINT_GPU_REGISTRERS
#endif

#include <string>

#include <SDL.h>

#include "controls.h"
#include "cpu.h"
#include "gpu.h"
#include "memory.h"

struct GameBoy
{
  GameBoy(std::string filename) : memory(filename, &keys), cpu(&this->memory, &this->ticks), gpu(&this->memory, &this->ticks, &this->cpu)
  {
    this->keys.p14.pad_bool = 0x00;
    this->keys.p15.pad_bool = 0X00;

    this->memory.write_byte(DIV_REGISTER_LOCATION, 0x00);
    this->div_register = this->memory.read_raw_byte(DIV_REGISTER_LOCATION);

    this->rom_title = this->memory.get_rom_title();
  }

  ~GameBoy()
  {
    std::cout << this->cpu;
  }

  Memory memory;
  CPU cpu;
  GPU gpu;

  uint8_t *div_register;

  Keys keys;

  std::string rom_title;

  bool halted = false;
  bool running = true;

#ifdef ENABLE_DEBUG
  bool debugging = true;
#endif

  unsigned long ticks = 0;
  unsigned long last_ticks = 0;
  unsigned long last_check_ticks = 0;

  void runTick()
  {
    if (this->ticks / DIV_REGISTER_UPDATE_TICKS != this->last_ticks / DIV_REGISTER_UPDATE_TICKS)
    {
      (*(this->div_register))++;
    }
    this->last_ticks = this->ticks;

    // CPU
    if (!this->halted)
    {
      if (!this->executeInstruction())
      {
        exit(1);
      }
    }
    else
    {
      // Avoid the program from locking up
      this->ticks += 1;
    }

#ifdef PRINT_CPU_REGISTRERS
    if (this->debugging)
    {
      std::cout << this->cpu;
    }
#endif

    // GPU
    this->executeGPU();
#ifdef PRINT_GPU_REGISTRERS
    std::cout << this->gpu;
#endif
    this->executeInterrupts();
  }

  void handleEvent(SDL_Event &event)
  {
    if (event.type == SDL_QUIT)
    {
      this->running = false;
    }
    else if (event.type == SDL_KEYDOWN || SDL_KEYUP)
    {
      bool p14_change, p15_change;
      p14_change = false;
      p15_change = false;
      switch (event.key.keysym.sym)
      {
      case SDLK_UP:
        this->keys.p14.up = event.key.state == SDL_RELEASED ? 0 : 1;
        p14_change = true;
        break;
      case SDLK_DOWN:
        this->keys.p14.down = event.key.state == SDL_RELEASED ? 0 : 1;
        p14_change = true;
        break;
      case SDLK_RIGHT:
        this->keys.p14.right = event.key.state == SDL_RELEASED ? 0 : 1;
        p14_change = true;
        break;
      case SDLK_LEFT:
        this->keys.p14.left = event.key.state == SDL_RELEASED ? 0 : 1;
        p14_change = true;
        break;
      case SDLK_w:
        this->keys.p15.a = event.key.state == SDL_RELEASED ? 0 : 1;
        p15_change = true;
        break;
      case SDLK_s:
        this->keys.p15.b = event.key.state == SDL_RELEASED ? 0 : 1;
        p15_change = true;
        break;
      case SDLK_n:
        this->keys.p15.start = event.key.state == SDL_RELEASED ? 0 : 1;
        p15_change = true;
        break;
      case SDLK_m:
        this->keys.p15.select = event.key.state == SDL_RELEASED ? 0 : 1;
        p15_change = true;
        break;
      case SDLK_ESCAPE:
        this->running = false;
        break;
      default:
        break;
      }

      p14_change = this->memory.read_byte(JOYPAD_LOCATION) >> 4 != p14_change;
      p15_change = this->memory.read_byte(JOYPAD_LOCATION) >> 5 != p15_change;

      if (p14_change || p15_change)
      {
        if (this->cpu.registrers.ime && *(this->cpu.interrupt_enable) & INTERRUPT_JOYPAD)
        {
          *(this->cpu.interrupt_flags) |= INTERRUPT_JOYPAD;
        }
      }
    }
  }

  bool executeInstruction();
  bool executeGPU()
  {
    return this->gpu.executeGPU();
  }
  bool executeInterrupts();
};
