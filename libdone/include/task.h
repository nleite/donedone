#include <string>

class Task{

    private:
        std::string title;
        int views_counter;
        std::string description;
        bool done;
        struct tm * create_date;
        struct tm * last_update;

    public:
        // simple title constructor
        Task(std::string t);
        std::string toString() const;
        //friend std::ostream& operator<< (std::ostream& os, const Task& t);
};
