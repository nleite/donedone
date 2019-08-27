#pragma once
#include <string>
#include <vector>
#include <json/reader.h>
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
      void load_tasks_from_file();
      Json::CharReaderBuilder builder;

    public:
      // constructor
      FileBackend(std::string tfp): tasks_file(tfp) {
        hello = "FileBackend";
        builder.settings_["allowSingleQuotes"] = true;
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

  Backend& load_backend(done::Config& config);

}
