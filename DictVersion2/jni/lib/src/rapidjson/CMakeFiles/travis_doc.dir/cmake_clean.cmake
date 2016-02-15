FILE(REMOVE_RECURSE
  "CMakeFiles/travis_doc"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/travis_doc.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
