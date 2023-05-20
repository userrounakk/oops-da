#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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

int main()
{
    getStudents();
    return 0;
}
