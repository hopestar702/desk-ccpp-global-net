#ifndef HEADER_EVENTHANDLER
#define HEADER_EVENTHANDLER
#include <memory>
#include <atomic>

#include "Buffer.h"
#include "PoolSharedPtr.h"
#include "Socket.h"
#include "AcceptSocket.h"

#define INVALID_TIMER -1

enum EVENT_FLAG {
	EVENT_READ    = 0x0001,	//read event
	EVENT_WRITE	  = 0x0002,	//write event
	EVENT_ACCEPT  = 0x0004,	//accept event
	EVENT_TIMER	  = 0x0008	//timer event
};

enum EVENT_ERROR {
	EVENT_ERROR_NO		= 0,
	EVENT_ERROR_TIMEOUT = 1,
	EVENT_ERROR_CLOSED	= 2
};

class CEventHandler {
public:
	CMemSharePtr<CBuffer>		_buffer;
	CMemSharePtr<CSocket>		_client_socket;
	int							_off_set;				//read or write size

	//don't change following members
	void*						_data = nullptr;
	int							_event_flag_set = 0;
	CAcceptSocket*				_accept_socket = nullptr;
	bool						_timer_out = false;
	bool						_timer_set = false;		//is add in timer map?
	unsigned int				_timer_id = 0;
	std::function<void(CMemSharePtr<CEventHandler>&, int error)>	_call_back;
};

class CAcceptEventHandler {
public:
	CMemSharePtr<CSocket>		_client_socket;
	int							_off_set;				//read or write size

	void*						_data = nullptr;
	int							_event_flag_set = 0;
	CAcceptSocket*				_accept_socket = nullptr;

	std::function<void(CMemSharePtr<CEventHandler>&, int error)>	_call_back;
};
#endif