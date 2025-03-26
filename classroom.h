#ifndef CLASSROOM_H
#define CLASSROOM_H

#include "student.h"

#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

class Classroom
{
private:
    int size;
    std::string teacher;
    int roomNumber;
    std::vector<Student> students;
public:
    Classroom();
    Classroom(std::string teacher, int roomNumber);
    Classroom(const Classroom& other);

    void addStudent(std::string name);

    std::string showStudents();

    // these methods are used by the json library. They require the friend keyword as they cannot be tied to a specific object 
    // but needs access to private data members (unless we want to use public ones instead)
    // The docs recommend to have them inside a 'namespace' but I wasn't able to try it out.

    friend void to_json(json& jsonData, const Classroom& classroom);

    friend void from_json(const json& jsonData, Classroom& classroom);
};

#endif