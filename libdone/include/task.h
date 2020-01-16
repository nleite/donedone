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
  bool is_due() const;
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

template <class Functor> class Eval {
public:
  Eval(Functor &f) : func(f){};
  template <typename A> bool operator()(A &arg) { return func(arg); };

private:
  Functor &func;
};

template <typename T, typename F> T filter(T list, F pred) {
  T ret;
  std::copy_if(list.begin(), list.end(), std::back_insert_iterator<T>(ret),
               Eval<F>(pred));
  return ret;
};

bool filter_done(const Task &t);
bool filter_open(const Task &t);
bool filter_due(const Task &t);
bool filter_all(const Task &t);

#endif // TASK_H_
