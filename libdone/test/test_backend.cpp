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
  std::string line = "uri=file:///tmp/tasks_file";
  generate_tmp_config_file(&filename, line);
  cfg = new Config(filename);

  std::string nf = "/tmp/unsupported.";
  std::string nline = "uri=notgood:///good_file";
  generate_tmp_config_file(&nf, nline);
  unsupportedcfg = new Config(nf);
}

void TestBackend::tearDown(){
  std::string config_filename = cfg->get_config_file_path();
  delete_tmp_config_file(&config_filename);
  delete cfg;
  config_filename = unsupportedcfg->get_config_file_path();
  delete unsupportedcfg;
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
