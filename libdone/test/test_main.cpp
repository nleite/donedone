#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <iostream>
#include "test_configuration.h"
#include "test_backend.h"

int main( int argc, char **argv){
  CppUnit::TextUi::TestRunner runner;
  CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
  //runner.addTest( registry.makeTest() );
  runner.addTest( TestConfig::suite() );
  runner.addTest(TestBackend::suite());
  bool wasSucessful = runner.run( "", false );
  return wasSucessful;
}
