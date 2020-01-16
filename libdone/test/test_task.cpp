#include "test_task.h"
#include "task.h"
#include <json/reader.h>
#include <json/value.h>

CPPUNIT_TEST_SUITE_REGISTRATION(TestTask);
CPPUNIT_TEST_SUITE_REGISTRATION(TestTaskFilter);

void TestTask::setUp() {
  Json::CharReaderBuilder builder;
  builder.settings_["allowSingleQuotes"] = true;
  Json::CharReader *reader = builder.newCharReader();
  // init json::value objects
  std::string valid_task_json =
      "{'id': 1, 'title': 'first title', 'description': 'some description', "
      "'done': true}";
  valid = new Json::Value();
  std::string errors;
  reader->parse(valid_task_json.c_str(),
                valid_task_json.c_str() + valid_task_json.size(), valid,
                &errors);
  // create Task objects
  t1 = new Task(valid);

  // no id json
  noId = new Json::Value();
  std::string no_id_json_string = "{'title': 'no id task'}";
  reader->parse(no_id_json_string.c_str(),
                no_id_json_string.c_str() + no_id_json_string.size(), noId,
                &errors);

  // no title json
  noTitle = new Json::Value();
  std::string no_title_json = "{'id': 10}";
  reader->parse(no_title_json.c_str(),
                no_title_json.c_str() + no_title_json.size(), noTitle, &errors);
}

void TestTask::tearDown() {
  delete valid;
  delete t1;
  delete noId;
  delete noTitle;
}

void TestTask::test_valid_json() {
  t2 = new Task(valid);
  CPPUNIT_ASSERT_MESSAGE("could not correctly build Task", t2 != NULL);
  delete t2;
}

void TestTask::test_noId_json_task() {
  CPPUNIT_ASSERT_THROW(new Task(noId), InvalidTask);
}

void TestTask::test_noTitle_json_task() {
  CPPUNIT_ASSERT_THROW(new Task(noTitle), InvalidTask);
}

void TestTask::test_get_title() {
  std::string expected = "first title";
  CPPUNIT_ASSERT_EQUAL(expected, t1->get_title());
}

void TestTask::test_get_id() {
  int expected = 1;
  CPPUNIT_ASSERT_EQUAL(expected, t1->get_id());
}

void TestTask::test_to_string() {
  const std::string expected = "title: first title";
  CPPUNIT_ASSERT_EQUAL(expected, t1->toString());
}

void TestTask::test_is_done_true() { CPPUNIT_ASSERT(t1->is_done()); }

// TestTaskFilter methods

void TestTaskFilter::setUp() {
  Task t1("some id");
  Json::CharReaderBuilder builder;
  builder.settings_["allowSingleQuotes"] = true;
  Json::CharReader *reader = builder.newCharReader();
  std::string valid_task_json =
      "{'id': 1, 'title': 'done task', 'description': 'some description', "
      "'done': true}";
  Json::Value *valid = new Json::Value();
  std::string errors;
  reader->parse(valid_task_json.c_str(),
                valid_task_json.c_str() + valid_task_json.size(), valid,
                &errors);
  Task t2(valid);
  Task t3("not done");

  tasks.push_back(t1);
  tasks.push_back(t2);
  tasks.push_back(t3);
}

void TestTaskFilter::tearDown() {}

void TestTaskFilter::test_filter_all() {
  vector<Task> actual = filter(tasks, filter_all);
  size_t expected = 3;
  CPPUNIT_ASSERT_EQUAL(expected, actual.size());
}

void TestTaskFilter::test_filter_done() {
  vector<Task> actual = filter(tasks, filter_done);
  size_t expected = 1;
  CPPUNIT_ASSERT_EQUAL(expected, actual.size());
  for (auto &t : actual) {
    CPPUNIT_ASSERT(t.is_done());
  }
}

void TestTaskFilter::test_filter_open() {
  vector<Task> actual = filter(tasks, filter_open);
  size_t expected = 2;
  CPPUNIT_ASSERT_EQUAL(expected, actual.size());
  for (auto &t : actual) {
    CPPUNIT_ASSERT(!t.is_done());
  }
}
