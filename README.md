# 🔧 Electronics Engineering Toolkit (C++)

A modular, menu-driven C++ console application providing practical electronics calculation tools, including resistor utilities, op-amp configuration analysis, and active filter design support (Butterworth & Chebyshev Sallen–Key filters).

Designed as an interactive engineering helper for circuit analysis, rapid design verification, and reinforcing analogue electronics principles through software.

---

## 📌 Overview

This project implements a structured multi-level CLI system written in modern C++ (C++14 standard), allowing users to perform common analogue electronics calculations.

The application demonstrates:

- Modular software architecture (`main.cpp`, `funcs.cpp`, `funcs.h`)
- Robust user input validation
- Use of STL containers (`std::vector`, `std::map`)
- Mathematical modelling of circuit behaviour
- Clean separation between UI control flow and calculation logic

---

## 🗂️ Project Structure


.
├── main.cpp # Main loop and primary menu system
├── funcs.cpp # All calculator implementations and circuit tools
├── funcs.h # Function declarations
└── README.md # Project documentation


---

## 🧮 Features

---

### 1️⃣ Resistor Calculator

Includes multiple utilities:

- 🔹 Calculate resistance from colour bands  
- 🔹 Combine resistors in series and parallel  
- 🔹 Find nearest preferred value resistor (E12 series)  
- 🔹 Suggest series/parallel combinations  
- 🔹 Generate colour code from resistance value  

Implements colour-to-digit mapping and multiplier logic using `std::map`.

---

### 2️⃣ Op-Amp Configurator

Supports:

#### 🔹 Inverting Amplifier
Gain formula:


Gain = −Rf / Rin


Output voltage:


Vout = Gain × Vin


---

#### 🔹 Non-Inverting Amplifier
Gain formula:


Gain = 1 + (Rf / Rg)


Output voltage:


Vout = Gain × Vin


Includes validation for positive resistor and voltage inputs.

---

### 3️⃣ Sallen–Key Active Filter Designer

Supports:

- 2, 4, or 6 pole filters
- Butterworth response
- 0.5 dB Chebyshev response
- 2 dB Chebyshev response
- Low-pass and High-pass configurations

For each stage, the program calculates:

- Stage gain
- Cutoff frequency
- Displays filter configuration diagram (ASCII schematic)

Cutoff frequency calculation:


fc = 1 / (2πRC × stage_factor)


Automatic frequency unit scaling:
- Hz
- kHz
- MHz

---

## 🏗️ Technical Highlights

- Structured menu-driven program design
- Input validation with error recovery
- Use of STL (`vector`, `map`, `algorithm`)
- Dynamic stage-by-stage filter modelling
- Engineering unit formatting
- ASCII schematic rendering
- Separation of interface and implementation
- Cross-platform compilation (Windows / macOS / Linux)

---
## 🧠 Concepts Demonstrated

This project showcases understanding of:

  - Analogue circuit modelling in software
  - Real-time CLI interaction loops
  - Defensive programming
  - Mathematical transformation of physical systems
  - Practical engineering utility design
  - Clean C++ modular structure

---
🚀 Potential Future Improvements

Add E24 / E48 / E96 resistor series

  - Include tolerance calculations
  - Add Bode magnitude response estimation
  - Implement automatic component sizing from target cutoff frequency

---
##👤 Author

Hamzah Zahid, Christoff Lotter & Aritro Roy
MEng Electronic & Electrical Engineering
