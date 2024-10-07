# Add subdirectories

add_subdirectory(slang_parser)

# Add the binary and sources
add_executable(
  slicc
  main.cc
)

target_link_libraries(slicc slang_parser)
set_target_properties(slicc PROPERTIES RUNTIME_OUTPUT_DIRECTORY "..")
