#pragma once
#include <cppunit/extensions/HelperMacros.h>
#include "backend.h"
#include "configuration.h"
#include "test_configuration.h"

using namespace CppUnit;
using namespace std;
using namespace done;


class TestBackend : public CppUnit::TestFixture {

  private:
    done::Config *cfg;

    CPPUNIT_TEST_SUITE(TestBackend);
    CPPUNIT_TEST( test_file_backend );
    CPPUNIT_TEST_SUITE_END();

  public:

    void setUp();
    void test_file_backend();
    void tearDown();
};