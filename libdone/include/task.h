#ifndef TASK_H_
#define TASK_H_
#pragma once
#include <iostream>
#include <json/value.h>
#include <string>

class Task {
private:
  int id;
  std::string title;
  int views_counter;
  std::string description;
  bool done;
  struct tm *create_date;
  struct tm *last_update;

  std::string compose_output() const;

public:
  // simple title constructor
  Task(std::string t);
  // json constructor
  Task(Json::Value *json);
  // getters
  int get_id() const;
  std::string get_title() const;
  bool is_done() const;
  std::string toString() const;
  // operator overloading
  friend std::ostream &operator<<(std::ostream &os, const Task &t);
};

class InvalidTask : public std::exception {
private:
  const std::string message;

public:
  InvalidTask(const std::string message = "Invalid Task") : message(message){};
  char const *what() const noexcept;
};
#endif // TASK_H_
