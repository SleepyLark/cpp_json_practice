#include "student.h"
#include "classroom.h"

#include <fstream>
#include "json.hpp"
#include <iostream>

using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
using std::cout;
using std::endl;
using json = nlohmann::json;

int main(int argc, char *argv[])
{
    Classroom myClassroom("gary",101);

    myClassroom.addStudent("frank");
    myClassroom.addStudent("ted");
    myClassroom.addStudent("john wick");
    myClassroom.addStudent("samatha");

    cout << myClassroom.showStudents() << endl;

    // calls the 'to_json()' method to serialize data members
    json jsonData = myClassroom;

    // create file and write to it
    std::ofstream output("classroom.json");
    output << std::setw(4) << jsonData << endl;

    // read a JSON file
    std::ifstream input("cool_classroom.json");
    json jsonToLoad;
    input >> jsonToLoad;

    // .get<your_type>() calls the 'from_json()' method to turn into an object based off of <your_type>
    // I think the way it works is that the object needs to have both a copy and default constructor in order to initial a new object.
    myClassroom = jsonToLoad.get<Classroom>();

    // should show different students
    cout << myClassroom.showStudents() << endl;

    // turn modify object to JSON
    jsonData = myClassroom;

    // as you should see, the object was serialized with the new values
    cout << std::setw(4) << jsonData << endl; 

    return 0;
}
