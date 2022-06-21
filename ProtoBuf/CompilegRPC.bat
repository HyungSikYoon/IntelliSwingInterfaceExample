@echo off

@setlocal
pushd "%~dp0"

set path=%cd%
set output_protobuf_path=%path%
set output_grpc_path=%path%
if not exist %output_protobuf_path% mkdir %output_protobuf_path%
if not exist %output_grpc_path% mkdir %output_grpc_path%

set protoc_path=%protobuf%\tools\protobuf
set grpc_protoc_plugins_path=%grpc%\tools\grpc

set src=IntelliSwingInterface.proto

%protoc_path%\protoc.exe %src% --grpc_out=%output_grpc_path% --plugin=protoc-gen-grpc=%grpc_protoc_plugins_path%\grpc_csharp_plugin.exe --proto_path=.\
%protoc_path%\protoc.exe %src% --grpc_out=%output_grpc_path% --plugin=protoc-gen-grpc=%grpc_protoc_plugins_path%\grpc_cpp_plugin.exe --proto_path=.\
%protoc_path%\protoc.exe %src% --grpc_out=%output_grpc_path% --plugin=protoc-gen-grpc=%grpc_protoc_plugins_path%\grpc_python_plugin.exe --proto_path=.\


%protoc_path%\protoc.exe %1 --cpp_out=%output_protobuf_path% --csharp_out=%output_protobuf_path% --python_out=%output_protobuf_path% --proto_path=.\


popd
@endlocal