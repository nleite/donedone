#include <string>
#include "backend.h"
#include "configuration.h"
// Backend is a class that handles different backend implementations
// For now we are going to keep it to one file backend


using namespace std;
using namespace done;
namespace backend{

  // constructor implementation
  Backend::Backend() {
    hello = "from backend";
    // ...
  }

  std::string Backend::hi(){
    return hello;
  }

  Backend& load_backend(done::Config& config){
    std::string uri_schema = config.get_uri_schema();
    if (std::string("file").compare(uri_schema) == 0){
      static Backend fb = FileBackend(config.get_uri());
      return fb;
    }
    static Backend b = Backend();
    return b;
  }
}
