#include "student.h"

#include <string>
#include <vector>
#include "json.hpp"

using std::string;
using std::vector;
using json = nlohmann::json;

    Student::Student(string name):name(name) {}

    void Student::addScore(int score)
    {
        grades.push_back(score);
    }

    string Student::getName()
    {
        return this->name;
    }

    void to_json(json& jsonData, const Student& student)
    {
        jsonData = json{
            {"name",student.name},
            {"grades",student.grades}};
    }

    void from_json(const json& jsonData, Student& student)
    {
        jsonData.at("name").get_to(student.name);
        jsonData.at("grades").get_to(student.grades);
    }