#pragma once
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Interval {
private:
	double first;
	double last;
	double count;
	double countRelative;
public:
	Interval(double _first, double _last) {
		first = _first;
		last = _last;
		count = 0;
		countRelative = 0;
	}

	Interval() {
		first = 0;
		last = 0;
		count = 0;
		countRelative = 0;
	}
	double begin() {
		return first;
	}
	double end() {
		return last;
	}
	int frequency() {
		return count;
	}
	double relativeFrequency() {
		return countRelative;
	}
	void setFreqvency(double _frequency) {
		count = _frequency;
	}
	void addFrequency(double _value) {
		count = count + _value;
	}
	void setRelativeFrequency(double _value) {
		countRelative = _value;
	}
};

