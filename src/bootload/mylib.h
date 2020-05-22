#ifndef _LIB_H_INCLUDED_
#define _LIB_H_INCLUDED_

#ifdef __cplusplus
extern "C"
{
#endif

    void *my_memset(void *b, int c, long len);
    void *my_memcpy(void *dst, const void *src, long len);
    int my_memcmp(const void *b1, const void *b2, long len);
    int my_strlen(const char *s);
    char *my_strcpy(char *dst, const char *src);
    int my_strcmp(const char *s1, const char *s2);
    int my_strncmp(const char *s1, const char *s2, int len);

    // 1文字送信
    int my_putc(unsigned char c);
    // 1文字受信
    unsigned char my_getc(void);
    // 文字列送信
    int my_puts(unsigned char *str);
    // 文字列受信
    int my_gets(unsigned char *buf);

    // 数値の16進表示
    int my_putxval(unsigned long value, int column);

#ifdef __cplusplus
}
#endif

#endif
