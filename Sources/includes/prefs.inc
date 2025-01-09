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

' Read default prefs
   Dim prefs_ini   as qfilestream
   Dim devises_ini as qfilestream
   mkdir  "c:\flytools\"
   mkdir  "c:\flytools\Prefs"
   mkdir  "c:\flytools\Database"
   mkdir  "c:\flytools\Logbook"

IF prefs_ini.Open("c:\flytools\prefs\Flyprefs.dat", fmOpenReadWrite) = False THEN
   prefs_ini.open ("c:\flytools\prefs\Flyprefs.dat", fmCreate)

' default values and reset values
   shint = 1 : mode_hint = "Yes" : ndec = 2 : aero_edt = string(" ")
   prefs_ini.writenum(ndec,num_byte)
   prefs_ini.writenum(shint,num_byte)
   prefs_ini.writestr(mode_hint,3)
   prefs_ini.writestr(aero_edt,100)
   prefs_ini.close
   END IF

   prefs_ini.Open("c:\flytools\prefs\Flyprefs.dat", fmOpenReadWrite)
   ndec      = prefs_ini.readnum(num_byte)
   shint     = prefs_ini.readnum(num_byte)
   mode_hint = prefs_ini.readstr(3)
   aero_edt  = prefs_ini.readstr(100)
   prefs_ini.close

' Default coins values
   IF devises_ini.Open("c:\flytools\prefs\Flydata.dat", fmOpenReadWrite) = False THEN
   devises_ini.open ("c:\flytools\prefs\Flydata.dat", fmCreate)

   t_fb     = 40.3399
   t_ff     = 6.56
   t_dm     = 1.96
   t_euro   = 1
   t_lire   = 1936.27
   t_livre  = 0.60
   t_us     = 0.96
   t_ca     = 1.38
   t_cz     = 36.13

   devises_ini.writenum(t_fb,num_double)
   devises_ini.writenum(t_ff,num_double)
   devises_ini.writenum(t_dm,num_double)
   devises_ini.writenum(t_euro,num_double)
   devises_ini.writenum(t_lire,num_double)
   devises_ini.writenum(t_livre,num_double)
   devises_ini.writenum(t_us,num_double)
   devises_ini.writenum(t_ca,num_double)
   devises_ini.writenum(t_cz,num_double)
   devises_ini.close
   END IF

   devises_ini.open("c:\flytools\prefs\flydata.dat", fmOpenReadWrite)

   t_fb     = devises_ini.readnum(num_double)
   t_ff     = devises_ini.readnum(num_double)
   t_dm     = devises_ini.readnum(num_double)
   t_euro   = devises_ini.readnum(num_double)
   t_lire   = devises_ini.readnum(num_double)
   t_livre  = devises_ini.readnum(num_double)
   t_us     = devises_ini.readnum(num_double)
   t_ca     = devises_ini.readnum(num_double)
   t_cz     = devises_ini.readnum(num_double)

   devises_ini.close
' END of file (don't modify this file !)