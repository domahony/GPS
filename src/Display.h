/*
 * Display.h
 *
 *  Created on: Mar 17, 2014
 *      Author: domahony
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "nmea/parser.h"
#include "nmea/info.h"
#include "Coordinate.h"
#include <string>

class Display {
public:
	Display();
	virtual void refresh_display() = 0;
	virtual void do_output(nmeaPARSER*, nmeaINFO*, const std::string&) = 0;

	virtual ~Display();

protected:
	void parse(nmeaPARSER*, nmeaINFO*, const std::string&);
	Coordinate latitude;
	Coordinate longitude;
	double speed;
	double elevation;
	double direction;
	double declination;
	nmeaTIME sample_time;
	nmeaTIME system_time;
};

#endif /* DISPLAY_H_ */
