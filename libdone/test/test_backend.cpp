#include <cppunit/extensions/HelperMacros.h>
#include <typeinfo>
#include <fstream>
#include "test_configuration.h"
#include "test_backend.h"
#include "backend.h"

using namespace CppUnit;
using namespace std;
using namespace done;
using namespace backend;

void write_tasks_file(std::string* filename){
  vector<string> tasks = {
    "{'id': 1, 'title': 'some title', 'done': false}\n",
    "{'id': 2, 'title': 'other title', 'done': true}\n"
  };
  std::ofstream fp;
  fp.open(filename->c_str());
  for(auto&& t: tasks){
    fp << t;
  }
  fp.close();
}

void delete_tasks_file(std::string* filename){
  std::remove(filename->c_str());
}

void TestBackend::setUp(){
  std::string filename("/tmp/backend.config.");
  std::string tasks_filename("/tmp/tasks_file.");
  add_alphanum_string(3, &tasks_filename);
  std::string line("uri=file://"+tasks_filename+"\n");
  generate_tmp_config_file(&filename, line);
  write_tasks_file(&tasks_filename);
  cfg = new Config(filename);

  std::string nf = "/tmp/unsupported.";
  std::string nline = "uri=notgood:///good_file";
  generate_tmp_config_file(&nf, nline);
  unsupportedcfg = new Config(nf);

  fe = new FileBackend(tasks_filename);
}

void TestBackend::tearDown(){
  std::string config_filename = cfg->get_config_file_path();
  delete_tmp_config_file(&config_filename);
  delete cfg;
  config_filename = unsupportedcfg->get_config_file_path();
  delete unsupportedcfg;
  delete fe;
}

void TestBackend::test_file_backend(){
  // dynamic cast to FileBackend
  auto be = dynamic_cast<FileBackend&>(backend::load_backend(*cfg));
  CPPUNIT_ASSERT_EQUAL(typeid(backend::FileBackend).name(), typeid(be).name());
}

void TestBackend::test_unsupported_schema(){
  CPPUNIT_ASSERT_THROW(
    backend::load_backend(*unsupportedcfg), backend::BackendNotSupported );
}

void TestBackend::test_filebackend_get_tasks_size(){
  vector<Task> tasks = fe->get_tasks();
  size_t expected = 2;
  CPPUNIT_ASSERT_EQUAL(expected, tasks.size());
}
