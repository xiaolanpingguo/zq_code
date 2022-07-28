#ifndef _PROTOCOL_MESSAGE_DISPATCHER_H_
#define _PROTOCOL_MESSAGE_DISPATCHER_H_

#include "DataDefine.h"
#include "ProtocolIndex.h"

class CPMDispatcher
{
	std::map<int,CProtocolIndex*> m_ProtocolIndex;
public:
	~CPMDispatcher();
	void ProtocolRun(_CNET_EVENT& ne);
	bool AddProtocol(int type, CProtocolIndex* p);
};

#endif