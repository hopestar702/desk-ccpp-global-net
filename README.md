## Quick Start
Quick use of `cppnet` and precautions, see [quick start](doc/start/quick_start.md).

## Interface

`cppnet` has three types of external interfaces, which are also defined in three header files   
- Initialization and global configuration, defined in [cppnet](/include/cppnet.h)   
- `socket` operation, defined in [cppnet_socket](/include/cppnet_socket.h)   
- `buffer` read, defined in [cppnet_buffer](/include/cppnet_buffer.h)   
   
For details, see [API](/doc/api/api.md).   

## Example

All simples are in [test](/test):   
- [simple](/test/simple): Most simple example.   
- [echo](/test/echo): Test program of echo with 200 connection.   
- [http](/test/http): Simple HTTP server is implemented with reference to muduo.   
- [sendfile](/test/sendfile): Example of sending and receiving files.   
- [pingpong](/test/pingpong): Pingpong test program.   
- [rpc](/test/rpc): Interesting rpc program.   
- [multi_port](/test/multi_port): Example of multiple listening ports.      

## Efficiency

Apache `ab` is used to pressure test the `http` test service in the [test](/test) directory, and compared with `muduo`.    
For details, see [ab benchmark](/doc/efficiency/apache_ab_bench.md)。

## Build

Look at [Build](/doc/build/build.md)
