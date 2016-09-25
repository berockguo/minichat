/* seq_server_config.h

 Generated by phxrpc_pb2server from seq.proto

*/

#pragma once

#include "phxrpc/rpc.h"

class SeqServerConfig
{
public:
    SeqServerConfig();

    ~SeqServerConfig();

    bool Read( const char * config_file );

    phxrpc::HshaServerConfig & GetHshaServerConfig();

private:
    phxrpc::HshaServerConfig ep_server_config_;
};
