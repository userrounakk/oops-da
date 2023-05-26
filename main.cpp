#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#define totalStudents 350
using namespace std;

/* ************* declaration functions ************* */

void seperator();                                                      // line seperator
void getStudents();                                                    // fills data in students variable
void getTeachers();                                                    // fils data in teachers variable
void splitStudentData(string, int);                                    // splits the student data from file and adds to students variable
void splitTeacherData(string, int);                                    // splits the teacher data from file and adds to teachers variable
void auth(int);                                                        // call respecitive auth function
void studentAuth();                                                    // middleware for student auth
void teacherAuth();                                                    // middleware for teacher auth
int passCheck(string, string);                                         // checks for passmatch and returns 1 if matched else 0
float mean(int data[], int n);                                         // calculate mean of data
float sd(int data[], int n);                                           // calculate sd of data
int calculateGradePoint(int marks, int mean, int sd);                  // calculate grade point
char calculateGrade(int gradePoint);                                   // calculate grade
void showMarks();                                                      // display marks of all students of a class
void gradeDistribution(string subject, float mean, float sd);          // show grade cut offs for subjects
void showGradeDistribution(string subjects[], int means[], int sds[]); // layout for grade cut off table

/* ************* end of function declaration ************* */

/* ************* declaring classes ************* */

class Class;
class Student;
class Teacher;

/* ************* end of class declaration ************* */

/* ************* defining classes ************* */

/*
 * TODO: Use scope resolution and define class at bottom
 * TODO: Claculate grade of each student
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

public:
    float marks[5];
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

public:
    Student myStudents[35];
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
string subjects[] = {"English", "Maths", "Science", "Computer", "Social"};

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
    cout << "**********************************************************************************************************************" << endl;
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
    showMarks();
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
float mean(int data[], int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum += data[i];
    return sum / n;
}
float sd(int data[], int n)
{
    float m = mean(data, n);
    float sum;
    for (int i = 0; i < n; i++)
        sum += pow(m - data[i], 2);
    return sqrt(sum / (n - 1));
}
int calculateGradePoint(int marks, int mean, int sd)
{
    if (marks >= ceil(mean + 1.5 * sd))
        return 10;
    else if (marks >= ceil(mean + .5 * sd))
        return 9;
    else if (marks >= ceil(mean - .5 * sd))
        return 8;
    else if (marks >= ceil(mean - sd))
        return 7;
    else if (marks >= ceil(mean - 1.5 * sd))
        return 6;
    else if (marks >= ceil(mean - 2 * sd))
        return 5;
    return 0;
}

char calculateGrade(int gradePoint)
{
    char grades[] = {'S', 'A', 'B', 'C', 'D', 'E'};
    return gradePoint == 0 ? 'F' : grades[10 - gradePoint];
}

void showMarks()
{
    int marks[5][35];
    float avg[5];
    float sdData[5];
    int grade[35][5];
    float gpa[35];
    for (int i = 0; i < 35; i++)
    {
        marks[0][i] = currentTeacher.myStudents[i].marks[0];
        marks[1][i] = currentTeacher.myStudents[i].marks[1];
        marks[2][i] = currentTeacher.myStudents[i].marks[2];
        marks[3][i] = currentTeacher.myStudents[i].marks[3];
        marks[4][i] = currentTeacher.myStudents[i].marks[4];
    }
    for (int i = 0; i < 5; i++)
    {
        avg[i] = mean(marks[i], 35);
        sdData[i] = sd(marks[i], 35);
    }
    for (int i = 0; i < 35; i++)
    {
        grade[i][0] = calculateGradePoint(currentTeacher.myStudents[i].marks[0], avg[0], sdData[0]);
        grade[i][1] = calculateGradePoint(currentTeacher.myStudents[i].marks[1], avg[1], sdData[1]);
        grade[i][2] = calculateGradePoint(currentTeacher.myStudents[i].marks[2], avg[2], sdData[2]);
        grade[i][3] = calculateGradePoint(currentTeacher.myStudents[i].marks[3], avg[3], sdData[3]);
        grade[i][4] = calculateGradePoint(currentTeacher.myStudents[i].marks[4], avg[4], sdData[4]);
        gpa[i] = mean(grade[i], 5);
    }
    cout << left << setw(12) << setfill(' ') << "Reg No"
         << setw(20) << "Name"
         << "    " << right
         << setw(10) << subjects[0]
         << "    "
         << setw(10) << subjects[1]
         << "    "
         << setw(10) << subjects[2]
         << "    "
         << setw(10) << subjects[3]
         << "    "
         << setw(10) << subjects[4]
         << setw(10) << "GPA" << endl;
    for (int i = 0; i < 35; i++)
    {
        Student s = currentTeacher.myStudents[i];
        cout << left << setw(12) << setfill(' ') << s.getReg()
             << setw(20) << s.getName() << right
             << setw(10) << s.marks[0] << " (" << calculateGrade(grade[i][0]) << ")"
             << setw(10) << s.marks[1] << " (" << calculateGrade(grade[i][1]) << ")"
             << setw(10) << s.marks[2] << " (" << calculateGrade(grade[i][2]) << ")"
             << setw(10) << s.marks[3] << " (" << calculateGrade(grade[i][3]) << ")"
             << setw(10) << s.marks[4] << " (" << calculateGrade(grade[i][4]) << ")"
             << setw(10) << gpa[i] << endl;
    }
}

void gradeDistribution(string subject, float mean, float sd)
{
    cout << setw(5) << setfill(' ') << subject
         << setw(5) << " >= " << ceil(mean + 1.5 * sd)
         << setw(5) << " >= " << ceil(mean + .5 * sd) << " and < " << ceil(mean + 1.5 * sd)
         << setw(5) << " >= " << ceil(mean - .5 * sd) << " and < " << ceil(mean + .5 * sd)
         << setw(5) << " >= " << ceil(mean - sd) << " and < " << ceil(mean - .5 * sd)
         << setw(5) << " >= " << ceil(mean - 1.5 * sd) << " and < " << ceil(mean - sd)
         << setw(5) << " >= " << ceil(mean - 2 * sd) << " and < " << ceil(mean - 1.5 * sd)
         << setw(5) << " <" << ceil(mean - 2 * sd) << endl;
}
void showGradeDistribution(string subjects[], int means[], int sds[])
{
    cout << setw(5) << setfill(' ') << "Subject"
         << setw(5) << "      "
         << "S"
         << setw(5) << "               "
         << "A"
         << setw(5) << "               "
         << "B"
         << setw(5) << "               "
         << "C"
         << setw(5) << "               "
         << "D"
         << setw(5) << "               "
         << "E"
         << setw(5) << "F" << endl;
    for (int i = 0; i < 5; i++)
        gradeDistribution(subjects[i], means[i], sds[i]);
    seperator();
}
/* ************* end of function definitions ************* */