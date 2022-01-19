/*******************************************************************************
 * Name    : Student.cpp
 * Author  : Robert Miller
 * Version : 1.0
 * Date    : September 2, 2021
 * Description : Computes the square root of the command-line argument.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

class Student{
private:
string first_;
string last_;
int id_;
float gpa_;
public:
Student(string first, string last, int id, float gpa) : first_(first), last_(last), id_(id), gpa_(gpa) {};
string full_name() const{
	return first_ + ' ' + last_;
}
int id() const{
	return id_;
}
float gpa() const{
	cout << fixed << setprecision(2);
	return gpa_;
}
void print_info() const{
	cout << full_name() << ", GPA: " << gpa() << ", ID: " << id() << endl;
}
};

void print_students(const vector<Student> &students) {
	for(const auto &student : students){
	student.print_info();
	}
    // Iterates through the students vector, calling print_info() for each student.
}
vector<Student> find_failing_students(const vector<Student> &students) {
    vector<Student> failing_students;
	for(const auto &student : students){
	if(student.gpa() < 1.0){
		failing_students.push_back(student);
		}
	}
	if(failing_students.size() == 0){
		cout << " None";
	} else{
		cout << endl;
	}
    // Iterates through the students vector, appending each student whose gpa is
    // less than 1.0 to the failing_students vector.
    return failing_students;
}
/**
* Takes a vector of Student objects and prints them to the screen.
*/


int main() {
    string first_name, last_name;
    float gpa;
    int id;
    char repeat;
    vector<Student> students;
    do {
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name;
        gpa = -1;
        while (gpa < 0 || gpa > 4) {
            cout << "Enter student's GPA (0.0-4.0): ";
            cin >> gpa;
        }
        cout << "Enter student's ID: ";
        cin >> id;
        students.push_back(Student(first_name, last_name, id, gpa));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat;
    } while (repeat == 'Y' || repeat == 'y');
    cout << endl << "All students:" << endl;
    print_students(students);
    cout << endl << "Failing students:";
    print_students(find_failing_students(students));



    return 0;
}

