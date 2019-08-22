#pragma once
#include <cppunit/extensions/HelperMacros.h>
#include "configuration.h"

using namespace CppUnit;
using namespace std;
using namespace done;

class TestConfig : public CppUnit::TestFixture {
  private:
    // unit test macros
    CPPUNIT_TEST_SUITE( TestConfig );
    CPPUNIT_TEST( test_equality );
    CPPUNIT_TEST_SUITE_END();

    done::Config *cfg1, *cfg2, *cfg3;
    std::string cfg2_file_path = "test_config.cfg2";

  public:
    void setUp();
    void tearDown();
    void test_equality();
    //static CppUnit::Test* suite();

};
