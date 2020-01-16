#include "backend.h"
#include "configuration.h"
#include "task.h"
#include <iostream>

using namespace std;
using namespace backend;

namespace done {

namespace { // annonymous namespace for private method implementation
Config load_config() {
  // TODO: allow to overide default config file path location
  return Config();
}

void list_tasks(bool done, bool due) {
  /// load configuration file
  Config cfg = load_config();
  // load the configured backend
  auto b = backend::load_backend(&cfg);
  // read all tasks from backend
  std::vector<Task> tasks = b->get_tasks();
  if (done) {
    tasks = filter(tasks, filter_done);
  }

  if (due) {
    tasks = filter(tasks, filter_due);
  }

  for (Task t : tasks) {
    cout << t << endl;
  }
  delete b;
}
} // namespace
typedef void (*filter_function)(Task &t);

void filtered(filter_function f) {
  Config cfg = load_config();
  auto b = backend::load_backend(&cfg);
  std::vector<Task> tasks = filter(b->get_tasks(), f);
  for (Task t : tasks) {
    cout << t << endl;
  }
  delete b;
};

void list_tasks_all() { list_tasks(false, false); }
void list_tasks_done() { list_tasks(true, false); }
void list_tasks_open() { filtered(filter_open); }
void list_tasks_due() { list_tasks(false, true); }

} // namespace done
