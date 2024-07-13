#define _CRT_SECURE_NO_WARNINGS

#include    <iostream>
#include    <cstdlib>
#include    <cstdio>
#include    <fstream>
#include    <string>

#include <sstream> //use break a sentence into chunk/individual string
#include <iomanip> //output of data e.g set pricision for fine amount

#include    "List.h"
#include    "LibStudent.h"
#include    "LibBook.h"

using namespace std;

bool ReadFile(string, List*);
bool DeleteRecord(List*, char*);
bool Display(List*, int, int);
bool InsertBook(string, List*);
bool SearchStudent(List*, char* id, LibStudent&);
bool computeAndDisplayStatistics(List*);
bool printStuWithSameBook(List*, char*);
bool displayWarnedStudent(List*, List*, List*);
int menu();


//functions for GUI/output
void displayWarning(string);
void bannerReadfile();
void bannerDeleteRec();
void bannerSearchStudent();
void bannerInsertBook();
void bannerDisplayStu();
void bannerDisplayStatistics();
void bannerprintStuWithSameBook();
void bannerDisplayWarnedStudent();

int main() {

    int opt, source, detail;
    char stu_id[8], call_num[20];
    List list,type1,type2;
    LibStudent libstudent;

    do {

        opt = menu();

        switch (opt) {
        case 1:
            bannerReadfile();
            if (!ReadFile("student.txt", &list)) {
                displayWarning("Unable to read file!");
            }
            system("pause");
            break;

        case 2:
            bannerDeleteRec();
            cout << "\t\t\t\t\t\t\t\t\t\t    Enter a student ID to delete record: ";
            cin >> stu_id; //1603679
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any remaining characters in the input buffer after reading input
            DeleteRecord(&list, stu_id);
            system("pause");
            break;

        case 3:
            bannerSearchStudent();
            cout << "\t\t\t\t\t\t\t\t\t\t    Enter a student ID to search student: ";
            cin >> stu_id; //1603679
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            SearchStudent(&list, stu_id, libstudent);
            system("pause");
            break;

        case 4:
            bannerInsertBook();
            if (!InsertBook("book.txt", &list)) {
                displayWarning("Unable to read file!");
            }
            system("pause");
            break;

        case 5:
            bannerDisplayStu();

            // Input validation loop for 'source'
            do {
                cout << "\n Where do you want to display the output (1 - File / 2 - Screen): ";
                cin >> source;
                if (cin.fail() || (source != 1 && source != 2)) {
                    cout << "\n Invalid choice! Please enter 1 or 2." << endl;
                    cin.clear();  // Clear the error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
                }
            } while (source != 1 && source != 2);

            // Input validation loop for 'detail'
            do {
                cout << "\n Do you want to display book list for every student (1 - YES / 2 - NO): ";
                cin >> detail;
                if (cin.fail() || (detail != 1 && detail != 2)) {
                    cout << "\n Invalid choice! Please enter 1 or 2." << endl;
                    cin.clear();  // Clear the error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
                }
            } while (detail != 1 && detail != 2);

            if (!Display(&list, source, detail)) {
                displayWarning("Failed to display records!");
            }
            system("pause");
            break;



        case 6:
            bannerDisplayStatistics();
            computeAndDisplayStatistics(&list);
            system("pause");
            break;

        case 7:
            bannerprintStuWithSameBook();
            cout << "\t\t\t\t\t\t\t\t\t\t    Enter a Call Number to get record: ";
            cin >> call_num; //1603679
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printStuWithSameBook(&list, call_num);
            system("pause");
            break;

        case 8:
            bannerDisplayWarnedStudent();
            displayWarnedStudent(&list, &type1 ,&type2 );
            system("pause");
            break;

        case 9:
            cout << "\n\t\t\t\t\t\t\t\t\t\t    > Exit <\n";
            break;


        default:
            system("cls");
            displayWarning("Invalid input");
            break;
        }
    } while (opt != 9);



    cout << "\n\n";
    system("pause");
    return 0;
}

// ======================================= Function 1 - bool ReadFile() =======================================

bool ReadFile(string file_name, List* list) {
    LibStudent student;
    string e_id[3], e_name[2], e_course[2], e_phone[3], duplicateId;
    ifstream inputFile(file_name);

    if (!inputFile) {
        displayWarning("Unable to read file!");
        return false;
    }
    else {
        while (!inputFile.eof()) {
            for (int i = 0; i < 3; i++) {
                inputFile >> e_id[i]; //eliminate unwanted string
            }
            inputFile >> student.id;

            for (int i = 0; i < 2; i++) {
                inputFile >> e_name[i]; //eliminate unwanted string
            }
            inputFile.ignore();
            inputFile.getline(student.name, 30);

            for (int i = 0; i < 2; i++) {
                inputFile >> e_course[i]; //eliminate unwanted string
            }
            inputFile >> student.course;

            for (int i = 0; i < 3; i++) {
                inputFile >> e_phone[i]; //eliminate unwanted string
            }
            inputFile >> student.phone_no;
            inputFile.ignore();

            bool duplicate = false;
            for (int i = 1; i <= list->size(); i++) {
                LibStudent tempStu;
                list->get(i, tempStu);
                if (strcmp(tempStu.id, student.id) == 0) {
                    duplicate = true;
                    duplicateId = student.id;
                    break;
                }
            }

            if (duplicate) {
                displayWarning("There is a duplicated record (" + duplicateId + ")");
            }
            else {
                list->insert(student);
            }
        }
    }


    inputFile.close();
    displayWarning(to_string(list->size()) + " records have been successfully read");
    return true;
}



// ======================================= End of Function 1 - bool ReadFile() =======================================


// ======================================= Function 2 - bool DeleteRecord() =======================================



bool DeleteRecord(List* list, char* id)
{

    Node* cur;
    cur = list->head;
    int posi = 1;

    // Check if the linked list is empty
    if (cur == NULL) {
        cout << "The list is empty. Please read file first !!" << endl;
        return false;
    }

    if (strlen(id) != 7)
    {
        cout << "Invalid Student ID." << endl;
        cout << "Hint: Student ID with 7 digit." << endl;
        return false;
    }
    else
    {
        while (cur != NULL) {
            if (strcmp(cur->item.id, id) == 0) //Compare the source string (item.id) with the target string id is true or false. If true will return to zero.
            {
                list->remove(posi); //If return to zero, then delete the id
                cout << "\nSuccessfully deleted record." << endl;

                // Display the updated contents of the linked list
                cout << "Update List Contents: \n" << endl;

                Node* cur = list->head;
                while (cur != NULL)
                {
                    cur->item.print(cout);
                    cout << "---------------------------------\n";
                    cur = cur->next;
                }

                return true;
            }

            cur = cur->next;  // Point to the following place to made the list complete
            posi++;
        }
    }

    // If the id is not match, then they system will show "This student does not exists".
    cout << "This student does not exist!" << endl;
    return false;

}



// ======================================= End of Function 2 - bool DeleteRecord() =======================================


// ======================================= Function 3 - bool SearchStudent() =======================================

bool SearchStudent(List* list, char* id, LibStudent& stu)
{
    Node* cur = list->head;// Start from head of linked list.
    if (list->empty()) // Check if the linked list is empty.
    {
        displayWarning("The list is empty. Please read file first ");
        return false;
    }
    if (strlen(id) != 7) 	// Check if the student ID has 7 digits.
    {
        cout << "\nInvalid Student Id! Id must has 7 digits" << endl;
        return false;
    }
    else
    {
        while (list != NULL) // Loop until list ended.
        {
            // compare student id with id input.
            if (strcmp(cur->item.id, id) == 0)
            {
                cur->item.print(cout);
                return true;

            }

            cur = cur->next; // Move to the next node in the linked list.

        }
        // If the loop completes without finding a match, the student doesn't exist in the linked list.
        cout << "\nThis Student Doesn't Exist!" << endl;
        return false;
    }
}


// ======================================= End of Function 3 - bool SearchStudent() =======================================


// ======================================= Function 4 - bool InsertBook() =======================================



// Calculate number of days between the due date and current date
int getNumberOfDueDay(int dueDay, int dueMonth, int dueYear, int curDay, int curMonth, int curYear) {
    // Convert the given due date to its Julian date
    int a_due = (14 - dueMonth) / 12;
    int y_due = dueYear + 4800 - a_due;
    int m_due = dueMonth + 12 * a_due - 3;
    int julian_due = dueDay + (153 * m_due + 2) / 5 + 365 * y_due + y_due / 4 - y_due / 100 + y_due / 400 - 32045;

    // Convert the given current date to its Julian date
    int a_cur = (14 - curMonth) / 12;
    int y_cur = curYear + 4800 - a_cur;
    int m_cur = curMonth + 12 * a_cur - 3;
    int julian_cur = curDay + (153 * m_cur + 2) / 5 + 365 * y_cur + y_cur / 4 - y_cur / 100 + y_cur / 400 - 32045;

    // Return difference between current date and due date
    return julian_cur - julian_due;
}

// Read book details from a file stream and populate them into a book structure
LibBook readBook(ifstream& inFile) {
    LibBook book;
    string info[8];

    // Read all the book details from the file
    for (int i = 0; i < 8; i++) {
        inFile >> info[i];
    }

    // Arrange author names directly
    for (char& c : info[0]) {
        if (c == '_') {
            c = ' ';
        }
    }

    // Arrange and store author names
    stringstream s_author(info[0]);
    for (int j = 0; j < 10 && getline(s_author, info[0], '/'); j++) {
        //delete[] book.author[j]; // Deallocate memory for existing author[j] to avoid memory leaks
        book.author[j] = new char[info[0].length() + 1];
        strcpy(book.author[j], info[0].c_str());
    }

    // Replacing underscores with spaces directly for title
    for (char& c : info[1]) {
        if (c == '_') {
            c = ' ';
        }
    }
    strcpy(book.title, info[1].c_str());

    // Replacing underscores with spaces directly for publisher
    for (char& c : info[2]) {
        if (c == '_') {
            c = ' ';
        }
    }

    strcpy(book.publisher, info[2].c_str());
    strcpy(book.ISBN, info[3].c_str());
    book.yearPublished = stoi(info[4]);
    strcpy(book.callNum, info[5].c_str());

    // Arrange date details for borrow date directly
    char separator;
    istringstream break_borrow_date(info[6]);
    break_borrow_date >> book.borrow.day >> separator >> book.borrow.month >> separator >> book.borrow.year;

    // Arrange date details for due date directly
    istringstream break_due_date(info[7]);
    break_due_date >> book.due.day >> separator >> book.due.month >> separator >> book.due.year;

    // Calculate total fine based on due date directly
    int curDate[3] = { 29, 3, 2020 }, dueDay;
    dueDay = getNumberOfDueDay(book.due.day, book.due.month, book.due.year, curDate[0], curDate[1], curDate[2]);
    if (dueDay > 0) {
        book.fine = dueDay * 0.5;
    }
    else {
        book.fine = 0;
    }

    return book;
}

// Insert book details from a file into the student list
bool InsertBook(string file_name, List* list)
{
    // Open the input file with the given file name.
    ifstream inFile(file_name);

    // Check if the file is successfully opened.
    if (inFile.is_open())
    {
        // Check if the list of students is empty.
        if (list->empty())
        {
            cout << "Student's detail are empty\n";
            return false;
        }
        else
        {
            string studentId;
            // Read student IDs from the file until the end of the file.
            while (inFile >> studentId)
            {
                // Convert the studentId from string to char array.
                char id[10];
                strcpy(id, studentId.c_str());

                // Initialize a pointer to keep track of the student (if found).
                Node* sID = NULL;

                // Check if there's a head node in the list.
                if (list->head != NULL)
                {
                    Node* current = list->head;
                    // Traverse the list to find the student with the matching ID.
                    while (current != NULL)
                    {
                        if (strcmp(current->item.id, id) == 0)
                        {
                            sID = current;
                            break;
                        }
                        current = current->next;
                    }
                }

                // Read the book details from the file.
                LibBook book = readBook(inFile);

                // If the student with the matching ID is found in the list.
                if (sID != NULL)
                {
                    bool isDuplicate = false;
                    // Check if the student already has the same book.
                    for (int i = 0; i < sID->item.totalbook; i++)
                    {
                        if (strcmp(sID->item.book[i].title, book.title) == 0)
                        {
                            isDuplicate = true;
                            break;
                        }
                    }

                    // If the book is not a duplicate.
                    if (!isDuplicate)
                    {
                        // Check if the student already has 15 or more books.
                        if (sID->item.totalbook >= 15)
                        {
                            cout << "Error: Student with ID " << string(sID->item.id) << " has more than 15 books.";
                        }
                        else
                        {
                            // Add the book to the student's list of books.
                            for (int i = 0; i < 15; i++)
                            {
                                if (strcmp(sID->item.book[i].title, " ") == 0)
                                {
                                    sID->item.book[i] = book;
                                    sID->item.totalbook++;
                                    sID->item.calculateTotalFine();
                                    break;
                                }
                            }
                        }
                    }
                }
                else
                {
                    // If the student with the given ID is not found in the list.
                    cout << "Student =" << studentId << ", are not founded\n";
                }
            }
        }
    }
    else
    {
        // If the file is not opened successfully.
        cout << "Unable to open file!\n";
        return false;
    }

    // If everything goes well.
    cout << "Insert book successfully\n";
    inFile.close();
    return true;
}






// ======================================= End of Function 4 - bool InsertBook() =======================================


// ======================================= Function 5 - bool Display() =======================================

bool Display(List* list, int source, int detail) {
    /*Description: This function prints student and possibly book information
                   to a specified source (file or screen).*/

    int studentCounter = 1;

    if (list->empty()) {
        displayWarning("List is empty. Kindly read student & book records first!");
        return false;
    }

    if (source == 1) { // Print to File
        ofstream outputFile;
        if (detail == 1) { // Student data + book data
            outputFile.open("student_booklist.txt");
        }
        else if (detail == 2) { // student data only
            outputFile.open("student_info.txt");
        }

        if (!outputFile) {
            displayWarning("Unable to open file!");// Display warning if unable to open file
            return false;
        }

        for (Node* current = list->head; current != NULL; current = current->next) {// Iterate through linked list of Student

            outputFile << "\nSTUDENT " << studentCounter++;
            current->item.print(outputFile);// Call print function and print student data into file

            if (detail == 1) {

                if (current->item.totalbook > 0) {
                    outputFile << "\nBOOK LIST: \n";
                    for (int i = 0; i < current->item.totalbook; i++) {
                        outputFile << "\nBook " << (i + 1) << "\n";
                        current->item.book[i].print(outputFile); // Call print function and print student data into file
                    }
                }
            }
            outputFile << "\n***************************\n";
        }
        outputFile.close(); // Close output file
    }
    else if (source == 2) { // Print to Screen
        for (Node* current = list->head; current != NULL; current = current->next) { // Iterate through linked list of Student

            cout << "\nSTUDENT " << studentCounter++;
            current->item.print(cout); // Call print function and print student data into file

            if (detail == 1) {
                if (current->item.totalbook > 0) {
                    cout << "\nBOOK LIST: \n";
                    for (int i = 0; i < current->item.totalbook; i++) { // Iterate through student's borrowed books
                        cout << "\nBook " << (i + 1) << "\n";
                        current->item.book[i].print(cout); // Call print function and print student data into file
                    }
                }
                else {
                    cout << "*** No books borrowed ***\n";
                }
            }
            cout << "\n***************************\n";
        }
    }

    return true;
}



// ======================================= End of Function 5 - bool Display() =======================================


// ======================================= Function 6 - bool computeAndDisplayStatistics() =======================================

bool courseExistOrNot(string courses[10][5], int numCourses, const string& course) { // function to check if a course already exists in the courses array
    for (int i = 0; i < numCourses; i++) {
        if (courses[i][0] == course) {
            return true;
        }
    }
    return false;
}

bool insertCourse(string courses[10][5], int& numCourses, const string& course) { // function to insert a new course into the courses array & initialize default value
    if (numCourses >= 10) {
        displayWarning("Maximum number of courses reached!");
        return false;
    }

    if (!courseExistOrNot(courses, numCourses, course)) {
        courses[numCourses][0] = course;
        courses[numCourses][1] = "0"; // Initialize the number of student of students to 0
        courses[numCourses][2] = "0"; // Initialize the total books borrowed of students to 0
        courses[numCourses][3] = "0"; // Initialize the total overdue books of students to 0
        courses[numCourses][4] = "0"; // Initialize the total overdue fine of students to 0
        numCourses++;
        return true;
    }
    return false;
}

void calNumberOfStudent(LibStudent student, string courses[10][5]) { // function to update the number of students for a specific course
    for (int i = 0; i < sizeof(courses[0]) / sizeof(courses[0][0]); i++) { // Iterate through course[][]
        if (student.course == courses[i][0]) {
            courses[i][1] = to_string(stoi(courses[i][1]) + 1); // get data from course[][], perform operation and assign new data to course[][]
            return;
        }
    }
}

void totalBooksBorrowed(LibStudent student, string courses[10][5]) { // function to update the total number of books borrowed for a specific course
    for (int i = 0; i < sizeof(courses[0]) / sizeof(courses[0][0]); i++) { // Iterate through course[][]
        if (student.course == courses[i][0]) {
            courses[i][2] = to_string(stoi(courses[i][2]) + student.totalbook); // get data from course[][], perform operation and assign new data to course[][]
            return;
        }
    }
}

void totalOverdueBooks(LibStudent student, string courses[10][5]) { // function to update the total number of overdue books for a specific course
    int currentDate[3] = { 29, 3, 2020 };

    for (int i = 0; i < sizeof(courses[0]) / sizeof(courses[0][0]); i++) { // Iterate through course[][]
        if (student.course == courses[i][0]) {
            int overdueBooks = 0;
            for (int j = 0; j < student.totalbook; j++) {  // Iterate through total books borrowed by student
                int dueDay = getNumberOfDueDay(student.book[j].due.day, student.book[j].due.month, student.book[j].due.year, currentDate[0], currentDate[1], currentDate[2]);
                if (dueDay > 0) {
                    overdueBooks++;
                }
            }

            courses[i][3] = to_string(stoi(courses[i][3]) + overdueBooks); // get data from course[][], perform operation and assign new data to course[][]
            return;
        }
    }
}

void totalOverdueFine(LibStudent student, string courses[10][5]) { // Function to update the total fine amount of overdue books for a specific course
    int currentDate[3] = { 29, 3, 2020 };
    float totalFine = 0.0;

    for (int i = 0; i < sizeof(courses[0]) / sizeof(courses[0][0]); i++) { // Iterate through course[][]
        if (student.course == courses[i][0]) {
            for (int j = 0; j < student.totalbook; j++) {
                int dueDay = getNumberOfDueDay(student.book[j].due.day, student.book[j].due.month, student.book[j].due.year, currentDate[0], currentDate[1], currentDate[2]);
                if (dueDay > 0) {
                    totalFine += student.book[j].fine; // Assuming there is a 'fine' field in the book structure.
                }
            }
            courses[i][4] = to_string(stof(courses[i][4]) + totalFine);  // get data from course[][], perform operation and assign new data to course[][]
            return;
        }
    }
}

void printStatTable(string courses[10][5], int numCourses) { // function to print the statistic in table form
    cout << "\t\t    +--------+--------------------+----------------------+---------------------+-------------------------+\n";
    cout << "\t\t    | Course | Number of Students | Total Books Borrowed | Total Overdue Books | Total Overdue Fine (RM) |\n";
    cout << "\t\t    +--------+--------------------+----------------------+---------------------+-------------------------+\n";
    for (int i = 0; i < numCourses; i++) {
        cout << "\t\t    | " << courses[i][0] << "\t | " << courses[i][1] << "\t\t\t\t  | " << courses[i][2] << "\t\t\t\t\t | " << courses[i][3] << "\t\t\t\t   | " << setprecision(2) << fixed << stof(courses[i][4]) << "\t\t\t\t\t |" << endl;
    }
    cout << "\t\t    +--------+--------------------+----------------------+---------------------+-------------------------+\n";
}

bool computeAndDisplayStatistics(List* list) {
    /*Description: This function calculate data and display in a table.*/

    string courses[10][5]; // assume there are no more than [10] courses
    int numCourses = 0;

    if (list->empty()) {
        displayWarning("List is empty. Kindly read student & book records first!");
        return false;
    }
    else {
        Node* current = list->head;

        while (current != NULL) {
            LibStudent student = current->item;
            insertCourse(courses, numCourses, student.course);
            calNumberOfStudent(student, courses);
            totalBooksBorrowed(student, courses);
            totalOverdueBooks(student, courses);
            totalOverdueFine(student, courses);
            current = current->next;
        }
        printStatTable(courses, numCourses);
    }

    return true;
}

// ======================================= End of Function 6 - bool computeAndDisplayStatistics() =======================================


// ======================================= Function 7 - bool printStuWithSameBook() =======================================

bool printStuWithSameBook(List* list, char* callNum) {
    if (list->empty()) {
        displayWarning("List is empty. Kindly read student & book record first!");
        return false;
    }
    else {
        int numOfStudent = 0;
        LibBook book[15];
        Node* current = list->head;
        while (current != NULL) {
            for (int i = 0; i < current->item.totalbook; i++) {
                if (strcmp(current->item.book[i].callNum, callNum) == 0) {
                    book[i] = current->item.book[i];
                    numOfStudent++;
                }
            }
            current = current->next;
        }

        if (numOfStudent == 0) {
            displayWarning("No students found who borrowed the book with call number " + string(callNum));
            return false;
        }
        else {
            cout << "\nThere are " << numOfStudent << " students that borrow the book with call number " << callNum << " as shown below:\n";

            current = list->head;
            while (current != NULL) {
                for (int i = 0; i < current->item.totalbook; i++) {

                    if (current->item.book[i].compareCallNum(book[i])) {
                        cout << "\nStudent ID = " << current->item.id;
                        cout << "\nName = " << current->item.name;
                        cout << "\nCourse = " << current->item.course;
                        cout << "\nPhone Number = " << current->item.phone_no;
                        cout << "\nBorrow Date: ";
                        current->item.book[i].borrow.print(cout);
                        cout << "\nDue Date: ";
                        current->item.book[i].due.print(cout);
                        cout << "\n\n";
                    }
                }
                current = current->next;
            }

            return true;
        }//QA76.73.C15K35  <-- tester
    }
}


// ======================================= End of Function 7 - bool printStuWithSameBook() =======================================


// ======================================= Function 8 - bool displayWarnedStudent() =======================================

int calculateTotalDays(int inputYear, int inputMonth, int inputDay)
{
    int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Determine if the provided year is a leap year
    if (inputYear % 4 == 0 && (inputYear % 100 != 0 || inputYear % 400 == 0))
        daysInMonth[1] = 29; // Update February's days for leap years

    // Compute days from the year 2000 up to the year before the provided year
    int totalDays = (inputYear - 2000) * 365 + (inputYear - 2000) / 4;

    // Adjust for years that are multiples of 100 but not of 400
    totalDays -= (inputYear - 2000) / 100;
    totalDays += (inputYear - 2000) / 400;

    // Add the days for completed months in the provided year
    for (int i = 0; i < inputMonth - 1; i++) {
        totalDays += daysInMonth[i];
    }

    // Incorporate days of the current month to the total
    totalDays += inputDay;

    return totalDays;
}



bool displayWarnedStudent(List* list, List* type1, List* type2) {
    LibBook book;

    // Check if the main list is empty.
    if (list->empty()) {
        displayWarning("List is empty. Kindly read student & book record first");
        return false;
    }

    int cur_date = calculateTotalDays(2020, 3, 29);

    // Start iterating over the main list from the head node.
    Node* curNode = list->head;
    while (curNode != NULL) {
        LibStudent student = curNode->item;
        int overdueCount = 0;
        bool allBooksOverdue = true;

        // Check each book of the current student
        for (int i = 0; i <= curNode->item.totalbook; i++) { // I change i < cur->item.total book to i <= cur->item.totalbook
            int due_date = calculateTotalDays(curNode->item.book[i].due.year, curNode->item.book[i].due.month, curNode->item.book[i].due.day);

            // Check if the book is overdue
            if (cur_date > due_date) {
                overdueCount++;
            }
            else {
                allBooksOverdue = false;
            }
        }

        // Check the conditions for type1 and type2
        if (overdueCount > 2 ) {  // more than 2 books are overdue for >= 10 days
            type1->insert(curNode->item);
        }
        if (curNode->item.total_fine > 50.0 && allBooksOverdue ) {  // total fine > RM50.00 and all books are overdue
            type2->insert(curNode->item);
        }
        curNode = curNode->next;
    }

    // Display student in type1 list.
    cout << "Type 1 Students: " << endl;
    Node* Type1 = type1->head;

    if (Type1 == NULL)
    {
        cout << endl;
        cout << "No student has more than 2 books that are overdue for >= 10 days. " << endl;
        cout << endl;
    }

    while (Type1 != NULL) {
        Type1->item.print(cout);
        cout << endl;
        Type1 = Type1->next;
    }

    // Display student in type2 list
    cout << "Type 2 Students: " << endl;
    Node* Type2 = type2->head;

    if (Type2 == NULL)
    {
        cout << endl;
        cout << "No student have a fine more than RM50.00" << endl;
        cout << endl;
    }

    while (Type2 != NULL) {
        Type2->item.print(cout);
        cout << endl;
        Type2 = Type2->next;
    }

    return true; 
}


// ======================================= End of Function 8 - bool displayWarnedStudent() =======================================


// ======================================= Function 9 - int menu() =======================================

void menuOutputOH() { //menu output to be call multiple time
    cout << "\nMenu\n\n";
    cout << "1. Read file.\n";
    cout << "2. Delete record.\n";
    cout << "3. Search student.\n";
    cout << "4. Insert book.\n";
    cout << "5. Display output.\n";
    cout << "6. Compute and Display Statistics.\n";
    cout << "7. Student with Same Book.\n";
    cout << "8. Display Warned Student.\n";
    cout << "9. Exit.\n";
    cout << "Enter your choice: ";
}

void menuOutput() { //menu output to be call multiple time
    string banner = R"(
             ___ __ __   ________    ________  ___   __        ___ __ __   ______   ___   __    __  __
            /__//_//_/\ /_______/\  /_______/\/__/\ /__/\     /__//_//_/\ /_____/\ /__/\ /__/\ /_/\/_/\
            \  \| \| \ \\    _  \ \ \__    _\/\  \_\\  \ \    \  \| \| \ \\  ___\/ \  \_\\  \ \\ \ \ \ \
             \        \ \\  (_)  \ \   \  \ \  \   `-\  \ \    \        \ \\ \/___/\\   `-\  \ \\ \ \ \ \
              \  \-/\  \ \\   __  \ \  _\  \ \__\   _    \ \    \  \-/\  \ \\  ___\/ \   _    \ \\ \ \ \ \
               \. \  \  \ \\  \ \  \ \/__\  \__/\\  \`-\  \ \    \  \  \  \ \\ \____/\\  \`-\  \ \\ \_\ \ \
                \__\/ \__\/ \__\/\__\/\________\/ \__\/ \__\/     \__\/ \__\/ \_____\/ \__\/ \__\/ \_____\/

            ===================================================================================================
                                            
                                            (1) Read file.
                                            (2) Delete record.
                                            (3) Search student.
                                            (4) Insert book.
                                            (5) Display output.
                                            (6) Compute and Display Statistics.
                                            (7) Student with Same Book.
                                            (8) Display Warned Student.
                                            (9) Exit.
                                          
)";


    cout << banner << endl;
    cout << "  Enter your choice: ";

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

// ======================================= End of Function 9 - int menu() =======================================

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

// ======================================= Function 1 - bool ReadFile() =======================================
void bannerReadfile() {
    system("CLS");
    string banner_readfile = R"(
                                             __   ___       __      ___         ___
                                            |__) |__   /\  |  \    |__  | |    |__
                                            |  \ |___ /~~\ |__/    |    | |___ |___
                                                                                                                
            ===================================================================================================
    )";

    cout << banner_readfile << endl;
}

// ======================================= Function 2 - bool DeleteRecord() =======================================
void bannerDeleteRec() {
    system("CLS");
    string banner_deleterecord = R"(


                                    __   ___       ___ ___  ___     __   ___  __   __   __   __
                                   |  \ |__  |    |__   |  |__     |__) |__  /  ` /  \ |__) |  \
                                   |__/ |___ |___ |___  |  |___    |  \ |___ \__, \__/ |  \ |__/
       
            ===================================================================================================
                                  
    )";

    cout << banner_deleterecord << endl;
}

// ======================================= Function 3 - bool SearchStudent() =======================================
void bannerSearchStudent() {
    system("CLS");
    string banner_search = R"(
                                __   ___       __   __           __  ___       __   ___      ___
                               /__` |__   /\  |__) /  ` |__|    /__`  |  |  | |  \ |__  |\ |  |
                               .__/ |___ /~~\ |  \ \__, |  |    .__/  |  \__/ |__/ |___ | \|  |
                                                                         
            ===================================================================================================
                                  
    )";

    cout << banner_search << endl;
}

// ======================================= Function 4 - bool InsertBook() =======================================
void bannerInsertBook() {
    system("CLS");
    string banner_insert = R"(
                                              __   ___  __  ___     __   __   __
                                      | |\ | /__` |__  |__)  |     |__) /  \ /  \ |__/
                                      | | \| .__/ |___ |  \  |     |__) \__/ \__/ |  \
                                                                         
            ===================================================================================================
                                  
    )";


    cout << banner_insert << endl;
}

// ======================================= Function 5 - bool Display() =======================================
void bannerDisplayStu() {
    system("CLS");
    string banner_display = R"(
                           __  ___       __   ___      ___               __      __   __   __
                          /__`  |  |  | |  \ |__  |\ |  |      /\  |\ | |  \    |__) /  \ /  \ |__/
                          .__/  |  \__/ |__/ |___ | \|  |     /~~\ | \| |__/    |__) \__/ \__/ |  \
                                                ___  __   __             ___    __
                                        | |\ | |__  /  \ |__)  |\/|  /\   |  | /  \ |\ |
                                        | | \| |    \__/ |  \  |  | /~~\  |  | \__/ | \|

            ===================================================================================================
                                  
    )";

    cout << banner_display << endl;
}
// ======================================= Function 6 - bool computeAndDisplayStatistics() =======================================
void bannerDisplayStatistics() {
    system("CLS");
    string banner_displayS = R"(
                                    __       ___                 __     __       ___  __
                                   |  \  /\   |   /\     | |\ | /__` | / _` |__|  |  /__`
                                   |__/ /~~\  |  /~~\    | | \| .__/ | \__> |  |  |  .__/
                                                        
            ===================================================================================================

    )";

    cout << banner_displayS << endl;
}
// ======================================= Function 7 - bool printStuWithSameBook() =======================================

void bannerprintStuWithSameBook() {
    system("CLS");
    string banner_samebook = R"(
                                      __  ___       __   ___      ___  __
                                     /__`  |  |  | |  \ |__  |\ |  |  /__`    |\ |
                                     .__/  |  \__/ |__/ |___ | \|  |  .__/    | \|
                                                                    
                            __   __   __   __   __        ___  __      __   __   __        __
                           |__) /  \ |__) |__) /  \ |  | |__  |  \    |__) /  \ /  \ |__/ /__`
                           |__) \__/ |  \ |  \ \__/ |/\| |___ |__/    |__) \__/ \__/ |  \ .__/
                                                                    
            ===================================================================================================

    )";

    cout << banner_samebook << endl;
}

// ======================================= Function 8 - bool displayWarnedStudent() =======================================

void bannerDisplayWarnedStudent() {
    system("CLS");
    string banner_warned = R"(
                                    __        ___  __      __  ___       __   ___      ___  __
                         |  |  /\  |__) |\ | |__  |  \    /__`  |  |  | |  \ |__  |\ |  |  /__`
                         |/\| /~~\ |  \ | \| |___ |__/    .__/  |  \__/ |__/ |___ | \|  |  .__/
                                                                       
            ===================================================================================================

    )";

    cout << banner_warned << endl;

}
