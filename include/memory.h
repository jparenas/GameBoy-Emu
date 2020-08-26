#pragma once

#define ROM_OFFSET_TITLE 0x134
#define MBC_TYPE_OFFSET 0x147
#define ROM_OFFSET_ROM_SIZE 0x148
#define ROM_OFFSET_RAM_SIZE 0x149

#define ROM_BEGIN 0x0000
#define ROM_END 0x3FFF
#define SWITCHABLE_ROM_BEGIN 0x4000
#define SWITCHABLE_ROM_END 0x7FFF
#define VRAM_BEGIN 0x8000
#define VRAM_END 0x9FFF
#define SWITCHABLE_RAM_BEGIN 0xA000
#define SWITCHABLE_RAM_END 0xBFFF
#define INTERNAL_RAM_BEGIN 0xC000
#define INTERNAL_RAM_END 0xDFFF
#define ECHO_RAM_BEGIN 0xE000
#define ECHO_RAM_END 0xFDFF
#define OAM_BEGIN 0xFE00
#define OAM_END 0xFEFF
#define IO_BEGIN 0xFF00
#define IO_END 0xFF7F
#define STACK_INTERNAL_RAM_BEGIN 0xFF80
#define STACK_INTERNAL_RAM_END 0xFFFF

#define VRAM_POSITION 0x8000
#define LCDC_POSITION 0xFF40
#define STAT_POSITION 0xFF41
#define SCROLL_X_POSITION 0xFF42
#define SCROLL_Y_POSITION 0xFF43
#define SCANLINE_POSITION 0xFF44
#define LY_C_POSITION 0xFF45
#define BACKGROUND_PALETTE_POSITION 0xFF47
#define SPRITE_0_PALETTE_POSITION 0xFF48
#define SPRITE_1_PALETTE_POSITION 0xFF49
#define WINDOW_Y_POSITION 0xFF4A
#define WINDOW_X_POSITION 0xFF4B

#define ROM_BANK_SIZE SWITCHABLE_ROM_END - SWITCHABLE_ROM_BEGIN + 1
#define RAM_BANK_SIZE SWITCHABLE_RAM_END - SWITCHABLE_RAM_BEGIN + 1

#define JOYPAD_LOCATION 0xFF00

#include <memory>
#include <string>

#include "controls.h"

enum class MBC
{
  NONE,
  MBC_1,
  MBC_2
};

class Memory
{
private:
  std::unique_ptr<uint8_t[]> rom;
  uint8_t vram[VRAM_END - VRAM_BEGIN + 1];
  std::unique_ptr<uint8_t[]> switchable_ram;
  uint8_t ram[INTERNAL_RAM_END - INTERNAL_RAM_BEGIN + 1];
  uint8_t oam[OAM_END - OAM_BEGIN + 1];
  uint8_t io[IO_END - IO_BEGIN + 1];
  uint8_t stack_ram[STACK_INTERNAL_RAM_END - STACK_INTERNAL_RAM_BEGIN + 1];

  MBC mbc_type;
  bool enable_ram_write;
  bool set_rom_banking = false;
  uint8_t number_rom_banks;
  uint8_t number_ram_banks;
  uint8_t current_rom_bank;
  uint8_t current_ram_bank;

  Keys *keys;

  std::string rom_title;

  void read_ROM(std::string filename);

public:
  Memory(std::string filename, Keys *keys);
  uint8_t *read_raw_byte(uint16_t address);
  uint8_t read_byte(uint16_t address);
  uint16_t read_short(uint16_t address);
  void write_byte(uint16_t address, uint8_t value);
  void write_short(uint16_t address, uint16_t value);
  std::string get_rom_title()
  {
    return this->rom_title;
  }
};
