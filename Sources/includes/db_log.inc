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

' Create the main logbook form
CREATE logbook AS QForm
  Height  = 400
  Width   = 650
  Borderstyle = 4
  center  
  Caption     = "Favorites Flight LogBook : " + aero_edt
  
  ' Create the popup menu for the logbook
  CREATE pop_menu_log    as qpopupmenu
      CREATE help_log    as qmenuitem :Caption ="Help"                : shortcut = "F1"    : OnClick=help           :END CREATE
      CREATE calc_log    as qmenuitem :caption ="Calculator"          : shortcut = "F2"    : onclick=calc           :END CREATE
      CREATE prefs_log   as qmenuitem :Caption ="Prefs"               : shortcut = "F3"    : OnClick=main_prefs     :END CREATE
      CREATE air_launch  as qmenuitem :caption ="Airfield"            : shortcut = "F4"    : onclick=air_db         :END CREATE
      CREATE log_sep0    as qmenuitem : caption = "-"                 : END CREATE
      CREATE quit_log    as qmenuitem :Caption ="Close Database"      : shortcut = "Esc"   : OnClick=log_close      :END CREATE
  END CREATE 
  Popupmenu = pop_menu_log
  
  ' Create the main menu for the logbook
  CREATE MainMenu_log AS QMainMenu
     CREATE FileMenu_log    as QMenuItem:Caption   = "&File"
     CREATE OpenItem_log    AS QMenuItem:Caption   = "Open"   :shortcut = "ctrl+o" : OnClick = OpenClick_log    :END CREATE
     CREATE SaveItem_log    AS QMenuItem:Caption   = "Save"   :shortcut = "ctrl+s" : OnClick = SaveClick_log    :END CREATE
     CREATE SaveAsItem_log  AS QMenuItem:Caption   = "Save As":                    OnClick = SaveAsClick_log    :END CREATE
     CREATE log_sep1        as qmenuitem : caption = "-"      : END CREATE
     CREATE ExitItem_log    AS QMenuItem:Caption   = "Close"   :shortcut = "Esc" : OnClick = Log_close          :END CREATE
  END CREATE
END CREATE
  
  ' Create the status bar for the logbook
  CREATE StatusBar_log AS QStatusBar
      sizegrip = 0
      AddPanels "Items: 0","Search result: 0","Ready!"
      Panel(0).Width = 120
      Panel(1).Width = 150
  END CREATE
  
  ' Create the tab control for the logbook
  CREATE Tab_log AS QTabControl
    Width    = logbook.ClientWidth
    Height   = logbook.ClientHeight-20
    
    ' Main Panel
    CREATE Panel02 AS QPanel
      Top =5
      Left=5
      Width =tab_log.ClientWidth-10
      Height=tab_log.ClientHeight-10
      Visible=True
      bevelouter = 1
      ' Create toolbar image
      CREATE bar_log as qimage : top = 1 : left = 1 : width = 631 : height = 29 : bmphandle = toolbar : END CREATE
      
      ' Create buttons for various actions
      CREATE close_log_db as qcoolbtn
      Left    = 10
      Top     = 3
      width   = 27
      height  = 26
      flat    = 1
      layout  = 1
      bmphandle = bexit
      cursor  = hand
      hint = "Close LogBook database." : showhint = shint
      OnClick=log_close
      END CREATE
      
      CREATE open_log_db as qcoolbtn
      Left    = 40
      Top     = 3
      width   = 27
      height  = 26
      flat    = 1
      layout  = 1
      bmphandle = bopen
      cursor  = hand
      hint = "Open database." : showhint = shint
      OnClick =openclick_log
      END CREATE
      
      CREATE save_log_db as qcoolbtn
      Left    = 70
      Top     = 3
      width   = 27
      height  = 26
      flat    = 1
      layout  = 1
      bmphandle = bsave
      cursor  = hand
      hint = "Save Database." : showhint = shint
      OnClick =saveclick_log
      END CREATE
      
      CREATE add_log as qcoolbtn
      Left    = 100
      Top     = 3
      width   = 27
      height  = 26
      flat    = 1
      layout  = 1
      bmphandle = badd
      cursor  = hand
      hint = "ADD new filed to Database" : showhint = shint
      OnClick =add_entry_log
      END CREATE
      
      CREATE del_log as qcoolbtn
      Left    = 130
      Top     = 3
      width   = 27
      height  = 26
      flat    = 1
      layout  = 1
      bmphandle = brem
      cursor  = hand
      hint = "DEL last record from Database" : showhint = shint
      OnClick =del_entry_log
      END CREATE
      
      CREATE find_log as qcoolbtn
      Left    = 160
      Top     = 3
      width   = 27
      height  = 26
      flat    = 1
      layout  = 1
      bmphandle = bsearch
      cursor  = hand
      hint = "Search field from Database" : showhint = shint
      OnClick = b_search_log
      END CREATE
      
      ' Create label for database name
      CREATE whois2 as qlabel
      left = 190
      top  = 10
      transparent = 1
      caption = "DataBase : "
      END CREATE
      
      ' Create help button
      CREATE log_help as qcoolbtn : top = 3   : left = 605  : width = 27 : height = 26 : flat = 1 : layout = 1  : bmphandle = bhelp : cursor = hand : onclick = help : hint = "Display Helps." : showhint = shint :  END CREATE
            
      ' Create the main logbook grid
      CREATE mlv_log AS QStringGrid
      parent = panel02
      Width  = Panel02.ClientWidth
      Height = Panel02.ClientHeight-29
      Top= 29
      cell(0,0)="Date" : cell(1,0)="Pilot" : cell(2,0)="Aircraft" : cell(3,0)="TakeOff" : cell(4,0)="Landing": cell(5,0)="Time" : cell(6,0)="Fuel" :fixedcols=0        
      DefaultRowHeight=18
      addoptions goediting
      colcount =7
      rowcount=2
      colwidths(0) = 65
      colwidths(1) = 110
      colwidths(2) = 100
      colwidths(3) = 100
      colwidths(4) = 100
      colwidths(5) = 65
      colwidths(6) = 65
      END CREATE
    END CREATE
    
    ' Search Panel
    CREATE Panel12 AS QPanel
      Top =5
      Left=5
      Width =tab_log.ClientWidth-10
      Height=tab_log.ClientHeight-10
      Visible=False
      bevelouter = 1
      ' Create toolbar image
      CREATE bar_log2 as qimage : top = 1 : left = 1 : width = 631 : height = 29 : bmphandle = toolbar : END CREATE
      
      ' Create button to return to main database
      CREATE main_field_log as qcoolbtn
      Left    = 10
      Top     = 3
      width   = 27
      height  = 26
      flat    = 1
      layout  = 1
      bmphandle = bdb
      cursor  = hand
      hint = "Return to Database." : showhint = shint
      OnClick =b_main_log
      END CREATE
     
     ' Create search input and options
     CREATE sll2 as qlabel   :Parent  = panel12 :Top  = 8   :Left = 40 : caption="String :" :END CREATE
     CREATE SEdit2 As QEdit  :Parent  = panel12 :Left = 75  :Width = 130 : Top = 5: onkeypress=Searchlog :END CREATE
     
     CREATE scheck2 as qcheckbox     : left= 210 : top = 6   : width = 15     : END CREATE
     CREATE schek2_lab as qlabel     : caption = "Exact"     :transparent = 1 : left = 225 : top = 8 : width = 50 : END CREATE 

     CREATE sall2   as qcoolbtn      : layout = 1: flat = 1   :left= 260 :top = 3  :width = 27 : height = 26 :bmphandle = ball : cursor = hand :hint = "Check all search methods" : showhint = shint : onclick=Sselectall_log :END CREATE
     
     CREATE sdate   as qcheckbox     :left =295  : top=6  :width = 15 :Checked=True : END CREATE
     CREATE sdate_lab as qlabel      :left =310  : caption = "Date"   :transparent = 1 :top = 8 : width = 50 : END CREATE 

     CREATE spilot   as qcheckbox    :left =340  : top=6  :width = 15 :Checked=True : END CREATE
     CREATE spilot_lab as qlabel     :left =355  : caption = "Pilot"    :transparent = 1 : top = 8 : width = 50 : END CREATE 

     CREATE saircraft as qcheckbox   :left =385 : top=6  :width = 15 :Checked=True : END CREATE
     CREATE saircraft_lab as qlabel  :left =400 : caption = "Aircraft" :transparent = 1 : top = 8 : width = 50 : END CREATE 

     CREATE sTakeoff as qcheckbox    :left =440 : top=6  :width = 15 :Checked=True : END CREATE
     CREATE stakeoff_lab as qlabel   :left =455 : caption = "Takeoff"  :transparent = 1 : top = 8 : width = 50 : END CREATE 

     CREATE slanding as qcheckbox    :left =500 : top=6  :width = 15 :Checked=True : END CREATE
     CREATE slanding_lab as qlabel   :left =515 : caption = "Landing"  :transparent = 1 : top = 8 : width = 50 : END CREATE 

     ' Create help button
     CREATE log_search_help as qcoolbtn : top = 3   : left = 605  : width = 27 : height = 26 : flat = 1 : layout = 1  : bmphandle = bhelp : cursor = hand : onclick = help : hint = "Display Helps." : showhint = shint :  END CREATE

     ' Create the search results grid
     CREATE slv_log AS QStringGrid
      Parent  = Panel12
      Width   = Panel12.ClientWidth
      Height  = Panel12.ClientHeight-29
      Top=29
      cell(0,0)="Date" : cell(1,0)="Pilot" : cell(2,0)="Aircraft" : cell(3,0)="TakeOff" : cell(4,0)="Landing": cell(5,0)="Time" : cell(6,0)="Fuel" :fixedcols=0 
      DefaultRowHeight=18
      addoptions 5
      rowcount=2
      Colcount=7
      colwidths(0) = 65
      colwidths(1) = 110
      colwidths(2) = 100
      colwidths(3) = 100
      colwidths(4) = 100
      colwidths(5) = 65
      colwidths(6) = 65
     END CREATE

    END CREATE
END CREATE
END CREATE

' Switch to search panel
SUB b_search_log
  Panel02.Visible=False
  Panel12.Visible=True
END SUB

' Switch to main panel
SUB b_main_log
  Panel02.Visible=true
  Panel12.Visible=false
END SUB

' Search Routines
SUB Searchlog
 IF chr$(key)=chr$(13) then
  disablefunc_log
  dim i as integer,a as integer,ii as integer,a$ as string,b$ as string
  b$=lcase$(SEdit2.Text)
  slv_log.rowcount=2:sli_log=1
  For i=0 to 6
  slv_log.cell(i,1)=""
  next i
   for a=1 to mlv_log.rowcount-1
    For ii=0 to 6
     IF ii=0 and sdate.checked=true          then:a$=lcase$(mlv_log.cell(ii,a)) : END IF
     IF ii=1 and spilot.checked=true         then:a$=lcase$(mlv_log.cell(ii,a)) : END IF
     IF ii=2 and saircraft.checked=true      then:a$=lcase$(mlv_log.cell(ii,a)) : END IF
     IF ii=3 and stakeoff.checked=true       then:a$=lcase$(mlv_log.cell(ii,a)) : END IF
     IF ii=4 and slanding.checked=true       then:a$=lcase$(mlv_log.cell(ii,a)) : END IF
     select case scheck2.checked
      case 0
       IF instr(a$,b$)>0 then
        For i=0 to 6
        slv_log.cell(i,sli_log)=mlv_log.cell(i,a):Next i
        sli_log=sli_log+1
        a$=""
        slv_log.rowcount=sli_log:Doevents
        exit for
       END IF
      case 1
       IF a$=b$ then
        For i=0 to 6
        slv_log.cell(i,sli_log)=mlv_log.cell(i,a)
        Next i
        sli_log=sli_log+1:a$=""
        slv_log.rowcount=sli_log
        Doevents
       END IF
      END select
    Next ii
   Next a
  enablefunc_log
 END IF
END SUB

' Select all search options
SUB Sselectall_log
 sdate.checked        = true
 spilot.checked       = true
 saircraft.checked    = true
 stakeoff.checked     = true
 slanding.checked     = true
END SUB

' Add entry to logbook
SUB Add_entry_log
 mli=3
 mlv_log.cell(0,mlv_log.rowcount) = ""
 mlv_log.cell(1,mlv_log.rowcount) = ""
 mlv_log.cell(2,mlv_log.rowcount) = ""
 mlv_log.cell(3,mlv_log.rowcount) = ""
 mlv_log.cell(4,mlv_log.rowcount) = ""
 mlv_log.cell(5,mlv_log.rowcount) = ""
 mlv_log.cell(6,mlv_log.rowcount) = ""

 mlv_log.rowcount  = mli+mlv_log.rowcount-2
 
 StatusBar_log.Panel(0).Caption = "Items: "+str$(mlv_log.rowcount-1) 
END SUB

' Delete entry from logbook
SUB del_entry_log
 mli=3
 mlv_log.cell(0,mlv_log.rowcount) = ""
 mlv_log.cell(1,mlv_log.rowcount) = ""
 mlv_log.cell(2,mlv_log.rowcount) = ""
 mlv_log.cell(3,mlv_log.rowcount) = ""
 mlv_log.cell(4,mlv_log.rowcount) = ""
 mlv_log.cell(5,mlv_log.rowcount) = ""
 mlv_log.cell(6,mlv_log.rowcount) = ""
 
 IF mlv_log.rowcount <= 2 then
 mli=3
 else:
 mlv_log.rowcount  = mli-2+mlv_log.rowcount-2
 END IF
 StatusBar_log.Panel(0).Caption = "Items: "+str$(mlv_log.rowcount-1) 
END SUB