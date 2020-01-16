#include "test_backend.h"
#include "test_configuration.h"
#include "test_task.h"
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <iostream>

int main(int argc, char **argv) {
  CppUnit::TextUi::TestRunner runner;
  CppUnit::TestFactoryRegistry &registry =
      CppUnit::TestFactoryRegistry::getRegistry();
  // runner.addTest( registry.makeTest() );
  runner.addTest(TestConfig::suite());
  runner.addTest(TestBackend::suite());
  runner.addTest(TestTask::suite());
  runner.addTest(TestTaskFilter::suite());
  bool wasSucessful = runner.run("", false);
  return wasSucessful;
}
