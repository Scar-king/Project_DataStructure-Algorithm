#pragma once
#include <string>
using namespace std;

// Use inline so this can be shared across files without linker errors
inline const string INDENT = "\t\t\t\t\t\t\t\t";
inline const string TAB = "\t\t\t\t\t";

inline int MIN_STOCK = 0;
inline int MAX_STOCK = 10000;

inline double MIN_PRICE = 1.0;
inline double MAX_PRICE = 10000.0;

inline int MIN_ID = 1000;
inline int MAX_ID = 10000;

inline int MIN_OPTION = 0;
inline int MAX_OPTION = 4;

inline int MAX_SUBOPTION = 8;

inline int MAX_BACKUP_OPTION = 2;

inline int MAX_CHOICE = 3;

inline int MAX_AGE = 100;