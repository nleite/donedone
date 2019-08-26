#include <string>
#include <fstream>
#include "configuration.h"

std::string trim(const std::string& source, const char* delims = " \t\r\n") {
  std::string result(source);
  std::string::size_type index = result.find_last_not_of(delims);
  if(index != std::string::npos){
    result.erase(++index);
  }
  index = result.find_first_not_of(delims);

  if(index == std::string::npos){
    result.erase();
  } else {
    result.erase(0, index);
  }
  return result;
}

namespace done {

  const std::string& Config::get_config_file_path(){
    return path;
  }

  // configuration from config file
  Config::Config(const std::string cfp): path(cfp){
    std::ifstream file(path.c_str());
    // loaded information vars
    std::string line;
    std::string key;
    std::string value;
    int eq_sign_pos;
    // iterate over file lines
    while (std::getline(file,line)) {
      if (line[0] == '#') continue;
      eq_sign_pos = line.find('=');
      key = trim(line.substr(0,eq_sign_pos));
      value = trim(line.substr(eq_sign_pos+1));
      // check for URI "uri".compare(key)
      if (keys[0].compare(key) == 0){
         uri = value;
      }
    }
  }

  const std::string& Config::get_uri(){
    return uri;
  }

  const std::string Config::get_uri_schema(){
    size_t column_sign_pos = uri.find(':');
    if(column_sign_pos == std::string::npos){
      throw BadUriSchema("schema delimiter (column sign ':') not found", uri);
    }
    return trim(uri.substr(0, column_sign_pos));
  }

  // Config operators
  bool operator ==(const Config& a, const Config& b){
    // check for reference addresses
    if (&a == &b){
      return true;
    }
    // check if uri and file path are the same
    if (a.uri.compare(b.uri) == 0 && a.path.compare(b.path) == 0){
      return true;
    }
    return false;
  }

  bool operator !=(const Config& a, const Config& b){
    // check for reference addresses
    return !(a == b);
  }

// Configuration Exceptions

  BadUriSchema::BadUriSchema(const std::string& message, const std::string& uri )
  : message(message), uri(uri) {}

  char const* BadUriSchema::what() const noexcept{
        return ("uri: \'"+uri+"\' is incorrect - " + message ).c_str();
  }
}
