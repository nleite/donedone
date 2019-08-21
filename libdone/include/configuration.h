#pragma once
#include <string>

using namespace std;

namespace done {
  // default configuration file path
  const std::string default_config_path = "./.done/config";

  class Config {
    private:
      const std::string path;
      // uniform resource identifier (file://, http(s)://, kafka://, mongodb:// ...)
      // we determine the type of backend from the uri scheme
      std::string uri;
      // for more than one value allowed ...
      std::string keys[1] = {"uri"};
    public:

      // Constructor that takes a configuration file path value as argument
      Config(const std::string cfp);
      // delegating constructor
      Config(): Config(done::default_config_path){};

      // get the current set config file path
      const std::string& get_config_file_path();
      // get uri
      std::string const get_uri();
      // get schema uri
      std::string const get_uri_schema();
  };

}
