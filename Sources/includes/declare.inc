' **************************************************************
' FlyTools - Version 1.6.1
' Code by Benoit (BSM3D) Saint-Moulin
' Last tested: 08/01/2025 on Windows 10 x64 (2025)
' Language: RapidQ (Basic) Framework
' Initial Release: 04/01/2000
' This is a 25th Anniversary re-issue release for educational and learning purposes
'
' This code has no pretension - it was created in the 2000s
' and is therefore representative of that era. It is a simple program  
' written in Basic language, re-released freely for those who wish
' to easily understand the creation of a complete Windows application,
' or learn some Basic (Here RapidQ) coding mechanisms.
' **************************************************************
'
' LICENSE:
' This code is released under the MIT License
' Copyright (c) 2000 Benoit (BSM3D) Saint-Moulin
'
' Permission is hereby granted, free of charge, to any person obtaining a copy
' of this software and associated documentation files (the "Software"), to deal
' in the Software without restriction, including without limitation the rights
' to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
' copies of the Software, and to permit persons to whom the Software is
' furnished to do so, subject to the following conditions:
'
' The above copyright notice and this permission notice shall be included in all
' copies or substantial portions of the Software.
'
' NOTE: 
' This is a legacy codebase maintained for educational purposes.
' While still functional on modern Windows systems, it uses the RapidQ framework
' which is no longer actively maintained.
' ****************************************************************************************************************************************************************

' API call for opening an internet link
DECLARE SUB ShellExe LIB "SHELL32" ALIAS "ShellExecuteA" (HWnd AS LONG, lpOperation AS STRING, lpFile AS STRING, lpParameters AS STRING, lpDirectory AS STRING, nShowCmd AS LONG)

' Variables for preferences
    DIM SplashBMP AS QBITMAP
    SplashBMP.BMPHandle = start
    DIM shint AS BYTE
    DIM mode_hint AS STRING
    DIM ndec AS INTEGER
    DIM aero_edt AS STRING
    DIM machaine AS STRING
    DIM rem_ext AS INTEGER
    DIM boot AS INTEGER

' Variables for system files of the database
    DIM opf$ AS STRING
    DIM sli AS INTEGER, sli_log AS INTEGER
    DIM file AS qfilestream, file_log AS qfilestream
    DIM opendialog_log AS QOpenDialog
    DIM opendialog AS QOpenDialog
    DIM i AS INTEGER
    DIM ii AS INTEGER
    DIM mli AS INTEGER
    DIM ix AS INTEGER
    sli=1 : sli_log = 1
    DECLARE SUB b_search
    DECLARE SUB b_main
    DECLARE SUB b_search_log
    DECLARE SUB b_main_log

' Variables for conversions
    DIM basex AS INTEGER
    DIM base AS STRING
    DIM units AS DOUBLE, somme AS DOUBLE
    DIM th AS DOUBLE, tc AS DOUBLE, tas AS DOUBLE, wv AS DOUBLE, wd AS DOUBLE, mh AS DOUBLE, var AS DOUBLE, burn AS DOUBLE, ete AS DOUBLE, eta AS DOUBLE, etd AS DOUBLE, gs AS DOUBLE, dist AS DOUBLE, fuel AS DOUBLE

' Interface
    DECLARE SUB help
    DECLARE SUB loader
    DECLARE SUB clean_interface
    DECLARE SUB clear_field
    DECLARE SUB clear_wb
    DECLARE SUB mlogoclick
    DECLARE SUB paypalclick
    DECLARE SUB reset_prefs
    DECLARE SUB main_prefs
    DECLARE SUB prefs_save
    DECLARE SUB about
    DECLARE SUB register
    DECLARE SUB calc
    DECLARE SUB chose_ndec
    DECLARE SUB exit_about
    DECLARE SUB exit_flytools
    DECLARE SUB exit_license
    DECLARE SUB webzenair
    DECLARE SUB weblightplane

    DECLARE SUB web_nav3000
    DECLARE SUB web_aeroplanner
    DECLARE SUB web_icao

    DECLARE SUB web_meteofr
    DECLARE SUB web_baseops
    DECLARE SUB web_ais
    DECLARE SUB web_phd
    DECLARE SUB web_olivia
    DECLARE SUB web_meteo_lightplane
    DECLARE SUB web_occasions

    DECLARE SUB web_mapquest
    DECLARE SUB web_sia

    DECLARE SUB web_belgo
    DECLARE SUB web_safety
    DECLARE SUB web_europe

    DECLARE SUB exit_prefs
    DECLARE SUB switch_hint

' Database 
' Quick open Database
    DECLARE SUB open_world_icao
    DECLARE SUB open_online_icao

' Air field DB
    DECLARE SUB air_db
    DECLARE SUB TabChange
    DECLARE SUB air_close
    DECLARE SUB DisableFunc
    DECLARE SUB EnableFunc
    DECLARE SUB SaveClick
    DECLARE SUB SaveAsClick
    DECLARE SUB Save
    DECLARE SUB OpenClick
    DECLARE SUB load
    DECLARE SUB add_entry
    DECLARE SUB del_entry
    DECLARE SUB SearchRoutine(key AS BYTE)
    DECLARE SUB Sselectall

' Pilot logBook
    DECLARE SUB log_db
    DECLARE SUB TabChange_log
    DECLARE SUB log_close
    DECLARE SUB DisableFunc_log
    DECLARE SUB EnableFunc_log
    DECLARE SUB SaveClick_log
    DECLARE SUB SaveAsClick_log
    DECLARE SUB Save_log
    DECLARE SUB OpenClick_log
    DECLARE SUB load_log
    DECLARE SUB add_entry_log
    DECLARE SUB del_entry_log
    DECLARE SUB Searchlog(key AS BYTE)
    DECLARE SUB Sselectall_log

    DECLARE SUB wb_calc
    DECLARE SUB wb_clear_interface
    DECLARE SUB wb_close
    DECLARE SUB wb_print
    DECLARE SUB air_id_item
    DECLARE SUB ch601_tri
    DECLARE SUB ch601_tri_calc

' General Conversion
    DECLARE SUB main_angles
    DECLARE SUB conv_item_angles
    DECLARE SUB conv_degre
    DECLARE SUB conv_radian

    DECLARE SUB main_speeds
    DECLARE SUB conv_item_speeds
    DECLARE SUB conv_ms
    DECLARE SUB conv_kmh
    DECLARE SUB conv_mach
    DECLARE SUB conv_knoth
    DECLARE SUB conv_mileh
    DECLARE SUB conv_pied

    DECLARE SUB main_distances
    DECLARE SUB conv_item_distances
    DECLARE SUB conv_metre
    DECLARE SUB conv_kilometre
    DECLARE SUB conv_foot
    DECLARE SUB conv_inch
    DECLARE SUB conv_smile
    DECLARE SUB conv_nmile
    DECLARE SUB conv_yards

    DECLARE SUB main_poids
    DECLARE SUB conv_item_poids
    DECLARE SUB conv_kg
    DECLARE SUB conv_pound

    DECLARE SUB main_liquide
    DECLARE SUB conv_item_liquide
    DECLARE SUB conv_litre
    DECLARE SUB conv_gallonus
    DECLARE SUB conv_gallonuk

    DECLARE SUB main_temp
    DECLARE SUB conv_item_temp
    DECLARE SUB conv_degrec
    DECLARE SUB conv_degref
    DECLARE SUB conv_kelvin

    DECLARE SUB main_charge
    DECLARE SUB conv_item_charge
    DECLARE SUB conv_watt
    DECLARE SUB conv_kwatt
    DECLARE SUB conv_horse
    DECLARE SUB conv_btu

    DECLARE SUB main_pressure
    DECLARE SUB conv_item_pressure
    DECLARE SUB conv_atm
    DECLARE SUB conv_bar
    DECLARE SUB conv_millibar
    DECLARE SUB conv_psi

    DECLARE SUB base_conv
    DECLARE SUB conv_item_base
    DECLARE SUB conv_dec
    DECLARE SUB conv_hexa
    DECLARE SUB conv_bin
    DECLARE SUB conv_oct

' Money converter
    DIM t_fb AS DOUBLE
    DIM t_ff AS DOUBLE
    DIM t_dm AS DOUBLE
    DIM t_euro AS DOUBLE
    DIM t_lire AS DOUBLE
    DIM t_livre AS DOUBLE
    DIM t_us AS DOUBLE
    DIM t_ca AS DOUBLE
    DIM t_cz AS DOUBLE

    DECLARE SUB main_conv_change
    DECLARE SUB conv_item
    DECLARE SUB conv_fb
    DECLARE SUB conv_ff
    DECLARE SUB conv_dm
    DECLARE SUB conv_euro
    DECLARE SUB conv_lire
    DECLARE SUB conv_livre
    DECLARE SUB conv_us
    DECLARE SUB conv_ca
    DECLARE SUB conv_cz
    DECLARE SUB edit_taux

' General Aviation helper
    DECLARE SUB Th_calc
    DECLARE SUB th_Sub_calc
    DECLARE SUB mh_calc
    DECLARE SUB mh_sub_calc

    DECLARE SUB main_predic_gel
    DECLARE SUB sub_predic_gel
    DECLARE SUB main_wind
    DECLARE SUB sub_wind
    DECLARE SUB leg_calc
    DECLARE SUB leg_sub_calc
    DECLARE SUB gs_calc
    DECLARE SUB gs_sub_calc
' End of file (don't modify this file !)