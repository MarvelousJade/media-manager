cmake_minimum_required(VERSION 3.12)
project(MultimediaManagementSystem VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(media_manager
    main.cpp
    book.cpp
    movie.cpp
    tvShow.cpp
    spellChecker.cpp
    collection.cpp
    settings.cpp
    ui.cpp
)

# Add include directories
target_include_directories(media_manager PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Copy data files to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)

# Install targets
install(TARGETS media_manager DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/
        DESTINATION share/media_manager/data)

# Enable testing
enable_testing()

# Add a simple test
add_test(NAME BasicTest COMMAND media_manager --test)

# Output configuration information
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
