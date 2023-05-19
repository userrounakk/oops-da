#include <iostream>
using namespace std;

class Class
{
protected:
    string id;
    int strenght;
};

class Student : public Class
{
    int reg;
    string name;
    float marks[5];
};

class Teacher : public Class
{
    int emp_id;
    string name;
};