' **************************************************************
' FlyTools - Version 1.6.1
' Code by Benoit (BSM3D) Saint-Moulin
' Last tested: 08/01/2025 on Windows 10 x64 (2025)
' Language: RapidQ (Basic) Framework
' Initial Release: 04/01/2000
' This is a 25th Anniversary re-issue release for educational and learning purposes
'
' This code has no pretension - it was CREATED in the 2000s
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
' While still FUNCTIONAL on modern Windows systems, it uses the RapidQ framework
' which is no longer actively maintained.
' ****************************************************************************************************************************************************************

' Definition of the WB form
DIM L_sol AS INTEGER, l_lab AS INTEGER

' Global variable of the WB form
L_sol = 330 'align left solution
L_lab = 190 'align left label solution

' Wheels
DIM w1 AS DOUBLE, w2 AS DOUBLE, w3 AS DOUBLE

' Empty weight
DIM tew AS DOUBLE

' Empty C.G. weight
DIM ecg AS DOUBLE

' Loading
DIM pilotw AS DOUBLE, passw AS DOUBLE, bag_compw AS DOUBLE, wing_bagw AS DOUBLE, fuelw AS DOUBLE, twair AS DOUBLE, tlw AS DOUBLE

' Moment calculations
DIM mm0 AS DOUBLE, mm1 AS DOUBLE, mm2 AS DOUBLE, mm3 AS DOUBLE, mm4 AS DOUBLE 
DIM cm0 AS DOUBLE, cm1 AS DOUBLE, cm2 AS DOUBLE, cm3 AS DOUBLE, cm4 AS DOUBLE, tmm AS DOUBLE 

' Aircraft weight / C.G. verification
DIM rscg AS DOUBLE, chkw AS STRING, fcg AS STRING, rcg AS STRING

' Print variable
DIM p_airid AS STRING
p_airid = "Zodiac CH 601 (Tricycle)"

CREATE wb_form AS QForm
    caption = "Weight and Balance."
    width   = 400 : height = 355
    center
    borderstyle = 4
    CREATE wbback AS QImage : bmphandle = wb_back : top = 29 : left = 0 : width = 400 : height = 305 : END CREATE
 
    CREATE pop_menu_wb AS QPopupMenu
        CREATE Pop_helpwb   AS QMenuItem :Caption ="Help"         : shortcut = "F1"     : OnClick=help           :END CREATE
        CREATE win_calcwb   AS QMenuItem :caption ="Calculator"   : shortcut = "F2"     : onclick=calc           :END CREATE
        CREATE pop_prefswb  AS QMenuItem :Caption ="Prefs"        : shortcut = "F3"     : OnClick=main_prefs     :END CREATE
        CREATE Pop_quitwb   AS QMenuItem :Caption ="Close"        : shortcut = "Esc"    : OnClick=wb_close       :END CREATE
    END CREATE 
    Popupmenu = pop_menu_wb
  
    CREATE wb_panel AS QPanel
        top = 0 : left = 0 : height = 31 : width = 394 : bevelouter = 1
        CREATE wb_bar AS QImage : top = 1 : left = 1 : width = 392 : height = 29 : bmphandle = toolbar : END CREATE
 
        ' Buttons   
        CREATE wbbtn1      AS QCoolBtn : left = 10  : top = 3 : width = 27 : height = 26 : layout = 1 : flat = 1 : bmphandle = bexit   : cursor = hand : visible = 1 : hint = "Close Weight and Balance panel."      : onclick = wb_close          : showhint = shint         : END CREATE 
        CREATE wbbtn2      AS QCoolBtn : left = 40  : top = 3 : width = 27 : height = 26 : layout = 1 : flat = 1 : bmphandle = beval   : cursor = hand : visible = 1 : hint = "Solve your Weight and Balance."       : onclick = ch601_tri_calc    : showhint = shint         : END CREATE 
        CREATE wbbtn3      AS QCoolBtn : left = 70  : top = 3 : width = 27 : height = 26 : layout = 1 : flat = 1 : bmphandle = bdel    : cursor = hand : visible = 1 : hint = "Clear input datas"                    : onclick = clear_wb          : showhint = shint   : END CREATE
        CREATE wbbtn4      AS QCoolBtn : left = 100 : top = 3 : width = 27 : height = 26 : layout = 1 : flat = 1 : bmphandle = bprint  : cursor = hand : visible = 1 : hint = "Print your result sheet."             : onclick = wb_print          : showhint = shint   : END CREATE
        CREATE wbbtn5      AS QCoolBtn : top = 3    : left = 365  : width = 27 : height = 26 : flat = 1 : layout = 1  : bmphandle = bhelp : cursor = hand : onclick = help : hint = "Display Helps." : showhint = shint :  END CREATE
        CREATE Id_aircraft AS QLabel : caption = "Aircrafts : " : font = font4 : transparent = 1 : left = 135 : top = 7 : END CREATE
 
        CREATE Aircraft_ID AS QComboBox : top = 5 : left = 180 : width = 180 : dropdowncount = 1
            AddItems "CH 601 (Tricycle)" : itemindex = 0 : OnChange = air_id_item : END CREATE
    END CREATE
  
    ' Interface 
    CREATE w_point     AS QLabel : transparent = 1 : caption = "Weighing Point (Kg) :" : left = 5   : top = 40   : font  = f_jaune : visible = 1 : END CREATE
    CREATE wheel1      AS QLabel : transparent = 1 : caption = "Nose wheel" :left = 5   : top = 65   : font  = font5 : visible = 1 : END CREATE
    CREATE Dwheel1     AS QEdit  : left = 120 : top = 65   : width = 40    : visible = 1 : END CREATE
    CREATE wheel2      AS QLabel : transparent = 1 : caption = "Left wheel" :left = 5   : top = 95   : font  = font5 : visible = 1 : END CREATE
    CREATE Dwheel2     AS QEdit  : left = 120 : top = 95   : width = 40    : visible = 1 : END CREATE
    CREATE wheel3      AS QLabel : transparent = 1 : caption = "Right wheel" :left = 5   : top = 125  : font  = font5 : visible = 1 : END CREATE
    CREATE Dwheel3     AS QEdit  : left = 120 : top = 125  : width = 40    : visible = 1 : END CREATE
    CREATE Charge      AS QLabel : transparent = 1 : caption = "Weight add (Kg) :" :left = 5   : top = 160  : font  = f_jaune : visible = 1 : END CREATE
    CREATE charge1     AS QLabel : transparent = 1 : caption = "Pilot" :left = 5   : top = 185  : font  = font5 : visible = 1 : END CREATE
    CREATE dcharge1    AS QEdit  : left = 120 : top = 185  : width = 40    : visible = 1 : END CREATE
    CREATE charge2     AS QLabel : transparent = 1 : caption = "Passenger" :left = 5   : top = 215  : font = font5  : visible = 1 : END CREATE
    CREATE dcharge2    AS QEdit  : left = 120 : top = 215  : width = 40    : visible = 1 : END CREATE
    CREATE charge3     AS QLabel : transparent = 1 : caption = "Baggage compartment" :left = 5   : top = 245  : font = font5  : visible = 1 : END CREATE
    CREATE dcharge3    AS QEdit  : left = 120 : top = 245  : width = 40    : visible = 1 : END CREATE
    CREATE charge4     AS QLabel : transparent = 1 : caption = "Wing locker baggage" :left = 5   : top = 275  : font = font5  : visible = 1 : END CREATE
    CREATE dcharge4    AS QEdit  : left = 120 : top = 275  : width = 40    : visible = 1 : END CREATE 
    CREATE charge5     AS QLabel : transparent = 1 : caption = "Fuel (Liter)" :left = 5   : top = 305  : font = font5  : visible = 1 : END CREATE
    CREATE dcharge5    AS QEdit  : left = 120 : top = 305  : width = 40    : visible = 1 : END CREATE
 
    ' Solutions display
    CREATE empty_air   AS QLabel : transparent = 1 : left = L_lab : top = 65  : visible = 0 : font = font5 : END CREATE
    CREATE Sempty_air  AS QLabel : transparent = 1 : left = L_sol : top = 65  : visible = 0 : font = font5 : END CREATE
    CREATE empty_wcg   AS QLabel : transparent = 1 : left = L_lab : top = 95  : visible = 0 : font = font5 : END CREATE
    CREATE sempty_wcg  AS QLabel : transparent = 1 : left = L_sol : top = 95  : visible = 0 : font = font5 : END CREATE
    CREATE load_air    AS QLabel : transparent = 1 : left = L_lab : top = 125 : visible = 0 : font = font5 : END CREATE
    CREATE sload_air   AS QLabel : transparent = 1 : left = L_sol : top = 125 : visible = 0 : font = font5 : END CREATE
    CREATE search_cg   AS QLabel : transparent = 1 : left = L_lab : top = 185 : visible = 0 : font = font5 : END CREATE
    CREATE Ssearch_cg  AS QLabel : transparent = 1 : left = L_sol : top = 185 : visible = 0 : font = font5 : END CREATE
    CREATE total_air   AS QLabel : transparent = 1 : left = L_lab : top = 215 : visible = 0 : font = font5 : END CREATE
    CREATE Stotal_air  AS QLabel : transparent = 1 : left = L_sol : top = 215 : visible = 0 : font = font5 : END CREATE
    CREATE check_w     AS QLabel : transparent = 1 : left = L_lab : top = 245 : visible = 0 : font = font5 : END CREATE
    CREATE Scheck_w    AS QLabel : transparent = 1 : left = L_sol : top = 245 : visible = 0 :              : END CREATE
    CREATE tfcg        AS QLabel : transparent = 1 : left = L_lab : top = 275 : visible = 0 : font = font5 : END CREATE
    CREATE Stfcg       AS QLabel : transparent = 1 : left = L_sol : top = 275 : visible = 0 :              : END CREATE
    CREATE trcg        AS QLabel : transparent = 1 : left = L_lab : top = 305 : visible = 0 : font = font5 : END CREATE
    CREATE Strcg       AS QLabel : transparent = 1 : left = L_sol : top = 305 : visible = 0 :              : END CREATE
END CREATE

SUB clear_wb
    Dwheel1.text = ""
    Dwheel2.text = ""
    Dwheel3.text = ""
    dcharge1.text    = ""
    dcharge2.text    = ""
    dcharge3.text    = ""
    dcharge4.text    = ""
    dcharge5.text    = ""
    empty_air.caption = ""   : empty_air.visible   = 0
    sempty_air.caption = ""  : sempty_air.visible  = 0
    empty_wcg.caption = ""   : empty_wcg.visible   = 0
    sempty_wcg.caption = ""  : sempty_wcg.visible  = 0
    load_air.caption = ""    : load_air.visible    = 0
    sload_air.caption = ""   : sload_air.visible   = 0
    search_cg.caption = ""   : search_cg.visible   = 0
    ssearch_cg.caption = ""  : ssearch_cg.visible  = 0
    total_air.caption = ""   : total_air.visible   = 0
    stotal_air.caption = ""  : stotal_air.visible  = 0    
    check_w.caption = ""     : check_w.visible     = 0
    scheck_w.caption = ""    : scheck_w.visible    = 0
    tfcg.caption = ""        : tfcg.visible        = 0
    stfcg.caption = ""       : stfcg.visible       = 0
    trcg.caption = ""        : trcg.visible        = 0
    strcg.caption = ""       : strcg.visible       = 0
END SUB

' Clear weight and balance interface
SUB wb_clear_interface
    w_point.caption = "": w_point.visible = 0
    wheel1.caption = "" : Dwheel1.text = ""
    wheel1.visible = 0  : dwheel1.visible = 0
    wheel2.caption = "" : Dwheel2.text = ""
    wheel2.visible = 0  : dwheel2.visible = 0
    wheel3.caption = "" : Dwheel3.text = ""
    wheel3.visible = 0  : dwheel3.visible = 0
    charge.caption  = "" : charge.visible   = 0
    charge1.caption = "" : dcharge1.text    = ""
    charge1.visible = "" : dcharge1.visible = ""
    charge2.caption = "" : dcharge2.text    = ""
    charge2.visible = "" : dcharge2.visible = ""
    charge3.caption = "" : dcharge3.text    = ""
    charge3.visible = "" : dcharge3.visible = ""
    charge4.caption = "" : dcharge4.text    = ""
    charge4.visible = "" : dcharge4.visible = ""
    charge5.caption = "" : dcharge5.text    = ""
    charge5.visible = "" : dcharge5.visible = ""
    empty_air.caption = ""   : empty_air.visible   = 0
    sempty_air.caption = ""  : sempty_air.visible  = 0
    empty_wcg.caption = ""   : empty_wcg.visible   = 0
    sempty_wcg.caption = ""  : sempty_wcg.visible  = 0
    load_air.caption = ""    : load_air.visible    = 0
    sload_air.caption = ""   : sload_air.visible   = 0
    search_cg.caption = ""   : search_cg.visible   = 0
    ssearch_cg.caption = ""  : ssearch_cg.visible  = 0
    total_air.caption = ""   : total_air.visible   = 0
    stotal_air.caption = ""  : stotal_air.visible  = 0    
    check_w.caption = ""     : check_w.visible     = 0
    scheck_w.caption = ""    : scheck_w.visible    = 0
    tfcg.caption = ""        : tfcg.visible        = 0
    stfcg.caption = ""       : stfcg.visible       = 0
    trcg.caption = ""        : trcg.visible        = 0
    strcg.caption = ""       : strcg.visible       = 0
END SUB

' Choose an aircraft
SUB air_id_item
    SELECT CASE aircraft_id.ItemIndex  
        CASE 0
            CALL ch601_tri
    END SELECT
END SUB

SUB ch601_tri
    CALL wb_clear_interface
    p_airid = "Zodiac CH 601 (Tricycle)"
    w_point.visible = 1  : w_point.caption = "Weighing Point ( Kg ). :"
    wheel1.visible  = 1  : wheel1.caption = "Nose wheel"  : dwheel1.visible = 1
    wheel2.visible  = 1  : wheel2.caption = "Left wheel"  : dwheel2.visible = 1
    wheel3.visible  = 1  : wheel3.caption = "Right wheel" : dwheel3.visible = 1
    charge.visible  = 1  : charge.caption = "Weight ( Kg ). :"
    charge1.visible = 1  : charge1.caption = "Pilot"               : dcharge1.visible = 1
    charge2.visible = 1  : charge2.caption = "Passenger"           : dcharge2.visible = 1
    charge3.visible = 1  : charge3.caption = "Baggage compartment" : dcharge3.visible = 1
    charge4.visible = 1  : charge4.caption = "Wing locker baggage" : dcharge4.visible = 1
    charge5.visible = 1  : charge5.caption = "Fuel (Liter)"        : dcharge5.visible = 1
    wbbtn2.onclick = ch601_tri_calc
    wbbtn3.onclick = clear_wb       
    wbbtn4.onclick = wb_print
END SUB

SUB ch601_tri_calc
    ' Specific ARM to the aircraft
    mm0 = 217.78
    mm1 = 650
    mm2 = 1400
    mm3 = 600
    mm4 = 280
    ' Empty weight
    w1  = val(dwheel1.text)
    w2  = val(dwheel2.text)
    w3  = val(dwheel3.text)
    tew = w1 + w2 + w3
    ' Center weight modifier according to aircraft
    ecg = 630-((w1*1200)/tew)
    ' Loaded weight
    pilotw    = val(dcharge1.text)
    passw     = val(dcharge2.text)
    bag_compw = val(dcharge3.text)
    wing_bagw = val(dcharge4.text)
    fuelw     = val(dcharge5.text)* 0.72
    tlw       = pilotw + passw + bag_compw + wing_bagw + fuelw
    ' Total aircraft weight
    twair = tlw+tew
    ' Weight * arm = moment = research of C.G.
    cm0  = tew * mm0
    cm1  = (pilotw + passw) * mm1
    cm2  = bag_compw * mm2
    cm3  = wing_bagw * mm3
    cm4  = fuelw * mm4
    tmm  = cm0 + cm1 + cm2 + cm3 + cm4
    rscg = tmm / twair
    IF twair > 545.06 THEN 
        chkw = "TOO HEAVY !" 
        scheck_w.caption   = STRING(chkw): scheck_w.font = f_rouge : scheck_w.visible = 1
    ELSE 
        chkw = "OK" 
        scheck_w.caption   = STRING(chkw): scheck_w.font = f_vert : scheck_w.visible = 1
    END IF 
    IF rscg  >= 265   THEN 
        fcg  = "OK"
        sTfcg.caption = STRING(fcg): stfcg.font = f_vert  : stfcg.visible = 1
    ELSE 
        fcg = "NO GOOD !"
        sTfcg.caption = STRING(fcg): stfcg.font = f_rouge : stfcg.visible = 1
    END IF
    IF rscg  <= 445   THEN
        rcg  = "Ok" 
        Strcg.caption = STRING(rcg) : strcg.font = f_vert : strcg.visible = 1 
    ELSE 
        rcg = "NO GOOD !" 
        Strcg.caption = STRING(rcg) : strcg.font = f_rouge: strcg.visible = 1 
    END IF
    ' Display result of WB
    empty_air.caption  = "Empty weight Aircraft "       : empty_air.visible   = 1
    sempty_air.caption = bpo(tew,ndec)+ " KG"           : sempty_air.visible  = 1
    empty_wcg.caption  = "Empty weight C.G. "           : empty_wcg.visible   = 1
    sempty_wcg.caption = bpo(ecg,ndec)+ " KG"           : sempty_wcg.visible  = 1
    load_air.caption   = "Loaded weight "               : load_air.visible    = 1
    sload_air.caption  = bpo(tlw,ndec)+ " KG"           : sload_air.visible   = 1
    search_cg.caption  = "Result of search of C.G. "    : search_cg.visible   = 1
    ssearch_cg.caption = bpo(rscg,ndec)+ " MM"          : ssearch_cg.visible  = 1
    total_air.caption  = "Total aircraft weight "       : total_air.visible   = 1
    stotal_air.caption = bpo(twair,ndec)+ " KG"         : stotal_air.visible  = 1
    check_w.caption    = "Result of aircraft weight "   : check_w.visible     = 1
    Tfcg.caption       = "Result of forward C.G limit " : tfcg.visible        = 1
    trcg.caption       = "Result or rearward C.G limit ": trcg.visible        = 1
END SUB

' Print Wb sheet
SUB wb_print
    Printer.Orientation = 0
    Printer.BeginDoc
    Printer.Font = F_print12
    Printer.TextOut(25,30,"FlyTools - Weight & Balance datasheet.",0,-1)
    Printer.Line   (25,100,2500,100,0)
    Printer.Font = F_print10 
    Printer.TextOut(25,150,"Aircraft model : " + P_airid,0,-1)
    Printer.Font = F_print12
    Printer.TextOut(25,250,"User Datas :",0,-1)
    Printer.Line   (25,320,320,320,0)
    Printer.TextOut(25,350,"Weighing Point (Kg) :",0,-1)
    Printer.Font = F_print10
    Printer.TextOut(25,420,"Nose wheel = "  + dwheel1.text+ " Kg" ,0,-1)
    Printer.TextOut(25,490,"Left wheel = "  + dwheel2.text+ " Kg" ,0,-1)
    Printer.TextOut(25,560,"Right wheel = " + dwheel3.text+ " Kg" ,0,-1)
    Printer.Font = F_print12
    Printer.TextOut(25,660,"Weight (Kg) :",0,-1)
    Printer.Font = F_print10
    Printer.TextOut(25,730,"Pilot = " + dcharge1.text+ " Kg",0,-1)
    Printer.TextOut(25,800,"Passenger = " + dcharge2.text+ " Kg",0,-1)
    Printer.TextOut(25,870,"Baggage compartment = " + dcharge3.text+ " Kg",0,-1)
    Printer.TextOut(25,940,"Wing locker baggage = " + dcharge4.text+ " Kg",0,-1)
    Printer.TextOut(25,1010,"Fuel = " + dcharge5.text+ " Liters",0,-1)
    Printer.Font = F_print12
    Printer.TextOut(25,1110,"Results : ",0,-1)
    Printer.Line   (25,1180,240,1180,0)
    Printer.Font = F_print10
    Printer.TextOut   (25,1230,"Empty weight Aircraft = " + bpo(tew,ndec) + " Kg",0,-1)
    Printer.TextOut   (25,1300,"Empty weight C.G. = " + bpo(ecg,ndec)+ " Kg",0,-1)
    Printer.TextOut   (25,1370,"Loaded weight = " + bpo(tlw,ndec) + " Kg",0,-1)
    Printer.TextOut   (25,1440,"Result of search of C.G. = " + bpo(rscg,ndec) + " Mm",0,-1)
    Printer.TextOut   (25,1510,"Total aircraft weight = " + bpo(twair,ndec) + " Kg",0,-1)
    Printer.TextOut   (25,1580,"Result of aircraft weight is " + STRING(chkw),0,-1)
    Printer.TextOut   (25,1650,"Result of forward C.G limit is " + STRING(fcg),0,-1)
    Printer.TextOut   (25,1720,"Result or rearward C.G limit is " + STRING(rcg),0,-1)
    Printer.Line      (25,3250,2500,3250,0)
    printer.font = f_print9
    Printer.TextOut   (25,3300,"FlyTools V1.6.1 1999-2025 Benoit (BSM3D) Saint-Moulin - HTTP://www.lightplane.org",0,-1)
    Printer.EndDoc
END SUB