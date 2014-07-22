using namespace System;
public ref class SDR
{
public: void start(Object^ obj);
public: void stop(Object^ obj);
public: void startspectrum(Object^ obj);
public: void stopspectrum(Object^ obj);
public: void settrkprm(Object^ obj1,Object^ obj2);
};

public ref class CONFIG
{
public:
    String^ tb_input1;
    String^ tb_input2;
    int cmb_input;
    String^ tb_f1sf;
    String^ tb_f2sf;
    String^ tb_f1if;
    String^ tb_f2if;
    bool rb_f1IQ;
    bool rb_f2IQ;
    int cb_cf1;
    int cb_cf2;
    String^ tb_clk;

    String^ tb_corrn;
    String^ tb_corrd;
    String^ tb_corrp;
    String^ tb_dll1;
    String^ tb_pll1;
    String^ tb_fll1;
    String^ tb_dll2;
    String^ tb_pll2;
    String^ tb_fll2;

    /* GPS */
    bool rb_G_FE1;
    bool rb_G_FE2;
    bool chk_TYPE_L1CA;
    bool chk_G01;
    bool chk_G02;
    bool chk_G03;
    bool chk_G04;
    bool chk_G05;
    bool chk_G06;
    bool chk_G07;
    bool chk_G08;
    bool chk_G09;
    bool chk_G10;
    bool chk_G11;
    bool chk_G12;
    bool chk_G13;
    bool chk_G14;
    bool chk_G15;
    bool chk_G16;
    bool chk_G17;
    bool chk_G18;
    bool chk_G19;
    bool chk_G20;
    bool chk_G21;
    bool chk_G22;
    bool chk_G23;
    bool chk_G24;
    bool chk_G25;
    bool chk_G26;
    bool chk_G27;
    bool chk_G28;
    bool chk_G29;
    bool chk_G30;
    bool chk_G31;
    bool chk_G32;

    /* GLONASS */
    bool rb_R_FE1;
    bool rb_R_FE2;
    bool chk_TYPE_G1;
    bool chk_R_7;
    bool chk_R_6;
    bool chk_R_5;
    bool chk_R_4;
    bool chk_R_3;
    bool chk_R_2;
    bool chk_R_1;
    bool chk_R0;
    bool chk_R1;
    bool chk_R2;
    bool chk_R3;
    bool chk_R4;
    bool chk_R5;
    bool chk_R6;

    /* Galileo */
    bool rb_E_FE1;
    bool rb_E_FE2;
    bool chk_TYPE_E1B;
    bool chk_E11;
    bool chk_E12;
    bool chk_E19;
    bool chk_E20;

    /* BeiDou */
    bool rb_C_FE1;
    bool rb_C_FE2;
    bool chk_TYPE_B1I;
    bool chk_C01;
    bool chk_C02;
    bool chk_C03;
    bool chk_C04;
    bool chk_C05;
    bool chk_C06;
    bool chk_C07;
    bool chk_C08;
    bool chk_C09;
    bool chk_C10;
    bool chk_C11;
    bool chk_C12;
    bool chk_C13;
    bool chk_C14;

    /* QZSS */
    bool rb_Q_FE1;
    bool rb_Q_FE2;
    bool chk_TYPE_L1CAQZS;
    bool chk_TYPE_SAIF;
    bool chk_TYPE_LEX;
    bool chk_Q01;

    /* SBAS */
    bool rb_S_FE1;
    bool rb_S_FE2;
    bool chk_TYPE_SBASL1;
    bool chk_S120;
    bool chk_S121;
    bool chk_S122;
    bool chk_S123;
    bool chk_S124;
    bool chk_S125;
    bool chk_S126;
    bool chk_S127;
    bool chk_S128;
    bool chk_S129;
    bool chk_S130;
    bool chk_S131;
    bool chk_S132;
    bool chk_S133;
    bool chk_S134;
    bool chk_S135;
    bool chk_S136;
    bool chk_S137;
    bool chk_S138;

    bool chk_plotacq;
    bool chk_plottrk;
    bool chk_initfe;

    int cmb_outint;
    bool chk_rinex;
    bool chk_rtcm;
    bool chk_lex;
    bool chk_saif;
    String^ tb_rinex_dir;
    String^ tb_rtcm_port;
    String^ tb_lex_port;
    String^ tb_saif_port;

    bool rb_spec1;
    bool rb_spec2;

    String^ tb_lat;
    String^ tb_lon;
};
