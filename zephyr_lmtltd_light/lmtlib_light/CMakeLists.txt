list(APPEND SYSCALL_INCLUDE_DIRS ${ZEPHYR_CURRENT_MODULE_DIR}/include)
list(APPEND SYSCALL_INCLUDE_DIRS ${ZEPHYR_CURRENT_MODULE_DIR}/drivers)

set(LMTLIB_BASE ${CMAKE_CURRENT_SOURCE_DIR})
set(SYSCALL_INCLUDE_DIRS ${SYSCALL_INCLUDE_DIRS} PARENT_SCOPE)

zephyr_include_directories(
  include
)

add_subdirectory(drivers)
add_subdirectory(subsys)