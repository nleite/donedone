#include "task.h"
#include <iostream>
#include <json/value.h>
#include <string>
#include <time.h>

Task::Task(std::string t) {
  title = t;
  views_counter = 0;
  // initialize description with empty string
  description = "";
  done = false;
  time_t now;
  time(&now);
  create_date = gmtime(&now);
  last_update = gmtime(&now);
}

Task::Task(Json::Value *json) {
  if (!json->isMember("id") || !json->isMember("title")) {
    throw InvalidTask("no `id` or `title` key found in the json object");
  }
  id = json->get("id", -1).asInt();
  title = json->get("title", "").asString();
  description = json->get("description", "no description").asString();

  done = json->get("done", false).asBool();
}

std::string Task::toString() const { return "title: " + title; }

// getters
std::string Task::get_title() const { return title; }
int Task::get_id() const { return id; }
bool Task::is_done() const { return done; }

std::string Task::compose_output() const {
  std::string sign = done ? "(/)" : "(x)";
  std::string start(sign);
  std::string end = "";
  if (done) {
    start.append("\e[9m");
    end = "\e[0m";
  }
  return start + title + end;
}

bool Task::is_due() const {
  // TODO : evaluate task due date with current time and return true if due time
  // has passed
  return false;
}

// operator overloading
std::ostream &operator<<(std::ostream &os, const Task &t) {
  os << t.compose_output();
  return os;
}

//\ InvalidTask
const char *InvalidTask::what() const noexcept { return message.c_str(); }

//\ Task filter methods
bool filter_all(const Task &t) { return true; }
bool filter_done(const Task &t) { return t.is_done(); }
bool filter_due(const Task &t) { return t.is_due(); }
bool filter_open(const Task &t) { return !t.is_done(); }
