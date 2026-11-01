# CMake generated Testfile for 
# Source directory: /home/simonevaligi/c++/programmazione/Lotka-Volterra
# Build directory: /home/simonevaligi/c++/programmazione/Lotka-Volterra/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[lotka_volterra.t]=] "/home/simonevaligi/c++/programmazione/Lotka-Volterra/build/Debug/lotka_volterra.t")
  set_tests_properties([=[lotka_volterra.t]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/simonevaligi/c++/programmazione/Lotka-Volterra/CMakeLists.txt;42;add_test;/home/simonevaligi/c++/programmazione/Lotka-Volterra/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[lotka_volterra.t]=] "/home/simonevaligi/c++/programmazione/Lotka-Volterra/build/Release/lotka_volterra.t")
  set_tests_properties([=[lotka_volterra.t]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/simonevaligi/c++/programmazione/Lotka-Volterra/CMakeLists.txt;42;add_test;/home/simonevaligi/c++/programmazione/Lotka-Volterra/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[lotka_volterra.t]=] "/home/simonevaligi/c++/programmazione/Lotka-Volterra/build/RelWithDebInfo/lotka_volterra.t")
  set_tests_properties([=[lotka_volterra.t]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/simonevaligi/c++/programmazione/Lotka-Volterra/CMakeLists.txt;42;add_test;/home/simonevaligi/c++/programmazione/Lotka-Volterra/CMakeLists.txt;0;")
else()
  add_test([=[lotka_volterra.t]=] NOT_AVAILABLE)
endif()
