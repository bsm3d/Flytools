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

' Create the main airfield form
CREATE airfield AS QForm
  Height  = 400
  Width   = 615
  Borderstyle = 4
  center
  Caption     = "Favorites Airfield Database : " + aero_edt
  
  ' Create the popup menu for the airfield
  CREATE pop_menu_air    as qpopupmenu
      CREATE help_air    as qmenuitem :Caption ="Help"                : shortcut = "F1"  : OnClick=help           :END CREATE
      CREATE calc_air    as qmenuitem :caption ="Calculator"          : shortcut = "F2"  : onclick=calc           :END CREATE
      CREATE prefs_air   as qmenuitem :Caption ="Prefs"               : shortcut = "F3"  : OnClick=main_prefs     :END CREATE
      CREATE log_launch  as qmenuitem :caption ="LogBook"             : shortcut = "F5"  : onclick=log_db         :END CREATE
      CREATE air_sep0    as qmenuitem :caption = "-"       : END CREATE
      CREATE quit_air    as qmenuitem :Caption ="Close Database"      : shortcut = "Esc" : OnClick=air_close      :END CREATE
  END CREATE 
  Popupmenu = pop_menu_air
  
  ' Create the main menu for the airfield
  CREATE MainMenu AS QMainMenu
     
     CREATE FileMenu    as QMenuItem
     Caption   = "&File"
     CREATE OpenItem    AS QMenuItem:Caption   = "Open"    :shortcut = "ctrl+o"    : OnClick = OpenClick    :END CREATE
     CREATE SaveItem    AS QMenuItem:Caption   = "Save"    :shortcut = "ctrl+s"    : OnClick = SaveClick    :END CREATE
     CREATE SaveAsItem  AS QMenuItem:Caption   = "Save As" :OnClick  = SaveAsClick                          :END CREATE
     CREATE air_sep1    as qmenuitem : caption = "-"       : END CREATE
     CREATE ExitItem    AS QMenuItem:Caption   = "Close"   :shortcut = "Esc"       : OnClick = air_close    :END CREATE
     END CREATE
     
     CREATE Quick_db as qmenuitem
     caption = "Load Database"
     CREATE eur_db as qmenuitem : caption = "World ICAO"      : onclick = open_world_icao : END CREATE
     CREATE air_sep2    as qmenuitem : caption = "-"       : END CREATE
     END CREATE
  END CREATE
  
  ' Create the status bar for the airfield
  CREATE StatusBar AS QStatusBar
      sizegrip = 0
      AddPanels "Items: 0","Search result: 0","Ready!"
      Panel(0).Width = 120
      Panel(1).Width = 150
  END CREATE
  
  ' Create the tab control for the airfield
  CREATE Tab AS QTabControl
    Width    = airfield.ClientWidth
    Height   = airfield.ClientHeight-20
    
    ' Main Panel
    CREATE Panel0 AS QPanel
      Top =5
      Left=5
      Width =Tab.ClientWidth-10
      Height=Tab.ClientHeight-10
      bevelouter = 1
      Visible=True
      ' Create toolbar image
      CREATE bar_air as qimage : top = 1 : left = 1 : width = 596 : height = 29 : bmphandle = toolbar : END CREATE
      
      ' Create buttons for various actions
      CREATE close_air_db as qcoolbtn
      Left    = 10
      Top     = 3
      width   = 27
      height  = 26
      flat    = 1
      layout  = 1
      bmphandle = bexit
      cursor  = hand
      hint = "Close Airfield database." : showhint = shint
      OnClick=air_close
      END CREATE
      
      CREATE open_field as qcoolbtn
      Left    = 40
      Top     = 3
      width   = 27
      height  = 26
      flat    = 1
      layout  = 1
      bmphandle = bopen
      cursor  = hand
      hint = "Open database." : showhint = shint
      OnClick =openclick
      END CREATE
      
      CREATE save_field as qcoolbtn
      Left    = 70
      Top     = 3
      width   = 27
      height  = 26
      flat    = 1
      layout  = 1
      bmphandle = bsave
      cursor  = hand
      hint = "Save Database." : showhint = shint
      OnClick =saveclick
      END CREATE
      
      CREATE add_field as qcoolbtn
      Left    = 100
      Top     = 3
      width   = 27
      height  = 26
      flat    = 1
      layout  = 1
      bmphandle = badd
      cursor  = hand
      hint = "ADD new field to Database" : showhint = shint
      OnClick =add_entry
      END CREATE
      
      CREATE del_field as qcoolbtn
      Left    = 130
      Top     = 3
      width   = 27
      height  = 26
      flat    = 1
      layout  = 1
      bmphandle = brem
      cursor  = hand
      hint = "DEL last record from Database" : showhint = shint
      OnClick =del_entry
      END CREATE
      
      CREATE find_field as qcoolbtn
      Left    = 160
      Top     = 3
      width   = 27
      height  = 26
      flat    = 1
      layout  = 1
      bmphandle = bsearch
      cursor  = hand
      hint = "Search field from Database" : showhint = shint
      OnClick = b_search
      END CREATE
      
      ' Create label for database name
      CREATE whois as qlabel
      left = 190
      top  = 10
      transparent = 1
      caption = "Database : "
      END CREATE
       
      ' Create help button
      CREATE air_help as qcoolbtn : top = 3   : left = 570  : width = 27 : height = 26 : flat = 1 : layout = 1  : bmphandle = bhelp : cursor = hand : onclick = help : hint = "Display Helps." : showhint = shint :  END CREATE
 
      ' Create the main airfield grid
      CREATE mlv AS QStringGrid
      parent = panel0
      Width  = Panel0.ClientWidth
      Height = Panel0.ClientHeight-29
      Top= 29
      cell(0,0)="Airfield" : cell(1,0)="Code" :cell(2,0)="Country": cell(3,0)="Radio Freq." : cell(4,0)="Altitude" : cell(5,0)="Latitude" : cell(6,0)="Longitude" : fixedcols=0
      DefaultRowHeight=18
      addoptions goediting
      rowcount = 2
      colcount = 7
      colwidths(0) = 170
      colwidths(1) = 50
      colwidths(2) = 70
      colwidths(3) = 70
      colwidths(4) = 70
      colwidths(5) = 70
      colwidths(6) = 70
      END CREATE
    END CREATE
    
    ' Search Panel
    CREATE Panel1 AS QPanel
      Top =5
      Left=5
      Width =Tab.ClientWidth-10
      Height=Tab.ClientHeight-10
      Visible=False
      bevelouter = 1
      ' Create toolbar image
      CREATE bar_air2 as qimage : top = 1 : left = 1 : width = 596 : height = 29 : bmphandle = toolbar : END CREATE
      
      ' Create button to return to main database
      CREATE main_field as qcoolbtn
      Left    = 10
      Top     = 3
      width   = 27
      height  = 26
      flat    = 1
      layout  = 1
      bmphandle = bdb
      cursor  = hand
      hint = "Return to Database." : showhint = shint
      OnClick =b_main
      END CREATE
     
     ' Create search input and options
     CREATE sll as qlabel   :Parent  = panel1 :Top  = 8   :Left = 40   : caption = "String :" : END CREATE
     CREATE SEdit As QEdit  :Parent  = panel1 :Left = 75  :Width = 130 : Top = 5: onkeypress=Searchroutine : END CREATE
     
     CREATE scheck as qcheckbox     : left=210 :top=6   : width = 15 : END CREATE
     CREATE schek_lab as qlabel     : caption = "Exact" : transparent = 1 : left = 225 : top = 8 : width = 50 : END CREATE 

     CREATE sall as qcoolbtn        :layout = 1 : flat = 1  :left=260 :height = 26 : bmphandle = ball : top=3  :Width = 27 :cursor = hand :hint = "Check all search methods" : showhint = shint : onclick=Sselectall : END CREATE 
    
     CREATE sairfield as qcheckbox  : left=295 :top=6  :width = 15 :Checked=True               :END CREATE
     CREATE sairfield_lab as qlabel : caption = "Airfield" : transparent = 1 : left = 310 : top = 8 : width = 50 : END CREATE 

     CREATE scode as qcheckbox      : left=350 :top=6  :width = 15 :Checked=True               :END CREATE
     CREATE scode_lab as qlabel     : caption = "Code" : transparent = 1 : left = 365 : top = 8 : width = 50 : END CREATE 

     CREATE scountry as qcheckbox   : left=400 :top=6  :width = 15 :Checked=True               :END CREATE
     CREATE scountry_lab as qlabel  : caption = "Country" : transparent = 1 : left = 415 : top = 8 : width = 50 : END CREATE 

     CREATE sfreq as qcheckbox      : left=460 :top=6  :width = 15 :Checked=True               :END CREATE
     CREATE sfreq_lab as qlabel     : caption = "Freq." : transparent = 1 : left = 475 : top = 8 : width = 50 : END CREATE 
     
     ' Create help button
     CREATE air_help2 as qcoolbtn : top = 3   : left = 570  : width = 27 : height = 26 : flat = 1 : layout = 1  : bmphandle = bhelp : cursor = hand : onclick = help : hint = "Display Helps." : showhint = shint :  END CREATE

     ' Create the search results grid
     CREATE slv AS QStringGrid
      Parent  = Panel1
      Width   = Panel1.ClientWidth
      Height  = Panel1.ClientHeight-29
      Top=29
      cell(0,0)="Airfield" : cell(1,0)="Code" :cell(2,0)="Country": cell(3,0)="Radio Freq." : cell(4,0)="Altitude" : cell(5,0)="Latitude" : cell(6,0)="Longitude" : fixedcols=0
      DefaultRowHeight=18
      addoptions 5
      rowcount=2
      Colcount=7
      colwidths(0) = 170
      colwidths(1) = 50
      colwidths(2) = 70
      colwidths(3) = 70
      colwidths(4) = 70
      colwidths(5) = 70
      colwidths(6) = 70
     END CREATE
    END CREATE
   END CREATE
END CREATE

' Switch to search panel
SUB b_search
  Panel0.Visible=False
  Panel1.Visible=True
END SUB

' Switch to main panel
SUB b_main
  Panel0.Visible=true
  Panel1.Visible=false
END SUB

' Search Routines
SUB Searchroutine
 IF chr$(key)=chr$(13) then
  disablefunc
  dim i as integer,a as integer,ii as integer,a$ as string,b$ as string
  b$=lcase$(SEdit.Text)
  slv.rowcount=2:sli=1
  For i=0 to 6
  slv.cell(i,1)=""
  next i
   for a=1 to mlv.rowcount-1
    For ii=0 to 6
     IF ii=0 and sairfield.checked=true   then:a$=lcase$(mlv.cell(ii,a)) : END IF
     IF ii=1 and scode.checked=true       then:a$=lcase$(mlv.cell(ii,a)) : END IF
     IF ii=2 and scountry.checked=true    then:a$=lcase$(mlv.cell(ii,a)) : END IF
     IF ii=3 and sfreq.checked=true       then:a$=lcase$(mlv.cell(ii,a)) : END IF
     
        select case scheck.checked
          case 0
          IF instr(a$,b$)>0 then
            For i=0 to 6
            slv.cell(i,sli)=mlv.cell(i,a):Next i
            sli=sli+1
            a$=""
            slv.rowcount=sli:Doevents
            exit for
          END IF
          case 1
          IF a$=b$ then
            For i=0 to 6
            slv.cell(i,sli)=mlv.cell(i,a)
            Next i
            sli=sli+1:a$=""
            slv.rowcount=sli
            Doevents
          END IF
          END select
        Next ii
      Next a
      enablefunc
    END IF
  END SUB

' Select all search options
SUB Sselectall
  sairfield.checked  = true
  scode.checked      = true
  scountry.checked   = true
  sfreq.checked      = true
END SUB

' Add entry to airfield
SUB Add_entry
  dim rect as qrect
  mli=3
  mlv.cell(0,mlv.rowcount) = ""
  mlv.cell(1,mlv.rowcount) = ""
  mlv.cell(2,mlv.rowcount) = ""
  mlv.cell(3,mlv.rowcount) = ""
  mlv.cell(4,mlv.rowcount) = ""
  mlv.cell(5,mlv.rowcount) = ""
  mlv.cell(6,mlv.rowcount) = ""
  mlv.rowcount  = mli+mlv.rowcount-2
  StatusBar.Panel(0).Caption = "Items: "+str$(mlv.rowcount-1) 
END SUB

' Delete entry from airfield
SUB del_entry
  mli=3
  IF mlv.rowcount <= 2 then
    mli=3
  else:
    mlv.cell(0,mlv.rowcount) = ""
    mlv.cell(1,mlv.rowcount) = ""
    mlv.cell(2,mlv.rowcount) = ""
    mlv.cell(3,mlv.rowcount) = ""
    mlv.cell(4,mlv.rowcount) = ""
    mlv.cell(5,mlv.rowcount) = ""
    mlv.cell(6,mlv.rowcount) = ""
    mlv.rowcount  = mli-2+mlv.rowcount-2
  END IF
  StatusBar.Panel(0).Caption = "Items: "+str$(mlv.rowcount-1) 
END SUB