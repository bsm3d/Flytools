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
SUB OpenClick
 opendialog.initialdir="c:\flytools\database"
 OpenDialog.Filter="FAB (*.FAB)|*.fab"
 IF OpenDialog.Execute THEN
  opf$=OpenDialog.FileName
    
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
  
  whois.caption = "DataBase : " + machaine
  
  IF File.OPEN(OpenDialog.FileName,0)=False THEN
  ShowMessage("Couldn't Open File!")
   ELSE
   load
  END IF
 END IF
END SUB

' Load database
SUB load
 DIM mem AS qmemorystream
 DIM i AS INTEGER
 DIM p1 AS INTEGER,p2 AS INTEGER,p3 AS INTEGER,p4 AS INTEGER,p5 AS INTEGER,p6 AS INTEGER, p7 AS INTEGER, pp AS INTEGER
 DIM air$ AS STRING, code$ AS STRING, country$ AS STRING, freq$ AS STRING, altitude$ AS STRING, lat$ AS STRING,lon$ AS STRING
 DIM chaine$ AS STRING,b AS INTEGER,pb AS INTEGER,t AS INTEGER
 
 mem.copyfrom(file,file.size):mem.position=0:file.close:DisableFunc:i=1:mlv.rowcount=100000
 WHILE mem.position<mem.size
  pp=mem.position
  chaine$=mem.readstr(1000)
  
   p7=INSTR(chaine$,chr$(10))
   
   p1=INSTR(chaine$,"�")
   p2=INSTR(p1+1,chaine$,"�")
   p3=INSTR(p2+1,chaine$,"�") 
   p4=instr(p3+1,chaine$,"�")
   p5=INSTR(p4+1,chaine$,"�")
   p6=INSTR(p5+1,chaine$,"�")           
   
   air$      =left$(chaine$,p1-1)         '0
   code$     =mid$(chaine$,p1+1,p2-p1-1)  '1
   country$  =mid$(chaine$,p2+1,p3-p2-1)  '2
   freq$     =mid$(chaine$,p3+1,p4-p3-1)  '3
   altitude$ =mid$(chaine$,p4+1,p5-p4-1)  '4
   lat$      =mid$(chaine$,p5+1,p6-p5-1)  '5
   lon$      =mid$(chaine$,p6+1,p7-p6-2)  '6
   
   mlv.cell(0,i)=air$
   mlv.cell(1,i)=code$
   mlv.cell(2,i)=country$
   mlv.cell(3,i)=freq$
   mlv.cell(4,i)=altitude$
   mlv.cell(5,i)=lat$
   mlv.cell(6,i)=lon$  
   i=i+1
  mem.position=pp+p7 'p4
  doevents
 WEND
 mlv.rowcount=i
 mem.Close:enablefunc
END SUB

' Save file
SUB SaveClick
  IF opf$<>"" THEN
   File.OPEN(opf$,65535)
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
   Save
   ELSE
   SaveAsClick
  END IF
END SUB

' Save As new file
SUB SaveAsClick
 DIM SaveDialog AS QSaveDialog
 SaveDialog.InitialDir="c:\flytools\database"
 SaveDialog.Filter="FAB (*.FAB)|*.fab"
 IF SaveDialog.Execute THEN
   IF lcase$(right$(savedialog.filename,4))=".fab" THEN
   ELSE
   savedialog.filename=savedialog.filename+".fab"
   END IF
   File.OPEN(SaveDialog.FileName,65535)
   Save
   opf$=SaveDialog.FileName
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
  
  whois.caption = "DataBase : " + machaine
 END IF
END SUB

SUB Save
 disablefunc
 DIM sa AS INTEGER,si AS INTEGER,sen$ AS STRING, writ$ AS STRING
 DIM Sair$ AS STRING, Scode$ AS STRING,Scountry$ AS STRING, sfreq$ AS STRING, saltitude$ AS STRING, Slat$ AS STRING, Slongitude$ AS STRING
 sen$ = chr$(13)+chr$(10)
 FOR si=1 TO mlv.rowcount-1
  
  Sair$       =mlv.cell(1,si)
  Scode$      =mlv.cell(2,si)
  Scountry$   =mlv.cell(3,si)
  Sfreq$      =mlv.cell(4,si)
  Saltitude$  =mlv.cell(5,si) 
  Slat$       =mlv.cell(6,si)
  Slongitude$ =mlv.cell(7,si)
  
  IF Sair$        =mlv.cell(1,si-1) THEN
   IF Scode$      =mlv.cell(2,si-1) THEN
    IF Slongitude$=mlv.cell(7,si-1) THEN:sa=1:ELSE:sa=-1:END IF
   ELSE
    sa=-1
   END IF
  ELSE
   sa=-1
  END IF
  IF sa=-1 THEN    
    IF writ$<>"" THEN
      file.writestr(sen$,6)
    END IF   
   Sair$      =mlv.cell(0,si)
   Scode$     =mlv.cell(1,si)
   Scountry$  =mlv.cell(2,si)
   Sfreq$     =mlv.cell(3,si)
   Saltitude$ =mlv.cell(4,si)
   Slat$      =mlv.cell(5,si)
   Slongitude$=mlv.cell(6,si)  
   writ$=Sair$+"�"+Scode$+"�"+SCountry$+"�"+sfreq$+"�"+saltitude$+"�"+Slat$+"�"+Slongitude$+sen$
   
   file.writestr(writ$,len(writ$))
   sa=0
   writ$=""
  END IF
 NEXT si
 IF writ$<>"" THEN
 file.writestr(sen$,6)
 END IF
 file.close
 enablefunc
END SUB

SUB DisableFunc
 StatusBar.Panel(3).Caption = "Please Wait..."
 tab.enabled=False
 airfield.cursor   = -11
 openitem.enabled   = False
 saveitem.enabled   = False
 saveasitem.enabled = False
END SUB

SUB EnableFunc
 IF mlv.rowcount = 2 THEN
  StatusBar.Panel(0).Caption = "Items: 0"
 ELSE
  StatusBar.Panel(0).Caption = "Items: "+str$(mlv.rowcount-1)
 END IF
 IF slv.rowcount=2 THEN
  StatusBar.Panel(1).Caption = "Search result: 0"
 ELSE
  StatusBar.Panel(1).Caption = "Search result: "+str$(slv.rowcount-1)
 END IF
 airfield.cursor=0
 StatusBar.Panel(3).Caption = "Ready!"
  tab.enabled=True
  openitem.enabled=True
  saveitem.enabled=True
  saveasitem.enabled=True
 doevents
END SUB  

SUB open_world_icao
  IF fileexists ("c:\flytools\database\world_icao.fab") = False THEN
  messagedlg ("Default world ICAO database not found !!", mterror, mbOk , 0)
  END IF
  File.OPEN("c:\flytools\database\world_icao.fab",0)
  whois.caption = "DataBase : " + "World ICAO"
  load
END SUB