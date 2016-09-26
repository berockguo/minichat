
#pragma once

#include <string>

#include "logic.pb.h"

#include "phxrpc/network.h"

namespace phxrpc {
    class UThreadEpollScheduler;
};

class MiniChatAPI {
public:
    static bool Init( const char * config_file );
    static const char * GetPackageName();

public:
    MiniChatAPI( phxrpc::UThreadEpollScheduler * scheduler = NULL );
    ~MiniChatAPI();

    int Auth( const char * username, const char * pwd_md5, logic::AuthResponse * resp );

    int SendMsg( const char * username, const char * to,
            const char * text, logic::SendMsgResponse * resp );

    int Sync( const char * username, logic::SyncResponse * resp );

private:
    int Call_L0( const char * uri, int cmd_id,
            const logic::MiniRequest & req, logic::MiniResponse * resp );

    int Call_L1( const char * uri, int cmd_id,
            const google::protobuf::MessageLite & request,
            google::protobuf::MessageLite * response );

private:
    std::string username_;
    std::string session_key_;
    logic::SyncKey sync_key_;

    phxrpc::UThreadEpollScheduler * scheduler_;
};

