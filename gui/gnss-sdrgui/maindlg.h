#pragma once
#include <windows.h>
#include "monitordlg.h"
#include "trkprmdlg.h"
#include "radardlg.h"

namespace gnsssdrgui {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Runtime::InteropServices;
    using namespace System::Xml::Serialization;

    public ref class maindlg : public System::Windows::Forms::Form
    {
    public:
        maindlg(void)
        {
            InitializeComponent();
        }

    protected:
        ~maindlg()
        {
            if (components)
            {
                delete components;
            }
        }
    public: System::Windows::Forms::GroupBox^  gb_input;
    protected: 

    public: System::Windows::Forms::Button^  b_input1;
    public: System::Windows::Forms::TextBox^  tb_input1;
    public: System::Windows::Forms::ComboBox^  cmb_input;
    public: System::Windows::Forms::GroupBox^  gb_output;
    public: System::Windows::Forms::ComboBox^  cmb_outint;
    public: System::Windows::Forms::Label^  l_lex;
    public: System::Windows::Forms::Label^  l_output;
    public: System::Windows::Forms::CheckBox^  chk_lex;
    public: System::Windows::Forms::CheckBox^  chk_rtcm;
    public: System::Windows::Forms::CheckBox^  chk_rinex;
    public: System::Windows::Forms::GroupBox^  gb_setting;
    public: System::Windows::Forms::Button^  b_rinex;
    public: System::Windows::Forms::TextBox^  tb_rinex_dir;
    public: System::Windows::Forms::TextBox^  tb_rtcm_port;
    public: System::Windows::Forms::Label^  l_rtcm;
    public: System::Windows::Forms::Label^  l_rinex;
    public: System::Windows::Forms::TextBox^  tb_lex_port;
    public: System::Windows::Forms::CheckBox^  chk_plottrk;
    public: System::Windows::Forms::CheckBox^  chk_plotacq;
    public: System::Windows::Forms::GroupBox^  gb_gps;
    public: System::Windows::Forms::CheckBox^  chk_G32;
    public: System::Windows::Forms::CheckBox^  chk_G31;
    public: System::Windows::Forms::CheckBox^  chk_G30;
    public: System::Windows::Forms::CheckBox^  chk_G29;
    public: System::Windows::Forms::CheckBox^  chk_G28;
    public: System::Windows::Forms::CheckBox^  chk_G27;
    public: System::Windows::Forms::CheckBox^  chk_G26;
    public: System::Windows::Forms::CheckBox^  chk_G25;
    public: System::Windows::Forms::CheckBox^  chk_G24;
    public: System::Windows::Forms::CheckBox^  chk_G23;
    public: System::Windows::Forms::CheckBox^  chk_G22;
    public: System::Windows::Forms::CheckBox^  chk_G21;
    public: System::Windows::Forms::CheckBox^  chk_G20;
    public: System::Windows::Forms::CheckBox^  chk_G19;
    public: System::Windows::Forms::CheckBox^  chk_G18;
    public: System::Windows::Forms::CheckBox^  chk_G17;
    public: System::Windows::Forms::CheckBox^  chk_G16;
    public: System::Windows::Forms::CheckBox^  chk_G15;
    public: System::Windows::Forms::CheckBox^  chk_G14;
    public: System::Windows::Forms::CheckBox^  chk_G13;
    public: System::Windows::Forms::CheckBox^  chk_G12;
    public: System::Windows::Forms::CheckBox^  chk_G11;
    public: System::Windows::Forms::CheckBox^  chk_G10;
    public: System::Windows::Forms::CheckBox^  chk_G09;
    public: System::Windows::Forms::CheckBox^  chk_G08;
    public: System::Windows::Forms::CheckBox^  chk_G07;
    public: System::Windows::Forms::CheckBox^  chk_G06;
    public: System::Windows::Forms::CheckBox^  chk_G05;
    public: System::Windows::Forms::CheckBox^  chk_G04;
    public: System::Windows::Forms::CheckBox^  chk_G03;
    public: System::Windows::Forms::CheckBox^  chk_G02;
    public: System::Windows::Forms::CheckBox^  chk_G01;
    public: System::Windows::Forms::CheckBox^  chk_TYPE_L1CA;

    public: System::Windows::Forms::CheckBox^  chk_GALL;
    public: System::Windows::Forms::OpenFileDialog^  inputfiledlg;
    public: System::Windows::Forms::FolderBrowserDialog^  inputdirdlg;
    public: System::Windows::Forms::GroupBox^  gb_qzs;

    public: System::Windows::Forms::CheckBox^  chk_TYPE_LEX;


    public: System::Windows::Forms::CheckBox^  chk_Q01;
    public: System::Windows::Forms::CheckBox^  chk_TYPE_L1CAQZS;

    public: System::Windows::Forms::Button^  b_start;
    public: System::Windows::Forms::Button^  b_stop;
    public: System::Windows::Forms::Button^  b_exit;

    public: radardlg^ radar;
    public: monitordlg^ monitor;
    public: trkprmdlg^ trkprm;
    public: SDR^ sdr;
    public: System::Windows::Forms::Button^  b_input2;
    public: System::Windows::Forms::TextBox^  tb_input2;
    public: System::Windows::Forms::CheckBox^  chk_input2;

    public: System::Windows::Forms::Label^  l_input2;
    public: System::Windows::Forms::Label^  l_input1;
    public: System::Windows::Forms::Label^  label1;
    public: CONFIG^ config;
    public: System::Windows::Forms::CheckBox^  chk_spec;
    public: System::Windows::Forms::RadioButton^  rb_spec1;
    public: System::Windows::Forms::RadioButton^  rb_spec2;
    public: System::Windows::Forms::CheckBox^  chk_monitor;
    public: System::Windows::Forms::CheckBox^  chk_TYPE_SAIF;

    public: System::Windows::Forms::TextBox^  tb_saif_port;
    public: System::Windows::Forms::Label^  l_saif;
    public: System::Windows::Forms::CheckBox^  chk_saif;
    public: System::Windows::Forms::RadioButton^  rb_G_FE2;

    public: System::Windows::Forms::RadioButton^  rb_G_FE1;
    public: System::Windows::Forms::RadioButton^  rb_Q_FE2;


    public: System::Windows::Forms::RadioButton^  rb_Q_FE1;
    public: System::Windows::Forms::GroupBox^  gb_glo;


    public: System::Windows::Forms::RadioButton^  rb_R_FE2;

    public: System::Windows::Forms::RadioButton^  rb_R_FE1;

    public: System::Windows::Forms::CheckBox^  chk_R6;

    public: System::Windows::Forms::CheckBox^  chk_R5;

    public: System::Windows::Forms::CheckBox^  chk_R4;

    public: System::Windows::Forms::CheckBox^  chk_R2;

    public: System::Windows::Forms::CheckBox^  chk_R1;

    public: System::Windows::Forms::CheckBox^  chk_R0;

    public: System::Windows::Forms::CheckBox^  chk_R_1;

    public: System::Windows::Forms::CheckBox^  chk_R_2;

    public: System::Windows::Forms::CheckBox^  chk_R_3;

    public: System::Windows::Forms::CheckBox^  chk_R_4;

    public: System::Windows::Forms::CheckBox^  chk_R_5;

    public: System::Windows::Forms::CheckBox^  chk_R_6;

    public: System::Windows::Forms::CheckBox^  chk_R_7;

    public: System::Windows::Forms::CheckBox^  chk_TYPE_G1;


    public: System::Windows::Forms::CheckBox^  chk_RALL;
    public: System::Windows::Forms::GroupBox^  gb_gal;


    public: System::Windows::Forms::RadioButton^  rb_E_FE2;

    public: System::Windows::Forms::RadioButton^  rb_E_FE1;

    public: System::Windows::Forms::CheckBox^  chk_E20;
    public: System::Windows::Forms::CheckBox^  chk_E19;



    public: System::Windows::Forms::CheckBox^  chk_E12;

    public: System::Windows::Forms::CheckBox^  chk_E11;

    public: System::Windows::Forms::CheckBox^  chk_TYPE_E1B;

    public: System::Windows::Forms::CheckBox^  chk_EALL;
    public: System::Windows::Forms::GroupBox^  gb_bds;


    public: System::Windows::Forms::RadioButton^  rb_C_FE2;

    public: System::Windows::Forms::RadioButton^  rb_C_FE1;

    public: System::Windows::Forms::CheckBox^  chk_C14;

    public: System::Windows::Forms::CheckBox^  chk_C13;

    public: System::Windows::Forms::CheckBox^  chk_C12;

    public: System::Windows::Forms::CheckBox^  chk_C11;

    public: System::Windows::Forms::CheckBox^  chk_C10;

    public: System::Windows::Forms::CheckBox^  chk_C09;

    public: System::Windows::Forms::CheckBox^  chk_C08;

    public: System::Windows::Forms::CheckBox^  chk_C07;

    public: System::Windows::Forms::CheckBox^  chk_C06;

    public: System::Windows::Forms::CheckBox^  chk_C05;


    public: System::Windows::Forms::CheckBox^  chk_C03;

    public: System::Windows::Forms::CheckBox^  chk_C02;

    public: System::Windows::Forms::CheckBox^  chk_C01;

    public: System::Windows::Forms::CheckBox^  chk_TYPE_B1I;

    public: System::Windows::Forms::CheckBox^  chk_CALL;
    public: System::Windows::Forms::GroupBox^  gb_sbs;


    public: System::Windows::Forms::RadioButton^  rb_S_FE2;

    public: System::Windows::Forms::RadioButton^  rb_S_FE1;

    public: System::Windows::Forms::CheckBox^  chk_S138;

    public: System::Windows::Forms::CheckBox^  chk_S137;

    public: System::Windows::Forms::CheckBox^  chk_S136;

    public: System::Windows::Forms::CheckBox^  chk_S135;

    public: System::Windows::Forms::CheckBox^  chk_S134;

    public: System::Windows::Forms::CheckBox^  chk_S133;

    public: System::Windows::Forms::CheckBox^  chk_S132;

    public: System::Windows::Forms::CheckBox^  chk_S131;

    public: System::Windows::Forms::CheckBox^  chk_S130;

    public: System::Windows::Forms::CheckBox^  chk_S129;

    public: System::Windows::Forms::CheckBox^  chk_S128;

    public: System::Windows::Forms::CheckBox^  chk_S127;

    public: System::Windows::Forms::CheckBox^  chk_S126;

    public: System::Windows::Forms::CheckBox^  chk_S125;

    public: System::Windows::Forms::CheckBox^  chk_S124;

    public: System::Windows::Forms::CheckBox^  chk_S123;

    public: System::Windows::Forms::CheckBox^  chk_S122;

    public: System::Windows::Forms::CheckBox^  chk_S121;

    public: System::Windows::Forms::CheckBox^  chk_S120;
    public: System::Windows::Forms::CheckBox^  chk_TYPE_SBASL1;


    public: System::Windows::Forms::CheckBox^  chk_SALL;
    public: System::Windows::Forms::CheckBox^  chk_R3;
    public: System::Windows::Forms::CheckBox^  chk_C04;
    private: System::Windows::Forms::GroupBox^  gp_FE1;
    public: 

    public: 

    public: System::Windows::Forms::ComboBox^  cb_cf1;
    public: 

    public: System::Windows::Forms::Label^  label4;
    public: System::Windows::Forms::Label^  lb_cf1;
    private: 

    public: System::Windows::Forms::Label^  label2;
    public: System::Windows::Forms::Label^  l_f1sf;
    public: System::Windows::Forms::Label^  l_f1sft;
    public: System::Windows::Forms::TextBox^  tb_f1if;
    public: System::Windows::Forms::Label^  l_f1if;
    public: System::Windows::Forms::GroupBox^  groupBox3;
    public: System::Windows::Forms::RadioButton^  rb_f1IQ;
    public: System::Windows::Forms::RadioButton^  rb_f1I;
    public: System::Windows::Forms::TextBox^  tb_f1sf;
    private: System::Windows::Forms::GroupBox^  gp_FE2;
    public: 

    public: 

    public: System::Windows::Forms::ComboBox^  cb_cf2;
    public: 

    public: System::Windows::Forms::Label^  label5;
    public: System::Windows::Forms::Label^  lb_cf2;
    private: 

    public: System::Windows::Forms::Label^  label7;
    public: System::Windows::Forms::Label^  l_f2sf;
    public: System::Windows::Forms::Label^  l_f2sft;
    public: System::Windows::Forms::TextBox^  tb_f2if;
    public: System::Windows::Forms::Label^  l_f2if;
    public: System::Windows::Forms::GroupBox^  groupBox9;
    public: System::Windows::Forms::RadioButton^  rb_f2IQ;
    public: System::Windows::Forms::RadioButton^  rb_f2I;
    public: System::Windows::Forms::TextBox^  tb_f2sf;

    public: 
    public: System::Windows::Forms::Label^  lb_clk1;
    private: 
    public: System::Windows::Forms::Label^  lb_clk2;
    public: System::Windows::Forms::TextBox^  tb_clk;
    private: System::Windows::Forms::Button^  b_trkprm;
    public: 

    public: System::Windows::Forms::Label^  label3;
    public: System::Windows::Forms::CheckBox^  chk_log;
    private: System::Windows::Forms::GroupBox^  gb_misc;
    public: 
    public: System::Windows::Forms::Label^  label10;
    private: 
    public: System::Windows::Forms::Label^  label9;
    public: System::Windows::Forms::TextBox^  tb_lon;
    public: System::Windows::Forms::TextBox^  tb_lat;
    public: System::Windows::Forms::Label^  label6;
    private: System::Windows::Forms::Button^  b_radar;
    public: 


    private: 
    public: 
    private: 
    public: 



    public: 

    private:
        System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(maindlg::typeid));
            this->gb_input = (gcnew System::Windows::Forms::GroupBox());
            this->chk_input2 = (gcnew System::Windows::Forms::CheckBox());
            this->l_input2 = (gcnew System::Windows::Forms::Label());
            this->l_input1 = (gcnew System::Windows::Forms::Label());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->b_input2 = (gcnew System::Windows::Forms::Button());
            this->tb_input2 = (gcnew System::Windows::Forms::TextBox());
            this->b_input1 = (gcnew System::Windows::Forms::Button());
            this->tb_input1 = (gcnew System::Windows::Forms::TextBox());
            this->cmb_input = (gcnew System::Windows::Forms::ComboBox());
            this->gb_output = (gcnew System::Windows::Forms::GroupBox());
            this->chk_log = (gcnew System::Windows::Forms::CheckBox());
            this->tb_saif_port = (gcnew System::Windows::Forms::TextBox());
            this->l_saif = (gcnew System::Windows::Forms::Label());
            this->chk_saif = (gcnew System::Windows::Forms::CheckBox());
            this->b_rinex = (gcnew System::Windows::Forms::Button());
            this->tb_rinex_dir = (gcnew System::Windows::Forms::TextBox());
            this->tb_rtcm_port = (gcnew System::Windows::Forms::TextBox());
            this->l_rtcm = (gcnew System::Windows::Forms::Label());
            this->l_rinex = (gcnew System::Windows::Forms::Label());
            this->tb_lex_port = (gcnew System::Windows::Forms::TextBox());
            this->cmb_outint = (gcnew System::Windows::Forms::ComboBox());
            this->l_lex = (gcnew System::Windows::Forms::Label());
            this->l_output = (gcnew System::Windows::Forms::Label());
            this->chk_lex = (gcnew System::Windows::Forms::CheckBox());
            this->chk_rtcm = (gcnew System::Windows::Forms::CheckBox());
            this->chk_rinex = (gcnew System::Windows::Forms::CheckBox());
            this->gb_setting = (gcnew System::Windows::Forms::GroupBox());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->b_trkprm = (gcnew System::Windows::Forms::Button());
            this->lb_clk1 = (gcnew System::Windows::Forms::Label());
            this->lb_clk2 = (gcnew System::Windows::Forms::Label());
            this->tb_clk = (gcnew System::Windows::Forms::TextBox());
            this->gp_FE2 = (gcnew System::Windows::Forms::GroupBox());
            this->cb_cf2 = (gcnew System::Windows::Forms::ComboBox());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->lb_cf2 = (gcnew System::Windows::Forms::Label());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->l_f2sf = (gcnew System::Windows::Forms::Label());
            this->l_f2sft = (gcnew System::Windows::Forms::Label());
            this->tb_f2if = (gcnew System::Windows::Forms::TextBox());
            this->l_f2if = (gcnew System::Windows::Forms::Label());
            this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
            this->rb_f2IQ = (gcnew System::Windows::Forms::RadioButton());
            this->rb_f2I = (gcnew System::Windows::Forms::RadioButton());
            this->tb_f2sf = (gcnew System::Windows::Forms::TextBox());
            this->gp_FE1 = (gcnew System::Windows::Forms::GroupBox());
            this->cb_cf1 = (gcnew System::Windows::Forms::ComboBox());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->lb_cf1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->l_f1sf = (gcnew System::Windows::Forms::Label());
            this->l_f1sft = (gcnew System::Windows::Forms::Label());
            this->tb_f1if = (gcnew System::Windows::Forms::TextBox());
            this->l_f1if = (gcnew System::Windows::Forms::Label());
            this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
            this->rb_f1IQ = (gcnew System::Windows::Forms::RadioButton());
            this->rb_f1I = (gcnew System::Windows::Forms::RadioButton());
            this->tb_f1sf = (gcnew System::Windows::Forms::TextBox());
            this->chk_plottrk = (gcnew System::Windows::Forms::CheckBox());
            this->chk_plotacq = (gcnew System::Windows::Forms::CheckBox());
            this->gb_gps = (gcnew System::Windows::Forms::GroupBox());
            this->rb_G_FE2 = (gcnew System::Windows::Forms::RadioButton());
            this->rb_G_FE1 = (gcnew System::Windows::Forms::RadioButton());
            this->chk_G32 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G31 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G30 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G29 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G28 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G27 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G26 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G25 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G24 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G23 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G22 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G21 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G20 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G19 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G18 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G17 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G16 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G15 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G14 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G13 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G12 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G11 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G10 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G09 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G08 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G07 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G06 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G05 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G04 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G03 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G02 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_G01 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_TYPE_L1CA = (gcnew System::Windows::Forms::CheckBox());
            this->chk_GALL = (gcnew System::Windows::Forms::CheckBox());
            this->inputfiledlg = (gcnew System::Windows::Forms::OpenFileDialog());
            this->inputdirdlg = (gcnew System::Windows::Forms::FolderBrowserDialog());
            this->gb_qzs = (gcnew System::Windows::Forms::GroupBox());
            this->rb_Q_FE2 = (gcnew System::Windows::Forms::RadioButton());
            this->rb_Q_FE1 = (gcnew System::Windows::Forms::RadioButton());
            this->chk_TYPE_SAIF = (gcnew System::Windows::Forms::CheckBox());
            this->chk_TYPE_LEX = (gcnew System::Windows::Forms::CheckBox());
            this->chk_Q01 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_TYPE_L1CAQZS = (gcnew System::Windows::Forms::CheckBox());
            this->b_start = (gcnew System::Windows::Forms::Button());
            this->b_stop = (gcnew System::Windows::Forms::Button());
            this->b_exit = (gcnew System::Windows::Forms::Button());
            this->chk_spec = (gcnew System::Windows::Forms::CheckBox());
            this->rb_spec1 = (gcnew System::Windows::Forms::RadioButton());
            this->rb_spec2 = (gcnew System::Windows::Forms::RadioButton());
            this->chk_monitor = (gcnew System::Windows::Forms::CheckBox());
            this->gb_glo = (gcnew System::Windows::Forms::GroupBox());
            this->chk_R3 = (gcnew System::Windows::Forms::CheckBox());
            this->rb_R_FE2 = (gcnew System::Windows::Forms::RadioButton());
            this->rb_R_FE1 = (gcnew System::Windows::Forms::RadioButton());
            this->chk_R6 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_R5 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_R4 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_R2 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_R1 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_R0 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_R_1 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_R_2 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_R_3 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_R_4 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_R_5 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_R_6 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_R_7 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_TYPE_G1 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_RALL = (gcnew System::Windows::Forms::CheckBox());
            this->gb_gal = (gcnew System::Windows::Forms::GroupBox());
            this->rb_E_FE2 = (gcnew System::Windows::Forms::RadioButton());
            this->rb_E_FE1 = (gcnew System::Windows::Forms::RadioButton());
            this->chk_E20 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_E19 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_E12 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_E11 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_TYPE_E1B = (gcnew System::Windows::Forms::CheckBox());
            this->chk_EALL = (gcnew System::Windows::Forms::CheckBox());
            this->gb_bds = (gcnew System::Windows::Forms::GroupBox());
            this->rb_C_FE2 = (gcnew System::Windows::Forms::RadioButton());
            this->rb_C_FE1 = (gcnew System::Windows::Forms::RadioButton());
            this->chk_C14 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_C13 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_C12 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_C11 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_C10 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_C09 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_C08 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_C07 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_C06 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_C05 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_C04 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_C03 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_C02 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_C01 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_TYPE_B1I = (gcnew System::Windows::Forms::CheckBox());
            this->chk_CALL = (gcnew System::Windows::Forms::CheckBox());
            this->gb_sbs = (gcnew System::Windows::Forms::GroupBox());
            this->rb_S_FE2 = (gcnew System::Windows::Forms::RadioButton());
            this->rb_S_FE1 = (gcnew System::Windows::Forms::RadioButton());
            this->chk_S138 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_S137 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_S136 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_S135 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_S134 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_S133 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_S132 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_S131 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_S130 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_S129 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_S128 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_S127 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_S126 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_S125 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_S124 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_S123 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_S122 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_S121 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_S120 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_TYPE_SBASL1 = (gcnew System::Windows::Forms::CheckBox());
            this->chk_SALL = (gcnew System::Windows::Forms::CheckBox());
            this->gb_misc = (gcnew System::Windows::Forms::GroupBox());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->tb_lon = (gcnew System::Windows::Forms::TextBox());
            this->tb_lat = (gcnew System::Windows::Forms::TextBox());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->b_radar = (gcnew System::Windows::Forms::Button());
            this->gb_input->SuspendLayout();
            this->gb_output->SuspendLayout();
            this->gb_setting->SuspendLayout();
            this->gp_FE2->SuspendLayout();
            this->groupBox9->SuspendLayout();
            this->gp_FE1->SuspendLayout();
            this->groupBox3->SuspendLayout();
            this->gb_gps->SuspendLayout();
            this->gb_qzs->SuspendLayout();
            this->gb_glo->SuspendLayout();
            this->gb_gal->SuspendLayout();
            this->gb_bds->SuspendLayout();
            this->gb_sbs->SuspendLayout();
            this->gb_misc->SuspendLayout();
            this->SuspendLayout();
            // 
            // gb_input
            // 
            this->gb_input->Controls->Add(this->chk_input2);
            this->gb_input->Controls->Add(this->l_input2);
            this->gb_input->Controls->Add(this->l_input1);
            this->gb_input->Controls->Add(this->label1);
            this->gb_input->Controls->Add(this->b_input2);
            this->gb_input->Controls->Add(this->tb_input2);
            this->gb_input->Controls->Add(this->b_input1);
            this->gb_input->Controls->Add(this->tb_input1);
            this->gb_input->Controls->Add(this->cmb_input);
            this->gb_input->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Bold));
            this->gb_input->Location = System::Drawing::Point(7, 7);
            this->gb_input->Name = L"gb_input";
            this->gb_input->Size = System::Drawing::Size(414, 87);
            this->gb_input->TabIndex = 0;
            this->gb_input->TabStop = false;
            this->gb_input->Text = L"Input";
            // 
            // chk_input2
            // 
            this->chk_input2->AutoSize = true;
            this->chk_input2->Enabled = false;
            this->chk_input2->Location = System::Drawing::Point(67, 65);
            this->chk_input2->Name = L"chk_input2";
            this->chk_input2->Size = System::Drawing::Size(15, 14);
            this->chk_input2->TabIndex = 19;
            this->chk_input2->UseVisualStyleBackColor = true;
            this->chk_input2->CheckedChanged += gcnew System::EventHandler(this, &maindlg::chk_input2_CheckedChanged);
            // 
            // l_input2
            // 
            this->l_input2->AutoSize = true;
            this->l_input2->Enabled = false;
            this->l_input2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->l_input2->Location = System::Drawing::Point(7, 65);
            this->l_input2->Name = L"l_input2";
            this->l_input2->Size = System::Drawing::Size(57, 12);
            this->l_input2->TabIndex = 17;
            this->l_input2->Text = L"FrontEnd2";
            // 
            // l_input1
            // 
            this->l_input1->AutoSize = true;
            this->l_input1->Enabled = false;
            this->l_input1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->l_input1->Location = System::Drawing::Point(7, 43);
            this->l_input1->Name = L"l_input1";
            this->l_input1->Size = System::Drawing::Size(57, 12);
            this->l_input1->TabIndex = 16;
            this->l_input1->Text = L"FrontEnd1";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->label1->Location = System::Drawing::Point(7, 18);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(59, 12);
            this->label1->TabIndex = 14;
            this->label1->Text = L"Input Type";
            // 
            // b_input2
            // 
            this->b_input2->Enabled = false;
            this->b_input2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->b_input2->Location = System::Drawing::Point(393, 61);
            this->b_input2->Name = L"b_input2";
            this->b_input2->Size = System::Drawing::Size(18, 20);
            this->b_input2->TabIndex = 4;
            this->b_input2->Text = L"...";
            this->b_input2->UseVisualStyleBackColor = true;
            this->b_input2->Click += gcnew System::EventHandler(this, &maindlg::b_input2_Click);
            // 
            // tb_input2
            // 
            this->tb_input2->Enabled = false;
            this->tb_input2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->tb_input2->Location = System::Drawing::Point(84, 62);
            this->tb_input2->Name = L"tb_input2";
            this->tb_input2->Size = System::Drawing::Size(307, 19);
            this->tb_input2->TabIndex = 3;
            // 
            // b_input1
            // 
            this->b_input1->Enabled = false;
            this->b_input1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->b_input1->Location = System::Drawing::Point(393, 39);
            this->b_input1->Name = L"b_input1";
            this->b_input1->Size = System::Drawing::Size(18, 20);
            this->b_input1->TabIndex = 2;
            this->b_input1->Text = L"...";
            this->b_input1->UseVisualStyleBackColor = true;
            this->b_input1->Click += gcnew System::EventHandler(this, &maindlg::b_input1_Click);
            // 
            // tb_input1
            // 
            this->tb_input1->Enabled = false;
            this->tb_input1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->tb_input1->Location = System::Drawing::Point(84, 40);
            this->tb_input1->Name = L"tb_input1";
            this->tb_input1->Size = System::Drawing::Size(307, 19);
            this->tb_input1->TabIndex = 1;
            // 
            // cmb_input
            // 
            this->cmb_input->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cmb_input->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->cmb_input->FormattingEnabled = true;
            this->cmb_input->Items->AddRange(gcnew cli::array< System::Object^  >(11) {L"STEREO", L"GN3Sv2", L"GN3Sv3", L"RTL-SDR", L"BladeRF", 
                L"File (STEREO)", L"File (GN3Sv2)", L"File (GN3Sv3)", L"File (RTL-SDR)", L"File (BladeRF)", L"File"});
            this->cmb_input->Location = System::Drawing::Point(69, 15);
            this->cmb_input->Name = L"cmb_input";
            this->cmb_input->Size = System::Drawing::Size(100, 20);
            this->cmb_input->TabIndex = 0;
            this->cmb_input->SelectedIndexChanged += gcnew System::EventHandler(this, &maindlg::comb_input_SelectedIndexChanged);
            // 
            // gb_output
            // 
            this->gb_output->Controls->Add(this->chk_log);
            this->gb_output->Controls->Add(this->tb_saif_port);
            this->gb_output->Controls->Add(this->l_saif);
            this->gb_output->Controls->Add(this->chk_saif);
            this->gb_output->Controls->Add(this->b_rinex);
            this->gb_output->Controls->Add(this->tb_rinex_dir);
            this->gb_output->Controls->Add(this->tb_rtcm_port);
            this->gb_output->Controls->Add(this->l_rtcm);
            this->gb_output->Controls->Add(this->l_rinex);
            this->gb_output->Controls->Add(this->tb_lex_port);
            this->gb_output->Controls->Add(this->cmb_outint);
            this->gb_output->Controls->Add(this->l_lex);
            this->gb_output->Controls->Add(this->l_output);
            this->gb_output->Controls->Add(this->chk_lex);
            this->gb_output->Controls->Add(this->chk_rtcm);
            this->gb_output->Controls->Add(this->chk_rinex);
            this->gb_output->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Bold));
            this->gb_output->Location = System::Drawing::Point(7, 98);
            this->gb_output->Name = L"gb_output";
            this->gb_output->Size = System::Drawing::Size(414, 88);
            this->gb_output->TabIndex = 1;
            this->gb_output->TabStop = false;
            this->gb_output->Text = L"Output";
            // 
            // chk_log
            // 
            this->chk_log->AutoSize = true;
            this->chk_log->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_log->Location = System::Drawing::Point(358, 64);
            this->chk_log->Name = L"chk_log";
            this->chk_log->Size = System::Drawing::Size(46, 16);
            this->chk_log->TabIndex = 17;
            this->chk_log->Text = L"LOG";
            this->chk_log->UseVisualStyleBackColor = true;
            // 
            // tb_saif_port
            // 
            this->tb_saif_port->Enabled = false;
            this->tb_saif_port->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->tb_saif_port->Location = System::Drawing::Point(310, 38);
            this->tb_saif_port->Name = L"tb_saif_port";
            this->tb_saif_port->Size = System::Drawing::Size(59, 19);
            this->tb_saif_port->TabIndex = 16;
            this->tb_saif_port->Text = L"9997";
            this->tb_saif_port->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            // 
            // l_saif
            // 
            this->l_saif->AutoSize = true;
            this->l_saif->Enabled = false;
            this->l_saif->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->l_saif->Location = System::Drawing::Point(282, 41);
            this->l_saif->Name = L"l_saif";
            this->l_saif->Size = System::Drawing::Size(28, 12);
            this->l_saif->TabIndex = 15;
            this->l_saif->Text = L"Port:";
            // 
            // chk_saif
            // 
            this->chk_saif->AutoSize = true;
            this->chk_saif->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_saif->Location = System::Drawing::Point(194, 40);
            this->chk_saif->Name = L"chk_saif";
            this->chk_saif->Size = System::Drawing::Size(85, 16);
            this->chk_saif->TabIndex = 14;
            this->chk_saif->Text = L"SBAS/SAIF";
            this->chk_saif->UseVisualStyleBackColor = true;
            this->chk_saif->CheckedChanged += gcnew System::EventHandler(this, &maindlg::chk_saif_CheckedChanged);
            // 
            // b_rinex
            // 
            this->b_rinex->Enabled = false;
            this->b_rinex->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->b_rinex->Location = System::Drawing::Point(393, 16);
            this->b_rinex->Name = L"b_rinex";
            this->b_rinex->Size = System::Drawing::Size(18, 20);
            this->b_rinex->TabIndex = 13;
            this->b_rinex->Text = L"...";
            this->b_rinex->UseVisualStyleBackColor = true;
            this->b_rinex->Click += gcnew System::EventHandler(this, &maindlg::b_rinex_Click);
            // 
            // tb_rinex_dir
            // 
            this->tb_rinex_dir->Enabled = false;
            this->tb_rinex_dir->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->tb_rinex_dir->Location = System::Drawing::Point(119, 16);
            this->tb_rinex_dir->Name = L"tb_rinex_dir";
            this->tb_rinex_dir->Size = System::Drawing::Size(272, 19);
            this->tb_rinex_dir->TabIndex = 12;
            this->tb_rinex_dir->Text = L"../test/output";
            // 
            // tb_rtcm_port
            // 
            this->tb_rtcm_port->Enabled = false;
            this->tb_rtcm_port->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->tb_rtcm_port->Location = System::Drawing::Point(119, 38);
            this->tb_rtcm_port->Name = L"tb_rtcm_port";
            this->tb_rtcm_port->Size = System::Drawing::Size(59, 19);
            this->tb_rtcm_port->TabIndex = 11;
            this->tb_rtcm_port->Text = L"9999";
            this->tb_rtcm_port->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            // 
            // l_rtcm
            // 
            this->l_rtcm->AutoSize = true;
            this->l_rtcm->Enabled = false;
            this->l_rtcm->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->l_rtcm->Location = System::Drawing::Point(92, 41);
            this->l_rtcm->Name = L"l_rtcm";
            this->l_rtcm->Size = System::Drawing::Size(28, 12);
            this->l_rtcm->TabIndex = 10;
            this->l_rtcm->Text = L"Port:";
            // 
            // l_rinex
            // 
            this->l_rinex->AutoSize = true;
            this->l_rinex->Enabled = false;
            this->l_rinex->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->l_rinex->Location = System::Drawing::Point(91, 19);
            this->l_rinex->Name = L"l_rinex";
            this->l_rinex->Size = System::Drawing::Size(22, 12);
            this->l_rinex->TabIndex = 9;
            this->l_rinex->Text = L"Dir:";
            // 
            // tb_lex_port
            // 
            this->tb_lex_port->Enabled = false;
            this->tb_lex_port->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->tb_lex_port->Location = System::Drawing::Point(120, 60);
            this->tb_lex_port->Name = L"tb_lex_port";
            this->tb_lex_port->Size = System::Drawing::Size(59, 19);
            this->tb_lex_port->TabIndex = 8;
            this->tb_lex_port->Text = L"9998";
            this->tb_lex_port->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            // 
            // cmb_outint
            // 
            this->cmb_outint->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cmb_outint->Enabled = false;
            this->cmb_outint->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->cmb_outint->FormattingEnabled = true;
            this->cmb_outint->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"1Hz", L"5Hz", L"10Hz"});
            this->cmb_outint->Location = System::Drawing::Point(279, 60);
            this->cmb_outint->Name = L"cmb_outint";
            this->cmb_outint->Size = System::Drawing::Size(59, 20);
            this->cmb_outint->TabIndex = 6;
            // 
            // l_lex
            // 
            this->l_lex->AutoSize = true;
            this->l_lex->Enabled = false;
            this->l_lex->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->l_lex->Location = System::Drawing::Point(92, 63);
            this->l_lex->Name = L"l_lex";
            this->l_lex->Size = System::Drawing::Size(28, 12);
            this->l_lex->TabIndex = 5;
            this->l_lex->Text = L"Port:";
            // 
            // l_output
            // 
            this->l_output->AutoSize = true;
            this->l_output->Enabled = false;
            this->l_output->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->l_output->Location = System::Drawing::Point(194, 64);
            this->l_output->Name = L"l_output";
            this->l_output->Size = System::Drawing::Size(83, 12);
            this->l_output->TabIndex = 3;
            this->l_output->Text = L"Output Interval:";
            // 
            // chk_lex
            // 
            this->chk_lex->AutoSize = true;
            this->chk_lex->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_lex->Location = System::Drawing::Point(9, 62);
            this->chk_lex->Name = L"chk_lex";
            this->chk_lex->Size = System::Drawing::Size(77, 16);
            this->chk_lex->TabIndex = 2;
            this->chk_lex->Text = L"QZSS LEX";
            this->chk_lex->UseVisualStyleBackColor = true;
            this->chk_lex->CheckedChanged += gcnew System::EventHandler(this, &maindlg::chk_lex_CheckedChanged);
            // 
            // chk_rtcm
            // 
            this->chk_rtcm->AutoSize = true;
            this->chk_rtcm->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_rtcm->Location = System::Drawing::Point(9, 40);
            this->chk_rtcm->Name = L"chk_rtcm";
            this->chk_rtcm->Size = System::Drawing::Size(85, 16);
            this->chk_rtcm->TabIndex = 1;
            this->chk_rtcm->Text = L"RTCM MSM";
            this->chk_rtcm->UseVisualStyleBackColor = true;
            this->chk_rtcm->CheckedChanged += gcnew System::EventHandler(this, &maindlg::chk_rtcm_CheckedChanged);
            // 
            // chk_rinex
            // 
            this->chk_rinex->AutoSize = true;
            this->chk_rinex->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_rinex->Location = System::Drawing::Point(9, 18);
            this->chk_rinex->Name = L"chk_rinex";
            this->chk_rinex->Size = System::Drawing::Size(57, 16);
            this->chk_rinex->TabIndex = 0;
            this->chk_rinex->Text = L"RINEX";
            this->chk_rinex->UseVisualStyleBackColor = true;
            this->chk_rinex->CheckedChanged += gcnew System::EventHandler(this, &maindlg::chk_rinex_CheckedChanged);
            // 
            // gb_setting
            // 
            this->gb_setting->Controls->Add(this->label3);
            this->gb_setting->Controls->Add(this->b_trkprm);
            this->gb_setting->Controls->Add(this->lb_clk1);
            this->gb_setting->Controls->Add(this->lb_clk2);
            this->gb_setting->Controls->Add(this->tb_clk);
            this->gb_setting->Controls->Add(this->gp_FE2);
            this->gb_setting->Controls->Add(this->gp_FE1);
            this->gb_setting->Controls->Add(this->chk_plottrk);
            this->gb_setting->Controls->Add(this->chk_plotacq);
            this->gb_setting->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Bold));
            this->gb_setting->Location = System::Drawing::Point(7, 190);
            this->gb_setting->Name = L"gb_setting";
            this->gb_setting->Size = System::Drawing::Size(414, 187);
            this->gb_setting->TabIndex = 4;
            this->gb_setting->TabStop = false;
            this->gb_setting->Text = L"Setting";
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->label3->Location = System::Drawing::Point(9, 166);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(145, 12);
            this->label3->TabIndex = 34;
            this->label3->Text = L"Tracking Parameter Setting";
            // 
            // b_trkprm
            // 
            this->b_trkprm->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->b_trkprm->Location = System::Drawing::Point(154, 161);
            this->b_trkprm->Name = L"b_trkprm";
            this->b_trkprm->Size = System::Drawing::Size(20, 20);
            this->b_trkprm->TabIndex = 33;
            this->b_trkprm->Text = L"...";
            this->b_trkprm->UseVisualStyleBackColor = true;
            this->b_trkprm->Click += gcnew System::EventHandler(this, &maindlg::button1_Click);
            // 
            // lb_clk1
            // 
            this->lb_clk1->AutoSize = true;
            this->lb_clk1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->lb_clk1->Location = System::Drawing::Point(215, 145);
            this->lb_clk1->Name = L"lb_clk1";
            this->lb_clk1->Size = System::Drawing::Size(63, 12);
            this->lb_clk1->TabIndex = 32;
            this->lb_clk1->Text = L"Clock Error";
            // 
            // lb_clk2
            // 
            this->lb_clk2->AutoSize = true;
            this->lb_clk2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->lb_clk2->Location = System::Drawing::Point(313, 145);
            this->lb_clk2->Name = L"lb_clk2";
            this->lb_clk2->Size = System::Drawing::Size(26, 12);
            this->lb_clk2->TabIndex = 31;
            this->lb_clk2->Text = L"ppm";
            // 
            // tb_clk
            // 
            this->tb_clk->Enabled = false;
            this->tb_clk->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->tb_clk->Location = System::Drawing::Point(278, 142);
            this->tb_clk->Name = L"tb_clk";
            this->tb_clk->Size = System::Drawing::Size(35, 19);
            this->tb_clk->TabIndex = 30;
            this->tb_clk->Text = L"0";
            this->tb_clk->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            // 
            // gp_FE2
            // 
            this->gp_FE2->Controls->Add(this->cb_cf2);
            this->gp_FE2->Controls->Add(this->label5);
            this->gp_FE2->Controls->Add(this->lb_cf2);
            this->gp_FE2->Controls->Add(this->label7);
            this->gp_FE2->Controls->Add(this->l_f2sf);
            this->gp_FE2->Controls->Add(this->l_f2sft);
            this->gp_FE2->Controls->Add(this->tb_f2if);
            this->gp_FE2->Controls->Add(this->l_f2if);
            this->gp_FE2->Controls->Add(this->groupBox9);
            this->gp_FE2->Controls->Add(this->tb_f2sf);
            this->gp_FE2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Bold));
            this->gp_FE2->Location = System::Drawing::Point(7, 80);
            this->gp_FE2->Name = L"gp_FE2";
            this->gp_FE2->Size = System::Drawing::Size(399, 58);
            this->gp_FE2->TabIndex = 30;
            this->gp_FE2->TabStop = false;
            this->gp_FE2->Text = L"FrontEnd 2";
            // 
            // cb_cf2
            // 
            this->cb_cf2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cb_cf2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->cb_cf2->FormattingEnabled = true;
            this->cb_cf2->Location = System::Drawing::Point(89, 29);
            this->cb_cf2->Name = L"cb_cf2";
            this->cb_cf2->Size = System::Drawing::Size(115, 20);
            this->cb_cf2->TabIndex = 29;
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->label5->Location = System::Drawing::Point(359, 34);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(27, 12);
            this->label5->TabIndex = 28;
            this->label5->Text = L"MHz";
            // 
            // lb_cf2
            // 
            this->lb_cf2->AutoSize = true;
            this->lb_cf2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->lb_cf2->Location = System::Drawing::Point(102, 14);
            this->lb_cf2->Name = L"lb_cf2";
            this->lb_cf2->Size = System::Drawing::Size(90, 12);
            this->lb_cf2->TabIndex = 27;
            this->lb_cf2->Text = L"Center Freqency";
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->label7->Location = System::Drawing::Point(264, 34);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(27, 12);
            this->label7->TabIndex = 26;
            this->label7->Text = L"MHz";
            // 
            // l_f2sf
            // 
            this->l_f2sf->AutoSize = true;
            this->l_f2sf->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->l_f2sf->Location = System::Drawing::Point(210, 14);
            this->l_f2sf->Name = L"l_f2sf";
            this->l_f2sf->Size = System::Drawing::Size(80, 12);
            this->l_f2sf->TabIndex = 25;
            this->l_f2sf->Text = L"Sampling Freq.";
            // 
            // l_f2sft
            // 
            this->l_f2sft->AutoSize = true;
            this->l_f2sft->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->l_f2sft->Location = System::Drawing::Point(6, 14);
            this->l_f2sft->Name = L"l_f2sft";
            this->l_f2sft->Size = System::Drawing::Size(80, 12);
            this->l_f2sft->TabIndex = 20;
            this->l_f2sft->Text = L"Sampling Type";
            // 
            // tb_f2if
            // 
            this->tb_f2if->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->tb_f2if->Location = System::Drawing::Point(309, 31);
            this->tb_f2if->Name = L"tb_f2if";
            this->tb_f2if->Size = System::Drawing::Size(48, 19);
            this->tb_f2if->TabIndex = 24;
            this->tb_f2if->Text = L"0.0";
            this->tb_f2if->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            // 
            // l_f2if
            // 
            this->l_f2if->AutoSize = true;
            this->l_f2if->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->l_f2if->Location = System::Drawing::Point(299, 14);
            this->l_f2if->Name = L"l_f2if";
            this->l_f2if->Size = System::Drawing::Size(97, 12);
            this->l_f2if->TabIndex = 23;
            this->l_f2if->Text = L"Intermediate Freq.";
            // 
            // groupBox9
            // 
            this->groupBox9->BackColor = System::Drawing::Color::Transparent;
            this->groupBox9->Controls->Add(this->rb_f2IQ);
            this->groupBox9->Controls->Add(this->rb_f2I);
            this->groupBox9->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->groupBox9->Location = System::Drawing::Point(7, 22);
            this->groupBox9->Name = L"groupBox9";
            this->groupBox9->Size = System::Drawing::Size(74, 29);
            this->groupBox9->TabIndex = 22;
            this->groupBox9->TabStop = false;
            // 
            // rb_f2IQ
            // 
            this->rb_f2IQ->AutoSize = true;
            this->rb_f2IQ->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->rb_f2IQ->Location = System::Drawing::Point(31, 10);
            this->rb_f2IQ->Name = L"rb_f2IQ";
            this->rb_f2IQ->Size = System::Drawing::Size(40, 16);
            this->rb_f2IQ->TabIndex = 1;
            this->rb_f2IQ->Text = L"I/Q";
            this->rb_f2IQ->UseVisualStyleBackColor = true;
            // 
            // rb_f2I
            // 
            this->rb_f2I->AutoSize = true;
            this->rb_f2I->Checked = true;
            this->rb_f2I->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->rb_f2I->Location = System::Drawing::Point(5, 10);
            this->rb_f2I->Name = L"rb_f2I";
            this->rb_f2I->Size = System::Drawing::Size(26, 16);
            this->rb_f2I->TabIndex = 0;
            this->rb_f2I->TabStop = true;
            this->rb_f2I->Text = L"I";
            this->rb_f2I->UseVisualStyleBackColor = true;
            // 
            // tb_f2sf
            // 
            this->tb_f2sf->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->tb_f2sf->Location = System::Drawing::Point(215, 31);
            this->tb_f2sf->Name = L"tb_f2sf";
            this->tb_f2sf->Size = System::Drawing::Size(48, 19);
            this->tb_f2sf->TabIndex = 21;
            this->tb_f2sf->Text = L"20.0";
            this->tb_f2sf->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            // 
            // gp_FE1
            // 
            this->gp_FE1->Controls->Add(this->cb_cf1);
            this->gp_FE1->Controls->Add(this->label4);
            this->gp_FE1->Controls->Add(this->lb_cf1);
            this->gp_FE1->Controls->Add(this->label2);
            this->gp_FE1->Controls->Add(this->l_f1sf);
            this->gp_FE1->Controls->Add(this->l_f1sft);
            this->gp_FE1->Controls->Add(this->tb_f1if);
            this->gp_FE1->Controls->Add(this->l_f1if);
            this->gp_FE1->Controls->Add(this->groupBox3);
            this->gp_FE1->Controls->Add(this->tb_f1sf);
            this->gp_FE1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Bold));
            this->gp_FE1->Location = System::Drawing::Point(7, 18);
            this->gp_FE1->Name = L"gp_FE1";
            this->gp_FE1->Size = System::Drawing::Size(399, 58);
            this->gp_FE1->TabIndex = 24;
            this->gp_FE1->TabStop = false;
            this->gp_FE1->Text = L"FrontEnd 1";
            // 
            // cb_cf1
            // 
            this->cb_cf1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cb_cf1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->cb_cf1->FormattingEnabled = true;
            this->cb_cf1->Location = System::Drawing::Point(89, 29);
            this->cb_cf1->Name = L"cb_cf1";
            this->cb_cf1->Size = System::Drawing::Size(115, 20);
            this->cb_cf1->TabIndex = 29;
            this->cb_cf1->SelectedIndexChanged += gcnew System::EventHandler(this, &maindlg::cb_cf1_SelectedIndexChanged);
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->label4->Location = System::Drawing::Point(359, 34);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(27, 12);
            this->label4->TabIndex = 28;
            this->label4->Text = L"MHz";
            // 
            // lb_cf1
            // 
            this->lb_cf1->AutoSize = true;
            this->lb_cf1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->lb_cf1->Location = System::Drawing::Point(102, 14);
            this->lb_cf1->Name = L"lb_cf1";
            this->lb_cf1->Size = System::Drawing::Size(90, 12);
            this->lb_cf1->TabIndex = 27;
            this->lb_cf1->Text = L"Center Freqency";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->label2->Location = System::Drawing::Point(262, 34);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(27, 12);
            this->label2->TabIndex = 26;
            this->label2->Text = L"MHz";
            // 
            // l_f1sf
            // 
            this->l_f1sf->AutoSize = true;
            this->l_f1sf->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->l_f1sf->Location = System::Drawing::Point(210, 14);
            this->l_f1sf->Name = L"l_f1sf";
            this->l_f1sf->Size = System::Drawing::Size(80, 12);
            this->l_f1sf->TabIndex = 25;
            this->l_f1sf->Text = L"Sampling Freq.";
            // 
            // l_f1sft
            // 
            this->l_f1sft->AutoSize = true;
            this->l_f1sft->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->l_f1sft->Location = System::Drawing::Point(6, 14);
            this->l_f1sft->Name = L"l_f1sft";
            this->l_f1sft->Size = System::Drawing::Size(80, 12);
            this->l_f1sft->TabIndex = 20;
            this->l_f1sft->Text = L"Sampling Type";
            // 
            // tb_f1if
            // 
            this->tb_f1if->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->tb_f1if->Location = System::Drawing::Point(309, 31);
            this->tb_f1if->Name = L"tb_f1if";
            this->tb_f1if->Size = System::Drawing::Size(48, 19);
            this->tb_f1if->TabIndex = 24;
            this->tb_f1if->Text = L"4.0";
            this->tb_f1if->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            // 
            // l_f1if
            // 
            this->l_f1if->AutoSize = true;
            this->l_f1if->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->l_f1if->Location = System::Drawing::Point(299, 14);
            this->l_f1if->Name = L"l_f1if";
            this->l_f1if->Size = System::Drawing::Size(97, 12);
            this->l_f1if->TabIndex = 23;
            this->l_f1if->Text = L"Intermediate Freq.";
            // 
            // groupBox3
            // 
            this->groupBox3->BackColor = System::Drawing::Color::Transparent;
            this->groupBox3->Controls->Add(this->rb_f1IQ);
            this->groupBox3->Controls->Add(this->rb_f1I);
            this->groupBox3->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->groupBox3->Location = System::Drawing::Point(7, 22);
            this->groupBox3->Name = L"groupBox3";
            this->groupBox3->Size = System::Drawing::Size(74, 29);
            this->groupBox3->TabIndex = 22;
            this->groupBox3->TabStop = false;
            // 
            // rb_f1IQ
            // 
            this->rb_f1IQ->AutoSize = true;
            this->rb_f1IQ->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->rb_f1IQ->Location = System::Drawing::Point(31, 10);
            this->rb_f1IQ->Name = L"rb_f1IQ";
            this->rb_f1IQ->Size = System::Drawing::Size(40, 16);
            this->rb_f1IQ->TabIndex = 1;
            this->rb_f1IQ->Text = L"I/Q";
            this->rb_f1IQ->UseVisualStyleBackColor = true;
            // 
            // rb_f1I
            // 
            this->rb_f1I->AutoSize = true;
            this->rb_f1I->Checked = true;
            this->rb_f1I->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->rb_f1I->Location = System::Drawing::Point(5, 10);
            this->rb_f1I->Name = L"rb_f1I";
            this->rb_f1I->Size = System::Drawing::Size(26, 16);
            this->rb_f1I->TabIndex = 0;
            this->rb_f1I->TabStop = true;
            this->rb_f1I->Text = L"I";
            this->rb_f1I->UseVisualStyleBackColor = true;
            // 
            // tb_f1sf
            // 
            this->tb_f1sf->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->tb_f1sf->Location = System::Drawing::Point(215, 31);
            this->tb_f1sf->Name = L"tb_f1sf";
            this->tb_f1sf->Size = System::Drawing::Size(48, 19);
            this->tb_f1sf->TabIndex = 21;
            this->tb_f1sf->Text = L"20.0";
            this->tb_f1sf->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            // 
            // chk_plottrk
            // 
            this->chk_plottrk->AutoSize = true;
            this->chk_plottrk->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_plottrk->Location = System::Drawing::Point(116, 144);
            this->chk_plottrk->Name = L"chk_plottrk";
            this->chk_plottrk->Size = System::Drawing::Size(92, 16);
            this->chk_plottrk->TabIndex = 23;
            this->chk_plottrk->Text = L"Plot Tracking";
            this->chk_plottrk->UseVisualStyleBackColor = true;
            // 
            // chk_plotacq
            // 
            this->chk_plotacq->AutoSize = true;
            this->chk_plotacq->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_plotacq->Location = System::Drawing::Point(10, 144);
            this->chk_plotacq->Name = L"chk_plotacq";
            this->chk_plotacq->Size = System::Drawing::Size(105, 16);
            this->chk_plotacq->TabIndex = 22;
            this->chk_plotacq->Text = L"Plot Acquisition";
            this->chk_plotacq->UseVisualStyleBackColor = true;
            // 
            // gb_gps
            // 
            this->gb_gps->Controls->Add(this->rb_G_FE2);
            this->gb_gps->Controls->Add(this->rb_G_FE1);
            this->gb_gps->Controls->Add(this->chk_G32);
            this->gb_gps->Controls->Add(this->chk_G31);
            this->gb_gps->Controls->Add(this->chk_G30);
            this->gb_gps->Controls->Add(this->chk_G29);
            this->gb_gps->Controls->Add(this->chk_G28);
            this->gb_gps->Controls->Add(this->chk_G27);
            this->gb_gps->Controls->Add(this->chk_G26);
            this->gb_gps->Controls->Add(this->chk_G25);
            this->gb_gps->Controls->Add(this->chk_G24);
            this->gb_gps->Controls->Add(this->chk_G23);
            this->gb_gps->Controls->Add(this->chk_G22);
            this->gb_gps->Controls->Add(this->chk_G21);
            this->gb_gps->Controls->Add(this->chk_G20);
            this->gb_gps->Controls->Add(this->chk_G19);
            this->gb_gps->Controls->Add(this->chk_G18);
            this->gb_gps->Controls->Add(this->chk_G17);
            this->gb_gps->Controls->Add(this->chk_G16);
            this->gb_gps->Controls->Add(this->chk_G15);
            this->gb_gps->Controls->Add(this->chk_G14);
            this->gb_gps->Controls->Add(this->chk_G13);
            this->gb_gps->Controls->Add(this->chk_G12);
            this->gb_gps->Controls->Add(this->chk_G11);
            this->gb_gps->Controls->Add(this->chk_G10);
            this->gb_gps->Controls->Add(this->chk_G09);
            this->gb_gps->Controls->Add(this->chk_G08);
            this->gb_gps->Controls->Add(this->chk_G07);
            this->gb_gps->Controls->Add(this->chk_G06);
            this->gb_gps->Controls->Add(this->chk_G05);
            this->gb_gps->Controls->Add(this->chk_G04);
            this->gb_gps->Controls->Add(this->chk_G03);
            this->gb_gps->Controls->Add(this->chk_G02);
            this->gb_gps->Controls->Add(this->chk_G01);
            this->gb_gps->Controls->Add(this->chk_TYPE_L1CA);
            this->gb_gps->Controls->Add(this->chk_GALL);
            this->gb_gps->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Bold));
            this->gb_gps->Location = System::Drawing::Point(428, 7);
            this->gb_gps->Name = L"gb_gps";
            this->gb_gps->Size = System::Drawing::Size(432, 112);
            this->gb_gps->TabIndex = 25;
            this->gb_gps->TabStop = false;
            this->gb_gps->Text = L"GPS";
            // 
            // rb_G_FE2
            // 
            this->rb_G_FE2->AutoSize = true;
            this->rb_G_FE2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->rb_G_FE2->Location = System::Drawing::Point(208, 15);
            this->rb_G_FE2->Name = L"rb_G_FE2";
            this->rb_G_FE2->Size = System::Drawing::Size(75, 16);
            this->rb_G_FE2->TabIndex = 57;
            this->rb_G_FE2->Text = L"FrontEnd2";
            this->rb_G_FE2->UseVisualStyleBackColor = true;
            // 
            // rb_G_FE1
            // 
            this->rb_G_FE1->AutoSize = true;
            this->rb_G_FE1->Checked = true;
            this->rb_G_FE1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->rb_G_FE1->Location = System::Drawing::Point(130, 15);
            this->rb_G_FE1->Name = L"rb_G_FE1";
            this->rb_G_FE1->Size = System::Drawing::Size(75, 16);
            this->rb_G_FE1->TabIndex = 56;
            this->rb_G_FE1->TabStop = true;
            this->rb_G_FE1->Text = L"FrontEnd1";
            this->rb_G_FE1->UseVisualStyleBackColor = true;
            // 
            // chk_G32
            // 
            this->chk_G32->AutoSize = true;
            this->chk_G32->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G32->Location = System::Drawing::Point(52, 89);
            this->chk_G32->Name = L"chk_G32";
            this->chk_G32->Size = System::Drawing::Size(44, 16);
            this->chk_G32->TabIndex = 55;
            this->chk_G32->Text = L"G32";
            this->chk_G32->UseVisualStyleBackColor = true;
            // 
            // chk_G31
            // 
            this->chk_G31->AutoSize = true;
            this->chk_G31->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G31->Location = System::Drawing::Point(10, 89);
            this->chk_G31->Name = L"chk_G31";
            this->chk_G31->Size = System::Drawing::Size(44, 16);
            this->chk_G31->TabIndex = 54;
            this->chk_G31->Text = L"G31";
            this->chk_G31->UseVisualStyleBackColor = true;
            // 
            // chk_G30
            // 
            this->chk_G30->AutoSize = true;
            this->chk_G30->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G30->Location = System::Drawing::Point(388, 72);
            this->chk_G30->Name = L"chk_G30";
            this->chk_G30->Size = System::Drawing::Size(44, 16);
            this->chk_G30->TabIndex = 53;
            this->chk_G30->Text = L"G30";
            this->chk_G30->UseVisualStyleBackColor = true;
            // 
            // chk_G29
            // 
            this->chk_G29->AutoSize = true;
            this->chk_G29->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G29->Location = System::Drawing::Point(346, 72);
            this->chk_G29->Name = L"chk_G29";
            this->chk_G29->Size = System::Drawing::Size(44, 16);
            this->chk_G29->TabIndex = 52;
            this->chk_G29->Text = L"G29";
            this->chk_G29->UseVisualStyleBackColor = true;
            // 
            // chk_G28
            // 
            this->chk_G28->AutoSize = true;
            this->chk_G28->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G28->Location = System::Drawing::Point(304, 72);
            this->chk_G28->Name = L"chk_G28";
            this->chk_G28->Size = System::Drawing::Size(44, 16);
            this->chk_G28->TabIndex = 51;
            this->chk_G28->Text = L"G28";
            this->chk_G28->UseVisualStyleBackColor = true;
            // 
            // chk_G27
            // 
            this->chk_G27->AutoSize = true;
            this->chk_G27->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G27->Location = System::Drawing::Point(262, 72);
            this->chk_G27->Name = L"chk_G27";
            this->chk_G27->Size = System::Drawing::Size(44, 16);
            this->chk_G27->TabIndex = 50;
            this->chk_G27->Text = L"G27";
            this->chk_G27->UseVisualStyleBackColor = true;
            // 
            // chk_G26
            // 
            this->chk_G26->AutoSize = true;
            this->chk_G26->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G26->Location = System::Drawing::Point(220, 72);
            this->chk_G26->Name = L"chk_G26";
            this->chk_G26->Size = System::Drawing::Size(44, 16);
            this->chk_G26->TabIndex = 49;
            this->chk_G26->Text = L"G26";
            this->chk_G26->UseVisualStyleBackColor = true;
            // 
            // chk_G25
            // 
            this->chk_G25->AutoSize = true;
            this->chk_G25->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G25->Location = System::Drawing::Point(178, 72);
            this->chk_G25->Name = L"chk_G25";
            this->chk_G25->Size = System::Drawing::Size(44, 16);
            this->chk_G25->TabIndex = 48;
            this->chk_G25->Text = L"G25";
            this->chk_G25->UseVisualStyleBackColor = true;
            // 
            // chk_G24
            // 
            this->chk_G24->AutoSize = true;
            this->chk_G24->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G24->Location = System::Drawing::Point(136, 72);
            this->chk_G24->Name = L"chk_G24";
            this->chk_G24->Size = System::Drawing::Size(44, 16);
            this->chk_G24->TabIndex = 47;
            this->chk_G24->Text = L"G24";
            this->chk_G24->UseVisualStyleBackColor = true;
            // 
            // chk_G23
            // 
            this->chk_G23->AutoSize = true;
            this->chk_G23->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G23->Location = System::Drawing::Point(94, 72);
            this->chk_G23->Name = L"chk_G23";
            this->chk_G23->Size = System::Drawing::Size(44, 16);
            this->chk_G23->TabIndex = 46;
            this->chk_G23->Text = L"G23";
            this->chk_G23->UseVisualStyleBackColor = true;
            // 
            // chk_G22
            // 
            this->chk_G22->AutoSize = true;
            this->chk_G22->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G22->Location = System::Drawing::Point(52, 72);
            this->chk_G22->Name = L"chk_G22";
            this->chk_G22->Size = System::Drawing::Size(44, 16);
            this->chk_G22->TabIndex = 45;
            this->chk_G22->Text = L"G22";
            this->chk_G22->UseVisualStyleBackColor = true;
            // 
            // chk_G21
            // 
            this->chk_G21->AutoSize = true;
            this->chk_G21->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G21->Location = System::Drawing::Point(10, 72);
            this->chk_G21->Name = L"chk_G21";
            this->chk_G21->Size = System::Drawing::Size(44, 16);
            this->chk_G21->TabIndex = 44;
            this->chk_G21->Text = L"G21";
            this->chk_G21->UseVisualStyleBackColor = true;
            // 
            // chk_G20
            // 
            this->chk_G20->AutoSize = true;
            this->chk_G20->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G20->Location = System::Drawing::Point(388, 55);
            this->chk_G20->Name = L"chk_G20";
            this->chk_G20->Size = System::Drawing::Size(44, 16);
            this->chk_G20->TabIndex = 43;
            this->chk_G20->Text = L"G20";
            this->chk_G20->UseVisualStyleBackColor = true;
            // 
            // chk_G19
            // 
            this->chk_G19->AutoSize = true;
            this->chk_G19->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G19->Location = System::Drawing::Point(346, 55);
            this->chk_G19->Name = L"chk_G19";
            this->chk_G19->Size = System::Drawing::Size(44, 16);
            this->chk_G19->TabIndex = 42;
            this->chk_G19->Text = L"G19";
            this->chk_G19->UseVisualStyleBackColor = true;
            // 
            // chk_G18
            // 
            this->chk_G18->AutoSize = true;
            this->chk_G18->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G18->Location = System::Drawing::Point(304, 55);
            this->chk_G18->Name = L"chk_G18";
            this->chk_G18->Size = System::Drawing::Size(44, 16);
            this->chk_G18->TabIndex = 41;
            this->chk_G18->Text = L"G18";
            this->chk_G18->UseVisualStyleBackColor = true;
            // 
            // chk_G17
            // 
            this->chk_G17->AutoSize = true;
            this->chk_G17->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G17->Location = System::Drawing::Point(262, 55);
            this->chk_G17->Name = L"chk_G17";
            this->chk_G17->Size = System::Drawing::Size(44, 16);
            this->chk_G17->TabIndex = 40;
            this->chk_G17->Text = L"G17";
            this->chk_G17->UseVisualStyleBackColor = true;
            // 
            // chk_G16
            // 
            this->chk_G16->AutoSize = true;
            this->chk_G16->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G16->Location = System::Drawing::Point(220, 55);
            this->chk_G16->Name = L"chk_G16";
            this->chk_G16->Size = System::Drawing::Size(44, 16);
            this->chk_G16->TabIndex = 39;
            this->chk_G16->Text = L"G16";
            this->chk_G16->UseVisualStyleBackColor = true;
            // 
            // chk_G15
            // 
            this->chk_G15->AutoSize = true;
            this->chk_G15->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G15->Location = System::Drawing::Point(178, 55);
            this->chk_G15->Name = L"chk_G15";
            this->chk_G15->Size = System::Drawing::Size(44, 16);
            this->chk_G15->TabIndex = 38;
            this->chk_G15->Text = L"G15";
            this->chk_G15->UseVisualStyleBackColor = true;
            // 
            // chk_G14
            // 
            this->chk_G14->AutoSize = true;
            this->chk_G14->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G14->Location = System::Drawing::Point(136, 55);
            this->chk_G14->Name = L"chk_G14";
            this->chk_G14->Size = System::Drawing::Size(44, 16);
            this->chk_G14->TabIndex = 37;
            this->chk_G14->Text = L"G14";
            this->chk_G14->UseVisualStyleBackColor = true;
            // 
            // chk_G13
            // 
            this->chk_G13->AutoSize = true;
            this->chk_G13->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G13->Location = System::Drawing::Point(94, 55);
            this->chk_G13->Name = L"chk_G13";
            this->chk_G13->Size = System::Drawing::Size(44, 16);
            this->chk_G13->TabIndex = 36;
            this->chk_G13->Text = L"G13";
            this->chk_G13->UseVisualStyleBackColor = true;
            // 
            // chk_G12
            // 
            this->chk_G12->AutoSize = true;
            this->chk_G12->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G12->Location = System::Drawing::Point(52, 55);
            this->chk_G12->Name = L"chk_G12";
            this->chk_G12->Size = System::Drawing::Size(44, 16);
            this->chk_G12->TabIndex = 35;
            this->chk_G12->Text = L"G12";
            this->chk_G12->UseVisualStyleBackColor = true;
            // 
            // chk_G11
            // 
            this->chk_G11->AutoSize = true;
            this->chk_G11->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G11->Location = System::Drawing::Point(10, 55);
            this->chk_G11->Name = L"chk_G11";
            this->chk_G11->Size = System::Drawing::Size(44, 16);
            this->chk_G11->TabIndex = 34;
            this->chk_G11->Text = L"G11";
            this->chk_G11->UseVisualStyleBackColor = true;
            // 
            // chk_G10
            // 
            this->chk_G10->AutoSize = true;
            this->chk_G10->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G10->Location = System::Drawing::Point(388, 38);
            this->chk_G10->Name = L"chk_G10";
            this->chk_G10->Size = System::Drawing::Size(44, 16);
            this->chk_G10->TabIndex = 33;
            this->chk_G10->Text = L"G10";
            this->chk_G10->UseVisualStyleBackColor = true;
            // 
            // chk_G09
            // 
            this->chk_G09->AutoSize = true;
            this->chk_G09->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G09->Location = System::Drawing::Point(346, 38);
            this->chk_G09->Name = L"chk_G09";
            this->chk_G09->Size = System::Drawing::Size(44, 16);
            this->chk_G09->TabIndex = 32;
            this->chk_G09->Text = L"G09";
            this->chk_G09->UseVisualStyleBackColor = true;
            // 
            // chk_G08
            // 
            this->chk_G08->AutoSize = true;
            this->chk_G08->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G08->Location = System::Drawing::Point(304, 38);
            this->chk_G08->Name = L"chk_G08";
            this->chk_G08->Size = System::Drawing::Size(44, 16);
            this->chk_G08->TabIndex = 31;
            this->chk_G08->Text = L"G08";
            this->chk_G08->UseVisualStyleBackColor = true;
            // 
            // chk_G07
            // 
            this->chk_G07->AutoSize = true;
            this->chk_G07->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G07->Location = System::Drawing::Point(262, 38);
            this->chk_G07->Name = L"chk_G07";
            this->chk_G07->Size = System::Drawing::Size(44, 16);
            this->chk_G07->TabIndex = 30;
            this->chk_G07->Text = L"G07";
            this->chk_G07->UseVisualStyleBackColor = true;
            // 
            // chk_G06
            // 
            this->chk_G06->AutoSize = true;
            this->chk_G06->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G06->Location = System::Drawing::Point(220, 38);
            this->chk_G06->Name = L"chk_G06";
            this->chk_G06->Size = System::Drawing::Size(44, 16);
            this->chk_G06->TabIndex = 29;
            this->chk_G06->Text = L"G06";
            this->chk_G06->UseVisualStyleBackColor = true;
            // 
            // chk_G05
            // 
            this->chk_G05->AutoSize = true;
            this->chk_G05->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G05->Location = System::Drawing::Point(178, 38);
            this->chk_G05->Name = L"chk_G05";
            this->chk_G05->Size = System::Drawing::Size(44, 16);
            this->chk_G05->TabIndex = 28;
            this->chk_G05->Text = L"G05";
            this->chk_G05->UseVisualStyleBackColor = true;
            // 
            // chk_G04
            // 
            this->chk_G04->AutoSize = true;
            this->chk_G04->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G04->Location = System::Drawing::Point(136, 38);
            this->chk_G04->Name = L"chk_G04";
            this->chk_G04->Size = System::Drawing::Size(44, 16);
            this->chk_G04->TabIndex = 27;
            this->chk_G04->Text = L"G04";
            this->chk_G04->UseVisualStyleBackColor = true;
            // 
            // chk_G03
            // 
            this->chk_G03->AutoSize = true;
            this->chk_G03->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G03->Location = System::Drawing::Point(94, 38);
            this->chk_G03->Name = L"chk_G03";
            this->chk_G03->Size = System::Drawing::Size(44, 16);
            this->chk_G03->TabIndex = 26;
            this->chk_G03->Text = L"G03";
            this->chk_G03->UseVisualStyleBackColor = true;
            // 
            // chk_G02
            // 
            this->chk_G02->AutoSize = true;
            this->chk_G02->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G02->Location = System::Drawing::Point(52, 38);
            this->chk_G02->Name = L"chk_G02";
            this->chk_G02->Size = System::Drawing::Size(44, 16);
            this->chk_G02->TabIndex = 25;
            this->chk_G02->Text = L"G02";
            this->chk_G02->UseVisualStyleBackColor = true;
            // 
            // chk_G01
            // 
            this->chk_G01->AutoSize = true;
            this->chk_G01->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_G01->Location = System::Drawing::Point(10, 38);
            this->chk_G01->Name = L"chk_G01";
            this->chk_G01->Size = System::Drawing::Size(44, 16);
            this->chk_G01->TabIndex = 24;
            this->chk_G01->Text = L"G01";
            this->chk_G01->UseVisualStyleBackColor = true;
            // 
            // chk_TYPE_L1CA
            // 
            this->chk_TYPE_L1CA->AutoSize = true;
            this->chk_TYPE_L1CA->Checked = true;
            this->chk_TYPE_L1CA->CheckState = System::Windows::Forms::CheckState::Checked;
            this->chk_TYPE_L1CA->Enabled = false;
            this->chk_TYPE_L1CA->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_TYPE_L1CA->Location = System::Drawing::Point(69, 16);
            this->chk_TYPE_L1CA->Name = L"chk_TYPE_L1CA";
            this->chk_TYPE_L1CA->Size = System::Drawing::Size(52, 16);
            this->chk_TYPE_L1CA->TabIndex = 23;
            this->chk_TYPE_L1CA->Text = L"L1CA";
            this->chk_TYPE_L1CA->UseVisualStyleBackColor = true;
            // 
            // chk_GALL
            // 
            this->chk_GALL->AutoSize = true;
            this->chk_GALL->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_GALL->Location = System::Drawing::Point(10, 16);
            this->chk_GALL->Name = L"chk_GALL";
            this->chk_GALL->Size = System::Drawing::Size(44, 16);
            this->chk_GALL->TabIndex = 22;
            this->chk_GALL->Text = L"ALL";
            this->chk_GALL->UseVisualStyleBackColor = true;
            this->chk_GALL->CheckedChanged += gcnew System::EventHandler(this, &maindlg::chk_GALL_CheckedChanged);
            // 
            // inputfiledlg
            // 
            this->inputfiledlg->InitialDirectory = L"./";
            // 
            // gb_qzs
            // 
            this->gb_qzs->Controls->Add(this->rb_Q_FE2);
            this->gb_qzs->Controls->Add(this->rb_Q_FE1);
            this->gb_qzs->Controls->Add(this->chk_TYPE_SAIF);
            this->gb_qzs->Controls->Add(this->chk_TYPE_LEX);
            this->gb_qzs->Controls->Add(this->chk_Q01);
            this->gb_qzs->Controls->Add(this->chk_TYPE_L1CAQZS);
            this->gb_qzs->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Bold));
            this->gb_qzs->Location = System::Drawing::Point(428, 338);
            this->gb_qzs->Name = L"gb_qzs";
            this->gb_qzs->Size = System::Drawing::Size(432, 39);
            this->gb_qzs->TabIndex = 26;
            this->gb_qzs->TabStop = false;
            this->gb_qzs->Text = L"QZSS";
            // 
            // rb_Q_FE2
            // 
            this->rb_Q_FE2->AutoSize = true;
            this->rb_Q_FE2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->rb_Q_FE2->Location = System::Drawing::Point(235, 17);
            this->rb_Q_FE2->Name = L"rb_Q_FE2";
            this->rb_Q_FE2->Size = System::Drawing::Size(75, 16);
            this->rb_Q_FE2->TabIndex = 59;
            this->rb_Q_FE2->Text = L"FrontEnd2";
            this->rb_Q_FE2->UseVisualStyleBackColor = true;
            // 
            // rb_Q_FE1
            // 
            this->rb_Q_FE1->AutoSize = true;
            this->rb_Q_FE1->Checked = true;
            this->rb_Q_FE1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->rb_Q_FE1->Location = System::Drawing::Point(157, 17);
            this->rb_Q_FE1->Name = L"rb_Q_FE1";
            this->rb_Q_FE1->Size = System::Drawing::Size(75, 16);
            this->rb_Q_FE1->TabIndex = 58;
            this->rb_Q_FE1->TabStop = true;
            this->rb_Q_FE1->Text = L"FrontEnd1";
            this->rb_Q_FE1->UseVisualStyleBackColor = true;
            // 
            // chk_TYPE_SAIF
            // 
            this->chk_TYPE_SAIF->AutoSize = true;
            this->chk_TYPE_SAIF->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_TYPE_SAIF->Location = System::Drawing::Point(103, 18);
            this->chk_TYPE_SAIF->Name = L"chk_TYPE_SAIF";
            this->chk_TYPE_SAIF->Size = System::Drawing::Size(49, 16);
            this->chk_TYPE_SAIF->TabIndex = 25;
            this->chk_TYPE_SAIF->Text = L"SAIF";
            this->chk_TYPE_SAIF->UseVisualStyleBackColor = true;
            this->chk_TYPE_SAIF->CheckedChanged += gcnew System::EventHandler(this, &maindlg::chk_TYPE_SAIF_CheckedChanged);
            // 
            // chk_TYPE_LEX
            // 
            this->chk_TYPE_LEX->AutoSize = true;
            this->chk_TYPE_LEX->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_TYPE_LEX->Location = System::Drawing::Point(60, 18);
            this->chk_TYPE_LEX->Name = L"chk_TYPE_LEX";
            this->chk_TYPE_LEX->Size = System::Drawing::Size(44, 16);
            this->chk_TYPE_LEX->TabIndex = 22;
            this->chk_TYPE_LEX->Text = L"LEX";
            this->chk_TYPE_LEX->UseVisualStyleBackColor = true;
            this->chk_TYPE_LEX->CheckedChanged += gcnew System::EventHandler(this, &maindlg::chk_TYPE_LEX_CheckedChanged);
            // 
            // chk_Q01
            // 
            this->chk_Q01->AutoSize = true;
            this->chk_Q01->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_Q01->Location = System::Drawing::Point(346, 17);
            this->chk_Q01->Name = L"chk_Q01";
            this->chk_Q01->Size = System::Drawing::Size(44, 16);
            this->chk_Q01->TabIndex = 24;
            this->chk_Q01->Text = L"Q01";
            this->chk_Q01->UseVisualStyleBackColor = true;
            // 
            // chk_TYPE_L1CAQZS
            // 
            this->chk_TYPE_L1CAQZS->AutoSize = true;
            this->chk_TYPE_L1CAQZS->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_TYPE_L1CAQZS->Location = System::Drawing::Point(9, 18);
            this->chk_TYPE_L1CAQZS->Name = L"chk_TYPE_L1CAQZS";
            this->chk_TYPE_L1CAQZS->Size = System::Drawing::Size(52, 16);
            this->chk_TYPE_L1CAQZS->TabIndex = 23;
            this->chk_TYPE_L1CAQZS->Text = L"L1CA";
            this->chk_TYPE_L1CAQZS->UseVisualStyleBackColor = true;
            // 
            // b_start
            // 
            this->b_start->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->b_start->Location = System::Drawing::Point(244, 429);
            this->b_start->Name = L"b_start";
            this->b_start->Size = System::Drawing::Size(56, 24);
            this->b_start->TabIndex = 27;
            this->b_start->Text = L"Start";
            this->b_start->UseVisualStyleBackColor = true;
            this->b_start->Click += gcnew System::EventHandler(this, &maindlg::b_start_Click);
            // 
            // b_stop
            // 
            this->b_stop->Enabled = false;
            this->b_stop->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->b_stop->Location = System::Drawing::Point(305, 429);
            this->b_stop->Name = L"b_stop";
            this->b_stop->Size = System::Drawing::Size(56, 24);
            this->b_stop->TabIndex = 28;
            this->b_stop->Text = L"Stop";
            this->b_stop->UseVisualStyleBackColor = true;
            this->b_stop->Click += gcnew System::EventHandler(this, &maindlg::b_stop_Click);
            // 
            // b_exit
            // 
            this->b_exit->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->b_exit->Location = System::Drawing::Point(366, 429);
            this->b_exit->Name = L"b_exit";
            this->b_exit->Size = System::Drawing::Size(56, 24);
            this->b_exit->TabIndex = 29;
            this->b_exit->Text = L"Exit";
            this->b_exit->UseVisualStyleBackColor = true;
            this->b_exit->Click += gcnew System::EventHandler(this, &maindlg::b_exit_Click);
            // 
            // chk_spec
            // 
            this->chk_spec->Appearance = System::Windows::Forms::Appearance::Button;
            this->chk_spec->AutoSize = true;
            this->chk_spec->Enabled = false;
            this->chk_spec->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 10));
            this->chk_spec->Location = System::Drawing::Point(155, 429);
            this->chk_spec->Name = L"chk_spec";
            this->chk_spec->Size = System::Drawing::Size(25, 24);
            this->chk_spec->TabIndex = 32;
            this->chk_spec->Text = L"S";
            this->chk_spec->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            this->chk_spec->UseVisualStyleBackColor = true;
            this->chk_spec->CheckStateChanged += gcnew System::EventHandler(this, &maindlg::chk_spec_CheckStateChanged);
            // 
            // rb_spec1
            // 
            this->rb_spec1->AutoSize = true;
            this->rb_spec1->Checked = true;
            this->rb_spec1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->rb_spec1->Location = System::Drawing::Point(7, 434);
            this->rb_spec1->Name = L"rb_spec1";
            this->rb_spec1->Size = System::Drawing::Size(75, 16);
            this->rb_spec1->TabIndex = 34;
            this->rb_spec1->TabStop = true;
            this->rb_spec1->Text = L"FrontEnd1";
            this->rb_spec1->UseVisualStyleBackColor = true;
            // 
            // rb_spec2
            // 
            this->rb_spec2->AutoSize = true;
            this->rb_spec2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->rb_spec2->Location = System::Drawing::Point(80, 434);
            this->rb_spec2->Name = L"rb_spec2";
            this->rb_spec2->Size = System::Drawing::Size(75, 16);
            this->rb_spec2->TabIndex = 35;
            this->rb_spec2->Text = L"FrontEnd2";
            this->rb_spec2->UseVisualStyleBackColor = true;
            // 
            // chk_monitor
            // 
            this->chk_monitor->Appearance = System::Windows::Forms::Appearance::Button;
            this->chk_monitor->AutoSize = true;
            this->chk_monitor->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 10));
            this->chk_monitor->Location = System::Drawing::Point(211, 429);
            this->chk_monitor->Name = L"chk_monitor";
            this->chk_monitor->Size = System::Drawing::Size(27, 24);
            this->chk_monitor->TabIndex = 30;
            this->chk_monitor->Text = L"M";
            this->chk_monitor->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            this->chk_monitor->UseVisualStyleBackColor = true;
            this->chk_monitor->CheckedChanged += gcnew System::EventHandler(this, &maindlg::chk_monitor_CheckedChanged);
            // 
            // gb_glo
            // 
            this->gb_glo->Controls->Add(this->chk_R3);
            this->gb_glo->Controls->Add(this->rb_R_FE2);
            this->gb_glo->Controls->Add(this->rb_R_FE1);
            this->gb_glo->Controls->Add(this->chk_R6);
            this->gb_glo->Controls->Add(this->chk_R5);
            this->gb_glo->Controls->Add(this->chk_R4);
            this->gb_glo->Controls->Add(this->chk_R2);
            this->gb_glo->Controls->Add(this->chk_R1);
            this->gb_glo->Controls->Add(this->chk_R0);
            this->gb_glo->Controls->Add(this->chk_R_1);
            this->gb_glo->Controls->Add(this->chk_R_2);
            this->gb_glo->Controls->Add(this->chk_R_3);
            this->gb_glo->Controls->Add(this->chk_R_4);
            this->gb_glo->Controls->Add(this->chk_R_5);
            this->gb_glo->Controls->Add(this->chk_R_6);
            this->gb_glo->Controls->Add(this->chk_R_7);
            this->gb_glo->Controls->Add(this->chk_TYPE_G1);
            this->gb_glo->Controls->Add(this->chk_RALL);
            this->gb_glo->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Bold));
            this->gb_glo->Location = System::Drawing::Point(428, 120);
            this->gb_glo->Name = L"gb_glo";
            this->gb_glo->Size = System::Drawing::Size(432, 78);
            this->gb_glo->TabIndex = 58;
            this->gb_glo->TabStop = false;
            this->gb_glo->Text = L"GLONASS";
            // 
            // chk_R3
            // 
            this->chk_R3->AutoSize = true;
            this->chk_R3->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_R3->Location = System::Drawing::Point(9, 55);
            this->chk_R3->Name = L"chk_R3";
            this->chk_R3->Size = System::Drawing::Size(36, 16);
            this->chk_R3->TabIndex = 58;
            this->chk_R3->Text = L"03";
            this->chk_R3->UseVisualStyleBackColor = true;
            // 
            // rb_R_FE2
            // 
            this->rb_R_FE2->AutoSize = true;
            this->rb_R_FE2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->rb_R_FE2->Location = System::Drawing::Point(208, 15);
            this->rb_R_FE2->Name = L"rb_R_FE2";
            this->rb_R_FE2->Size = System::Drawing::Size(75, 16);
            this->rb_R_FE2->TabIndex = 57;
            this->rb_R_FE2->Text = L"FrontEnd2";
            this->rb_R_FE2->UseVisualStyleBackColor = true;
            // 
            // rb_R_FE1
            // 
            this->rb_R_FE1->AutoSize = true;
            this->rb_R_FE1->Checked = true;
            this->rb_R_FE1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->rb_R_FE1->Location = System::Drawing::Point(130, 15);
            this->rb_R_FE1->Name = L"rb_R_FE1";
            this->rb_R_FE1->Size = System::Drawing::Size(75, 16);
            this->rb_R_FE1->TabIndex = 56;
            this->rb_R_FE1->TabStop = true;
            this->rb_R_FE1->Text = L"FrontEnd1";
            this->rb_R_FE1->UseVisualStyleBackColor = true;
            // 
            // chk_R6
            // 
            this->chk_R6->AutoSize = true;
            this->chk_R6->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_R6->Location = System::Drawing::Point(136, 55);
            this->chk_R6->Name = L"chk_R6";
            this->chk_R6->Size = System::Drawing::Size(36, 16);
            this->chk_R6->TabIndex = 36;
            this->chk_R6->Text = L"06";
            this->chk_R6->UseVisualStyleBackColor = true;
            // 
            // chk_R5
            // 
            this->chk_R5->AutoSize = true;
            this->chk_R5->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_R5->Location = System::Drawing::Point(94, 55);
            this->chk_R5->Name = L"chk_R5";
            this->chk_R5->Size = System::Drawing::Size(36, 16);
            this->chk_R5->TabIndex = 35;
            this->chk_R5->Text = L"05";
            this->chk_R5->UseVisualStyleBackColor = true;
            // 
            // chk_R4
            // 
            this->chk_R4->AutoSize = true;
            this->chk_R4->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_R4->Location = System::Drawing::Point(52, 55);
            this->chk_R4->Name = L"chk_R4";
            this->chk_R4->Size = System::Drawing::Size(36, 16);
            this->chk_R4->TabIndex = 34;
            this->chk_R4->Text = L"04";
            this->chk_R4->UseVisualStyleBackColor = true;
            // 
            // chk_R2
            // 
            this->chk_R2->AutoSize = true;
            this->chk_R2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_R2->Location = System::Drawing::Point(388, 38);
            this->chk_R2->Name = L"chk_R2";
            this->chk_R2->Size = System::Drawing::Size(36, 16);
            this->chk_R2->TabIndex = 33;
            this->chk_R2->Text = L"02";
            this->chk_R2->UseVisualStyleBackColor = true;
            // 
            // chk_R1
            // 
            this->chk_R1->AutoSize = true;
            this->chk_R1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_R1->Location = System::Drawing::Point(346, 38);
            this->chk_R1->Name = L"chk_R1";
            this->chk_R1->Size = System::Drawing::Size(36, 16);
            this->chk_R1->TabIndex = 32;
            this->chk_R1->Text = L"01";
            this->chk_R1->UseVisualStyleBackColor = true;
            // 
            // chk_R0
            // 
            this->chk_R0->AutoSize = true;
            this->chk_R0->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_R0->Location = System::Drawing::Point(304, 38);
            this->chk_R0->Name = L"chk_R0";
            this->chk_R0->Size = System::Drawing::Size(36, 16);
            this->chk_R0->TabIndex = 31;
            this->chk_R0->Text = L"00";
            this->chk_R0->UseVisualStyleBackColor = true;
            // 
            // chk_R_1
            // 
            this->chk_R_1->AutoSize = true;
            this->chk_R_1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_R_1->Location = System::Drawing::Point(262, 38);
            this->chk_R_1->Name = L"chk_R_1";
            this->chk_R_1->Size = System::Drawing::Size(42, 16);
            this->chk_R_1->TabIndex = 30;
            this->chk_R_1->Text = L"-01";
            this->chk_R_1->UseVisualStyleBackColor = true;
            // 
            // chk_R_2
            // 
            this->chk_R_2->AutoSize = true;
            this->chk_R_2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_R_2->Location = System::Drawing::Point(220, 38);
            this->chk_R_2->Name = L"chk_R_2";
            this->chk_R_2->Size = System::Drawing::Size(42, 16);
            this->chk_R_2->TabIndex = 29;
            this->chk_R_2->Text = L"-02";
            this->chk_R_2->UseVisualStyleBackColor = true;
            // 
            // chk_R_3
            // 
            this->chk_R_3->AutoSize = true;
            this->chk_R_3->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_R_3->Location = System::Drawing::Point(178, 38);
            this->chk_R_3->Name = L"chk_R_3";
            this->chk_R_3->Size = System::Drawing::Size(42, 16);
            this->chk_R_3->TabIndex = 28;
            this->chk_R_3->Text = L"-03";
            this->chk_R_3->UseVisualStyleBackColor = true;
            // 
            // chk_R_4
            // 
            this->chk_R_4->AutoSize = true;
            this->chk_R_4->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_R_4->Location = System::Drawing::Point(136, 38);
            this->chk_R_4->Name = L"chk_R_4";
            this->chk_R_4->Size = System::Drawing::Size(42, 16);
            this->chk_R_4->TabIndex = 27;
            this->chk_R_4->Text = L"-04";
            this->chk_R_4->UseVisualStyleBackColor = true;
            // 
            // chk_R_5
            // 
            this->chk_R_5->AutoSize = true;
            this->chk_R_5->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_R_5->Location = System::Drawing::Point(94, 38);
            this->chk_R_5->Name = L"chk_R_5";
            this->chk_R_5->Size = System::Drawing::Size(42, 16);
            this->chk_R_5->TabIndex = 26;
            this->chk_R_5->Text = L"-05";
            this->chk_R_5->UseVisualStyleBackColor = true;
            // 
            // chk_R_6
            // 
            this->chk_R_6->AutoSize = true;
            this->chk_R_6->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_R_6->Location = System::Drawing::Point(52, 38);
            this->chk_R_6->Name = L"chk_R_6";
            this->chk_R_6->Size = System::Drawing::Size(42, 16);
            this->chk_R_6->TabIndex = 25;
            this->chk_R_6->Text = L"-06";
            this->chk_R_6->UseVisualStyleBackColor = true;
            // 
            // chk_R_7
            // 
            this->chk_R_7->AutoSize = true;
            this->chk_R_7->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_R_7->Location = System::Drawing::Point(9, 38);
            this->chk_R_7->Name = L"chk_R_7";
            this->chk_R_7->Size = System::Drawing::Size(42, 16);
            this->chk_R_7->TabIndex = 24;
            this->chk_R_7->Text = L"-07";
            this->chk_R_7->UseVisualStyleBackColor = true;
            // 
            // chk_TYPE_G1
            // 
            this->chk_TYPE_G1->AutoSize = true;
            this->chk_TYPE_G1->Checked = true;
            this->chk_TYPE_G1->CheckState = System::Windows::Forms::CheckState::Checked;
            this->chk_TYPE_G1->Enabled = false;
            this->chk_TYPE_G1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_TYPE_G1->Location = System::Drawing::Point(69, 16);
            this->chk_TYPE_G1->Name = L"chk_TYPE_G1";
            this->chk_TYPE_G1->Size = System::Drawing::Size(38, 16);
            this->chk_TYPE_G1->TabIndex = 23;
            this->chk_TYPE_G1->Text = L"G1";
            this->chk_TYPE_G1->UseVisualStyleBackColor = true;
            // 
            // chk_RALL
            // 
            this->chk_RALL->AutoSize = true;
            this->chk_RALL->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_RALL->Location = System::Drawing::Point(10, 16);
            this->chk_RALL->Name = L"chk_RALL";
            this->chk_RALL->Size = System::Drawing::Size(44, 16);
            this->chk_RALL->TabIndex = 22;
            this->chk_RALL->Text = L"ALL";
            this->chk_RALL->UseVisualStyleBackColor = true;
            this->chk_RALL->CheckedChanged += gcnew System::EventHandler(this, &maindlg::chk_RALL_CheckedChanged);
            // 
            // gb_gal
            // 
            this->gb_gal->Controls->Add(this->rb_E_FE2);
            this->gb_gal->Controls->Add(this->rb_E_FE1);
            this->gb_gal->Controls->Add(this->chk_E20);
            this->gb_gal->Controls->Add(this->chk_E19);
            this->gb_gal->Controls->Add(this->chk_E12);
            this->gb_gal->Controls->Add(this->chk_E11);
            this->gb_gal->Controls->Add(this->chk_TYPE_E1B);
            this->gb_gal->Controls->Add(this->chk_EALL);
            this->gb_gal->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Bold));
            this->gb_gal->Location = System::Drawing::Point(428, 199);
            this->gb_gal->Name = L"gb_gal";
            this->gb_gal->Size = System::Drawing::Size(432, 60);
            this->gb_gal->TabIndex = 59;
            this->gb_gal->TabStop = false;
            this->gb_gal->Text = L"Galileo";
            // 
            // rb_E_FE2
            // 
            this->rb_E_FE2->AutoSize = true;
            this->rb_E_FE2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->rb_E_FE2->Location = System::Drawing::Point(208, 15);
            this->rb_E_FE2->Name = L"rb_E_FE2";
            this->rb_E_FE2->Size = System::Drawing::Size(75, 16);
            this->rb_E_FE2->TabIndex = 57;
            this->rb_E_FE2->Text = L"FrontEnd2";
            this->rb_E_FE2->UseVisualStyleBackColor = true;
            // 
            // rb_E_FE1
            // 
            this->rb_E_FE1->AutoSize = true;
            this->rb_E_FE1->Checked = true;
            this->rb_E_FE1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->rb_E_FE1->Location = System::Drawing::Point(130, 15);
            this->rb_E_FE1->Name = L"rb_E_FE1";
            this->rb_E_FE1->Size = System::Drawing::Size(75, 16);
            this->rb_E_FE1->TabIndex = 56;
            this->rb_E_FE1->TabStop = true;
            this->rb_E_FE1->Text = L"FrontEnd1";
            this->rb_E_FE1->UseVisualStyleBackColor = true;
            // 
            // chk_E20
            // 
            this->chk_E20->AutoSize = true;
            this->chk_E20->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_E20->Location = System::Drawing::Point(136, 38);
            this->chk_E20->Name = L"chk_E20";
            this->chk_E20->Size = System::Drawing::Size(43, 16);
            this->chk_E20->TabIndex = 27;
            this->chk_E20->Text = L"E20";
            this->chk_E20->UseVisualStyleBackColor = true;
            // 
            // chk_E19
            // 
            this->chk_E19->AutoSize = true;
            this->chk_E19->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_E19->Location = System::Drawing::Point(94, 38);
            this->chk_E19->Name = L"chk_E19";
            this->chk_E19->Size = System::Drawing::Size(43, 16);
            this->chk_E19->TabIndex = 26;
            this->chk_E19->Text = L"E19";
            this->chk_E19->UseVisualStyleBackColor = true;
            // 
            // chk_E12
            // 
            this->chk_E12->AutoSize = true;
            this->chk_E12->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_E12->Location = System::Drawing::Point(52, 38);
            this->chk_E12->Name = L"chk_E12";
            this->chk_E12->Size = System::Drawing::Size(43, 16);
            this->chk_E12->TabIndex = 25;
            this->chk_E12->Text = L"E12";
            this->chk_E12->UseVisualStyleBackColor = true;
            // 
            // chk_E11
            // 
            this->chk_E11->AutoSize = true;
            this->chk_E11->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_E11->Location = System::Drawing::Point(10, 38);
            this->chk_E11->Name = L"chk_E11";
            this->chk_E11->Size = System::Drawing::Size(43, 16);
            this->chk_E11->TabIndex = 24;
            this->chk_E11->Text = L"E11";
            this->chk_E11->UseVisualStyleBackColor = true;
            // 
            // chk_TYPE_E1B
            // 
            this->chk_TYPE_E1B->AutoSize = true;
            this->chk_TYPE_E1B->Checked = true;
            this->chk_TYPE_E1B->CheckState = System::Windows::Forms::CheckState::Checked;
            this->chk_TYPE_E1B->Enabled = false;
            this->chk_TYPE_E1B->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_TYPE_E1B->Location = System::Drawing::Point(69, 16);
            this->chk_TYPE_E1B->Name = L"chk_TYPE_E1B";
            this->chk_TYPE_E1B->Size = System::Drawing::Size(45, 16);
            this->chk_TYPE_E1B->TabIndex = 23;
            this->chk_TYPE_E1B->Text = L"E1B";
            this->chk_TYPE_E1B->UseVisualStyleBackColor = true;
            // 
            // chk_EALL
            // 
            this->chk_EALL->AutoSize = true;
            this->chk_EALL->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_EALL->Location = System::Drawing::Point(10, 16);
            this->chk_EALL->Name = L"chk_EALL";
            this->chk_EALL->Size = System::Drawing::Size(44, 16);
            this->chk_EALL->TabIndex = 22;
            this->chk_EALL->Text = L"ALL";
            this->chk_EALL->UseVisualStyleBackColor = true;
            this->chk_EALL->CheckedChanged += gcnew System::EventHandler(this, &maindlg::chk_EALL_CheckedChanged);
            // 
            // gb_bds
            // 
            this->gb_bds->Controls->Add(this->rb_C_FE2);
            this->gb_bds->Controls->Add(this->rb_C_FE1);
            this->gb_bds->Controls->Add(this->chk_C14);
            this->gb_bds->Controls->Add(this->chk_C13);
            this->gb_bds->Controls->Add(this->chk_C12);
            this->gb_bds->Controls->Add(this->chk_C11);
            this->gb_bds->Controls->Add(this->chk_C10);
            this->gb_bds->Controls->Add(this->chk_C09);
            this->gb_bds->Controls->Add(this->chk_C08);
            this->gb_bds->Controls->Add(this->chk_C07);
            this->gb_bds->Controls->Add(this->chk_C06);
            this->gb_bds->Controls->Add(this->chk_C05);
            this->gb_bds->Controls->Add(this->chk_C04);
            this->gb_bds->Controls->Add(this->chk_C03);
            this->gb_bds->Controls->Add(this->chk_C02);
            this->gb_bds->Controls->Add(this->chk_C01);
            this->gb_bds->Controls->Add(this->chk_TYPE_B1I);
            this->gb_bds->Controls->Add(this->chk_CALL);
            this->gb_bds->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Bold));
            this->gb_bds->Location = System::Drawing::Point(428, 260);
            this->gb_bds->Name = L"gb_bds";
            this->gb_bds->Size = System::Drawing::Size(432, 77);
            this->gb_bds->TabIndex = 60;
            this->gb_bds->TabStop = false;
            this->gb_bds->Text = L"BeiDou";
            // 
            // rb_C_FE2
            // 
            this->rb_C_FE2->AutoSize = true;
            this->rb_C_FE2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->rb_C_FE2->Location = System::Drawing::Point(208, 15);
            this->rb_C_FE2->Name = L"rb_C_FE2";
            this->rb_C_FE2->Size = System::Drawing::Size(75, 16);
            this->rb_C_FE2->TabIndex = 57;
            this->rb_C_FE2->Text = L"FrontEnd2";
            this->rb_C_FE2->UseVisualStyleBackColor = true;
            // 
            // rb_C_FE1
            // 
            this->rb_C_FE1->AutoSize = true;
            this->rb_C_FE1->Checked = true;
            this->rb_C_FE1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->rb_C_FE1->Location = System::Drawing::Point(130, 15);
            this->rb_C_FE1->Name = L"rb_C_FE1";
            this->rb_C_FE1->Size = System::Drawing::Size(75, 16);
            this->rb_C_FE1->TabIndex = 56;
            this->rb_C_FE1->TabStop = true;
            this->rb_C_FE1->Text = L"FrontEnd1";
            this->rb_C_FE1->UseVisualStyleBackColor = true;
            // 
            // chk_C14
            // 
            this->chk_C14->AutoSize = true;
            this->chk_C14->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_C14->Location = System::Drawing::Point(136, 55);
            this->chk_C14->Name = L"chk_C14";
            this->chk_C14->Size = System::Drawing::Size(44, 16);
            this->chk_C14->TabIndex = 37;
            this->chk_C14->Text = L"C14";
            this->chk_C14->UseVisualStyleBackColor = true;
            // 
            // chk_C13
            // 
            this->chk_C13->AutoSize = true;
            this->chk_C13->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_C13->Location = System::Drawing::Point(94, 55);
            this->chk_C13->Name = L"chk_C13";
            this->chk_C13->Size = System::Drawing::Size(44, 16);
            this->chk_C13->TabIndex = 36;
            this->chk_C13->Text = L"C13";
            this->chk_C13->UseVisualStyleBackColor = true;
            // 
            // chk_C12
            // 
            this->chk_C12->AutoSize = true;
            this->chk_C12->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_C12->Location = System::Drawing::Point(52, 55);
            this->chk_C12->Name = L"chk_C12";
            this->chk_C12->Size = System::Drawing::Size(44, 16);
            this->chk_C12->TabIndex = 35;
            this->chk_C12->Text = L"C12";
            this->chk_C12->UseVisualStyleBackColor = true;
            // 
            // chk_C11
            // 
            this->chk_C11->AutoSize = true;
            this->chk_C11->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_C11->Location = System::Drawing::Point(10, 55);
            this->chk_C11->Name = L"chk_C11";
            this->chk_C11->Size = System::Drawing::Size(44, 16);
            this->chk_C11->TabIndex = 34;
            this->chk_C11->Text = L"C11";
            this->chk_C11->UseVisualStyleBackColor = true;
            // 
            // chk_C10
            // 
            this->chk_C10->AutoSize = true;
            this->chk_C10->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_C10->Location = System::Drawing::Point(388, 38);
            this->chk_C10->Name = L"chk_C10";
            this->chk_C10->Size = System::Drawing::Size(44, 16);
            this->chk_C10->TabIndex = 33;
            this->chk_C10->Text = L"C10";
            this->chk_C10->UseVisualStyleBackColor = true;
            // 
            // chk_C09
            // 
            this->chk_C09->AutoSize = true;
            this->chk_C09->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_C09->Location = System::Drawing::Point(346, 38);
            this->chk_C09->Name = L"chk_C09";
            this->chk_C09->Size = System::Drawing::Size(44, 16);
            this->chk_C09->TabIndex = 32;
            this->chk_C09->Text = L"C09";
            this->chk_C09->UseVisualStyleBackColor = true;
            // 
            // chk_C08
            // 
            this->chk_C08->AutoSize = true;
            this->chk_C08->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_C08->Location = System::Drawing::Point(304, 38);
            this->chk_C08->Name = L"chk_C08";
            this->chk_C08->Size = System::Drawing::Size(44, 16);
            this->chk_C08->TabIndex = 31;
            this->chk_C08->Text = L"C08";
            this->chk_C08->UseVisualStyleBackColor = true;
            // 
            // chk_C07
            // 
            this->chk_C07->AutoSize = true;
            this->chk_C07->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_C07->Location = System::Drawing::Point(262, 38);
            this->chk_C07->Name = L"chk_C07";
            this->chk_C07->Size = System::Drawing::Size(44, 16);
            this->chk_C07->TabIndex = 30;
            this->chk_C07->Text = L"C07";
            this->chk_C07->UseVisualStyleBackColor = true;
            // 
            // chk_C06
            // 
            this->chk_C06->AutoSize = true;
            this->chk_C06->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_C06->Location = System::Drawing::Point(220, 38);
            this->chk_C06->Name = L"chk_C06";
            this->chk_C06->Size = System::Drawing::Size(44, 16);
            this->chk_C06->TabIndex = 29;
            this->chk_C06->Text = L"C06";
            this->chk_C06->UseVisualStyleBackColor = true;
            // 
            // chk_C05
            // 
            this->chk_C05->AutoSize = true;
            this->chk_C05->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_C05->Location = System::Drawing::Point(178, 38);
            this->chk_C05->Name = L"chk_C05";
            this->chk_C05->Size = System::Drawing::Size(44, 16);
            this->chk_C05->TabIndex = 28;
            this->chk_C05->Text = L"C05";
            this->chk_C05->UseVisualStyleBackColor = true;
            // 
            // chk_C04
            // 
            this->chk_C04->AutoSize = true;
            this->chk_C04->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_C04->Location = System::Drawing::Point(136, 38);
            this->chk_C04->Name = L"chk_C04";
            this->chk_C04->Size = System::Drawing::Size(44, 16);
            this->chk_C04->TabIndex = 27;
            this->chk_C04->Text = L"C04";
            this->chk_C04->UseVisualStyleBackColor = true;
            // 
            // chk_C03
            // 
            this->chk_C03->AutoSize = true;
            this->chk_C03->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_C03->Location = System::Drawing::Point(94, 38);
            this->chk_C03->Name = L"chk_C03";
            this->chk_C03->Size = System::Drawing::Size(44, 16);
            this->chk_C03->TabIndex = 26;
            this->chk_C03->Text = L"C03";
            this->chk_C03->UseVisualStyleBackColor = true;
            // 
            // chk_C02
            // 
            this->chk_C02->AutoSize = true;
            this->chk_C02->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_C02->Location = System::Drawing::Point(52, 38);
            this->chk_C02->Name = L"chk_C02";
            this->chk_C02->Size = System::Drawing::Size(44, 16);
            this->chk_C02->TabIndex = 25;
            this->chk_C02->Text = L"C02";
            this->chk_C02->UseVisualStyleBackColor = true;
            // 
            // chk_C01
            // 
            this->chk_C01->AutoSize = true;
            this->chk_C01->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_C01->Location = System::Drawing::Point(10, 38);
            this->chk_C01->Name = L"chk_C01";
            this->chk_C01->Size = System::Drawing::Size(44, 16);
            this->chk_C01->TabIndex = 24;
            this->chk_C01->Text = L"C01";
            this->chk_C01->UseVisualStyleBackColor = true;
            // 
            // chk_TYPE_B1I
            // 
            this->chk_TYPE_B1I->AutoSize = true;
            this->chk_TYPE_B1I->Checked = true;
            this->chk_TYPE_B1I->CheckState = System::Windows::Forms::CheckState::Checked;
            this->chk_TYPE_B1I->Enabled = false;
            this->chk_TYPE_B1I->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_TYPE_B1I->Location = System::Drawing::Point(69, 16);
            this->chk_TYPE_B1I->Name = L"chk_TYPE_B1I";
            this->chk_TYPE_B1I->Size = System::Drawing::Size(41, 16);
            this->chk_TYPE_B1I->TabIndex = 23;
            this->chk_TYPE_B1I->Text = L"B1I";
            this->chk_TYPE_B1I->UseVisualStyleBackColor = true;
            // 
            // chk_CALL
            // 
            this->chk_CALL->AutoSize = true;
            this->chk_CALL->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_CALL->Location = System::Drawing::Point(10, 16);
            this->chk_CALL->Name = L"chk_CALL";
            this->chk_CALL->Size = System::Drawing::Size(44, 16);
            this->chk_CALL->TabIndex = 22;
            this->chk_CALL->Text = L"ALL";
            this->chk_CALL->UseVisualStyleBackColor = true;
            this->chk_CALL->CheckedChanged += gcnew System::EventHandler(this, &maindlg::chk_CALL_CheckedChanged);
            // 
            // gb_sbs
            // 
            this->gb_sbs->Controls->Add(this->rb_S_FE2);
            this->gb_sbs->Controls->Add(this->rb_S_FE1);
            this->gb_sbs->Controls->Add(this->chk_S138);
            this->gb_sbs->Controls->Add(this->chk_S137);
            this->gb_sbs->Controls->Add(this->chk_S136);
            this->gb_sbs->Controls->Add(this->chk_S135);
            this->gb_sbs->Controls->Add(this->chk_S134);
            this->gb_sbs->Controls->Add(this->chk_S133);
            this->gb_sbs->Controls->Add(this->chk_S132);
            this->gb_sbs->Controls->Add(this->chk_S131);
            this->gb_sbs->Controls->Add(this->chk_S130);
            this->gb_sbs->Controls->Add(this->chk_S129);
            this->gb_sbs->Controls->Add(this->chk_S128);
            this->gb_sbs->Controls->Add(this->chk_S127);
            this->gb_sbs->Controls->Add(this->chk_S126);
            this->gb_sbs->Controls->Add(this->chk_S125);
            this->gb_sbs->Controls->Add(this->chk_S124);
            this->gb_sbs->Controls->Add(this->chk_S123);
            this->gb_sbs->Controls->Add(this->chk_S122);
            this->gb_sbs->Controls->Add(this->chk_S121);
            this->gb_sbs->Controls->Add(this->chk_S120);
            this->gb_sbs->Controls->Add(this->chk_TYPE_SBASL1);
            this->gb_sbs->Controls->Add(this->chk_SALL);
            this->gb_sbs->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Bold));
            this->gb_sbs->Location = System::Drawing::Point(428, 378);
            this->gb_sbs->Name = L"gb_sbs";
            this->gb_sbs->Size = System::Drawing::Size(432, 77);
            this->gb_sbs->TabIndex = 61;
            this->gb_sbs->TabStop = false;
            this->gb_sbs->Text = L"SBAS";
            // 
            // rb_S_FE2
            // 
            this->rb_S_FE2->AutoSize = true;
            this->rb_S_FE2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->rb_S_FE2->Location = System::Drawing::Point(208, 15);
            this->rb_S_FE2->Name = L"rb_S_FE2";
            this->rb_S_FE2->Size = System::Drawing::Size(75, 16);
            this->rb_S_FE2->TabIndex = 57;
            this->rb_S_FE2->Text = L"FrontEnd2";
            this->rb_S_FE2->UseVisualStyleBackColor = true;
            // 
            // rb_S_FE1
            // 
            this->rb_S_FE1->AutoSize = true;
            this->rb_S_FE1->Checked = true;
            this->rb_S_FE1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->rb_S_FE1->Location = System::Drawing::Point(130, 15);
            this->rb_S_FE1->Name = L"rb_S_FE1";
            this->rb_S_FE1->Size = System::Drawing::Size(75, 16);
            this->rb_S_FE1->TabIndex = 56;
            this->rb_S_FE1->TabStop = true;
            this->rb_S_FE1->Text = L"FrontEnd1";
            this->rb_S_FE1->UseVisualStyleBackColor = true;
            // 
            // chk_S138
            // 
            this->chk_S138->AutoSize = true;
            this->chk_S138->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S138->Location = System::Drawing::Point(346, 55);
            this->chk_S138->Name = L"chk_S138";
            this->chk_S138->Size = System::Drawing::Size(42, 16);
            this->chk_S138->TabIndex = 42;
            this->chk_S138->Text = L"138";
            this->chk_S138->UseVisualStyleBackColor = true;
            // 
            // chk_S137
            // 
            this->chk_S137->AutoSize = true;
            this->chk_S137->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S137->Location = System::Drawing::Point(304, 55);
            this->chk_S137->Name = L"chk_S137";
            this->chk_S137->Size = System::Drawing::Size(42, 16);
            this->chk_S137->TabIndex = 41;
            this->chk_S137->Text = L"137";
            this->chk_S137->UseVisualStyleBackColor = true;
            // 
            // chk_S136
            // 
            this->chk_S136->AutoSize = true;
            this->chk_S136->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S136->Location = System::Drawing::Point(262, 55);
            this->chk_S136->Name = L"chk_S136";
            this->chk_S136->Size = System::Drawing::Size(42, 16);
            this->chk_S136->TabIndex = 40;
            this->chk_S136->Text = L"136";
            this->chk_S136->UseVisualStyleBackColor = true;
            // 
            // chk_S135
            // 
            this->chk_S135->AutoSize = true;
            this->chk_S135->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S135->Location = System::Drawing::Point(220, 55);
            this->chk_S135->Name = L"chk_S135";
            this->chk_S135->Size = System::Drawing::Size(42, 16);
            this->chk_S135->TabIndex = 39;
            this->chk_S135->Text = L"135";
            this->chk_S135->UseVisualStyleBackColor = true;
            // 
            // chk_S134
            // 
            this->chk_S134->AutoSize = true;
            this->chk_S134->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S134->Location = System::Drawing::Point(178, 55);
            this->chk_S134->Name = L"chk_S134";
            this->chk_S134->Size = System::Drawing::Size(42, 16);
            this->chk_S134->TabIndex = 38;
            this->chk_S134->Text = L"134";
            this->chk_S134->UseVisualStyleBackColor = true;
            // 
            // chk_S133
            // 
            this->chk_S133->AutoSize = true;
            this->chk_S133->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S133->Location = System::Drawing::Point(136, 55);
            this->chk_S133->Name = L"chk_S133";
            this->chk_S133->Size = System::Drawing::Size(42, 16);
            this->chk_S133->TabIndex = 37;
            this->chk_S133->Text = L"133";
            this->chk_S133->UseVisualStyleBackColor = true;
            // 
            // chk_S132
            // 
            this->chk_S132->AutoSize = true;
            this->chk_S132->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S132->Location = System::Drawing::Point(94, 55);
            this->chk_S132->Name = L"chk_S132";
            this->chk_S132->Size = System::Drawing::Size(42, 16);
            this->chk_S132->TabIndex = 36;
            this->chk_S132->Text = L"132";
            this->chk_S132->UseVisualStyleBackColor = true;
            // 
            // chk_S131
            // 
            this->chk_S131->AutoSize = true;
            this->chk_S131->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S131->Location = System::Drawing::Point(52, 55);
            this->chk_S131->Name = L"chk_S131";
            this->chk_S131->Size = System::Drawing::Size(42, 16);
            this->chk_S131->TabIndex = 35;
            this->chk_S131->Text = L"131";
            this->chk_S131->UseVisualStyleBackColor = true;
            // 
            // chk_S130
            // 
            this->chk_S130->AutoSize = true;
            this->chk_S130->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S130->Location = System::Drawing::Point(10, 55);
            this->chk_S130->Name = L"chk_S130";
            this->chk_S130->Size = System::Drawing::Size(42, 16);
            this->chk_S130->TabIndex = 34;
            this->chk_S130->Text = L"130";
            this->chk_S130->UseVisualStyleBackColor = true;
            // 
            // chk_S129
            // 
            this->chk_S129->AutoSize = true;
            this->chk_S129->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S129->Location = System::Drawing::Point(388, 38);
            this->chk_S129->Name = L"chk_S129";
            this->chk_S129->Size = System::Drawing::Size(42, 16);
            this->chk_S129->TabIndex = 33;
            this->chk_S129->Text = L"129";
            this->chk_S129->UseVisualStyleBackColor = true;
            // 
            // chk_S128
            // 
            this->chk_S128->AutoSize = true;
            this->chk_S128->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S128->Location = System::Drawing::Point(346, 38);
            this->chk_S128->Name = L"chk_S128";
            this->chk_S128->Size = System::Drawing::Size(42, 16);
            this->chk_S128->TabIndex = 32;
            this->chk_S128->Text = L"128";
            this->chk_S128->UseVisualStyleBackColor = true;
            // 
            // chk_S127
            // 
            this->chk_S127->AutoSize = true;
            this->chk_S127->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S127->Location = System::Drawing::Point(304, 38);
            this->chk_S127->Name = L"chk_S127";
            this->chk_S127->Size = System::Drawing::Size(42, 16);
            this->chk_S127->TabIndex = 31;
            this->chk_S127->Text = L"127";
            this->chk_S127->UseVisualStyleBackColor = true;
            // 
            // chk_S126
            // 
            this->chk_S126->AutoSize = true;
            this->chk_S126->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S126->Location = System::Drawing::Point(262, 38);
            this->chk_S126->Name = L"chk_S126";
            this->chk_S126->Size = System::Drawing::Size(42, 16);
            this->chk_S126->TabIndex = 30;
            this->chk_S126->Text = L"126";
            this->chk_S126->UseVisualStyleBackColor = true;
            // 
            // chk_S125
            // 
            this->chk_S125->AutoSize = true;
            this->chk_S125->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S125->Location = System::Drawing::Point(220, 38);
            this->chk_S125->Name = L"chk_S125";
            this->chk_S125->Size = System::Drawing::Size(42, 16);
            this->chk_S125->TabIndex = 29;
            this->chk_S125->Text = L"125";
            this->chk_S125->UseVisualStyleBackColor = true;
            // 
            // chk_S124
            // 
            this->chk_S124->AutoSize = true;
            this->chk_S124->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S124->Location = System::Drawing::Point(178, 38);
            this->chk_S124->Name = L"chk_S124";
            this->chk_S124->Size = System::Drawing::Size(42, 16);
            this->chk_S124->TabIndex = 28;
            this->chk_S124->Text = L"124";
            this->chk_S124->UseVisualStyleBackColor = true;
            // 
            // chk_S123
            // 
            this->chk_S123->AutoSize = true;
            this->chk_S123->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S123->Location = System::Drawing::Point(136, 38);
            this->chk_S123->Name = L"chk_S123";
            this->chk_S123->Size = System::Drawing::Size(42, 16);
            this->chk_S123->TabIndex = 27;
            this->chk_S123->Text = L"123";
            this->chk_S123->UseVisualStyleBackColor = true;
            // 
            // chk_S122
            // 
            this->chk_S122->AutoSize = true;
            this->chk_S122->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S122->Location = System::Drawing::Point(94, 38);
            this->chk_S122->Name = L"chk_S122";
            this->chk_S122->Size = System::Drawing::Size(42, 16);
            this->chk_S122->TabIndex = 26;
            this->chk_S122->Text = L"122";
            this->chk_S122->UseVisualStyleBackColor = true;
            // 
            // chk_S121
            // 
            this->chk_S121->AutoSize = true;
            this->chk_S121->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S121->Location = System::Drawing::Point(52, 38);
            this->chk_S121->Name = L"chk_S121";
            this->chk_S121->Size = System::Drawing::Size(42, 16);
            this->chk_S121->TabIndex = 25;
            this->chk_S121->Text = L"121";
            this->chk_S121->UseVisualStyleBackColor = true;
            // 
            // chk_S120
            // 
            this->chk_S120->AutoSize = true;
            this->chk_S120->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_S120->Location = System::Drawing::Point(10, 38);
            this->chk_S120->Name = L"chk_S120";
            this->chk_S120->Size = System::Drawing::Size(42, 16);
            this->chk_S120->TabIndex = 24;
            this->chk_S120->Text = L"120";
            this->chk_S120->UseVisualStyleBackColor = true;
            // 
            // chk_TYPE_SBASL1
            // 
            this->chk_TYPE_SBASL1->AutoSize = true;
            this->chk_TYPE_SBASL1->Checked = true;
            this->chk_TYPE_SBASL1->CheckState = System::Windows::Forms::CheckState::Checked;
            this->chk_TYPE_SBASL1->Enabled = false;
            this->chk_TYPE_SBASL1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_TYPE_SBASL1->Location = System::Drawing::Point(69, 16);
            this->chk_TYPE_SBASL1->Name = L"chk_TYPE_SBASL1";
            this->chk_TYPE_SBASL1->Size = System::Drawing::Size(54, 16);
            this->chk_TYPE_SBASL1->TabIndex = 23;
            this->chk_TYPE_SBASL1->Text = L"SBAS";
            this->chk_TYPE_SBASL1->UseVisualStyleBackColor = true;
            // 
            // chk_SALL
            // 
            this->chk_SALL->AutoSize = true;
            this->chk_SALL->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->chk_SALL->Location = System::Drawing::Point(10, 16);
            this->chk_SALL->Name = L"chk_SALL";
            this->chk_SALL->Size = System::Drawing::Size(44, 16);
            this->chk_SALL->TabIndex = 22;
            this->chk_SALL->Text = L"ALL";
            this->chk_SALL->UseVisualStyleBackColor = true;
            this->chk_SALL->CheckedChanged += gcnew System::EventHandler(this, &maindlg::chk_SALL_CheckedChanged);
            // 
            // gb_misc
            // 
            this->gb_misc->Controls->Add(this->label10);
            this->gb_misc->Controls->Add(this->label9);
            this->gb_misc->Controls->Add(this->tb_lon);
            this->gb_misc->Controls->Add(this->tb_lat);
            this->gb_misc->Controls->Add(this->label6);
            this->gb_misc->Controls->Add(this->b_radar);
            this->gb_misc->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(128)));
            this->gb_misc->Location = System::Drawing::Point(7, 380);
            this->gb_misc->Name = L"gb_misc";
            this->gb_misc->Size = System::Drawing::Size(414, 38);
            this->gb_misc->TabIndex = 62;
            this->gb_misc->TabStop = false;
            this->gb_misc->Text = L"MISC";
            // 
            // label10
            // 
            this->label10->AutoSize = true;
            this->label10->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->label10->Location = System::Drawing::Point(17, 17);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(53, 12);
            this->label10->TabIndex = 47;
            this->label10->Text = L"Lat (deg):";
            // 
            // label9
            // 
            this->label9->AutoSize = true;
            this->label9->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->label9->Location = System::Drawing::Point(126, 17);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(55, 12);
            this->label9->TabIndex = 46;
            this->label9->Text = L"Lon (deg):";
            // 
            // tb_lon
            // 
            this->tb_lon->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->tb_lon->Location = System::Drawing::Point(182, 13);
            this->tb_lon->Name = L"tb_lon";
            this->tb_lon->Size = System::Drawing::Size(50, 19);
            this->tb_lon->TabIndex = 44;
            this->tb_lon->Text = L"139.8";
            this->tb_lon->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            // 
            // tb_lat
            // 
            this->tb_lat->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->tb_lat->Location = System::Drawing::Point(71, 13);
            this->tb_lat->Name = L"tb_lat";
            this->tb_lat->Size = System::Drawing::Size(50, 19);
            this->tb_lat->TabIndex = 43;
            this->tb_lat->Text = L"35.7";
            this->tb_lat->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->label6->Location = System::Drawing::Point(237, 17);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(148, 12);
            this->label6->TabIndex = 42;
            this->label6->Text = L"Current GNSS Constellation";
            // 
            // b_radar
            // 
            this->b_radar->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
            this->b_radar->Location = System::Drawing::Point(386, 12);
            this->b_radar->Name = L"b_radar";
            this->b_radar->Size = System::Drawing::Size(20, 20);
            this->b_radar->TabIndex = 41;
            this->b_radar->Text = L"...";
            this->b_radar->UseVisualStyleBackColor = true;
            this->b_radar->Click += gcnew System::EventHandler(this, &maindlg::b_radar_Click);
            // 
            // maindlg
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(865, 460);
            this->Controls->Add(this->gb_misc);
            this->Controls->Add(this->gb_sbs);
            this->Controls->Add(this->gb_bds);
            this->Controls->Add(this->gb_gal);
            this->Controls->Add(this->gb_glo);
            this->Controls->Add(this->chk_monitor);
            this->Controls->Add(this->rb_spec2);
            this->Controls->Add(this->rb_spec1);
            this->Controls->Add(this->chk_spec);
            this->Controls->Add(this->b_exit);
            this->Controls->Add(this->b_stop);
            this->Controls->Add(this->b_start);
            this->Controls->Add(this->gb_qzs);
            this->Controls->Add(this->gb_gps);
            this->Controls->Add(this->gb_setting);
            this->Controls->Add(this->gb_output);
            this->Controls->Add(this->gb_input);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
            this->MaximizeBox = false;
            this->Name = L"maindlg";
            this->Text = L"GNSS-SDRLIB-GUI";
            this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &maindlg::maindlg_FormClosing);
            this->Load += gcnew System::EventHandler(this, &maindlg::maindlg_Load);
            this->gb_input->ResumeLayout(false);
            this->gb_input->PerformLayout();
            this->gb_output->ResumeLayout(false);
            this->gb_output->PerformLayout();
            this->gb_setting->ResumeLayout(false);
            this->gb_setting->PerformLayout();
            this->gp_FE2->ResumeLayout(false);
            this->gp_FE2->PerformLayout();
            this->groupBox9->ResumeLayout(false);
            this->groupBox9->PerformLayout();
            this->gp_FE1->ResumeLayout(false);
            this->gp_FE1->PerformLayout();
            this->groupBox3->ResumeLayout(false);
            this->groupBox3->PerformLayout();
            this->gb_gps->ResumeLayout(false);
            this->gb_gps->PerformLayout();
            this->gb_qzs->ResumeLayout(false);
            this->gb_qzs->PerformLayout();
            this->gb_glo->ResumeLayout(false);
            this->gb_glo->PerformLayout();
            this->gb_gal->ResumeLayout(false);
            this->gb_gal->PerformLayout();
            this->gb_bds->ResumeLayout(false);
            this->gb_bds->PerformLayout();
            this->gb_sbs->ResumeLayout(false);
            this->gb_sbs->PerformLayout();
            this->gb_misc->ResumeLayout(false);
            this->gb_misc->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private: System::Void chk_rinex_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
                 if (chk_rinex->Checked) {
                     l_rinex->Enabled=true;
                     l_output->Enabled=true;
                     cmb_outint->Enabled=true;
                     tb_rinex_dir->Enabled=true;
                     b_rinex->Enabled=true;
                 } else {
                     l_rinex->Enabled=false;
                     tb_rinex_dir->Enabled=false;
                     b_rinex->Enabled=false;
                     if (!chk_rtcm->Checked) {
                         cmb_outint->Enabled=false;
                         l_output->Enabled=false;
                     }
                 }
             }
    private: System::Void chk_rtcm_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
                 if (chk_rtcm->Checked) {
                     l_rtcm->Enabled=true; 
                     l_output->Enabled=true;
                     cmb_outint->Enabled=true;
                     tb_rtcm_port->Enabled=true;
                 } else {
                     l_rtcm->Enabled=false; 
                     tb_rtcm_port->Enabled=false;
                     if (!chk_rinex->Checked) {
                         cmb_outint->Enabled=false;
                         l_output->Enabled=false;
                     }
                 }
             }
    private: System::Void chk_lex_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
                 if (chk_lex->Checked) {
                     l_lex->Enabled=true;
                     tb_lex_port->Enabled=true;
                 } else {
                     l_lex->Enabled=false;
                     tb_lex_port->Enabled=false;
                 }
             }
    private: System::Void chk_saif_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
                 if (chk_saif->Checked) {
                     l_saif->Enabled=true;
                     tb_saif_port->Enabled=true;
                 } else {
                     l_saif->Enabled=false;
                     tb_saif_port->Enabled=false;
                 }
             }
    private: System::Void chk_GALL_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
                 if (chk_GALL->Checked) {
                     chk_G01->Checked=true;
                     chk_G02->Checked=true;
                     chk_G03->Checked=true;
                     chk_G04->Checked=true;
                     chk_G05->Checked=true;
                     chk_G06->Checked=true;
                     chk_G07->Checked=true;
                     chk_G08->Checked=true;
                     chk_G09->Checked=true;
                     chk_G10->Checked=true;
                     chk_G11->Checked=true;
                     chk_G12->Checked=true;
                     chk_G13->Checked=true;
                     chk_G14->Checked=true;
                     chk_G15->Checked=true;
                     chk_G16->Checked=true;
                     chk_G17->Checked=true;
                     chk_G18->Checked=true;
                     chk_G19->Checked=true;
                     chk_G20->Checked=true;
                     chk_G21->Checked=true;
                     chk_G22->Checked=true;
                     chk_G23->Checked=true;
                     chk_G24->Checked=true;
                     chk_G25->Checked=true;
                     chk_G26->Checked=true;
                     chk_G27->Checked=true;
                     chk_G28->Checked=true;
                     chk_G29->Checked=true;
                     chk_G30->Checked=true;
                     chk_G31->Checked=true;
                     chk_G32->Checked=true;
                 } else {
                     chk_G01->Checked=false;
                     chk_G02->Checked=false;
                     chk_G03->Checked=false;
                     chk_G04->Checked=false;
                     chk_G05->Checked=false;
                     chk_G06->Checked=false;
                     chk_G07->Checked=false;
                     chk_G08->Checked=false;
                     chk_G09->Checked=false;
                     chk_G10->Checked=false;
                     chk_G11->Checked=false;
                     chk_G12->Checked=false;
                     chk_G13->Checked=false;
                     chk_G14->Checked=false;
                     chk_G15->Checked=false;
                     chk_G16->Checked=false;
                     chk_G17->Checked=false;
                     chk_G18->Checked=false;
                     chk_G19->Checked=false;
                     chk_G20->Checked=false;
                     chk_G21->Checked=false;
                     chk_G22->Checked=false;
                     chk_G23->Checked=false;
                     chk_G24->Checked=false;
                     chk_G25->Checked=false;
                     chk_G26->Checked=false;
                     chk_G27->Checked=false;
                     chk_G28->Checked=false;
                     chk_G29->Checked=false;
                     chk_G30->Checked=false;
                     chk_G31->Checked=false;
                     chk_G32->Checked=false;
                 }
             }
    private: System::Void chk_RALL_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
                 if (chk_RALL->Checked) {
                     chk_R_7->Checked=true;
                     chk_R_6->Checked=true;
                     chk_R_5->Checked=true;
                     chk_R_4->Checked=true;
                     chk_R_3->Checked=true;
                     chk_R_2->Checked=true;
                     chk_R_1->Checked=true;
                     chk_R0->Checked=true;
                     chk_R1->Checked=true;
                     chk_R2->Checked=true;
                     chk_R3->Checked=true;
                     chk_R4->Checked=true;
                     chk_R5->Checked=true;
                     chk_R6->Checked=true;
                 } else {
                     chk_R_7->Checked=false;
                     chk_R_6->Checked=false;
                     chk_R_5->Checked=false;
                     chk_R_4->Checked=false;
                     chk_R_3->Checked=false;
                     chk_R_2->Checked=false;
                     chk_R_1->Checked=false;
                     chk_R0->Checked=false;
                     chk_R1->Checked=false;
                     chk_R2->Checked=false;
                     chk_R3->Checked=false;
                     chk_R4->Checked=false;
                     chk_R5->Checked=false;
                     chk_R6->Checked=false;
                 }
             }
    private: System::Void chk_EALL_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
                 if (chk_EALL->Checked) {
                     chk_E11->Checked=true;
                     chk_E12->Checked=true;
                     chk_E19->Checked=true;
                     chk_E20->Checked=true;
                 } else {
                     chk_E11->Checked=false;
                     chk_E12->Checked=false;
                     chk_E19->Checked=false;
                     chk_E20->Checked=false;
                 }
             }
    private: System::Void chk_CALL_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
                 if (chk_CALL->Checked) {
                     chk_C01->Checked=true;
                     chk_C02->Checked=true;
                     chk_C03->Checked=true;
                     chk_C04->Checked=true;
                     chk_C05->Checked=true;
                     chk_C06->Checked=true;
                     chk_C07->Checked=true;
                     chk_C08->Checked=true;
                     chk_C09->Checked=true;
                     chk_C10->Checked=true;
                     chk_C11->Checked=true;
                     chk_C12->Checked=true;
                     chk_C13->Checked=true;
                     chk_C14->Checked=true;
                 } else {
                     chk_C01->Checked=false;
                     chk_C02->Checked=false;
                     chk_C03->Checked=false;
                     chk_C04->Checked=false;
                     chk_C05->Checked=false;
                     chk_C06->Checked=false;
                     chk_C07->Checked=false;
                     chk_C08->Checked=false;
                     chk_C09->Checked=false;
                     chk_C10->Checked=false;
                     chk_C11->Checked=false;
                     chk_C12->Checked=false;
                     chk_C13->Checked=false;
                     chk_C14->Checked=false;
                 }
             }
    private: System::Void chk_SALL_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
                 if (chk_SALL->Checked) {
                     chk_S120->Checked=true;
                     chk_S121->Checked=true;
                     chk_S122->Checked=true;
                     chk_S123->Checked=true;
                     chk_S124->Checked=true;
                     chk_S125->Checked=true;
                     chk_S126->Checked=true;
                     chk_S127->Checked=true;
                     chk_S128->Checked=true;
                     chk_S129->Checked=true;
                     chk_S130->Checked=true;
                     chk_S131->Checked=true;
                     chk_S132->Checked=true;
                     chk_S133->Checked=true;
                     chk_S134->Checked=true;
                     chk_S135->Checked=true;
                     chk_S136->Checked=true;
                     chk_S137->Checked=true;
                     chk_S138->Checked=true;
                 } else {
                     chk_S120->Checked=false;
                     chk_S121->Checked=false;
                     chk_S122->Checked=false;
                     chk_S123->Checked=false;
                     chk_S124->Checked=false;
                     chk_S125->Checked=false;
                     chk_S126->Checked=false;
                     chk_S127->Checked=false;
                     chk_S128->Checked=false;
                     chk_S129->Checked=false;
                     chk_S130->Checked=false;
                     chk_S131->Checked=false;
                     chk_S132->Checked=false;
                     chk_S133->Checked=false;
                     chk_S134->Checked=false;
                     chk_S135->Checked=false;
                     chk_S136->Checked=false;
                     chk_S137->Checked=false;
                     chk_S138->Checked=false;
                 }
             }
    private: System::Void comb_input_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

                 config->tb_corrn="5";
                 config->tb_corrd="4";
                 config->tb_corrp="4";
                 config->tb_dll1="5.0";
                 config->tb_pll1="30.0";
                 config->tb_fll1="500.0";
                 config->tb_dll2="1.0";
                 config->tb_pll2="10.0";
                 config->tb_fll2="50.0";

                 switch (cmb_input->SelectedIndex) {
                 case 0: /* STEREO */
                     cb_freq_stereo();

                     tb_input1->Enabled=false;
                     b_input1->Enabled=false;
                     l_input1->Enabled=false;
                     tb_input2->Enabled=false;
                     b_input2->Enabled=false;
                     chk_input2->Enabled=false;
                     l_input2->Enabled=false;
                     rb_f1I->Checked=true;
                     rb_f2IQ->Checked=true;
                     tb_f1sf->Text="20.0";
                     tb_f1if->Text="4.0";
                     tb_f2sf->Text="20.0";
                     tb_f2if->Text="0.0";

                     chk_input2->Checked=false;
                     chk_input2->Enabled=false;

                     ppm_disable();

                     enable_FE2();
                     break;
                 case 1: /* GN3Sv2 */
                     cb_freq_L1();

                     tb_input1->Enabled=false;
                     b_input1->Enabled=false;
                     l_input1->Enabled=false;
                     tb_input2->Enabled=false;
                     b_input2->Enabled=false;
                     chk_input2->Enabled=false;
                     l_input2->Enabled=false;
                     rb_f1IQ->Checked=true;
                     rb_f2IQ->Checked=true;
                     tb_f1sf->Text="8.1838";
                     tb_f1if->Text="0.0384";
                     tb_f2sf->Text="0.0";
                     tb_f2if->Text="0.0";

                     chk_input2->Checked=false;
                     chk_input2->Enabled=false;

                     ppm_disable();

                     disable_FE2();

                     config->tb_corrn="6";
                     config->tb_corrd="2";
                     config->tb_corrp="2";
                     break;
                 case 2: /* GN3Sv3 */
                     cb_freq_L1();

                     tb_input1->Enabled=false;
                     b_input1->Enabled=false;
                     l_input1->Enabled=false;
                     tb_input2->Enabled=false;
                     b_input2->Enabled=false;
                     chk_input2->Enabled=false;
                     l_input2->Enabled=false;
                     rb_f1I->Checked=true;
                     rb_f2IQ->Checked=true;
                     tb_f1sf->Text="16.368";
                     tb_f1if->Text="4.092";
                     tb_f2sf->Text="0.0";
                     tb_f2if->Text="0.0";

                     chk_input2->Checked=false;
                     chk_input2->Enabled=false;

                     ppm_disable();

                     disable_FE2();

                     config->tb_corrn="6";
                     config->tb_corrd="3";
                     config->tb_corrp="6";
                     break;
                 case 3: /* RTLSDR */
                     cb_freq_L1();

                     tb_input1->Enabled=false;
                     b_input1->Enabled=false;
                     l_input1->Enabled=false;
                     tb_input2->Enabled=false;
                     b_input2->Enabled=false;
                     chk_input2->Enabled=false;
                     l_input2->Enabled=false;
                     rb_f1IQ->Checked=true;
                     rb_f2IQ->Checked=true;
                     tb_f1sf->Text="2.048";
                     tb_f1if->Text="0.0";
                     tb_f2sf->Text="0.0";
                     tb_f2if->Text="0.0";

                     chk_input2->Checked=false;
                     chk_input2->Enabled=false;

                     ppm_enable();

                     disable_FE2();

                     config->tb_corrn="4";
                     config->tb_corrd="1";
                     config->tb_corrp="1";
                     config->tb_dll2="2.0";
                     config->tb_pll2="20.0";
                     config->tb_fll2="50.0";
                     break;
                 case 4: /* BladeRF */
                     cb_freq_L1();

                     tb_input1->Enabled=false;
                     b_input1->Enabled=false;
                     l_input1->Enabled=false;
                     tb_input2->Enabled=false;
                     b_input2->Enabled=false;
                     chk_input2->Enabled=false;
                     l_input2->Enabled=false;
                     rb_f1IQ->Checked=true;
                     rb_f2IQ->Checked=true;
                     tb_f1sf->Text="20.0";
                     tb_f1if->Text="0.0";
                     tb_f2sf->Text="0.0";
                     tb_f2if->Text="0.0";

                     chk_input2->Checked=false;
                     chk_input2->Enabled=false;

                     ppm_disable();

                     disable_FE2();
                     break;
                 case 5: /* File (STEREO) */
                     cb_freq_stereo();

                     tb_input1->Enabled=true;
                     b_input1->Enabled=true;
                     l_input1->Enabled=true;
                     tb_input2->Enabled=false;
                     b_input2->Enabled=false;
                     chk_input2->Enabled=false;
                     l_input2->Enabled=false;
                     rb_f1I->Checked=true;
                     rb_f2IQ->Checked=true;
                     tb_f1sf->Text="20.0";
                     tb_f1if->Text="4.0";
                     tb_f2sf->Text="20.0";
                     tb_f2if->Text="0.0";

                     chk_input2->Checked=false;
                     chk_input2->Enabled=false;

                     ppm_disable();

                     enable_FE2();
                     break;
                 case 6: /* FILE(GN3Sv2) */
                     cb_freq_L1();

                     tb_input1->Enabled=true;
                     b_input1->Enabled=true;
                     l_input1->Enabled=true;
                     tb_input2->Enabled=false;
                     b_input2->Enabled=false;
                     chk_input2->Enabled=false;
                     l_input2->Enabled=false;
                     rb_f1IQ->Checked=true;
                     rb_f2IQ->Checked=true;
                     tb_f1sf->Text="8.1838";
                     tb_f1if->Text="0.0384";
                     tb_f2sf->Text="0.0";
                     tb_f2if->Text="0.0";

                     chk_input2->Checked=false;
                     chk_input2->Enabled=false;

                     ppm_disable();

                     disable_FE2();

                     config->tb_corrn="6";
                     config->tb_corrd="2";
                     config->tb_corrp="2";
                     break;
                 case 7: /* FILE(GN3Sv3) */
                     cb_freq_L1();

                     tb_input1->Enabled=true;
                     b_input1->Enabled=true;
                     l_input1->Enabled=true;
                     tb_input2->Enabled=false;
                     b_input2->Enabled=false;
                     chk_input2->Enabled=false;
                     l_input2->Enabled=false;
                     rb_f1I->Checked=true;
                     rb_f2IQ->Checked=true;
                     tb_f1sf->Text="16.368";
                     tb_f1if->Text="4.092";
                     tb_f2sf->Text="0.0";
                     tb_f2if->Text="0.0";

                     chk_input2->Checked=false;
                     chk_input2->Enabled=false;

                     ppm_disable();

                     disable_FE2();

                     config->tb_corrn="6";
                     config->tb_corrd="3";
                     config->tb_corrp="6";
                     break;
                 case 8: /* FILE(RTLSDR) */
                     cb_freq_L1();

                     tb_input1->Enabled=true;
                     b_input1->Enabled=true;
                     l_input1->Enabled=true;
                     tb_input2->Enabled=false;
                     b_input2->Enabled=false;
                     chk_input2->Enabled=false;
                     l_input2->Enabled=false;
                     rb_f1IQ->Checked=true;
                     rb_f2IQ->Checked=true;
                     tb_f1sf->Text="2.048";
                     tb_f1if->Text="0.0";
                     tb_f2sf->Text="0.0";
                     tb_f2if->Text="0.0";

                     chk_input2->Checked=false;
                     chk_input2->Enabled=false;

                     ppm_enable();

                     disable_FE2();

                     config->tb_corrn="4";
                     config->tb_corrd="1";
                     config->tb_corrp="1";
                     config->tb_dll2="2.0";
                     config->tb_pll2="20.0";
                     config->tb_fll2="50.0";
                     break;
                 case 9: /* FILE(BladeRF) */
                     cb_freq_L1();

                     tb_input1->Enabled=true;
                     b_input1->Enabled=true;
                     l_input1->Enabled=true;
                     tb_input2->Enabled=false;
                     b_input2->Enabled=false;
                     chk_input2->Enabled=false;
                     l_input2->Enabled=false;
                     rb_f1IQ->Checked=true;
                     rb_f2IQ->Checked=true;
                     tb_f1sf->Text="20.0";
                     tb_f1if->Text="0.0";
                     tb_f2sf->Text="0.0";
                     tb_f2if->Text="0.0";

                     chk_input2->Checked=false;
                     chk_input2->Enabled=false;

                     ppm_disable();

                     disable_FE2();
                     break;
                 case 10: /* File */
                     cb_freq_all();

                     tb_input1->Enabled=true;
                     b_input1->Enabled=true;
                     l_input1->Enabled=true;
                     tb_input2->Enabled=false;
                     b_input2->Enabled=false;
                     chk_input2->Enabled=false;
                     l_input2->Enabled=false;
                     rb_f1I->Checked=true;
                     rb_f2IQ->Checked=true;

                     ppm_disable();

                     chk_input2->Enabled=true;
                     disable_FE2();
                     break;
                 }
             }
    private: System::Void b_input1_Click(System::Object^  sender, System::EventArgs^  e) {
                 inputfiledlg->ShowDialog();
                 tb_input1->Text=inputfiledlg->FileName;
             }
    private: System::Void b_input2_Click(System::Object^  sender, System::EventArgs^  e) {
                 inputfiledlg->ShowDialog();
                 tb_input2->Text=inputfiledlg->FileName;
             }
    private: System::Void b_rinex_Click(System::Object^  sender, System::EventArgs^  e) {
                 inputdirdlg->ShowDialog();
                 tb_rinex_dir->Text=inputdirdlg->SelectedPath;
             }
    private: System::Void b_monitor_Click(System::Object^  sender, System::EventArgs^  e) {
                 monitor=gcnew monitordlg();
                 monitor->Show();
             }
    public: System::Void b_start_Click(System::Object^  sender, System::EventArgs^  e) {
                saveform();
                WriteConfig();
                b_start->Enabled=false;
                b_stop->Enabled=true; 
                sdr->start(this);
                gb_input->Enabled=false;
                gb_output->Enabled=false;
                gb_setting->Enabled=false;
                gb_gps->Enabled=false;
                gb_glo->Enabled=false;
                gb_gal->Enabled=false;
                gb_bds->Enabled=false;
                gb_qzs->Enabled=false;
                gb_sbs->Enabled=false;
                chk_spec->Enabled=true;
            }
    private: System::Void b_stop_Click(System::Object^  sender, System::EventArgs^  e) {
                 sdr->stop(this);
             }
    private: System::Void b_exit_Click(System::Object^  sender, System::EventArgs^  e) {
                 Close();
             }
    private: System::Void maindlg_Load(System::Object^  sender, System::EventArgs^  e) {
                 sdr=gcnew SDR();

                 if (ReadConfig() == true)
                 {
                     config->tb_corrn="5";
                     config->tb_corrd="4";
                     config->tb_corrp="4";
                     config->tb_dll1="5.0";
                     config->tb_pll1="30.0";
                     config->tb_fll1="500.0";
                     config->tb_dll2="1.0";
                     config->tb_pll2="10.0";
                     config->tb_fll2="50.0";

                     switch (cmb_input->SelectedIndex) {
                     case 0: /* STEREO */
                         cb_freq_stereo();
                         break;
                     case 1: /* GN3Sv2 */
                         cb_freq_L1();
                         config->tb_corrn="6";
                         config->tb_corrd="2";
                         config->tb_corrp="2";
                         break;
                     case 2: /* GN3Sv3 */
                         cb_freq_L1();
                         config->tb_corrn="6";
                         config->tb_corrd="3";
                         config->tb_corrp="6";
                         break;
                     case 3: /* RTLSDR */
                         cb_freq_L1();
                         config->tb_corrn="4";
                         config->tb_corrd="1";
                         config->tb_corrp="1";
                         config->tb_dll2="2.0";
                         config->tb_pll2="20.0";
                         config->tb_fll2="50.0";
                         break;
                     case 4: /* BladeRF */
                         cb_freq_L1();
                         break;
                     case 5: /* File (STEREO) */
                         cb_freq_stereo();
                         break;
                     case 6: /* File (GN3Sv2) */
                         cb_freq_L1();
                         config->tb_corrn="6";
                         config->tb_corrd="2";
                         config->tb_corrp="2";
                         break;
                     case 7: /* File (GN3Sv3) */
                         cb_freq_L1();
                         config->tb_corrn="6";
                         config->tb_corrd="3";
                         config->tb_corrp="6";
                         break;
                     case 8: /* File (RTLSDR) */
                         cb_freq_L1();
                         config->tb_corrn="4";
                         config->tb_corrd="1";
                         config->tb_corrp="1";
                         config->tb_dll2="2.0";
                         config->tb_pll2="20.0";
                         config->tb_fll2="50.0";
                         break;
                     case 9: /* File (BladeRF) */
                         cb_freq_L1();
                         break;
                     case 10: /* File */
                         cb_freq_all();
                         break;
                     }
                 } else {
                     cmb_outint->SelectedIndex=0;
                     saveform();
                     WriteConfig();
                 }

                 loadform();
             }
    private: System::Void maindlg_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
                 saveform();
                 WriteConfig();
             }
             delegate void mprintfdelegate(String^str);
    public: void mprintf(String^str) {
                /* form has not been created */
                if (monitor==nullptr) return;
                else if (monitor->IsDisposed) return;

                /* mprintf is called from other thread */
                if (monitor->ls_monitor->InvokeRequired) {
                    monitor->ls_monitor->Invoke(gcnew mprintfdelegate(this,&maindlg::mprintf),gcnew array<Object^,1>{str});
                    return;
                }
                monitor->ls_monitor->Items->Add(str);
                monitor->ls_monitor->Update();
                monitor->ls_monitor->TopIndex=monitor->ls_monitor->Items->Count-1; 
            }
            delegate void guistopdelegate();
    public: void guistop() {
                /* guistop is called from other thread */
                if (this->InvokeRequired) {
                    this->Invoke(gcnew guistopdelegate(this,&maindlg::guistop));
                    return;
                }
                sleepms(500);
                b_stop->Enabled=false;
                b_start->Enabled=true;
                gb_input->Enabled=true;
                gb_output->Enabled=true;
                gb_setting->Enabled=true;
                gb_gps->Enabled=true;
                gb_glo->Enabled=true;
                gb_gal->Enabled=true;
                gb_bds->Enabled=true;
                gb_qzs->Enabled=true;
                gb_sbs->Enabled=true;
                chk_spec->Checked=false;
                chk_spec->Enabled=false;
            }
    private: String^ GetUserAppDataPath(void)
             {
                 String^ path = String::Format("{0}\\{1}\\{2}",
                     Environment::GetFolderPath(Environment::SpecialFolder::ApplicationData),
                     Application::CompanyName,
                     Application::ProductName);

                 if (Directory::Exists(path) == false)
                 {
                     Directory::CreateDirectory(path);
                 }

                 return path;
             }
    private: property String^ ConfigPath {
                 String^ get()
                 {
                     return this->GetUserAppDataPath() + "\\" + "gnsssdrlib_v2.0b.config";
                 }
             }
    public: bool WriteConfig(void)
            {
                bool retVal = false;
                XmlSerializer^ serializer = nullptr;
                StreamWriter^ writer = nullptr;

                try {
                    serializer = gcnew XmlSerializer(CONFIG::typeid);
                    writer = gcnew StreamWriter(this->ConfigPath, false);
                    serializer->Serialize(writer, config);
                    retVal = true;
                } catch (Exception^ ex) {
                } finally {
                    if (writer != nullptr)
                    {
                        writer->Close();
                    }
                }

                return retVal;
            }
    public: bool ReadConfig(void)
            {
                bool retVal = false;
                FileInfo^ fileinfo = gcnew FileInfo(this->ConfigPath);
                XmlSerializer^ serializer = nullptr;
                FileStream^ filestream = nullptr;

                try {
                    if (fileinfo->Exists == true)
                    {
                        serializer = gcnew XmlSerializer(CONFIG::typeid);
                        filestream = fileinfo->OpenRead();
                        config = (CONFIG^)serializer->Deserialize(filestream);
                        retVal = true;
                    }
                } catch (Exception^ ex) {
                } finally {
                    if (filestream != nullptr)
                    {
                        filestream->Close();
                    }
                    if (config == nullptr)
                    {
                        config = gcnew CONFIG();
                    }
                }

                return retVal;
            }
    public: void loadform()
            {
                tb_input1->Text=config->tb_input1;
                tb_input2->Text=config->tb_input2;
                cmb_input->SelectedIndex=config->cmb_input;
                tb_f1sf->Text=config->tb_f1sf;
                tb_f2sf->Text=config->tb_f2sf;
                tb_f1if->Text=config->tb_f1if;
                tb_f2if->Text=config->tb_f2if;
                rb_f1IQ->Checked=config->rb_f1IQ;
                rb_f2IQ->Checked=config->rb_f2IQ;
                cb_cf1->SelectedIndex=config->cb_cf1;
                cb_cf2->SelectedIndex=config->cb_cf2;
                tb_clk->Text=config->tb_clk;

                /* GPS */
                rb_G_FE1->Checked=config->rb_G_FE1;
                rb_G_FE2->Checked=config->rb_G_FE2;
                chk_TYPE_L1CA->Checked=config->chk_TYPE_L1CA;
                chk_G01->Checked=config->chk_G01;
                chk_G02->Checked=config->chk_G02;
                chk_G03->Checked=config->chk_G03;
                chk_G04->Checked=config->chk_G04;
                chk_G05->Checked=config->chk_G05;
                chk_G06->Checked=config->chk_G06;
                chk_G07->Checked=config->chk_G07;
                chk_G08->Checked=config->chk_G08;
                chk_G09->Checked=config->chk_G09;
                chk_G10->Checked=config->chk_G10;
                chk_G11->Checked=config->chk_G11;
                chk_G12->Checked=config->chk_G12;
                chk_G13->Checked=config->chk_G13;
                chk_G14->Checked=config->chk_G14;
                chk_G15->Checked=config->chk_G15;
                chk_G16->Checked=config->chk_G16;
                chk_G17->Checked=config->chk_G17;
                chk_G18->Checked=config->chk_G18;
                chk_G19->Checked=config->chk_G19;
                chk_G20->Checked=config->chk_G20;
                chk_G21->Checked=config->chk_G21;
                chk_G22->Checked=config->chk_G22;
                chk_G23->Checked=config->chk_G23;
                chk_G24->Checked=config->chk_G24;
                chk_G25->Checked=config->chk_G25;
                chk_G26->Checked=config->chk_G26;
                chk_G27->Checked=config->chk_G27;
                chk_G28->Checked=config->chk_G28;
                chk_G29->Checked=config->chk_G29;
                chk_G30->Checked=config->chk_G30;
                chk_G31->Checked=config->chk_G31;
                chk_G32->Checked=config->chk_G32;

                /* GLONASS */
                rb_R_FE1->Checked=config->rb_R_FE1;
                rb_R_FE2->Checked=config->rb_R_FE2;
                chk_TYPE_G1->Checked=config->chk_TYPE_G1;
                chk_R_7->Checked=config->chk_R_7;
                chk_R_6->Checked=config->chk_R_6;
                chk_R_5->Checked=config->chk_R_5;
                chk_R_4->Checked=config->chk_R_4;
                chk_R_3->Checked=config->chk_R_3;
                chk_R_2->Checked=config->chk_R_2;
                chk_R_1->Checked=config->chk_R_1;
                chk_R0->Checked=config->chk_R0;
                chk_R1->Checked=config->chk_R1;
                chk_R2->Checked=config->chk_R2;
                chk_R3->Checked=config->chk_R3;
                chk_R4->Checked=config->chk_R4;
                chk_R5->Checked=config->chk_R5;
                chk_R6->Checked=config->chk_R6;

                /* Galileo */
                rb_E_FE1->Checked=config->rb_E_FE1;
                rb_E_FE2->Checked=config->rb_E_FE2;
                chk_TYPE_E1B->Checked=config->chk_TYPE_E1B;
                chk_E11->Checked=config->chk_E11;
                chk_E12->Checked=config->chk_E12;
                chk_E19->Checked=config->chk_E19;
                chk_E20->Checked=config->chk_E20;

                /* BeiDou */
                rb_C_FE1->Checked=config->rb_C_FE1;
                rb_C_FE2->Checked=config->rb_C_FE2;
                chk_TYPE_B1I->Checked=config->chk_TYPE_B1I;
                chk_C01->Checked=config->chk_C01;
                chk_C02->Checked=config->chk_C02;
                chk_C03->Checked=config->chk_C03;
                chk_C04->Checked=config->chk_C04;
                chk_C05->Checked=config->chk_C05;
                chk_C06->Checked=config->chk_C06;
                chk_C07->Checked=config->chk_C07;
                chk_C08->Checked=config->chk_C08;
                chk_C09->Checked=config->chk_C09;
                chk_C10->Checked=config->chk_C10;
                chk_C11->Checked=config->chk_C11;
                chk_C12->Checked=config->chk_C12;
                chk_C13->Checked=config->chk_C13;
                chk_C14->Checked=config->chk_C14;

                /* QZSS */
                chk_TYPE_L1CAQZS->Checked=config->chk_TYPE_L1CAQZS;
                chk_TYPE_SAIF->Checked=config->chk_TYPE_SAIF;
                chk_TYPE_LEX->Checked=config->chk_TYPE_LEX;
                chk_Q01->Checked=config->chk_Q01;

                /* SBAS */
                rb_S_FE1->Checked=config->rb_S_FE1;
                rb_S_FE2->Checked=config->rb_S_FE2;
                chk_TYPE_SBASL1->Checked=config->chk_TYPE_SBASL1;
                chk_S120->Checked=config->chk_S120;
                chk_S121->Checked=config->chk_S121;
                chk_S122->Checked=config->chk_S122;
                chk_S123->Checked=config->chk_S123;
                chk_S124->Checked=config->chk_S124;
                chk_S125->Checked=config->chk_S125;
                chk_S126->Checked=config->chk_S126;
                chk_S127->Checked=config->chk_S127;
                chk_S128->Checked=config->chk_S128;
                chk_S129->Checked=config->chk_S129;
                chk_S130->Checked=config->chk_S130;
                chk_S131->Checked=config->chk_S131;
                chk_S132->Checked=config->chk_S132;
                chk_S133->Checked=config->chk_S133;
                chk_S134->Checked=config->chk_S134;
                chk_S135->Checked=config->chk_S135;
                chk_S136->Checked=config->chk_S136;
                chk_S137->Checked=config->chk_S137;
                chk_S138->Checked=config->chk_S138;

                chk_plotacq->Checked=config->chk_plotacq;
                chk_plottrk->Checked=config->chk_plottrk;

                cmb_outint->SelectedIndex=config->cmb_outint;
                chk_rinex->Checked=config->chk_rinex;
                chk_rtcm->Checked=config->chk_rtcm;
                chk_lex->Checked=config->chk_lex;
                chk_saif->Checked=config->chk_saif;

                tb_rinex_dir->Text=config->tb_rinex_dir;
                tb_rtcm_port->Text=config->tb_rtcm_port;
                tb_lex_port->Text=config->tb_lex_port;
                tb_saif_port->Text=config->tb_saif_port;

                rb_spec1->Checked=config->rb_spec1;
                rb_spec2->Checked=config->rb_spec2;

                tb_lat->Text=config->tb_lat;
                tb_lon->Text=config->tb_lon;

            }
    public: void saveform()
            {
                config->tb_input1=tb_input1->Text;
                config->tb_input2=tb_input2->Text;
                config->cmb_input=cmb_input->SelectedIndex;
                config->tb_f1sf=tb_f1sf->Text;
                config->tb_f2sf=tb_f2sf->Text;
                config->tb_f1if=tb_f1if->Text;
                config->tb_f2if=tb_f2if->Text;
                config->rb_f1IQ=rb_f1IQ->Checked;
                config->rb_f2IQ=rb_f2IQ->Checked;
                config->cb_cf1=cb_cf1->SelectedIndex;
                config->cb_cf2=cb_cf2->SelectedIndex;
                config->tb_clk=tb_clk->Text;

                /* GPS */
                config->rb_G_FE1=rb_G_FE1->Checked;
                config->rb_G_FE2=rb_G_FE2->Checked;
                config->chk_TYPE_L1CA=chk_TYPE_L1CA->Checked;
                config->chk_G01=chk_G01->Checked;
                config->chk_G02=chk_G02->Checked;
                config->chk_G03=chk_G03->Checked;
                config->chk_G04=chk_G04->Checked;
                config->chk_G05=chk_G05->Checked;
                config->chk_G06=chk_G06->Checked;
                config->chk_G07=chk_G07->Checked;
                config->chk_G08=chk_G08->Checked;
                config->chk_G09=chk_G09->Checked;
                config->chk_G10=chk_G10->Checked;
                config->chk_G11=chk_G11->Checked;
                config->chk_G12=chk_G12->Checked;
                config->chk_G13=chk_G13->Checked;
                config->chk_G14=chk_G14->Checked;
                config->chk_G15=chk_G15->Checked;
                config->chk_G16=chk_G16->Checked;
                config->chk_G17=chk_G17->Checked;
                config->chk_G18=chk_G18->Checked;
                config->chk_G19=chk_G19->Checked;
                config->chk_G20=chk_G20->Checked;
                config->chk_G21=chk_G21->Checked;
                config->chk_G22=chk_G22->Checked;
                config->chk_G23=chk_G23->Checked;
                config->chk_G24=chk_G24->Checked;
                config->chk_G25=chk_G25->Checked;
                config->chk_G26=chk_G26->Checked;
                config->chk_G27=chk_G27->Checked;
                config->chk_G28=chk_G28->Checked;
                config->chk_G29=chk_G29->Checked;
                config->chk_G30=chk_G30->Checked;
                config->chk_G31=chk_G31->Checked;
                config->chk_G32=chk_G32->Checked;

                /* GLONASS */
                config->rb_R_FE1=rb_R_FE1->Checked;
                config->rb_R_FE2=rb_R_FE2->Checked;
                config->chk_TYPE_G1=chk_TYPE_G1->Checked;
                config->chk_R_7=chk_R_7->Checked;
                config->chk_R_6=chk_R_6->Checked;
                config->chk_R_5=chk_R_5->Checked;
                config->chk_R_4=chk_R_4->Checked;
                config->chk_R_3=chk_R_3->Checked;
                config->chk_R_2=chk_R_2->Checked;
                config->chk_R_1=chk_R_1->Checked;
                config->chk_R0=chk_R0->Checked;
                config->chk_R1=chk_R1->Checked;
                config->chk_R2=chk_R2->Checked;
                config->chk_R3=chk_R3->Checked;
                config->chk_R4=chk_R4->Checked;
                config->chk_R5=chk_R5->Checked;
                config->chk_R6=chk_R6->Checked;

                /* Galileo */
                config->rb_E_FE1=rb_E_FE1->Checked;
                config->rb_E_FE2=rb_E_FE2->Checked;
                config->chk_TYPE_E1B=chk_TYPE_E1B->Checked;
                config->chk_E11=chk_E11->Checked;
                config->chk_E12=chk_E12->Checked;
                config->chk_E19=chk_E19->Checked;
                config->chk_E20=chk_E20->Checked;

                /* BeiDou */
                config->rb_C_FE1=rb_C_FE1->Checked;
                config->rb_C_FE2=rb_C_FE2->Checked;
                config->chk_TYPE_B1I=chk_TYPE_B1I->Checked;
                config->chk_C01=chk_C01->Checked;
                config->chk_C02=chk_C02->Checked;
                config->chk_C03=chk_C03->Checked;
                config->chk_C04=chk_C04->Checked;
                config->chk_C05=chk_C05->Checked;
                config->chk_C06=chk_C06->Checked;
                config->chk_C07=chk_C07->Checked;
                config->chk_C08=chk_C08->Checked;
                config->chk_C09=chk_C09->Checked;
                config->chk_C10=chk_C10->Checked;
                config->chk_C11=chk_C11->Checked;
                config->chk_C12=chk_C12->Checked;
                config->chk_C13=chk_C13->Checked;
                config->chk_C14=chk_C14->Checked;

                /* QZSS */
                config->chk_TYPE_L1CAQZS=chk_TYPE_L1CAQZS->Checked;
                config->chk_TYPE_SAIF=chk_TYPE_SAIF->Checked;
                config->chk_TYPE_LEX=chk_TYPE_LEX->Checked;
                config->chk_Q01=chk_Q01->Checked;

                /* SBAS */
                config->rb_S_FE1=rb_S_FE1->Checked;
                config->rb_S_FE2=rb_S_FE2->Checked;
                config->chk_TYPE_SBASL1=chk_TYPE_SBASL1->Checked;
                config->chk_S120=chk_S120->Checked;
                config->chk_S121=chk_S121->Checked;
                config->chk_S122=chk_S122->Checked;
                config->chk_S123=chk_S123->Checked;
                config->chk_S124=chk_S124->Checked;
                config->chk_S125=chk_S125->Checked;
                config->chk_S126=chk_S126->Checked;
                config->chk_S127=chk_S127->Checked;
                config->chk_S128=chk_S128->Checked;
                config->chk_S129=chk_S129->Checked;
                config->chk_S130=chk_S130->Checked;
                config->chk_S131=chk_S131->Checked;
                config->chk_S132=chk_S132->Checked;
                config->chk_S133=chk_S133->Checked;
                config->chk_S134=chk_S134->Checked;
                config->chk_S135=chk_S135->Checked;
                config->chk_S136=chk_S136->Checked;
                config->chk_S137=chk_S137->Checked;
                config->chk_S138=chk_S138->Checked;

                config->chk_plotacq=chk_plotacq->Checked;
                config->chk_plottrk=chk_plottrk->Checked;

                config->cmb_outint=cmb_outint->SelectedIndex;
                config->chk_rinex=chk_rinex->Checked;
                config->chk_rtcm=chk_rtcm->Checked;
                config->chk_lex=chk_lex->Checked;
                config->chk_saif=chk_saif->Checked;

                config->tb_rinex_dir=tb_rinex_dir->Text;
                config->tb_rtcm_port=tb_rtcm_port->Text;
                config->tb_lex_port=tb_lex_port->Text;
                config->tb_saif_port=tb_saif_port->Text;

                config->rb_spec1=rb_spec1->Checked;
                config->rb_spec2=rb_spec2->Checked;

                config->tb_lat=tb_lat->Text;
                config->tb_lon=tb_lon->Text;
            }
    private: System::Void chk_spec_CheckStateChanged(System::Object^  sender, System::EventArgs^  e) {
                 if (chk_spec->Checked) {
                     sdr->startspectrum(this);
                 } else {
                     sdr->stopspectrum(this);
                     chk_spec->Enabled=false;
                     Sleep(1000);
                     chk_spec->Enabled=true;
                 }
             }
    private: System::Void chk_monitor_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
                 if (chk_monitor->Checked) {
                     monitor=gcnew monitordlg();
                     monitor->Show();
                 } else {
                     monitor->Close();
                     chk_monitor->Enabled=false;
                     Sleep(1000);
                     chk_monitor->Enabled=true;
                 }
             }
    private: System::Void chk_input2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
                 if (chk_input2->Checked) {
                     tb_input2->Enabled=true;
                     b_input2->Enabled=true;
                     enable_FE2();
                 }else{
                     tb_input2->Enabled=false;
                     b_input2->Enabled=false;
                     disable_FE2();
                 }
             }
    private: Void disable_FE2() {
                 gp_FE2->Enabled=false;

                 rb_G_FE1->Checked=true;
                 rb_R_FE1->Checked=true;
                 rb_E_FE1->Checked=true;
                 rb_C_FE1->Checked=true;
                 rb_Q_FE1->Checked=true;
                 rb_S_FE1->Checked=true;
                 rb_spec1->Enabled=true;

                 rb_G_FE2->Enabled=false;
                 rb_R_FE2->Enabled=false;
                 rb_E_FE2->Enabled=false;
                 rb_C_FE2->Enabled=false;
                 rb_Q_FE2->Enabled=false;
                 rb_S_FE2->Enabled=false;
                 rb_spec2->Enabled=false;
             }
    private: Void enable_FE2() {
                 gp_FE2->Enabled=true;

                 rb_G_FE2->Enabled=true;
                 rb_R_FE2->Enabled=true;
                 rb_E_FE2->Enabled=true;
                 rb_C_FE2->Enabled=true;
                 rb_Q_FE2->Enabled=true;
                 rb_S_FE2->Enabled=true;
                 rb_spec2->Enabled=true;
             }
    private: Void cb_freq_stereo() {
                 cb_cf1->Items->Clear();
                 cb_cf2->Items->Clear();

                 cb_cf1->Items->Add("1575.420 MHz(L1)");
                 cb_cf1->Items->Add("1561.098 MHz(B1)");
                 cb_cf1->Items->Add("1602.000 MHz(G1)");

                 cb_cf2->Items->Add("1575.420 MHz(L1)");
                 cb_cf2->Items->Add("1561.098 MHz(B1)");
                 cb_cf2->Items->Add("1602.000 MHz(G1)");
                 cb_cf2->Items->Add("1227.600 MHz(L2)");
                 cb_cf2->Items->Add("1176.450 MHz(L5)");
                 cb_cf2->Items->Add("1278.750 MHz(L6)");
                 cb_cf2->Items->Add("1246.000 MHz(G2)");
                 cb_cf2->Items->Add("1207.140 MHz(B2)");

                 cb_cf1->SelectedIndex=0;
                 cb_cf2->SelectedIndex=0;
             }
    private: Void cb_freq_L1() {
                 cb_cf1->Items->Clear();
                 cb_cf2->Items->Clear();

                 cb_cf1->Items->Add("1575.420 MHz(L1)");

                 cb_cf1->SelectedIndex=0;
             }
    private: Void cb_freq_all() {
                 cb_cf1->Items->Clear();
                 cb_cf2->Items->Clear();

                 cb_cf1->Items->Add("1575.420 MHz(L1)");
                 cb_cf1->Items->Add("1561.098 MHz(B1)");
                 cb_cf1->Items->Add("1602.000 MHz(G1)");
                 cb_cf1->Items->Add("1227.600 MHz(L2)");
                 cb_cf1->Items->Add("1176.450 MHz(L5)");
                 cb_cf1->Items->Add("1278.750 MHz(L6)");
                 cb_cf1->Items->Add("1246.000 MHz(G2)");
                 cb_cf1->Items->Add("1207.140 MHz(B2)");

                 cb_cf2->Items->Add("1575.420 MHz(L1)");
                 cb_cf2->Items->Add("1561.098 MHz(B1)");
                 cb_cf2->Items->Add("1602.000 MHz(G1)");
                 cb_cf2->Items->Add("1227.600 MHz(L2)");
                 cb_cf2->Items->Add("1176.450 MHz(L5)");
                 cb_cf2->Items->Add("1278.750 MHz(L6)");
                 cb_cf2->Items->Add("1246.000 MHz(G2)");
                 cb_cf2->Items->Add("1207.140 MHz(B2)");

                 cb_cf1->SelectedIndex=0;
                 cb_cf2->SelectedIndex=0;
             }
    private: Void ppm_enable() {
                 lb_clk1->Enabled=true;
                 lb_clk2->Enabled=true;
                 tb_clk->Enabled=true;
             }
    private: Void ppm_disable() {
                 lb_clk1->Enabled=false;
                 lb_clk2->Enabled=false;
                 tb_clk->Enabled=false;
             }
    private: System::Void chk_TYPE_LEX_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
                 if (chk_TYPE_LEX->Checked) {
                     chk_TYPE_SAIF->Checked=false;
                     chk_TYPE_L1CAQZS->Checked=false;
                     chk_Q01->Checked=true;
                     rb_Q_FE2->Checked=true;
                     chk_TYPE_SAIF->Enabled=false;
                     chk_TYPE_L1CAQZS->Enabled=false;
                 } else {
                     rb_Q_FE1->Checked=true;
                     chk_TYPE_SAIF->Enabled=true;
                     chk_TYPE_L1CAQZS->Enabled=true;
                 }
             }
    private: System::Void chk_TYPE_SAIF_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
                 if (chk_TYPE_SAIF->Checked) {
                     chk_TYPE_LEX->Checked=false;
                     chk_TYPE_L1CAQZS->Checked=false;
                     chk_Q01->Checked=true;
                     rb_Q_FE1->Checked=true;
                     chk_TYPE_LEX->Enabled=false;
                     chk_TYPE_L1CAQZS->Enabled=false;
                 } else {
                     rb_Q_FE1->Checked=true;
                     chk_TYPE_LEX->Enabled=true;
                     chk_TYPE_L1CAQZS->Enabled=true;
                 }
             }
    private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
                 trkprm=gcnew trkprmdlg();

                 trkprm->tb_corrn->Text=config->tb_corrn;
                 trkprm->tb_corrd->Text=config->tb_corrd;
                 trkprm->tb_corrp->Text=config->tb_corrp;
                 trkprm->tb_dll1->Text=config->tb_dll1;
                 trkprm->tb_pll1->Text=config->tb_pll1;
                 trkprm->tb_fll1->Text=config->tb_fll1;
                 trkprm->tb_dll2->Text=config->tb_dll2;
                 trkprm->tb_pll2->Text=config->tb_pll2;
                 trkprm->tb_fll2->Text=config->tb_fll2;

                 trkprm->Show();
                 trkprm->Owner = this;
             }
    private: System::Void cb_cf1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

                 switch (cmb_input->SelectedIndex) {
                 case 0: /* STEREO */
                 case 5: /* FILE STEREO*/
                     switch (cb_cf1->SelectedIndex) {
                     case 0: /* L1 */
                         tb_f1if->Text="4.0";
                         break;
                     case 1:/* B1 */
                         tb_f1if->Text="6.5";
                         break;
                     case 2:/* G1 */
                         tb_f1if->Text="4.62";
                         break;
                     }
                     break;
                 }
             }
    private: System::Void b_radar_Click(System::Object^  sender, System::EventArgs^  e) {
                 String ^ url = "http://www.taroz.net/GNSS-Radar_sky.html"+
                     "?lat="+tb_lat->Text+"&lon="+tb_lon->Text;

                 radar=gcnew radardlg();

                 radar->wb_radar->Navigate(url);
                 radar->wb_radar->Refresh();
                 radar->Show();
             }

    };
}
