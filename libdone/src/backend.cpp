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

FileBackend::~FileBackend() {
  // swap the vector to clean its memory allocation
  std::vector<Task>().swap(tasks);
}

std::string FileBackend::hi() { return tasks_file; }

std::vector<Task> FileBackend::get_tasks() {
  load_tasks_from_file();
  return tasks;
}

void FileBackend::load_tasks_from_file() {
  // open file
  std::ifstream fp(tasks_file.c_str());
  // read file
  std::string line;
  Json::CharReader *reader = builder.newCharReader();
  while (std::getline(fp, line)) {
    Json::Value j;
    string errors;
    bool parsing_result =
        reader->parse(line.c_str(), line.c_str() + line.size(), &j, &errors);
    if (!parsing_result) {
      break;
    }
    // instanciate tasks
    // add Task to vector
    tasks.push_back(Task(&j));
  }
  // close file
  fp.close();
  // delete char reader
  delete reader;
}

//\ BackendNotSupported

const char *BackendNotSupported::what() const noexcept {
  return ("expected uri schema: \'" + unsupported + "\' is not supported")
      .c_str();
}

// Factory method

Backend *load_backend(done::Config *config) {
  std::string uri_schema = config->get_uri_schema();
  if (std::string("file").compare(uri_schema) == 0) {
    // TODO move supported URI prefixes to an util class
    std::string file_uri_prefix = "file://";
    std::string tfp = config->get_uri().substr(file_uri_prefix.length());
    static FileBackend *fb = new FileBackend(tfp);
    return fb;
  }
  throw backend::BackendNotSupported(uri_schema);
}
} // namespace backend
