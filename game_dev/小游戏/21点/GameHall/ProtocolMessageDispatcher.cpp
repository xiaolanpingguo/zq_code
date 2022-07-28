#include "ProtocolMessageDispatcher.h"
#include "..\\GameProtocol\\Protocol.h"
void CPMDispatcher::ProtocolRun(_CNET_EVENT& ne)
{
	_PROTOCOL* xy = (_PROTOCOL*)ne.data;
	std::map<int,CProtocolIndex*>::iterator it = m_ProtocolIndex.find(xy->type);
	if(it != m_ProtocolIndex.end())
		it->second->ProtocolFun(ne);
}

CPMDispatcher::~CPMDispatcher()
{
	std::map<int,CProtocolIndex*>::iterator it;
	for(it = m_ProtocolIndex.begin(); it != m_ProtocolIndex.end(); ++it)
	{
		delete it->second;
	}
}

bool CPMDispatcher::AddProtocol(int type, CProtocolIndex* p)
{
	m_ProtocolIndex.insert(std::pair<int,CProtocolIndex*>(type,p));
	return true;
}