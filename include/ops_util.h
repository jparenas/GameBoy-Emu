#pragma once

#include "gameboy.h"
#include "gpu.h"
#include "ops.h"

int8_t unsigned_8_to_signed(uint8_t x);

uint16_t convert_uint8_to_uint16(uint8_t a, uint8_t b);

void write_short_to_stack(GameBoy &gameboy, uint16_t value);

uint16_t pop_short_from_stack(GameBoy &gameboy);

std::string format_instruction(const Instruction &instruction, const Operands &operands);
