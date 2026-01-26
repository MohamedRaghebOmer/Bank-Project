# 🏦 Enterprise Bank Management System (C++)

![Language](https://img.shields.io/badge/Language-C++17-00599C.svg)
![Architecture](https://img.shields.io/badge/Architecture-Modular%20OOP-orange.svg)
![Data](https://img.shields.io/badge/Data-Flat%20File%20%28NoSQL%29-green.svg)

A robust, professional-grade simulation of a banking ecosystem built entirely in **C++**. This project is a mastery showcase of **Object-Oriented Design (OOD)** and **Low-Level Data Management**. 

Unlike standard applications that rely on SQL engines, this system implements a **custom-built data persistence layer**, handling all data serialization, parsing, and retrieval using **Flat Text Files**. This approach demonstrates a deep understanding of data structures, string manipulation, and algorithm efficiency without external dependencies.

--- 

## 🏗️ Architectural Design
The project follows a strict **Separation of Concerns** principle, dividing the application into three logical layers:

1.  **Core Layer (`src/Core`):** Contains Business Objects (`Client`, `User`, `Currency`) and logic. It has zero knowledge of the UI.
2.  **Screen Layer (`src/Screens`):** Handles all Console UI rendering and user inputs. It communicates only with the Core layer.
3.  **Utility Layer (`src/Lib`):** Helper classes for Date validation, String manipulation, and Input validation.

---

## 🚀 Key Features

### 1. 👥 Client Management (CRUD)
Complete lifecycle management for bank clients, implemented with direct file manipulation:
- **Add New Client:** Serializes object data and appends to `Clients.txt`.
- **Update/Delete:** Reads file into memory (vector), modifies the specific object, and rewrites the file (simulating a database commit).
- **Find Client:** Efficient linear search algorithms to retrieve client details by Account Number.

### 2. 💸 Transaction System
- **Deposit & Withdraw:** Real-time balance updates with strict validation (e.g., insufficient funds check).
- **Transfer:** Atomic transfer operations between two accounts.
- **Transfer Log:** Automatically records every transfer transaction into a `TransferLog.txt` file with timestamps.

### 3. 🔐 Security & Access Control
- **Authentication:** Secure Login/Logout mechanism.
- **Role-Based Access Control (RBAC):** Implemented using **Bitwise Operators**. This allows granular permission settings (e.g., a User can be allowed to *Add Clients* but blocked from *Deleting Clients*).
- **Login Register:** Audits all login attempts (Success/Fail) in `LoginRegister.txt`.

### 4. 💱 Currency Exchange Engine
A fully functional module for managing international currencies:
- **Currency Data:** Stores currency codes, names, and rates in `Currencies.txt`.
- **Exchange Calculator:** Converts amounts between any two currencies using USD as a base intermediate.
- **Update Rates:** Admin capability to modify exchange rates dynamically.

---

## 💾 Data Persistence (The "No-DB" Approach)
**This system does NOT use SQL, ADO.NET, or any external Database.**

Instead, it acts as its own Database Engine by implementing a custom **ORM (Object-Relational Mapping)** logic:
* **Serialization:** Converts C++ Objects $\rightarrow$ String Records (Line by line) with a custom separator (`#//#`).
* **Deserialization:** Parses String Lines $\rightarrow$ C++ Objects when loading data into memory.
* **Atomicity:** Ensures file integrity during write operations.

*Example of the internal data format:*
`A101#//#1234#//#John Doe#//#5000.00#//#Active`

---

## 📂 Project Structure (Refactored)

```text
📁 Bank-System-Root
├── 📁 src
│   ├── 📁 Core          # Business Entities (clsBankClient, clsUser, clsCurrency)
│   ├── 📁 Screens       # UI & Menus (clsMainScreen, clsLoginScreen)
│   ├── 📁 Lib           # Utilities (clsDate, clsString, clsUtil)
│   └── 📄 Main.cpp      # Entry Point
├── 📁 Data              # Text Files (The Database)
│   ├── 📄 Clients.txt
│   ├── 📄 Users.txt
│   └── 📄 Currencies.txt
└── 📄 README.md

```

---

## 📸 Screenshots

### Main Dashboard & Permissions

The system dynamically builds the menu based on the logged-in user's permissions (Bitwise check).

*(Add Screenshot Here)*

### Currency Exchange Menu

Real-time conversion and rate management interface.

*(Add Screenshot Here)*

---

## 🛠️ Getting Started

1. **Clone the Repository:**
```bash
git clone [https://github.com/YourUsername/Bank-System-CPP.git](https://github.com/YourUsername/Bank-System-CPP.git)

```


2. **Open in Visual Studio:**
* Open the `.sln` file.
* Ensure the `Data` folder is in the same directory as the executable (or update the file paths in `clsString.h` / Configuration).


3. **Build & Run:**
* Select **Release** mode for better performance.
* Run via Local Windows Debugger.



---

## 🔮 Future Improvements

* [ ] Implement an encryption algorithm for passwords in text files.
* [ ] Add an ATM interface module.
* [ ] Migrate the Data Layer to SQL Server (as a separate branch to compare implementations).

---

## ⚖️ License

This project is licensed under the MIT License.
