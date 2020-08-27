#include <iostream>

#include "gameboy.h"
#include "ops.h"

const std::unordered_map<BreakpointType, std::string> breakpoint_type_to_string = {
    {BreakpointType::PC, "PC"},
    {BreakpointType::MEMORY, "Memory"},
    {BreakpointType::INSTRUCTION, "Instruction"},
};

void GameBoy::fetchAndDecodeInstruction(uint8_t &instruction_code, Instruction &instruction, Operands &operands)
{
  instruction_code = this->memory.read_byte(this->cpu.registrers.pc);
  instruction = instruction_set[instruction_code];
  if (instruction.size > 0)
  {
    for (uint8_t i = 0; i < instruction.size; i++)
    {
      operands.values[i] = this->memory.read_byte(this->cpu.registrers.pc + i + 1);
    }
  }
}

bool GameBoy::executeInstruction()
{
  uint8_t instruction_code;
  Instruction instruction;
  Operands operands;
  this->fetchAndDecodeInstruction(instruction_code, instruction, operands);
  this->cpu.registrers.pc += 1 + instruction.size;

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
  // Check for breakpoints
  auto &breakpoints = this->breakpoints[BreakpointType::PC];
  auto it = breakpoints.find(this->cpu.registrers.pc);
  if (it != breakpoints.end())
  {
    std::cout << "Breakpoint! 0x" << std::hex << this->cpu.registrers.pc << std::dec << std::endl;
    std::cout << "0x" << std::hex << (*it).first << std::dec << std::endl;
    // Found a breakpoint
    this->debugging = true;
  }
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

void GameBoy::render()
{
  std::string cpu_debug_title = this->gameboy_title;
  cpu_debug_title.append(" - CPU");
  ImVec2 debug_window_position;
  ImVec2 debug_window_size;

  ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_Once);
  if (ImGui::Begin(cpu_debug_title.c_str(), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar))
  {
    if (ImGui::CollapsingHeader("CPU"))
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
        ImGui::Text("Last Executed OP: %s", format_instruction(*(this->last_instruction), this->last_operands).c_str());
      }
      else
      {
        ImGui::Text("Last Executed OP: NULL");
      }
      uint8_t next_instruction_code;
      Instruction next_instruction;
      Operands next_operands;
      this->fetchAndDecodeInstruction(next_instruction_code, next_instruction, next_operands);
      ImGui::Text("Next OP: %s", format_instruction(next_instruction, next_operands).c_str());
    }
    if (ImGui::CollapsingHeader("Timers"))
    {
      ImGui::Text("Divider: %d", *(this->div_register));
      ImGui::Text("Timer: %d", *(this->tima_register));
    }
    if (ImGui::CollapsingHeader("GPU"))
    {
      std::string mode;
      switch (this->gpu.current_mode)
      {
      case GPU_mode::H_BLANK:
        mode = "H_BLANK";
        break;
      case GPU_mode::V_BLANK:
        mode = "V_BLANK";
        break;
      case GPU_mode::OAM:
        mode = "OAM";
        break;
      case GPU_mode::VRAM:
        mode = "VRAM";
        break;
      }
      ImGui::Text("Mode: %s", mode.c_str());
      ImGui::Text("Scan line: %d", *(this->gpu.scanline));
    }
    ImGui::Checkbox("Debugging", &(this->debugging));
    if (this->debugging)
    {
      if (ImGui::Button("Step"))
      {
        this->step = true;
      }
    }
    if (ImGui::Button("Breakpoints"))
    {
      this->breakpoints_window = true;
    }

    if (ImGui::Button("Go to PC"))
    {
      this->memory_editor.GotoAddrAndHighlight(static_cast<size_t>(this->cpu.registrers.pc), static_cast<size_t>(this->cpu.registrers.pc));
    }

    debug_window_position = ImGui::GetWindowPos();
    debug_window_size = ImGui::GetWindowSize();
  }
  ImGui::End();

  if (this->breakpoints_window)
  {
    ImGui::SetNextWindowPos(ImVec2(debug_window_position.x, debug_window_position.y + debug_window_size.y + 10), ImGuiCond_Once);
    if (ImGui::Begin("Breakpoints", &(this->breakpoints_window), ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar))
    {
      // Display breakpoints
      ImGui::Text("Breakpoints:");
      std::for_each(this->breakpoints.begin(), this->breakpoints.end(), [&](auto &map) {
        std::vector<uint16_t> breakpoints_to_delete;
        for (auto breakpoint : map.second)
        {
          bool pushed_color = false;
          if (breakpoint.second.type == BreakpointType::PC && breakpoint.first == this->cpu.registrers.pc)
          {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0, 0, 0, 1.0));
            pushed_color = true;
          }
          ImGui::Text("Address: 0x%04X Type: %s", breakpoint.first, breakpoint_type_to_string.at(breakpoint.second.type).c_str());
          if (pushed_color)
          {
            ImGui::PopStyleColor();
          }
          ImGui::SameLine();
          char buffer[13];
          sprintf(buffer, "Remove##%04X", breakpoint.first);
          if (ImGui::Button(buffer))
          {
            breakpoints_to_delete.push_back(breakpoint.first);
          }
        }
        std::for_each(breakpoints_to_delete.begin(), breakpoints_to_delete.end(), [&](auto breakpoint) {
          map.second.erase(breakpoint);
        });
      });
      ImGui::Text("Breakpoints set: %lu", init_if_absent<>(this->breakpoints, BreakpointType::PC).size());
      ImGui::Text("Address:");
      ImGui::SameLine();
      bool entered_address = false;
      entered_address |= ImGui::InputText("##adress", this->breakpoints_input_buffer, BREAKPOINTS_BUFFER_LENGTH, ImGuiInputTextFlags_EnterReturnsTrue);
      ImGui::SameLine();
      entered_address |= ImGui::Button("Add Breakpoint");
      if (entered_address)
      {
        uint16_t byte = convert_string_to_hex(std::string(this->breakpoints_input_buffer));
        memset(this->breakpoints_input_buffer, 0, BREAKPOINTS_BUFFER_LENGTH);
        Breakpoint breakpoint = {byte, BreakpointType::PC};
        init_if_absent<>(this->breakpoints, BreakpointType::PC).insert(std::pair<uint16_t, Breakpoint>(byte, breakpoint));
      }
    }
    ImGui::End();
  }

  ImGui::SetNextWindowPos(ImVec2(debug_window_position.x + debug_window_size.x + 100, debug_window_position.y), ImGuiCond_Once);
  ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_Once);
  current_gameboy_to_use = this;
  this->memory_editor.DrawWindow("Memory Editor", 0x0000, TOTAL_MEMORY_SIZE + 1);

  ImGui::SetNextWindowPos(ImVec2(debug_window_position.x + debug_window_size.x + 100, debug_window_position.y + 200 + 10), ImGuiCond_Once);
  if (ImGui::Begin(this->gameboy_title.c_str(), &this->running, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar))
  {
    //ImGui::SetWindowSize(ImVec2(OUTPUT_WIDTH * 2, OUTPUT_HEIGHT * 2));
    ImGui::Image((void *)(intptr_t)this->gpu.frame_texture, ImVec2(OUTPUT_WIDTH * 2, OUTPUT_HEIGHT * 2));
  }
  ImGui::End();
}

GameBoy *current_gameboy_to_use = NULL;

ImU8 read_memory_data(const ImU8 *data, size_t offset)
{
  return current_gameboy_to_use->memory.read_byte(offset);
}

void write_memory_data(ImU8 *data, size_t offset, ImU8 data_to_write)
{
  *(current_gameboy_to_use->memory.read_raw_byte(offset)) = data_to_write;
}

bool highlight_memory_data(const ImU8 *data, size_t offset)
{
  return current_gameboy_to_use->cpu.registrers.pc == offset;
}
