# Bank Project With OOP 🏦

A comprehensive **Bank Management System** implemented in C++ using Object‑Oriented Programming (OOP) principles. This project simulates real‑world banking operations including account management, transactions, and persistent data storage, offering a robust CLI (command-line) experience.

---

## 🔍 Features

* **Account Management**:

  * Create new bank accounts
  * Edit or delete existing accounts
  * Search for customers by ID or name

* **Transactions**:

  * Deposit and withdraw funds
  * Transfer money between accounts
  * Check account balance

* **Persistence**:

  * Data is stored in files, ensuring information is saved across sessions
  * Transaction history is maintained for each account

* **OOP Design**:

  * Use of classes and encapsulation for account, transaction, and bank logic
  * Inheritance and polymorphism for different account types (if applicable)
  * Clean separation of concerns (UI / business logic / data storage)

* **User Interface**:

  * Text-based / console interface: simple, fast, and platform-independent
  * Menu-driven interaction for ease of use

* **Error Handling & Validation**:

  * Input validation to prevent invalid operations
  * Safe checks on withdrawal, transfers, etc.

---

## 🛠️ Why This Project Is Valuable

* It’s **large-scale and realistic** — more than a toy example.
* Demonstrates strong grasp of **OOP design patterns** in C++.
* Teaches how to build a **stateful application** with persistent data (files).
* Excellent project to showcase on your GitHub profile / portfolio for recruiters.
* Can serve as a foundation for future expansion (e.g., GUI, database integration).

---

## 🚀 Getting Started

### Prerequisites

* A C++ compiler (e.g., g++, MSVC)
* Basic build tools (make or just use IDE)
* Git (to clone the repository)

### Clone the Repository

```bash
git clone https://github.com/MohamedRaghebOmer/Bank-Project-With-OOP-.git
cd Bank-Project-With-OOP-
```

### Build & Run

If you're using a terminal / command-line environment:

```bash
g++ -std=c++17 -o BankApp main.cpp Account.cpp Transaction.cpp Bank.cpp
./BankApp
```

> **Note**: Replace `.cpp` file names with the actual ones in your project.

---

## ✅ How to Use

1. Run the application.
2. Choose from the main menu: create account / make transaction / view accounts / exit.
3. Follow on-screen prompts to enter user details, deposit / withdraw, or transfer money.
4. All data is saved in text files so next time you run, your accounts persist.

---

## 📚 What You’ll Learn / Demonstrate

* Core **OOP concepts** in C++ (classes, inheritance, encapsulation)
* File handling in C++ (reading/writing persistent data)
* Basic user-interface logic via console
* Data validation and error handling in a real-world-like scenario
* Modular code design

---

## 🧪 Future Improvements (Next Steps)

* Add **unit tests** for core classes (Account, Transaction, Bank)
* Move from plain files to a **lightweight database** (e.g., SQLite)
* Create a **GUI** (desktop or web) for better usability
* Implement **authentication** (PINs or passwords) for accounts
* Add **reporting** (monthly summaries, transaction history filtering)

---

## 🤝 Contributing

1. Fork the repository
2. Create a new branch: `git checkout -b feature/YourFeature`
3. Commit your changes: `git commit -m "Add some feature"`
4. Push to the branch: `git push origin feature/YourFeature`
5. Open a Pull Request

---

## 📄 License

This project is open-source and can be licensed under **MIT License**.
