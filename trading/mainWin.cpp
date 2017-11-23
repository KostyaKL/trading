#include <iostream>
#include <fstream>
#include "mainWin.h"
#include "methods.h"
#include "sqlite3.h"

using namespace std;

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
//WinMain
void main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	trading::mainWin form;
	Application::Run(%form);
	exit(0);
}

void trading::mainWin::avgVol(ifstream &file, double &up_price, double &down_price, double &up_day, double &down_day) {
	char *data= new char[50];
	LINE today, yesterday;
	double upC, downC;
	int flag = 1;

	

	up_price = 0;
	down_price = 0;
	up_day = 0;
	down_day = 0;
	upC = 0;
	downC = 0;

	

	//data = read_line(file);
	sql_read_line(1);
	strcpy(data, ret.c_str());
	today.update_line(data, 1);
	//day_bef = yesterday = today;
	for (int i = 2;i <= 4978;) {
		if (today.getCP() > yesterday.getCP()) {
			up_price += (today.getCP() - yesterday.getCP());
			while (today.getCP() > yesterday.getCP() && i <= 4978) {
				up_day++;
				i++;

				yesterday = today;
				//data = read_line(file);
				sql_read_line(i);
				strcpy(data, ret.c_str());
				today.update_line(data, i);

				updateLabel(up_price, up_day, down_price, down_day);
			}
			upC++;
		}
		else if (today.getCP() < yesterday.getCP()) {
			down_price += (yesterday.getCP() - today.getCP());
			while (today.getCP() < yesterday.getCP() && i <= 4978) {
				down_day++;
				i++;

				yesterday = today;
				//data = read_line(file);
				sql_read_line(i);
				strcpy(data, ret.c_str());
				today.update_line(data, i);

				updateLabel(up_price, up_day, down_price, down_day);
			}
			downC++;
		}
		else {
			yesterday = today;
			//data = read_line(file);
			sql_read_line(i);
			strcpy(data, ret.c_str());
			today.update_line(data, i);
			i++;
		}
	}

	up_price /= upC;
	up_day /= upC;
	down_price /= downC;
	down_day /= downC;

	updateLabel(up_price, up_day, down_price, down_day);

	delete[] data;

	
}

void trading::mainWin::updateLabel(double up_price, double up_day, double down_price, double down_day) {
	static int i = 0;

	priceMod(up_price);
	priceMod(down_price);

	upPrice->Text = Convert::ToString(up_price);
	upDays->Text = Convert::ToString(round(up_day));
	downPrice->Text = Convert::ToString(down_price);
	downDays->Text = Convert::ToString(round(down_day));

	if (!(i++ % 100)) {
		this->Refresh();
	}
}

