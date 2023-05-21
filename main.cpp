#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* ************* declaration functions ************* */

void seperator();              // line seperator
void getStudents();            // fills data in students variable
void splitData(string, int);   // splits the student data from file and adds to students variable
void auth(int);                // call respecitive auth function
void studentAuth();            // middleware for student auth
void teacherAuth();            // middleware for teacher auth
int passCheck(string, string); // checks for passmatch and returns 1 if matched else 0

/* ************* end of function declaration ************* */

/* ************* declaring classes ************* */

class Class;
class Student;
class Teacher;

/* ************* end of class declaration ************* */

/* ************* defining classes ************* */

class Class
{
protected:
    string id;
    int strenght;
};

class Student : public Class
{

    string reg;
    string name;
    float marks[5];

public:
    void addData(string data[])
    {
        reg = data[0];
        name = data[1];
        id = data[2];
        for (int i = 0; i < 5; i++)
            marks[i] = stof(data[i + 3]);
    }
    string getName()
    {
        return name;
    }
    string getReg()
    {
        return reg;
    }
};

class Teacher : public Class
{
    int emp_id;
    string name;
};

/* ************* end of class definition ************* */

/* ************* defining global variables ************* */

#define totalStudents 385
Student students[totalStudents];
Student currentStudent;
Teacher currentTeacher;

/* ************* global variables end ************* */

int main()
{
    getStudents();
    int choice;
    seperator();
    cout << "Are you a stuedent or a teacher?" << endl
         << "1. Teacher" << endl
         << "2. Student" << endl
         << "3 Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    seperator();
    if (choice == 3)
        return 0;
    if (choice != 1 and choice != 2)
        cout << "Invalid choice" << endl;
    else
        auth(choice);
    return 0;
}

/* ************* defining functions ************* */

void seperator()
{
    cout << "*********************************************" << endl;
}

void getStudents()
{
    string line;
    ifstream fin;
    string lines[totalStudents];
    fin.open("student-record.csv");
    int i = 0;
    while (getline(fin, line))
        lines[i++] = line;
    for (int j = 0; j < totalStudents; j++)
        splitData(lines[j], j);
    fin.close();
}

void splitData(string s, int n)
{
    string data[8];
    int i = 0;
    int start, end = -1;
    do
    {
        start = end + 1;
        end = s.find(",", start);
        data[i++] = s.substr(start, end - start);
    } while (end != -1);
    students[n].addData(data);
}

void auth(int choice)
{
    if (choice == 1)
        teacherAuth();
    else
        studentAuth();
}

void studentAuth()
{
    string reg, pass;
    int res;
    cout << "Enter your reg number: ";
    cin >> reg;
    int found = -1;
    for (int i = 0; i < totalStudents; i++)
        if (students[i].getReg() == reg)
        {
            found = i;
            break;
        }
    if (found == -1)
        cout << "Student record not found please check your reg number" << endl;
    ifstream fin;
    string lines[totalStudents];
    string line;
    fin.open("student-auth.csv");
    int i = 0;
    while (getline(fin, line))
    {
        if (i == found)
        {
            res = passCheck(line, reg);
            if (res)
            {
                currentStudent = students[i];
                cout << "Welcome " << currentStudent.getName() << endl;
            };
        }
        i++;
    }
    fin.close();
    seperator();
}

void teacherAuth()
{
}

int passCheck(string line, string id)
{
    string pass;
    string data[2];
    int i = 0;
    int start, end = -1;
    do
    {
        start = end + 1;
        end = line.find(",", start);
        data[i++] = line.substr(start, end - start);
    } while (end != -1);
    data[1] = data[1].substr(0, data[1].length() - 1);
    if (data[0] == id)
    {
        cout << "Enter your password: ";
        cin >> pass;
        if (data[1] == pass)
        {
            return 1;
        }
        else
        {
            cout << "Invalid Password" << endl;
        }
    }
    return 0;
}
/* ************* end of function definitions ************* */