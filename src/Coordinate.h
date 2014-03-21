/*
 * Coordinate.h
 *
 *  Created on: Mar 19, 2014
 *      Author: domahony
 */

#ifndef COORDINATE_H_
#define COORDINATE_H_

class Coordinate {
public:
	Coordinate(const int deg=0, const int min=0, const double secs=0.) : deg(deg), min(min), secs(secs) {

	}

	void set(const int deg, const int min, const double secs) {
			this->deg = deg;
			this->min = min;
			this->secs = secs;
	}

	const int get_deg() const {
		return deg;
	}
	const int get_min() const {
		return min;
	}
	const double get_secs() const {
		return secs;
	}

	virtual ~Coordinate() {

	}

private:
	int deg;
	int min;
	double secs;
};

#endif /* COORDINATE_H_ */
