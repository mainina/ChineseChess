#pragma once
#include "stdafx.h"
#include <Windows.h>

class CThread
{
public:
	CThread(bool bDetach = true);
	~CThread();

	virtual void Run() = 0;
	int Start();
	int Join();
	void Destory();

	int Get_Thread_Id() { return thr_id_; }
	void Set_Thread_Id(unsigned long thrId) { thr_id_ = thrId; }
	bool isExit() { return bExit_; }

protected:
	static DWORD WINAPI Proc(LPVOID lpParam);

private:
	size_t thr_id_;
	bool bExit_;
	DWORD dwThreadId1;
	HANDLE hThread1;

private:
	CThread(const CThread&);
	CThread& operator=(const CThread&);
};

