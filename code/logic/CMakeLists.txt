# code/logic/CMakeLists.txt

# Define the include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Collect all header files in logic/fossil/*
file(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/fossil/*.h)

# List the source files
set(TEST_CODE
    tls.c
)

# Create the library target
add_library(fossil-tls STATIC ${TEST_CODE} ${HEADER_FILES})

# Link the math library
target_link_libraries(fossil-tls PUBLIC m)

# Link to Winsock library only on Windows
if(WIN32)
    target_link_libraries(fossil-tls PUBLIC ws2_32)
endif()

# Set the library to be installed
install(TARGETS fossil-tls
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install the header files
install(FILES ${HEADER_FILES} DESTINATION include/fossil)

# Declare the dependency
add_library(fossil_tls_dep INTERFACE)
target_link_libraries(fossil_tls_dep INTERFACE fossil-tls)
target_include_directories(fossil_tls_dep INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})