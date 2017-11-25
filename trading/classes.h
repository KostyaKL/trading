#pragma once

#include <iostream>

#include <string>
using namespace std;

string dbLine;


double getPrice(int &j, int line);

class DATE {
public:
	DATE() {
		day = 0;
		month = 0;
		year = 0;
	}
	DATE(const DATE &cpy) {
		day = cpy.day;
		month = cpy.month;
		year = cpy.year;
	}
	const DATE operator = (const DATE &cpy) {
		this->day = cpy.day;
		this->month = cpy.month;
		this->year = cpy.year;
		return *this;
	}
	~DATE() {

	}

	void set() {
		day = (dbLine[0]-48)*10 + dbLine[1] - 48;
		month = (dbLine[3] - 48) * 10 + dbLine[4] - 48;
		year = (dbLine[6]-48)*1000 + (dbLine[7]-48)*100 + (dbLine[8]-48)*10 + dbLine[9] - 48;
	}

	int getD() {
		return day;
	}

	int getM() {
		return month;
	}

	int getY() {
		return year;
	}

	string get() {
		string ret;
		string d, m, y;
	
		if (day / 10)
			d = to_string(day);
		else
			d = "0" + to_string(day);

		if (month / 10)
			m = to_string(month);
		else
			m = "0" + to_string(month);

		y = to_string(year);

		ret = d + "/" + m + "/" + y;
		return ret;
	}


private:
	int day;
	int month;
	int year;
};

class LINE {
public:
	LINE(double CP = 0, double OP = 0, double DH = 0, double DL = 0) {
		close_price = CP;
		open_price = OP;
		day_high = DH;
		day_low = DL;
	}

	LINE(const LINE &cpy) {
		date = cpy.date;
		close_price = cpy.close_price;
		open_price = cpy.open_price;
		day_high = cpy.day_high;
		day_low = cpy.day_low;
	}

	const LINE operator=(const LINE &cpy) {
		this->date = cpy.date;
		this->close_price = cpy.close_price;
		this->open_price = cpy.open_price;
		this->day_high = cpy.day_high;
		this->day_low = cpy.day_low;
		return *this;
	}

	~LINE() {

	}

	void setCP(double price) {
		close_price = price;
	}
	void setOP(double price) {
		open_price = price;
	}
	void setDH(double price) {
		day_high = price;
	}
	void setDL(double price) {
		day_low = price;
	}

	void incCP(double price) {
		close_price += price;
	}
	void incOP(double price) {
		open_price += price;
	}
	void incDH(double price) {
		day_high += price;
	}
	void incDL(double price) {
		day_low += price;
	}

	double getCP() {
		return close_price;
	}
	double getOP() {
		return open_price;
	}
	double getDH() {
		return day_high;
	}
	double getDL() {
		return day_low;
	}

	DATE getDate() {
		return date;
	}

	void update_line(int i) {
		int j = 11;
		date.set();
		close_price = getPrice(j, i);
		open_price = getPrice(j, i);
		day_high = getPrice(j, i);
		day_low = getPrice(j, i);
	}

private:
	DATE date;
	double close_price, open_price, day_high, day_low;
};