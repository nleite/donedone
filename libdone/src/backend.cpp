#include "backend.h"
#include "configuration.h"
#include "task.h"
#include <fstream>
#include <string>
#include <typeinfo>

// Backend is a class that handles different backend implementations
// For now we are going to keep it to one file backend

using namespace std;
using namespace done;
namespace backend {

//\ FileBackend

std::string FileBackend::hi() { return hello; }

std::vector<Task> FileBackend::get_tasks() {
  load_tasks_from_file();
  return tasks;
}

void FileBackend::load_tasks_from_file() {
  // open file
  std::ifstream fp(tasks_file.c_str());
  cout << "tasks file: " << tasks_file.c_str() << endl;
  // read file
  std::string line;
  Json::CharReader *reader = builder.newCharReader();
  while (std::getline(fp, line)) {
    Json::Value j;
    string errors;
    bool parsing_result =
        reader->parse(line.c_str(), line.c_str() + line.size(), &j, &errors);
    if (!parsing_result) {
      cout << errors << endl;
      break;
    }
    // instanciate tasks
    // add Task to vector
    tasks.push_back(Task(j["title"].asString()));
  }
  // close file
  fp.close();
}

//\ BackendNotSupported

const char *BackendNotSupported::what() const noexcept {
  return ("expected uri schema: \'" + unsupported + "\' is not supported")
      .c_str();
}

// loose methods

Backend load_backend(done::Config *config) {
  std::string uri_schema = config->get_uri_schema();
  if (std::string("file").compare(uri_schema) == 0) {
    FileBackend fb = FileBackend(config->get_uri());
    return fb;
  }
  throw backend::BackendNotSupported(uri_schema);
}
} // namespace backend
