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

void trading::mainWin::avgVol(double &up_price, double &down_price, double &up_day, double &down_day) {
	sqlite3 *dbSql;
	LINE today, yesterday;
	double upC, downC;
	int flag = 1;

	up_price = 0;
	down_price = 0;
	up_day = 0;
	down_day = 0;
	upC = 0;
	downC = 0;

	sql_open_db(&dbSql);

	sql_read_line(dbSql, 1);
	today.update_line(1);
	for (int i = 2;i <= 4978;) {
		if (today.getCP() > yesterday.getCP()) {
			up_price += (today.getCP() - yesterday.getCP());
			while (today.getCP() > yesterday.getCP() && i <= 4978) {
				up_day++;
				i++;

				yesterday = today;
				sql_read_line(dbSql, i);
				today.update_line(i);

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
				sql_read_line(dbSql, i);
				today.update_line(i);

				updateLabel(up_price, up_day, down_price, down_day);
			}
			downC++;
		}
		else {
			yesterday = today;
			sql_read_line(dbSql, i);
			today.update_line(i);
			i++;
		}
	}

	up_price /= upC;
	up_day /= upC;
	down_price /= downC;
	down_day /= downC;

	updateLabel(up_price, up_day, down_price, down_day);

	sql_close_db(dbSql);
}

void trading::mainWin::updateLabel(double up_price, double up_day, double down_price, double down_day) {
	static int i = 0;

	if (!(i++ % 100) || i>4700) {
		priceMod(up_price);
		priceMod(down_price);

		upPrice->Text = Convert::ToString(up_price);
		upDays->Text = Convert::ToString(round(up_day));
		downPrice->Text = Convert::ToString(down_price);
		downDays->Text = Convert::ToString(round(down_day));

		this->Refresh();
	}
}

