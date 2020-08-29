#pragma once

#include <cstdint>

struct GameBoy;

void rlc(GameBoy &gameboy, uint8_t &value);

void rl(GameBoy &gameboy, uint8_t &value);

void rrc(GameBoy &gameboy, uint8_t &value);

void rr(GameBoy &gameboy, uint8_t &value);
