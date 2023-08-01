protoc.exe -I=./ --cpp_out=./ ./Protobuf.proto

if errorlevel 1 pause
