#pragma once

namespace gnsssdrgui {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO;

    public ref class monitordlg : public System::Windows::Forms::Form
    {
    public:
        monitordlg(void)
        {
            InitializeComponent();
        }

    protected:
        ~monitordlg()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::Panel^  panel1;
    protected: 
    private: System::Windows::Forms::Button^  b_save;
    private: System::Windows::Forms::Button^  b_clear;
    public: System::Windows::Forms::ListBox^  ls_monitor;
    private: System::Windows::Forms::SaveFileDialog^  savefiledlg;

    private:
        System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(monitordlg::typeid));
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->b_save = (gcnew System::Windows::Forms::Button());
            this->b_clear = (gcnew System::Windows::Forms::Button());
            this->ls_monitor = (gcnew System::Windows::Forms::ListBox());
            this->savefiledlg = (gcnew System::Windows::Forms::SaveFileDialog());
            this->panel1->SuspendLayout();
            this->SuspendLayout();
            // 
            // panel1
            // 
            this->panel1->Controls->Add(this->b_save);
            this->panel1->Controls->Add(this->b_clear);
            this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
            this->panel1->Location = System::Drawing::Point(0, 0);
            this->panel1->Name = L"panel1";
            this->panel1->Size = System::Drawing::Size(497, 26);
            this->panel1->TabIndex = 0;
            // 
            // b_save
            // 
            this->b_save->Location = System::Drawing::Point(447, 3);
            this->b_save->Name = L"b_save";
            this->b_save->Size = System::Drawing::Size(47, 20);
            this->b_save->TabIndex = 1;
            this->b_save->Text = L"Save";
            this->b_save->UseVisualStyleBackColor = true;
            this->b_save->Click += gcnew System::EventHandler(this, &monitordlg::b_save_Click);
            // 
            // b_clear
            // 
            this->b_clear->Location = System::Drawing::Point(399, 3);
            this->b_clear->Name = L"b_clear";
            this->b_clear->Size = System::Drawing::Size(47, 20);
            this->b_clear->TabIndex = 0;
            this->b_clear->Text = L"Clear";
            this->b_clear->UseVisualStyleBackColor = true;
            this->b_clear->Click += gcnew System::EventHandler(this, &monitordlg::b_clear_Click);
            // 
            // ls_monitor
            // 
            this->ls_monitor->Dock = System::Windows::Forms::DockStyle::Fill;
            this->ls_monitor->DrawMode = System::Windows::Forms::DrawMode::OwnerDrawFixed;
            this->ls_monitor->FormattingEnabled = true;
            this->ls_monitor->ItemHeight = 12;
            this->ls_monitor->Items->AddRange(gcnew cli::array< System::Object^  >(1) {L" "});
            this->ls_monitor->Location = System::Drawing::Point(0, 26);
            this->ls_monitor->Name = L"ls_monitor";
            this->ls_monitor->ScrollAlwaysVisible = true;
            this->ls_monitor->Size = System::Drawing::Size(497, 380);
            this->ls_monitor->TabIndex = 1;
            this->ls_monitor->DrawItem += gcnew System::Windows::Forms::DrawItemEventHandler(this, &monitordlg::ls_monitor_DrawItem);
            // 
            // savefiledlg
            // 
            this->savefiledlg->Filter = L"\"text file(*.txt)|*.txt|all(*.*)|*.*\"";
            // 
            // monitordlg
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(497, 406);
            this->ControlBox = false;
            this->Controls->Add(this->ls_monitor);
            this->Controls->Add(this->panel1);
            this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
            this->Name = L"monitordlg";
            this->Text = L"Monitor";
            this->panel1->ResumeLayout(false);
            this->ResumeLayout(false);

        }
#pragma endregion
    private: System::Void b_clear_Click(System::Object^  sender, System::EventArgs^  e) {
                 ls_monitor->Items->Clear();
                 ls_monitor->Items->AddRange(gcnew cli::array< System::Object^  >(1) {L" "});
             }
    private: System::Void b_save_Click(System::Object^  sender, System::EventArgs^  e) {
                 savefiledlg->ShowDialog();
                 if (savefiledlg->FileName == "") return;

                 StreamWriter^ sw = File::CreateText(savefiledlg->FileName);
                 for (int i=0;i<ls_monitor->Items->Count;i++)
                     sw->WriteLine(ls_monitor->Items[i]);
                 sw->Close();
             }
    private: System::Void ls_monitor_DrawItem(System::Object^  sender, System::Windows::Forms::DrawItemEventArgs^  e) {
                 e->DrawBackground();
                 Brush^b;
                 ListBox^lb = (ListBox^)sender;
                 String^str = lb->Items[e->Index]->ToString();

                 /* set font color */
                 if (str->IndexOf("!")>=0)
                     b = gcnew SolidBrush(Color::Blue);
                 else if (str->IndexOf("error")>=0)
                     b = gcnew SolidBrush(Color::Red);
                 else
                     b = gcnew SolidBrush(e->ForeColor);

                 e->Graphics->DrawString(str, e->Font, b, e->Bounds);
                 e->DrawFocusRectangle();
             }
    };
}
