#ifndef __EXAMPLE__
#define __EXAMPLE__

#include "../lib/e-Paper/EPD_IT8951.h"
#include "../lib/Config/DEV_Config.h"

// 1 bit per pixel, which is 2 grayscale
#define BitsPerPixel_1 1
// 2 bit per pixel, which is 4 grayscale
#define BitsPerPixel_2 2
// 4 bit per pixel, which is 16 grayscale
#define BitsPerPixel_4 4
// 8 bit per pixel, which is 256 grayscale, but will automatically reduce by hardware to 4bpp, which is 16 grayscale
#define BitsPerPixel_8 8

// For all refresh fram buf except touch panel
extern uint8_t *Refresh_Frame_Buf;

// Only for touch panel
extern uint8_t *Panel_Frame_Buf;
extern uint8_t *Panel_Area_Frame_Buf;

extern bool Four_Byte_Align;

uint8_t Display_ColorPalette_Example(uint16_t Panel_Width, uint16_t Panel_Height, uint32_t Init_Target_Memory_Addr);

uint8_t Display_CharacterPattern_Example(uint16_t Panel_Width, uint16_t Panel_Height, uint32_t Init_Target_Memory_Addr, uint8_t BitsPerPixel);

uint8_t Display_BMP_Example(uint16_t Panel_Width, uint16_t Panel_Height, uint32_t Init_Target_Memory_Addr, uint8_t BitsPerPixel);

uint8_t Dynamic_Refresh_Example(IT8951_Dev_Info Dev_Info, uint32_t Init_Target_Memory_Addr);

uint8_t Dynamic_GIF_Example(uint16_t Panel_Width, uint16_t Panel_Height, uint32_t Init_Target_Memory_Addr);

uint8_t Check_FrameRate_Example(uint16_t Panel_Width, uint16_t Panel_Height, uint32_t Target_Memory_Addr, uint8_t BitsPerPixel);

uint8_t TouchPanel_ePaper_Example(uint16_t Panel_Width, uint16_t Panel_Height, uint32_t Init_Target_Memory_Addr);

void Factory_Test_Only(IT8951_Dev_Info Dev_Info, uint32_t Init_Target_Memory_Addr);
void Color_Test(IT8951_Dev_Info Dev_Info, uint32_t Init_Target_Memory_Addr);

#endif
