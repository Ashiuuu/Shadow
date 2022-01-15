#!/bin/sh

clang-format -i src/*.c;
clang-format -i src/exec/*.c;
clang-format -i src/io/*.c;
clang-format -i src/lexer/*.c;
clang-format -i src/parser/*.c;
clang-format -i src/printer/*.c;
clang-format -i src/utils/*.c;

clang-format -i test/*.c;
clang-format -i test/io_test/*.c;
clang-format -i test/lexer_test/*.c;
