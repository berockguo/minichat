/* account_server_config.h

 Generated by phxrpc_pb2server from account.proto

*/

#pragma once

#include "phxrpc/rpc.h"

class AccountServerConfig
{
public:
    AccountServerConfig();

    ~AccountServerConfig();

    bool Read( const char * config_file );

    phxrpc::HshaServerConfig & GetHshaServerConfig();

private:
    phxrpc::HshaServerConfig ep_server_config_;
};
