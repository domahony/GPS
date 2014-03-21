/*
 * Display.cpp
 *
 *  Created on: Mar 17, 2014
 *      Author: domahony
 */

#include <cmath>
#include <Display.h>
#include "nmea/nmea.h"

Display::Display() : latitude(), longitude(), speed(0), elevation(0), direction(0), declination(0) {

}

Display::~Display() {
	// TODO Auto-generated destructor stub
}

void Display::
parse(nmeaPARSER* p, nmeaINFO* info, const std::string& str)
{
	nmea_time_now(&this->system_time);
	if (!nmea_parse(p, str.c_str(), str.length(), info)) {
		return;
	}

	if (info->sig && (info->smask & GPRMC)) {
		double raw_secs_lat = fabs(info->lat - trunc(info->lat));
		double lat_secs = raw_secs_lat * 60.0;
		int degs = static_cast<int>(trunc(info->lat / 100.f));
		int mins = static_cast<int>(fabs(trunc(info->lat - (degs * 100))));

		latitude.set(degs, mins, lat_secs);

		double raw_secs_lon = fabs(info->lon - trunc(info->lon));
		double lon_secs = raw_secs_lon * 60.0;
		degs = static_cast<int>(trunc(info->lon / 100.f));
		mins = static_cast<int>(fabs(trunc(info->lon - (degs * 100))));

		longitude.set(degs, mins, lon_secs);

		this->sample_time = info->utc;
		this->speed = info->speed;
		this->elevation = info->elv;
		this->declination = info->declination;
		this->direction = info->direction;
	}
}
