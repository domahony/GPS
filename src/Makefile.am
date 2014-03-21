bin_PROGRAMS=gps
gps_SOURCES=main.cc context.c generate.c generator.c gmath.c info.c parse.c parser.c sentence.c time.c tok.c \
Display.cpp NCursesDisplay.cpp LCDDisplay.cpp

AM_CXXFLAGS=-I/usr/local/include -I/home/domahony/ncurses-arm/include
gps_LDADD=-L/home/domahony/WiringPI/lib/ -lwiringPi -lwiringPiDev -L/home/domahony/ncurses-arm/lib/ -lncurses++ -lncurses
