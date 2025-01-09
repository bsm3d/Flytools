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

' OPEN file
  SUB OpenClick_log
    opendialog_log.initialdir="c:\flytools\Logbook"
    OpenDialog_log.Filter="FLB (*.FLB)|*.flb"
    IF OpenDialog_log.Execute THEN
      opf$=OpenDialog_log.FileName
      
        machaine = opf$ 
        rem_ext = instr(maChaine,"\")
      WHILE(rem_ext<> 0)
        machaine = mid$(machaine,rem_ext+1,len(machaine)-rem_ext-1)
        rem_ext  = instr(maChaine,"\")
      WEND
        rem_ext  = instr(machaine,".")
      IF(rem_ext <> 0) THEN 
        machaine = left$(machaine,rem_ext -1 )
      END IF  
      
      whois2.caption = "DataBase : " + machaine
      
      IF File_log.OPEN(OpenDialog_log.FileName,0)=False THEN
      ShowMessage("Couldn't Open File!")
      ELSE
      load_log
      END IF
    END IF
  END SUB

' Load database
  SUB load_log
    DIM mem AS qmemorystream,i AS integer
    DIM p1 AS integer,p2 AS integer,p3 AS integer,p4 AS integer,p5 AS integer, p6 AS integer, p7 AS integer ,pp AS integer
    DIM Ldate$ AS string, pilot$ AS string,aircraft$ AS string,takeoff$ AS string, landing$ AS string, Ltime$ AS string, fuel$ AS string
    DIM chaine$ AS string,b AS integer,pb AS integer,t AS integer
    
    mem.copyfrom(file_log,file_log.size) : mem.position=0
    file_log.close
    DisableFunc_log
    i=1
    mlv_log.rowcount=100000
    
    WHILE mem.position<mem.size
      pp      = mem.position
      chaine$ = mem.readstr(1000)
      
      p7 = INSTR(chaine$,chr$(10))
      
      p1   =INSTR(chaine$,"�")
      p2   =INSTR(p1+1,chaine$,"�")
      p3   =INSTR(p2+1,chaine$,"�")
      p4   =INSTR(p3+1,chaine$,"�")
      p5   =INSTR(p4+1,chaine$,"�")
      p6   =INSTR(p5+1,chaine$,"�")
      
      Ldate$     =left$(chaine$,p1-1)         '0  
      pilot$      =mid$(chaine$,p1+1,p2-p1-1) '1
      aircraft$   =mid$(chaine$,p2+1,p3-p2-1) '2
      takeoff$    =mid$(chaine$,p3+1,p4-p3-1) '3
      landing$    =mid$(chaine$,p4+1,p5-p4-1) '4
      ltime$      =mid$(chaine$,p5+1,p6-p5-1) '5
      fuel$       =mid$(chaine$,p6+1,p7-p6-2) '6
      
      mlv_log.cell(0,i)=ldate$
      mlv_log.cell(1,i)=pilot$
      mlv_log.cell(2,i)=aircraft$
      mlv_log.cell(3,i)=takeoff$
      mlv_log.cell(4,i)=landing$
      mlv_log.cell(5,i)=ltime$
      mlv_log.cell(6,i)=fuel$
      
      i=i+1
        
      mem.position = pp+p7
      doevents
    WEND
    mlv_log.rowcount=i
    mem.Close
    enablefunc_log
  END SUB

' Save file on the file
  SUB SaveClick_log
    IF opf$<>"" THEN
    File_log.OPEN(opf$,65535)
    machaine = opf$ 
      rem_ext = instr(maChaine,"\")
    WHILE(rem_ext<> 0)
      machaine = mid$(machaine,rem_ext+1,len(machaine)-rem_ext-1)
      rem_ext  = instr(maChaine,"\")
    WEND
      rem_ext  = instr(machaine,".")
    IF(rem_ext <> 0) THEN 
      machaine = left$(machaine,rem_ext -1 )
    END IF  
    whois2.caption = "DataBase : " + machaine
    Save_log
    ELSE
    SaveAsClick_log
    END IF
  END SUB

' Save As new file
  SUB SaveAsClick_log
    DIM SaveDialog_log AS QSaveDialog
    SaveDialog_log.InitialDir="c:\flytools\Logbook"
    SaveDialog_log.Filter="FLB (*.FLB)|*.flb"
    IF SaveDialog_log.Execute THEN
      IF lcase$(right$(savedialog_log.filename,4))=".flb" THEN
      ELSE
      savedialog_log.filename=savedialog_log.filename+".flb"
      END IF
      File_log.OPEN(SaveDialog_log.FileName,65535)
      Save_log
      opf$=SaveDialog_log.FileName
        
        machaine = opf$ 
        rem_ext = instr(maChaine,"\")
      WHILE(rem_ext<> 0)
        machaine = mid$(machaine,rem_ext+1,len(machaine)-rem_ext-1)
        rem_ext  = instr(maChaine,"\")
      WEND
        rem_ext  = instr(machaine,".")
      IF(rem_ext <> 0) THEN 
        machaine = left$(machaine,rem_ext -1 )
      END IF  
      
      whois2.caption = "DataBase : " + machaine
    END IF
  END SUB

  SUB Save_log
  disablefunc_log
  DIM sa AS integer,si AS integer,sen$ AS string, writ$ AS string,Spilot$ AS string
  DIM sLdate$ AS string,spilo$ AS string,saircraft$ AS string,stakeoff$ AS string, slanding$ AS string, sLtime$ AS string, sfuel$ AS string

  sen$=chr$(13)+chr$(10)
  
  FOR si=1 TO mlv_log.rowcount-1
    Sldate$     =mlv_log.cell(1,si)
    Spilo$      =mlv_log.cell(2,si)
    Saircraft$  =mlv_log.cell(3,si)
    Stakeoff$   =mlv_log.cell(4,si)
    SLanding$   =mlv_log.cell(5,si)
    Sltime$     =mlv_log.cell(6,si)
    Sfuel$      =mlv_log.cell(7,si)
  
    IF Sldate$    =mlv_log.cell(1,si-1) THEN
    IF Spilo$    =mlv_log.cell(2,si-1) THEN
      IF Sfuel$   =mlv_log.cell(7,si-1) THEN
      sa=1
      ELSE
      sa=-1
      END IF
    ELSE
      sa=-1
    END IF
    ELSE
    sa=-1
    END IF
    IF sa=-1 THEN
    IF writ$<>"" THEN
    file_log.writestr(sen$,6)
    END IF
      Sldate$     =mlv_log.cell(0,si)
      Spilo$      =mlv_log.cell(1,si)
      Saircraft$  =mlv_log.cell(2,si)
      Stakeoff$   =mlv_log.cell(3,si)
      SLanding$   =mlv_log.cell(4,si)
      Sltime$     =mlv_log.cell(5,si)
      Sfuel$      =mlv_log.cell(6,si)
    
    writ$=sldate$+"�"+Spilo$+"�"+Saircraft$+"�"+Stakeoff$+"�"+Slanding$+"�"+sltime$+"�"+sfuel$+sen$
    
    file_log.writestr(writ$,len(writ$))
    sa=0
    writ$=""
    END IF
  NEXT si
    IF writ$<>"" THEN
    file_log.writestr(sen$,6)
    END IF
    file_log.close
    enablefunc_log
  END SUB

  SUB DisableFunc_log
    StatusBar_log.Panel(3).Caption = "Please Wait..."
    tab_log.enabled        =False
    logbook.cursor         = -11
    openitem_log.enabled   = False
    saveitem_log.enabled   = False
    saveasitem_log.enabled = False
  END SUB

  SUB EnableFunc_log
    IF mlv_log.rowcount = 2 THEN
      StatusBar_log.Panel(0).Caption = "Items: 0"
    ELSE
      StatusBar_log.Panel(0).Caption = "Items: "+str$(mlv_log.rowcount-1)
    END IF
    IF slv_log.rowcount=2 THEN
      StatusBar_log.Panel(1).Caption = "Search result: 0"
    ELSE
      StatusBar_log.Panel(1).Caption = "Search result: "+str$(slv_log.rowcount-1)
    END IF
    logbook.cursor=0
    StatusBar_log.Panel(3).Caption = "Ready!"
      tab_log.enabled       =True
      openitem_log.enabled  =True
      saveitem_log.enabled  =True
      saveasitem_log.enabled=True
    doevents
  END SUB


