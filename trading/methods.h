#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "classes.h"
#include "sqlite3.h"

using namespace std;

string ret;

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
	ret.clear();
	for (i = 1; i < argc; i++) {
		//printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		//cout << (argv[i] ? argv[i] : "NULL") << ",";
		ret = ret + (argv[i] ? argv[i] : "NULL") + ",";
	}
	//printf("\n");
	return 0;
}

void newDB() {
	sqlite3 *db;
	char *sql;
	char *err = 0;
	
	ifstream file;

	file_open(file);

	sqlite3_open("test.db", &db);

	sql = "CREATE TABLE HISTORY("  \
		"LINE			INT PRIMARY KEY		NOT NULL, " \
		"DATE			CHAR(10)			NOT NULL, " \
		"CLOSE_PRICE	REAL				NOT NULL, " \
		"OPEN_PRICE		REAL				NOT NULL, " \
		"DAY_HIGH		REAL, " \
		"DAY_LOW		REAL );";

	

	sqlite3_exec(db, sql, callback, 0, &err);

	for (int i = 1;i <= 4978;i++) { //i=4978
		char *sql_in = new char[1024];
		char *data, date[10];
		LINE line;
		string input, num;

		data = read_line(file);
		line.update_line(data, i);

		line.getDate().get(date);

		input = "INSERT INTO HISTORY (LINE,DATE,CLOSE_PRICE,OPEN_PRICE,DAY_HIGH,DAY_LOW)"
			"VALUES("
			+ to_string(i) + ", "
			+ "\"" + date + "\"" + ", "
			+ to_string(line.getCP()) + ", "
			+ to_string(line.getOP()) + ", "
			+ to_string(line.getDH()) + ", "
			+ to_string(line.getDL()) + ");";

		strcpy(sql_in, input.c_str());
		sqlite3_exec(db, sql_in, callback, 0, &err);
		delete[] sql_in;
		cout << i << endl;
	}

	sql = "SELECT * FROM HISTORY;";
	sqlite3_exec(db, sql, callback, 0, &err);

	sqlite3_close(db);
	file_close(file);
	
}

void sql_read_line(int i) {
	sqlite3 *db;
	char *sql = new char[50];
	string sqlCom;
	char *err = 0;

	sqlite3_open("test.db", &db);
	sqlCom = "select * from history where line = " + to_string(i);
	strcpy(sql, sqlCom.c_str());
	sqlite3_exec(db, sql, callback, 0, &err);

	sqlite3_close(db);
	delete[] sql;
}

///sql///