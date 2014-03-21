/*
 * main.cc
 *
 *  Created on: Mar 13, 2014
 *      Author: domahony
 */

#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>
#include <unistd.h>
#include <cmath>
#include "nmea/parser.h"
#include "nmea/sentence.h"
#include "nmea/info.h"
#include <string>
#include <cstring>
#include <ncurses/ncurses.h>
#include "Display.h"
#include "NCursesDisplay.h"
#include "LCDDisplay.h"

int
main(int argc, char**argv)
{
	wiringPiSetup();

	Display *display = new LCDDisplay();

	int fd = serialOpen(argv[1], 9600);

	if (fd == -1) {
		delete display;
		return -1;
	}

	nmeaPARSER p;
	nmea_parser_init(&p);
	nmeaINFO info;
	nmea_zero_INFO(&info);

	std::string buf;
	while (true) {

		int c = serialGetchar(fd);
		switch (c) {
		case -1:
			break;
		case '\n':
			buf.push_back(c);
			display->do_output(&p, &info, buf);
			buf.clear();
			break;
		default:
			buf.push_back(c);
			break;
		}
		display->refresh_display();
	}

	delete display;
	return 0;
}
