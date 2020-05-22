#ifndef _DEFINES_H_INCLUDED_
#define _DEFINES_H_INCLUDED_

#ifdef __cplusplus
extern "C"
{
#endif

// NULL ポインタの定義
#define NULL ((void *)0)
// 標準のシリアルデバイス
#define SERIAL_DEFAULT_DEVICE 1

    // ビット幅固定の整数型
    typedef unsigned char uint8;
    typedef unsigned short uint16;
    typedef unsigned long uint32;

#ifdef __cplusplus
}
#endif

#endif
