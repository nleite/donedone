#include <cppunit/extensions/HelperMacros.h>
#include "test_configuration.h"
#include "configuration.h"

using namespace CppUnit;
using namespace std;
using namespace done;

CPPUNIT_TEST_SUITE_REGISTRATION( TestConfig );

void TestConfig::setUp(){
  cfg1 = new done::Config();
  cfg2 = new done::Config(cfg2_file_path);
  cfg3 = new done::Config();
}

void TestConfig::tearDown(){
  delete cfg1;
  delete cfg2;
  delete cfg3;
}

void TestConfig::test_equality(){
  CPPUNIT_ASSERT( *cfg1 == *cfg3);
}
