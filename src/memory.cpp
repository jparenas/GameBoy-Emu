#include <cmath>
#include <fstream>
#include <iostream>

#include "memory.h"

Memory::Memory(std::string filename, Keys *keys)
{
  this->keys = keys;

  this->read_ROM(filename);
}

void Memory::read_ROM(std::string filename)
{
  std::streampos size;

  std::fstream file(filename, std::ios::in | std::ios::binary);

  if (!file.is_open())
  {
    std::cout << "Error opening file" << std::endl;
    exit(1);
  }

  file.seekg(0, std::ios::end);
  size = file.tellg();
  if (size < 0x180)
  {
    std::cout << "ROM file too small. File size: " << size << std::endl;
    file.close();
    exit(1);
  }

  std::cout << "File size: " << size << std::endl;

  char title[17];
  title[16] = '\0';
  file.seekg(ROM_OFFSET_TITLE, std::ios::beg);
  file.read(title, 16);

  this->rom_title = std::string(title);

  std::cout << "ROM title: " << this->rom_title << std::endl;

  char romSize;

  file.seekg(ROM_OFFSET_ROM_SIZE, std::ios::beg);
  file.read(&romSize, 1);

  this->number_rom_banks = pow(2, romSize + 1);

  std::cout << "ROM size: " << this->number_rom_banks * 16 << "KB" << std::endl;

  if (size != this->number_rom_banks * 16 * 1024)
  {
    std::cout << "ROM filesize does not equal ROM size!" << std::endl;
    file.close();
    exit(1);
  }

  this->rom = std::unique_ptr<uint8_t[]>(new uint8_t[size]);

  file.seekg(0, std::ios::beg);
  file.read(reinterpret_cast<char *>(this->rom.get()), size);
  file.close();

  this->number_ram_banks = this->rom[ROM_OFFSET_RAM_SIZE];

  uint16_t ram_size;
  switch (this->number_ram_banks)
  {
  case 0:
  case 1:
    ram_size = 0x2000;
    break;
  case 3:
    ram_size = 0x8000;
  default:
    ram_size = 0x2000;
    break;
  }

  std::cout << "MBC Type: ";
  switch (this->rom[MBC_TYPE_OFFSET])
  {
  case 1:
  case 2:
  case 3:
    std::cout << "MBC 1";
    this->mbc_type = MBC::MBC_1;
    this->enable_ram_write = false;
    break;
  case 5:
  case 6:
    std::cout << "MBC 2";
    this->mbc_type = MBC::MBC_2;
    this->enable_ram_write = false;
    break;
  default:
    std::cout << "None";
    this->mbc_type = MBC::NONE;
    this->enable_ram_write = true;
    break;
  }
  std::cout << std::endl;

  this->switchable_ram = std::unique_ptr<uint8_t[]>(new uint8_t[ram_size]);

  this->current_ram_bank = 0;
  this->current_rom_bank = 1;
}

uint8_t *Memory::read_raw_byte(uint16_t address)
{
  if (address <= ROM_END && address >= ROM_BEGIN)
  {
    return &(this->rom[address - ROM_BEGIN]);
  }
  else if (address <= SWITCHABLE_ROM_END && address >= SWITCHABLE_ROM_BEGIN)
  {
    return &(this->rom[address - SWITCHABLE_ROM_BEGIN + this->current_rom_bank * ROM_BANK_SIZE]);
  }
  else if (address <= VRAM_END && address >= VRAM_BEGIN)
  {
    return &(this->vram[address - VRAM_BEGIN]);
  }
  else if (address <= SWITCHABLE_RAM_END && address >= SWITCHABLE_RAM_BEGIN)
  {
    return &(this->switchable_ram[address - SWITCHABLE_RAM_BEGIN + this->current_ram_bank * RAM_BANK_SIZE]);
  }
  else if (address <= INTERNAL_RAM_END && address >= INTERNAL_RAM_BEGIN)
  {
    return &(this->ram[address - INTERNAL_RAM_BEGIN]);
  }
  else if (address <= ECHO_RAM_END && address >= ECHO_RAM_BEGIN)
  {
    return &(this->ram[address - ECHO_RAM_BEGIN]);
  }
  else if (address <= OAM_END && address >= OAM_BEGIN)
  {
    return &(this->oam[address - OAM_BEGIN]);
  }
  else if (address <= IO_END && address >= IO_BEGIN)
  {
    if (address == JOYPAD_LOCATION)
    {
      if (!(this->io[JOYPAD_LOCATION - IO_BEGIN] & 0x20))
      {
        this->io[JOYPAD_LOCATION - IO_BEGIN] = 0xC0 | 0x10 | ((~this->keys->p15.pad_bool) & 0x0F);
      }
      else if (!(this->io[JOYPAD_LOCATION - IO_BEGIN] & 0x10))
      {
        this->io[JOYPAD_LOCATION - IO_BEGIN] = 0xC0 | 0x20 | ((~this->keys->p14.pad_bool) & 0x0F);
      }
      else if (!(this->io[JOYPAD_LOCATION - IO_BEGIN] & 0x30))
      {
        this->io[JOYPAD_LOCATION - IO_BEGIN] = 0xFF;
      }
      else
      {
        this->io[JOYPAD_LOCATION - IO_BEGIN] = 0xC0 | 0x0F;
      }
      return &(this->io[JOYPAD_LOCATION - IO_BEGIN]);
    }
    return &(this->io[address - IO_BEGIN]);
  }
  else if (address <= STACK_INTERNAL_RAM_END && address >= STACK_INTERNAL_RAM_BEGIN)
  {
    return &(this->stack_ram[address - STACK_INTERNAL_RAM_BEGIN]);
  }
  std::cout << "READ UNREACHABLE RAM:0x" << std::hex << address << std::endl;
  return NULL;
}

uint8_t Memory::read_byte(uint16_t address)
{
  //std::cout << "Read byte at 0x" << std::hex << address << ": 0x" << (int)*(this->read_raw_byte(address)) << std::endl;
  return *(this->read_raw_byte(address));
}

uint16_t Memory::read_short(uint16_t address)
{
  return (uint16_t)this->read_byte(address) | (((uint16_t)this->read_byte(address + 1)) << 8);
}

void Memory::write_byte(uint16_t address, uint8_t value)
{
  //std::cout << "Written byte at 0x" << std::hex << address << ": 0x" << (int)value << std::endl;
  if (address < VRAM_BEGIN)
  {
    // Banking Handling
    if (address < 0x2000)
    {
      if (this->mbc_type == MBC::MBC_1 || (this->mbc_type == MBC::MBC_2 && (address >> 4 & 0x01) == 0))
      {
        if (value & 0x0F == 0x0A)
        {
          this->enable_ram_write = true;
        }
        else if (value & 0x0F == 0x00)
        {
          this->enable_ram_write = false;
        }
      }
    }
    else if (address >= 0x2000 && address < 0x4000)
    {
      if (this->mbc_type == MBC::MBC_1)
      {
        this->current_rom_bank = (this->current_rom_bank & 0b11100000) | (value & 0b00011111);
        if (this->current_rom_bank == 0)
        {
          this->current_rom_bank = 1;
        }
      }
      else if (this->mbc_type == MBC::MBC_2)
      {
        this->current_rom_bank = value & 0x0F;
        if (this->current_rom_bank == 0)
        {
          this->current_rom_bank = 1;
        }
      }
    }
    else if (address >= 0x4000 && address < 0x6000)
    {
      if (this->mbc_type == MBC::MBC_1)
      {
        if (this->set_rom_banking)
        {
          this->current_rom_bank = (this->current_rom_bank & 0b11100000) | (value & 0b00011111);
          if (this->current_rom_bank == 0)
          {
            this->current_rom_bank = 1;
          }
        }
        else
        {
          this->current_ram_bank = value & 0x03;
        }
      }
    }
    else if (address >= 0x6000 && address < 0x8000)
    {
      if (this->mbc_type == MBC::MBC_1)
      {
        this->set_rom_banking = value & 0x01 == 0;
        this->current_ram_bank = 0;
      }
    }
  }
  else if (address <= VRAM_END && address >= VRAM_BEGIN)
  {
    this->vram[address - VRAM_BEGIN] = value;
  }
  else if (address <= SWITCHABLE_RAM_END && address >= SWITCHABLE_RAM_BEGIN)
  {
    if (this->enable_ram_write)
    {
      this->switchable_ram[address - SWITCHABLE_RAM_BEGIN + this->current_ram_bank * RAM_BANK_SIZE] = value;
    }
  }
  else if (address <= INTERNAL_RAM_END && address >= INTERNAL_RAM_BEGIN)
  {
    //std::cout << "Written byte at 0x" << std::hex << address << ": byte 0x" << (int)value << std::endl;
    this->ram[address - INTERNAL_RAM_BEGIN] = value;
  }
  else if (address <= ECHO_RAM_END && address >= ECHO_RAM_BEGIN)
  {
    this->ram[address - ECHO_RAM_BEGIN] = value;
  }
  else if (address <= OAM_END && address >= OAM_BEGIN)
  {
    std::cout << "Written to OAM: 0x" << std::hex << address << std::endl;
    if (this->read_byte(0xFF41) /*STAT*/ & 0b00000011 != 0b10 && this->read_byte(0xFF41) /*STAT*/ & 0b00000011 != 0b11)
    {
      this->oam[address - OAM_BEGIN] = value;
    }
  }
  else if (address == 0xFF46)
  {
    this->io[address - IO_BEGIN] = value;
    uint16_t start_address = ((uint16_t)value) << 8;
    //std::cout << "DMA request, address 0x" << std::hex << start_address << std::endl;
    for (uint16_t i = 0; i < 160; i++)
    {
      this->oam[i] = this->read_byte(start_address + i);
      //std::cout << (int)this->oam[i];
    }
    //std::cout << std::endl;
  }
  else if (address <= IO_END && address >= IO_BEGIN)
  {
    if (address == JOYPAD_LOCATION)
    {
      this->io[address - IO_BEGIN] = value | 0xCF;
      return;
    }
    else if (address == 0xFF02)
    {
      if (value == 0x81)
      {
        std::cout << this->io[0xFF01 - IO_BEGIN];
      }
    }
    else if (address == 0xFF04)
    {
      this->io[address - IO_BEGIN] = 0;
    }
    else if (address == 0xFF44)
    {
      this->io[address - IO_BEGIN] = 0;
    }
    else
    {
      this->io[address - IO_BEGIN] = value;
    }
  }
  else if (address <= STACK_INTERNAL_RAM_END && address >= STACK_INTERNAL_RAM_BEGIN)
  {
    this->stack_ram[address - STACK_INTERNAL_RAM_BEGIN] = value;
  }
  else
  {
    std::cout << "WRITTEN UNREACHABLE RAM:0x" << std::hex << address << std::endl;
  }
}

void Memory::write_short(uint16_t address, uint16_t value)
{
  this->write_byte(address, (uint8_t)(value & 0x00FF));
  this->write_byte(address + 1, (uint8_t)((value & 0xFF00) >> 8));
}
