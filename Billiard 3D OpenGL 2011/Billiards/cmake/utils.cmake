
function(get_target_compiler_flags ARG_TARGET ARG_COMPILER_FLAGS)

  get_target_property(VALUE ${ARG_TARGET} COMPILE_OPTIONS)
  if(VALUE)
    list(APPEND ARG_COMPILER_FLAGS ${VALUE})
  endif()

  string(TOUPPER "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" VALUE)
  set(VALUE "${${VALUE}}")
  if(VALUE)
    list(APPEND ARG_COMPILER_FLAGS ${VALUE})
  endif()

  list(APPEND ARG_COMPILER_FLAGS ${CMAKE_CXX_FLAGS})

  separate_arguments(ARG_COMPILER_FLAGS)

  set(${ARG_COMPILER_FLAGS} PARENT_SCOPE)

endfunction()