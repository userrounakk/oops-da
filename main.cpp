#include <iostream>
#include <fstream>
#include <string>
#define totalStudents 350
using namespace std;

/* ************* declaration functions ************* */

void seperator();                   // line seperator
void getStudents();                 // fills data in students variable
void getTeachers();                 // fils data in teachers variable
void splitStudentData(string, int); // splits the student data from file and adds to students variable
void splitTeacherData(string, int); // splits the teacher data from file and adds to teachers variable
void auth(int);                     // call respecitive auth function
void studentAuth();                 // middleware for student auth
void teacherAuth();                 // middleware for teacher auth
int passCheck(string, string);      // checks for passmatch and returns 1 if matched else 0
string trimfnc(string);

/* ************* end of function declaration ************* */

/* ************* declaring classes ************* */

class Class;
class Student;
class Teacher;

/* ************* end of class declaration ************* */

/* ************* defining classes ************* */

/*
 * TODO: Use scope resolution and define class at bottom
 */

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
    string getClass()
    {
        return id;
    }
};

Student students[totalStudents];
class Teacher : public Class
{
    string emp_id;
    string name;
    int studentCount;
    Student myStudents[35];

public:
    Teacher()
    {
        studentCount = 0;
    }
    void addData(string data[], int n)
    {
        emp_id = data[0];
        name = data[1];
        id = to_string(n + 1);
        for (int i = 35 * (10 - n - 1); i < 35 * (10 - n); i++)
        {
            // cout << students[i].getClass() << endl;
            if ((students[i].getClass()) == (id))
                myStudents[studentCount++] = students[i];
        }
    }
    string getEmpId()
    {
        return emp_id;
    }
    string getName()
    {
        return name;
    }
    void showStudents()
    {
        for (int i = 0; i < studentCount; i++)
        {
            cout << i + 1 << " " << myStudents[i].getName() << endl;
        }
    }
};

/* ************* end of class definition ************* */

/* ************* defining global variables ************* */

Teacher teachers[10];
Student currentStudent;
Teacher currentTeacher;

/* ************* global variables end ************* */

int main()
{
    getStudents();
    getTeachers();
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
    fin.open("student-record.csv");
    int i = 0;
    while (getline(fin, line))
        splitStudentData(line, i++);
    fin.close();
}

void getTeachers()
{
    string line;
    ifstream fin;
    fin.open("teacher-record.csv");
    int i = 0;
    while (getline(fin, line))
        splitTeacherData(line, i++);
    fin.close();
}

void splitStudentData(string s, int n)
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

void splitTeacherData(string s, int n)
{
    string data[3];
    int i = 0;
    int start, end = -1;
    do
    {
        start = end + 1;
        end = s.find(",", start);
        data[i++] = s.substr(start, end == -1 ? end - start + 1 : end - start);
    } while (end != -1);
    teachers[n].addData(data, n);
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
    string emp_id, pass;
    int res;
    cout << "Enter your Employee Id: ";
    cin >> emp_id;
    int found = -1;
    for (int i = 0; i < 10; i++)
        if (teachers[i].getEmpId() == emp_id)
        {
            found = i;
            break;
        }
    if (found == -1)
        cout << "Teacher record not found please check your Employee Id" << endl;
    ifstream fin;
    string line;
    fin.open("teacher-auth.csv");
    int i = 0;
    while (getline(fin, line))
    {
        if (i == found)
        {
            res = passCheck(line, emp_id);
            if (res)
            {
                currentTeacher = teachers[i];
                cout << "Welcome " << currentTeacher.getName() << endl;
            };
        }
        i++;
    }
    fin.close();
    seperator();
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
string trimfnc(string str)
{
    const char *typeOfWhitespaces = " \t\n\r\f\v";
    str.erase(str.find_last_not_of(typeOfWhitespaces) + 1);
    str.erase(0, str.find_first_not_of(typeOfWhitespaces));
    return str;
}
/* ************* end of function definitions ************* */