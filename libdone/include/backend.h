#pragma once
#include <string>
#include <vector>
#include "configuration.h"
#include "task.h"

using namespace std;
using namespace done;
namespace backend{

  class Backend {
    private:
      // empty for now
    protected:
      std::string hello;
      std::vector<Task> tasks;

    public:
      // constructor
      Backend(){
        hello = "from backend";
      }
      // virtual method
      virtual std::string hi(){return hello;};
      virtual std::vector<Task> get_tasks(){return tasks;};
  };

  class FileBackend: virtual public Backend {
    private:
      const std::string tasks_file;
      // friend bool operator ==(const FileBackend& a, const FileBackend& b);

    public:
      // constructor
      FileBackend(std::string tfp): tasks_file(tfp) {
        hello = "FileBackend";
      };

      virtual std::string hi();
      virtual std::vector<Task> get_tasks();
  };

  class BackendNotSupported : public std::exception {
    // not sure I need more than this for this type.
    private:
      const std::string unsupported;
    public:
      BackendNotSupported(const std::string& unsupported )
      : unsupported(unsupported){};

      char const* what() const noexcept;
  };


  // Backend& build_filebackend(done::Config& config){
  //   static Backend fb = FileBackend(config.get_uri());
  //   return fb;
  // }
  // // factory map
  // const std::map< std::string, Backend& (*func)(done::Config& config) > supported_backends = {
  //   {"file", build_filebackend}
  // };

  Backend& load_backend(done::Config& config);

}
