#include "defines.h"
#include "serial.h"
#include "mylib.h"

// メモリを特定パターンで埋める
void *my_memset(void *b, int c, long len)
{
    char *p;
    for (p = b; len > 0; len--)
        *(p++) = c;
    return b;
}

// メモリのコピーを行う
void *my_memcpy(void *dst, const void *src, long len)
{
    char *d = dst;
    const char *s = src;
    for (; len > 0; len--)
        *(d++) = *(s++);
    return dst;
}

// メモリ上のデータの比較を行う
int my_memcmp(const void *b1, const void *b2, long len)
{
    const char *p1 = b1, *p2 = b2;
    for (; len > 0; len--)
    {
        if (*p1 != *p2)
            return (*p1 > *p2) ? 1 : -1;
        p1++;
        p2++;
    }
    return 0;
}

// 文字列の長さを返す
int my_strlen(const char *s)
{
    int len;
    for (len = 0; *s; s++, len++)
        ;
    return len;
}

// 文字列のコピーを行う
char *my_strcpy(char *dst, const char *src)
{
    char *d = dst;
    for (;; dst++, src++)
    {
        *dst = *src;
        if (!*src)
            break;
    }
    return d;
}

// 文字列の比較を行う
int my_strcmp(const char *s1, const char *s2)
{
    while (*s1 || *s2)
    {
        if (*s1 != *s2)
            return (*s1 > *s2) ? 1 : -1;
        s1++;
        s2++;
    }
    return 0;
}

// 長さ制限有りで文字列の比較を行う
int my_strncmp(const char *s1, const char *s2, int len)
{
    while ((*s1 || *s2) && (len > 0))
    {
        if (*s1 != *s2)
            return (*s1 > *s2) ? 1 : -1;
        s1++;
        s2++;
        len--;
    }
    return 0;
}

// 1文字送信
int my_putc(unsigned char c)
{
    if (c == '\n')
        serial_send_byte(SERIAL_DEFAULT_DEVICE, '\r');
    return serial_send_byte(SERIAL_DEFAULT_DEVICE, c);
}

unsigned char my_getc(void)
{
    unsigned char c = serial_recv_byte(SERIAL_DEFAULT_DEVICE);
    c = (c == '\r') ? '\n' : c;
    // エコーバック
    my_putc(c);
    return c;
}

// 文字列送信
int my_puts(unsigned char *str)
{
    while (*str)
        my_putc(*(str++));
    return 0;
}

// 文字列受信
int my_gets(unsigned char *buf)
{
    int i = 0;
    unsigned char c;
    do
    {
        // 1文字受信
        c = my_getc();
        // 改行コードは削る
        if (c == '\n')
            c = '\0';
        buf[i++] = c;
    } while (c);
    return i - 1;
}

// 数値の16進数表示
int my_putxval(unsigned long value, int column)
{

    // 文字列出力用のバッファ
    char buf[9];
    char *p;

    // 下の桁から処理するので、バッファの終端から利用する
    p = buf + sizeof(buf) - 1;
    *(p--) = '\0';
    if (!value && !column)
        column++;

    char arr[16];
    // char a[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    my_memcpy(&arr, "0123456789abcdef", sizeof(char) * 16);
    while (value || column)
    {
        // 16進文字に変換してバッファに格納する
        //*(p--) = arr[value & 0xf];
        // 次の桁に進める
        value >>= 4;
        // 桁数指定がある場合はカウントする
        if (column)
            column--;
    }

    // バッファの内容を出力する
    // MEMO: p-- で終端から開始しているので先頭は p+1 になる
    my_puts(p + 1);

    return 0;
}
