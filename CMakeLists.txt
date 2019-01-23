cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(tiny2-object VERSION 0.3.3 LANGUAGES C)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX /usr/ CACHE PATH "Default install prefix" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
endif()

set(CMAKE_C_STANDARD 11)

if (MSVC)
  add_library(tiny2-object ${CMAKE_CURRENT_LIST_DIR}/tiny2-object.c ${CMAKE_CURRENT_LIST_DIR}/tiny2-object.h)
else()
  add_library(tiny2-object SHARED ${CMAKE_CURRENT_LIST_DIR}/tiny2-object.c)
endif()

add_executable(
  to-test
  ${CMAKE_CURRENT_LIST_DIR}/test.c
  ${CMAKE_CURRENT_LIST_DIR}/test-greeter.c
  ${CMAKE_CURRENT_LIST_DIR}/test-greeter.h
  ${CMAKE_CURRENT_LIST_DIR}/test-titlegreeter.c
  ${CMAKE_CURRENT_LIST_DIR}/test-titlegreeter.h
)
target_link_libraries(to-test tiny2-object)

configure_file(${CMAKE_CURRENT_LIST_DIR}/tiny2-object.pc.in ${CMAKE_CURRENT_BINARY_DIR}/tiny2-object.pc)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/tiny2-object.pc DESTINATION lib/pkgconfig)

if(MSVC)
  install(
    TARGETS tiny2-object
    ARCHIVE DESTINATION lib
  )
  install(FILES ${CMAKE_CURRENT_LIST_DIR}/tiny2-object.h DESTINATION include)
else()
  install(
    TARGETS tiny2-object
    LIBRARY DESTINATION lib
  )
  install(FILES ${CMAKE_CURRENT_LIST_DIR}/tiny2-object.h DESTINATION include)
endif()
