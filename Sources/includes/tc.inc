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

CREATE tc_form AS QForm
 caption = "True Course and Distance."
 width   = 400 : height = 300
 center
 borderstyle = 4
 color = &h774422
 
' Interface
 CREATE coord_S     AS QLabel : caption = "Start : " : left = 5 : top = 5 : font = font5 : END CREATE
 CREATE coord_S_Lat AS QLabel : caption = "Latitude : " : left = 5 : top = 30 : font = font5 : END CREATE
 CREATE coord_S_lon AS QLabel : caption = "Longitude : " : left = 5 : top = 60 : font = font5 : END CREATE
 CREATE coord_D     AS QLabel : caption = "Destination : " : left = 200 : top = 5 : font = font5 : END CREATE
END CREATE