#pragma once
#include <iostream>
#include <fstream>
#include "classes.h"
#include "sqlite3.h"

using namespace std;

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

void priceMod(double &price) {
	double tmp;

	tmp = modf(price, &price);
	tmp *= 10000;
	modf(tmp, &tmp);
	tmp /= 10000;
	price += tmp;
}

///sql///

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void newDB() {
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
}

///sql///