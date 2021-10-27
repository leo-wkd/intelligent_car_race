#include "Drive.h"
uint8 my_CAR[128*8] =
{
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0xFC,0xFE,0x0E,0x1C,
      0x18,0x1C,0x0E,0xFE,0xFC,0x00,0x7C,0xFC,
      0x80,0xFC,0xFC,0x00,0x00,0x00,0x7C,0xFE,
      0xC6,0xC6,0xC6,0x00,0x40,0xE8,0xA8,0xF8,
      0xF0,0x00,0xF8,0xF8,0x10,0x18,0x00,0x00,
      0xC0,0xC0,0x00,0xC0,0xC0,0x00,0xC0,0xC0,
      0x00,0x00,0x06,0x09,0x12,0x09,0x06,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x40,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,
      0x12,0x22,0x44,0x22,0x12,0x0C,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0xFE,0x04,0x08,
      0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x81,0x41,0x40,0x80,0x40,
      0x40,0x80,0x01,0x01,0x00,0x04,0x05,0x05,
      0x07,0x03,0xC0,0x20,0x40,0x20,0xC1,0x01,
      0x01,0x01,0x00,0x00,0x01,0x01,0x01,0x81,
      0x80,0x81,0xC1,0xC0,0x40,0xC0,0xC0,0xE1,
      0xE1,0xE0,0xE1,0xE1,0xE0,0xE1,0xE1,0xE0,
      0xE0,0xE0,0x60,0x60,0x40,0x40,0xC0,0xE0,
      0xE0,0xA0,0x90,0x8C,0x02,0x01,0x00,0x00,
      0x00,0x00,0x00,0x10,0x28,0x50,0x28,0x10,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,
      0x00,0x00,0x00,0x01,0x02,0x04,0x08,0x10,
      0x20,0x40,0xFF,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x01,0x02,0x04,0x08,0x04,0x02,
      0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x01,0xC2,0xE1,0xF0,0x30,0x18,
      0x08,0x3C,0xF6,0xFE,0xFB,0x1D,0x0D,0x02,
      0xC2,0xCB,0x09,0x09,0x09,0x09,0x08,0x08,
      0x08,0x08,0x08,0x08,0x00,0xC0,0xFF,0xFC,
      0xFC,0xF9,0xE1,0xC1,0x11,0x12,0x02,0xC6,
      0xC5,0xC9,0xD9,0xF3,0xE3,0xC6,0x0E,0x0C,
      0x1C,0x38,0x38,0xF0,0xE0,0xC0,0x00,0x00,
      0x00,0x00,0x00,0x00,0x0C,0x12,0x24,0x12,
      0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x08,0x10,0x20,0x40,0x80,
      0x00,0x00,0x00,0x00,0x00,0x80,0x40,0x20,
      0x10,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x80,0x40,0x70,0xF0,0x38,0x18,0x0C,
      0x0C,0x0E,0x0E,0x0E,0x86,0x8E,0x0B,0x0B,
      0x0B,0x03,0x13,0x31,0x36,0x57,0xE7,0x87,
      0x07,0x07,0x07,0x07,0x07,0x03,0x03,0x03,
      0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
      0x03,0x03,0x03,0x33,0x3B,0x33,0x33,0xF3,
      0x03,0x03,0x03,0x03,0x03,0x03,0x83,0x83,
      0xC3,0x63,0x33,0x91,0x91,0x89,0x08,0x00,
      0x84,0x84,0x84,0x85,0x87,0x07,0x07,0x06,
      0x1E,0x38,0x78,0xE0,0xC0,0x80,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x80,0x40,0x20,0x11,
      0x0A,0x04,0x0A,0x11,0x20,0x40,0x80,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x78,0xFC,0xEF,
      0xFF,0x7B,0x1B,0x08,0xF0,0xF8,0xFC,0xFE,
      0xFF,0xEF,0x0F,0x1F,0x1F,0x0F,0xFF,0xFF,
      0xFE,0xFC,0xF9,0xF2,0x04,0x00,0x03,0xFE,
      0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,
      0x00,0x00,0x00,0x00,0x9E,0x7F,0x73,0x18,
      0x0E,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0x0F,
      0x1F,0x1F,0x0F,0x7F,0xFF,0xFF,0xFE,0xFC,
      0xFC,0xF8,0x18,0xFD,0xFF,0xFF,0x7E,0x1C,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0xE2,0x21,0x20,0x20,0x20,0x20,0x20,
      0x20,0x20,0x40,0x80,0x00,0x00,0x01,0x02,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x27,
      0x26,0x30,0x30,0x3F,0x3F,0x3F,0x3F,0x3E,
      0x26,0x22,0x39,0x39,0x20,0x3C,0x3E,0x3F,
      0x3F,0x3F,0x3F,0x3E,0x38,0x38,0x39,0x39,
      0x38,0x38,0x3A,0x3A,0x3A,0x3A,0x3A,0x3A,
      0x3A,0x3A,0x3A,0x3A,0x3A,0x3A,0x3B,0x3B,
      0x3B,0x3B,0x3B,0x3B,0x3B,0x39,0x38,0x38,
      0x39,0x39,0x39,0x39,0x38,0x38,0x38,0x3E,
      0x3F,0x3F,0x3F,0x3F,0x3E,0x3E,0x31,0x39,
      0x39,0x30,0x34,0x3E,0x3F,0x3F,0x3F,0x3F,
      0x3B,0x3A,0x33,0x33,0x31,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0xFF,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
      0x20,0x10,0x08,0x07,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
uint8 my_PIG[128*8] =
{
      0x00,0x8C,0x10,0x10,0x20,0x20,0x19,0x04,
      0x12,0x02,0xC0,0x02,0x11,0x00,0x00,0x00,
      0x00,0x40,0x18,0x20,0x5C,0x62,0x22,0x5C,
      0x40,0x24,0x10,0x90,0x21,0x02,0x04,0x04,
      0x00,0x00,0x00,0x00,0x02,0x10,0x00,0x00,
      0x00,0x00,0x40,0x18,0x20,0x5C,0x62,0x22,
      0x5C,0x40,0x24,0x10,0x90,0x21,0x02,0x04,
      0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x08,0xD4,0x32,0x12,0x8A,0x89,0x09,0x05,
      0x06,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
      0x08,0x08,0x08,0x10,0xF0,0x18,0x08,0x08,
      0x10,0x20,0x20,0xC0,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,
      0x40,0xB8,0xC4,0x44,0xB9,0x80,0x48,0x20,
      0x20,0x4B,0x0C,0xF8,0x09,0x08,0x08,0x88,
      0x78,0x00,0x00,0x00,0x20,0x28,0xA8,0xA8,
      0xA8,0xF8,0xA8,0xA8,0xA8,0x28,0x20,0x00,
      0x00,0x08,0x08,0x08,0x08,0xC8,0x48,0x28,
      0x18,0x08,0x00,0x00,0x00,0xE0,0xF0,0xF0,
      0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0xC0,0x3C,0x83,
      0x80,0x80,0x99,0x00,0x00,0x00,0x00,0x00,
      0xE0,0x00,0x00,0x02,0x0C,0x00,0x00,0x00,
      0x00,0x00,0x80,0x03,0x00,0x00,0x02,0x02,
      0x0E,0xF1,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x80,
      0x00,0x00,0x00,0x00,0x20,0x00,0x00,0xA1,
      0xA0,0x90,0x90,0x8B,0x84,0x8A,0x91,0x90,
      0xA0,0xA0,0x00,0xA0,0x28,0x2F,0x2A,0x2A,
      0x3F,0x2A,0xAA,0x2F,0xA8,0x20,0x00,0x00,
      0x80,0x80,0xA0,0x20,0xBF,0x80,0x80,0x80,
      0x80,0x80,0x00,0x00,0x80,0x9B,0x9B,0x80,
      0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,
      0x00,0x00,0x00,0x3F,0x40,0x87,0x08,0x16,
      0x10,0x2C,0x21,0x21,0x22,0x9C,0x80,0x80,
      0x80,0x80,0x00,0x01,0x08,0x08,0x08,0x08,
      0x00,0x07,0x04,0x06,0x00,0x80,0x60,0x1E,
      0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x85,
      0x41,0x41,0x02,0x00,0x20,0x00,0x20,0x2E,
      0xAA,0xEA,0xBF,0x2A,0xAF,0x6A,0x2A,0x2E,
      0x20,0x00,0xE0,0x1B,0x80,0x7E,0xEA,0xAA,
      0xEA,0x3F,0xC2,0x23,0x9A,0x00,0x00,0xFF,
      0x24,0xFF,0x00,0xFF,0x08,0x0F,0x08,0x08,
      0x8F,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,
      0x04,0x02,0x01,0x00,0x00,0x00,0x00,0x00,
      0x00,0xC0,0x20,0x10,0x88,0x45,0x27,0x12,
      0x02,0x20,0x05,0x05,0x05,0x03,0x03,0x03,
      0x03,0x43,0x00,0x00,0x00,0x08,0x08,0x08,
      0x08,0x0C,0x0A,0x09,0x10,0x60,0x80,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x24,0x03,0x00,0x02,
      0x00,0x78,0x80,0x00,0x20,0x02,0x82,0x42,
      0x42,0x42,0x81,0x01,0x01,0x02,0x02,0x00,
      0x40,0x01,0x02,0x01,0x00,0x01,0xC0,0x22,
      0x21,0x20,0x41,0x83,0x00,0x03,0x00,0x02,
      0x23,0x00,0x03,0x02,0x02,0x02,0x02,0xC3,
      0x20,0x20,0x20,0x40,0x82,0x02,0x03,0x00,
      0x00,0x20,0x00,0x00,0x00,0x00,0x38,0x47,
      0xF0,0x04,0x03,0x02,0x02,0x04,0x05,0x05,
      0x06,0x02,0x0A,0x0A,0x0A,0x0A,0x04,0x04,
      0x14,0x14,0x14,0x14,0x1B,0x20,0xC0,0x00,
      0x00,0x00,0x00,0x00,0x00,0x01,0xFE,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x17,0x10,0x09,0x04,0x24,
      0x08,0x00,0x11,0x01,0x00,0x03,0x04,0x04,
      0x02,0x00,0x01,0x0A,0x02,0x02,0x04,0x00,
      0x00,0x00,0x08,0x00,0x00,0x01,0x02,0x02,
      0x01,0x00,0x20,0x05,0x01,0x01,0x02,0x00,
      0x20,0x00,0x00,0x08,0x00,0x00,0x01,0x02,
      0x02,0x01,0x00,0x20,0x05,0x01,0x01,0x02,
      0x00,0x20,0x00,0x00,0x00,0x00,0x1F,0x38,
      0x30,0x28,0x30,0x20,0x10,0x00,0x20,0x0C,
      0x10,0x30,0x20,0x00,0x20,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x3F,0x01,0x02,
      0x04,0x18,0x24,0x14,0x24,0x1F,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};


//��ʾ����

uint8 F14x16_Idx[] =
{
	"�����ܵĿ춼������"
};
uint8 F14x16[] = {//����32*32
	  0x00,0x00,0x00,0x60,0xE0,0xC0,0x00,0x00,//��
      0x00,0x00,0x00,0x0C,0xFC,0x78,0x00,0x00,
      0x00,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0xFF,0xFF,0x0C,0x0C,
      0x86,0x84,0x00,0xFC,0xFF,0x04,0x06,0x02,
      0x03,0x01,0x01,0x00,0xC0,0x00,0x00,0x00,
      0x00,0x00,0x18,0x1C,0x0F,0x06,0x03,0x01,
      0x00,0x00,0x00,0x01,0x07,0x0E,0x0C,0x1C,
      0x18,0x18,0x1C,0x1C,0x0F,0x0F,0x00,0x00,

 	  0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,//��
      0xC0,0xC0,0x01,0x7F,0xFE,0x00,0x00,0x10,
      0x30,0x70,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x30,0x31,0x31,0x11,0xFF,
      0xFE,0x88,0x48,0x0C,0x0F,0x7E,0xE6,0x82,
      0xF2,0x72,0x10,0x00,0x00,0x00,0x00,0x00,
      0x00,0x04,0x0C,0x06,0x06,0x13,0x61,0xFF,
      0x3F,0x00,0x00,0x08,0x0C,0x06,0x03,0x07,
      0x0C,0x38,0x70,0xE0,0xC0,0xF8,0xE0,0x00,

	  0x00,0x00,0x00,0x70,0xF0,0x30,0x10,0x90,//��
      0xF8,0x30,0x00,0x80,0xE0,0xF8,0xDF,0x4E,
      0x44,0x60,0xE0,0xE0,0x40,0x00,0x00,0x00,
      0x00,0x00,0x18,0xF8,0x03,0x03,0xFF,0x7D,
      0x11,0x10,0x8A,0xF9,0x48,0x6C,0x7C,0x2C,
      0x60,0xF8,0x3F,0x07,0x00,0x80,0x00,0x00,
      0x04,0x0C,0x06,0x07,0x03,0x03,0x03,0x01,
      0x01,0x00,0x01,0x0F,0x18,0x30,0x30,0x30,
      0x30,0x30,0x30,0x30,0x38,0x3F,0x1E,0x00,

 	  0x00,0x00,0x00,0x00,0x00,0xC0,0x78,0x38,//��
      0x18,0x00,0x00,0x00,0x00,0x80,0xF0,0x3E,
      0x0E,0x84,0x80,0x80,0x80,0x00,0x00,0x00,
      0x00,0x00,0x06,0xFE,0xFE,0x23,0x22,0x23,
      0xFF,0xFF,0x0A,0x0C,0x17,0x31,0x71,0x61,
      0x01,0x01,0x01,0xFF,0xFF,0x01,0x00,0x00,
      0x00,0x00,0x00,0x0F,0x0F,0x04,0x06,0x06,
      0x1F,0x0F,0x00,0x00,0x00,0x00,0x00,0x18,
      0x30,0x70,0x7E,0x3F,0x01,0x00,0x00,0x00,

 	  0x00,0x00,0x00,0x00,0x06,0xFE,0x8C,0x80,//��
      0x00,0x00,0x80,0x80,0xC3,0xFF,0x5E,0x40,
      0xE0,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,
      0x00,0x3C,0x1F,0x00,0x00,0xFF,0x00,0x31,
      0x31,0x30,0x30,0xF0,0xFF,0x3F,0xD0,0x90,
      0x1F,0x1F,0x18,0x18,0x18,0x18,0x00,0x00,
      0x00,0x00,0x00,0x00,0x3E,0x3F,0x00,0x10,
      0x18,0x0C,0x06,0x03,0x00,0x00,0x00,0x03,
      0x0E,0x1C,0x1C,0x18,0x18,0x10,0x10,0x00,

 	  0x00,0x00,0x00,0x00,0x00,0x40,0x60,0x61,//��
      0xFF,0x7F,0x20,0xB0,0xE0,0x38,0x10,0xC0,
      0xC0,0x40,0x60,0xE0,0xE0,0x60,0x00,0x00,
      0x00,0x04,0x0C,0x0C,0x84,0xC4,0xF6,0xB6,
      0xBF,0x9E,0x13,0xF3,0x72,0x03,0x02,0xFF,
      0xFF,0x80,0x0E,0x1B,0xF0,0xE0,0x00,0x00,
      0x00,0x04,0x02,0x03,0x01,0x00,0x1F,0x0D,
      0x04,0x04,0x1C,0x1F,0x00,0x00,0x00,0xFF,
      0xFF,0x00,0x01,0x03,0x07,0x07,0x00,0x00,

 	  0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x00,//��
      0x00,0x00,0x02,0xFF,0xFE,0x06,0x00,0x00,
      0x00,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x38,0xBF,0x1F,0x18,
      0x18,0x08,0x08,0xFF,0xFF,0x0C,0x04,0x04,
      0x04,0x9F,0x8F,0x01,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x30,0x3F,0x3F,0x18,
      0x18,0x18,0x08,0x0F,0x0F,0x0C,0x0C,0x04,
      0x04,0x0F,0x3F,0x1F,0x00,0x00,0x00,0x00,

 	  0x00,0x00,0x00,0x10,0x30,0x70,0x60,0x00,//��
      0x00,0x40,0x40,0x4C,0x58,0xE0,0xF0,0x28,
      0x2F,0x37,0x32,0x30,0x30,0x00,0x00,0x00,
      0x00,0x00,0x08,0x0C,0x7C,0xFC,0x0C,0x00,
      0x00,0x00,0x0E,0xFE,0x4B,0x6B,0x2A,0x21,
      0x2F,0xFF,0x82,0x00,0x00,0x00,0x00,0x00,
      0x00,0x04,0x0C,0x0C,0x04,0x07,0x04,0x0C,
      0x08,0x08,0x19,0x1B,0x11,0x31,0x31,0x31,
      0x33,0x37,0x31,0x30,0x30,0x30,0x10,0x10,

 	  0x00,0x00,0x00,0xF8,0xF0,0x18,0x88,0xF8,//��
      0x3C,0x18,0x00,0x00,0x00,0xFC,0xFC,0x1C,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0xFF,0xFF,0x00,0x08,0x1F,
      0x1E,0x00,0x00,0xC0,0xFC,0x1F,0x1F,0x30,
      0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x1F,0x1F,0x00,0x00,0x08,
      0x0C,0x06,0x03,0x01,0x00,0x00,0x00,0x00,
      0x00,0x03,0x07,0x07,0x06,0x06,0x04,0x04
};