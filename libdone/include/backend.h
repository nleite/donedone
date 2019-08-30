#pragma once
#include "configuration.h"
#include "task.h"
#include <json/reader.h>
#include <string>
#include <vector>

using namespace std;
using namespace done;
namespace backend {

class Backend {
private:
  // empty for now
protected:
  std::string hello;
  std::vector<Task> tasks;

public:
  // constructor
  Backend() { hello = "from backend"; }
  virtual ~Backend(){};
  // virtual method
  virtual std::string hi() { return hello; };
  virtual std::vector<Task> get_tasks() = 0;
};

class FileBackend : virtual public Backend {
private:
  const std::string tasks_file;
  void load_tasks_from_file();
  Json::CharReaderBuilder builder;

public:
  // constructor
  FileBackend(std::string tfp) : tasks_file(tfp) {
    // hello = "FileBackend";
    builder.settings_["allowSingleQuotes"] = true;
  };
  ~FileBackend();
  std::string hi();
  std::vector<Task> get_tasks();
};

class BackendNotSupported : public std::exception {
  // not sure I need more than this for this type.
private:
  const std::string unsupported;

public:
  BackendNotSupported(const std::string &unsupported)
      : unsupported(unsupported){};

  char const *what() const noexcept;
};

// Factory method

Backend *load_backend(done::Config *config);
} // namespace backend
