## Сборка из исходников | logMat
---
### Windows
1. Установите [Инструменты сборки для Visual Studio 2022](https://visualstudio.microsoft.com/ru/downloads/)
2. Установите [CMake](https://cmake.org/download/)
3. Установите [git](https://git-scm.com/downloads/win)
4. Установите [vcpkg](https://vcpkg.io/en/) через [git](https://git-scm.com)
	```
	C:\> cd \
	C:\> mkdir dev
	C:\> cd dev
	C:\> git clone https://github.com/microsoft/vcpkg
	С:\> cd vcpkg
	C:\> .\bootstrap-vcpkg.bat
	```
	Настройте переменную среды VCPKG_ROOT.
	```
	$env:VCPKG_ROOT = "C:\dev\vcpkg"
	$env:PATH = "$env:VCPKG_ROOT;$env:PATH"
	```
5. Установите [Boost](https://www.boost.org/) через [vcpkg](https://vcpkg.io/en/)
	```
	C:\> vcpkg install boost:x64-windows
	```
6. Добавьте директори в переменную среды PATH
	```
	C:\dev\vcpkg\installed\x64-windows\bin
	C:\dev\vcpkg\installed\x64-windows\lib
	C:\dev\vcpkg\installed\x64-windows\include
	C:\dev\vcpkg\installed\x64-windows\share
	C:\dev\vcpkg\installed\x64-windows\debug\bin
	C:\dev\vcpkg\installed\x64-windows\debug\lib
	```
7. Произведите сборку
	```
	C:\> cmake -B build .
	C:\> cd build
	C:\> cmake --build . -j %NUMBER_OF_PROCESSORS%
	```