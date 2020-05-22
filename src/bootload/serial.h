#ifndef _SERIAL_H_INCLUDED_
#define _SERIAL_H_INCLUDED_

#ifdef __cplusplus
extern "C"
{
#endif

    // デバイス初期化
    int serial_init(int index);
    // 送信可能かを確認
    int serial_is_send_enable(int index);
    // 1文字送信
    int serial_send_byte(int index, unsigned char b);
    // 受信可能かを確認
    int serial_is_recv_enable(int index);
    // 1文字受信
    unsigned char serial_recv_byte(int index);

#ifdef __cplusplus
}
#endif

#endif
