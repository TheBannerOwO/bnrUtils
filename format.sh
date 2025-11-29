#! /usr/bin/bash
find -regextype egrep -regex ".*\.[ch]" | xargs clang-format -i