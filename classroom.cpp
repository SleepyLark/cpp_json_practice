#include "classroom.h"

#include "student.h"
#include <ctime>
#include <string>
#include <vector>

using std::string;
using std::vector;
using json = nlohmann::json;

Classroom::Classroom(): size(0), teacher("unknown"), roomNumber(0) {}
Classroom::Classroom(string teacher, int roomNumber): size(0), teacher(teacher), roomNumber(roomNumber) {}

Classroom::Classroom(const Classroom& other)
{
    teacher = other.teacher;
    roomNumber = other.roomNumber;
    size = other.size;
    students = vector<Student>(other.students);
}

void Classroom::addStudent(string name)
{
    std::srand(time(0));

    Student newStudent(name);
    for(int i = 0; i < 10; i++)
    {
        int randomScore = std::rand() % 101;
        newStudent.addScore(randomScore);
    }

    students.push_back(newStudent);
    size++;
}

string Classroom::showStudents()
{
    string list;
    for(Student& student : students)
    {
        list += student.getName() + ", ";
    }

    return list;
}

void to_json(json& jsonData, const Classroom& classroom)
{
    jsonData = json{
        {"size",classroom.size}, 
        {"teacher",classroom.teacher},
        {"roomnumber",classroom.roomNumber},
        {"students",classroom.students}};
        // because students is a vector of a specific object, 
        // that object will need to have it's own working 'to_json' and 'from_json' in order for this to work
}

void from_json(const json& jsonData, Classroom& classroom)
{
    jsonData.at("size").get_to(classroom.size);
    jsonData.at("teacher").get_to(classroom.teacher);
    jsonData.at("roomnumber").get_to(classroom.roomNumber);

    // there may be a way to get it to load a json for a list of a specific object, but for now this way works too
    // similar to how copy constructors work, we'll need to get the data from the json and use it to make a new student to be added to the list
    vector<Student> studentsToLoad;
    for (const auto& studentJson : jsonData.at("students")) 
    {
        string name = studentJson.at("name").get<string>();  // Get the name from the JSON
        Student studentToAdd(name);  // Create a Student object using the constructor with the name

        for(const auto& scoreJson : studentJson.at("grades"))
        {
            // copy data from json into the student's list
            studentToAdd.addScore(scoreJson);
        }

        studentsToLoad.push_back(studentToAdd);  // Add the student to the temporary vector.
    }

    classroom.students = studentsToLoad; // replace vector with our new vector of students.
}