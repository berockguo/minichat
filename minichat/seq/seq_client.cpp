/* seq_client.cpp

 Generated by phxrpc_pb2client from seq.proto

*/

#include <iostream>
#include <memory>
#include <stdlib.h>
#include <mutex>

#include "seq_client.h"
#include "phxrpc_seq_stub.h"

#include "phxrpc/rpc.h"

static phxrpc::ClientConfig global_seqclient_config_;
static phxrpc::ClientMonitorPtr global_seqclient_monitor_;

bool SeqClient :: Init( const char * config_file )
{
    return global_seqclient_config_.Read( config_file );
}

const char * SeqClient :: GetPackageName() {
    const char * ret = global_seqclient_config_.GetPackageName();
    if (strlen(ret) == 0) {
        ret = "seq";
    }
    return ret;
}

SeqClient :: SeqClient()
{
    static std::mutex monitor_mutex;
    if ( !global_seqclient_monitor_.get() ) { 
        monitor_mutex.lock();
        if ( !global_seqclient_monitor_.get() ) {
            global_seqclient_monitor_ = phxrpc::MonitorFactory::GetFactory()
                ->CreateClientMonitor( GetPackageName() );
        }
        global_seqclient_config_.SetClientMonitor( global_seqclient_monitor_ );
        monitor_mutex.unlock();
    }
}

SeqClient :: ~SeqClient()
{
}

int SeqClient :: PHXEcho( const google::protobuf::StringValue & req,
        google::protobuf::StringValue * resp )
{
    const phxrpc::Endpoint_t * ep = global_seqclient_config_.GetRandom();

    if(ep != nullptr) {
        phxrpc::BlockTcpStream socket;
        bool open_ret = phxrpc::PhxrpcTcpUtils::Open(&socket, ep->ip, ep->port,
                    global_seqclient_config_.GetConnectTimeoutMS(), NULL, 0, 
                    *(global_seqclient_monitor_.get()));
        if ( open_ret ) {
            socket.SetTimeout(global_seqclient_config_.GetSocketTimeoutMS());

            SeqStub stub(socket, *(global_seqclient_monitor_.get()));
            return stub.PHXEcho(req, resp);
        } 
    }

    return -1;
}

int SeqClient :: PhxBatchEcho( const google::protobuf::StringValue & req,
        google::protobuf::StringValue * resp )
{
    int ret = -1; 
    size_t echo_server_count = 2;
    uthread_begin;
    for (size_t i = 0; i < echo_server_count; i++) {
        uthread_t [=, &uthread_s, &ret](void *) {
            const phxrpc::Endpoint_t * ep = global_seqclient_config_.GetByIndex(i);
            if (ep != nullptr) {
                phxrpc::UThreadTcpStream socket;
                if(phxrpc::PhxrpcTcpUtils::Open(&uthread_s, &socket, ep->ip, ep->port,
                            global_seqclient_config_.GetConnectTimeoutMS(), *(global_seqclient_monitor_.get()))) { 
                    socket.SetTimeout(global_seqclient_config_.GetSocketTimeoutMS());
                    SeqStub stub(socket, *(global_seqclient_monitor_.get()));
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

int SeqClient :: Alloc( const seq::AllocReq & req,
        google::protobuf::UInt32Value * resp )
{
    const phxrpc::Endpoint_t * ep = global_seqclient_config_.GetRandom();

    if(ep != nullptr) {
        phxrpc::BlockTcpStream socket;
        bool open_ret = phxrpc::PhxrpcTcpUtils::Open(&socket, ep->ip, ep->port,
                    global_seqclient_config_.GetConnectTimeoutMS(), NULL, 0, 
                    *(global_seqclient_monitor_.get()));
        if ( open_ret ) {
            socket.SetTimeout(global_seqclient_config_.GetSocketTimeoutMS());

            SeqStub stub(socket, *(global_seqclient_monitor_.get()));
            return stub.Alloc(req, resp);
        } 
    }

    return -1;
}

int SeqClient :: Get( const google::protobuf::StringValue & req,
        seq::SyncKey * resp )
{
    const phxrpc::Endpoint_t * ep = global_seqclient_config_.GetRandom();

    if(ep != nullptr) {
        phxrpc::BlockTcpStream socket;
        bool open_ret = phxrpc::PhxrpcTcpUtils::Open(&socket, ep->ip, ep->port,
                    global_seqclient_config_.GetConnectTimeoutMS(), NULL, 0, 
                    *(global_seqclient_monitor_.get()));
        if ( open_ret ) {
            socket.SetTimeout(global_seqclient_config_.GetSocketTimeoutMS());

            SeqStub stub(socket, *(global_seqclient_monitor_.get()));
            return stub.Get(req, resp);
        } 
    }

    return -1;
}


