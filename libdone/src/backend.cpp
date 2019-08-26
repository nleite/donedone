#include <string>
#include "backend.h"
#include "configuration.h"
#include <typeinfo>
// Backend is a class that handles different backend implementations
// For now we are going to keep it to one file backend

using namespace std;
using namespace done;
namespace backend{



//\ FileBackend

  std::string FileBackend::hi(){
    return hello;
  }

  std::vector<Task> FileBackend::get_tasks(){
    return tasks;
  }


//\ BackendNotSupported

  const char* BackendNotSupported::what() const noexcept {
    return ("expected uri schema: \'"+unsupported+"\' is not supported" ).c_str();
  }


// loose methods

  Backend& load_backend(done::Config& config){
    std::string uri_schema = config.get_uri_schema();
    if (std::string("file").compare(uri_schema) == 0){
      static FileBackend fb = FileBackend(config.get_uri());
      return fb;
    }
    throw backend::BackendNotSupported(uri_schema);
  }
}
