include(GoogleTest)

# Helpful macro to add unittest
# Accepts src_file (with utest) as mandatory argument
# and list of linked libraries after it
macro(hsim_add_utest src_file)
  set(TEST_NAME "${src_file}_test")
  add_executable(${TEST_NAME} ${src_file})

  target_link_libraries(${TEST_NAME} PRIVATE GTest::gtest_main hSIM::defaults)
  foreach(arg IN LISTS ARGN)
    target_link_libraries(${TEST_NAME} PRIVATE ${arg})
  endforeach()
  gtest_discover_tests(
    ${TEST_NAME}
    EXTRA_ARGS --gtest_color=yes
    PROPERTIES LABELS unit)
endmacro()

add_subdirectory(hello)
