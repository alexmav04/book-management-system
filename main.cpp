#include <iostream>
#include <string>
#include <Windows.h>
#include "menu.h"

using namespace std;

void mainMenu(void);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    system("color 4b");

    mainMenu();
    return 0;
}