#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

for header in ./kactl/content/**/*.h; do
  # in order to expand the kactl macros, you need to copy-paste the macros into
  # the beginning of each .h file
  cat kactl_macros.h "$header" > chicken
  shortened_path="${header/\/kactl\/content/}"
  # need to create directory: below `cpp` command expects directory to exist
  mkdir -p $(dirname "$shortened_path")
  cpp -std=c17 -nostdinc -C -P chicken "$shortened_path"
done

rm chicken

# the cpp preprocessor sometimes leaves blank empty lines
sed --in-place '/^[[:space:]]*$/d' ./**/*.h
# cpp command messes up formatting
clang-format -i --style=file:.clang-format ./**/*.h ./**/*.cpp
