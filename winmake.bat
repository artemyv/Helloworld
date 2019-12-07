setlocal

set platform=x64
rem set platform=Win32
set config=Release
rem set config=Debug
set out=win32/%config%.%platform%
cmake -S test1 -B %out% -A %platform% -DCMAKE_BUILD_TYPE=%config%
cmake --build %out% --config %config%
cd %out%
ctest -C %config%