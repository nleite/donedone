#include <cppunit/extensions/HelperMacros.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include "test_configuration.h"
#include "configuration.h"

using namespace CppUnit;
using namespace std;
using namespace done;

CPPUNIT_TEST_SUITE_REGISTRATION( TestConfig );

// util method to overcome the limitation that MACOS deprecates tmpnam and
// filesystem lib is not included in my development box. 
void add_alphanum_string(const int size, std::string* to_append){
  srand(time(NULL));
  for(int i = 0; i < size; i++){
      char v = char((rand() % 26) + 97);
      to_append->append(1, v);
  }
}

void TestConfig::generate_tmp_config_file(){
  add_alphanum_string(6, &cfg2_file_path);
  FILE * fp = fopen(cfg2_file_path.c_str(), "wb");
  char line[] = "uri=file://some_file\n";
  fwrite( line, sizeof(char), sizeof(line), fp);
  fclose(fp);
}

void TestConfig::delete_tmp_config_file(){
  std::remove(cfg2_file_path.c_str());
}

void TestConfig::setUp(){
  generate_tmp_config_file();
  cfg1 = new done::Config();
  cfg2 = new done::Config(cfg2_file_path);
  cfg3 = new done::Config();
}

void TestConfig::tearDown(){
  delete_tmp_config_file();
  delete cfg1;
  delete cfg2;
  delete cfg3;
}

void TestConfig::test_equality(){
  CPPUNIT_ASSERT( *cfg1 == *cfg3);
}

void TestConfig::test_not_equals(){
  CPPUNIT_ASSERT( *cfg1 != *cfg2 );
}

void TestConfig::test_uri_match(){
  std::string expected_uri = "file://some_file";
  CPPUNIT_ASSERT_EQUAL_MESSAGE( " not matching expected",
  expected_uri, cfg2->get_uri());
}
