#pragma once
#include "backend.h"
#include "configuration.h"
#include "test_configuration.h"
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;
using namespace std;
using namespace done;

class TestBackend : public CppUnit::TestFixture {

private:
  done::Config *cfg, *unsupportedcfg, *defaultcfg;
  backend::FileBackend *fe;
  backend::FileBackend *defaultbe;

  CPPUNIT_TEST_SUITE(TestBackend);
  CPPUNIT_TEST(test_file_backend);
  CPPUNIT_TEST(test_unsupported_schema);
  CPPUNIT_TEST(test_filebackend_get_tasks_size);
  CPPUNIT_TEST(test_default_config_tasks_size);
  CPPUNIT_TEST(test_default_config_task_filename);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();
  void test_file_backend();
  void test_unsupported_schema();
  void test_filebackend_get_tasks_size();
  void test_default_config_tasks_size();
  void test_default_config_task_filename();
};
