from __future__ import print_function
import asyncio
import logging

import grpc
import type_pb2
import IntelliSwingInterface_pb2
import IntelliSwingService_pb2
import IntelliSwingInterface_pb2_grpc


async def run():
    # NOTE(gRPC Python Team): .close() is possible on a channel and should be
    # used in circumstances in which the with statement does not fit the needs
    # of the code.
    async with grpc.aio.insecure_channel('localhost:50051') as channel:
        stub = IntelliSwingInterface_pb2_grpc.IntelliSwingProtocolStub(channel)
        response = stub.Initialize(IntelliSwingInterface_pb2.InitializeMsg(client=2))
        
        
        hello_stream = stub.Start(IntelliSwingInterface_pb2.StartMsg())
        while True:
            response = await hello_stream.read()
            if response == grpc.aio.EOF:
                break
            print("Greeter client received from direct read: " +
                  response.heartBeat.meg)


if __name__ == '__main__':
    logging.basicConfig()
    asyncio.run(run())
