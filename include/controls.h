#pragma once

struct Keys
{
  struct
  {
    union {
      uint8_t pad_bool;
      struct
      {
        bool right : 1;
        bool left : 1;
        bool up : 1;
        bool down : 1;
        uint8_t _pad : 4;
      };
    };
  } p14;
  struct
  {
    union {
      uint8_t pad_bool;
      struct
      {
        bool a : 1;
        bool b : 1;
        bool select : 1;
        bool start : 1;
        uint8_t _pad : 4;
      };
    };
  } p15;
};
