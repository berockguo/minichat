/* logic_server_config.cpp

 Generated by phxrpc_pb2server from logic.proto

*/

#include "logic.pb.h"
#include "logic_server_config.h"

LogicServerConfig :: LogicServerConfig()
{
}

LogicServerConfig :: ~LogicServerConfig()
{
}

bool LogicServerConfig :: Read( const char * config_file )
{
    bool ret = ep_server_config_.Read( config_file );

    if ( strlen( ep_server_config_.GetPackageName() ) == 0 ) {
        ep_server_config_.SetPackageName( 
logic::MiniRequest::default_instance().GetDescriptor()->file()->package().c_str() );
    }

    return ret;
}

const phxrpc::HshaServerConfig & LogicServerConfig :: GetHshaServerConfig()
{
    return ep_server_config_;
}