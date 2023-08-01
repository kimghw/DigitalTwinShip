pushd %~dp0
REM protoc.exe -I=./ --cpp_out=./ ./Enum.proto
REM protoc.exe -I=./ --cpp_out=./ ./Struct.proto
protoc.exe -I=./ --cpp_out=./ ./Protocol.proto

REM GenPackets.exe --path=./Protocol.proto --output=ClientPacketHandler --recv=C_ --send=S_
REM GenPackets.exe --path=./Protocol.proto --output=ServerPacketHandler --recv=S_ --send=C_

IF ERRORLEVEL 1 PAUSE

REM XCOPY /Y Enum.pb.h "../../../GameServer"
REM XCOPY /Y Enum.pb.cc "../../../GameServer"
REM XCOPY /Y Struct.pb.h "../../../GameServer"
REM XCOPY /Y Struct.pb.cc "../../../GameServer"
XCOPY /Y Protocol.pb.h "../GameServer"
PAUSE
XCOPY /Y Protocol.pb.cc "../GameServer"
REM XCOPY /Y ClientPacketHandler.h "../../../GameServer"

REM XCOPY /Y Enum.pb.h "../../../DummyClient"
REM XCOPY /Y Enum.pb.cc "../../../DummyClient"
REM XCOPY /Y Struct.pb.h "../../../DummyClient"
REM XCOPY /Y Struct.pb.cc "../../../DummyClient"
XCOPY /Y Protocol.pb.h "../DummyClient"
XCOPY /Y Protocol.pb.cc "../DummyClient"
REM XCOPY /Y ServerPacketHandler.h "../../../DummyClient"

DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc
DEL /Q /F *.h

PAUSE