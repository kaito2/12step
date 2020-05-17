PREFIX = ../../../tools
ARCH = h8300-elf
BINDIR = ${PREFIX}/bin
ADDNAME = ${ARCH}-

# 利用するツール群の指定
AR = ${BINDIR}/${ADDNAME}ar
AS = ${BINDIR}/${ADDNAME}as
CC = ${BINDIR}/${ADDNAME}gcc
LD = ${BINDIR}/${ADDNAME}ld
NM = ${BINDIR}/${ADDNAME}nm
OBJCOPY = ${BINDIR}/${ADDNAME}objcopy
OBJDUMP = ${BINDIR}/${ADDNAME}objdump
RANLIB = ${BINDIR}/${ADDNAME}ranlib
STRIP = ${BINDIR}/${ADDNAME}strip

# フラッシュROM書き込みツール
H8WRITE = ${PREFIX}/kz_h8write

# シリアル接続先
H8WRITE_SERDEV = /dev/tty.usbserial-FTSXFJAF

# コンパイルするソースコード群
OBJS = vector.o startup.o main.o
OBJS += lib.o serial.o


TARGET = kzload

# コンパイルオプション
CFLAGS = -Wall -mh -nostdinc -nostdlib -fno-builtin
# CFLAGS += -mint32 # int を 32 ビットにすると掛け算割り算ができなくなる
CFLAGS += -I.
CFLAGS += -Os
CFLAGS += -DKZLOAD

# リンクオプション
LFLAGS = -static -T ld.scr -L.

.SUFFIXES: .c .o
.SUFFIXES: .s .o

all : 			$(TARGET)

# 実行形式の生成ルール
$(TARGET) : 	$(OBJS)
				$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LFLAGS)
				cp $(TARGET) $(TARGET).elf
				$(STRIP) $(TARGET)

# *.c ファイルのコンパイル・ルール
.c.o : 			$<
				$(CC) -c $(CFLAGS) $<

# アセンブラファイルのアセンブル・ルール
.s.o :	 		$<
				$(CC) -c $(CFLAGS) $<

# モトローラSレコード・フォーマットへの変換
$(TARGET).mot :	$(TARGET)
				$(OBJCOPY) -O srec $(TARGET) $(TARGET).mot

image : 		$(TARGET).mot

# フラッシュROMへの転送
write :			$(TARGET).mot
				$(H8WRITE) -3069 -f20 $(TARGET).mot $(H8WRITE_SERDEV)

# フォルダの掃除
clean : 
				rm -f $(OBJS) $(TARGET) $(TARGET).elf $(TARGET).mot
