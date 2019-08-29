#include "test_configuration.h"
#include "configuration.h"
#include <cppunit/extensions/HelperMacros.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

using namespace CppUnit;
using namespace std;
using namespace done;

CPPUNIT_TEST_SUITE_REGISTRATION(TestConfig);

// util method to overcome the limitation that MACOS deprecates tmpnam and
// filesystem lib is not included in my development box.
void add_alphanum_string(const int size, std::string *to_append) {
  srand(time(NULL));
  for (int i = 0; i < size; i++) {
    char v = char((rand() % 26) + 97);
    to_append->append(1, v);
  }
}

void generate_tmp_config_file(std::string *filename, std::string line) {
  add_alphanum_string(6, filename);
  std::ofstream fp;
  fp.open(filename->c_str());
  fp << line;
  fp.close();
}

void delete_tmp_config_file(std::string *filename) {
  std::remove(filename->c_str());
}

void TestConfig::setUp() {
  cfg1 = new done::Config();
  generate_tmp_config_file(&cfg2_file_path, "uri=file://some_file\n");
  cfg2 = new done::Config(cfg2_file_path);
  cfg3 = new done::Config();
  std::string bad_config_uri_schema_filename("/tmp/bad_uri.");
  generate_tmp_config_file(&bad_config_uri_schema_filename,
                           "uri=bad_schema/a\n");
  bad_config_uri_schema = new done::Config(bad_config_uri_schema_filename);
}

void TestConfig::tearDown() {
  delete cfg1;
  delete cfg2;
  delete_tmp_config_file(&cfg2_file_path);
  delete cfg3;
  std::string bad_file = bad_config_uri_schema->get_config_file_path();
  delete_tmp_config_file(&bad_file);
  delete bad_config_uri_schema;
}

void TestConfig::test_equality() { CPPUNIT_ASSERT(*cfg1 == *cfg3); }

void TestConfig::test_not_equals() { CPPUNIT_ASSERT(*cfg1 != *cfg2); }

void TestConfig::test_uri_match() {
  std::string expected_uri = "file://some_file";
  CPPUNIT_ASSERT_EQUAL_MESSAGE("not matching expected", expected_uri,
                               cfg2->get_uri());
}

void TestConfig::test_bad_uri_schema() {
  CPPUNIT_ASSERT_THROW(bad_config_uri_schema->get_uri_schema(),
                       done::BadUriSchema);
}

void TestConfig::test_good_uri_schema() {
  CPPUNIT_ASSERT_NO_THROW(cfg2->get_uri_schema());
  std::string expected = "file";
  CPPUNIT_ASSERT_EQUAL(expected, cfg2->get_uri_schema());
}

void TestConfig::test_default_constructor() {
  std::string expected = done::default_config_path();
  CPPUNIT_ASSERT_EQUAL(expected, cfg3->get_config_file_path());
  // coment this please - this is only valid on my personal macosx
  // std::string expected_2 = "/Users/norberto/.done/config";
  // CPPUNIT_ASSERT_EQUAL(expected_2, cfg3->get_config_file_path());
}
