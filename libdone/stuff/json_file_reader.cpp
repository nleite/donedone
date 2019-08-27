// to compile the file on macosx
// > g++ -arch x86_64 -stdlib=libc++ -O2 -L /usr/local/lib -std=c++1z -ljsoncpp -I /usr/local/include json_file_reader.cpp -o json
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <json/value.h>
#include <json/reader.h>
#include <json/writer.h>

using namespace std;

void write_json_file(std::string filename){
  vector<string> tasks = {
    "{'id': 1, 'title': 'some title', 'done': false }\n",
    "{'id': 2, 'title': 'other title', 'done': true }\n"
  };
  std::ofstream os ( filename );
  for(auto&& t: tasks){
    os << t;
  }
  os.close();
}


vector<Json::Value> read_json_from_file(std::string filename){
  vector<Json::Value> json_lines;
  Json::CharReaderBuilder builder;
  builder.settings_["allowSingleQuotes"] = true;
  Json::CharReader * reader = builder.newCharReader();
  std::ifstream in (filename);
  std::string line;
  while(std::getline(in, line)){
    Json::Value j;
    string errors;
    cout << "parsing: " << line << endl;
    bool parsing_result = reader->parse(line.c_str(), line.c_str() + line.size(), &j, &errors);
    if(!parsing_result){
      cout << errors << endl;
      break;
    }
    json_lines.push_back(j);
  }
  in.close();
  return json_lines;
}

int main(){
  std::string filename("/tmp/json_cpp.json");
  write_json_file(filename);
  auto vs = read_json_from_file(filename);
  Json::StyledStreamWriter writer;
  for (Json::Value v: vs){
    writer.write(cout, v);
    cout << "after parsing:" << v["done"].asString() << endl ;
  }
}
