#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::endl;

class Person
{
private:
    string name;
    string idNum;
public:
    Person(const string &nm, const string &id); //person constructor
    virtual ~Person();      //virtual destructors is a good idea
    virtual void print();                   //virtual allows compiler to know which print to call
    string getName() const { return name; }
    string getId() const { return idNum; }
};


class Student : public Person
{
private:
    string m_major;
    int gradYear;
public:
//student constructor has person and student members
    Student(const string &nm, const string &id, const string &mj, int gy);
    string getMajor() const { return m_major; }
    int getGradYear() const { return gradYear; }    //don't really need these getters
    void print(); //still need virtual down here
    void setMajor(const string &newMajor);
    void changeMajor(const string &newMajor);
};


int main()
{
    Person *p1 = new Person("Kyle", "123-45");
    Person *p2 = new Student("Megan", "345-67", "Communications", 2015);
    Student *s1 = new Student("Kyle G", "578-55", "Computer Science", 2020);

    p1->print();
    p2->print();

    s1->changeMajor("Electrical Engineering");
    s1->print();

    delete p1;
    delete p2;
    delete s1;

    return 0;
}

Person::Person(const string &nm, const string &id)
{
    name = nm;
    idNum = id;
}

Person::~Person()
{

}

void Person::print()
{
    cout << "Name: " << name << endl;
    cout << "IDNum: " << idNum << endl;
}
//this is how we tell the compiler which features from Person to inherit
Student::Student(const string &nm, const string &id, const string &mj, int gy)
 : Person(nm, id)
{
    m_major = mj;
    gradYear = gy;
}

void Student::print()
{
    cout << "Name: " << getName() << endl;
    cout << "IDNum: " << getId() << endl;
    cout << "Major: " << m_major << endl;
    cout << "Grad Year: " << gradYear << endl;
}

void Student::changeMajor(const string &newMajor)
{
    setMajor(newMajor);
}

void Student::setMajor(const string &newMajor)
{
    m_major = newMajor;
}