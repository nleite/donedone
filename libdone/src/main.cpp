#include <iostream>
#include <exception>
#include "task.h"
#include "api.h"
using namespace std;
using namespace done;
int main() {
  try {
    Task t = Task("hello");
    done::list_tasks();
  } catch (const std::exception &e) {
    cout << e.what() << endl;
  }
}
