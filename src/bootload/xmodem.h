#ifndef _XMODEM_H_INCLUDED_
#define _XMODEM_H_INCLUDED_

#ifdef __cplusplus
extern "C"
{
#endif

    // XMODEM によるファイルの受信
    long xmodem_recv(char *buf);

#ifdef __cplusplus
}
#endif

#endif
