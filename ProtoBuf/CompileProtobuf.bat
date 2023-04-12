@echo off

@setlocal
pushd "%~dp0"

set path=%cd%
set output_protobuf_path=%path%
set output_grpc_path=%path%
if not exist %output_protobuf_path% mkdir %output_protobuf_path%
if not exist %output_grpc_path% mkdir %output_grpc_path%

set protoc_path=%zLib%\protobuf_v3.18.0\bin\x64\Release

REM %protoc_path%\protoc.exe *.proto --cpp_out=%output_protobuf_path% --csharp_out=%output_protobuf_path% --python_out=%output_protobuf_path% --proto_path=.\
%protoc_path%\protoc.exe *.proto --cpp_out=%output_protobuf_path% --python_out=%output_protobuf_path% --proto_path=.\


popd
@endlocal