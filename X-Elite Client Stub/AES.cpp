#include "stdafx.h"

#include "AES.h"
# pragma comment ( lib, "cryptlib" )
using CryptoPP::Exception;
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::AES;
using CryptoPP::CFB_Mode;
using CryptoPP::CBC_Mode;
using CryptoPP::Base64Encoder;
using CryptoPP::Base64Decoder;
namespace Crypt
{
	std::string encrypt(std::string& str_in, std::string& key, std::string& iv)
	{
		std::string str_out;
		CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryption((byte*)key.c_str(), key.length(), (byte*)iv.c_str());
		CryptoPP::StringSource encryptor(str_in, true, new CryptoPP::StreamTransformationFilter(encryption, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(str_out), false)));
		return str_out;
	}

	std::string decrypt(std::string& str_in, std::string& key, std::string& iv)
	{
		std::string str_out;
		CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decryption((byte*)key.c_str(), key.length(), (byte*)iv.c_str());
		CryptoPP::StringSource decryptor(str_in, true, new CryptoPP::Base64Decoder(new CryptoPP::StreamTransformationFilter(decryption, new CryptoPP::StringSink(str_out))));
		return str_out;
	}
}