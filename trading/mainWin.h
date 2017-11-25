#pragma once
#include <iostream>
#include "methods.h"

using namespace std;

namespace trading {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for mainWin
	/// </summary>

	public ref class mainWin : public System::Windows::Forms::Form
	{
	public:
		mainWin(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			//newDB();
		}
		
		void avgVol(double &up_price, double &down_price, double &up_day, double &down_day);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~mainWin()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  upPrice;
	private: System::Windows::Forms::Label^  downPrice;
	private: System::Windows::Forms::Label^  upDays;
	private: System::Windows::Forms::Label^  downDays;
	private: System::Windows::Forms::Button^  button1;
	
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

		void updateLabel(double up_price, double up_day, double down_price, double down_day);

		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->upPrice = (gcnew System::Windows::Forms::Label());
			this->downPrice = (gcnew System::Windows::Forms::Label());
			this->upDays = (gcnew System::Windows::Forms::Label());
			this->downDays = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// upPrice
			// 
			this->upPrice->AutoSize = true;
			this->upPrice->Location = System::Drawing::Point(212, 165);
			this->upPrice->Name = L"upPrice";
			this->upPrice->Size = System::Drawing::Size(13, 13);
			this->upPrice->TabIndex = 0;
			this->upPrice->Text = L"0";
			// 
			// downPrice
			// 
			this->downPrice->AutoSize = true;
			this->downPrice->Location = System::Drawing::Point(342, 165);
			this->downPrice->Name = L"downPrice";
			this->downPrice->Size = System::Drawing::Size(13, 13);
			this->downPrice->TabIndex = 1;
			this->downPrice->Text = L"0";
			// 
			// upDays
			// 
			this->upDays->AutoSize = true;
			this->upDays->Location = System::Drawing::Point(212, 251);
			this->upDays->Name = L"upDays";
			this->upDays->Size = System::Drawing::Size(13, 13);
			this->upDays->TabIndex = 2;
			this->upDays->Text = L"0";
			// 
			// downDays
			// 
			this->downDays->AutoSize = true;
			this->downDays->Location = System::Drawing::Point(342, 251);
			this->downDays->Name = L"downDays";
			this->downDays->Size = System::Drawing::Size(13, 13);
			this->downDays->TabIndex = 3;
			this->downDays->Text = L"0";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(396, 391);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 4;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &mainWin::button1_Click);
			// 
			// mainWin
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(638, 516);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->downDays);
			this->Controls->Add(this->upDays);
			this->Controls->Add(this->downPrice);
			this->Controls->Add(this->upPrice);
			this->Name = L"mainWin";
			this->Text = L"mainWin";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		double up_price, down_price, up_day, down_day;
		avgVol(up_price, down_price, up_day, down_day);
	}
};
}
