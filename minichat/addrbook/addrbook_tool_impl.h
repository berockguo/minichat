/* addrbook_tool_impl.h

 Generated by phxrpc_pb2tool from addrbook.proto

*/

#pragma once

#include <stdio.h>

#include "phxrpc_addrbook_tool.h"
namespace phxrpc {
    class OptMap;
}

class AddrbookToolImpl : public AddrbookTool
{
public:
    AddrbookToolImpl();
    virtual ~AddrbookToolImpl();

    virtual int PHXEcho( phxrpc::OptMap & opt_map );

    virtual int Add( phxrpc::OptMap & opt_map );

    virtual int GetAll( phxrpc::OptMap & opt_map );

    virtual int GetOne( phxrpc::OptMap & opt_map );

};
