#pragma once
#include <math.h>
#include <string>

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBoxA;
	private: System::Windows::Forms::TextBox^ textBoxC;
	private: System::Windows::Forms::TextBox^ textBoxB;
	private: System::Windows::Forms::RichTextBox^ richTextBox;

	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::TextBox^ textBoxX2;
	private: System::Windows::Forms::TextBox^ textBoxX1;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::Button^ SolveBtn;
	private: System::Windows::Forms::Button^ ClearBtn;
	
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBoxA = (gcnew System::Windows::Forms::TextBox());
			this->textBoxC = (gcnew System::Windows::Forms::TextBox());
			this->textBoxB = (gcnew System::Windows::Forms::TextBox());
			this->richTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->textBoxX2 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxX1 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->SolveBtn = (gcnew System::Windows::Forms::Button());
			this->ClearBtn = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(17, 31);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(42, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"a = ";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(17, 108);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(42, 20);
			this->label2->TabIndex = 1;
			this->label2->Text = L"c = ";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(17, 69);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(36, 20);
			this->label3->TabIndex = 2;
			this->label3->Text = L"b =";
			// 
			// textBoxA
			// 
			this->textBoxA->Location = System::Drawing::Point(66, 31);
			this->textBoxA->Name = L"textBoxA";
			this->textBoxA->Size = System::Drawing::Size(339, 22);
			this->textBoxA->TabIndex = 4;
			// 
			// textBoxC
			// 
			this->textBoxC->Location = System::Drawing::Point(65, 108);
			this->textBoxC->Name = L"textBoxC";
			this->textBoxC->Size = System::Drawing::Size(340, 22);
			this->textBoxC->TabIndex = 5;
			// 
			// textBoxB
			// 
			this->textBoxB->Location = System::Drawing::Point(66, 69);
			this->textBoxB->Name = L"textBoxB";
			this->textBoxB->Size = System::Drawing::Size(339, 22);
			this->textBoxB->TabIndex = 6;
			// 
			// richTextBox
			// 
			this->richTextBox->Location = System::Drawing::Point(6, 21);
			this->richTextBox->Name = L"richTextBox";
			this->richTextBox->ReadOnly = true;
			this->richTextBox->Size = System::Drawing::Size(399, 165);
			this->richTextBox->TabIndex = 8;
			this->richTextBox->Text = L"";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->textBoxC);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->textBoxB);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->textBoxA);
			this->groupBox1->Location = System::Drawing::Point(26, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(411, 138);
			this->groupBox1->TabIndex = 9;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Коофиценты уравнения";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->textBoxX2);
			this->groupBox2->Controls->Add(this->textBoxX1);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Location = System::Drawing::Point(26, 156);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(411, 106);
			this->groupBox2->TabIndex = 10;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Корни уравнения";
			// 
			// textBoxX2
			// 
			this->textBoxX2->Location = System::Drawing::Point(65, 70);
			this->textBoxX2->Name = L"textBoxX2";
			this->textBoxX2->ReadOnly = true;
			this->textBoxX2->Size = System::Drawing::Size(340, 22);
			this->textBoxX2->TabIndex = 9;
			// 
			// textBoxX1
			// 
			this->textBoxX1->Location = System::Drawing::Point(66, 31);
			this->textBoxX1->Name = L"textBoxX1";
			this->textBoxX1->ReadOnly = true;
			this->textBoxX1->Size = System::Drawing::Size(339, 22);
			this->textBoxX1->TabIndex = 10;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(17, 31);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(45, 20);
			this->label5->TabIndex = 8;
			this->label5->Text = L"x1 =";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(17, 70);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(51, 20);
			this->label4->TabIndex = 7;
			this->label4->Text = L"x2 = ";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->richTextBox);
			this->groupBox3->Location = System::Drawing::Point(26, 315);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(411, 192);
			this->groupBox3->TabIndex = 11;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Сообщения об ошибках";
			// 
			// SolveBtn
			// 
			this->SolveBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->SolveBtn->Location = System::Drawing::Point(32, 269);
			this->SolveBtn->Name = L"SolveBtn";
			this->SolveBtn->Size = System::Drawing::Size(239, 40);
			this->SolveBtn->TabIndex = 12;
			this->SolveBtn->Text = L"Решить";
			this->SolveBtn->UseVisualStyleBackColor = true;
			this->SolveBtn->Click += gcnew System::EventHandler(this, &MyForm::SolveBtn_Click);
			// 
			// ClearBtn
			// 
			this->ClearBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ClearBtn->Location = System::Drawing::Point(277, 269);
			this->ClearBtn->Name = L"ClearBtn";
			this->ClearBtn->Size = System::Drawing::Size(160, 40);
			this->ClearBtn->TabIndex = 13;
			this->ClearBtn->Text = L"Сбросить";
			this->ClearBtn->UseVisualStyleBackColor = true;
			this->ClearBtn->Click += gcnew System::EventHandler(this, &MyForm::ClearBtn_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(449, 519);
			this->Controls->Add(this->ClearBtn);
			this->Controls->Add(this->SolveBtn);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	
	
	private: System::Void SolveBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (textBoxA->Text == L"" || textBoxB->Text == L"" || textBoxC->Text == L"") {
			richTextBox->Text += L"\nПоля должны быть заполнены!";
			return;
		}
		textBoxX1->Text = L"";
		textBoxX2->Text = L"";
		double a, b, c, D, x1, x2;
		if(Double::TryParse(textBoxA->Text, a) && Double::TryParse(textBoxB->Text, b) && Double::TryParse(textBoxC->Text, c))
		{
			
			a = Convert::ToDouble(textBoxA->Text);
			b = Convert::ToDouble(textBoxB->Text);
			c = Convert::ToDouble(textBoxC->Text);
		}
		else
		{
			richTextBox->Text += L"\nВ полях должны быть числа!";
			return;
		}

		if (a != 0) {
			D = b * b - 4 * a * c;
			if (sqrt(D) > 0) {
				x1 = (-b + sqrt(D)) / (2 * a);
				x2 = (-b - sqrt(D)) / (2 * a);
				textBoxX1->Text = Convert::ToString(x1);
				textBoxX2->Text = Convert::ToString(x2);
				richTextBox->Text += L"\nКвадратное уравнение решено!";
				return;
			}
			else if (D == 0) {
				x1 = (-b / (2 * a));
				textBoxX1->Text = Convert::ToString(x1);
				textBoxX2->Text = Convert::ToString(x1);
				richTextBox->Text += L"\nДескриминант равен 0, поэтому найден 1 корень!";
				return;
			}
			else {
				richTextBox->Text += L"\nНет корней в этом квадратном уравнении!";
				return;
			}
		}
		else {
			richTextBox->Text += L"\nЭто не квадратное уравнение!";
			return;
		}
	}
	private: System::Void ClearBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		textBoxX1->Text = L"";
		textBoxX2->Text = L"";
		textBoxA->Text = L"";
		textBoxB->Text = L"";
		textBoxC->Text = L"";
		richTextBox->Text = L"";
	}
};
}
