/* profile_client.cpp

 Generated by phxrpc_pb2client from profile.proto

*/

#include <iostream>
#include <memory>
#include <stdlib.h>
#include <mutex>

#include "profile_client.h"
#include "phxrpc_profile_stub.h"

#include "phxrpc/rpc.h"

static phxrpc::ClientConfig global_profileclient_config_;
static phxrpc::ClientMonitorPtr global_profileclient_monitor_;

bool ProfileClient :: Init( const char * config_file )
{
    return global_profileclient_config_.Read( config_file );
}

const char * ProfileClient :: GetPackageName() {
    const char * ret = global_profileclient_config_.GetPackageName();
    if (strlen(ret) == 0) {
        ret = "profile";
    }
    return ret;
}

ProfileClient :: ProfileClient()
{
    static std::mutex monitor_mutex;
    if ( !global_profileclient_monitor_.get() ) { 
        monitor_mutex.lock();
        if ( !global_profileclient_monitor_.get() ) {
            global_profileclient_monitor_ = phxrpc::MonitorFactory::GetFactory()
                ->CreateClientMonitor( GetPackageName() );
        }
        global_profileclient_config_.SetClientMonitor( global_profileclient_monitor_ );
        monitor_mutex.unlock();
    }
}

ProfileClient :: ~ProfileClient()
{
}

int ProfileClient :: PHXEcho( const google::protobuf::StringValue & req,
        google::protobuf::StringValue * resp )
{
    const phxrpc::Endpoint_t * ep = global_profileclient_config_.GetRandom();

    if(ep != nullptr) {
        phxrpc::BlockTcpStream socket;
        bool open_ret = phxrpc::PhxrpcTcpUtils::Open(&socket, ep->ip, ep->port,
                    global_profileclient_config_.GetConnectTimeoutMS(), NULL, 0, 
                    *(global_profileclient_monitor_.get()));
        if ( open_ret ) {
            socket.SetTimeout(global_profileclient_config_.GetSocketTimeoutMS());

            ProfileStub stub(socket, *(global_profileclient_monitor_.get()));
            return stub.PHXEcho(req, resp);
        } 
    }

    return -1;
}

int ProfileClient :: PhxBatchEcho( const google::protobuf::StringValue & req,
        google::protobuf::StringValue * resp )
{
    int ret = -1; 
    size_t echo_server_count = 2;
    uthread_begin;
    for (size_t i = 0; i < echo_server_count; i++) {
        uthread_t [=, &uthread_s, &ret](void *) {
            const phxrpc::Endpoint_t * ep = global_profileclient_config_.GetByIndex(i);
            if (ep != nullptr) {
                phxrpc::UThreadTcpStream socket;
                if(phxrpc::PhxrpcTcpUtils::Open(&uthread_s, &socket, ep->ip, ep->port,
                            global_profileclient_config_.GetConnectTimeoutMS(), *(global_profileclient_monitor_.get()))) { 
                    socket.SetTimeout(global_profileclient_config_.GetSocketTimeoutMS());
                    ProfileStub stub(socket, *(global_profileclient_monitor_.get()));
                    int this_ret = stub.PHXEcho(req, resp);
                    if (this_ret == 0) {
                        ret = this_ret;
                        uthread_s.Close();
                    }   
                }   
            }
        };  
    }   
    uthread_end;
    return ret;
}

int ProfileClient :: Set( const profile::Setting & req,
        google::protobuf::Empty * resp )
{
    const phxrpc::Endpoint_t * ep = global_profileclient_config_.GetRandom();

    if(ep != nullptr) {
        phxrpc::BlockTcpStream socket;
        bool open_ret = phxrpc::PhxrpcTcpUtils::Open(&socket, ep->ip, ep->port,
                    global_profileclient_config_.GetConnectTimeoutMS(), NULL, 0, 
                    *(global_profileclient_monitor_.get()));
        if ( open_ret ) {
            socket.SetTimeout(global_profileclient_config_.GetSocketTimeoutMS());

            ProfileStub stub(socket, *(global_profileclient_monitor_.get()));
            return stub.Set(req, resp);
        } 
    }

    return -1;
}

int ProfileClient :: Get( const google::protobuf::StringValue & req,
        profile::Setting * resp )
{
    const phxrpc::Endpoint_t * ep = global_profileclient_config_.GetRandom();

    if(ep != nullptr) {
        phxrpc::BlockTcpStream socket;
        bool open_ret = phxrpc::PhxrpcTcpUtils::Open(&socket, ep->ip, ep->port,
                    global_profileclient_config_.GetConnectTimeoutMS(), NULL, 0, 
                    *(global_profileclient_monitor_.get()));
        if ( open_ret ) {
            socket.SetTimeout(global_profileclient_config_.GetSocketTimeoutMS());

            ProfileStub stub(socket, *(global_profileclient_monitor_.get()));
            return stub.Get(req, resp);
        } 
    }

    return -1;
}

