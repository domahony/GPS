/*
 * LCDDisplay.h
 *
 *  Created on: Mar 17, 2014
 *      Author: domahony
 */

#ifndef LCDDISPLAY_H_
#define LCDDISPLAY_H_

#include <sys/time.h>
#include <Display.h>
#include <lcd.h>

class LCDDisplay: public Display {

enum Phase {
	LOCATION=0,
	SPEED_ELEVATION=1,
	DIR_DECL=2
};

public:
	LCDDisplay() : lcd(lcdInit(2,16,4, 11,10, 0,1,2,3, 0,0,0,0)), phase(LOCATION), pstamp(0), ustamp(0), poffset(0) {

		lcdClear(lcd);

	}

	virtual ~LCDDisplay() {

	}

	void refresh_display() {

	}

	void do_output(nmeaPARSER* p, nmeaINFO* info, const std::string& str)
	{
		parse(p, info, str);
		struct timeval now;
		gettimeofday(&now, 0);

		if (now.tv_sec - pstamp >= 10) {
			poffset = (poffset + 1) % 3;
			pstamp = now.tv_sec;
		}

		if (now.tv_sec - ustamp >= 1) {
			ustamp = now.tv_sec;
		} else {
			return;
		}


		//lcdClear(lcd);
		switch (phase + poffset) {
		case LOCATION:
			lcdPosition(lcd, 0, 0);
			lcdPrintf(lcd, "%+04d %02d %02.3f",
				latitude.get_deg(), latitude.get_min(), latitude.get_secs());
			lcdPosition(lcd, 0, 1);
			lcdPrintf(lcd, "%+04d %02d %02.3f",
				longitude.get_deg(), longitude.get_min(), longitude.get_secs());
			break;
		case SPEED_ELEVATION:
			lcdPosition(lcd, 0, 0);
			lcdPrintf(lcd, "Speed %04.4f", this->speed);
			lcdPosition(lcd, 0, 1);
			lcdPrintf(lcd, "Head %03.4f", this->direction);
			break;
		case DIR_DECL:
			lcdPosition(lcd, 0, 0);
			lcdPrintf(lcd, "Ele %05.4f", this->elevation);
			lcdPosition(lcd, 0, 1);
			lcdPrintf(lcd, "Decl %03.4f", this->declination);
			break;
		}

	}

private:
	int lcd;
	Phase phase;
	time_t pstamp;
	time_t ustamp;
	int poffset;

};

#endif /* LCDDISPLAY_H_ */
