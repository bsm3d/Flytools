' **************************************************************
' FlyTools - Version 1.6.1
' Code by Benoit (BSM3D) Saint-Moulin
' Last tested: 08/01/2025 on Windows 10 x64 (2025)
' Language: RapidQ (Basic) Framework
' Initial Release: 04/01/2000
' This is a 25th Anniversary re-issue release for educational and learning purposes
'
' This code has no pretension - it was CREATEd in the 2000s
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
' to use, copy, modIFy, merge, publish, distribute, sublicense, and/or sell
' copies of the Software, and to permit persons to whom the Software is
' furnished to do so, subject to the following conditions:
'
' The above copyright notice and this permission notice shall be included in all
' copies or substantial portions of the Software.
'
' NOTE: 
' This is a legacy codebase maintained for educational purposes.
' While still FUNCTIONal on modern Windows systems, it uses the RapidQ framework
' which is no longer actively maintained.
' ****************************************************************************************************************************************************************

'CREATE Fonts
  CREATE F_print12  as qfont : name = "Arial"  : size = 12                                     : END CREATE
  CREATE F_print10  as qfont : name = "Arial"  : size = 10                                     : END CREATE
  CREATE F_print9   as qfont : name = "Arial"  : size = 9                                      : END CREATE
  CREATE font4      as qfont : name = "Arial"  : size = 9                                      : END CREATE
  CREATE font5      as qfont :                 : size = 9  : color = &hffffff                  : END CREATE
  CREATE font_intro as qfont :                 : size = 10 : addstyles = fsBold : color = &hffffff                  : END CREATE
  CREATE F_jaune    as qfont :                 : size = 9  : addstyles = 2 : color = &h33eeff  : END CREATE
  CREATE F_rouge    as qfont :                 : size = 9  : color = &h33eeff                  : END CREATE
  CREATE F_vert     as qfont :                 : size = 9  : color = &h00ff00                  : END CREATE

' Display Date
  Declare FUNCTION MonthName (month%) as String
  dim mdy$ as string,  m2$ as string , mn2$ as string

  mdy$ = monthname (Val(left$(DATE$,2)))
  mdy$ = mdy$ + " " + mid$(DATE$,4,2) 
  mdy$ = mdy$ + ", "+ RIGHT$(DATE$, 4)

  FUNCTION MonthName (month%) as String
    m2$ = "January   February  March     April     "
    m2$ = m2$ + "May       June      July      August    "
    m2$ = m2$ + "September October   November  December  "
    mn2$ = Mid$(m2$, (month% - 1) * 10 + 1, 10)
    mn2$ = RTrim$(mn2$)
  MonthName = mn2$
  END FUNCTION

'Display hours
  Declare FUNCTION times (hrs%, min%) as String
  Declare SUB QTimer1

  dim hrs% as integer, min% as integer, temp% as integer
  dim min$ as string 

    CREATE Timer1 as QTimer
      Interval=500
      Enabled=1
      OnTimer=QTimer1 
    END CREATE

  FUNCTION times (hrs%,min%)
      min$ = ":" + Str$(min%)      
  IF hrs% > 24 then
      hrs% = hrs% - 24
  END IF 
  IF min% < 10 then
      min$ = ":0" + str$(min%)  
  END IF   
      Times = str$(hrs%) + min$
      'Times = str$(hrs%-Tzone) + min$
  END FUNCTION

'Masking Decimal
Declare FUNCTION bpo(bsm as double, bpovar as integer) as string

  FUNCTION bpo(bsm as double, bpovar as integer) as string
  dim s as string
  dim posi as integer
  s=str$(bsm)
  posi=instr(s,".")
  IF posi = 0 then
    bpo = s
  ELSEIF(len(s)<posi+bpovar) then
    bpo =s
  else
  bpo = left$(s,posi+bpovar)
  END IF
  END FUNCTION