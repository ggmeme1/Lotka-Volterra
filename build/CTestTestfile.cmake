# CMake generated Testfile for 
# Source directory: /home/gg/Downloads/progetto
# Build directory: /home/gg/Downloads/progetto/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[simulation.t]=] "/home/gg/Downloads/progetto/build/Debug/simulation.t")
  set_tests_properties([=[simulation.t]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/gg/Downloads/progetto/CMakeLists.txt;36;add_test;/home/gg/Downloads/progetto/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[simulation.t]=] "/home/gg/Downloads/progetto/build/Release/simulation.t")
  set_tests_properties([=[simulation.t]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/gg/Downloads/progetto/CMakeLists.txt;36;add_test;/home/gg/Downloads/progetto/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[simulation.t]=] "/home/gg/Downloads/progetto/build/RelWithDebInfo/simulation.t")
  set_tests_properties([=[simulation.t]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/gg/Downloads/progetto/CMakeLists.txt;36;add_test;/home/gg/Downloads/progetto/CMakeLists.txt;0;")
else()
  add_test([=[simulation.t]=] NOT_AVAILABLE)
endif()
