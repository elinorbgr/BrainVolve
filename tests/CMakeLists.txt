project("alife_tests")

add_subdirectory(neural)

file(GLOB ${PROJECT_NAME}_SOURCE "../src/*.cpp")
file(GLOB ${PROJECT_NAME}_MAIN "../src/main.cpp")
list(REMOVE_ITEM ${PROJECT_NAME}_SOURCE ${${PROJECT_NAME}_MAIN})
file(GLOB ${PROJECT_NAME}_TEST_SOURCE "./*.cpp")

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCE} ${${PROJECT_NAME}_TEST_SOURCE})
target_link_libraries(${PROJECT_NAME} UnitTest++ neural)

add_test(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME})
