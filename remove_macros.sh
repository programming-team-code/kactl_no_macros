#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update --remote --merge

for header in ./kactl/content/**/*.h; do
  shortened_path=${header/\/kactl\/content/}
  mkdir -p "$(dirname "$shortened_path")"
  # explanation: something like
  #
  # cpp -std=c17 -nostdinc -C -P <(cat kactl_macros.h "$header")
  #
  # won't work when $header file includes some other file, because the cpp
  # command can't find that included file (since cpp command reads output of
  # cat from sub-shell, and doesn't know path of $header)
  #
  # So solution is to call cpp command twice: first with just $header as
  # argument, so cpp command knows the path; now included files are copy-pasted
  # into file.
  #
  # Then concatenate in kactl_macros.h and run cpp command again to expand
  # macros.
  cpp -std=c17 -nostdinc -C -P "$header" | cat kactl_macros.h - | cpp -std=c17 -nostdinc -C -P - -o "$shortened_path"
done

# the cpp preprocessor sometimes leaves blank empty lines
sed --in-place '/^[[:space:]]*$/d' $(find . -path ./kactl -prune -o -name '*.h')
# cpp command messes up formatting
clang-format -i --style=file:.clang-format $(find . -path ./kactl -prune -o -name '*.h')
