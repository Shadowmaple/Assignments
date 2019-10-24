/*
课程：C++面向对象程序设计
题目：类族对象统计
要求：设计一个person类，派生出student类，在student类的基础上派生出undergraduate类。
为设计的三个类以不同的方式生成多个对象，然后统计每类对象数。

开发环境：Linux
编译器：g++
时间：2019.10.23
*/

# include <iostream>
# include <cstring>

using namespace std;

class Person {
private:
    static int count;
public:
    char name[10];
    int age;
    Person(const char *name, int age) {
        strcpy(this->name, name);
        this->age = age;
        this->count++;
    }
    ~Person() {count--;}
    static void show_count() {
        cout << "Person 类：" << count << endl;
    };
};

class Student : public Person {
private:
    static int count;
public:
    char sid[11]; // 学号
    Student(const char *name, int age, const char *sid):Person(name, age) {
        strcpy(this->sid, sid);
        count++;
    }
    static void show_count() {
        cout << "Student 类：" << count << endl;
    };
};

class Undergraduate : public Student {
private:
    static int count;
public:
    char academy[20];
    int grade;  // 年级
    Undergraduate(const char *name, int age, const char *sid, const char *academy, int grade):Student(name, age, sid) {
        strcpy(this->academy, academy);
        this->grade = grade;
        count++;
    }
    static void show_count() {
        cout << "Undergraduate 类：" << count << endl;
    };
};

int Person::count = 0;
int Student::count = 0;
int Undergraduate::count = 0;

int main() {
    Person p_1("Mick", 15);
    Student stu_1("Nick", 16, "2015214444");
    Student stu_2("Air", 26, "2012214344");
    Undergraduate ustu_1("Maple", 20, "2018214554", "计算机", 2018);

    // 输入各类对象的成员数
    cout << "各类对象数：" << endl;
    Person::show_count();
    Student::show_count();
    Undergraduate::show_count();

    return 0;
}
