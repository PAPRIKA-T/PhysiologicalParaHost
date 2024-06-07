#pragma once
typedef signed char         i8;
typedef signed short        i16;
typedef signed int          i32;
typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;

typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      HWORD;  //两个字节组成一个半字
typedef unsigned int        WORD;   //四个字节组成一个字
typedef long                LONG;

#define LOHWORD(w)          ((HWORD)(w))                            //字的低半字 
#define HIHWORD(w)          ((HWORD)(((WORD)(w) >> 16) & 0xFFFF))   //字的高半字

#define LOBYTE(hw)          ((BYTE)(hw) )                           //半字的低字节
#define HIBYTE(hw)          ((BYTE)(((WORD)(hw) >> 8) & 0xFF))      //半字的高字节

//两个字节组成一个半字
#define MAKEHWORD(bH, bL)   ((HWORD)(((BYTE)(bL)) | ((HWORD)((BYTE)(bH))) << 8))

//两个半字组成一个字
#define MAKEWORD(hwH, hwL)  ((WORD)(((HWORD)(hwL)) | ((WORD)((HWORD)(hwH))) << 16))

#define TRUE          1
#define FALSE         0
#define NULL          0
#define INVALID_DATA  -100
