#pragma once
#include <string>
#include <exception>

using namespace std;

namespace done {
  // default configuration file path
  const std::string default_config_path = "/tmp/done/config";

  class Config {
    private:
      const std::string path;
      // uniform resource identifier (file://, http(s)://, kafka://, mongodb:// ...)
      // we determine the type of backend from the uri scheme
      std::string uri;
      // for more than one value allowed ...
      std::string keys[1] = {"uri"};
      // operator ==
      friend bool operator ==(const Config& a, const Config& b);
    public:

      // Constructor that takes a configuration file path value as argument
      Config(const std::string cfp);
      // delegating constructor
      Config(): Config(done::default_config_path){};

      // get the current set config file path
      const std::string& get_config_file_path();
      // get uri
      const std::string& get_uri();
      // get schema uri
      const std::string get_uri_schema();
  };


  class BadUriSchema : public std::exception {
    private:
      const std::string uri;
      const std::string message;

    public:
      BadUriSchema(const std::string& message, const std::string& uri );
      char const* what() const noexcept;
  };
}