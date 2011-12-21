cmake_minimum_required (VERSION 2.6)
project (Procsi_emul)
find_package(Curses)
add_executable(ProcSI main.c parser.c function.c interface.c)
