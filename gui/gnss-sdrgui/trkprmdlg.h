#pragma once
#include "gnss-sdrgui.h"

namespace gnsssdrgui {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class trkprmdlg : public System::Windows::Forms::Form
    {
    public:
        trkprmdlg(void)
        {
            InitializeComponent();
        }

    protected:
        ~trkprmdlg()
        {
            if (components)
            {
                delete components;
            }
        }
    public: System::Windows::Forms::GroupBox^  groupBox1;
    protected: 

    public: SDR^ sdr;
    public: System::Windows::Forms::Label^  label5;
    public: System::Windows::Forms::Label^  label3;
    public: System::Windows::Forms::TextBox^  tb_corrp;

    public: System::Windows::Forms::Label^  label2;
    public: System::Windows::Forms::TextBox^  tb_corrd;

    public: System::Windows::Forms::Label^  label1;
    public: System::Windows::Forms::TextBox^  tb_corrn;

    public: System::Windows::Forms::Label^  label4;
    public: System::Windows::Forms::GroupBox^  groupBox2;
    public: System::Windows::Forms::Label^  label7;
    public: System::Windows::Forms::TextBox^  tb_fll2;

    public: System::Windows::Forms::Label^  label13;
    public: System::Windows::Forms::TextBox^  tb_pll2;

    public: System::Windows::Forms::Label^  label14;
    public: System::Windows::Forms::TextBox^  tb_dll2;

    public: System::Windows::Forms::Label^  label12;
    public: System::Windows::Forms::Label^  label11;
    public: System::Windows::Forms::TextBox^  tb_fll1;

    public: System::Windows::Forms::Label^  label10;
    public: System::Windows::Forms::TextBox^  tb_pll1;

    public: System::Windows::Forms::Label^  label6;
    public: System::Windows::Forms::Label^  label8;
    public: System::Windows::Forms::Label^  label9;
    public: System::Windows::Forms::TextBox^  tb_dll1;

    private:
        System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->tb_corrp = (gcnew System::Windows::Forms::TextBox());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->tb_corrd = (gcnew System::Windows::Forms::TextBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->tb_corrn = (gcnew System::Windows::Forms::TextBox());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->tb_fll2 = (gcnew System::Windows::Forms::TextBox());
            this->label13 = (gcnew System::Windows::Forms::Label());
            this->tb_pll2 = (gcnew System::Windows::Forms::TextBox());
            this->label14 = (gcnew System::Windows::Forms::Label());
            this->tb_dll2 = (gcnew System::Windows::Forms::TextBox());
            this->label12 = (gcnew System::Windows::Forms::Label());
            this->label11 = (gcnew System::Windows::Forms::Label());
            this->tb_fll1 = (gcnew System::Windows::Forms::TextBox());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->tb_pll1 = (gcnew System::Windows::Forms::TextBox());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->tb_dll1 = (gcnew System::Windows::Forms::TextBox());
            this->groupBox1->SuspendLayout();
            this->groupBox2->SuspendLayout();
            this->SuspendLayout();
            // 
            // groupBox1
            // 
            this->groupBox1->Controls->Add(this->label5);
            this->groupBox1->Controls->Add(this->label3);
            this->groupBox1->Controls->Add(this->tb_corrp);
            this->groupBox1->Controls->Add(this->label2);
            this->groupBox1->Controls->Add(this->tb_corrd);
            this->groupBox1->Controls->Add(this->label1);
            this->groupBox1->Controls->Add(this->tb_corrn);
            this->groupBox1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->groupBox1->Location = System::Drawing::Point(9, 9);
            this->groupBox1->Name = L"groupBox1";
            this->groupBox1->Size = System::Drawing::Size(275, 86);
            this->groupBox1->TabIndex = 2;
            this->groupBox1->TabStop = false;
            this->groupBox1->Text = L"Correlation";
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->label5->Location = System::Drawing::Point(216, 60);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(55, 12);
            this->label5->TabIndex = 9;
            this->label5->Text = L"(samples)";
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->label3->Location = System::Drawing::Point(4, 60);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(137, 12);
            this->label3->TabIndex = 7;
            this->label3->Text = L"Harf of Correlator Space: ";
            // 
            // tb_corrp
            // 
            this->tb_corrp->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->tb_corrp->Location = System::Drawing::Point(170, 57);
            this->tb_corrp->Name = L"tb_corrp";
            this->tb_corrp->Size = System::Drawing::Size(45, 19);
            this->tb_corrp->TabIndex = 6;
            this->tb_corrp->Text = L"8";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->label2->Location = System::Drawing::Point(4, 39);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(159, 12);
            this->label2->TabIndex = 5;
            this->label2->Text = L"Interval of Correlation Points: ";
            // 
            // tb_corrd
            // 
            this->tb_corrd->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->tb_corrd->Location = System::Drawing::Point(170, 36);
            this->tb_corrd->Name = L"tb_corrd";
            this->tb_corrd->Size = System::Drawing::Size(45, 19);
            this->tb_corrd->TabIndex = 4;
            this->tb_corrd->Text = L"4";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->label1->Location = System::Drawing::Point(4, 18);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(160, 12);
            this->label1->TabIndex = 3;
            this->label1->Text = L"Number of Correlation Points: ";
            // 
            // tb_corrn
            // 
            this->tb_corrn->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->tb_corrn->Location = System::Drawing::Point(170, 15);
            this->tb_corrn->Name = L"tb_corrn";
            this->tb_corrn->Size = System::Drawing::Size(45, 19);
            this->tb_corrn->TabIndex = 2;
            this->tb_corrn->Text = L"6";
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(225, 48);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(55, 12);
            this->label4->TabIndex = 8;
            this->label4->Text = L"(samples)";
            // 
            // groupBox2
            // 
            this->groupBox2->Controls->Add(this->label7);
            this->groupBox2->Controls->Add(this->tb_fll2);
            this->groupBox2->Controls->Add(this->label13);
            this->groupBox2->Controls->Add(this->tb_pll2);
            this->groupBox2->Controls->Add(this->label14);
            this->groupBox2->Controls->Add(this->tb_dll2);
            this->groupBox2->Controls->Add(this->label12);
            this->groupBox2->Controls->Add(this->label11);
            this->groupBox2->Controls->Add(this->tb_fll1);
            this->groupBox2->Controls->Add(this->label10);
            this->groupBox2->Controls->Add(this->tb_pll1);
            this->groupBox2->Controls->Add(this->label6);
            this->groupBox2->Controls->Add(this->label8);
            this->groupBox2->Controls->Add(this->label9);
            this->groupBox2->Controls->Add(this->tb_dll1);
            this->groupBox2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->groupBox2->Location = System::Drawing::Point(9, 101);
            this->groupBox2->Name = L"groupBox2";
            this->groupBox2->Size = System::Drawing::Size(275, 120);
            this->groupBox2->TabIndex = 10;
            this->groupBox2->TabStop = false;
            this->groupBox2->Text = L"Loop Filter";
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->label7->Location = System::Drawing::Point(173, 97);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(26, 12);
            this->label7->TabIndex = 20;
            this->label7->Text = L"FLL:";
            // 
            // tb_fll2
            // 
            this->tb_fll2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->tb_fll2->Location = System::Drawing::Point(201, 94);
            this->tb_fll2->Name = L"tb_fll2";
            this->tb_fll2->Size = System::Drawing::Size(45, 19);
            this->tb_fll2->TabIndex = 19;
            this->tb_fll2->Text = L"50.0";
            // 
            // label13
            // 
            this->label13->AutoSize = true;
            this->label13->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->label13->Location = System::Drawing::Point(95, 97);
            this->label13->Name = L"label13";
            this->label13->Size = System::Drawing::Size(26, 12);
            this->label13->TabIndex = 18;
            this->label13->Text = L"PLL:";
            // 
            // tb_pll2
            // 
            this->tb_pll2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->tb_pll2->Location = System::Drawing::Point(123, 94);
            this->tb_pll2->Name = L"tb_pll2";
            this->tb_pll2->Size = System::Drawing::Size(45, 19);
            this->tb_pll2->TabIndex = 17;
            this->tb_pll2->Text = L"10.0";
            // 
            // label14
            // 
            this->label14->AutoSize = true;
            this->label14->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->label14->Location = System::Drawing::Point(17, 97);
            this->label14->Name = L"label14";
            this->label14->Size = System::Drawing::Size(27, 12);
            this->label14->TabIndex = 16;
            this->label14->Text = L"DLL:";
            // 
            // tb_dll2
            // 
            this->tb_dll2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->tb_dll2->Location = System::Drawing::Point(45, 94);
            this->tb_dll2->Name = L"tb_dll2";
            this->tb_dll2->Size = System::Drawing::Size(45, 19);
            this->tb_dll2->TabIndex = 15;
            this->tb_dll2->Text = L"1.0";
            // 
            // label12
            // 
            this->label12->AutoSize = true;
            this->label12->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->label12->Location = System::Drawing::Point(13, 78);
            this->label12->Name = L"label12";
            this->label12->Size = System::Drawing::Size(215, 12);
            this->label12->TabIndex = 14;
            this->label12->Text = L"After Navigation Frame Synchronaization";
            // 
            // label11
            // 
            this->label11->AutoSize = true;
            this->label11->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->label11->Location = System::Drawing::Point(173, 55);
            this->label11->Name = L"label11";
            this->label11->Size = System::Drawing::Size(26, 12);
            this->label11->TabIndex = 13;
            this->label11->Text = L"FLL:";
            // 
            // tb_fll1
            // 
            this->tb_fll1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->tb_fll1->Location = System::Drawing::Point(201, 52);
            this->tb_fll1->Name = L"tb_fll1";
            this->tb_fll1->Size = System::Drawing::Size(45, 19);
            this->tb_fll1->TabIndex = 12;
            this->tb_fll1->Text = L"200.0";
            // 
            // label10
            // 
            this->label10->AutoSize = true;
            this->label10->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->label10->Location = System::Drawing::Point(95, 55);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(26, 12);
            this->label10->TabIndex = 11;
            this->label10->Text = L"PLL:";
            // 
            // tb_pll1
            // 
            this->tb_pll1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->tb_pll1->Location = System::Drawing::Point(123, 52);
            this->tb_pll1->Name = L"tb_pll1";
            this->tb_pll1->Size = System::Drawing::Size(45, 19);
            this->tb_pll1->TabIndex = 10;
            this->tb_pll1->Text = L"30.0";
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->label6->Location = System::Drawing::Point(17, 55);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(27, 12);
            this->label6->TabIndex = 9;
            this->label6->Text = L"DLL:";
            // 
            // label8
            // 
            this->label8->AutoSize = true;
            this->label8->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->label8->Location = System::Drawing::Point(13, 36);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(223, 12);
            this->label8->TabIndex = 5;
            this->label8->Text = L"Before Navigation Frame Synchronaization";
            // 
            // label9
            // 
            this->label9->AutoSize = true;
            this->label9->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->label9->Location = System::Drawing::Point(6, 18);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(190, 12);
            this->label9->TabIndex = 3;
            this->label9->Text = L"DLL/PLL/FLL Noise Bandwidth (Hz)";
            // 
            // tb_dll1
            // 
            this->tb_dll1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->tb_dll1->Location = System::Drawing::Point(45, 52);
            this->tb_dll1->Name = L"tb_dll1";
            this->tb_dll1->Size = System::Drawing::Size(45, 19);
            this->tb_dll1->TabIndex = 2;
            this->tb_dll1->Text = L"5.0";
            // 
            // trkprmdlg
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(293, 229);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->groupBox2);
            this->Controls->Add(this->groupBox1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"trkprmdlg";
            this->ShowIcon = false;
            this->Text = L"Tracking Parameter Setting";
            this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &trkprmdlg::trkprmdlg_FormClosing);
            this->Load += gcnew System::EventHandler(this, &trkprmdlg::trkprmdlg_Load);
            this->groupBox1->ResumeLayout(false);
            this->groupBox1->PerformLayout();
            this->groupBox2->ResumeLayout(false);
            this->groupBox2->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private: System::Void trkprmdlg_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
                 sdr->settrkprm(this,this->Owner);
             }
    private: System::Void trkprmdlg_Load(System::Object^  sender, System::EventArgs^  e) {
                 sdr=gcnew SDR();
             }
    };
}
