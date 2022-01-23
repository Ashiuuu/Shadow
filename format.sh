#!/bin/sh

clang-format -i src/*.c;
clang-format -i src/exec/*.c;
clang-format -i src/exec/*.h;
clang-format -i src/io/*.c;
clang-format -i src/io/*.h;
clang-format -i src/lexer/*.c;
clang-format -i src/lexer/*.h;
clang-format -i src/parser/*.c;
clang-format -i src/parser/*.h;
clang-format -i src/printer/*.c;
clang-format -i src/printer/*.h;
clang-format -i src/utils/*.c;
clang-format -i src/utils/*.h;
clang-format -i src/interactive/*.c;
clang-format -i src/interactive/*.h;
clang-format -i src/script/*.c;
clang-format -i src/script/*.h;
clang-format -i src/variables/*.c;
clang-format -i src/variables/*.h;


clang-format -i test/*.c;
clang-format -i test/io_test/*.c;
clang-format -i test/lexer_test/*.c;
