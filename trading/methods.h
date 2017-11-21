#pragma once
#include <iostream>
#include <fstream>
#include "classes.h"
#include "mainWin.h"
#include "sqlite3.h"

using namespace std;
using namespace System;

void file_open(ifstream &file) {
	file.open("gpb usd nov 17.csv");
}

void file_close(ifstream &file) {
	file.close();
}

char *read_line(ifstream &file) {
	char *data;
	data = new char[50];
	file >> data;
	return data;
}

double getPrice(char *data,  int &j, int line) {
	int flag, div;
	double tmp, price;
	div = 10;
	flag = 1;
	price = 0;
	while (data[j] != ',' && j <= 50) {
		if (data[j] == '.') {
			flag = 0;
			j++;
		}
		if (flag) {
			price+=data[j] - 48;
		}
		else {
			tmp = data[j] - 48;
			price+=(tmp / div);
			div *= 10;
		}
		j++;
	}
	j++;
	return price;
}


void avgVol(ifstream &file, double &up_price, double &down_price, double &up_day, double &down_day) {
	char *data;
	LINE today, yesterday, day_bef;
	double upC, downC;
	int flag = 1;



	up_price = 0;
	down_price = 0;
	up_day = 0;
	down_day = 0;
	upC = 0;
	downC = 0;

	data = read_line(file);
	today.update_line(data, 1);
	day_bef = yesterday = today;
	for (int i = 2;i <= 4978;) {
		if (today.getCP() > yesterday.getCP()) {
			up_price += (today.getCP() - yesterday.getCP());
			while (today.getCP() > yesterday.getCP() && i <= 4978) {
				up_day++;
				i++;

				yesterday = today;
				data = read_line(file);
				today.update_line(data, i);
			}
			upC++;
		}
		else if (today.getCP() < yesterday.getCP()) {
			down_price += (yesterday.getCP() - today.getCP());
			while (today.getCP() < yesterday.getCP() && i <= 4978) {
				down_day++;
				i++;

				yesterday = today;
				data = read_line(file);
				today.update_line(data, i);
			}
			downC++;
		}

		else {
			yesterday = today;
			data = read_line(file);
			today.update_line(data, i);
			i++;
		}
	}

	up_price /= upC;
	up_day /= upC;
	down_price /= downC;
	down_day /= downC;

	delete[] data;
}

	static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
		int i;
		for (i = 0; i<argc; i++) {
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		}
		printf("\n");
		return 0;
	}

	/*void newDB() {
		sqlite3 *db;
		char *sql;
		char *err = 0;


		sqlite3_open("test.db", &db);
		sql = "CREATE TABLE COMPANY("  \
			"ID INT PRIMARY KEY     NOT NULL," \
			"NAME           TEXT    NOT NULL," \
			"AGE            INT     NOT NULL," \
			"ADDRESS        CHAR(50)," \
			"SALARY         REAL );";
		sqlite3_exec(db, sql, callback, 0, &err);
		sqlite3_close(db);
	}*/

	void priceMod(double &price) {
		double tmp;

		tmp = modf(price, &price);
		tmp *= 10000;
		modf(tmp, &tmp);
		tmp /= 10000;
		price += tmp;
	}

	void cprint(double up_price, double up_day, double down_price, double down_day) {
		priceMod(up_price);
		priceMod(down_price);

		Console::WriteLine(Convert::ToString(up_price));
		Console::WriteLine(Convert::ToString(up_day));
		Console::WriteLine(Convert::ToString(down_price));
		Console::WriteLine(Convert::ToString(down_day));
		Console::WriteLine(Convert::ToString("\n"));
	}