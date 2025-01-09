# FlyTools User Manual

## Table of Contents
1. [Introduction](#introduction)
2. [Software Origin and Philosophy](#software-origin-and-philosophy)
3. [System Requirements](#system-requirements)
4. [Installation](#installation)
5. [Comprehensive Feature Set](#comprehensive-feature-set)
6. [User Interface](#user-interface)
7. [Aviation Calculation Modules](#aviation-calculation-modules)
8. [Conversion Tools](#conversion-tools)
9. [Database Management](#database-management)
10. [Detailed Module Examples](#detailed-module-examples)
11. [Keyboard Shortcuts](#keyboard-shortcuts)
12. [Preferences and Customization](#preferences-and-customization)
13. [Licensing and Support](#licensing-and-support)
14. [Disclaimer](#disclaimer)
15. [Copyright and Acknowledgments](#copyright-and-acknowledgments)

## Introduction

FlyTools is a comprehensive aviation software designed primarily for light aircraft homebuilder pilots. Developed by Saint-Moulin Benoît, this versatile application provides an extensive range of tools to assist pilots with navigation, calculations, and flight planning.

## Software Origin and Philosophy

Created in the early 2000s, FlyTools embodies a simple yet powerful approach to aviation software development. The application was designed with several core principles:
- Lightweight and resource-efficient design
- No complex external dependencies
- Easy updates and maintenance
- User-friendly interface
- Comprehensive aviation support tools

## System Requirements

### Compatible Operating Systems
- Windows 95
- Windows 98
- Windows NT 4
- Windows 2000
- Windows XP

### Hardware Specifications
- Minimal 1 MB of hard disk space
- Screen resolution of 800x600, 256 colors
- Mouse device (optional, as all functions can be performed via keyboard)
- Optional deskjet printer

## Installation

1. Download the installation package from the official website
2. Run the executable installer
3. Follow on-screen instructions
4. No additional software or complex setup required

## Comprehensive Feature Set

FlyTools offers an impressive array of functionalities designed to support pilots in various aspects of flight preparation and navigation:

### Core Modules
- Flight Leg Computing
- Weight & Balance Calculations
- True Heading Computation
- Magnetic Heading Determination
- Ground Speed Analysis
- Wind Direction Calculation
- Freezing Level Prediction

### Conversion Utilities
Powerful conversion tools for multiple units:
- Angle
- Base numbers
- Currency
- Fuel
- Length
- Mass
- Pressure
- Power
- Speed
- Temperature

### Additional Features
- Custom ICAO Database Management
- Flight Logbook Functionality
- Configurable Preferences System
- Online Aviation Resources Access

## User Interface

### Main Window Layout
- Intuitive, clean design
- Tabbed interface for easy navigation
- Consistent icon-based controls
- Responsive to keyboard and mouse input

### Interface Icons

#### General Icons
- Exit: Close current window or application
- Evaluate: Compute or solve calculations
- Calculator: Launch integrated calculator
- Help: Display help documentation
- Delete: Clear input data
- Print: Generate printable output
- OK: Confirm current action

#### Database Icons
- Add: Add new record to database
- Search: Open database search interface
- Remove: Delete selected record
- Open: Open existing file
- Save: Save current data

## Aviation Calculation Modules

### 1. Flight Leg Computing

A critical module for precise route navigation and planning.

**Calculation Parameters:**
- Estimated Time of Departure (E.T.D.)
- Magnetic Variation
- Distance
- Fuel Burn
- Wind Velocity and Direction
- True Course
- True Airspeed

**Example Calculation:**
- Input: 
  - E.T.D.: 12:50
  - Magnetic Variation: -12° (East)
  - Distance: 80 nautical miles
  - Wind Direction: 200° (True)
  - Wind Velocity: 28 knots
  - True Airspeed: 115 knots
  - True Course: 245°

**Calculated Outputs:**
- True Heading: 224.79°
- Magnetic Heading: 232.79°
- Ground Speed: 97.79 knots
- Estimated Fuel Consumption: 11.45 units
- Estimated Time En Route: 0.81 hours
- Estimated Time of Arrival: 13:31

### 2. Weight & Balance Calculations

Ensures safe aircraft loading and weight distribution.

**Example Scenario (Zenair CH 601 HD):**
- Nose Wheel Weight: 101.20 kg
- Right Wheel Weight: 96.20 kg
- Left Wheel Weight: 97.20 kg
- Pilot Weight: 79 kg
- Passenger Weight: 58 kg
- Baggage Compartment: 14 kg
- Wing Locker Baggage: 30 kg
- Fuel Load: 96 Liters

**Calculation Results:**
- Empty Aircraft Weight: 294.6 kg
- Empty Weight Center of Gravity: 217.78 kg
- Total Aircraft Weight: 544.72 kg
- Center of Gravity: 385.81 mm
- Safety Check: All limits verified

### 3. True Heading Computation
- Converts magnetic course to true heading
- Accounts for magnetic declination
- Example: Magnetic Course 250° with 15° West Variation = True Heading 265°

### 4. Magnetic Heading Determination
- Adjusts true course for local magnetic variations
- Example: True Course 245° with 12° East Variation = Magnetic Heading 233°

### 5. Ground Speed Analysis

Ground Speed Analysis is a critical calculation that helps pilots determine their actual speed over the ground by accounting for various wind conditions. 

**Example Calculation Scenario:**
- True Airspeed: 120 knots
- Wind Direction: 045° (from the northeast)
- Wind Speed: 20 knots
- Aircraft Heading: 225° (southwest)

**Calculation Methodology:**
The module performs complex vectorial calculations to decompose wind effects, considering:
- Wind vector relative to aircraft heading
- Impact of wind speed and direction
- Precise trigonometric analysis of trajectory modifications

**Practical Applications:**
- Accurate distance estimation
- Fuel consumption prediction
- Estimated time of arrival calculations
- Navigation precision improvement

### 6. Wind Direction Calculation

Wind Direction Calculation provides pilots with a comprehensive analysis of wind's complex effects on aircraft performance.

**Detailed Scenario Analysis:**
- Magnetic Heading: 300°
- Wind Direction: 110° (True)
- Wind Velocity: 35 knots
- Magnetic Variation: 15° East

**Wind Component Breakdown:**
- Tailwind Component: 31.72 knots (positive indicates wind from behind)
- Crosswind Component: -14.79 knots (negative indicates wind from right)

### 7. Freezing Level Prediction

A critical safety tool for assessing potential icing conditions.

**Example Scenario:**
- Altitude: 6,500 feet
- Ambient Temperature: -7°C

**Prediction Results:**
- Dry Freezing Level (Clear Weather): 3,000 feet
- Wet Freezing Level (Cloudy Conditions): 1,833.33 feet

## Conversion Tools

### Supported Conversion Categories
- Angle
- Base Numbers
- Currency
- Fuel
- Length
- Mass
- Pressure
- Power
- Speed
- Temperature

### Currency Conversion
Supports conversion between:
- German Mark
- Euro
- Belgian Franc
- French Franc
- Italian Lira
- British Pound
- US Dollar
- Canadian Dollar
- Czech Koruna

## Database Management

### Airfields Database
Comprehensive airport information management:
- Airport Name
- ICAO Code
- Country
- Radio Frequencies
- Altitude
- Geographical Coordinates

#### Database Operations
- Add New Records
- Delete Existing Records
- Advanced Searching
  - Exact Name Search
  - Airfield Search
  - Code Search
  - Country Search

### Pilot Logbook
Detailed flight history tracking:
- Date Recording
- Pilot Information
- Aircraft Details
- Takeoff and Landing Information

#### Logbook Features
- Add Flight Entries
- Delete Entries
- Advanced Search Capabilities
  - Date-based Search
  - Pilot Name Search
  - Aircraft Search
  - Takeoff/Landing Search

## Keyboard Shortcuts

### Function Keys
| Key | Function |
|-----|----------|
| F1 | Help |
| F2 | Calculator |
| F3 | Preferences |
| F4 | Airfields Database |
| F5 | Logbook |
| F6 | Flight Leg Calculations |
| F7 | Weight & Balance |
| Esc | Close Window |

### Control Key Conversions
| Shortcut | Function |
|----------|----------|
| CTRL + A | Angle Conversion |
| CTRL + B | Base Number Conversion |
| CTRL + C | Currency Conversion |
| CTRL + F | Fuel Conversion |
| CTRL + L | Length Conversion |
| CTRL + M | Mass Conversion |
| CTRL + P | Pressure Conversion |
| CTRL + S | Speed Conversion |
| CTRL + T | Temperature Conversion |
| CTRL + O | Open File |
| CTRL + Q | Quit FlyTools |

## Preferences and Customization

### Configurable Settings
- Currency Preferences
- Help Bubble Display
- Decimal Rounding Precision
- Aero-Club Name
- Default Unit Preferences

### Preference Management
- Accessible via F3 Shortcut
- Easy Configuration
- Save and Reset Options

## Licensing and Support

- **Type:** Open source
- **Cost:** Free to use and share
- **Donation:** Suggested (€10)
- **Donation Email:** helloworld@tdt3d.com
- **Official Website:** http://www.lightplane.org

## Disclaimer

**CRITICAL WARNING**
- No explicit warranty is provided
- Use the software entirely at your own risk
- Always cross-verify critical calculations
- This tool is intended to assist, not replace, professional aviation judgment

## Copyright and Acknowledgments

© Benoît Saint-Moulin 

**Special Thanks:**
- William Yu (RapidQ Development)
- Bruno Poupier
- Franz De Muynck
- All Beta Testers

**Included Technologies:**
- RapidQ © William Yu
- Inno Setup © Jordan Russell
- Zenair © Zenaith Aircraft Ltd.

---

**Version:** 1.6.1
**Release Date:** April 6, 2006
**Last Compatibility Test:** January 8, 2025 (Windows 10 x64)

**Note:** This is a 25th Anniversary re-issue release for educational and learning purposes, representing software development practices of the early 2000s.
