/*****************************************************************************
* | File          :   EPD_IT8951.h
* | Author      :   Waveshare team
* | Function    :   IT8951 Common driver
* | Info        :
*----------------
* |    This version:   V1.0
* | Date        :   2019-09-17
* | Info        :
* -----------------------------------------------------------------------------
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef __EPD_IT8951_H_
#define __EPD_IT8951_H_

#include <stdbool.h>

#include "../Config/DEV_Config.h"

// INIT mode, for every init or some time after A2 mode refresh
extern uint8_t INIT_Mode;
// GC16 mode, for every time to display 16 grayscale image
extern uint8_t GC16_Mode;
// A2 mode, for fast refresh without flash
extern uint8_t A2_Mode;

typedef struct IT8951_Load_Img_Info
{
    uint16_t Endian_Type;        // little or Big Endian
    uint16_t Pixel_Format;       // bpp
    uint16_t Rotate;             // Rotate mode
    uint8_t *Source_Buffer_Addr; // Start address of source Frame buffer
    uint32_t Target_Memory_Addr; // Base address of target image buffer
} IT8951_Load_Img_Info;

typedef struct IT8951_Area_Img_Info
{
    uint16_t Area_X;
    uint16_t Area_Y;
    uint16_t Area_W;
    uint16_t Area_H;
} IT8951_Area_Img_Info;

typedef struct IT8951_Dev_Info
{
    uint16_t Panel_W;
    uint16_t Panel_H;
    uint16_t Memory_Addr_L;
    uint16_t Memory_Addr_H;
    uint16_t FW_Version[8];
    uint16_t LUT_Version[8];
} IT8951_Dev_Info;

/*-----------------------------------------------------------------------
IT8951 Command defines
------------------------------------------------------------------------*/

// Built in I80 Command Code
#define IT8951_TCON_SYS_RUN        0x0001
#define IT8951_TCON_STANDBY        0x0002
#define IT8951_TCON_SLEEP          0x0003
#define IT8951_TCON_REG_RD         0x0010
#define IT8951_TCON_REG_WR         0x0011

#define IT8951_TCON_MEM_BST_RD_T   0x0012
#define IT8951_TCON_MEM_BST_RD_S   0x0013
#define IT8951_TCON_MEM_BST_WR     0x0014
#define IT8951_TCON_MEM_BST_END    0x0015

#define IT8951_TCON_LD_IMG         0x0020
#define IT8951_TCON_LD_IMG_AREA    0x0021
#define IT8951_TCON_LD_IMG_END     0x0022

// I80 User defined command code
#define USDEF_I80_CMD_DPY_AREA     0x0034
#define USDEF_I80_CMD_GET_DEV_INFO 0x0302
#define USDEF_I80_CMD_DPY_BUF_AREA 0x0037
#define USDEF_I80_CMD_VCOM         0x0039

/*-----------------------------------------------------------------------
 IT8951 Mode defines
------------------------------------------------------------------------*/

// Rotate mode
#define IT8951_ROTATE_0   0
#define IT8951_ROTATE_90  1
#define IT8951_ROTATE_180 2
#define IT8951_ROTATE_270 3

// Pixel mode (Bit per Pixel)
#define IT8951_2BPP 0
#define IT8951_3BPP 1
#define IT8951_4BPP 2
#define IT8951_8BPP 3

// Endian Type
#define IT8951_LDIMG_L_ENDIAN 0
#define IT8951_LDIMG_B_ENDIAN 1

/*-----------------------------------------------------------------------
IT8951 Registers defines
------------------------------------------------------------------------*/
// Register Base Address
#define DISPLAY_REG_BASE 0x1000 // Register RW access

// Base Address of Basic LUT Registers
#define LUT0EWHR (DISPLAY_REG_BASE + 0x00)  // LUT0 Engine Width Height Reg
#define LUT0XYR (DISPLAY_REG_BASE + 0x40)   // LUT0 XY Reg
#define LUT0BADDR (DISPLAY_REG_BASE + 0x80) // LUT0 Base Address Reg
#define LUT0MFN (DISPLAY_REG_BASE + 0xC0)   // LUT0 Mode and Frame number Reg
#define LUT01AF (DISPLAY_REG_BASE + 0x114)  // LUT0 and LUT1 Active Flag Reg

// Update Parameter Setting Register
#define UP0SR (DISPLAY_REG_BASE + 0x134)     // Update Parameter0 Setting Reg
#define UP1SR (DISPLAY_REG_BASE + 0x138)     // Update Parameter1 Setting Reg
#define LUT0ABFRV (DISPLAY_REG_BASE + 0x13C) // LUT0 Alpha blend and Fill rectangle Value
#define UPBBADDR (DISPLAY_REG_BASE + 0x17C)  // Update Buffer Base Address
#define LUT0IMXY (DISPLAY_REG_BASE + 0x180)  // LUT0 Image buffer X/Y offset Reg
#define LUTAFSR (DISPLAY_REG_BASE + 0x224)   // LUT Status Reg (status of All LUT Engines)
#define BGVR (DISPLAY_REG_BASE + 0x250)      // Bitmap (1bpp) image color table

// System Registers
#define SYS_REG_BASE 0x0000

// Address of System Registers
#define I80CPCR (SYS_REG_BASE + 0x04)

// Memory Converter Registers
#define MCSR_BASE_ADDR 0x0200
#define MCSR (MCSR_BASE_ADDR + 0x0000)
#define LISAR (MCSR_BASE_ADDR + 0x0008)

/*
void EPD_IT8951_SystemRun();
void EPD_IT8951_Standby();
void EPD_IT8951_Sleep();

uint16_t EPD_IT8951_ReadReg(uint16_t Reg_Address);
void EPD_IT8951_WriteReg(uint16_t Reg_Address,uint16_t Reg_Value);
uint16_t EPD_IT8951_GetVCOM(void);
void EPD_IT8951_SetVCOM(uint16_t VCOM);

void EPD_IT8951_LoadImgStart( IT8951_Load_Img_Info* Load_Img_Info );
void EPD_IT8951_LoadImgAreaStart( IT8951_Load_Img_Info* Load_Img_Info, IT8951_Area_Img_Info* Area_Img_Info );
void EPD_IT8951_LoadImgEnd(void);

void EPD_IT8951_GetSystemInfo(void* Buf);
void EPD_IT8951_SetTargetMemoryAddr(uint32_t Target_Memory_Addr);
void EPD_IT8951_WaitForDisplayReady(void);


void EPD_IT8951_HostAreaPackedPixelWrite_8bp(IT8951_Load_Img_Info*Load_Img_Info,IT8951_Area_Img_Info*Area_Img_Info);

void EPD_IT8951_HostAreaPackedPixelWrite_1bp(IT8951_Load_Img_Info*Load_Img_Info,IT8951_Area_Img_Info*Area_Img_Info, bool Packed_Write);

void EPD_IT8951_HostAreaPackedPixelWrite_2bp(IT8951_Load_Img_Info*Load_Img_Info,IT8951_Area_Img_Info*Area_Img_Info, bool Packed_Write);

void EPD_IT8951_Display_Area(uint16_t X,uint16_t Y,uint16_t W,uint16_t H,uint16_t Mode);
void EPD_IT8951_Display_AreaBuf(uint16_t X,uint16_t Y,uint16_t W,uint16_t H,uint16_t Mode, uint32_t Target_Memory_Addr);

void EPD_IT8951_Display_1bp(uint16_t X, uint16_t Y, uint16_t W, uint16_t H, uint16_t Mode,uint32_t Target_Memory_Addr, uint8_t Front_Gray_Val, uint8_t Back_Gray_Val);
*/

void Enhance_Driving_Capability(void);

void EPD_IT8951_SystemRun(void);

void EPD_IT8951_Standby(void);

void EPD_IT8951_Sleep(void);

IT8951_Dev_Info EPD_IT8951_Init(uint16_t VCOM);

void EPD_IT8951_Clear_Refresh(IT8951_Dev_Info Dev_Info, uint32_t Target_Memory_Addr, uint16_t Mode);

void EPD_IT8951_1bp_Refresh(uint8_t *Frame_Buf, uint16_t X, uint16_t Y, uint16_t W, uint16_t H, uint8_t Mode, uint32_t Target_Memory_Addr, bool Packed_Write);
void EPD_IT8951_1bp_Multi_Frame_Write(uint8_t *Frame_Buf, uint16_t X, uint16_t Y, uint16_t W, uint16_t H, uint32_t Target_Memory_Addr, bool Packed_Write);
void EPD_IT8951_1bp_Multi_Frame_Refresh(uint16_t X, uint16_t Y, uint16_t W, uint16_t H, uint32_t Target_Memory_Addr);

void EPD_IT8951_2bp_Refresh(uint8_t *Frame_Buf, uint16_t X, uint16_t Y, uint16_t W, uint16_t H, bool Hold, uint32_t Target_Memory_Addr, bool Packed_Write);

void EPD_IT8951_4bp_Refresh(uint8_t *Frame_Buf, uint16_t X, uint16_t Y, uint16_t W, uint16_t H, bool Hold, uint32_t Target_Memory_Addr, bool Packed_Write);

void EPD_IT8951_8bp_Refresh(uint8_t *Frame_Buf, uint16_t X, uint16_t Y, uint16_t W, uint16_t H, bool Hold, uint32_t Target_Memory_Addr);

#endif
