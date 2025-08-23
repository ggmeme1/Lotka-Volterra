cmake_minimum_required(VERSION 3.28)
project(lotka_volterra VERSION 0.1.0)

# Abilita il supporto per i test, tra cui l'opzione BUILD_TESTING usata sotto
include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Richiedi l'uso di C++20, senza estensioni non-standard offerte dal compilatore usato
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Abilita warning
string(APPEND CMAKE_CXX_FLAGS " -fno-omit-frame-pointer -Wall -Wextra")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  string(APPEND CMAKE_CXX_FLAGS " -D_GLIBCXX_ASSERTIONS")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  string(APPEND CMAKE_CXX_FLAGS " -D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE")
endif()

# Abilita l'address sanitizer e l'undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined ")

add_executable(lotka_volterra main.cpp simulation.cpp)

# Se il testing e' abilitato...
#   per disabilitare il testing, passare -DBUILD_TESTING=OFF a cmake durante la fase di configurazione
if (BUILD_TESTING)

  # Aggiungi l'eseguibile simulation.t
  add_executable(simulation.t simulation.test.cpp simulation.cpp)
  # Aggiungi l'eseguibile simulation.t alla lista dei test
  add_test(NAME simulation.t COMMAND simulation.t)

endif()