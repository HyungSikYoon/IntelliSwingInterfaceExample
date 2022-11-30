#include "pch.h"
#include <iostream>
#include "ZIntelliSwingServer.h"


ZIntelliSwingServer::ZIntelliSwingServer(grpc::Service* pService, const std::string& address) : m_pService(pService), m_strServerAddress(address)
{

}
bool ZIntelliSwingServer::OnStart()
{
	std::cout << "ZIntelliSwingServer::OnStart " << std::endl;

	m_ThreadCtx.m_pUserData = this;

	grpc::ServerBuilder builder;
	//GRPC_DEFAULT_MAX_SEND_MESSAGE_LENGTH
	builder.SetMaxSendMessageSize(GRPC_DEFAULT_MAX_RECV_MESSAGE_LENGTH *2 );
	builder.SetMaxReceiveMessageSize(GRPC_DEFAULT_MAX_RECV_MESSAGE_LENGTH * 2);
	
	std::cout << "Max Buffer Size changed " << std::endl;
	
	// Listen on the given address without any authentication mechanism.
	builder.AddListeningPort(m_strServerAddress, grpc::InsecureServerCredentials());
	// Register "service" as the instance through which we'll communicate with
	// clients. In this case it corresponds to an *synchronous* service.
	builder.RegisterService(m_pService);
	// Finally assemble the server.
	m_upServer = builder.BuildAndStart();
	
	return true;
}

bool ZIntelliSwingServer::OnStop()
{
	std::cout << "ZIntelliSwingServer::OnStop "<<std::endl;

	if (m_upServer != nullptr)
	{
		m_upServer->Shutdown();
	}
	return true;
}

bool ZIntelliSwingServer::Run(ZThreadContext* ctx)
{
	if (m_upServer != nullptr)
	{
		std::cout << "Server listening on " << m_strServerAddress<<std::endl;

		// Wait for the server to shutdown. Note that some other thread must be
		// responsible for shutting down the server for this call to ever return.
		m_upServer->Wait();
	}
	else
	{
		std::cout<< "Server listening Failure " << m_strServerAddress<<std::endl;
	}

	return true;
}

bool ZIntelliSwingServer::Shutdown()
{
	std::cout<< "ZIntelliSwingServer::Shutdown "<<std::endl;
	//
	if (m_upServer != nullptr)
	{
		m_upServer->Shutdown();
	}
	return true;
}
