$TYPECHECK ON
'******************************************************************************
'FlyTools - Version 1.6.1
'Code by Benoit (BSM3D) Saint-Moulin
'Last tested: 08/01/2025 on Windows 10 x64 (2025)
'Language: RapidQ (Basic) Framework
'Initial Release: 04/01/2000
'This is a 25th Anniversary re-issue release for educational and learning purposes
'
'This code has no pretension - it was CREATEd in the 2000s
'and is therefore representative of that era. It is a simple program
'written in Basic language, re-released freely for those who wish
'to easily understand the creation of a complete Windows application,
'or learn some Basic (Here RapidQ) coding mechanisms.
'******************************************************************************
'
'FEATURES:
'- Aviation computations and tools
'- Unit conversions (currency, speed, temperature, etc.)
'- Custom ICAO database management
'- Custom Flight logbook functionality
'- Weight and balance calculations
'- Online aviation resources access
'- Configurable preferences system
'
'LICENSE:
'This code is released under the MIT License
'Copyright (c) 2000 Benoit (BSM3D) Saint-Moulin
'
'Permission is hereby granted, free of charge, to any person obtaining a copy
'of this software and associated documentation files (the "Software"), to deal
'in the Software without restriction, including without limitation the rights
'to use, copy, modIFy, merge, publish, distribute, SUBlicense, and/or sell
'copies of the Software, and to permit persons to whom the Software is
'furnished to do so, SUBject to the following conditions:
'
'The above copyright notice and this permission notice shall be included in all
'copies or SUBstantial portions of the Software.
'
'NOTE:
'This is a legacy codebase maintained for educational purposes.
'While still functional on modern Windows systems, it uses the RapidQ framework
'which is no longer actively maintained.
'******************************************************************************

'RapidQ compiler parameters
'For Compiling: RC.exe Flytools.bas
$OPTIMIZE ON
$APPTYPE gui
$TYPECHECK on

'Resources
$RESOURCE start AS "c:\rapidq\projets\flytools\bitmaps\start.bmp"
$RESOURCE logo  AS "c:\rapidq\projets\flytools\bitmaps\flytoolslogo.bmp"
$RESOURCE credit AS "c:\rapidq\projets\flytools\bitmaps\flytoolsabout.bmp"
$RESOURCE toolbar AS "c:\rapidq\projets\flytools\bitmaps\toolsbar2.bmp"
$RESOURCE BEval AS "c:\rapidq\projets\flytools\bitmaps\eval.bmp"
$RESOURCE Bdel  AS "c:\rapidq\projets\flytools\bitmaps\del.bmp"
$RESOURCE Bcalc AS "c:\rapidq\projets\flytools\bitmaps\calc.bmp"
$RESOURCE Bprint AS "c:\rapidq\projets\flytools\bitmaps\print.bmp"
$RESOURCE Bopen AS "c:\rapidq\projets\flytools\bitmaps\open.bmp"
$RESOURCE Bsave AS "c:\rapidq\projets\flytools\bitmaps\save.bmp"
$RESOURCE Bsearch AS "c:\rapidq\projets\flytools\bitmaps\search.bmp"
$RESOURCE Badd  AS "c:\rapidq\projets\flytools\bitmaps\add.bmp"
$RESOURCE Brem  AS "c:\rapidq\projets\flytools\bitmaps\rem.bmp"
$RESOURCE Bdb  AS "c:\rapidq\projets\flytools\bitmaps\exit.bmp"
$RESOURCE Ball  AS "c:\rapidq\projets\flytools\bitmaps\all.bmp"
$RESOURCE Bexit AS "c:\rapidq\projets\flytools\bitmaps\exit.bmp"
$RESOURCE Bhelp AS "c:\rapidq\projets\flytools\bitmaps\help.bmp"
$RESOURCE Bok  AS "c:\rapidq\projets\flytools\bitmaps\ok.bmp"
$RESOURCE Berase AS "c:\rapidq\projets\flytools\bitmaps\erase.bmp"
$RESOURCE ipt_back AS "c:\rapidq\projets\flytools\bitmaps\back_input.bmp"
$RESOURCE wb_back AS "c:\rapidq\projets\flytools\bitmaps\wb_back.bmp"
$RESOURCE ico  AS "c:\rapidq\projets\flytools\icons\ico.ico"

'Includes
$include     "c:\rapidq\projets\flytools\includes\constante.inc"
$include     "c:\rapidq\projets\flytools\includes\declare.inc"
$include     "c:\rapidq\projets\flytools\includes\system.inc"
$include     "c:\rapidq\projets\flytools\includes\prefs.inc"

'Database Launching
$include    "c:\rapidq\projets\flytools\includes\db_airfield.inc"
$include    "c:\rapidq\projets\flytools\includes\db_log.inc"
$include    "c:\rapidq\projets\flytools\includes\files_log.inc"
$include    "c:\rapidq\projets\flytools\includes\files_airfield.inc"
$include    "c:\rapidq\projets\flytools\includes\wb.inc"

'Registry information
DIM regver_key AS STRING  :  regver_key = "1.6.1"
DIM regdat_key AS STRING  :  regdat_key = "06-04-2006"

'Interface creation

'Boot Loader and Debug panel
CREATE boot_form AS QFORM
    BorderStyle = 0
    Center
    Height = 210
    Width = 272
    Color = &h885533
    CREATE boot_pic AS QIMAGE  :  Height = 196  :  Width = 271  :  BMPHandle = start  :  END CREATE
    CREATE boot_loader AS QLABEL  :  Color = &h885533  :  Top = 196  :  Left = 1  :  Width = 269  :  Font = font5  :  END CREATE
    Show
    Repaint
END CREATE

CREATE mainform AS QFORM
    Caption = "FlyTools - 1.6.1 (06-04-2006) : " + aero_edt
    BorderStyle = 1
    DelBorderIcons = 2
    Center
    Height = 480
    Width = 480
    IcoHandle = ico
    Visible = 0

    'Popup menu and shortcuts
    CREATE pop_menu AS QPOPUPMENU
        CREATE Pop_help AS QMENUITEM  : Caption = "Help"    :  ShortCut = "F1"   :  OnClick = help    : END CREATE
        CREATE win_calc AS QMENUITEM  : caption = "Calc"    :  ShortCut = "F2"   :  OnClick = calc    : END CREATE
        CREATE pop_prefs AS QMENUITEM  : Caption = "Prefs"    :  ShortCut = "F3"   :  OnClick = main_prefs   : END CREATE
        CREATE main_sep0 AS QMENUITEM  : caption = "-"    :  END CREATE
        CREATE Pop_quit AS QMENUITEM  : Caption = "Quit FlyTools !"  :  ShortCut = "ctrl+Q"  :  OnClick = exit_flytools  : END CREATE
    END CREATE
    PopupMenu = pop_menu

    'Tooltips and status
    CREATE panelinfo AS QSTATUSBAR
        SizeGrip = 0
        AddPanels "Decimal Fix : " + STR$(ndec) , "Tools tips : " + mode_hint , "Date: " + mdy$ , "Local Time : " + "Check..."  'times (hrs%, min%)
        Hint = "Status display panel"  :  ShowHint = STR$(shint)
        Panel(0).Width = 110
        Panel(1).Width = 110
        Panel(2).Width = 136
        Panel(3).Width = 124
        Panel(0).Alignment = 2
        Panel(1).Alignment = 2
        Panel(2).Alignment = 2
        Panel(3).Alignment = 2
    END CREATE

    'Input boxes creation
    CREATE Input_panel AS QPANEL
        BevelOuter = 1
        Top = 35
        Left = 5
        Height = 375
        Width = 350
        CREATE input_back AS QIMAGE  :  BMPHandle = ipt_back  :  Left = 1  :  Top = 1  :  Height = 373  :  Width = 348  :  END CREATE

        'Introduction text and welcome
        CREATE intro_text0 AS QLABEL  :  Transparent = 1  :  Top = 5  :  Left = 5  :  Visible = 1  :  Font = font_intro  :
        Caption = "Welcome to FlyTools 1.6.1 !"  :  END CREATE

        CREATE intro_text1 AS QLABEL  :  Transparent = 1  :  Top = 35  :  Left = 5  :  Visible = 1  :  Font = font_intro  :
        Caption = "FlyTools by Benoit (BSM3D) Saint-Moulin"  :  END CREATE

        CREATE intro_text2 AS QLABEL  :  Transparent = 1  :  Top = 55  :  Left = 5  :  Visible = 1  :  Font = font_intro  :
        Caption = "This is a free software for light aircraft pilots"  :  END CREATE

        CREATE intro_text3 AS QLABEL  :  Transparent = 1  :  Top = 85  :  Left = 5  :  Visible = 1  :  Font = font5  :
        Caption = "Please read documentation and tutorials for help."  :  END CREATE

        CREATE intro_text4 AS QLABEL  :  Transparent = 1  :  Top = 105  :  Left = 5  :  Visible = 1  :  Font = F_rouge  :
        Caption = "WARNING : Use it at your own risk - no warranty !!"  :  END CREATE

        CREATE label AS QLABEL  :  Transparent = 1  :  Top = 5  :  Left = 5  :  Visible = 0  :  Font = font5  :  Hint = "Display operations"  :  ShowHint = shint  :  END CREATE
        CREATE d1 AS QEDIT  :  Top = 40   :  Left = 70  :  Width = 100  :  Visible = 0  :  END CREATE
        CREATE d4 AS QEDIT  :  Top = 40   :  Left = 240  :  Width = 100  :  Visible = 0  :  END CREATE
        CREATE d2 AS QEDIT  :  Top = 80   :  Left = 70  :  Width = 100  :  Visible = 0  :  END CREATE
        CREATE d5 AS QEDIT  :  Top = 80   :  Left = 240  :  Width = 100  :  Visible = 0  :  END CREATE
        CREATE d3 AS QEDIT  :  Top = 120  :  Left = 70  :  Width = 100  :  Visible = 0  :  END CREATE
        CREATE d6 AS QEDIT  :  Top = 120  :  Left = 240  :  Width = 100  :  Visible = 0  :  END CREATE
        CREATE d7 AS QEDIT  :  Top = 160  :  Left = 70  :  Width = 100  :  Visible = 0  :  END CREATE
        CREATE d8 AS QEDIT  :  Top = 160  :  Left = 240  :  Width = 100  :  Visible = 0  :  END CREATE

        CREATE dlab1 AS QLABEL  :  Transparent = 1  : top = 40  :  Left = 5  :  Visible = 0  :  Font = font5  :  END CREATE
        CREATE dlab4 AS QLABEL  :  Transparent = 1  : top = 40  :  Left = 175  :  Visible = 0  :  Font = font5  :  END CREATE
        CREATE dlab2 AS QLABEL  :  Transparent = 1  : top = 80  :  Left = 5  :  Visible = 0  :  Font = font5  :  END CREATE
        CREATE dlab5 AS QLABEL  :  Transparent = 1  : top = 80  :  Left = 175  :  Visible = 0  :  Font = font5  :  END CREATE
        CREATE dlab3 AS QLABEL  :  Transparent = 1  : top = 120  :  Left = 5  :  Visible = 0  :  Font = font5  :  END CREATE
        CREATE dlab6 AS QLABEL  :  Transparent = 1  : top = 120  :  Left = 175  :  Visible = 0  :  Font = font5  :  END CREATE
        CREATE dlab7 AS QLABEL  :  Transparent = 1  : top = 160  :  Left = 5  :  Visible = 0  :  Font = font5  :  END CREATE
        CREATE dlab8 AS QLABEL  :  Transparent = 1  : top = 160  :  Left = 175  :  Visible = 0  :  Font = font5  :  END CREATE
        CREATE changes AS QLABEL  :  Transparent = 1  : top = 40  :  Left = 175  :  Visible = 0  :  Font = font5  :  END CREATE

        'ComboBox for conversions
        CREATE conv_devise AS QCOMBOBOX  :  Top = 40  :  Left = 240  :  Width = 100  :  Visible = 0  :  DropDownCount = 9
        AddItems "Belgian Franc" , "French Franc" , "German Mark" , "Euro" , "Italian Lira" , "British Pound" , "US Dollar" , "Canadian Dollar" , "Czech Koruna"  :  ItemIndex = 0  :  OnChange = conv_item  :  END CREATE

        CREATE conv_speeds AS QCOMBOBOX  :  Top = 40  :  Left = 240  :  Width = 90  :  Visible = 0
        AddItems "M/s" , "Km/h" , "Mach/h" , "Knot/h" , "Mile/h" , "feet/m"  :  ItemIndex = 0  :  OnChange = conv_item_speeds  :  END CREATE

        CREATE conv_charge AS QCOMBOBOX  :  Top = 40  :  Left = 240  :  Width = 90  :  Visible = 0
        AddItems "Watt" , "Kilowatt" , "Horsepower" , "BTU/m"  :  ItemIndex = 0  :  OnChange = conv_item_charge  :  END CREATE

        CREATE conv_pressure AS QCOMBOBOX  :  Top = 40  :  Left = 240  :  Width = 90  :  Visible = 0
        AddItems "ATM" , "BAR" , "Millibar" , "PSI"  :  ItemIndex = 0  :  OnChange = conv_item_pressure  :  END CREATE

        CREATE conv_poids AS QCOMBOBOX  :  Top = 40  :  Left = 240  :  Width = 90  :  Visible = 0
        AddItems "KG" , "Pound"  :  ItemIndex = 0  :  OnChange = conv_item_poids  :  END CREATE

        CREATE conv_liquide AS QCOMBOBOX  :  Top = 40  :  Left = 240  :  Width = 90  :  Visible = 0
        AddItems "Liter" , "Gallon US" , "Gallon UK"  :  ItemIndex = 0  :  OnChange = conv_item_liquide  :  END CREATE

        CREATE conv_temp AS QCOMBOBOX  :  Top = 40  :  Left = 240  :  Width = 90  :  Visible = 0
        AddItems "Celsius" , "Fahrenheit" , "Kelvin"  :  ItemIndex = 0  :  OnChange = conv_item_temp  :  END CREATE

        CREATE conv_distances AS QCOMBOBOX  :  Top = 40  :  Left = 240  :  Width = 90  :  Visible = 0
        AddItems "Meter" , "Kilometer" , "Foot" , "Inch" , "Statute Mile" , "Nautical Mile" , "Yard"  :  ItemIndex = 0  :  OnChange = conv_item_distances  :  END CREATE

        CREATE conv_angles AS QCOMBOBOX  :  Top = 40  :  Left = 240  :  Width = 90  :  Visible = 0
        AddItems "Degree" , "Radian"  :  ItemIndex = 0  :  OnChange = conv_item_angles  :  END CREATE

        CREATE conv_base AS QCOMBOBOX  :  Top = 40  :  Left = 240  :  Width = 90  :  Visible = 0
        AddItems "Decimal" , "Hexadecimal" , "Binary" , "Octal"  :  ItemIndex = 0  :  OnChange = conv_item_base  :  END CREATE
    END CREATE

    'Calculation functions panel
    CREATE toolbar_panel AS QPANEL
        BevelOuter = 1  :  Top = 0  :  Left = 5  :  Height = 31  :  Width = 350
        CREATE bar AS QIMAGE  :  Top = 1  :  Left = 1  :  Width = 348  :  Height = 29  :  BMPHandle = toolbar  :  END CREATE
        CREATE btn0 AS QCOOLBTN  :  Top = 3  :  Left = 10  :  Width = 27  :  Height = 26  :  Flat = 1  :  Layout = 1  :  BMPHandle = Bexit  :  Cursor = hand  :  OnClick = exit_flytools  :  Hint = "Quit FlyTools !"  :  ShowHint = shint  :  END CREATE
        CREATE btn1 AS QCOOLBTN  :  Top = 3  :  Left = 40  :  Width = 27  :  Height = 26  :  Flat = 1  :  Layout = 1  :  BMPHandle = BEval  :  Cursor = hand  :  Hint = "Solve / compute solutions."  :  ShowHint = shint  :  END CREATE
        CREATE btn2 AS QCOOLBTN  :  Top = 3  :  Left = 70  :  Width = 27  :  Height = 26  :  Flat = 1  :  Layout = 1  :  BMPHandle = Bdel  :  Cursor = hand  :  Hint = "Clear input datas."  :  ShowHint = shint  :  END CREATE
        CREATE btn3 AS QCOOLBTN  :  Top = 3  :  Left = 100  :  Width = 27  :  Height = 26  :  Flat = 1  :  Layout = 1  :  BMPHandle = Bcalc  :  Cursor = hand  :  OnClick = calc  :  Hint = "Calculator."  :  ShowHint = shint  :  END CREATE
        CREATE btn4 AS QCOOLBTN  :  Top = 3  :  Left = 270  :  Width = 27  :  Height = 26  :  Flat = 1  :  Layout = 1  :  BMPHandle = Bprint  :  Cursor = hand  :  Hint = "Print results."  :  ShowHint = shint  :  Enabled = 0  :  END CREATE
        CREATE btn5 AS QCOOLBTN  :  Top = 3  :  Left = 320  :  Width = 27  :  Height = 26  :  Flat = 1  :  Layout = 1  :  BMPHandle = Bhelp  :  Cursor = hand  :  OnClick = help  :  Hint = "Display Helps."  :  ShowHint = shint  :  END CREATE
    END CREATE

    'Solutions panel
    CREATE paneldroit AS QPANEL
        BevelOuter = 1  : top = 0  :  Left = 360  :  Height = 410  :  Width = 110  :  ShowHint = shint
        Color = &h33bbdd
        CREATE mlogo AS QIMAGE  :  Top = 3  :  Left = 5  :  Width = 101  :  Height = 41  :  Hint = "Visit FlyTools web site!"  :  Cursor = hand  :  AutoSize = TRUE  :  BMPHandle = logo  :  OnClick = mlogoclick  :  END CREATE
        CREATE sol1 AS QEDIT  :  Top = 60  :  Left = 5  :  Width = 95  :  Visible = 0  :  END CREATE
        CREATE sol2 AS QEDIT  :  Top = 100  :  Left = 5  :  Width = 95  :  Visible = 0  :  END CREATE
        CREATE sol3 AS QEDIT  :  Top = 140  :  Left = 5  :  Width = 95  :  Visible = 0  :  END CREATE
        CREATE sol4 AS QEDIT  :  Top = 180  :  Left = 5  :  Width = 95  :  Visible = 0  :  END CREATE
        CREATE sol5 AS QEDIT  :  Top = 220  :  Left = 5  :  Width = 95  :  Visible = 0  :  END CREATE
        CREATE sol6 AS QEDIT  :  Top = 260  :  Left = 5  :  Width = 95  :  Visible = 0  :  END CREATE
        CREATE sol7 AS QEDIT  :  Top = 300  :  Left = 5  :  Width = 95  :  Visible = 0  :  END CREATE
        CREATE sol8 AS QEDIT  :  Top = 340  :  Left = 5  :  Width = 95  :  Visible = 0  :  END CREATE
        CREATE sol9 AS QEDIT  :  Top = 380  :  Left = 5  :  Width = 95  :  Visible = 0  :  END CREATE
        CREATE dsol1 AS QLABEL  :  Transparent = 1  :  Top = 45  :  Left = 5  :  Visible = 0  :  Font = font4  : END CREATE
        CREATE dsol2 AS QLABEL  :  Transparent = 1  :  Top = 85  :  Left = 5  :  Visible = 0  :  Font = font4  : END CREATE
        CREATE dsol3 AS QLABEL  :  Transparent = 1  :  Top = 125  :  Left = 5  :  Visible = 0  :  Font = font4  : END CREATE
        CREATE dsol4 AS QLABEL  :  Transparent = 1  :  Top = 165  :  Left = 5  :  Visible = 0  :  Font = font4  : END CREATE
        CREATE dsol5 AS QLABEL  :  Transparent = 1  :  Top = 205  :  Left = 5  :  Visible = 0  :  Font = font4  : END CREATE
        CREATE dsol6 AS QLABEL  :  Transparent = 1  :  Top = 245  :  Left = 5  :  Visible = 0  :  Font = font4  : END CREATE
        CREATE dsol7 AS QLABEL  :  Transparent = 1  :  Top = 285  :  Left = 5  :  Visible = 0  :  Font = font4  : END CREATE
        CREATE dsol8 AS QLABEL  :  Transparent = 1  :  Top = 325  :  Left = 5  :  Visible = 0  :  Font = font4  : END CREATE
        CREATE dsol9 AS QLABEL  :  Transparent = 1  :  Top = 365  :  Left = 5  :  Visible = 0  :  Font = font4  : END CREATE
    END CREATE

    'Preferences window
    CREATE prefs_form AS QFORM
        Center
        Width = 400
        Height = 320
        CREATE prefsback AS QIMAGE  :  BMPHandle = wb_back  :  Top = 29  :  Left = 0  :  Width = 400  :  Height = 290  :  END CREATE
        BorderStyle = 4
        Caption = "Preferences :"
        CREATE prefs_panel AS QPANEL
            Top = 0  :  Left = 0  :  Height = 31  :  Width = 394  :  BevelOuter = 1
            CREATE prefs_bar AS QIMAGE  :  Top = 1  :  Left = 1  :  Width = 392  :  Height = 29  :  BMPHandle = toolbar  :  END CREATE

            'Buttons
            CREATE prefs_btn1  AS QCOOLBTN  :  Left = 10  :  Top = 3  :  Width = 27  :  Height = 26  :  Layout = 1  :  Flat = 1  :  BMPHandle = Bexit  :  Cursor = hand  :  Visible = 1  :  Hint = "Close Preferences."      :  OnClick = exit_prefs    :  ShowHint = shint  :  END CREATE
            CREATE prefs_btn2  AS QCOOLBTN  :  Left = 40  :  Top = 3  :  Width = 27  :  Height = 26  :  Layout = 1  :  Flat = 1  :  BMPHandle = Bsave  :  Cursor = hand  :  Visible = 1  :  Hint = "Save Preferences."      :  OnClick = prefs_save    :  ShowHint = shint  :  END CREATE
            CREATE prefs_btn3  AS QCOOLBTN  :  Left = 70  :  Top = 3  :  Width = 27  :  Height = 26  :  Layout = 1  :  Flat = 1  :  BMPHandle = Berase  :  Cursor = hand  :  Visible = 1  :  Hint = "Reset Preferences to default !"   :  OnClick = reset_prefs    :  ShowHint = shint  :  END CREATE
            CREATE prefs_btn4  AS QCOOLBTN  :  Left = 365  :  Top = 3  :  Width = 27  :  Height = 26  :  Layout = 1  :  Flat = 1  :  BMPHandle = Bhelp  :  Cursor = hand  :  Visible = 1  :  Hint = "Display Helps."       :  OnClick = help     :  ShowHint = shint  :  END CREATE
        END CREATE

        CREATE money AS QLABEL  :  Transparent = 1  : left = 5  :  Top = 35  :  Font = f_jaune  :  Caption = "Currency :"  :  END CREATE
        CREATE tl_dm AS QLABEL  :  Transparent = 1  :  Top = 55  :  Left = 5  :   :  Font = font5  :  Caption = "German Mark"  :  END CREATE
        CREATE te_dm AS QEDIT  :  Top = 53  :  Left = 95  :  Width = 50  :  Text = bpo(t_dm , ndec)  :  END CREATE
        CREATE tl_fb AS QLABEL  :  Transparent = 1  :  Top = 80  :  Left = 5  :   :  Font = font5  :  Caption = "Belgian Franc"  :  END CREATE
        CREATE te_fb AS QEDIT  :  Top = 78  :  Left = 95  :  Width = 50  :  Text = bpo(t_fb , ndec)  :  END CREATE
        CREATE tl_ff AS QLABEL  :  Transparent = 1  :  Top = 105  :  Left = 5  :   :  Font = font5  :  Caption = "French Franc"  :  END CREATE
        CREATE te_ff AS QEDIT  :  Top = 103  :  Left = 95  :  Width = 50  :  Text = bpo(t_ff , ndec)  :  END CREATE
        CREATE tl_euro AS QLABEL  :  Transparent = 1  :  Top = 130  :  Left = 5  :   :  Font = font5  :  Caption = "Euro"  :  END CREATE
        CREATE te_euro AS QEDIT  :  Top = 128  :  Left = 95  :  Width = 50  :  Text = bpo(t_euro , ndec)  :  END CREATE
        CREATE tl_lire AS QLABEL  :  Transparent = 1  :  Top = 155  :  Left = 5  :   :  Font = font5  :  Caption = "Italian Lira"  :  END CREATE
        CREATE te_lire AS QEDIT  :  Top = 153  :  Left = 95  :  Width = 50  :  Text = bpo(t_lire , ndec)  :  END CREATE
        CREATE tl_livre AS qlabel :  Transparent = 1  :  Top = 180  :  Left = 5  :   :  Font = font5  :  Caption = "British Pound"  :  END CREATE
        CREATE te_livre AS QEDIT  :  Top = 178  :  Left = 95  :  Width = 50  :  Text = bpo(t_livre , ndec)  :  END CREATE
        CREATE tl_us AS QLABEL  :  Transparent = 1  :  Top = 205  :  Left = 5  :   :  Font = font5  :  Caption = "US Dollar"  :  END CREATE
        CREATE te_us AS QEDIT  :  Top = 203  :  Left = 95  :  Width = 50  :  Text = bpo(t_us , ndec)  :  END CREATE
        CREATE tl_ca AS QLABEL  :  Transparent = 1  :  Top = 230  :  Left = 5  :   :  Font = font5  :  Caption = "Canadian Dollar"  :  END CREATE
        CREATE te_ca AS QEDIT  :  Top = 228  :  Left = 95  :  Width = 50  :  Text = bpo(t_ca , ndec)  :  END CREATE
        CREATE tl_cz AS QLABEL  :  Transparent = 1  :  Top = 255  :  Left = 5  :   :  Font = font5  :  Caption = "Czech Koruna"  :  END CREATE
        CREATE te_cz AS QEDIT  :  Top = 253  :  Left = 95  :  Width = 50  :  Text = bpo(t_cz , ndec)  :  END CREATE

        CREATE general2 AS QLABEL  :  Transparent = 1  : left = 180  :  Top = 35  :  Font = f_jaune  :  Caption = "General :"  :  END CREATE
        CREATE bulle_aide AS QLABEL   :  Top = 55  :  Transparent = 1  : left = 180  :  Font = font5  :  Caption = "Help Bubbles "  :  END CREATE
        CREATE hint_butt AS QBUTTON   :  Top = 50  :  Left = 280  :  Cursor = hand  :  Caption = mode_hint  :  Hint = "Enable / Disable helps bubbles."  :  ShowHint = shint  :  Width = 40  :  Height = 22  :  OnClick = switch_hint  :  END CREATE
        CREATE ndecL AS QLABEL    :  Top = 80  :  Transparent = 1  : left = 180  :  Font = font5   :  Caption = "Fix decimal (0 - 9) "  :  END CREATE
        CREATE ndec_item AS QEDIT   :  Top = 78  :  Left = 280  :  Width = 40   :  Text = STR$(ndec)  :  END CREATE
        CREATE aeroclub AS QLABEL   :  Top = 105  :  Transparent = 1  : left = 180  :  Font = font5   :  Caption = "Aero - Club Name "  :  END CREATE
        CREATE aero_edit AS QEDIT   :  Top = 103  :  Left = 280  :  Width = 100   :  Text = aero_edt  :  END CREATE
    END CREATE

    'About window
    CREATE about_form AS QFORM
        Width = 300
        Height = 249
        Center
        BorderStyle = 4
        Caption = "About : "
        CREATE reg_image AS QIMAGE   :  Top = 0  :  Left = 0  :  Width = 300  :  Height = 220  :  BMPHandle = credit  :  END CREATE
        CREATE about_btn AS QCOOLBTN  :  Top = 191  :  Left = 266  :  Width = 27  :  Height = 26  :  Flat = 1  :  Layout = 1  :  BMPHandle = Bok  :  Cursor = hand  :  OnClick = exit_about  :  Hint = "Close About box"  :  ShowHint = shint  :  END CREATE
    END CREATE

    'FlyTools menu creation
    CREATE mmenu AS QMAINMENU

        'File menu
        CREATE menufile AS QMENUITEM
            Caption = "&File"
            CREATE quit AS QMENUITEM
                Caption = "Quit"
                ShortCut = "ctrl+Q"
                OnClick = exit_flytools
            END CREATE
        END CREATE

        'Avionics menu
        CREATE avi_menu AS QMENUITEM
            Caption = "&Favorites"

            CREATE air_dbase AS QMENUITEM
                Caption = "AirField ICAO"
                ShortCut = "F4"
                OnClick = air_db
            END CREATE

            CREATE PLB_dbase AS QMENUITEM
                Caption = "Flight LogBook"
                ShortCut = "F5"
                OnClick = log_db
            END CREATE
        END CREATE

        'Avionics Helpers
        CREATE avionics_helpers AS QMENUITEM
            Caption = "&Aviation computing"
            CREATE fleg AS QMENUITEM
                Caption = "Flight Leg"
                ShortCut = "F6"
                OnClick = leg_calc
            END CREATE

            CREATE wb AS QMENUITEM
                Caption = "Weight and Balance"
                ShortCut = "F7"
                OnClick = wb_calc
            END CREATE

            CREATE true_h AS QMENUITEM
                Caption = "True Heading"
                OnClick = Th_calc
            END CREATE

            CREATE m_h AS QMENUITEM
                Caption = "Magnetic heading"
                OnClick = mh_calc
            END CREATE

            CREATE g_s AS QMENUITEM
                Caption = "Ground Speed"
                OnClick = gs_calc
            END CREATE

            CREATE temp_alt AS QMENUITEM
                Caption = "Predicting freezing levels"
                OnClick = main_predic_gel
            END CREATE

            CREATE wins AS QMENUITEM
                Caption = "Wind direction"
                OnClick = main_wind
            END CREATE
        END CREATE

        'Conversion menu
        CREATE menuconv AS QMENUITEM
            Caption = "&Conversions"
            CREATE unites_angles AS QMENUITEM
                Caption = "Angle"
                ShortCut = "ctrl+A"
                OnClick = main_angles
            END CREATE

            CREATE base_calc AS QMENUITEM
                Caption = "Base"
                OnClick = base_conv
                ShortCut = "ctrl+B"
            END CREATE

            CREATE change AS QMENUITEM
                Caption = "Currency"
                ShortCut = "ctrl+C"
                OnClick = main_conv_change
            END CREATE

            CREATE units_liquide AS QMENUITEM
                Caption = "Fuel"
                ShortCut = "ctrl+F"
                OnClick = main_liquide
            END CREATE

            CREATE units_distances AS QMENUITEM
                Caption = "Length"
                ShortCut = "ctrl+L"
                OnClick = main_distances
            END CREATE

            CREATE units_poids AS QMENUITEM
                Caption = "Mass"
                ShortCut = "ctrl+M"
                OnClick = main_poids
            END CREATE

            CREATE units_pression AS QMENUITEM
                Caption = "Pressure"
                ShortCut = "ctrl+P"
                OnClick = main_pressure
            END CREATE

            CREATE units_charge AS QMENUITEM
                Caption = "Power"
                ShortCut = "ctrl+W"
                OnClick = main_charge
            END CREATE

            CREATE Units_speeds AS QMENUITEM
                Caption = "Speed"
                ShortCut = "ctrl+S"
                OnClick = main_speeds
            END CREATE

            CREATE units_temp AS QMENUITEM
                Caption = "Temperature"
                ShortCut = "ctrl+T"
                OnClick = main_temp
            END CREATE
        END CREATE

        'Preferences menu
        CREATE menuprefs AS QMENUITEM
            Caption = "&Others"

            CREATE prefs AS QMENUITEM
                Caption = "Preferences"
                ShortCut = "F3"
                OnClick = main_prefs
            END CREATE

            CREATE apropos AS QMENUITEM
                Caption = "About"
                OnClick = about
            END CREATE

            CREATE visit_lightplane AS QMENUITEM
                Caption = "Flytools website"
                OnClick = weblightplane
            END CREATE
        END CREATE

        'Help menu
        CREATE menuhelp AS QMENUITEM
            Caption = "&Help"
            CREATE welcome AS QMENUITEM
                Caption = "Contents"
                ShortCut = "F1"
                OnClick = help
            END CREATE
        END CREATE
    END CREATE
END CREATE

'Include SUB conversion and help
$include "c:\rapidq\projets\flytools\includes\loader.inc"

CALL loader

$include "c:\rapidq\projets\flytools\includes\convertionSUB.inc"
$include "c:\rapidq\projets\flytools\includes\help.inc"

'Airfield database
SUB air_db
    airfield.Show
END SUB

'Logbook
SUB log_db
    logbook.Show
END SUB

SUB WB_calc
    wb_form.Show
END SUB

'Go to Web pages
SUB Mlogoclick
    ShellExe 0 , "Open" , "http://www.lightplane.org" , "" , "" , 1
END SUB

'About form
SUB about
    about_form.Show
END SUB

'Interface reset routines
SUB clean_interface
    intro_text0.Caption = ""
    intro_text1.Caption = ""
    intro_text2.Caption = ""
    intro_text3.Caption = ""
    intro_text4.Caption = ""

    label.Caption = ""
    dlab1.Caption = ""  :  dlab4.Caption = ""
    dlab2.Caption = ""  :  dlab5.Caption = ""
    dlab3.Caption = ""  :  dlab6.Caption = ""
    dlab7.Caption = ""  :  dlab8.Caption = ""
    label.Visible = 0
    dlab1.Visible = 0  :  d1.Visible = 0  :  dlab4.Visible = 0  :  d4.Visible = 0
    dlab2.Visible = 0  :  d2.Visible = 0  :  dlab5.Visible = 0  :  d5.Visible = 0
    dlab3.Visible = 0  :  d3.Visible = 0  :  dlab6.Visible = 0  :  d6.Visible = 0
    dlab7.Visible = 0  :  d7.Visible = 0  :  dlab8.Visible = 0  :  d8.Visible = 0
    dsol1.Visible = 0  :  sol1.Visible = 0  :  dsol1.Caption = ""
    dsol2.Visible = 0  :  sol2.Visible = 0  :  dsol2.Caption = ""
    dsol3.Visible = 0  :  sol3.Visible = 0  :  dsol3.Caption = ""
    dsol4.Visible = 0  :  sol4.Visible = 0  :  dsol4.Caption = ""
    dsol5.Visible = 0  :  sol5.Visible = 0  :  dsol5.Caption = ""
    dsol6.Visible = 0  :  sol6.Visible = 0  :  dsol6.Caption = ""
    dsol7.Visible = 0  :  sol7.Visible = 0  :  dsol7.Caption = ""
    dsol8.Visible = 0  :  sol8.Visible = 0  :  dsol8.Caption = ""
    dsol9.Visible = 0  :  sol9.Visible = 0  :  dsol9.Caption = ""
    btn4.Enabled = 0
    sol1.Text = ""  :  sol2.Text = ""  :  sol3.Text = ""  :  sol4.Text = ""  :  sol5.Text = ""  :  sol6.Text = ""  :  sol7.Text = ""  :  sol8.Text = ""  :  sol9.Text = ""
    d1.Text = ""   :  d2.Text = ""   :  d3.Text = ""   :  d4.Text = ""   :  d5.Text = ""   :  d6.Text = ""  :  d7.Text = ""  :  d8.Text = ""
    conv_devise.Visible  = 0
    changes.Visible   = 0
    conv_speeds.Visible  = 0
    conv_charge.Visible  = 0
    conv_pressure.Visible = 0
    conv_poids.Visible  = 0
    conv_temp.Visible  = 0
    conv_liquide.Visible = 0
    conv_distances.Visible = 0
    conv_angles.Visible  = 0
    conv_base.Visible  = 0
END SUB

'preferences
SUB main_prefs

    'Preferences variables
    panelinfo.Panel(1).Caption = "Tools tips : " + mode_hint
    aero_edt = STRING(aero_edit.Text)

    'Display help bubbles
    hint_butt.Caption = mode_hint
    paneldroit.ShowHint = STR$(shint)
    label.ShowHint  = STR$(shint)
    hint_butt.ShowHint = STR$(shint)
    mlogo.ShowHint  = STR$(shint)
    add_field.ShowHint = STR$(shint)
    sall.ShowHint   = STR$(shint)
    del_field.ShowHint = STR$(shint)
    add_log.ShowHint  = STR$(shint)
    sall2.ShowHint  = STR$(shint)
    del_log.ShowHint  = STR$(shint)
    main_field_log.ShowHint = STR$(shint)
    find_field.ShowHint = STR$(shint)
    find_log.ShowHint  = STR$(shint)
    save_log_db.ShowHint = STR$(shint)
    open_log_db.ShowHint = STR$(shint)
    main_field.ShowHint = STR$(shint)
    find_field.ShowHint = STR$(shint)
    save_field.ShowHint = STR$(shint)
    open_field.ShowHint = STR$(shint)
    btn0.ShowHint   = STR$(shint)
    btn1.ShowHint   = STR$(shint)
    btn2.ShowHint   = STR$(shint)
    btn3.ShowHint   = STR$(shint)
    btn4.ShowHint   = STR$(shint)
    btn5.ShowHint   = STR$(shint)
    wbbtn1.ShowHint  = STR$(shint)
    wbbtn2.ShowHint  = STR$(shint)
    wbbtn3.ShowHint  = STR$(shint)
    wbbtn4.ShowHint  = STR$(shint)
    wbbtn5.ShowHint  = STR$(shint)
    close_log_db.ShowHint = STR$(shint)
    close_air_db.ShowHint = STR$(shint)
    air_help.ShowHint  = STR$(shint)
    air_help2.ShowHint  = STR$(shint)
    log_help.ShowHint  = STR$(shint)
    log_search_help.ShowHint = STR$(shint)
    prefs_btn1.ShowHint  = STR$(shint)
    prefs_btn2.ShowHint  = STR$(shint)
    prefs_btn3.ShowHint  = STR$(shint)
    prefs_btn4.ShowHint  = STR$(shint)
    about_btn.ShowHint  = STR$(shint)

    prefs_form.Show
END SUB

'Save preferences
SUB prefs_save
    prefs_ini.Open("c:\flytools\prefs\Flyprefs.dat" , fmOpenReadWrite)
    ndec  = VAL(ndec_item.Text)

    IF aero_edit.Text = "" THEN
        aero_edt = STRING(" ")
    ELSE
        aero_edt = STRING(aero_edit.Text)
    END IF

    prefs_ini.WriteNum(ndec , Num_BYTE)
    prefs_ini.WriteNum(shint , Num_BYTE)
    prefs_ini.WriteStr(mode_hint , 3)
    prefs_ini.WriteStr(aero_edt , 100)
    Prefs_ini.Close

    t_dm = VAL(te_dm.Text)
    t_fb = VAL(te_fb.Text)
    t_ff = VAL(te_ff.Text)
    t_euro = VAL(te_euro.Text)
    t_lire = VAL(te_lire.Text)
    t_livre = VAL(te_livre.Text)
    t_us = VAL(te_us.Text)
    t_ca = VAL(te_ca.Text)
    t_cz = VAL(te_cz.Text)
    devises_ini.Open("c:\flytools\prefs\Flydata.dat" , fmOpenReadWrite)
    devises_ini.WriteNum(t_fb , Num_DOUBLE)
    devises_ini.WriteNum(t_ff , Num_DOUBLE)
    devises_ini.WriteNum(t_dm , Num_DOUBLE)
    devises_ini.WriteNum(t_euro , Num_DOUBLE)
    devises_ini.WriteNum(t_lire , Num_DOUBLE)
    devises_ini.WriteNum(t_livre , Num_DOUBLE)
    devises_ini.WriteNum(t_us , Num_DOUBLE)
    devises_ini.WriteNum(t_ca , Num_DOUBLE)
    devises_ini.WriteNum(t_cz , Num_DOUBLE)
    devises_ini.Close
    panelinfo.Panel(0).Caption = "Decimal Fix : " + STR$(ndec)
END SUB

'Enable or disable help bubbles
SUB switch_hint
    IF shint = 1 THEN
        shint = 0  :  hint_butt.Caption = mode_hint  :  mode_hint = "No"
    ELSEIF shint = 0 THEN
        shint = 1  :  hint_butt.Caption = mode_hint  :  mode_hint = "Yes"
    END IF
    CALL main_prefs
END SUB

'Conversion rates EURO
SUB reset_prefs
    te_dm.Text = STR$(1.96)
    te_fb.Text = STR$(40.3399)
    te_ff.Text = STR$(6.56)
    te_euro.Text = STR$(1)
    te_lire.Text = STR$(1936.27)
    te_livre.Text = STR$(0.60)
    te_us.Text = STR$(0.96)
    te_ca.Text = STR$(1.38)
    te_cz.Text = STR$(36.13)
END SUB

'Local time display
SUB QTimer1(hrs% , min%)
    DIM I AS INTEGER
    Timer1.Interval = 500
    I = I + 1
    hrs% = VAL(LEFT$(TIME$ , 2))
    min% = VAL(MID$(TIME$ , 4 , 2))
    IF temp% <> min% THEN
        panelinfo.Panel(3).Caption = "Local Time : " + times(hrs% , min%)
        temp% = min%
    END IF
END SUB

'Exit routines
SUB wb_close
    wb_form.Close
END SUB

SUB air_close
    DIM a AS INTEGER
    IF mlv.RowCount > 2 THEN
        a = MESSAGEDLG("Save File Before You Exit?" , 3 , 3 , "")
        IF a = 6 THEN
            saveclick
        END IF
    END IF
    airfield.Close
END SUB

SUB log_close
    DIM a AS INTEGER
    IF mlv_log.RowCount > 2 THEN
        a = MESSAGEDLG("Save File Before You Exit?" , 3 , 3 , "")
        IF a = 6 THEN
            saveclick_log
        END IF
    END IF
    logbook.Close
END SUB

SUB exit_prefs
    ndec = VAL(ndec_item.Text)
    panelinfo.Panel(0).Caption = "Decimal Fix : " + STR$(ndec)
    logbook.Caption  = "Flight LogBook : "  + STRING(aero_edit.Text)
    airfield.Caption = "Airfield Database : " + STRING(aero_edit.Text)
    mainform.Caption = "FlyTools : "   + STRING(aero_edit.Text)
    prefs_form.Close
END SUB

SUB exit_about
    about_form.Close
END SUB

SUB weblightplane
    ShellExe 0 , "Open" , "http://www.lightplane.org" , "" , "" , 1
END SUB

SUB exit_flytools
    IF MESSAGEDLG("Exit FlyTools ?" , mtConfirmation , mbYes OR mbNo , 0) = mrYes THEN
        mainform.Close
    END IF
END SUB
'END of Main code...
