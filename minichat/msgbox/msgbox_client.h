/* msgbox_client.h

 Generated by phxrpc_pb2client from msgbox.proto

*/

#pragma once

#include "msgbox.pb.h"
#include "phxrpc/rpc.h"

class MsgBoxClient
{
public:
    static bool Init( const char * config_file );

    static const char * GetPackageName();

public:
    MsgBoxClient();
    ~MsgBoxClient();

    int PHXEcho( const google::protobuf::StringValue & req,
        google::protobuf::StringValue * resp );

    int PhxBatchEcho( const google::protobuf::StringValue & req,
        google::protobuf::StringValue * resp );

    int Add( const msgbox::MsgIndex & req,
        msgbox::AddMsgResp * resp );

    int GetBySeq( const msgbox::GetBySeqReq & req,
        msgbox::MsgIndexList * resp );

    int GetAll( const google::protobuf::StringValue & req,
        msgbox::MsgIndexList * resp );


};
