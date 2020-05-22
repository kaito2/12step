#include "defines.h"
#include "serial.h"
#include "xmodem.h"
#include "mylib.h"

int init(void)
{
    // リンカ・スクリプトで定義してあるシンボルを参照可能にする。
    extern int erodata, data_start, edata, bss_start, ebss;

    /*
     * データ領域とBSS領域を初期化する。この処理以降でないと、
     * グローバル変数が初期化されていないので注意。
     */

    // 静的領域（データ領域・BSS領域）を初期化する。
    my_memcpy(&data_start, &erodata, (long)&edata - (long)&data_start);
    my_memset(&bss_start, 0, (long)&ebss - (long)&bss_start);

    // シリアルの初期化
    serial_init(SERIAL_DEFAULT_DEVICE);

    return 0;
}

// メモリの16進ダンプ出力
static int dump(char *buf, long size)
{
    long i;
    if (size < 0)
    {
        my_puts("no data.\n");
        return -1;
    }
    for (i = 0; i < size; i++)
    {
        my_putxval(buf[i], 2);
        if ((i & 0xf) == 15)
        {
            my_puts("\n");
        }
        else
        {
            if ((i & 0xf) == 7)
                my_puts(" ");
            my_puts(" ");
        }
    }
    my_puts("\n");

    return 0;
}

// ウェイト用のサービス関数を追加
static void wait()
{
    volatile long i;
    for (i = 0; i < 300000; i++)
        ;
}

int main(void)
{
    static char buf[16];
    static long size = -1;
    static unsigned char *loadbuf = NULL;
    // リンカ・スクリプトで定義されているバッファ
    static int buffer_start;

    init();

    my_puts("kzload (kozos boot loader) started.\n");

    while (1)
    {
        // プロンプトの表示
        my_puts("kzload> ");
        // シリアルからのコマンド受信
        my_gets(buf);

        // XMODEMでのファイルのダウンロード
        if (!my_strcmp(buf, "load"))
        {
            loadbuf = (char *)(&buffer_start);
            my_puts("cmodem_recv is start...\n"); // TODO: remove debug print
            size = xmodem_recv(loadbuf);
            my_puts("cmodem_recv is done!!\n"); // TODO: remove debug print
            // 転送アプリが終了し、端末アプリに制御が戻るまで待ち合わせる
            wait();
            if (size < 0)
            {
                my_puts("\nXMODEM receive error!\n");
            }
            else
            {
                my_puts("\nXMODEM receive succeeded.\n");
            }
        }
        // メモリの16新ダンプを出力
        else if (!my_strcmp(buf, "dump"))
        {
            my_puts("size: ");
            my_putxval(size, 0);
            my_puts("\n");
            dump(loadbuf, size);
        }
        else
        {
            my_puts("unknown.\n");
        }
    }

    return 0;
}
