#include    <iostream>
#include    <fstream>
#include    <cstdlib>
#include    <cstdio>
#include    <ctime>
#include    "BST.h"
#include    "Student.h"

#include <sstream> //use break a sentence into chunk/individual string


using namespace std;

int menu();
bool readFile(const char* filename, BST* t1);
bool CheckDupliID(BST* t1, int ID);
bool CheckDupliID2(BTNode* cur, int ID);
bool isInteger(const string& input);

void displayWarning(string);

int main() {

    BST t1, t2;
    Student student;
    char file_name[12];

    int opt;

    do {
        opt = menu();

        switch (opt) {
        case 1:
            cout << "Read data to BST\n" << endl;
            if (!readFile("student.txt", &t1))
            {
                cout << "Cannot read file." << endl;
            }
            break;

        case 2:
            cout << "Print Deepest Nodes\n" << endl;
            if (!t1.deepestNodes())
            {
                cout << "\ndeepestNodes function not working ... \n\n ";
            }
            break;

        case 3:
        {
            cout << "Display Student\n" << endl;

            string input;  // Use a string to capture user input
            int order, source;
            bool input_order = false, input_source = false;

            while (!input_order || !input_source)
            {
                if (!input_order)
                {
                    // Let user input order of Output
                    cout << "\nEnter Order of Output (1 for asc || 2 for desc): ";
                    getline(cin, input);  // Use getline to capture entire line of input

                    if (isInteger(input))
                    {
                        order = stoi(input);
                        if (order == 1 || order == 2)
                        {
                            input_order = true;
                        }
                        else
                        {
                            cout << "\nError: Invalid 'order' parameter. Use 1 for ascending or 2 for descending.\n";
                        }
                    }
                    else
                    {
                        cout << "\nError: Please enter a valid number.\n";
                    }
                }

                if (input_order && !input_source)
                {
                    // Let user input source of output
                    cout << "\nEnter Source of Output (1 for screen || 2 for file): ";
                    getline(cin, input);

                    if (isInteger(input))
                    {
                        source = stoi(input);
                        if (source == 1 || source == 2)
                        {
                            input_source = true;
                        }
                        else
                        {
                            cout << "Error: Invalid 'source' parameter. Use 1 for screen or 2 for file." << endl;
                        }
                    }
                    else
                    {
                        cout << "\nError: Please enter a valid number.\n";
                    }
                }
            }


            if (!t1.display(order, source))
            {
                cout << "Display Error. \n";
            }

            break;
        }



        
        case 4:
            cout << "Clone Subtree\n" << endl;

            if (!t1.CloneSubtree(&t2, student)) {
                cout << "Cannot clone subtree." << endl;
            }

            break;

        case 5:
            cout << "Print Level Nodes\n" << endl;

            if (!t1.printLevelNodes()) {
                cout << "Unable to print BST." << endl;
            }
            break;

        case 6:
            cout << "Print Path\n" << endl;

            if (!t1.printPath()) {
                cout << "Unable to print path." << endl;
            }
            break;

        case 7:
            cout << "Exit\n" << endl;
            break;

        default:
            break;
        }

    } while (opt != 7);

    system("pause");
    return 0;
}

// ======================================= Start of - readfile() =======================================
bool readFile(const char* filename, BST* t1) {

    char string[30];
    int studNum = 0;
    int dupliID = 0;
    Student student;
    ifstream inFile(filename);


    while (!inFile.eof())
    {
        inFile >> string >> string >> string >> student.id;
        inFile >> string >> string;
        inFile.ignore();
        inFile.getline(student.name, 100);

        inFile >> string >> string;
        inFile.ignore();
        inFile.getline(student.address, 100);

        inFile >> string >> string >> student.DOB;

        inFile >> string >> string >> string >> student.phone_no;

        inFile >> string >> string >> student.course;

        inFile >> string >> string >> student.cgpa;

        if (CheckDupliID(t1, student.id)) {
            dupliID++;
            continue;
        }
        t1->insert(student);
        ++studNum;
    }

    if (dupliID > 0)
        cout << "\nThere are " << dupliID << " duplicated student records. \n";

    cout << "\n There are " << studNum << " student records have been successfully read!\n\n";

    return true;
}

bool CheckDupliID(BST* t1, int ID) {
    if (t1->root == NULL) return false;
    return CheckDupliID2(t1->root, ID);
}

bool CheckDupliID2(BTNode* cur, int ID) {
    if (cur == NULL) return false;
    if (cur->item.compare3(ID))
        return true;
    if (ID < cur->item.id)
        return CheckDupliID2(cur->left, ID);
    else
        return CheckDupliID2(cur->right, ID);
}
// ======================================= End of - readfile() =======================================




// ======================================= Start of - int menu() =======================================

void menuOutput() { //menu output to be call multiple time
    cout << "\n(1)    Read data to BST";
    cout << "\n(2)    Print deepest nodes";
    cout << "\n(3)    Display student";
    cout << "\n(4)    Clone Subtree";
    cout << "\n(5)    Print Level Nodes";
    cout << "\n(6)    Print Path";
    cout << "\n(7)    Exit";
    cout << "\nEnter your choice: ";
}

bool isInteger(const string& input) { // Function to check if input is an integer or not
    stringstream ss(input);
    int value;
    return (ss >> value) && ss.eof();
}

int menu() { //menu function to retrieve variable in main function
    int input;
    string inputStr;

    do {
        menuOutput();
        getline(cin, inputStr);

        if (isInteger(inputStr)) {
            input = stoi(inputStr);
            return input;
        }
        else {
            displayWarning("Invalid input. Kindly input an integer only!");
        }
    } while (true);
}

// ======================================= End of - int menu() =======================================


// ======================================= Other function =======================================

void displayWarning(string errorMessage) {
    const int totalWidth = 60;
    const int messageWidth = errorMessage.length() + 4;

    int leftPadding = (totalWidth - messageWidth) / 2;
    int rightPadding = totalWidth - messageWidth - leftPadding;

    cout << "\n\t\t\t\t\t\t\t";
    for (int i = 0; i < totalWidth; ++i) {
        cout << "*";
    }
    cout << endl;

    cout << "\t\t\t\t\t\t\t";
    cout << "* ";
    for (int i = 0; i < leftPadding; ++i) {
        cout << " ";
    }
    cout << errorMessage;
    for (int i = 0; i < rightPadding; ++i) {
        cout << " ";
    }
    cout << " *\n";

    cout << "\t\t\t\t\t\t\t";
    for (int i = 0; i < totalWidth; ++i) {
        cout << "*";
    }
    cout << endl;
}

// ======================================= Other function =======================================