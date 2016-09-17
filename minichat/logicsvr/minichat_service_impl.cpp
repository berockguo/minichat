/* minichat_service_impl.cpp

 Generated by phxrpc_pb2service from minichat.proto

*/

#include "minichat_service_impl.h"
#include "minichat_server_config.h"
#include "minichat.pb.h"
#include "phxrpc/file.h"

#include "cgi_sendmsg.h"

MiniChatServiceImpl :: MiniChatServiceImpl( ServiceArgs_t * app_args )
    : config_( *(app_args->config) )
{
}

MiniChatServiceImpl :: ~MiniChatServiceImpl()
{
}

int MiniChatServiceImpl :: PHXEcho( const google::protobuf::StringValue & req,
        google::protobuf::StringValue * resp )
{
    resp->set_value( req.value() );
    return 0;
}

int MiniChatServiceImpl :: Auth( const minichat::MiniRequest & req,
        minichat::MiniResponse * resp )
{
    return -1;
}

int MiniChatServiceImpl :: Sync( const minichat::MiniRequest & req,
        minichat::MiniResponse * resp )
{
    return -1;
}

int MiniChatServiceImpl :: SendMsg( const minichat::MiniRequest & req,
        minichat::MiniResponse * resp )
{
    CgiSendMsg cgi;

    int ret = cgi.Execute( req, resp );

    resp->set_ret( 0 );
    resp->set_err_msg( "ok" );
    printf( "%s\n", resp->DebugString().c_str() );

    return ret;
}

