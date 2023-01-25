add_subdirectory(./lib)
set(gtest_SOURCE_DIR, ./lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include)

set(TEST_SOURCE_FILES runAllTests.cpp runAllTests.cpp BankAccountFixture.cpp BankAccountTest.cpp AddressBookFixture.cpp)
add_executable(Test ${TEST_SOURCE_FILES} runAllTests.cpp)
target_link_libraries(Test gtest gtest_main core)