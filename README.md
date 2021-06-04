<p align="left"><img width="500" src="./doc/image/logo.png" alt="cppnet logo"></p>

<p align="left">
    <a href="https://travis-ci.org/caozhiyi/CppNet"><img src="https://travis-ci.org/caozhiyi/CppNet.svg?branch=master" alt="Build Status"></a>
    <a href="https://opensource.org/licenses/BSD-3-Clause"><img src="https://img.shields.io/badge/license-bsd-orange.svg" alt="Licenses"></a>
</p> 

See [chinese](/README_cn.md)    
See the details in chinese [Wiki](https://github.com/caozhiyi/CppNet/wiki)
## Introduction

Cppnet is a proactor mode and multithreaded network with C++11 on tcp. Support Window, Linux and macOS.    
 - Simple:    
    + Only export a little interfaces, all net io insterface are asynchronous callbacks
    + Insterface as much as possible like calling the socket API of the system
    + There is only one additional buffer interface for the client
    + Support both IPv4 and IPv6

 - Fast: 
    + Use epoll, IOCP and kqueue
    + Multithreaded threads are handled by the kernel
    + Each socket has a single memory pool object. All memory requested from the memory pool is managed by an intelligent pointer 
    + Using time wheel to realize timer   
 
 - Clear：
    + Three layers: event-driven layer, session management layer and interface layer
    + Upward notification through callbacks between layers. Clear division of responsibilities among modules, pay to Caesar what belongs to Caesar and God what belongs to God
    + The interface decoupling module is used to meet the minimum interface principle and dependency inversion principle  

## Interface

All the interface files are in [include](/include).   
The interface definitions for library initialization and timer are in [cppnet](/include/cppnet.h):    
```c++
// cppnet instance
class CppNet {
public:
    // common
    // init cppnet library.
    // thread_num : the number of running threads.
    void Init(int32_t thread_num = 0);
    void Destory();

    // thread join
    void Join();

    // must set callback before listen
    void SetReadCallback(const read_call_back& cb);
    void SetWriteCallback(const write_call_back& cb);
    void SetDisconnectionCallback(const connect_call_back& cb);

    // if use socket timer, set it
    void SetTimerCallback(const timer_call_back& cb);

    // return timer id
    uint64_t AddTimer(int32_t interval, const user_timer_call_back& cb, void* param = nullptr, bool always = false);
    void RemoveTimer(uint64_t timer_id);

    //server
    void SetAcceptCallback(const connect_call_back& cb);
    bool ListenAndAccept(const std::string& ip, int16_t port);

    //client
    void SetConnectionCallback(const connect_call_back& cb);
    bool Connection(const std::string& ip, int16_t port);
};
```
Since all network IO interfaces are defined as callback notification modes, callback functions for each call need to be set when initializing the library.     
By setting callbacks instead of providing virtual function inheritance, we hope to be as simple as possible, reduce the inheritance relationship of classes, and increase the flexibility of callbacks. You can set callbacks to any function.         
The interface definition for network IO are in [cppnet_socket](/include/cppnet_socket.h):      
```c++
class CNSocket {
public:
    // get socket
    virtual uint64_t GetSocket() = 0;
    // get socket IP and address
    virtual bool GetAddress(std::string& ip, uint16_t& port) = 0;
    // post sync write event.
    virtual bool Write(const char* src, uint32_t len) = 0;
    // close the connect
    virtual void Close() = 0;
    // add a timer. must set timer call back
    // interval support max 1 minute
    virtual void AddTimer(uint32_t interval, bool always = false) = 0;
    virtual void StopTimer() = 0;
};
```
The function of the interface is evident through declarations and annotations. Attention should be paid to the error code returned by the interface, defined in [cppnet_type](/include/cppnet_type.h):    
```c++
    // error code
    CEC_SUCCESS                = 0,    // success.
    CEC_CLOSED                 = 1,    // remote close the socket.
    CEC_CONNECT_BREAK          = 2,    // connect break.
    CEC_CONNECT_REFUSE         = 3,    // remote refuse connect or server not exist.
```
All notifications about the connection status are called back to the connection related functions.     

## Example

All simples are in [test](/test):   
[simple](/test/simple): A most simple example.   
[echo](/test/echo): A test program of echo with 10000 connection.   
[http](/test/http): A simple HTTP server is implemented with reference to muduo.   
[sendfile](/test/sendfile): An example of sending and receiving files.   
[pingpong](/test/pingpong): A pingpong test program.   
[rpc](/test/rpc): A interesting rpc program.   

## Efficiency
Only use apache ab test HTTP echo，comparison with Muduo. The command executed is：ab -kc[1-2000] -n100000 http://127.0.0.1:8000/hello.
<p align="left"><img width="896" src="./doc/image/muduo_vs_cppnet.png" alt="mudo vs cppnet"></p>

## Build

Look at [Build](/doc/build/build.md)

## Licenses

This program is under the terms of the BSD 3-Clause License. See [https://opensource.org/licenses/BSD-3-Clause](https://opensource.org/licenses/BSD-3-Clause).
