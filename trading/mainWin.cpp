#include <iostream>
#include <fstream>
#include "mainWin.h"
#include "methods.h"

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

