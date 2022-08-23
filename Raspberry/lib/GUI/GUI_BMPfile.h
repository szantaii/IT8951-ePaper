/*****************************************************************************
* | File          :   GUI_BMPfile.h
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master
*                and enhance portability
*----------------
* |    This version:   V2.0
* | Date        :   2018-11-12
* | Info        :
* 1.Change file name: GUI_BMP.h -> GUI_BMPfile.h
* 2.fix: GUI_ReadBmp()
*   Now Xstart and Xstart can control the position of the picture normally,
*   and support the display of images of any size. If it is larger than
*   the actual display range, it will not be displayed.
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
#ifndef __GUI_BMPFILE_H
#define __GUI_BMPFILE_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

#include "../Config/DEV_Config.h"

extern uint8_t *bmp_dst_buf;
extern uint8_t *bmp_src_buf;

/*Bitmap file header   14bit*/
typedef struct
{
    uint16_t bType;                        //File identifier, as for bmp is:0x4D42
    uint32_t bSize;                      //The size of the file
    uint16_t brgbReversed1;                   //rgbReversed value, must be set to 0
    uint16_t brgbReversed2;                   //rgbReversed value, must be set to 0
    uint32_t bOffset;                       //The offset from the beginning of the file header to the beginning of the image data bit
}__attribute__((packed)) BMPFILEHEADER; //Tell the compiler to cancel optimal alignment of the structure during compilation


/*Bitmap information header  40bit*/
typedef struct
{
    uint32_t biInfoSize;                   //The size of the header: 40
    uint32_t biWidth;                      //The width of the image
    uint32_t biHeight;                      //The height of the image
    uint16_t biPlanes;                          //The number of target planes in the image
    uint16_t biBitCount;                      //The number of bits per pixel
    uint32_t biCompression;                //Compression type
    uint32_t bimpImageSize;                //The size of the image in bytes. The data must be a multiple of 4.
    uint32_t biXPelsPerMeter;              //Number of horizontal pixel of the target device per meter
    uint32_t biYPelsPerMeter;              //Number of vertical pixel of the target device per meter
    uint32_t biClrUsed;                    //Number of colors for bitmap used in color palette
    uint32_t biClrImportant;               //Specifies the number of important colors. When the value of this field is equal to the number of colors (or equal to 0), it means that all colors are equally important.
}__attribute__((packed)) BMPINFOHEADER;//Tell the compiler to cancel optimal alignment of the structure during compilation

typedef struct
{
    uint8_t rgbBlue;                  //rgbBlue intensity
    uint8_t rgbGreen;                 //rgbGreen intensity
    uint8_t rgbRed;                   //rgbRed intensity
    uint8_t rgbReversed;              //rgbReversed value
}__attribute__((packed)) BMPRGBQUAD;//Tell the compiler to cancel optimal alignment of the structure during compilation

uint8_t GUI_ReadBmp(const char *path, uint16_t x, uint16_t y);

#endif
