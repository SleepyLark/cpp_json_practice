#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

class Student
{
private:
    std::vector<int> grades;
    std::string name;

public:
    Student(std::string name);

    void addScore(int score);

    std::string getName();

    friend void to_json(json& jsonData, const Student& student);

    friend void from_json(const json& jsonData, Student& student);
};

#endif