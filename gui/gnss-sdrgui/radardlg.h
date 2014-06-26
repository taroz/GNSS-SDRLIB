#pragma once

namespace gnsssdrgui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// radardlg の概要
	/// </summary>
	public ref class radardlg : public System::Windows::Forms::Form
	{
	public:
		radardlg(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~radardlg()
		{
			if (components)
			{
				delete components;
			}
		}
    public: System::Windows::Forms::WebBrowser^  wb_radar;
    protected: 

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
            this->wb_radar = (gcnew System::Windows::Forms::WebBrowser());
            this->SuspendLayout();
            // 
            // wb_radar
            // 
            this->wb_radar->AllowNavigation = false;
            this->wb_radar->AllowWebBrowserDrop = false;
            this->wb_radar->Dock = System::Windows::Forms::DockStyle::Fill;
            this->wb_radar->Location = System::Drawing::Point(0, 0);
            this->wb_radar->MinimumSize = System::Drawing::Size(20, 20);
            this->wb_radar->Name = L"wb_radar";
            this->wb_radar->ScrollBarsEnabled = false;
            this->wb_radar->Size = System::Drawing::Size(442, 536);
            this->wb_radar->TabIndex = 0;
            this->wb_radar->Url = (gcnew System::Uri(L"http://www.taroz.net/GNSS-Radar_sky.html", System::UriKind::Absolute));
            // 
            // radardlg
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(442, 536);
            this->Controls->Add(this->wb_radar);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"radardlg";
            this->ShowIcon = false;
            this->ShowInTaskbar = false;
            this->Text = L"GNSS Radar";
            this->ResumeLayout(false);

        }
#pragma endregion
	};
}
