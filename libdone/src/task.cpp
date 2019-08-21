#include "task.h"
#include <string>
#include <time.h>

//using namespace std;


Task::Task(std::string t){
    title = t;
    views_counter = 0;
    // initialize description with empty string
    description = "";
    done = false;
    time_t now;
    time( &now );
    create_date = gmtime( &now );
    last_update = gmtime( &now );
}

std::string Task::toString() const{
    return "title: " + title;
}

/*
// Overload operator<<
std::ostream& operator<< (std::ostream& os, const Task& t){
    return os << t.toString();
}
*/
