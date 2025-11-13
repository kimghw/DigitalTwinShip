@echo off
REM PythonJinja 코드 생성 스크립트
echo ======================================
echo PythonJinja Code Generator
echo ======================================
echo.

REM Python 실행
echo [1/2] Running PythonJinja.py...
python PythonJinja.py

REM 실행 결과 확인
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Code generation failed!
    echo Please check the error messages above.
    pause
    exit /b %errorlevel%
)

echo.
echo [2/2] Code generation completed successfully!
echo.
echo Generated files:
echo   - GameServer/EDT0001_PacketHandler.cpp
echo   - GameServer/EDT0001_PacketHandler.h
echo   - GameServer/ClientPacketHandler.h
echo   - Protobuf/EDT0001.proto
echo   - Protobuf/MRSchema.proto
echo   - Protobuf/enum.proto
echo   - DummyClient/ServerPacketHandler.h
echo.
echo ======================================
echo Done!
echo ======================================
pause
