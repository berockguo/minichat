/* cert_tool_impl.cpp

 Generated by phxrpc_pb2tool from cert.proto

*/

#include "cert_tool_impl.h"
#include "cert_client.h"

#include "phxrpc/file.h"

#include "taocrypt/include/config.h"
#include "taocrypt/include/rsa.hpp"

#include "crypt/pem_file.h"

using namespace phxrpc;

CertToolImpl:: CertToolImpl()
{
}

CertToolImpl:: ~CertToolImpl()
{
}

int CertToolImpl :: PHXEcho( phxrpc::OptMap & opt_map )
{
    google::protobuf::StringValue req;
    google::protobuf::StringValue resp;

    if( NULL == opt_map.Get( 's' ) ) return -1;

    req.set_value( opt_map.Get( 's' ) );

    CertClient client;
    int ret = client.PHXEcho( req, &resp );
    printf( "%s return %d\n", __func__, ret );
    printf( "resp: {\n%s}\n", resp.DebugString().c_str() );

    return ret;
}

int CertToolImpl :: RSADecrypt( phxrpc::OptMap & opt_map )
{
    cert::CodecBuff req;
    google::protobuf::BytesValue resp;

    //TODO: fill req from opt_map

    req.set_key_version( 1 );

    {
        TaoCrypt::RSA_PublicKey pub;
        PemFileUtils::LoadPubKey( "~/minichat/etc/client/minichat_pubkey.pem", &pub );

        TaoCrypt::RandomNumberGenerator rng;
        TaoCrypt::RSAES_Encryptor enc( pub );

        req.mutable_buff()->resize( pub.FixedCiphertextLength() );

        TaoCrypt::byte message[] = "Everyone gets Friday off.";
        const TaoCrypt::word32 len = (TaoCrypt::word32)strlen((char*)message);
        enc.Encrypt( message, len, (unsigned char*)req.buff().data(), rng);
    }

    CertClient client;
    int ret = client.RSADecrypt( req, &resp );
    printf( "%s return %d\n", __func__, ret );
    printf( "resp: {\n%s}\n", resp.DebugString().c_str() );

    return ret;
}

int CertToolImpl :: AESEncrypt( phxrpc::OptMap & opt_map )
{
    cert::CodecBuff req;
    google::protobuf::BytesValue resp;

    //TODO: fill req from opt_map

    req.set_buff( "Hello Cert!" );

    CertClient client;
    int ret = client.AESEncrypt( req, &resp );
    printf( "%s return %d\n", __func__, ret );
    printf( "resp: {\n%s}\n", resp.DebugString().c_str() );

    return ret;
}

int CertToolImpl :: AESDecrypt( phxrpc::OptMap & opt_map )
{
    cert::CodecBuff req;
    google::protobuf::BytesValue resp;

    //TODO: fill req from opt_map

    req.set_buff( "Hello Cert!" );

    CertClient client;
    int ret = client.AESEncrypt( req, &resp );

    printf( "AESEncrypt return %d\n", ret );
    printf( "resp: {\n%s}\n", resp.DebugString().c_str() );

    req.set_buff( resp.value() );
    ret = client.AESDecrypt( req, &resp );

    printf( "%s return %d\n", __func__, ret );
    printf( "resp: {\n%s}\n", resp.DebugString().c_str() );

    return ret;
}

