@echo # Premake for MinGW
@echo # (C) 2016, Ricyn Lee

:: MinGW\bin路径设置,结尾不写'\'
@set MingwBinPath=C:\ProgramFiles\MinGW\bin

:: 设置PATH
@echo [%Time:~0,8%] Adding MinGW toolchains to temporary PATH
@set PATH=%MingwBinPath%;%PATH%
@if exist %MingwBinPath%\make.exe goto wait

:linkmake
@echo [%Time:~0,8%] 'make' not found
@pushd %cd%
@cd /d %MingwBinPath%
@echo [%Time:~0,8%] Linking 'make' to 'mingw32-make'
@mklink /h make.exe mingw32-make.exe > nul
@popd

:wait
@echo [%Time:~0,8%] 'make' found
@cmd /k echo [%Time:~0,8%] Premake done; 'gcc', 'make', etc. is available
