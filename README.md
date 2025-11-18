# Client Management Console (C++)

A simple **console-based** client management application written in modern, easy-to-read C++. The program stores client records in a plain text file (`Clients.txt`) and provides a small menu-driven interface to add, list, find, update, and delete client records.

---

## Table of Contents

* [Features](#features)
* [Project Structure](#project-structure)
* [Clients data format](#clients-data-format)
* [Requirements](#requirements)
* [Build & Run (Visual Studio Community 2022)](#build--run-visual-studio-community-2022)
* [How to use](#how-to-use)
* [Key Functions / Modules](#key-functions--modules)
* [Possible Improvements](#possible-improvements)
* [License](#license)
* [Author](#author)

---

## Features

* Add one or multiple clients with validation for unique account numbers.
* List all clients in a formatted table.
* Find and display a client by account number.
* Update client details.
* Soft-delete clients (records removed from file when saved).
* Plain-text storage for portability and easy inspection.

## Project Structure

* `main.cpp` (or your single C++ source file)
* `Clients.txt` (data file used by the program; create it in the same folder as the executable)

> The supplied source is a single-file console app that reads/writes `Clients.txt` using a custom separator.

## Clients data format

Each client record is a single line in `Clients.txt`. Fields are joined using the separator `#//#` in this order:

1. `AccountNumber` (string)
2. `PINCode` (string)
3. `Name` (string)
4. `Phone` (string)
5. `AccountBalance` (double)

**Example line:**

```
123456#//#4321#//#John Doe#//#0123456789#//#1500.50
```

> Note: `AccountBalance` is parsed with `std::stod` — use dot (`.`) as a decimal separator.

## Requirements

* Visual Studio Community 2022 (recommended by author)
* C++ compiler with C++11 support (the code uses standard library features available since C++11)
* No external libraries required

## Build & Run (Visual Studio Community 2022)

1. Open Visual Studio Community 2022.
2. Create a new **Console App** (C++) project.
3. Replace the generated `main.cpp` content with the provided source file (or add it to the project).
4. Make sure project set to use the default C++ language standard (C++11 or later).
5. Build the project (`Build > Build Solution`).
6. Copy or create an empty `Clients.txt` file in the same folder as the executable (typically `$(ProjectDir)\$(Configuration)\`).
7. Run with `Debug > Start Without Debugging` (or Run) to see the menu.

## How to use

When the program runs it shows a main menu with options:

1. Show Client List — prints all clients in a table layout.
2. Add New Client — guided input; account numbers must be unique.
3. Delete Client — prompts for account number and asks for confirmation.
4. Update Client Info — allows editing client fields.
5. Find Client — prints detailed client card for a given account number.
6. Exit — close the program.

**Important**: Use numbers 1–6 to select operations. When adding or updating, follow on-screen prompts and press Enter to confirm inputs.

## Key Functions / Modules (short overview)

* `SplitString` — split a string by a delimiter into vector<string>.
* `ConvertLineToRecord` / `ConvertRecordToLine` — convert between `stClient` and its string representation.
* `LoadClientsDataFromFile` / `SaveClientDataToFile` — I/O helpers for `Clients.txt`.
* CRUD operations: `AddNewClient(s)`, `DeleteClientByAccountNumber`, `UpdateClientByAccountNumber`, `FindClientByAccountNumber`.
* Helper screens: `ShowMainMenueScreen`, `ShowClientsList`, `ShowAddNewClientScreen`, etc.

## Possible Improvements

* Add input validation for phone number and numeric fields.
* Use file locking or transaction approach to avoid corruption on concurrent runs.
* Migrate storage to a CSV or binary file, or a lightweight database (SQLite) for reliability.
* Improve UX with command-line arguments (e.g., `--import`, `--export`).
* Add unit tests for parsing and I/O functions.

## License

This repository is provided under the **MIT License** — feel free to reuse and adapt the code. If you prefer a different license, change the file accordingly.

## Author

Mohamed Ragheb Omar

---

