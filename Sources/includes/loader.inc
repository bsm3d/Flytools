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
' to use, copy, modify, merge, publish, distribute, SUBlicense, and/or sell
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

SUB loader
  boot_loader.caption = "                                                                        "
  boot_loader.caption = "Loading : File I/O..."
    sleep 0.2
    
  boot_loader.caption = "                                                                        "
  boot_loader.caption = "Loading : Interface..."
    sleep 0.2

  boot_loader.caption = "                                                                        "
  boot_loader.caption = "Loading : Database..."
   sleep 0.2

  boot_loader.caption = "                                                                        "
  boot_loader.caption = "Loading : Conversion..."
    sleep 0.2

  IF fileexists ("c:\flytools\prefs\flyprefs.dat") = False then
  boot_loader.caption = "                                                                        "
  boot_loader.caption = "Check prefs : Files ok..."
  END if
     sleep 0.2

'check for help
  IF fileexists ("c:\flytools\help\flytools.chm") = False then
  boot_loader.caption = "                                                                        "
  boot_loader.caption = "Check help : Not found !..."
      sleep .3
  else
  boot_loader.caption = "                                                                        "
  boot_loader.caption = "Check help : File ok..."
  END if
      sleep 0.2 

  boot_form.close
  mainform.showmodal
      
END SUB