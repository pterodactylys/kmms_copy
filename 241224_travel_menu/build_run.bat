@echo off
chcp 1251 > log
del log

set CPP_FILES="menu_functions.cpp menu_functions.hpp menu.hpp menu_item.cpp menu_item.hpp main.cpp"
set EXE=travel_menu.exe
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

if exist %EXE% del %EXE%

g++ "%CHARSET%" "%CPP_FILES%" -o %EXE%

%EXE%
