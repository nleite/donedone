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
    CPPUNIT_TEST( test_not_equals );
    CPPUNIT_TEST( test_uri_match );
    CPPUNIT_TEST( test_bad_uri_schema );
    CPPUNIT_TEST( test_good_uri_schema );
    CPPUNIT_TEST_SUITE_END();

    done::Config *cfg1, *cfg2, *cfg3, *bad_config_uri_schema;
    std::string cfg2_file_path = "/tmp/config.";

  public:
    void setUp();
    void tearDown();
    void test_equality();
    void test_not_equals();

    // test correct uri loading
    void test_uri_match();
    void test_bad_uri_schema();
    void test_good_uri_schema();

};

void generate_tmp_config_file(std::string* filename, std::string line);
void delete_tmp_config_file(std::string *filename);
void add_alphanum_string(const int size, std::string* to_append);
