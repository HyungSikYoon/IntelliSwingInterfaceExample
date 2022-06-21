#pragma once

#include <string>
#include <memory>
#include <grpc++/grpc++.h>

/**
 * IntelliSwing Client Communication Server has own thread
 */


 // zthread context
class ZThreadContext
{
public:
	bool m_bContinue;
	std::thread* m_pThread;
	void* m_pUserData;

public:
	ZThreadContext()
	{
		m_bContinue = false;
		m_pThread = NULL;
		m_pUserData = NULL;
	}
};

// single thread template class
template <typename T>

class ZSingleThread
{
protected:
	ZThreadContext m_ThreadCtx;

	static void _Run(T* pMe)
	{
		pMe->OnStart();
		pMe->Run(&pMe->m_ThreadCtx);
		pMe->OnStop();
	}

public:
	bool Start()
	{
		if (!m_ThreadCtx.m_pThread)
		{
			m_ThreadCtx.m_bContinue = true;
			m_ThreadCtx.m_pThread = new std::thread(ZSingleThread::_Run, (T*)this);
		}

		return true;
	}

	bool Stop()
	{
		m_ThreadCtx.m_bContinue = false;
		if (m_ThreadCtx.m_pThread)
		{
			m_ThreadCtx.m_pThread->join();
			delete m_ThreadCtx.m_pThread;
			m_ThreadCtx.m_pThread = NULL;
		}

		return true;
	}

	virtual bool OnStart() { return true; }
	virtual bool OnStop() { return true; }
	virtual bool Run(ZThreadContext* ctx) { return true; }
};


class ZIntelliSwingServer : public ZSingleThread<ZIntelliSwingServer>
{

	std::string m_strServerAddress;
	grpc::Service *m_pService;
	std::unique_ptr<grpc::Server> m_upServer;
public:
	ZIntelliSwingServer(grpc::Service* pService, const std::string& address = "0.0.0.0:50051");

	virtual bool OnStart();

	virtual bool OnStop();

	virtual bool Run(ZThreadContext* ctx);

	bool Shutdown();
};

