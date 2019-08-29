#include <iostream>
#include "backend.h"
#include "configuration.h"

using namespace std;
using namespace backend;

namespace done {

namespace { // annonymous namespace for private method implementation
Config load_config() {
  // TODO: allow to overide default config file path location
  return Config();
}
}

void list_tasks() {
  /// load configuration file
  Config cfg = load_config();
  // load the configured backend
  auto b = backend::load_backend(cfg);
  // read all tasks from backend

  // print tasks to stdout

  cout << "We got so far" << endl;
  cout << "Now with a backend: " << b.hi() << endl;
  cout << "Configuration file: " << cfg.get_config_file_path() << endl;
  cout << "found uri: " << cfg.get_uri() << endl;
}
}
