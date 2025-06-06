#include <iostream>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define WHITE   "\033[37m"

void welcome(){
    cout << GREEN << R"(
   ___              __         __    __  ___                                       __    
  / _ \_______  ___/ /_ ______/ /_  /  |/  /__ ____  ___ ____ ____ __ _  ___ ___  / /_   
 / ___/ __/ _ \/ _  / // / __/ __/ / /|_/ / _ `/ _ \/ _ `/ _ `/ -_)  ' \/ -_) _ \/ __/   
/_/  /_/  \___/\_,_/\_,_/\__/\__/ /_/  /_/\_,_/_//_/\_,_/\_, /\__/_/_/_/\__/_//_/\__/    
                                                        /___/                            
    )" << RESET << endl;
}