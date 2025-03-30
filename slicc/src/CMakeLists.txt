# Add subdirectories

add_subdirectory(slang_parser)
add_subdirectory(risc_gen)

# Add the binary and sources
add_executable(
  slicc
  main.cc
)

target_link_libraries(slicc slang_parser)
target_link_libraries(slicc risc_gen)
set_target_properties(slicc PROPERTIES RUNTIME_OUTPUT_DIRECTORY "..")
