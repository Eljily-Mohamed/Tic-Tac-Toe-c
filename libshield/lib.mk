
UDEFS += -DUSE_MBEDSHIELD

LIBSHIELD = libshield

SRC += $(LIBSHIELD)/leds.c $(LIBSHIELD)/sw.c \
       $(LIBSHIELD)/lcd_128x32.c $(LIBSHIELD)/libshield.c
