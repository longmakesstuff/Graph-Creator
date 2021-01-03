cmake_minimum_required(VERSION 3.0)

project(bugs)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 REQUIRED network audio graphics window system)
find_package(Eigen3 3.3 REQUIRED)
find_package(OpenMP)
find_library(LIB_CPPUNIT cppunit)
find_package(TGUI 0.9.0 REQUIRED)

INCLUDE_DIRECTORIES ( "${EIGEN3_INCLUDE_DIR}" )

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
else ()
    message(ERROR_FATAL "Can not find SFML")
endif ()


set(PACKAGES "${PROJECT_NAME}")

# Adding source files in "src"
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})


# Adding executable files in "bin"
file(GLOB bin_files "${CMAKE_CURRENT_SOURCE_DIR}/bin/*.cpp")
foreach (file ${bin_files})
    get_filename_component(file_name ${file} NAME_WLE)

    add_executable(${file_name} ${file})

    target_link_libraries(${file_name} ${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${PROJECT_NAME} ${TGUI_LIBRARY} tgui sfml-graphics sfml-window sfml-system Eigen3::Eigen m OpenMP::OpenMP_CXX)
endforeach ()

# Adding header files in "include"
target_include_directories(${PROJECT_NAME} PUBLIC include)

# Adding unit tests in "test"
file(GLOB test_files "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
if (NOT LIB_CPPUNIT)
    message(FATAL_ERROR "cppunit not found")
endif ()
foreach (file ${test_files})
    get_filename_component(file_name ${file} NAME_WLE)

    add_executable(${file_name} ${file})

    target_link_libraries(${file_name} ${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${PROJECT_NAME} ${TGUI_LIBRARY} sfml-graphics sfml-window sfml-system Eigen3::Eigen m OpenMP::OpenMP_CXX cppunit)
endforeach ()

# Copy resource files from from data to build directory
file(GLOB resource_files "${CMAKE_CURRENT_SOURCE_DIR}/data/*")
foreach (item ${resource_files})
    FILE(COPY ${item} DESTINATION "${CMAKE_BINARY_DIR}")
endforeach ()