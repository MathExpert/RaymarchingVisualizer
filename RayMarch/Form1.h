#pragma once
//#include "myvector.h"
#include "tracer.h"

namespace RayMarch {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox;
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
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox
			// 
			this->pictureBox->Location = System::Drawing::Point(0, 0);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(564, 382);
			this->pictureBox->TabIndex = 0;
			this->pictureBox->TabStop = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(564, 382);
			this->Controls->Add(this->pictureBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 Bitmap ^bmp = gcnew Bitmap(pictureBox->Width, pictureBox->Height);

				 // инициализируем сцену
				 Material mat1(vec3(0.3f, 0.3f, 0.3f), vec3(0.2f, 0.15f, 0.8f), vec3(0.8f, 0.8f, 0.8f), 15);
				 Material mat2(vec3(0.2f, 0.2f, 0.2f), vec3(0.2f, 1.0f, 0.1f), vec3(0.5f, 0.5f, 0.5f), 5);
				 Material mat4(vec3(0.3f, 0.3f, 0.3f), vec3(1.0f, 0.8f, 0.1f), vec3(0.5f, 0.5f, 0.5f), 20);
				 Material mat3(vec3(0.3f, 0.3f, 0.3f), vec3(0.9f, 0.9f, 0.9f), vec3(0.5f, 0.5f, 0.5f), 20);
				 mat3.refl = 0.5;

				 Scene scene(0.1f, color(0.3f, 0.3f, 0.3f));
				 scene.setBox(200.0f, 200.0f, 200.0f);

				 scene.setCam(vec3(0.0f, 25.0f, -50.0f), vec3(0.0, 0.0, 50.0), vec3(0, 1, 0), 30.0f, 0.1f);
				 scene.addLight(vec3(0.5f, 0.5f, 0.5f), vec3(0.8f, 0.8f, 0.8f), vec3(10.0, 10.0, 20.0));
 				 scene.addLight(vec3(0.5f, 0.8f, 0.65f), vec3(0.8f, 0.8f, 0.8f), vec3(-20.0, 15.0, 0.0));

				 scene.addSphere(vec3(-11, -5, 25), 4, mat1);
 				 scene.addRoundBox(vec3(-15, -5, 30), vec3(5, 5, 5), 0.8f, mat3);
				 scene.addBoolean(1);
 				 scene.addSphere(vec3(10, -5, 35), 6, mat3);
				 scene.addPlane(vec4(0, 1, 0, 12), mat2);
				 scene.addTorus(vec3(10, -10, 35), 10, 2, mat4);
				 scene.addSphere(vec3(-10, -10, 10), 2, mat4);

				 //рисуем
				 scene.Draw(bmp);
				 pictureBox->Image = bmp;
			 }
	};
}

