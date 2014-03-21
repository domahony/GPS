/*
 * NCursesDisplay.h
 *
 *  Created on: Mar 17, 2014
 *      Author: domahony
 */

#ifndef NCURSESDISPLAY_H_
#define NCURSESDISPLAY_H_

#include <unistd.h>
#include <cmath>
#include "nmea/parser.h"
#include "nmea/sentence.h"
#include "nmea/info.h"
#include <string>
#include <cstring>
#include <ncurses/ncurses.h>
#include "Display.h"

class NCursesDisplay: public Display {
public:
	NCursesDisplay() {
		initscr();
		cbreak();
		noecho();
	}

	void refresh_display() {
		refresh();
	}

	void do_output(nmeaPARSER* p, nmeaINFO* info, const std::string& str) {

		parse(p, info, str);
		mvprintw(5,0, "Current: ");
		mvprintw(5, strlen("Timestamp: "), "%04d/%02d/%02d %02d:%02d:%02d",
				system_time.year + 1900, system_time.mon + 1, system_time.day,
				system_time.hour, system_time.min, system_time.sec);

		if (!nmea_parse(p, str.c_str(), str.length(), info)) {
			return;
		}

	if (info->sig && (info->smask & GPRMC)) {
		mvprintw(2,0, "Latitude: ");
		clrtoeol();
		mvprintw(2, strlen("Longitude: "), "%+04d° %02d' %02.6f\"",
				latitude.get_deg(), latitude.get_min(), latitude.get_secs());

		mvprintw(3,0, "Longitude: ");
		clrtoeol();
		mvprintw(3, strlen("Longitude: "), "%+04d° %02d' %02.6f\"",
				longitude.get_deg(), longitude.get_min(), longitude.get_secs());

		mvprintw(4,0, "Timestamp: ");
		mvprintw(4,strlen("Timestamp: "), "%04d/%02d/%02d %02d:%02d:%02d",
				this->sample_time.year + 1900, this->sample_time.mon + 1, this->sample_time.day,
				this->sample_time.hour, this->sample_time.min, this->sample_time.sec);

		mvprintw(6,0, "Speed %04.4f", this->speed);
		mvprintw(6,21, "Heading %03.4f", this->direction);
		mvprintw(7,0, "Elevation %05.4f", this->elevation);
		mvprintw(7,21, "Declination %03.4f", this->declination);

		move(8,0);
		clrtoeol();
		mvprintw(8,0, "Signal: %s", info->sig == 1? "Fix" : info->sig == 2 ? "Differential" : "Sensitive");
		mvprintw(8,21, "Fix: %s", info->fix == 1? "Not Available" : info->fix == 2 ? "2D" : "3D");
		move(9,0);
		clrtoeol();
		mvprintw(9,0, "Satellites (Use, View): %d, %d", info->satinfo.inuse, info->satinfo.inview);

	} else if (info->sig && (info->smask & GPGSV)) {
		move(9,0);
		clrtoeol();
		mvprintw(9,0, "Satellites (Use, View): %d, %d", info->satinfo.inuse, info->satinfo.inview);
	}

	}

	void do_outputx(nmeaPARSER* p, nmeaINFO* info, const std::string& str) {

	nmeaTIME time;
	nmea_time_now(&time);
	mvprintw(5,0, "Current: ");
	mvprintw(5, strlen("Timestamp: "), "%04d/%02d/%02d %02d:%02d:%02d",
				time.year + 1900, time.mon + 1, time.day,
				time.hour, time.min, time.sec);
	if (!nmea_parse(p, str.c_str(), str.length(), info)) {
		return;
	}

	if (info->sig && (info->smask & GPRMC)) {
		double raw_secs_lat = fabs(info->lat - trunc(info->lat));
		double lat_secs = raw_secs_lat * 60.0;
		int degs = static_cast<int>(trunc(info->lat / 100.f));
		int mins = static_cast<int>(fabs(trunc(info->lat - (degs * 100))));

		mvprintw(2,0, "Latitude: ");
		clrtoeol();
		mvprintw(2, strlen("Longitude: "), "%+04d° %02d' %02.6f\"", degs, mins, lat_secs);

		double raw_secs_lon = fabs(info->lon - trunc(info->lon));
		double lon_secs = raw_secs_lon * 60.0;
		degs = static_cast<int>(trunc(info->lon / 100.f));
		mins = static_cast<int>(fabs(trunc(info->lon - (degs * 100))));

		mvprintw(3,0, "Longitude: ");
		clrtoeol();
		mvprintw(3, strlen("Longitude: "), "%+04d° %02d' %02.6f\"", degs, mins, lon_secs);

		mvprintw(4,0, "Timestamp: ");
		mvprintw(4,strlen("Timestamp: "), "%04d/%02d/%02d %02d:%02d:%02d",
				info->utc.year + 1900, info->utc.mon + 1, info->utc.day,
				info->utc.hour, info->utc.min, info->utc.sec);

		mvprintw(6,0, "Speed %04.4f", info->speed);
		mvprintw(6,21, "Heading %03.4f", info->direction);
		mvprintw(7,0, "Elevation %05.4f", info->elv);
		mvprintw(7,21, "Declination %03.4f", info->declination);

		move(8,0);
		clrtoeol();
		mvprintw(8,0, "Signal: %s", info->sig == 1? "Fix" : info->sig == 2 ? "Differential" : "Sensitive");
		mvprintw(8,21, "Fix: %s", info->fix == 1? "Not Available" : info->fix == 2 ? "2D" : "3D");
		move(9,0);
		clrtoeol();
		mvprintw(9,0, "Satellites (Use, View): %d, %d", info->satinfo.inuse, info->satinfo.inview);

		mvprintw(20,0, "Lat Raw: %05.8f", info->lat);
		mvprintw(21,0, "Lon Raw: %05.8f", info->lon);
		mvprintw(22,0, "Raw: %05.8f", raw_secs_lat);
		mvprintw(23,0, "Raw: %05.8f", raw_secs_lon);

	} else if (info->sig && (info->smask & GPGSV)) {
		//mvprintw(10,0, "Signal: %s", info->sig == 1? "Fix" : info->sig == 2 ? "Differential" : "Sensitive");
		//mvprintw(11,0, "Fix: %s", info->fix == 1? "Not Available" : info->fix == 2 ? "2D" : "3D");
		move(9,0);
		clrtoeol();
		mvprintw(9,0, "Satellites (Use, View): %d, %d", info->satinfo.inuse, info->satinfo.inview);
	}

	}

	void clear();

	virtual ~NCursesDisplay() {
		endwin();
	}
};

#endif /* NCURSESDISPLAY_H_ */
