#include <string>
#include <fstream>
#include "configuration.h"

std::string trim(std::string const& source, char const* delims = " \t\r\n") {
  std::string result(source);
  std::string::size_type index = result.find_last_not_of(delims);
  if(index != std::string::npos)
    result.erase(++index);

  index = result.find_first_not_of(delims);
  if(index != std::string::npos)
    result.erase(0, index);
  else
    result.erase();
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

  std::string const Config::get_uri(){
    return uri;
  }

  std::string const Config::get_uri_schema(){
    int column_sign_pos = uri.find(':');
    return trim(uri.substr(0, column_sign_pos));
  }

}
