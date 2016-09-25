/* cert_service_impl.cpp

 Generated by phxrpc_pb2service from cert.proto

*/

#include "cert_service_impl.h"
#include "cert_server_config.h"
#include "cert.pb.h"
#include "phxrpc/file.h"

#include "cert_codec.h"

CertServiceImpl :: CertServiceImpl( ServiceArgs_t & args )
    : args_( args )
{
}

CertServiceImpl :: ~CertServiceImpl()
{
}

int CertServiceImpl :: PHXEcho( const google::protobuf::StringValue & req,
        google::protobuf::StringValue * resp )
{
    resp->set_value( req.value() );
    return 0;
}

int CertServiceImpl :: RSADecrypt( const cert::CodecBuff & req,
        google::protobuf::BytesValue * resp )
{
    return CertCodec::GetDefault()->RSADecrypt( req, resp );
}

int CertServiceImpl :: AESEncrypt( const cert::CodecBuff & req,
        google::protobuf::BytesValue * resp )
{
    return CertCodec::GetDefault()->AESEncrypt( req, resp );
}


int CertServiceImpl :: AESDecrypt( const cert::CodecBuff & req,
        google::protobuf::BytesValue * resp )
{
    return CertCodec::GetDefault()->AESDecrypt( req, resp );
}


