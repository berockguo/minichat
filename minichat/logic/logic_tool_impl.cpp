/* logic_tool_impl.cpp

 Generated by phxrpc_pb2tool from logic.proto

*/

#include "logic_tool_impl.h"
#include "logic_client.h"

#include "phxrpc/file.h"

#include "minichat_api.h"

using namespace phxrpc;

LogicToolImpl:: LogicToolImpl()
{
}

LogicToolImpl:: ~LogicToolImpl()
{
}

int LogicToolImpl :: PHXEcho( phxrpc::OptMap & opt_map )
{
    google::protobuf::StringValue req;
    google::protobuf::StringValue resp;

    if( NULL == opt_map.Get( 's' ) ) return -1;

    req.set_value( opt_map.Get( 's' ) );

    LogicClient client;
    int ret = client.PHXEcho( req, &resp );
    printf( "%s return %d\n", __func__, ret );
    printf( "resp: {\n%s}\n", resp.DebugString().c_str() );

    return ret;
}

int LogicToolImpl :: Auth( phxrpc::OptMap & opt_map )
{
    if( NULL == opt_map.Get( 'u' ) || NULL == opt_map.Get( 'p' ) ) {
        return -1;
    }

    MiniChatAPI api;

    logic::AuthResponse resp_obj;

    int ret = api.Auth( opt_map.Get( 'u' ), opt_map.Get( 'p' ), &resp_obj );

    printf( "%s return %d\n", __func__, ret );
    printf( "resp: {\n%s}\n", resp_obj.DebugString().c_str() );

    return ret;
}

int LogicToolImpl :: Sync( phxrpc::OptMap & opt_map )
{
    if( NULL == opt_map.Get( 'u' ) ) return -1;

    MiniChatAPI api;

    logic::SyncResponse resp_obj;

    int ret = api.Sync( opt_map.Get( 'u' ), &resp_obj );
    
    printf( "%s return %d\n", __func__, ret );
    printf( "resp_obj: {\n%s}\n", resp_obj.DebugString().c_str() );

    return ret;
}

int LogicToolImpl :: SendMsg( phxrpc::OptMap & opt_map )
{
    if( NULL == opt_map.Get( 's' ) || NULL == opt_map.Get( 't' )
            || NULL == opt_map.Get( 'm' ) ) {
        return -1;
    }

    MiniChatAPI api;

    logic::SendMsgResponse resp_obj;

    int ret = api.SendMsg( opt_map.Get( 's' ), opt_map.Get( 't' ),
            opt_map.Get( 'm' ), &resp_obj );

    printf( "%s return %d\n", __func__, ret );
    printf( "resp_obj: {\n%s\n}\n", resp_obj.DebugString().c_str() );

    return ret;
}

