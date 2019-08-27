#pragma once
#include <string>
#include <json/value.h>

class Task{

  private:
    int id;
    std::string title;
    int views_counter;
    std::string description;
    bool done;
    struct tm * create_date;
    struct tm * last_update;

  public:
    // simple title constructor
    Task(std::string t);
    // json constructor
    Task(Json::Value* json);
    // getters
    int get_id() const;
    std::string get_title() const;
    std::string toString() const;
};


class InvalidTask : public std::exception {
  private:
    const std::string message;
  public:
    InvalidTask(const std::string message = "Invalid Task") : message(message) {};
    char const* what() const noexcept;
};
