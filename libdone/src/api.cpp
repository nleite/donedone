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
} // namespace

void list_tasks() {
  /// load configuration file
  Config cfg = load_config();
  // load the configured backend
  auto b = backend::load_backend(&cfg);
  // read all tasks from backend
  std::vector<Task> tasks = b->get_tasks();
  // print tasks to stdout
  cout << "tasks size" << tasks.size() << endl;

  for (Task t : tasks) {
    cout << t << endl;
  }
  delete b;
}
} // namespace done
