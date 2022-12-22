#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <vector>
#include <iomanip>

using namespace std;

void addData(void);
void deleteData(void);
void updateData(void);
void viewData(void);
void mainMenu(void);

bool isAdmin = false;

void adminOption(){
    int option;
    string password;
    if (!isAdmin){
        cout << "Please enter the password. Type \"q\" to turn back to Main Menu.: " << endl;
        cin >> password;
        if (password == "q"){
            mainMenu();
        }
        while (password != "admin"){
            cout << "Invalid password!" << endl;
            cout << "Try again. Type \"q\" to turn back to Main Menu.: " << endl;
            cin >> password;
            if (password == "q"){
                mainMenu();
            }
        }
    }
    isAdmin = true;
    cout << "\n" << endl;
    cout << "Choose one action: " << endl;
    cout << "1. Add Data" << endl;
    cout << "2. Delete Data" << endl;
    cout << "3. Update Data" << endl;
    cout << "4. View Table" << endl;
    cout << "5. Main Menu " << endl;
    cout << "6. Exit" << endl;

    cout << "Enter a number: " << endl;

    do {
        cin >> option;
        switch (option){
            case 1:
                addData();
                break;
            case 2:
                deleteData();
                break;
            case 3:
                updateData();
                break;
            case 4:
                viewData();
                break;
            case 5:
                mainMenu();
                break;
            case 6:
                system("cls");
                cout << "Exit the system." << endl;
                exit(0);
                break;

            default:
                cout << "That's invalid number." << endl;
                cout << "1. Add Data" << endl;
                cout << "2. Delete Data" << endl;
                cout << "3. Update Data" << endl;
                cout << "4. View Table" << endl;
                cout << "5. Main Menu " << endl;
                cout << "6. Exit" << endl;

                cout << "Enter a number: " << endl;
                break;
        }
    } while (option != 6);
}

void addData(){
    system("cls");
    fstream file("data.csv", ios::out | ios::app);

    if (!file){
        cout << "Data not found." << endl;
        exit(0);
    } else {
        cout << "---------- Add Data ----------" << endl;
    }
    string title, publishDate, author, price, isAdd;

    //input
    cout << "Title: " << endl;
    cin.get();
    getline(cin, title);
    cout << "Publish Date: " << endl;
    getline(cin, publishDate);
    cout << "Author: " << endl;
    getline(cin, author);
    cout << "Price: " << endl;
    getline(cin, price);

    //add data into the file.
    file << "\n" << title << ",";
    file << publishDate << ",";
    file << author << ",";
    file << price;
    file.close();

    cout << "Need to add more data? (y/n): " << endl;
    cin >> isAdd;

    if (isAdd == "y"){
        addData();
    } else if (isAdd == "n"){
        adminOption();
    } else {
        cout << "Invalid option. Need to add more data? (y/n): " << endl;
    }
}

void deleteData(){
    system("cls");
    fstream fin("data.csv", ios::in);
    fstream fout("data_v1.csv", ios::out);
    bool isDeleteData = false;
    bool isFirstLine = true;
    string line, content, titleBook;
    vector<string> info;
    
    cout << "Enter the title of the book you want to delete: " << endl;
    cin.get();
    getline(cin, titleBook);
    
    while (!fin.eof()){
        info.clear();
        getline(fin, line);
        stringstream ss1(line);

        while (getline(ss1, content, ',')){
            info.push_back(content);
        }
        
        int infoSize = info.size();

        if (info[0] != titleBook){
            if (!isFirstLine){
                fout << "\n";
            }
            isFirstLine = false;
            for (int i = 0; i < infoSize - 1; i++){
                fout << info[i] << ",";
            }
            fout << info[infoSize - 1];
        } else {
            isDeleteData = true;
        }
    }
    if (isDeleteData){
        cout << "The book is deleted." << endl;
        fin.close();
        fout.close();
        remove("data.csv");
        rename("data_v1.csv","data.csv");
    } else{
        cout << "The book not found." << endl;
        fin.close();
        fout.close();
        remove("data_v1.csv");
    }
    adminOption();
}

void updateData(){
    system("cls");
    fstream fin("data.csv", ios::in);
    fstream fout("data_v1.csv", ios::out);
    bool isUpdateData = false;
    bool isFirstLine = true;
    string line, content, titleBook, newContent;
    vector<string> info;
    int updateOpt;

    cout << "Enter the title of the book you want to update: " << endl;
    cin.get();
    getline(cin, titleBook);
    cout << "Enter which one you want to update" << endl;
    cout << "(1) title/(2) publish date/(3) author/(4) price/(5) Exit: " << endl;
    cin >> updateOpt;

    while (updateOpt != 1 && updateOpt != 2 && updateOpt != 3 && updateOpt != 4 && updateOpt != 5){
        cout << "Invalid Option." << endl;
        cout << "Enter which one you want to update" << endl;
        cout << "(1) title/(2) publish date/(3) author/(4) price/(5) Exit: " << endl;
        cin >> updateOpt;
    }
    if (updateOpt == 5){
        system("cls");
        adminOption();
    }
    cout << "Enter information: " << endl;
    cin.get();
    getline(cin, newContent);

    while (!fin.eof()){
        info.clear();
        getline(fin, line);
        stringstream ss1(line);
        
        while (getline(ss1, content, ',')){
            info.push_back(content);
        }
        int infoSize = info.size();

        if (info[0] != titleBook){
            if (!isFirstLine){
                fout << "\n";
            }
            isFirstLine = false;
            for (int i = 0; i < infoSize - 1; i++){
                fout << info[i] << ",";
            }
            fout << info[infoSize - 1];
        } else {
            if (!isFirstLine){
                fout << "\n";
            }
            isFirstLine = false;
            isUpdateData = true;
            stringstream ss2;
            ss2 << newContent;
            info[updateOpt - 1] = ss2.str();

            for (int i = 0; i < infoSize - 1; i++){
                fout << info[i] << ",";
            }
            fout << info[infoSize - 1];
        }
    }
    if (isUpdateData)
        cout << "The book has been updated!" << endl;
    else
        cout << "The book is not found!" << endl;
    
    fin.close();
    fout.close();
    remove("data.csv");
    rename("data_v1.csv","data.csv");
    adminOption();
}

void viewData(){
    system("cls");
    fstream file("data.csv");
    string title, publish_date, author, price;

    if (!file){
        cout << "Data not found." << endl;
        exit(0);
    }

    cout << "----------------------------------------" << "Books" << "----------------------------------------" << endl;
    cout << setw(30) << "title" << "  |" << setw(15) << "publish date" << "  |" << setw(20) << "author" << "  |"  << setw(10) << "price" << endl;
    cout << "-------------------------------------------------------------------------------------" << endl ;

    while(!file.eof()){
        getline(file, title, ',');
        getline(file, publish_date, ',');
        getline(file, author, ',');
        getline(file, price, '\n');

        cout << setw(30) << title << "  |" << setw(15) << publish_date << "  |" << setw(20) << author << "  |" << setw(10) << price << endl;
    }
    file.close();
    cout << "-------------------------------------------------------------------------------------" << endl ;

    if (isAdmin){
        adminOption();
    } else {
        mainMenu();
    }

}

void mainMenu(){
    if (isAdmin){
        system("cls");
    }
    int number;
    isAdmin = false;

    cout << "Login As: " << endl;
    cout << "1. Admin " << endl;
    cout << "2. Customer" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter the number: " << endl;

    cin >> number;
    switch (number){
        case 1:
            adminOption();
            break;

        case 2:
            isAdmin = false;
            viewData();
            break;

        case 3:
            exit(0);
            break;
    
    default:
        break;
    }

}

