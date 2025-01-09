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
' to use, copy, modIFy, merge, publish, distribute, SUBlicense, and/or sell
' copies of the Software, and to permit persons to whom the Software is
' furnished to do so, SUBject to the following conditions:
'
' The above copyright notice and this permission notice shall be included in all
' copies or SUBstantial portions of the Software.
'
' NOTE: 
' This is a legacy codebase maintained for educational purposes.
' While still functional on modern Windows systems, it uses the RapidQ framework
' which is no longer actively maintained.
' ****************************************************************************************************************************************************************

' Angle conversion
' DegToRad = ( PI / 180.0f ) * val
' RadToDeg = ( 180.0f / PI ) * val
' FIX      = str$(fix(numeric-expression))

SUB clear_field
    sol1.text = ""  : sol2.text = ""  : sol3.text = ""  : sol4.text = ""  : sol5.text = ""  : sol6.text = "" : sol7.text = "" : sol8.text ="" : sol9.text =""
    d1.text =""     : d2.text =""     : d3.text =""     : d4.text =""     : d5.text =""     : d6.text =""    : d7.text = ""   : d8.text =""
    dsol4.visible = 0 : sol4.visible = 0 : dsol4.caption = ""
ENd SUB

' Leg calculation

SUB leg_calc
    CALL clean_interface
    label.caption = "Flight leg :"
    dlab1.caption = "E.T.D :"
    dlab2.caption = "VAR :"
    dlab3.caption = "Dist :" 
    dlab4.caption = "W.velocity :"
    dlab5.caption = "W.direction :"
    dlab6.caption = "T.course :"
    dlab7.caption = "Burn :"
    dlab8.caption = "T.airspeed :"

    label.visible = 1
    dlab1.visible = 1 : d1.visible = 1
    dlab2.visible = 1 : d2.visible = 1
    dlab3.visible = 1 : d3.visible = 1
    dlab4.visible = 1 : d4.visible = 1
    dlab5.visible = 1 : d5.visible = 1
    dlab6.visible = 1 : d6.visible = 1
    dlab7.visible = 1 : d7.visible = 1
    dlab8.visible = 1 : d8.visible = 1

    dsol1.visible = 1 : sol1.visible = 1 : dsol1.caption = "T.heading :"
    dsol2.visible = 1 : sol2.visible = 1 : dsol2.caption = "M.heading :"
    dsol3.visible = 1 : sol3.visible = 1 : dsol3.caption = "Distance :"
    dsol4.visible = 1 : sol4.visible = 1 : dsol4.caption = "G.speed :"
    dsol5.visible = 1 : sol5.visible = 1 : dsol5.caption = "Fuel :"
    dsol6.visible = 1 : sol6.visible = 1 : dsol6.caption = "E.T.E :"
    dsol7.visible = 1 : sol7.visible = 1 : dsol7.caption = "E.T.A :"

    btn1.onclick = leg_SUB_calc
    btn2.onclick = clear_field
ENd SUB
 
SUB leg_SUB_calc
    etd        = val(d1.text) 
    var        = val(d2.text)
    dist       = val(d3.text)
    wv         = val(d4.text)
    wd         = val(d5.text)
    TC         = val(d6.text)
    burn       = val(d7.text)
    tas        = val(d8.text)
    '------------------------
    th   = tc+asin((wv/tas)*sin(wd-tc))
    mh   = th+var
    gs   = tas*cos(th-tc)-wv*cos(wd-tc)
    ete  = dist/gs
    fuel = burn*ete
    eta  = etd + ete
    sol1.text = bpo(th,ndec)
    sol2.text = bpo(mh,ndec)
    sol3.text = bpo(dist,ndec)
    sol4.text = bpo(gs,ndec)
    sol5.text = bpo(fuel,ndec)
    sol6.text = bpo(ete,ndec)
    sol7.text = bpo(eta,ndec)
ENd SUB

' True Heading
SUB th_calc
    CALL clean_interface
    label.caption = "True Heading :"
    dlab1.caption = "T.Course :" 
    dlab2.caption = "T.airspeed"
    dlab3.caption = "W.velocity"
    dlab4.caption = "W.Direction"
 
    label.visible = 1
    dlab1.visible = 1 : d1.visible = 1
    dlab2.visible = 1 : d2.visible = 1
    dlab3.visible = 1 : d3.visible = 1
    dlab4.visible = 1 : d4.visible = 1
    dsol1.visible = 1 : sol1.visible = 1 : dsol1.caption = "True heading :"

    btn1.onclick = th_SUB_calc
    btn2.onclick = clear_field
ENd SUB

SUB th_SUB_calc
    tc         = val(d1.text) 
    tas        = val(d2.text)
    wv         = val(d3.text)
    wd         = val(d4.text)
    th = tc+asin((wv/tas)*sin(wd-tc))
    sol1.text = bpo(th,ndec)
ENd SUB

' Magnetic Heading
SUB mh_calc
    CALL clean_interface
    label.caption = "Magnetic Heading :"
    dlab1.caption = "T.heading :" 
    dlab2.caption = "Var :"

    label.visible = 1
    dlab1.visible = 1 : d1.visible = 1
    dlab2.visible = 1 : d2.visible = 1
    dsol1.visible = 1 : sol1.visible = 1 : dsol1.caption = "M.heading :"

    btn1.onclick = mh_SUB_calc
    btn2.onclick = clear_field
ENd SUB

SUB mh_SUB_calc
    th      = val(d1.text)
    var     = val(d2.text) 
    mh = th + var
    sol1.text = bpo(mh,ndec)
ENd SUB

' Ground Speed

SUB gs_calc
    CALL clean_interface
    label.caption = "Ground Speed :"
    dlab1.caption = "T.heading :"
    dlab2.caption = "T.airspeed :"
    dlab3.caption = "T.course :"
    dlab4.caption = "W.direction :"
    dlab5.caption = "W.velocity :"
    label.visible = 1
    dlab1.visible = 1 : d1.visible = 1
    dlab2.visible = 1 : d2.visible = 1
    dlab3.visible = 1 : d3.visible = 1
    dlab4.visible = 1 : d4.visible = 1
    dlab5.visible = 1 : d5.visible = 1
    dsol1.visible = 1 : sol1.visible = 1 : dsol1.caption = "G.speed :"
    btn1.onclick = gs_SUB_calc
    btn2.onclick = clear_field
ENd SUB

SUB gs_SUB_calc
    th      = val(d1.text)
    tas     = val(d2.text)
    tc      = val(d3.text)
    wd      = val(d4.text)
    wv      = val(d5.text) 
    gs = tas*cos(th-tc)-wv*cos(wd-tc)
    sol1.text = bpo(gs,ndec)
ENd SUB

' Predicting freezing levels
SUB main_predic_gel
    CALL clean_interface
    label.caption = "Predicting freezing levels :"
    dlab1.caption = "Alt. (feet)  :" 
    dlab2.caption = "Temp (Celsius) :" 
    label.visible = 1
    dlab1.visible = 1 : d1.visible = 1
    dlab2.visible = 1 : d2.visible = 1
    dsol1.visible = 1 : sol1.visible = 1 : dsol1.caption = "Clear weather :"
    dsol2.visible = 1 : sol2.visible = 1 : dsol2.caption = "Clouds :"

    btn1.onclick = SUB_predic_gel
    btn2.onclick = clear_field
ENd SUB

SUB SUB_predic_gel
    dim df as double, wf as double, alt as double, temperature as double
    ALT         = val(d1.text) 
    Temperature = val(d2.text) 
    df = alt+1000*(temperature/2)
    wf = alt+1000*(temperature/1.5)
    sol1.text = bpo(df,ndec) + " Feet"
    sol2.text = bpo(wf,ndec) + " Feet"
ENd SUB

' Aviation winds
SUB main_wind
    CALL clean_interface
    label.caption = "Cross and tail wind :"
    dlab1.caption = "W.velocity :" 
    dlab2.caption = "W.direction :"
    dlab3.caption = "M.Heading :"
    dlab4.caption = "Var (+W -E):"
    label.visible = 1
    dlab1.visible = 1 : d1.visible = 1
    dlab2.visible = 1 : d2.visible = 1
    dlab3.visible = 1 : d3.visible = 1
    dlab4.visible = 1 : d4.visible = 1
    dsol1.visible = 1 : sol1.visible = 1 : dsol1.caption = "Crosswind :"
    dsol2.visible = 1 : sol2.visible = 1 : dsol2.caption = "Tailwind :"
    btn1.onclick = SUB_wind
    btn2.onclick = clear_field
ENd SUB

SUB SUB_wind
    dim tw as double , cw as double, vard as string

    wv   = val(d1.text) 
    wd   = val(d2.text)
    MH   = val(d3.text)
    var  = val(mid$(d4.text,2,2))
    vard = string(left$(d4.text,1))
    cw   = wv*sin(((wd-mh-var)*pi)/180)
    tw   = wv*cos(((wd-mh-var)*pi)/180)
    sol1.text = bpo(cw,ndec)
    sol2.text = bpo(tw,ndec)

    IF vard = ("-") then
        sol1.text = bpo(abs(cw),ndec) + " Right"
    ELSEIF vard = ("+") then
        sol1.text = bpo(abs(cw),ndec) + " Left"
    ELSEIF vard =("") then
        sol1.text = bpo(abs(cw),ndec) + " Right"
    ENd IF

    IF tw < 0 then
        sol2.text = bpo(abs(tw),ndec) + " Tail"
    ELSEIF tw > 0 then
        sol2.text = bpo(abs(tw),ndec) + " Head"
    ENd IF

ENd SUB

' Calculator
SUB calc
    IF fileexists ("c:\windows\system32\calc.exe") = False then
        run "c:\windows\calc.exe"
    else
        run "c:\windows\system32\calc.exe"
    ENd IF
ENd SUB

' Base converter
SUB base_conv
    call clean_interface
    label.caption = "Base converter :"
    dlab1.caption = "Value : "
    label.visible = 1
    dlab1.visible = 1  : d1.visible = 1
    dsol1.visible = 1 : sol1.visible = 1 : dsol1.caption = "Decimal :"
    dsol2.visible = 1 : sol2.visible = 1 : dsol2.caption = "Hexadecimal :"
    dsol3.visible = 1 : sol3.visible = 1 : dsol3.caption = "Binary :"
    dsol4.visible = 1 : sol4.visible = 1 : dsol4.caption = "Octal :"
    conv_base.visible = 1 : changes.visible = 1 : changes.caption = "Base :" 
    btn1.onclick = conv_item_base
    btn2.onclick = clear_field
ENd SUB

SUB conv_item_base
    Select Case conv_base.ItemIndex
        Case 0
            call conv_dec
        Case 1
            call conv_hexa
        Case 2
            call conv_bin
        Case 3
            call conv_oct
    ENd Select
ENd SUB

SUB conv_dec
    units     = val(d1.text)
    basex     = abs(units)
    sol1.text = str$(basex)
    sol2.text = convbase$(str$(basex),10,16)
    sol3.text = convbase$(str$(basex),10,2) 
    sol4.text = convbase$(str$(basex),10,8) 
ENd SUB

SUB conv_hexa
    base      = string(d1.text)
    sol1.text = convbase$(string(base),16,10) 
    sol2.text = string(base) 
    sol3.text = convbase$(string(base),16,2)
    sol4.text = convbase$(string(base),16,8)  
ENd SUB

SUB conv_bin
    units     = val(d1.text)
    basex     = abs(units)
    sol1.text = convbase$(str$(basex),2,10) 
    sol2.text = convbase$(str$(basex),2,16) 
    sol3.text = str$(basex)
    sol4.text = convbase$(str$(basex),2,8) 
ENd SUB

SUB conv_oct
    units     = val(d1.text)
    basex     = abs(units)
    sol1.text = convbase$(str$(basex),2,10) 
    sol2.text = convbase$(str$(basex),2,16)
    sol3.text = convbase$(str$(basex),2,8)  
    sol4.text = str$(basex)
ENd SUB

' Angle units conversion
SUB main_angles
    call clean_interface
    label.caption = "Angle units  :"
    dlab1.caption = "Value : "
    label.visible = 1
    dlab1.visible = 1  : d1.visible = 1
    dsol1.visible = 1  : sol1.visible = 1        : dsol1.caption = "Degree :"
    dsol2.visible = 1  : sol2.visible = 1        : dsol2.caption = "Radian :"
    conv_angles.visible = 1 : changes.visible = 1 : changes.caption = "Units :" 
    btn1.onclick = conv_item_angles
    btn2.onclick = clear_field
ENd SUB

SUB conv_item_angles
    Select Case conv_angles.ItemIndex
        Case 0
            call conv_degre
        Case 1
            call conv_radian
    ENd Select
ENd SUB

SUB conv_degre
    units     = val(d1.text)
    sol1.text = bpo(units,ndec)
    sol2.text = bpo(((pi/180)*units),ndec)
ENd SUB

SUB conv_radian
    units     = val(d1.text)
    sol1.text = bpo(((180/pi)*units),ndec)
    sol2.text = bpo(units,ndec)
ENd SUB

' Distance units conversion
SUB main_distances
    call clean_interface
    label.caption = "Length units :"
    dlab1.caption = "Value : "
    label.visible = 1
    dlab1.visible = 1 : d1.visible = 1
    dsol1.visible = 1 : sol1.visible = 1 : dsol1.caption = "Meter :"
    dsol2.visible = 1 : sol2.visible = 1 : dsol2.caption = "Kilometer :"
    dsol3.visible = 1 : sol3.visible = 1 : dsol3.caption = "Foot :"
    dsol4.visible = 1 : sol4.visible = 1 : dsol4.caption = "Inch :"
    dsol5.visible = 1 : sol5.visible = 1 : dsol5.caption = "Statute Mile :"
    dsol6.visible = 1 : sol6.visible = 1 : dsol6.caption = "Nautical Mile :"
    dsol7.visible = 1 : sol7.visible = 1 : dsol7.caption = "Yard :"
    conv_distances.visible = 1 : changes.visible = 1 : changes.caption = "Units :" 
    btn1.onclick = conv_item_distances
    btn2.onclick = clear_field
ENd SUB

SUB conv_item_distances
    Select Case conv_distances.ItemIndex
        Case 0
            call conv_metre
        Case 1
            call conv_kilometre
        Case 2
            call conv_foot
        Case 3
            call conv_inch
        Case 4
            call conv_smile
        Case 5
            call conv_nmile
        Case 6
            call conv_yards
    ENd Select
ENd SUB

SUB conv_metre
    units     = val(d1.text)
    sol1.text = bpo(units,ndec)
    sol2.text = bpo((units*0.001),ndec)
    sol3.text = bpo((units*3.280839),ndec)
    sol4.text = bpo((units*39.370078),ndec)
    sol5.text = bpo((units*0.000621371),ndec)
    sol6.text = bpo((units*0.000539957),ndec)
    sol7.text = bpo((units*1.093),ndec)
ENd SUB

SUB conv_kilometre
    units     = val(d1.text)
    sol1.text = bpo((units*1000),ndec)       
    sol2.text = bpo(units,ndec)
    sol3.text = bpo((units*3280.839895),ndec)
    sol4.text = bpo((units*39370.078740136),ndec)
    sol5.text = bpo((units*0.621371),ndec)
    sol6.text = bpo((units*0.539956),ndec)
    sol7.text = bpo((units*1093.61),ndec)
ENd SUB

SUB conv_foot
    units     = val(d1.text)
    sol1.text = bpo((units*0.3048),ndec)
    sol2.text = bpo((units*0.0003048),ndec)
    sol3.text = bpo(units,ndec)
    sol4.text = bpo((units*12),ndec)
    sol5.text = bpo((units*0.000189394),ndec)
    sol6.text = bpo((units*0.000164579),ndec)
    sol7.text = bpo((units*0.333),ndec)
ENd SUB

SUB conv_inch
    units     = val(d1.text)
    sol1.text = bpo((units*0.0254),ndec)
    sol2.text = bpo((units*0.0000254),ndec)
    sol3.text = bpo((units*0.083333333),ndec)
    sol4.text = bpo(units,ndec)
    sol5.text = bpo((units*0.000015783),ndec)
    sol6.text = bpo((units*0.000013715),ndec)
    sol7.text = bpo((units*0.02777),ndec)
ENd SUB

SUB conv_smile
    units     = val(d1.text)
    sol1.text = bpo((units*1609.344),ndec)
    sol2.text = bpo((units*1.609344),ndec)
    sol3.text = bpo((units*5280),ndec)
    sol4.text = bpo((units*63360),ndec)
    sol5.text = bpo(units,ndec)
    sol6.text = bpo((units*0.868976242),ndec)
    sol7.text = bpo((units*1760),ndec)
ENd SUB

SUB conv_nmile
    units     = val(d1.text)
    sol1.text = bpo((units*1852),ndec)
    sol2.text = bpo((units*1.852),ndec)
    sol3.text = bpo((units*6076.115485),ndec)
    sol4.text = bpo((units*72913.385826),ndec)
    sol5.text = bpo((units*1.150779),ndec)
    sol6.text = bpo(units,ndec)
    sol7.text = bpo((units*2025),ndec)
ENd SUB

SUB conv_yards
    units     = val(d1.text)
    sol1.text = bpo((units*0.9114),ndec)
    sol2.text = bpo((units*0.0009144),ndec)
    sol3.text = bpo((units*3),ndec)
    sol4.text = bpo((units*36),ndec)
    sol5.text = bpo((units*0.000568182),ndec)
    sol6.text = bpo((units*0.000493737),ndec)
    sol7.text = bpo(units,ndec)
ENd SUB

' Mass units conversion
SUB main_poids
    call clean_interface
    label.caption = "Mass units :"
    dlab1.caption = "Value : "
    label.visible = 1
    dlab1.visible = 1  : d1.visible = 1
    dsol1.visible = 1 : sol1.visible = 1 : dsol1.caption = "KG :"
    dsol2.visible = 1 : sol2.visible = 1 : dsol2.caption = "Pound :"
    conv_poids.visible = 1 : changes.visible = 1 : changes.caption = "Units :" 

    btn1.onclick = conv_item_poids
    btn2.onclick = clear_field
ENd SUB

SUB conv_item_poids
    Select Case conv_poids.ItemIndex
        Case 0
            call conv_kg
        Case 1
            call conv_pound
    ENd Select
ENd SUB

SUB conv_kg
    units    = val(d1.text)
    sol1.text = bpo(units,ndec)
    sol2.text = bpo((units/0.453592370),ndec)
ENd SUB

SUB conv_pound
    units    = val(d1.text)
    sol1.text = bpo((units*0.453592370),ndec)
    sol2.text = bpo(units,ndec)
ENd SUB

' Temperature units conversion
SUB main_temp
    call clean_interface
    label.caption = "Temperature units :"
    dlab1.caption = "Value : "
    label.visible = 1
    dlab1.visible = 1  : d1.visible = 1
    dsol1.visible = 1 : sol1.visible = 1 : dsol1.caption = "Celsius :"
    dsol2.visible = 1 : sol2.visible = 1 : dsol2.caption = "Fahrenheit :"
    dsol3.visible = 1 : sol3.visible = 1 : dsol3.caption = "Kelvin :"
    conv_temp.visible = 1 : changes.visible = 1 : changes.caption = "Units :" 

    btn1.onclick = conv_item_temp
    btn2.onclick = clear_field
ENd SUB

SUB conv_item_temp
    Select Case conv_temp.ItemIndex
        Case 0
            call conv_degrec
        Case 1
            call conv_degref
        Case 2
            Call conv_kelvin
    ENd Select
ENd SUB

SUB conv_degrec
    units     = val(d1.text)
    sol1.text = bpo(units,ndec)
    sol2.text = bpo((((units*9/5)+32)),ndec)
    sol3.text = bpo((units+273),ndec)
ENd SUB

SUB conv_degref
    units     = val(d1.text)
    sol1.text = bpo((((units-32)*5/9)),ndec)
    sol2.text = bpo(units,ndec)
    sol3.text = bpo((((units-32)*5/9)+273),ndec)
ENd SUB

SUB conv_kelvin
    units     = val(d1.text)
    sol1.text = bpo((units-273),ndec)
    sol2.text = bpo(((((units-273)*9/5)+32)),ndec)
    sol3.text = bpo(units,ndec)
ENd SUB

' Flow units conversion
SUB main_liquide
    call clean_interface
    label.caption = "Flow units"
    dlab1.caption = "Value : "
    label.visible = 1
    dlab1.visible = 1  : d1.visible = 1
    dsol1.visible = 1 : sol1.visible = 1 : dsol1.caption = "Liter :"
    dsol2.visible = 1 : sol2.visible = 1 : dsol2.caption = "Gallon US :"
    dsol3.visible = 1 : sol3.visible = 1 : dsol3.caption = "Gallon UK :"
    dsol4.visible = 1 : sol4.visible = 1 : dsol4.caption = "KG :"
    dsol5.visible = 1 : sol5.visible = 1 : dsol5.caption = "Pound :"
    conv_liquide.visible = 1 : changes.visible = 1 : changes.caption = "Units :" 
    btn1.onclick = conv_item_liquide
    btn2.onclick = clear_field
ENd SUB

SUB conv_item_liquide
    Select Case conv_liquide.ItemIndex
        Case 0
            call conv_litre
        Case 1
            call conv_gallonus
        Case 2
            call conv_gallonuk
    ENd Select
ENd SUB

SUB conv_litre
    units     = val(d1.text)
    sol1.text = bpo(units,ndec)
    sol2.text = bpo((units*0.26417),ndec)
    sol3.text = bpo((units*0.21996),ndec)
    sol4.text = bpo((units*0.72),ndec)
    sol5.text = bpo(((units*0.72)/0.453592370),ndec)
ENd SUB

SUB conv_gallonus
    units     = val(d1.text)
    sol1.text = bpo((units*3.785411784),ndec)
    sol2.text = bpo(units,ndec)
    sol3.text = bpo((units*0.83267),ndec)
    sol4.text = bpo(((units*3.785411784)*0.72),ndec)
    sol5.text = bpo((((units*3.785411784)*0.72)/0.453592370),ndec)

ENd SUB

SUB conv_gallonuk
    units     = val(d1.text)
    sol1.text = bpo((units*4.54),ndec)
    sol2.text = bpo((units*1.2),ndec)
    sol3.text = bpo(units,ndec)
    sol4.text = bpo(((units*4.54)*0.74),ndec)
    sol5.text = bpo((((units*4.54)*0.74)/0.453592370),ndec)
ENd SUB

' Pressure units conversion
SUB main_pressure
    call clean_interface
    label.caption = "Pressure units :"
    dlab1.caption = "Value :"
    label.visible = 1
    dlab1.visible = 1 : d1.visible = 1
    dsol1.visible = 1 : sol1.visible = 1 : dsol1.caption = "ATM :"
    dsol2.visible = 1 : sol2.visible = 1 : dsol2.caption = "BAR :"
    dsol3.visible = 1 : sol3.visible = 1 : dsol3.caption = "Millibar :"
    dsol4.visible = 1 : sol4.visible = 1 : dsol4.caption = "PSI :"
    conv_pressure.visible = 1 : changes.visible = 1 : changes.caption = "Units :" 

    btn1.onclick = conv_item_pressure
    btn2.onclick = clear_field
ENd SUB

SUB conv_item_pressure
    Select Case conv_pressure.ItemIndex
        Case 0
            call conv_atm
        Case 1
            call conv_bar
        Case 2
            call conv_millibar
        Case 3
            call conv_psi
    ENd Select
ENd SUB

SUB conv_atm
    units     = val(d1.text)
    sol1.text = bpo(units,ndec)
    sol2.text = bpo((units*1.01325),ndec)
    sol3.text = bpo((units*1013.25),ndec)
    sol4.text = bpo((units*14.695948775),ndec)
ENd SUB

SUB conv_bar
    units     = val(d1.text)
    sol1.text = bpo((units*0.986923267),ndec)
    sol2.text = bpo(units,ndec)
    sol3.text = bpo((units*1000),ndec)
    sol4.text = bpo((units*14.503773773),ndec)
ENd SUB

SUB conv_millibar
    units     = val(d1.text)
    sol1.text = bpo((units*0.000986923),ndec)
    sol2.text = bpo((units*0.001),ndec)
    sol3.text = bpo(units,ndec)
    sol4.text = bpo((units*0.014503774),ndec)
ENd SUB

SUB conv_psi
    units     = val(d1.text)
    sol1.text = bpo((units*0.068045964),ndec)
    sol2.text = bpo((units*0.068947573),ndec)
    sol3.text = bpo((units*68.947572932),ndec)
    sol4.text = bpo(units,ndec)
ENd SUB

' Power units conversion
SUB main_charge
    call clean_interface
    label.caption = "Power units :"
    dlab1.caption = "Value : "
    label.visible = 1
    dlab1.visible = 1  : d1.visible = 1
    dsol1.visible = 1 : sol1.visible = 1 : dsol1.caption = "Watt :"
    dsol2.visible = 1 : sol2.visible = 1 : dsol2.caption = "Kilowatt :"
    dsol3.visible = 1 : sol3.visible = 1 : dsol3.caption = "Horsepower :"
    dsol4.visible = 1 : sol4.visible = 1 : dsol4.caption = "BTU/m :"
    conv_charge.visible = 1 : changes.visible = 1 : changes.caption = "Units :" 
    btn1.onclick = conv_item_charge
    btn2.onclick = clear_field
ENd SUB

SUB conv_item_charge
    Select Case conv_charge.ItemIndex
        Case 0
            call conv_watt
        Case 1
            call conv_kwatt
        Case 2
            call conv_horse
        Case 3
            call conv_btu
    ENd Select
ENd SUB

SUB conv_watt
    units     = val(d1.text)
    sol1.text = bpo(units,ndec)
    sol2.text = bpo((units*0.001),ndec)
    sol3.text = bpo((units*0.001341022),ndec)
    sol4.text = bpo((units*0.056868270),ndec)
ENd SUB

SUB conv_kwatt
    sol1.text = bpo((units*1000),ndec)
    sol2.text = bpo(units,ndec)
    sol3.text = bpo((units*1.341022090),ndec)
    sol4.text = bpo((units*56.868270001),ndec)
ENd SUB

SUB conv_horse
    sol1.text = bpo((units*745.699871580),ndec)
    sol2.text = bpo((units*0.745699872),ndec)
    sol3.text = bpo(units,ndec)
    sol4.text = bpo((units*42.406661637),ndec)
ENd SUB

SUB conv_btu
    sol1.text = bpo((units*17.584498350),ndec)
    sol2.text = bpo((units*0.017584498),ndec)
    sol3.text = bpo((units*0.023581201),ndec)
    sol4.text = bpo(units,ndec)
ENd SUB

' Speed units conversion
SUB main_speeds
    call clean_interface
    label.caption = "Speed units :"
    dlab1.caption = "Value : "
    label.visible = 1
    dlab1.visible = 1  : d1.visible = 1
    dsol1.visible = 1  : sol1.visible = 1 : dsol1.caption = "M/s :"
    dsol2.visible = 1  : sol2.visible = 1 : dsol2.caption = "Km/h :"
    dsol3.visible = 1  : sol3.visible = 1 : dsol3.caption = "Mach/h :"
    dsol4.visible = 1  : sol4.visible = 1 : dsol4.caption = "Knot/h :"
    dsol5.visible = 1  : sol5.visible = 1 : dsol5.caption = "Mile/h :"
    dsol6.visible = 1  : sol6.visible = 1 : dsol6.caption = "Pied/m :"
    conv_speeds.visible = 1 : changes.visible = 1 : changes.caption = "Units :" 
    btn1.onclick = conv_item_speeds
    btn2.onclick = clear_field
ENd SUB

SUB conv_item_speeds
    Select Case conv_speeds.ItemIndex
        Case 0
            call conv_ms
        Case 1
            call conv_kmh
        Case 2
            call conv_mach
        Case 3
            call conv_knoth
        Case 4 
            call conv_mileh
        Case 5
            call conv_pied
    ENd Select
ENd SUB

SUB conv_ms
    units     = val(d1.text)
    sol1.text = bpo(units,ndec)
    sol2.text = bpo((units*3.6),ndec)
    sol3.text = bpo((units*0.003),ndec)
    sol4.text = bpo((units*1.943),ndec)
    sol5.text = bpo((units*2.236),ndec)
    sol6.text = bpo((units*196.850),ndec)
ENd SUB

SUB conv_kmh
    units    = val(d1.text)
    sol1.text = bpo((units*0.277778),ndec)
    sol2.text = bpo(units,ndec)
    sol3.text = bpo((units*0.0008380431358),ndec)
    sol4.text = bpo((units*0.5399568035),ndec)
    sol5.text = bpo((units*0.6213711922),ndec)
    sol6.text = bpo((units*54.680664917),ndec)
ENd SUB

SUB conv_mach
    units     = val(d1.text)
    sol1.text = bpo((units*331.46),ndec)
    sol2.text = bpo((units*1193.256),ndec)
    sol3.text = bpo(units,ndec)
    sol4.text = bpo((units*644.3066955),ndec)
    sol5.text = bpo((units*741.4549034),ndec)
    sol6.text = bpo((units*65248.031496001),ndec)
ENd SUB

SUB conv_knoth
    units     = val(d1.text)
    sol1.text = bpo((units*0.5144444444),ndec)
    sol2.text = bpo((units*1.852),ndec)
    sol3.text = bpo((units*0.001552055887),ndec)
    sol4.text = bpo(units,ndec)
    sol5.text = bpo((units*1.150779448),ndec)
    sol6.text = bpo((units*101.268591426),ndec)
ENd SUB

SUB conv_mileh
    units     = val(d1.text)
    sol1.text = bpo((units*0.44704),ndec)
    sol2.text = bpo((units*1.609344),ndec)
    sol3.text = bpo((units*0.001348700),ndec)
    sol4.text = bpo((units*0.868976242),ndec)
    sol5.text = bpo(units,ndec)
    sol6.text = bpo((units*88),ndec)
ENd SUB

SUB conv_pied
    units     = val(d1.text)
    sol1.text = bpo((units*0.00508),ndec)
    sol2.text = bpo((units*0.018288),ndec)
    sol3.text = bpo((units*0.000015326),ndec)
    sol4.text = bpo((units*0.009874730),ndec)
    sol5.text = bpo((units*0.000493737),ndec)
    sol6.text = bpo(units,ndec)
ENd SUB

' Currency conversion
SUB main_conv_change
    CALL clean_interface
    label.caption = "Currency conversion :"
    dlab1.caption = "Value :"
    label.visible = 1
    dlab1.visible = 1 : d1.visible = 1
    dsol1.visible = 1 : sol1.visible = 1 : dsol1.caption = "German Mark :"
    dsol2.visible = 1 : sol2.visible = 1 : dsol2.caption = "Euro :"
    dsol3.visible = 1 : sol3.visible = 1 : dsol3.caption = "Belgian Franc :"
    dsol4.visible = 1 : sol4.visible = 1 : dsol4.caption = "French Franc :"
    dsol5.visible = 1 : sol5.visible = 1 : dsol5.caption = "Italian Lira :"
    dsol6.visible = 1 : sol6.visible = 1 : dsol6.caption = "British Pound :"
    dsol7.visible = 1 : sol7.visible = 1 : dsol7.caption = "US Dollar :"
    dsol8.visible = 1 : sol8.visible = 1 : dsol8.caption = "Canadian Dollar :"
    dsol9.visible = 1 : sol9.visible = 1 : dsol9.caption = "Czech Koruna :"

    conv_devise.visible = 1 : changes.visible = 1 : changes.caption = "Currency :"
    btn1.onclick = conv_item
    btn2.onclick = clear_field
ENd SUB

SUB conv_item
    Select Case conv_devise.ItemIndex
        Case 0
            call conv_fb
        Case 1
            call conv_ff
        Case 2
            call conv_dm
        Case 3
            call conv_euro
        Case 4
            call conv_lire
        Case 5 
            call conv_livre
        Case 6
            call conv_us
        Case 7
            call conv_ca
        Case 8 
            call conv_cz
    ENd Select
ENd SUB

SUB conv_fb
    somme     = val(d1.text)
    sol1.text = bpo(((t_dm/t_fb)*somme),ndec)
    sol2.text = bpo(((t_euro/t_fb)*somme),ndec)
    sol3.text = bpo(somme,ndec)
    sol4.text = bpo(((t_ff/t_fb)*somme),ndec)
    sol5.text = bpo(((t_lire/t_fb)*somme),ndec)
    sol6.text = bpo(((t_livre/t_fb)*somme),ndec)
    sol7.text = bpo(((t_us/t_fb)*somme),ndec)
    sol8.text = bpo(((t_ca/t_fb)*somme),ndec)
    sol9.text = bpo(((t_cz/t_fb)*somme),ndec)
ENd SUB

SUB conv_ff
    somme     = val(d1.text)
    sol1.text = bpo(((t_dm/t_ff)*somme),ndec) 
    sol2.text = bpo(((t_euro/t_ff)*somme),ndec)
    sol3.text = bpo(((t_fb/t_ff)*somme),ndec)
    sol4.text = bpo(somme,ndec)
    sol5.text = bpo(((t_lire/t_ff)*somme),ndec)
    sol6.text = bpo(((t_livre/t_ff)*somme),ndec)
    sol7.text = bpo(((t_us/t_ff)*somme),ndec)
    sol8.text = bpo(((t_ca/t_ff)*somme),ndec)
    sol9.text = bpo(((t_cz/t_ff)*somme),ndec)
ENd SUB

SUB conv_dm
    somme     = val(d1.text)
    sol1.text = bpo(somme,ndec) 
    sol2.text = bpo(((t_euro/t_dm)*somme),ndec)
    sol3.text = bpo(((t_fb/t_dm)*somme),ndec)
    sol4.text = bpo(((t_ff/t_dm)*somme),ndec)
    sol5.text = bpo(((t_lire/t_dm)*somme),ndec)
    sol6.text = bpo(((t_livre/t_dm)*somme),ndec)
    sol7.text = bpo(((t_us/t_dm)*somme),ndec)
    sol8.text = bpo(((t_ca/t_dm)*somme),ndec)
    sol9.text = bpo(((t_cz/t_dm)*somme),ndec)
ENd SUB

SUB conv_euro
    somme     = val(d1.text)
    sol1.text = bpo(((t_dm/t_euro)*somme),ndec) 
    sol2.text = bpo(somme,ndec)
    sol3.text = bpo(((t_fb/t_euro)*somme),ndec)
    sol4.text = bpo(((t_ff/t_euro)*somme),ndec)
    sol5.text = bpo(((t_lire/t_euro)*somme),ndec)
    sol6.text = bpo(((t_livre/t_euro)*somme),ndec)
    sol7.text = bpo(((t_us/t_euro)*somme),ndec)
    sol8.text = bpo(((t_ca/t_euro)*somme),ndec)
    sol9.text = bpo(((t_cz/t_euro)*somme),ndec)
ENd SUB

SUB conv_lire
    somme     = val(d1.text)
    sol1.text = bpo(((t_dm/t_lire)*somme),ndec) 
    sol2.text = bpo(((t_euro/t_lire)*somme),ndec)
    sol3.text = bpo(((t_fb/t_lire)*somme),ndec)
    sol4.text = bpo(((t_ff/t_lire)*somme),ndec)
    sol5.text = bpo(somme,ndec)
    sol6.text = bpo(((t_livre/t_lire)*somme),ndec)
    sol7.text = bpo(((t_us/t_lire)*somme),ndec)
    sol8.text = bpo(((t_ca/t_lire)*somme),ndec)
    sol9.text = bpo(((t_cz/t_lire)*somme),ndec)
ENd SUB

SUB conv_livre
    somme     = val(d1.text)
    sol1.text = bpo(((t_dm/t_livre)*somme),ndec) 
    sol2.text = bpo(((t_euro/t_livre)*somme),ndec)
    sol3.text = bpo(((t_fb/t_livre)*somme),ndec)
    sol4.text = bpo(((t_ff/t_livre)*somme),ndec)
    sol5.text = bpo(((t_lire/t_livre)*somme),ndec)
    sol6.text = bpo(somme,ndec)
    sol7.text = bpo(((t_us/t_livre)*somme),ndec)
    sol8.text = bpo(((t_ca/t_livre)*somme),ndec)
    sol9.text = bpo(((t_cz/t_livre)*somme),ndec)
ENd SUB

SUB conv_us
    somme     = val(d1.text)
    sol1.text = bpo(((t_dm/t_us)*somme),ndec)
    sol2.text = bpo(((t_euro/t_us)*somme),ndec)
    sol3.text = bpo(((t_fb/t_us)*somme),ndec)
    sol4.text = bpo(((t_ff/t_us)*somme),ndec)
    sol5.text = bpo(((t_lire/t_us)*somme),ndec)
    sol6.text = bpo(((t_livre/t_us)*somme),ndec)
    sol7.text = bpo(somme,ndec)
    sol8.text = bpo(((t_ca/t_us)*somme),ndec)
    sol9.text = bpo(((t_cz/t_us)*somme),ndec)
ENd SUB

SUB conv_ca
    somme     = val(d1.text)
    sol1.text = bpo(((t_dm/t_ca)*somme),ndec) 
    sol2.text = bpo(((t_euro/t_ca)*somme),ndec)
    sol3.text = bpo(((t_fb/t_ca)*somme),ndec)
    sol4.text = bpo(((t_ff/t_ca)*somme),ndec)
    sol5.text = bpo(((t_lire/t_ca)*somme),ndec)
    sol6.text = bpo(((t_livre/t_ca)*somme),ndec)
    sol7.text = bpo(((t_us/t_ca)*somme),ndec)
    sol8.text = bpo(somme,ndec)
    sol9.text = bpo(((t_cz/t_ca)*somme),ndec)
ENd SUB

SUB conv_cz
    somme     = val(d1.text)
    sol1.text = bpo(((t_dm/t_cz)*somme),ndec) 
    sol2.text = bpo(((t_euro/t_cz)*somme),ndec)
    sol3.text = bpo(((t_fb/t_cz)*somme),ndec)
    sol4.text = bpo(((t_ff/t_cz)*somme),ndec)
    sol5.text = bpo(((t_lire/t_cz)*somme),ndec)
    sol6.text = bpo(((t_livre/t_cz)*somme),ndec)
    sol7.text = bpo(((t_us/t_cz)*somme),ndec)
    sol8.text = bpo(((t_ca/t_cz)*somme),ndec)
    sol9.text = bpo(somme,ndec)
ENd SUB
' ENd of file (don't modIFy this file !)