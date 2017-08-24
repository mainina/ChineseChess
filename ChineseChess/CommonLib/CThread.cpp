#include "stdafx.h"
#include "CThread.h"


CThread::CThread(bool bDetach)
{
	bExit_ = false;
}


CThread::~CThread()
{
}

int CThread::Start()
{
	// 6.创建线程执行收发数据 
	hThread1 = CreateThread(NULL, NULL, CThread::Proc, this, 0, &dwThreadId1);
	return 1;
}

int CThread::Join()
{
	bExit_ = true;
	WaitForSingleObject(hThread1, INFINITE);
	return 1;
}

void CThread::Destory()
{
	if (!bExit_) {
		Join();
	}
	CloseHandle(hThread1);
}

DWORD CThread::Proc(LPVOID lpParam)
{
	CThread* pthis = static_cast<CThread*>(lpParam);
	while (!pthis->bExit_)
	{
		pthis->Run();
		pthis->Join();
	}
	return pthis->dwThreadId1;
}
