#include <iostream>

#include "gameboy.h"
#include "ops_util.h"

const std::unordered_map<BreakpointType, std::string> breakpoint_type_to_string = {
    {BreakpointType::PC, "PC"},
    {BreakpointType::MEMORY, "Memory"},
    {BreakpointType::INSTRUCTION, "Instruction"},
};

GameBoy::GameBoy(std::string filename) : memory(this, filename, &keys), cpu(&(this->memory), &(this->ticks)), gpu(&(this->memory), &(this->ticks), &(this->cpu))
{
  this->keys.p14.pad_bool = 0x00;
  this->keys.p15.pad_bool = 0X00;

  *(this->memory.read_raw_byte(JOYPAD_LOCATION)) = 0xFF;
  this->div_register = this->memory.read_raw_byte(DIV_REGISTER_POSITION);
  *(this->div_register) = 0xCF;
  this->tima_register = this->memory.read_raw_byte(TIMA_REGISTER_POSITION);
  this->timer_counter = timer_ticks[0];

  this->rom_title = this->memory.get_rom_title();
  this->gameboy_title = "Gameboy - ";
  this->gameboy_title.append(this->rom_title);

  this->memory_editor.ReadFn = read_memory_data;
  this->memory_editor.WriteFn = write_memory_data;
  this->memory_editor.HighlightFn = highlight_memory_data;

  memset(this->breakpoint_pc_input_buffer, 0, BREAKPOINTS_BUFFER_LENGTH);
  memset(this->breakpoint_memory_input_buffer, 0, BREAKPOINTS_BUFFER_LENGTH);
  memset(this->breakpoint_instruction_input_buffer, 0, BREAKPOINTS_BUFFER_LENGTH);
}

void GameBoy::fetchAndDecodeInstruction(uint8_t &instruction_code, Instruction &instruction, Operands &operands)
{
  instruction_code = this->memory.read_byte(this->cpu.registrers.pc, false);
  instruction = instruction_set[instruction_code];
  if (instruction.size > 0)
  {
    for (uint8_t i = 0; i < instruction.size; i++)
    {
      operands.values[i] = this->memory.read_byte(this->cpu.registrers.pc + i + 1, false);
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
  this->last_instruction_code = instruction_code;
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
    this->breakpoint_trigger = &((*it).second);
  }
  // Check for instruction breakpoints
  this->fetchAndDecodeInstruction(instruction_code, instruction, operands);
  breakpoints = this->breakpoints[BreakpointType::INSTRUCTION];
  it = breakpoints.find(static_cast<uint16_t>(instruction_code));
  if (it != breakpoints.end())
  {
    // Found a breakpoint
    this->debugging = true;
    this->breakpoint_trigger = &((*it).second);
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
        this->cpu.registrers.ime = false;
        write_short_to_stack(*this, this->cpu.registrers.pc);
        this->cpu.registrers.pc = INTERRUPT_VBLANK_INSTRUCTION;
        this->ticks += 12;
      }
      else if (enabled_flags & INTERRUPT_STAT)
      {
        *(this->cpu.interrupt_flags) &= ~INTERRUPT_STAT;
        this->cpu.registrers.ime = false;
        write_short_to_stack(*this, this->cpu.registrers.pc);
        this->cpu.registrers.pc = INTERRUPT_STAT_INSTRUCTION;
        this->ticks += 12;
      }
      else if (enabled_flags & INTERRUPT_TIMER)
      {
        *(this->cpu.interrupt_flags) &= ~INTERRUPT_TIMER;
        this->cpu.registrers.ime = false;
        write_short_to_stack(*this, this->cpu.registrers.pc);
        this->cpu.registrers.pc = INTERRUPT_TIMER_INSTRUCTION;
        this->ticks += 12;
      }
      else if (enabled_flags & INTERRUPT_SERIAL)
      {
        *(this->cpu.interrupt_flags) &= ~INTERRUPT_SERIAL;
        this->cpu.registrers.ime = false;
        write_short_to_stack(*this, this->cpu.registrers.pc);
        this->cpu.registrers.pc = INTERRUPT_SERIAL_INSTRUCTION;
        this->ticks += 12;
      }
      else if (enabled_flags & INTERRUPT_JOYPAD)
      {
        *(this->cpu.interrupt_flags) &= ~INTERRUPT_JOYPAD;
        this->cpu.registrers.ime = false;
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
      ImGui::Text("Interrupts enabled: %s", bool_to_string(this->cpu.registrers.ime).c_str());
      ImGui::Text("V Blank: %s STAT: %s Timer: %s Joy Pad: %s Serial: %s", bool_to_string(*(this->cpu.interrupt_flags) | INTERRUPT_VBLANK).c_str(), bool_to_string(*(this->cpu.interrupt_flags) | INTERRUPT_STAT).c_str(), bool_to_string(*(this->cpu.interrupt_flags) | INTERRUPT_TIMER).c_str(), bool_to_string(*(this->cpu.interrupt_flags) | INTERRUPT_JOYPAD).c_str(), bool_to_string(*(this->cpu.interrupt_flags) | INTERRUPT_SERIAL).c_str());
      ImGui::Text("Ticks: %ld", this->ticks);
      ImGui::Text("Last Executed OP: %s", format_instruction(this->last_instruction_code, this->last_operands).c_str());
      uint8_t next_instruction_code;
      Instruction next_instruction;
      Operands next_operands;
      this->fetchAndDecodeInstruction(next_instruction_code, next_instruction, next_operands);
      ImGui::Text("Next OP: %s", format_instruction(next_instruction_code, next_operands).c_str());
    }
    if (ImGui::CollapsingHeader("Timers"))
    {
      ImGui::Text("Divider: %d", *(this->div_register));
      ImGui::Text("Timer: %d", *(this->tima_register));
    }
    if (ImGui::CollapsingHeader("GPU"))
    {
      ImGui::Text("Mode: %s", gpu_mode_to_string(this->gpu.current_mode).c_str());
      ImGui::SameLine();
      ImGui::Text("GPU Ticks: %d", this->gpu.gpu_ticks);
      ImGui::Text("Scan line: %d", *(this->gpu.scanline));
      ImGui::Text("LY-C: %d", *(this->gpu.ly_c));
      ImGui::Text("Scroll X: %d", *(this->gpu.scroll_x));
      ImGui::SameLine();
      ImGui::Text("Scroll Y: %d", *(this->gpu.scroll_y));
      ImGui::Text("Window X: %d", *(this->gpu.window_x));
      ImGui::SameLine();
      ImGui::Text("Window Y: %d", *(this->gpu.window_y));
      ImGui::Text("Window Y: %d", *(this->gpu.window_y));
      ImGui::Text("LCD enabled: %s BG & W display: %s Sprite display: %s Window display: %s", bool_to_string(this->gpu.lcd_control->lcd_control_operation).c_str(), bool_to_string(this->gpu.lcd_control->bg_window_display).c_str(), bool_to_string(this->gpu.lcd_control->sprite_display).c_str(), bool_to_string(this->gpu.lcd_control->window_display).c_str());
      ImGui::Text("Sprite size: %s", this->gpu.lcd_control->sprite_size ? "8x16" : "8x8");
      ImGui::Text("BG Tile Map: (%d) %s BG Window Tile Data: (%d) %s Window Tile Map: (%d) %s", this->gpu.lcd_control->bg_tile_map_select, this->gpu.lcd_control->bg_tile_map_select ? "0x9C00" : "0x9800", this->gpu.lcd_control->bg_window_tile_data_select, this->gpu.lcd_control->bg_window_tile_data_select ? "0x8000" : "0x8800", this->gpu.lcd_control->window_tile_map_select, this->gpu.lcd_control->window_tile_map_select ? "0x9C00" : "0x9800");
    }
    if (ImGui::Checkbox("Debugging", &(this->debugging)))
    {
      this->breakpoint_trigger = NULL;
    }
    if (this->debugging)
    {
      if (ImGui::Button("Step"))
      {
        this->breakpoint_trigger = NULL;
        this->step = true;
      }
      ImGui::SameLine();
      if (ImGui::Button("Continue"))
      {
        this->breakpoint_trigger = NULL;
        this->debugging = false;
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
        for (auto &breakpoint : map.second)
        {
          bool pushed_color = false;
          if (&(breakpoint.second) == this->breakpoint_trigger)
          {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0, 0, 0, 1.0));
            pushed_color = true;
          }
          if (breakpoint.second.type != BreakpointType::INSTRUCTION)
          {
            ImGui::Text("Address: 0x%04X Type: %s", breakpoint.first, breakpoint_type_to_string.at(breakpoint.second.type).c_str());
          }
          else
          {
            ImGui::Text("Instruction: 0x%02X Type: %s", breakpoint.first, breakpoint_type_to_string.at(breakpoint.second.type).c_str());
          }

          if (breakpoint.second.type == BreakpointType::MEMORY)
          {
            std::string mode;
            if (breakpoint.second.memory_action.read)
            {
              mode.append("R");
            }
            if (breakpoint.second.memory_action.write)
            {
              mode.append("W");
            }
            ImGui::SameLine();
            ImGui::Text("Mode: %s", mode.c_str());
          }
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
      ImGui::PushItemWidth(80);
      bool entered_address = false;
      entered_address |= ImGui::InputText("##address_pc", this->breakpoint_pc_input_buffer, BREAKPOINTS_BUFFER_LENGTH, ImGuiInputTextFlags_EnterReturnsTrue);
      ImGui::SameLine();
      entered_address |= ImGui::Button("Add PC Breakpoint");
      if (entered_address)
      {
        uint16_t byte = convert_string_to_hex(std::string(this->breakpoint_pc_input_buffer));
        memset(this->breakpoint_pc_input_buffer, 0, BREAKPOINTS_BUFFER_LENGTH);
        Breakpoint breakpoint = {byte, BreakpointType::PC};
        init_if_absent<>(this->breakpoints, BreakpointType::PC).insert(std::pair<uint16_t, Breakpoint>(byte, breakpoint));
      }
      entered_address = false;
      ImGui::Text("Address:");
      ImGui::SameLine();
      ImGui::PushItemWidth(80);
      entered_address = false;
      entered_address |= ImGui::InputText("##address_memory", this->breakpoint_memory_input_buffer, BREAKPOINTS_BUFFER_LENGTH, ImGuiInputTextFlags_EnterReturnsTrue);
      ImGui::SameLine();
      ImGui::Checkbox("Write trigger", &(this->breakpoint_memory_write));
      ImGui::SameLine();
      ImGui::Checkbox("Read trigger", &(this->breakpoint_memory_read));
      ImGui::SameLine();
      entered_address |= ImGui::Button("Add Memory Breakpoint");
      if (entered_address)
      {
        uint16_t byte = convert_string_to_hex(std::string(this->breakpoint_memory_input_buffer));
        memset(this->breakpoint_memory_input_buffer, 0, BREAKPOINTS_BUFFER_LENGTH);
        BreakpointMemoryActionType memory_action;
        memory_action.write = this->breakpoint_memory_write;
        memory_action.read = this->breakpoint_memory_read;
        this->breakpoint_memory_write = false;
        this->breakpoint_memory_read = true;
        Breakpoint breakpoint = {byte, BreakpointType::MEMORY, memory_action};
        init_if_absent<>(this->breakpoints, BreakpointType::MEMORY).insert(std::pair<uint16_t, Breakpoint>(byte, breakpoint));
      }
      entered_address = false;
      ImGui::Text("Instruction:");
      ImGui::SameLine();
      ImGui::PushItemWidth(80);
      entered_address |= ImGui::InputText("##address_instruction", this->breakpoint_instruction_input_buffer, BREAKPOINTS_BUFFER_LENGTH, ImGuiInputTextFlags_EnterReturnsTrue);
      ImGui::SameLine();
      entered_address |= ImGui::Button("Add Instruction Breakpoint");
      if (entered_address)
      {
        uint16_t byte = convert_string_to_hex(std::string(this->breakpoint_instruction_input_buffer));
        memset(this->breakpoint_instruction_input_buffer, 0, BREAKPOINTS_BUFFER_LENGTH);
        Breakpoint breakpoint = {byte, BreakpointType::INSTRUCTION};
        init_if_absent<>(this->breakpoints, BreakpointType::INSTRUCTION).insert(std::pair<uint16_t, Breakpoint>(byte, breakpoint));
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
  return current_gameboy_to_use->memory.read_byte(offset, false);
}

void write_memory_data(ImU8 *data, size_t offset, ImU8 data_to_write)
{
  *(current_gameboy_to_use->memory.read_raw_byte(offset)) = data_to_write;
}

bool highlight_memory_data(const ImU8 *data, size_t offset)
{
  return current_gameboy_to_use->cpu.registrers.pc == offset;
}
