@echo off
setlocal

set BUILD=debug
if /i "%1"=="release" set BUILD=release

set BUILD_DIR=%~dp0Build\Debug
if /i "%BUILD%"=="release" set BUILD_DIR=%~dp0Build\Release

if exist "%BUILD_DIR%" (
    pushd "%BUILD_DIR%"

    if not exist "SSTL.exe" (
        echo [SSTL] SSTL.exe not found. Run Build.bat %BUILD% first.
        popd
        exit /b 1
    )

    start "" "SSTL.exe"
    popd
) else (
    echo [SSTL] SSTL.exe not found. Run Build.bat %BUILD% first.
)

endlocal
