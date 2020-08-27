#pragma once

#define OPS_PER_SEC 1050000

#define DIV_REGISTER_LOCATION 0xFF04
#define DIV_REGISTER_UPDATE_FREQUENCY 16384
#define DIV_REGISTER_UPDATE_TICKS (OPS_PER_SEC / DIV_REGISTER_UPDATE_FREQUENCY)

// #define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
#define PRINT_INSTRUCTIONS
#define PRINT_CPU_REGISTRERS
//#define PRINT_GPU_REGISTRERS
#endif

#include <string>

#include "imgui.h"
#include <imgui_memory_editor/imgui_memory_editor.h>

#include <SDL.h>

#include "controls.h"
#include "cpu.h"
#include "gpu.h"
#include "memory.h"

extern Memory *current_memory_to_use;

struct GameBoy
{
  GameBoy(std::string filename) : memory(this, filename, &keys), cpu(&this->memory, &this->ticks), gpu(&this->memory, &this->ticks, &this->cpu), last_operands(0)
  {
    this->keys.p14.pad_bool = 0x00;
    this->keys.p15.pad_bool = 0X00;

    this->memory.write_byte(DIV_REGISTER_LOCATION, 0x00);
    this->div_register = this->memory.read_raw_byte(DIV_REGISTER_LOCATION);

    this->rom_title = this->memory.get_rom_title();
    this->gameboy_title = "Gameboy - ";
    this->gameboy_title.append(this->rom_title);

    this->memory_editor.ReadFn = read_memory_data;
    this->memory_editor.WriteFn = write_memory_data;
  }

  ~GameBoy()
  {
    std::cout << this->cpu;
  }

  Memory memory;
  CPU cpu;
  GPU gpu;

  MemoryEditor memory_editor;

  uint8_t *div_register;

  Keys keys;

  std::string rom_title;
  std::string gameboy_title;

  bool halted = false;
  bool running = true;
  bool debugging = false;
  bool step = false;

  bool is_window_open = true;

  unsigned long ticks = 0;
  unsigned long last_ticks = 0;
  unsigned long last_check_ticks = 0;

  const Instruction *last_instruction = NULL;
  Operands last_operands;

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
    if (event.type == SDL_KEYDOWN || SDL_KEYUP)
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

  void render()
  {
    if (ImGui::Begin(this->gameboy_title.c_str(), &this->is_window_open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar))
    {
      //ImGui::SetWindowSize(ImVec2(OUTPUT_WIDTH * 2, OUTPUT_HEIGHT * 2));
      ImGui::Image((void *)(intptr_t)this->gpu.frame_texture, ImVec2(OUTPUT_WIDTH * 2, OUTPUT_HEIGHT * 2));
    }
    ImGui::End();

    std::string cpu_debug_title = this->gameboy_title;
    cpu_debug_title.append(" - CPU");

    if (ImGui::Begin(cpu_debug_title.c_str(), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar))
    {
      ImGui::Text("AF: 0x%04X Z: %d N: %d H: %d C: %d", this->cpu.registrers.af, this->cpu.registrers.f.z, this->cpu.registrers.f.n, this->cpu.registrers.f.h, this->cpu.registrers.f.c);
      ImGui::Text("BC: 0x%04X", this->cpu.registrers.bc);
      ImGui::Text("DE: 0x%04X", this->cpu.registrers.de);
      ImGui::Text("HL: 0x%04X", this->cpu.registrers.hl);
      ImGui::Text("PC: 0x%04X", this->cpu.registrers.pc);
      ImGui::Text("SP: 0x%04X", this->cpu.registrers.sp);
      ImGui::Text("IME: 0x%02X", this->cpu.registrers.ime);
      ImGui::Text("Ticks: %ld", this->ticks);
      if (this->last_instruction != NULL)
      {
        if (this->last_instruction->size == 0)
        {
          ImGui::Text("Last Executed OP: %s", this->last_instruction->name.c_str());
        }
        else if (this->last_instruction->size == 1)
        {
          ImGui::Text("Last Executed OP: %s 0x%02X", this->last_instruction->name.c_str(), this->last_operands.values[0]);
        }
        else if (this->last_instruction->size == 2)
        {
          ImGui::Text("Last Executed OP: %s 0x%02X 0x%02X", this->last_instruction->name.c_str(), this->last_operands.values[0], this->last_operands.values[1]);
        }
      }
      ImGui::Checkbox("Debugging", &(this->debugging));
      if (this->debugging)
      {
        if (ImGui::Button("Step"))
        {
          this->step = true;
        }
      }
    }
    ImGui::End();

    current_memory_to_use = &(this->memory);
    this->memory_editor.DrawWindow("Memory Editor", 0x0000, TOTAL_MEMORY_SIZE + 1);
  }
};
