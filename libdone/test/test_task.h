#ifndef TEST_TASK_H_
#define TEST_TASK_H_
#pragma once

#include "task.h"
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <vector>

using namespace CppUnit;
using namespace std;

class TestTask : public CppUnit::TestFixture {
private:
  Task *t1, *t2;
  Json::Value *valid, *noId, *noTitle;

  CPPUNIT_TEST_SUITE(TestTask);
  CPPUNIT_TEST(test_valid_json);
  CPPUNIT_TEST(test_noId_json_task);
  CPPUNIT_TEST(test_noTitle_json_task);
  CPPUNIT_TEST(test_get_title);
  CPPUNIT_TEST(test_get_id);
  CPPUNIT_TEST(test_to_string);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();
  // constructor tests
  void test_valid_json();
  void test_noId_json_task();
  void test_noTitle_json_task();
  // get methods test
  void test_get_title();
  void test_get_id();
  void test_to_string();
  void test_is_done_true();
  // ...
};

class TestTaskFilter : public CppUnit::TestFixture {
private:
  vector<Task> tasks;

  CPPUNIT_TEST_SUITE(TestTaskFilter);
  CPPUNIT_TEST(test_filter_done);
  // CPPUNIT_TEST(test_filter_due);
  CPPUNIT_TEST(test_filter_all);
  CPPUNIT_TEST(test_filter_open);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();
  // filter methods
  void test_filter_done();
  // void test_filter_due();
  void test_filter_all();
  void test_filter_open();
};

#endif // TEST_TASK_H_
