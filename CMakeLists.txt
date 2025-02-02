cmake_minimum_required(VERSION 3.30)
project(coursework1)

set(CMAKE_CXX_STANDARD 20)

# Опция для покрытия кода
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
if(ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(STATUS "Coverage enabled")
        add_compile_options(-fprofile-arcs -ftest-coverage)
        add_link_options(-fprofile-arcs -ftest-coverage)
    endif()
endif()

# Основная цель приложения
add_executable(coursework1
    main.cpp
    List.cpp
    List.h
    BigNumber.cpp
    BigNumber.h
    BigRacNumber.cpp
    BigRacNumber.h
)

# Цель для unit тестов
add_executable(unit_tests
    tests/test.cpp
    List.cpp
    List.h
    BigNumber.cpp
    BigNumber.h
    BigRacNumber.cpp
    BigRacNumber.h
)

# Добавляем тесты в CTest (если требуется запуск через ctest)
enable_testing()
add_test(NAME UnitTests COMMAND unit_tests)

# Цель для генерации отчёта покрытия (gcov)
if(ENABLE_COVERAGE)
    add_custom_target(coverage
        COMMAND unit_tests
        COMMAND lcov --capture --directory . --output-file coverage.info
        COMMAND genhtml coverage.info --output-directory coverage_report
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running tests and generating coverage report..."
    )
endif()
