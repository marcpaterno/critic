########################################################################
# art_dictionary
#
#   Wrapper around cetbuildtools' build_dictionary featuring the ### MIGRATE-ACTION-REQUIRED: remove
#   addition of commonly required libraries to the dictionary library
#   link list.
#
# USAGE
#
#   art_dictionary([NO_DEFAULT_LIBRARIES] ...)
#
# OPTIONS
#
#   NO_DEFAULT_LIBRARIES
#
#     Do not add the usual set of default libraries to the
#     DICTIONARY_LIBRARIES list: equivalent to calling build_dictionary
#     directly.
#
#########################################################################
include(BuildDictionary)

function(art_dictionary)
  if ("NO_DEFAULT_LIBRARIES" IN_LIST ARGV)
    string(REGEX REPLACE "(^|;)NO_DEFAULT_LIBRARIES(;|$)" "\\1NOP\\2"
      ARGV "${ARGV}")
  else()
    list(PREPEND ARGV DICTIONARY_LIBRARIES canvas cetlib cetlib_except NOP)
  endif()
  list(FIND ARGV "DICT_NAME_VAR" idx)
  if (idx GREATER -1)
    math(EXPR idx "${idx} + 1")
    list(GET ARGV ${idx} dict_name_var)
  endif()
  build_dictionary(${ARGV})
  if (dict_name_var)
    set(${dict_name_var} "${${dict_name_var}}" PARENT_SCOPE)
  endif()
endfunction()
