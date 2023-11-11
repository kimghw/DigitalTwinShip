pushd %~dp0
REM protoc.exe -I=./ --cpp_out=./ ./Enum.proto
REM protoc.exe -I=./ --cpp_out=./ ./Struct.proto
protoc.exe -I=./ --cpp_out=./ ./Protocol.proto
protoc.exe -I=./ --cpp_out=./ ./EDT0001.proto


REM GenPackets.exe --path=./Protocol.proto --output=ClientPacketHandler --recv=C_ --send=S_
REM GenPackets.exe --path=./Protocol.proto --output=ServerPacketHandler --recv=S_ --send=C_


IF ERRORLEVEL 1 PAUSE

REM XCOPY /Y Enum.pb.h "../../../GameServer"
REM XCOPY /Y Enum.pb.cc "../../../GameServer"
REM XCOPY /Y Struct.pb.h "../../../GameServer"
REM XCOPY /Y Struct.pb.cc "../../../GameServer"
XCOPY /Y Protocol.pb.h "../../GameServer"
XCOPY /Y Protocol.pb.cc "../../GameServer"
XCOPY /Y EDT0001.pb.h "../../GameServer"
XCOPY /Y EDT0001.pb.cc "../../GameServer"
REM XCOPY /Y ClientPacketHandler.h "../GameServer"

REM XCOPY /Y Protocol.pb.h "./test"
REM XCOPY /Y Protocol.pb.cc "./test"
REM XCOPY /Y ClientPacketHandler.h "./test"


REM XCOPY /Y Enum.pb.h "../../../DummyClient"
REM XCOPY /Y Enum.pb.cc "../../../DummyClient"
REM XCOPY /Y Struct.pb.h "../../../DummyClient"
REM XCOPY /Y Struct.pb.cc "../../../DummyClient"
XCOPY /Y Protocol.pb.h "../../DummyClient"
XCOPY /Y Protocol.pb.cc "../../DummyClient"
XCOPY /Y EDT0001.pb.h "../../DummyClient"
XCOPY /Y EDT0001.pb.cc "../../DummyClient"
REM XCOPY /Y ServerPacketHandler.h "../DummyClient"

REM XCOPY /Y Enum.pb.h "../../../Streamsocket"
REM XCOPY /Y Enum.pb.cc "../../../Streamsocket"
REM XCOPY /Y Struct.pb.h "../../../Streamsocket"
REM XCOPY /Y Struct.pb.cc "../../../Streamsocket"
REM XCOPY /Y Protocol.pb.h "../Streamsocket"
REM XCOPY /Y Protocol.pb.cc "../Streamsocket"
REM XCOPY /Y ServerPacketHandler.h "../Streamsocket"


DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc
DEL /Q /F *.h

