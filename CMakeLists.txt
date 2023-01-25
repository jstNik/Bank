cmake_minimum_required(VERSION 3.16.3)
project(LabProg)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(Test)

set(SOURCE_FILES BankAccount.cpp BankAccount.h Subject.h Observer.h Register.cpp Register.h AddressBook.cpp AddressBook.h MoreExceptions.h Transaction.cpp Transaction.h)
add_executable(LabProg main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(LabProg core)