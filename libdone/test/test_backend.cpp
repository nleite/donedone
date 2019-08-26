#include <cppunit/extensions/HelperMacros.h>
#include <typeinfo>
#include "test_configuration.h"
#include "test_backend.h"
#include "backend.h"

using namespace CppUnit;
using namespace std;
using namespace done;
using namespace backend;

void TestBackend::setUp(){
  std::string filename = "/tmp/backend.config.";
  std::string line = "uri=file:///good_file";
  generate_tmp_config_file(&filename, line);
  cfg = new Config(filename);
}

void TestBackend::tearDown(){
  std::string config_filename = cfg->get_config_file_path();
  delete_tmp_config_file(&config_filename);
  delete cfg;
}

void TestBackend::test_file_backend(){
  // dynamic cast to FileBackend
  auto be = dynamic_cast<FileBackend&>(backend::load_backend(*cfg));
  CPPUNIT_ASSERT_EQUAL(typeid(backend::FileBackend).name(), typeid(be).name());
}
