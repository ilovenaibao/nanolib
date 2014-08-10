//=====================================================================
//
// itoolkit.h - 工具函数大集合
//
// NOTE:
// for more information, please see the readme file.
//
//=====================================================================

#ifndef __ITOOLKIT_H__
#define __ITOOLKIT_H__

#include "imemdata.h"
#include "inetcode.h"
#include "iposix.h"


#ifdef __cplusplus
extern "C" {
#endif


//=====================================================================
// CAsyncNotify
//=====================================================================
struct CAsyncNotify;
typedef struct CAsyncNotify CAsyncNotify;


//=====================================================================
// interfaces
//=====================================================================

// create object
CAsyncNotify* async_notify_new(int serverid);

// delete object
void async_notify_delete(CAsyncNotify *notify);


#define ASYNC_NOTIFY_EVT_DATA			1
#define ASYNC_NOTIFY_EVT_ACCEPT			2
#define ASYNC_NOTIFY_EVT_ESTAB			4
#define ASYNC_NOTIFY_EVT_LISTEN			8
#define ASYNC_NOTIFY_EVT_CLOSED			16
#define ASYNC_NOTIFY_EVT_ERROR			32
#define ASYNC_NOTIFY_EVT_CORE			64

// wait events
void async_notify_wait(CAsyncNotify *notify, IUINT32 millisec);

// wake-up from waiting
void async_notify_wake(CAsyncNotify *notify);

// read events, returns data length of the message, 
// and returns -1 for no event, -2 for buffer size too small,
// returns data size when data equals NULL.
long async_notify_read(CAsyncNotify *notify, int *event, long *wparam,
	long *lparam, void *data, long maxsize);


// new listen: return id(-1 error, -2 port conflict), flag&1(reuse)
long async_notify_listen(CAsyncNotify *notify, const struct sockaddr *addr,
	int addrlen, int flag);

// remove listening port
int async_notify_remove(CAsyncNotify *notify, long listenid, int code);

// setup self server id
void async_notify_change(CAsyncNotify *notify, int new_server_id);


// send message to server
int async_notify_send(CAsyncNotify *notify, int sid, short cmd, 
	const void *data, long size);

// close server connection
int async_notify_close(CAsyncNotify *notify, int sid, int mode, int code);

// get listening port
int async_notify_get_port(CAsyncNotify *notify, long listenid);

// config
int async_notify_option(CAsyncNotify *notify, int type, int value);

// clear ip allow table
void async_notify_allow_clear(CAsyncNotify *notify);

// add or update ip in allow table
void async_notify_allow_add(CAsyncNotify *notify, const void *ip, int size);

// remove ip from table
void async_notify_allow_del(CAsyncNotify *notify, const void *ip, int size);

// ip table enable: enable is 0(disable allow table) otherwise(enable)
void async_notify_allow_enable(CAsyncNotify *notify, int enable);


// add or update a sid into sid2addr
void async_notify_sid_add(CAsyncNotify *notify, int sid,
	struct sockaddr *remote, int size);

// add or update a sid into sid2addr
void async_notify_sid_del(CAsyncNotify *notify, int sid);

// list sids into an array
int async_notify_sid_list(CAsyncNotify *notify, int *sids);


#define ASYNC_NOTIFY_LOG_INFO		1
#define ASYNC_NOTIFY_LOG_REJECT		2
#define ASYNC_NOTIFY_LOG_WARNING	4

#ifdef __cplusplus
}
#endif


#endif


