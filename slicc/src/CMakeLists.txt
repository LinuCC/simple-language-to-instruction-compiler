# Add subdirectories

add_subdirectory(parser_gen)

# Add the binary and sources
add_executable(
  slicc
  main.cc
)

target_link_libraries(slicc parser_gen)
set_target_properties(slicc PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../..")
