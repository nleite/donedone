#include "api.h"
#include "docopt.h"
#include <exception>
#include <iostream>
using namespace std;
using namespace done;

static const char USAGE[] =
    R"(donedone
  Usage:
    done list [-aoc] [-f FILE]

  Options:
    -a --all      List all tasks (including archived tasks)
    -o --open     List all tasks that have not yet been completed
    -c --closed   List all tasks that have been completed/accomplished
    -f FILE

)";

int main(int argc, const char **argv) {
  try {
    std::map<std::string, docopt::value> args =
        docopt::docopt(USAGE, {argv + 1, argv + argc}, true, "Done 0.1");
    if (args["list"]) {
      done::list_tasks();
    }
  } catch (const std::exception &e) {
    cout << e.what() << endl;
    return 1;
  }
  return 0;
}
