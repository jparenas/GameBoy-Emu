#pragma once

#define OUTPUT_WIDTH 160
#define OUTPUT_HEIGHT 144

#define MAX_SPRITES_PER_SCANLINE 15

#define OAM_TIME 80

#define OAM_LOCATION 0xFE00

#define GL_SILENCE_DEPRECATION

#include <algorithm>
#include <iterator>
#include <set>

#include <SDL.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#else
#include <GL/glu.h>
#endif

#include "cpu.h"
#include "memory.h"

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

struct GPU
{
  GPU(Memory *memory, unsigned long *ticks, CPU *cpu) : memory(memory), ticks(ticks), cpu(cpu)
  {
    this->lcd_control = (LCD_Control *)this->memory->read_raw_byte(LCDC_POSITION);
    this->ly_c = this->memory->read_raw_byte(LY_C_POSITION);
    this->scroll_x = this->memory->read_raw_byte(SCROLL_X_POSITION);
    this->scroll_y = this->memory->read_raw_byte(SCROLL_Y_POSITION);
    this->scanline = this->memory->read_raw_byte(SCANLINE_POSITION);
    this->stat = this->memory->read_raw_byte(STAT_POSITION);
    this->window_x = this->memory->read_raw_byte(WINDOW_X_POSITION);
    this->window_y = this->memory->read_raw_byte(WINDOW_Y_POSITION);

    *(this->memory->read_raw_byte(LCDC_POSITION)) = 0x91;
    *(this->memory->read_raw_byte(BACKGROUND_PALETTE_POSITION)) = 0xFC;
    *(this->memory->read_raw_byte(SPRITE_0_PALETTE_POSITION)) = 0xFF;
    *(this->memory->read_raw_byte(SPRITE_1_PALETTE_POSITION)) = 0xFF;
    *(this->memory->read_raw_byte(SCANLINE_POSITION)) = 0x00;

    glGenTextures(1, &this->frame_texture);
    glBindTexture(GL_TEXTURE_2D, this->frame_texture);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, OUTPUT_WIDTH, OUTPUT_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    for (int y = 0; y < OUTPUT_HEIGHT; y++)
    {
      for (int x = 0; x < OUTPUT_WIDTH; x++)
      {
        this->pixels[this->getIndex(x, y)] = {0, 0, 0, 255};
      }
    }

    this->renderFramebuffer();
  }

  ~GPU()
  {
    glDeleteTextures(1, &this->frame_texture);
  }

  unsigned long *ticks;

  uint32_t gpu_ticks = 29;
  unsigned long previous_ticks = 0;

  LCD_Control *lcd_control;
  uint8_t *scanline;
  uint8_t *stat;
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

  bool executeGPU(unsigned long ticks_elapsed)
  {
    this->gpu_ticks += ticks_elapsed;

    switch (this->current_mode)
    {
    case GPU_mode::H_BLANK:
      if (this->gpu_ticks >= 204)
      {
        *(this->scanline) += 1;

        if (*(this->scanline) == 143)
        {
          if (this->cpu->registrers.ime && *(this->cpu->interrupt_enable) & INTERRUPT_VBLANK)
          {
            *(this->cpu->interrupt_flags) |= INTERRUPT_VBLANK;
          }

          this->current_mode = GPU_mode::V_BLANK;
        }
        else
        {
          this->current_mode = GPU_mode::OAM;
        }
        this->gpu_ticks -= 204;
      }
      break;
    case GPU_mode::V_BLANK:
      if (this->gpu_ticks >= 456)
      {
        *(this->scanline) += 1;

        if (*(this->scanline) > 153)
        {
          *(this->scanline) = 0;
          this->current_mode = GPU_mode::OAM;
        }

        this->gpu_ticks -= 456;
      }
      break;
    case GPU_mode::OAM:
      if (this->gpu_ticks >= 80)
      {
        this->current_mode = GPU_mode::VRAM;

        this->gpu_ticks -= 80;
      }
      break;
    case GPU_mode::VRAM:
      if (this->gpu_ticks >= 172)
      {
        this->current_mode = GPU_mode::H_BLANK;
        this->renderScanline();
        this->gpu_ticks -= 172;
      }
      break;
    }

    *(this->stat) &= 0b11111000;
    *(this->stat) |= (int)this->current_mode;
    *(this->stat) |= (*(this->scanline) == *(this->ly_c)) << 2;

    return true;
  }

  void renderScanline()
  {
    if ((*(this->lcd_control)).bg_window_display)
    {
      // Tiles display

      bool using_window = false;
      if ((*(this->lcd_control)).window_display && *(this->window_y) <= *(this->scanline))
      {
        using_window = true;
      }

      bool sign = false;
      uint16_t tile_data_position;
      if ((*(this->lcd_control)).bg_window_tile_data_select)
      {
        tile_data_position = 0x8000;
      }
      else
      {
        tile_data_position = 0x8800;
        sign = true;
      }

      uint16_t background_map_position;
      if ((!using_window && (*(this->lcd_control)).bg_tile_map_select) || (using_window && (*(this->lcd_control)).window_tile_map_select))
      {
        background_map_position = 0x9C00;
      }
      else
      {
        background_map_position = 0x9800;
      }

      uint8_t y_position;
      if (!using_window)
      {
        y_position = *(this->scroll_y) + *(this->scanline);
      }
      else
      {
        y_position = *(this->scanline) - *(this->window_y);
      }

      int tile_row = y_position / 8 * 32;

      for (int pixel = 0; pixel < OUTPUT_WIDTH; pixel++)
      {

        uint8_t x_position = pixel + *(this->scroll_x);

        // translate the current x pos to window space if necessary
        if (using_window && pixel >= *(this->window_x))
        {
          x_position = pixel - *(this->window_x);
        }

        // Check bounds
        if ((x_position < 0) || (x_position > 159))
        {
          continue;
        }

        int tile_col = (x_position / 8);
        int tile_number;

        uint16_t tile_address = background_map_position + tile_row + tile_col;
        if (sign)
        {
          tile_number = (int8_t)this->memory->read_byte(tile_address);
        }
        else
        {
          tile_number = (uint8_t)this->memory->read_byte(tile_address);
        }

        // deduce where this tile identifier is in memory
        uint16_t tile_location = tile_data_position;

        if (sign)
        {
          tile_location += ((tile_number + 128) * 16);
        }
        else
        {
          tile_location += (tile_number * 16);
        }

        //std::cout << "Using tile: " << std::dec << tile_number << " With number: " << std::dec << tile_number << " and location: 0x" << std::hex << tile_location << std::endl;

        // find the correct vertical line we're on of the
        // tile to get the tile data
        // from in memory
        uint8_t line = y_position % 8;
        line *= 2; // each vertical line takes up two bytes of memory
        uint8_t data1 = this->memory->read_byte(tile_location + line);
        uint8_t data2 = this->memory->read_byte(tile_location + line + 1);

        // pixel 0 in the tile is it 7 of data 1 and data2.
        // Pixel 1 is bit 6 etc..
        int color_bit = x_position % 8;
        color_bit = 7 - color_bit;

        // combine data 2 and data 1 to get the colour id for this pixel
        // in the tile
        uint8_t pixel_color = data2 >> color_bit & 0x01;
        pixel_color <<= 1;
        pixel_color |= data1 >> color_bit & 0x01;

        Color color = getColorFromPalette(pixel_color, BACKGROUND_PALETTE_POSITION);

        this->pixels[this->getIndex(pixel, *(this->scanline))] = color;
        //std::cout << "Updating scan line " << (int)*(this->scanline) << " Palette: " << (int)color_palette << " " << (int)color.r << " " << (int)color.g << " " << (int)color.b << " " << (int)this->pixels[OUTPUT_WIDTH * *(this->scanline) + pixel].r << std::endl;
      }
    }

    if ((*(this->lcd_control)).sprite_display)
    {
      // Sprites display
      bool use_large_sprites = (*(this->lcd_control)).sprite_size;
      uint8_t y_size = use_large_sprites ? 16 : 8;

      std::multiset<Sprite *, decltype(&compare_sprites)> sprites_on_scanline(&compare_sprites);
      for (uint8_t sprite_num = 0; sprite_num < 40; sprite_num++)
      {
        uint8_t index = sprite_num * sizeof(Sprite);
        Sprite *sprite = (Sprite *)this->memory->read_raw_byte(OAM_LOCATION + index);
        //std::cout << std::dec << "Sprite: " << (int)sprite_num << " x pos: " << (int)sprite->x_pos << " y pos: " << (int)sprite->y_pos << " data: 0x" << std::hex << (int)this->memory[OAM_LOCATION + index] << this->memory[OAM_LOCATION + index + 1] << this->memory[OAM_LOCATION + index + 2] << this->memory[OAM_LOCATION + index + 3] << std::endl;
        if (*(this->scanline) >= sprite->y_pos - 16 && *(this->scanline) < sprite->y_pos + y_size - 16)
        {
          //std::cout << "Sprite on scanline " << (int)*(this->scanline) << " " << (int)sprite_num << std::endl;
          sprites_on_scanline.insert(sprite);
        }
      }

      if (sprites_on_scanline.size() != 0)
      {
        auto sprites_iterator = sprites_on_scanline.rbegin();
        int sprites_to_advance = (int)sprites_on_scanline.size() - MAX_SPRITES_PER_SCANLINE;
        if (false && sprites_to_advance > 0)
        {
          std::advance(sprites_iterator, sprites_to_advance);
        }
        for (; sprites_iterator != sprites_on_scanline.rend(); std::advance(sprites_iterator, 1))
        {
          Sprite sprite = **sprites_iterator;
          int line = *(this->scanline) - (sprite.y_pos - 16);

          if (sprite.y_flip)
          {
            line = y_size - line - 1;
          }

          line *= 2;

          uint16_t sprite_data_address = (VRAM_POSITION + (sprite.tile_location * y_size * 2)) + line;
          uint8_t data1 = this->memory->read_byte(sprite_data_address);
          uint8_t data2 = this->memory->read_byte(sprite_data_address + 1);

          for (int8_t pixel = 7; pixel >= 0; pixel--)
          {
            int16_t x_position = (sprite.x_pos - 8) + 7 - pixel;
            if (x_position < 0 || x_position >= OUTPUT_WIDTH)
            {
              continue;
            }

            //std::cout << "Rendering pixel " << std::dec << 7 - (int)pixel << " at " << (sprite.x_pos - 8) + 7 - pixel << std::endl;
            int color_bit = pixel;
            if (sprite.x_flip)
            {
              color_bit = 7 - color_bit;
            }

            uint8_t pixel_color = data2 >> color_bit & 0x01;
            pixel_color <<= 1;
            pixel_color |= data1 >> color_bit & 0x01;

            uint16_t sprite_palette = sprite.palette ? SPRITE_1_PALETTE_POSITION : SPRITE_0_PALETTE_POSITION;

            Color color = getColorFromPalette(pixel_color, sprite_palette);

            if (color == palette[0] || (sprite.priority && this->pixels[this->getIndex(x_position, *(this->scanline))] != palette[0]))
            {
              continue;
            }

            this->pixels[this->getIndex(x_position, *(this->scanline))] = color;
          }
        }
      }
    }
  }

  Color getColorFromPalette(uint8_t color, uint16_t palette_address)
  {
    uint8_t color_position = color * 2;
    uint8_t color_palette = this->memory->read_byte(palette_address) >> (color_position + 1) & 0x01;
    color_palette <<= 1;
    color_palette |= this->memory->read_byte(palette_address) >> color_position & 0x01;

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
  std::string mode;
  switch (gpu.current_mode)
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
  o << std::dec << "Mode: " << mode << std::endl;
  o << std::dec << "Scan line: " << (int)*(gpu.scanline) << std::endl;
  o << std::dec << "LCDC: " << std::bitset<8>((*(bool *)(gpu.lcd_control))) << std::endl;
  o << std::dec << "STAT: " << std::bitset<8>(*(gpu.stat)) << std::endl;
  o << std::endl;
  return o;
}
