#define NOMINMAX //disable Windows.h from defining min/max macros
#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<ctime>
#include<algorithm>  // for std::find_if, std::not1, std::ptr_fun
#include<cctype>     // for isspace
#include<windows.h>
#include"BST.h"
#include"Student.h"

#pragma warning(push);
#pragma warning(disable: 4996);

using namespace std;

bool readFile(const char *, BST *);
string trim(const string&);
int menu();
void mainFunction();
void printMenu();

const int MAX_FILENAME = 50;
int option, source, order;
char fileName[MAX_FILENAME];
Student student;
BST t1, t2;


int main() {
 
	mainFunction();
	system("pause");
	return 0;
}

// Helper function to trim leading and trailing whitespace
string trim(const string& str) {
    auto start = find_if_not(str.begin(), str.end(), [](int c) { return isspace(c); });
    auto end = find_if_not(str.rbegin(), str.rend(), [](int c) { return isspace(c); }).base();
    return string(start, end);
}

bool readFile(const char* fileName, BST* t1) {
    if (!t1) {
        cerr << "\n\033[31mError: BST is null." << "\033[0m" << endl;
        return false;
    }

    ifstream readFile(fileName);
    if (!readFile.is_open()) {
        cerr << "\n\033[31mError: Cannot open file: " << fileName << "\033[0m" << endl;
        return false;
    }

    int recordCount = 0, count = 0;
    string readLine;

    while (getline(readFile, readLine, '=')) {
        Student student;

        // Read ID
        if (!(readFile >> student.id)) {
            cerr << "Error reading ID. Possibly malformed data." << endl;
            break;
        }
        readFile.ignore(numeric_limits<streamsize>::max(), '\n');

        // Read Name (and trim)
        getline(readFile, readLine, '=');
        getline(readFile, readLine);
        string trimmedName = trim(readLine);
        strcpy(student.name, trimmedName.c_str());  // Copy into char[]

        // Read Address (and trim)
        getline(readFile, readLine, '=');
        getline(readFile, readLine);
        string trimmedAddress = trim(readLine);
        strcpy(student.address, trimmedAddress.c_str());  // Copy into char[]

        // Read DOB (and trim)
        getline(readFile, readLine, '=');
        getline(readFile, readLine);
        string trimmedDOB = trim(readLine);
        strcpy(student.DOB, trimmedDOB.c_str());  // Copy into char[]

        // Read Phone No.
        getline(readFile, readLine, '=');
        if (!(readFile >> student.phone_no)) {
            cerr << "Error reading phone number. Expected a numeric value." << endl;
            break;
        }
        readFile.ignore(numeric_limits<streamsize>::max(), '\n');

        // Read Course (and trim)
        getline(readFile, readLine, '=');
        getline(readFile, readLine);
        string trimmedCourse = trim(readLine);
        strcpy(student.course, trimmedCourse.c_str());  // Copy into char[]

        // Read CGPA
        getline(readFile, readLine, '=');
        if (!(readFile >> student.cgpa)) {
            cerr << "Error reading CGPA. Expected a floating-point value." << endl;
            break;
        }
        readFile.ignore(numeric_limits<streamsize>::max(), '\n');

        if (t1->duplicate(t1->root, student)) {
            count++; //duplicate count++
            continue;
        }
        
        // Insert into BST
        if (!t1->insert(student)) {
            cerr << "Warning: Failed to insert student with ID: " << student.id << endl;
            continue;  // Skip but continue processing
        }
        recordCount++;
    }
   
    readFile.close();
    cout << "\n" << recordCount << " records have been successfully read from " << fileName << "." << endl;
    cout << "\n" << count << " duplicate records have been ingnored." << endl;
    return (recordCount > 0);  // Returns true if at least one record was read
}

int menu() {
    int option;
    bool validInput = false;

    do {
        printMenu();
        if (cin >> option) {
            if (option >= 1 && option <= 7) {
                validInput = true;
            }
            else {
                cout << "\n\033[31mERROR: Invalid option! Please enter 1-7.\033[0m\n\n";
                system("pause");
            }
        }
        else {
            cout << "\n\033[31mERROR: Invalid input! Please enter a number.\033[0m\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("pause");
        }
        
        system("cls");

    } while (!validInput);

    return option;
}

void mainFunction() {
    

    do {
        option = menu();
        system("cls");  // Clear screen at start of each iteration

        switch (option) {
        case 1:  // Read Data
            cout << "\nREAD DATA TO BST\n";
            cout << "-----------------\n";
            cout << "Enter filename (e.g., student.txt): ";
            cin >> fileName;
            if (!readFile(fileName, &t1)) {
                cout << "\n\033[31mERROR: Failed to read file!\033[0m\n";
            }
            break;

        case 2:  // Deepest Nodes
            cout << "\nDEEPEST NODES\n";
            cout << "--------------\n";
            if (t1.empty()) {
                cout << "\033[31mNo data available. Please read data first.\033[0m\n";
            }
            else {
                t1.deepestNodes();
            }
            break;

        case 3:  // Display Data
            cout << "\nDISPLAY OPTIONS\n";
            cout << "----------------\n";
            cout << "Output destination (1-Screen | 2-File): ";

            while (!(cin >> source) || (source != 1 && source != 2)) {
                cout << "\n\033[31mERROR: Invalid input! Please enter 1 or 2.\033[0m\n" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Output destination (1-Screen | 2-File): ";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nSort order (1-Ascending | 2-Descending): ";

            while (!(cin >> order) || (order != 1 && order != 2)) {
                cout << "\n\033[31mERROR: Invalid input! Please enter 1 or 2.\033[0m\n" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Sort order (1-Ascending | 2-Descending): ";
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (!t1.display(order, source)) {
                cout << "\n\033[31mERROR: Invalid display options!\033[0m\n";
            }
            break;

        case 4:  // Clone Subtree
            cout << "\nCLONE SUBTREE\n";
            cout << "--------------\n";
            cout << "Enter student ID to clone: ";
            cin >> student.id;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (!t2.cloneSubtree(t1, student)) {
                cout << "\n\033[31mERROR: Clone failed (ID not found or tree empty)\033[0m\n";
            }
            break;

        case 5:  // Level Order
            cout << "\nLEVEL ORDER TRAVERSAL\n";
            cout << "----------------------\n";
            if (t1.empty()) {
                cout << "\n\033[31mERROR: Tree is empty!\033[0m\n";
            }
            else if (!t1.printLevelNodes()) {
                cout << "\n\033[31mNOTE: Tree contains only root node\033[0m\n";
            }
            break;

        case 6:  // Print Paths
            cout << "\nEXTERNAL PATHS\n";
            cout << "---------------\n";
            if (t1.empty()) {
                cout << "\n\033[31mERROR: Tree is empty!\033[0m\n";
            }
            else if (!t1.printpath()) {
                cout << "\n\033[31mNOTE: Tree contains only root node\033[0m\n";
            }
            break;

        case 7:  // Exit
            cout << "EXITING PROGRAM\n";
            cout << "---------------\n\n";
            cout << "     /\\_/\\  \n";
            cout << "    ( o.o ) \n";
            cout << "     > ^ <  \n";
            cout << "    Goodbye!!!\n\n";
            break;

        default:
            cout << "\n\033[31mERROR: Invalid option (" << option << ")!\033[0m\n";
            cout << "Please enter 1-7.\n";
            break;
        }

        if (option != 7) {
            cout << "\n";
            system("pause");
            system("cls");
        }

    } while (option != 7);
}

void printMenu(){
    const char MENU[18][80] = {
        "\033[1m==========================================================        \033[0m\n",
        "                                                                            \n",
        "\033[31m          ,--./,-.                                               \033[0m\n",
        "\033[31m         / #      \\                                             \033[0m\n",
        "\033[31m        |          | \033[0m \033[32mBINARY SEARCH TREE MENU     \033[0m\n",
        "\033[31m         \\        /                                             \033[0m\n",
        "\033[31m          `._,._,'                                               \033[0m\n",
        "                                                                            \n",
        "\033[1m==========================================================        \033[0m\n",
        "1. Read data to BST\n",
        "2. Print deepest nodes\n",
        "3. Display student\n",
        "4. Clone Subtree\n",
        "5. Print Level Nodes \n",
        "6. Print Paths\n",
        "7. Exit\n",
        "----------------------------------------------------------\n",
        "Please select an option (1-7): ",
    };

    int len = sizeof(MENU) / sizeof(MENU[0]);
    
    for (int index = 0; index < len; index++) {
        cout << MENU[index];
        Sleep(0.09 * 1000);
    }

}