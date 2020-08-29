#pragma once

#define OPS_PER_SEC 1050000

#define DIV_REGISTER_UPDATE_FREQUENCY 16384
#define DIV_REGISTER_UPDATE_TICKS (OPS_PER_SEC / DIV_REGISTER_UPDATE_FREQUENCY)

#define BREAKPOINTS_BUFFER_LENGTH 5

// #define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
#define PRINT_INSTRUCTIONS
#define PRINT_CPU_REGISTRERS
//#define PRINT_GPU_REGISTRERS
#endif

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "imgui.h"
#include <imgui_memory_editor/imgui_memory_editor.h>

#include <SDL.h>

#include "controls.h"
#include "cpu.h"
#include "gpu.h"
#include "memory.h"
#include "ops.h"
#include "util.h"

const int timer_ticks[] = {
    OPS_PER_SEC / 4096 /*Hz*/,
    OPS_PER_SEC / 262144 /*Hz*/,
    OPS_PER_SEC / 65536 /*Hz*/,
    OPS_PER_SEC / 16384 /*Hz*/
};

enum class BreakpointType
{
  PC,
  MEMORY,
  INSTRUCTION
};

extern const std::unordered_map<BreakpointType, std::string> breakpoint_type_to_string;

struct BreakpointMemoryActionType
{
  bool read = false;
  bool write = false;
};

struct Breakpoint
{
  uint16_t address;
  BreakpointType type;
  BreakpointMemoryActionType memory_action;
};

extern GameBoy *current_gameboy_to_use;

ImU8 read_memory_data(const ImU8 *data, size_t offset);
void write_memory_data(ImU8 *data, size_t offset, ImU8 data_to_write);
bool highlight_memory_data(const ImU8 *data, size_t offset);

struct GameBoy
{
  GameBoy(std::string filename);

  Memory memory;
  CPU cpu;
  GPU gpu;

  MemoryEditor memory_editor;

  uint8_t *div_register;
  uint8_t *tima_register;

  int16_t timer_counter;

  Keys keys;

  std::string rom_title;
  std::string gameboy_title;

  bool halted = false;
  bool running = true;
  bool debugging = false;
  bool step = false;

  unsigned long ticks = 0;
  unsigned long last_ticks = 0;
  unsigned long last_check_ticks = 0;

  uint8_t last_instruction_code = 0;
  Operands last_operands;

  std::unordered_map<BreakpointType, std::map<uint16_t, Breakpoint>> breakpoints;
  Breakpoint *breakpoint_trigger = NULL;

  // GUI related variables
  bool breakpoints_window = false;
  char breakpoint_pc_input_buffer[BREAKPOINTS_BUFFER_LENGTH];
  char breakpoint_memory_input_buffer[BREAKPOINTS_BUFFER_LENGTH];

  bool breakpoint_memory_read = true;
  bool breakpoint_memory_write = false;

  void runTick()
  {
    unsigned long ticks_elapsed = this->ticks - this->last_ticks;
    if (this->ticks / DIV_REGISTER_UPDATE_TICKS != this->last_ticks / DIV_REGISTER_UPDATE_TICKS)
    {
      (*(this->div_register))++;
    }
    if ((this->memory.read_byte(TAC_REGISTER_POSITION, false) & 0b00000100) >> 2) // Timers enabled
    {
      this->timer_counter -= ticks_elapsed;
      if (this->timer_counter <= 0)
      {
        // Reset Timer Counter
        this->timer_counter = timer_ticks[(this->memory.read_byte(TAC_REGISTER_POSITION, false) & 0b00000011, false)] + this->timer_counter;
        if (*(this->tima_register) == 255)
        {
          // Set TIMER interrupt
          this->cpu.register_interrupt(INTERRUPT_TIMER);
          *(this->tima_register) = this->memory.read_byte(TMA_REGISTER_POSITION);
        }
        else
        {
          (*(this->tima_register))++;
        }
      }
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
    ticks_elapsed = this->ticks - this->last_ticks;
    this->executeGPU(ticks_elapsed);
#ifdef PRINT_GPU_REGISTRERS
    std::cout << this->gpu;
#endif
    this->executeInterrupts();
  }

  void handleEvent(SDL_Event &event)
  {
    if (event.type == SDL_KEYDOWN || SDL_KEYUP)
    {
      bool p14_change, p15_change;
      p14_change = false;
      p15_change = false;
      switch (event.key.keysym.sym)
      {
      case SDLK_UP:
        this->keys.p14.up = event.key.state == SDL_RELEASED ? 0 : 1;
        p14_change = this->keys.p14.up;
        break;
      case SDLK_DOWN:
        this->keys.p14.down = event.key.state == SDL_RELEASED ? 0 : 1;
        p14_change = this->keys.p14.down;
        break;
      case SDLK_RIGHT:
        this->keys.p14.right = event.key.state == SDL_RELEASED ? 0 : 1;
        p14_change = this->keys.p14.right;
        break;
      case SDLK_LEFT:
        this->keys.p14.left = event.key.state == SDL_RELEASED ? 0 : 1;
        p14_change = this->keys.p14.left;
        break;
      case SDLK_w:
        this->keys.p15.a = event.key.state == SDL_RELEASED ? 0 : 1;
        p15_change = this->keys.p15.a;
        break;
      case SDLK_s:
        this->keys.p15.b = event.key.state == SDL_RELEASED ? 0 : 1;
        p15_change = this->keys.p15.b;
        break;
      case SDLK_n:
        this->keys.p15.start = event.key.state == SDL_RELEASED ? 0 : 1;
        p15_change = this->keys.p15.start;
        break;
      case SDLK_m:
        this->keys.p15.select = event.key.state == SDL_RELEASED ? 0 : 1;
        p15_change = this->keys.p15.select;
        break;
      /*
      case SDLK_ESCAPE:
        std::cout << "Got ESC Key, shutting down GB" << std::endl;
        this->running = false;
        break;
        */
      default:
        break;
      }

      p14_change = this->memory.read_byte(JOYPAD_LOCATION, false) >> 4 != p14_change;
      p15_change = this->memory.read_byte(JOYPAD_LOCATION, false) >> 5 != p15_change;

      if (p14_change || p15_change)
      {
        this->cpu.register_interrupt(INTERRUPT_JOYPAD);
      }
    }
  }

  void fetchAndDecodeInstruction(uint8_t &instruction_code, Instruction &instruction, Operands &operands);
  bool executeInstruction();
  bool executeGPU(unsigned long ticks_elapsed)
  {
    return this->gpu.executeGPU(ticks_elapsed);
  }
  bool executeInterrupts();

  void render();
};
