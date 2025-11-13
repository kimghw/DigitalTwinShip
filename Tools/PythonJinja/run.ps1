# PythonJinja 코드 생성 스크립트 (PowerShell)

Write-Host "======================================" -ForegroundColor Cyan
Write-Host "PythonJinja Code Generator" -ForegroundColor Cyan
Write-Host "======================================" -ForegroundColor Cyan
Write-Host ""

# Python 실행
Write-Host "[1/2] Running PythonJinja.py..." -ForegroundColor Yellow
python PythonJinja.py

# 실행 결과 확인
if ($LASTEXITCODE -ne 0) {
    Write-Host ""
    Write-Host "[ERROR] Code generation failed!" -ForegroundColor Red
    Write-Host "Please check the error messages above." -ForegroundColor Red
    Read-Host "Press Enter to exit"
    exit $LASTEXITCODE
}

Write-Host ""
Write-Host "[2/2] Code generation completed successfully!" -ForegroundColor Green
Write-Host ""
Write-Host "Generated files:" -ForegroundColor White
Write-Host "  - GameServer/EDT0001_PacketHandler.cpp" -ForegroundColor Gray
Write-Host "  - GameServer/EDT0001_PacketHandler.h" -ForegroundColor Gray
Write-Host "  - GameServer/ClientPacketHandler.h" -ForegroundColor Gray
Write-Host "  - Protobuf/EDT0001.proto" -ForegroundColor Gray
Write-Host "  - Protobuf/MRSchema.proto" -ForegroundColor Gray
Write-Host "  - Protobuf/enum.proto" -ForegroundColor Gray
Write-Host "  - DummyClient/ServerPacketHandler.h" -ForegroundColor Gray
Write-Host ""
Write-Host "======================================" -ForegroundColor Cyan
Write-Host "Done!" -ForegroundColor Green
Write-Host "======================================" -ForegroundColor Cyan

Read-Host "Press Enter to exit"
