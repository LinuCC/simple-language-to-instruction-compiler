
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB HH_FILES *.hh)
file(GLOB SRC_FILES *.cc)
file(GLOB HXX_FILES *.hxx)

add_library(risc_gen
            STATIC
            ${HH_FILES}
            ${SRC_FILES}
            ${HXX_FILES}
)
