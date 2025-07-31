# <p align="center">PRODUCT INVENTORY MANAGEMENT SYSTEM</p>
<img width="1024" height="1024" alt="image" src="https://github.com/user-attachments/assets/6389a4f7-7e31-42b9-bf21-9d2b0f023e11" />


# 📋 Table of Contents

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Technology Used](#technology-used)
- [Setup & Installation](#setup-&-installation)
- [Systems Requirement](#systems-requirement)


# 📌 Overview

Product Inventory Management System is a console-based application designed to help administrators and users efficiently manage product inventories. It supports product addition, update, deletion, searching, reporting, backup and restore, and user authentication. The system uses C++ data structures and algorithms to ensure fast and reliable operations, and stores data in CSV files for easy access and backup.

# 🚀 Features

## 1. Add, update, delete, and search products
## 2. User and admin authentication with password encryption
## 3. View product lists and detailed product information
## 4. Generate overall sales and profit reports with ASCII graph visualization
## 5. Backup and restore product data to prevent data loss

# 📂 Project Structure

```
Project/
├── data/
│   ├── Backup_ProductList.csv
│   ├── History.csv
│   ├── OverallReport.csv
│   ├── ProductList.csv
│   └── userdata.csv
│
├── include/
│   ├── Authentication.h
│   ├── Constants.h
│   ├── Design_Structure.h
│   ├── FileManager.h
│   ├── ProductList.h
│   └── validation.h
│
├── src/
│   └── main.cpp
│
├── test/
│   └── main.exe
│
├── .gitignore
└── README.md

```

# 🌐 Technology Used

- C++ Programming Language
- Visual Studio Code ( IDE )
- GitHub ( Code Communication )

# 🛠️ Setup & Installation

## 1. Prerequisites

- VsCode

## 2. Clone the Repository

```
git clone https://github.com/Scar-king/Project_DataStructure-Algorithm.git
cd Project/src
```

## 4. Run the Program

Compile and execute the main Cpp file:
```
g++ main.cpp -o main

./main
```
# 💻 Systems Requirement

- **OS:** Windows 10 / macOS 10.15 (Catalina) / Linux (Ubuntu 20.04+ recommended)  
- **CPU:** Dual-core processor (Intel i3 or equivalent, 2.0 GHz or higher)  
- **RAM:** 4GB minimum (8GB recommended for smooth performance)  
- **Storage:** At least 200MB free space for program files and CSV data storage  
- **C++ Version:** C++17 or later (requires g++, MinGW, or