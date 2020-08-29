#pragma once

#define OUTPUT_WIDTH 160
#define OUTPUT_HEIGHT 144

#define MAX_SPRITES_PER_SCANLINE 15

#define OAM_TIME 80

#define OAM_LOCATION 0xFE00

#define GL_SILENCE_DEPRECATION

#include <SDL.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#else
#include <GL/glu.h>
#endif

#include "cpu.h"
#include "memory.h"

struct Sprite
{
  uint8_t y_pos;
  uint8_t x_pos;
  uint8_t tile_location;
  struct
  {
    uint8_t _pad : 4;
    bool palette : 1;
    bool x_flip : 1;
    bool y_flip : 1;
    bool priority : 1;
  };
};

inline bool compare_sprites(Sprite *lhs, Sprite *rhs)
{
  return lhs->x_pos < rhs->x_pos;
}

struct Color
{
  uint8_t b;
  uint8_t g;
  uint8_t r;
  uint8_t a;

  bool operator==(const Color &color)
  {
    return this->r == color.r && this->g == color.g && this->b && color.b && this->a == color.a;
  }

  bool operator!=(const Color &color)
  {
    return !(*this == color);
  }
};

const Color palette[4] = {
    {255, 255, 255, 255},
    {192, 192, 192, 255},
    {96, 96, 96, 255},
    {0, 0, 0, 255},
};

enum class GPU_mode
{
  H_BLANK = 0,
  V_BLANK = 1,
  OAM = 2,
  VRAM = 3,
};

struct LCD_Control
{
  bool bg_window_display : 1;
  bool sprite_display : 1;
  bool sprite_size : 1;
  bool bg_tile_map_select : 1;
  bool bg_window_tile_data_select : 1;
  bool window_display : 1;
  bool window_tile_map_select : 1;
  bool lcd_control_operation : 1;
};

static_assert(sizeof(LCD_Control) == 1, "LCDC size is not correct");

struct STAT_register
{
  uint8_t mode_flag : 2;
  bool scanline_coincidence : 1;
  bool h_blank_interrupt_enable : 1;
  bool v_blank_interrupt_enable : 1;
  bool oam_interrupt_enable : 1;
  bool coincidence_interrupt_enable : 1;
  bool _pad : 1;
};

static_assert(sizeof(STAT_register) == 1, "STAT register size is not correct");

std::string gpu_mode_to_string(const GPU_mode &mode);

struct GPU
{
  GPU(Memory *memory, unsigned long *ticks, CPU *cpu);

  ~GPU()
  {
    glDeleteTextures(1, &this->frame_texture);
  }

  unsigned long *ticks;

  uint32_t gpu_ticks = 29;
  unsigned long previous_ticks = 0;

  LCD_Control *lcd_control;
  uint8_t *scanline;
  STAT_register *stat;
  uint8_t *ly_c;
  uint8_t *scroll_x;
  uint8_t *scroll_y;
  uint8_t *window_x;
  uint8_t *window_y;

  Memory *memory;
  CPU *cpu;

  GPU_mode current_mode = GPU_mode::V_BLANK;

  //SDL_Renderer *renderer;
  GLuint frame_texture;
  Color pixels[OUTPUT_WIDTH * OUTPUT_HEIGHT];

  bool executeGPU(unsigned long ticks_elapsed);

  void renderScanline();

  Color getColorFromPalette(uint8_t color, uint16_t palette_address)
  {
    uint8_t color_position = color * 2;
    uint8_t color_palette = this->memory->read_byte(palette_address, false) >> (color_position + 1) & 0x01;
    color_palette <<= 1;
    color_palette |= this->memory->read_byte(palette_address, false) >> color_position & 0x01;

    return palette[color_palette];
  }

  unsigned int getIndex(uint8_t x, uint8_t y)
  {
    return OUTPUT_WIDTH * y + x;
  }

  void renderFramebuffer()
  {
    if ((*(this->lcd_control)).lcd_control_operation) // Bit 7
    {
      glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, OUTPUT_WIDTH, OUTPUT_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->pixels);
    }
  }
};

inline std::ostream &operator<<(std::ostream &o, const GPU &gpu)
{
  std::string mode = gpu_mode_to_string(gpu.current_mode);
  o << std::dec << "Mode: " << mode << std::endl;
  o << std::dec << "Scan line: " << (int)*(gpu.scanline) << std::endl;
  o << std::dec << "LCDC: " << std::bitset<8>((*(bool *)(gpu.lcd_control))) << std::endl;
  o << std::dec << "STAT: " << std::bitset<8>(*(reinterpret_cast<uint8_t *>(gpu.stat))) << std::endl;
  o << std::endl;
  return o;
}
