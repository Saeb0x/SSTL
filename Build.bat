@echo off
setlocal enabledelayedexpansion

call vcvarsall.bat x64 >nul 2>&1
if %errorlevel% neq 0 (
    echo [SSTL] Failed to call vcvarsall.bat. Ensure Microsoft C/C++ build tools are installed and vcvarsall.bat is accessible from the current environment.
    exit /b 1
)

set BUILD=debug
if /i "%1"=="release" set BUILD=release

set BUILD_DIR=%~dp0Build\Debug
if /i "%BUILD%"=="release" set BUILD_DIR=%~dp0Build\Release

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
pushd "%BUILD_DIR%"

if /i "%BUILD%"=="debug" (
    echo [SSTL] Compiling and linking [debug]...
    cl /nologo /std:c++17 /MTd /W4 /WX /permissive- /Od /Zi /EHsc /I "%~dp0Include" "%~dp0Src\Main.cpp" /Fd:"SSTL.pdb" /Fe:"SSTL.exe" /link /nologo /debug Kernel32.lib
    if !errorlevel! neq 0 goto error
) else (
    echo [SSTL] Compiling and linking [release]...
    cl /nologo /std:c++17 /MT /W4 /WX /permissive- /O2 /EHsc /I "%~dp0Include" "%~dp0Src\Main.cpp" /Fe:"SSTL.exe" /link /nologo
    if !errorlevel! neq 0 goto error
)

echo.
echo [SSTL] Build succeeded.
popd
goto end

:error
echo.
echo [SSTL] Build failed.
popd
exit /b 1

:end
endlocal
