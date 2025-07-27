@echo off

echo ----------Compling----------
g++ -finput-charset=utf-8 -fexec-charset=gbk "../utils/dll_main.cpp"^
    -o "utils.dll" -shared -DUTILS_INCLUDE_STB_IMPL

echo ----------End----------
pause
