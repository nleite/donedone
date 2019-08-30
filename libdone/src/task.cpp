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

std::string Task::get_title() const { return title; }
int Task::get_id() const { return id; }

// operator overloading
std::ostream &operator<<(std::ostream &os, const Task &t) {
  std::string mark = "(x)";
  if (t.done) {
    mark = "(/)";
  }
  os << mark << "\t"
     << "title: " << t.get_title();
  return os;
}

//\ InvalidTask
const char *InvalidTask::what() const noexcept { return message.c_str(); }
