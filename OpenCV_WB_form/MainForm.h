#pragma once
#include <opencv2\opencv.hpp> 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <stdlib.h> 
#include <stdio.h> 
#include <cmath> 
#include <math.h>
#include <iostream>

namespace OpenCV_WB_form {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace std;
	using namespace cv;

	Mat src;
	string Dum;
	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnBrowse;
	private: System::Windows::Forms::Button^  btnProcess;
	private: System::Windows::Forms::PictureBox^  ptbSource;
	private: System::Windows::Forms::Label^  label;
	protected: 

	protected: 


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnBrowse = (gcnew System::Windows::Forms::Button());
			this->btnProcess = (gcnew System::Windows::Forms::Button());
			this->ptbSource = (gcnew System::Windows::Forms::PictureBox());
			this->label = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ptbSource))->BeginInit();
			this->SuspendLayout();
			// 
			// btnBrowse
			// 
			this->btnBrowse->Location = System::Drawing::Point(12, 12);
			this->btnBrowse->Name = L"btnBrowse";
			this->btnBrowse->Size = System::Drawing::Size(136, 55);
			this->btnBrowse->TabIndex = 0;
			this->btnBrowse->Text = L"Browse";
			this->btnBrowse->UseVisualStyleBackColor = true;
			this->btnBrowse->Click += gcnew System::EventHandler(this, &MainForm::btnBrowse_Click);
			// 
			// btnProcess
			// 
			this->btnProcess->Location = System::Drawing::Point(165, 12);
			this->btnProcess->Name = L"btnProcess";
			this->btnProcess->Size = System::Drawing::Size(136, 55);
			this->btnProcess->TabIndex = 1;
			this->btnProcess->Text = L"Process";
			this->btnProcess->UseVisualStyleBackColor = true;
			this->btnProcess->Click += gcnew System::EventHandler(this, &MainForm::btnProcess_Click);
			// 
			// ptbSource
			// 
			this->ptbSource->Location = System::Drawing::Point(12, 120);
			this->ptbSource->Name = L"ptbSource";
			this->ptbSource->Size = System::Drawing::Size(395, 292);
			this->ptbSource->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->ptbSource->TabIndex = 2;
			this->ptbSource->TabStop = false;
			// 
			// label
			// 
			this->label->AutoSize = true;
			this->label->Location = System::Drawing::Point(36, 101);
			this->label->Name = L"label";
			this->label->Size = System::Drawing::Size(70, 13);
			this->label->TabIndex = 3;
			this->label->Text = L"source image";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(944, 451);
			this->Controls->Add(this->label);
			this->Controls->Add(this->ptbSource);
			this->Controls->Add(this->btnProcess);
			this->Controls->Add(this->btnBrowse);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ptbSource))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnBrowse_Click(System::Object^  sender, System::EventArgs^  e) {
				 OpenFileDialog^ dgOpen = gcnew OpenFileDialog();
				 dgOpen->Filter = "Image ( *.bmp;	*.jpg)| *.bmp; *.jpg|All files (*.*)|*.*||";
				 if(dgOpen->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
					 return;
				 Bitmap^ bmpSrc = gcnew Bitmap(dgOpen->FileName);
				// System::string^ er=dgOpen->FileName;
				// ptbSource->Image = bmpSrc;
				// ptbSource->Refresh();
				// Dum=dgOpen->FileName;
				 src = imread(ConvertString2Char(dgOpen->FileName));
				 imshow	("Source image",src);
			 }
			 private: char* ConvertString2Char(System::String^ str)
					  {
						  char* str2=(char*)(void*)Marshal::StringToHGlobalAnsi(str);
						  return str2;
					  }
private: System::Void btnProcess_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 IplImage* image = 0; 
			// имя картинки задаётся первым параметром 
			//std::string filename("D:\\Программирование\\Обработка изображений\\ConsoleApplication1\\11.jpg"); 
			// получаем картинку 
			//image = cvLoadImage(filename.c_str(), 1); 
			// клонируем картинку 
			//src = cvCloneImage(image); 

			//printf("[i] image: %s\n", filename); 
			//assert(src != 0); 

			// окно для отображения картинки 
			//cvNamedWindow("original", CV_WINDOW_KEEPRATIO); 
			cvNamedWindow("changed", CV_WINDOW_AUTOSIZE); 
			Mat source; 
			source = src; 
			Mat inv_source = Mat::zeros(source.size(), CV_8UC3); 
			// показываем картинку 
			//cvShowImage("original", image); 
			int min; 
			for (int i = 0; i < source.rows; ++i) 
			for (int j = 0; j < source.cols; ++j) 
			{ 
			int Mmin=source.at<Vec3b>(i, j).val[0];
				if (source.at<Vec3b>(i, j).val[1] < Mmin)
			Mmin=source.at<Vec3b>(i, j).val[1];
				if(source.at<Vec3b>(i, j).val[2] < Mmin)
			Mmin=source.at<Vec3b>(i, j).val[2];
		
			min=Mmin;
			inv_source.at<Vec3b>(i, j) = Vec3b(min, min, min); 
			} 
			imshow("changed", inv_source); 
			cvWaitKey(0); 
			// освобождаем ресурсы 
			//cvReleaseImage(&image); 
			//cvReleaseImage(&src); 
			// удаляем окно 
			//cvDestroyWindow("original"); 
	
		 }
};
}
