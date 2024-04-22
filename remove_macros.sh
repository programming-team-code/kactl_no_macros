#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

# to create all directories (cpp command below fails if destination path isn't created)
cp -r ./kactl/content/. .

for header in ./kactl/content/**/*.h; do
  # in order to expand the kactl macros, you need to copy-paste the macros into
  # the beginning of each .h file
  cat kactl_macros.h "$header" > chicken
  cpp -std=c17 -nostdinc -C -P chicken "${header/\/content/}"
done

rm chicken

# the cpp preprocessor sometimes leaves blank empty lines
sed --in-place '/^[[:space:]]*$/d' ./**/*.h
# cpp command messes up formatting
clang-format -i --style=file:.clang-format ./**/*.h ./**/*.cpp
