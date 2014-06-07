project("neural_tests")

file(GLOB ${PROJECT_NAME}_SOURCE "./*.cpp")

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE})
target_link_libraries(${PROJECT_NAME} UnitTest++ neural)

add_test(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME})
