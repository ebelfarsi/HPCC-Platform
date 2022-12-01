IMPORT PARQUET;

Set_date_sk:=[-2];
Set_date_dt:=['          '];
Set_date_sd:=['-2         '];
Set_date_ld:=['NA                              '];
Set_yr_num:=[0];
Set_half_yr_num:=[0];
Set_half_yr_nam_sd:=['         '];
Set_half_yr_nam_ld:=['                                '];
Set_qtr_num:=[0];
Set_qtr_nam_sd:=['  '];
Set_qtr_nam_ld:=['         '];
Set_qtr_start_dt:=[0];
Set_qtr_end_dt:=[0];
Set_yr_qtr_num:=[0];
Set_yr_qtr_nam_sd:=['          '];
Set_yr_qtr_nam_ld:=['                  '];
Set_mth_num:=[0];
Set_mth_nam_sd:=['     '];
Set_mth_nam_ld:=['         '];
Set_mth_end_dt:=[0];
Set_days_in_mth_num:=[0];
Set_yr_mth_num:=[0];
Set_yr_mth_nam_sd:=['          '];
Set_yr_mth_nam_ld:=['                        '];
Set_days_in_yr_num:=[0];
Set_day_of_mth_num:=[0];
Set_day_of_wk_num:=[0];
Set_day_of_wk_nam_sd:=['     '];
Set_day_of_wk_nam_ld:=['          '];
Set_day_of_yr_num:=[0];
Set_wk_of_yr_num:=[0];
Set_wk_start_dt:=[0];
Set_wk_end_dt:=[0];
Set_wkday_fl:=[' '];
Set_holiday_fl:=['N'];
Set_major_event_fl:=[' '];
Set_first_seen_dt:=[20151105];
Set_last_seen_dt:=[20151105];
Set_iso_wk_start_dt:=['          '];
Set_iso_wk_end_dt:=['          '];
Set_iso_wk_num_of_year:=[0];
Set_ins_wk_num_of_month:=[5];
Set_ins_like_day:=[0];
Set_ins_rev_day:=['0'];
Set_bsv_rev_day:=['0'];
Set_bsv_fcst_day_factor:=['0'];
Set_iso_yr_num:=[0];
Set_ln_holiday_fl:=['N'];
Set_work_hours:=[0];
Set_qtr_start_date:=['          '];
Set_qtr_end_date:=['          '];
Set_mth_start_date:=['          '];
Set_mth_end_date:=['          '];
Set_year_start_date:=['          '];
Set_year_end_date:=['          '];
Set_iso_year_week_num:=[0];
Set_ins_lag_day:=[0];
Set_ins_like_date:=['          '];
Set_hc_rev_day:=['0'];
Row_1:=['-2','          ','-2         ','NA                              ','0','0','         ','                                ','0','  ','         ','0','0','0','          ','                  ','0','     ','         ','0','0','0','          ','                        ','0','0','0','     ','          ','0','0','0','0',' ','N',' ','20151105','20151105','          ','          ','0','5','0','0','0','0','0','N','0','          ','          ','          ','          ','          ','          ','0','0','          ','0'];
empty_record :=
  record
    integer4 date_sk;
    string10 date_dt;
    string11 date_sd;
    string32 date_ld;
    unsigned2 yr_num;
    unsigned1 half_yr_num;
    string9 half_yr_nam_sd;
    string32 half_yr_nam_ld;
    unsigned1 qtr_num;
    string2 qtr_nam_sd;
    string9 qtr_nam_ld;
    unsigned4 qtr_start_dt;
    unsigned4 qtr_end_dt;
    unsigned3 yr_qtr_num;
    string10 yr_qtr_nam_sd;
    string18 yr_qtr_nam_ld;
    unsigned1 mth_num;
    string5 mth_nam_sd;
    string9 mth_nam_ld;
    unsigned4 mth_end_dt;
    unsigned1 days_in_mth_num;
    unsigned3 yr_mth_num;
    string10 yr_mth_nam_sd;
    string24 yr_mth_nam_ld;
    unsigned2 days_in_yr_num;
    unsigned1 day_of_mth_num;
    unsigned1 day_of_wk_num;
    string5 day_of_wk_nam_sd;
    string10 day_of_wk_nam_ld;
    unsigned2 day_of_yr_num;
    unsigned1 wk_of_yr_num;
    unsigned4 wk_start_dt;
    unsigned4 wk_end_dt;
    string1 wkday_fl;
    string1 holiday_fl;
    string1 major_event_fl;
    unsigned4 first_seen_dt;
    unsigned4 last_seen_dt;
    string10 iso_wk_start_dt;
    string10 iso_wk_end_dt;
    integer8 iso_wk_num_of_year;
    integer8 ins_wk_num_of_month;
    integer8 ins_like_day;
    decimal3_2 ins_rev_day;
    decimal3_2 bsv_rev_day;
    decimal15_3 bsv_fcst_day_factor;
    integer4 iso_yr_num;
    string1 ln_holiday_fl;
    integer2 work_hours;
    string10 qtr_start_date;
    string10 qtr_end_date;
    string10 mth_start_date;
    string10 mth_end_date;
    string10 year_start_date;
    string10 year_end_date;
    integer8 iso_year_week_num;
    integer8 ins_lag_day;
    string10 ins_like_date;
    decimal3_2 hc_rev_day;
    UNICODE null_data;
  end;
empty_dataset := dataset([{-2, '          ', '-2         ', 'NA                              ', 0, 0, '         ', '                                ', 0, '  ', '         ', 0, 0, 0, '          ', '                  ', 0, '     ', '         ', 0, 0, 0, '          ', '                        ', 0, 0, 0, '     ', '          ', 0, 0, 0, 0, ' ', 'N', ' ', 20151105, 20151105, '          ', '          ', 0, 5, 0, '0', '0', '0', 0, 'N', 0, '          ', '          ', '          ', '          ', '          ', '          ', 0, 0, '          ', '0', '\123\000\000\000\123'}], empty_record);

Write(empty_dataset, '/datadrive/dev/test_data/empty_parquet.parquet');

empty_data_in := Read(empty_record, '/datadrive/dev/test_data/empty_parquet.parquet');
OUTPUT(empty_data_in);