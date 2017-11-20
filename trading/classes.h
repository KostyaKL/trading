#pragma once
double getPrice(char *data, int &j, int line);

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

	void get(char *in) {
		day = (in[0]-48)*10 + in[1] - 48;
		month = (in[3] - 48) * 10 + in[4] - 48;
		year = (in[6]-48)*1000 + (in[7]-48)*100 + (in[8]-48)*10 + in[9] - 48;
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

	void update_line(char *data, int i) {
		int j = 11;
		date.get(data);
		close_price = getPrice(data, j, i);
		open_price = getPrice(data, j, i);
		day_high = getPrice(data, j, i);
		day_low = getPrice(data, j, i);
	}

private:
	DATE date;
	double close_price, open_price, day_high, day_low;
};