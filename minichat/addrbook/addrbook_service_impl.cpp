/* addrbook_service_impl.cpp

 Generated by phxrpc_pb2service from addrbook.proto

*/

#include "addrbook_service_impl.h"
#include "addrbook_server_config.h"
#include "addrbook.pb.h"
#include "phxrpc/file.h"

#include "addrbook_dao.h"

#include "common/redis_client_factory.h"

AddrbookServiceImpl :: AddrbookServiceImpl( ServiceArgs_t & args )
    : args_( args )
{
}

AddrbookServiceImpl :: ~AddrbookServiceImpl()
{
}

int AddrbookServiceImpl :: PHXEcho( const google::protobuf::StringValue & req,
        google::protobuf::StringValue * resp )
{
    resp->set_value( req.value() );
    return 0;
}

int AddrbookServiceImpl :: Set( const addrbook::ContactReq & req,
        google::protobuf::Empty * resp )
{
    AddrbookDAO dao( args_.factory->Get() );

    return dao.Set( req, resp );
}

int AddrbookServiceImpl :: GetAll( const google::protobuf::StringValue & req,
        addrbook::ContactList * resp )
{
    AddrbookDAO dao( args_.factory->Get() );

    return dao.GetAll( req, resp );;
}

int AddrbookServiceImpl :: GetOne( const addrbook::GetOneReq & req,
        addrbook::Contact * resp )
{
    AddrbookDAO dao( args_.factory->Get() );

    return dao.GetOne( req, resp );
}


int AddrbookServiceImpl :: GetBySeq( const addrbook::GetBySeqReq & req,
        addrbook::ContactList * resp )
{
    AddrbookDAO dao( args_.factory->Get() );

    return dao.GetBySeq( req, resp );;
}

