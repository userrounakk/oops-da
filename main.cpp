#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void seperator()
{
    cout << "*********************************************" << endl;
}
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
};

class Teacher : public Class
{
    int emp_id;
    string name;
};

Student students[385];

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

void getStudents()
{
    string line;
    ifstream fin;
    string lines[385];
    fin.open("student-record.csv");
    int i = 0;
    while (getline(fin, line))
        lines[i++] = line;
    for (int j = 0; j < 385; j++)
        splitData(lines[j], j);
    fin.close();
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

void studentAuth()
{
    string reg, pass;
    int res;
    cout << "Enter your reg number: ";
    cin >> reg;
    ifstream fin;
    string lines[385];
    string line;
    fin.open("student-auth.csv");
    int i = 0;
    while (getline(fin, line))
        lines[i++] = line;
    for (int j = 0; j < 385; j++)
    {
        res = passCheck(lines[j], reg);
        if (res)
        {
            cout << "Welcome " << students[j].getName() << endl;
            break;
        }
    }
    if (!res)
    {
        cout << "Student record not found please check your reg number" << endl;
    }
    fin.close();
    seperator();
}
void teacherAuth()
{
}
void auth(int choice)
{
    if (choice == 1)
        teacherAuth();
    else
        studentAuth();
}

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
