#include <string>
#include "configuration.h"
#include "task.h"

using namespace std;
using namespace done;
namespace backend{

  class Backend {
    // empty for now
    private:

    protected:
      std::string hello;
      // current set of tasks available
      // std::vector<Task> tasks;

    public:
      // constructor
      Backend();
      std::string hi();
  };

  class FileBackend: public Backend {
    private:
      const std::string tasks_file;

    public:
      FileBackend(std::string tfp): tasks_file(tfp) {
        hello = "FileBackend";
      };
  };

  Backend& load_backend(done::Config& config);
}
