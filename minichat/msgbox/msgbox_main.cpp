/* msgbox_main.cpp

 Generated by phxrpc_pb2server from msgbox.proto

*/

#include <iostream>
#include <memory>
#include <unistd.h>
#include <signal.h>
#include "phxrpc_msgbox_dispatcher.h"
#include "msgbox_service_impl.h"
#include "msgbox_server_config.h"

#include "phxrpc/rpc.h"
#include "phxrpc/http.h"
#include "phxrpc/file.h"

#include "common/redis_client_factory.h"

using namespace std;

void HttpDispatch( const phxrpc::HttpRequest & request, phxrpc::HttpResponse * response, phxrpc::DispatcherArgs_t * args ) {

    ServiceArgs_t * service_args = (ServiceArgs_t *)(args->service_args);

    MsgBoxServiceImpl service( * service_args );
    MsgBoxDispatcher dispatcher( service, args );

    phxrpc::HttpDispatcher<MsgBoxDispatcher> http_dispatcher(
            dispatcher, MsgBoxDispatcher::GetURIFuncMap() );
    if( ! http_dispatcher.Dispatch( request, response ) ) {
        response->SetStatusCode( 404 );
        response->SetReasonPhrase( "Not Found" );
    }
}

void showUsage( const char * program ) {
    printf( "\n" );
    printf( "Usage: %s [-c <config>] [-d] [-l <log level>] [-v]\n", program );
    printf( "\n" );

    exit( 0 );
}

int main( int argc, char * argv[] ) {
    const char * config_file = NULL;
    bool daemonize = false;;
    int log_level = -1;
    extern char *optarg ;
    int c ;
    while( ( c = getopt( argc, argv, "c:vl:d" ) ) != EOF ) {
        switch ( c ) {
            case 'c' : config_file = optarg; break;
            case 'd' : daemonize = true; break;
            case 'l' : log_level = atoi( optarg ); break;

            case 'v' :
            default: showUsage( argv[ 0 ] ); break;
        }
    }

    if( daemonize ) phxrpc::ServerUtils::Daemonize();

    assert(signal(SIGPIPE, SIG_IGN) != SIG_ERR);

    //set customize log/monitor
    //phxrpc::setlog(openlog, closelog, vlog);
    //phxrpc::MonitorFactory::SetFactory( new YourSelfsMonitorFactory() );

    if( NULL == config_file ) showUsage( argv[0] );

    MsgBoxServerConfig config;
    if( ! config.Read( config_file ) ) showUsage( argv[0] );

    if( log_level > 0 ) config.GetHshaServerConfig().SetLogLevel( log_level );

    phxrpc::openlog( argv[0], config.GetHshaServerConfig().GetLogDir(),
            config.GetHshaServerConfig().GetLogLevel() );

    ServiceArgs_t service_args;
    service_args.config = &config;
    service_args.factory = new RedisClientFactory( "~/minichat/etc/client/redis_client.conf" );

    phxrpc::HshaServer server( config.GetHshaServerConfig(), HttpDispatch, &service_args );
    server.RunForever();

    phxrpc::closelog();

    return 0;
}
