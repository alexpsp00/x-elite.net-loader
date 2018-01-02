
#include "AESTrans.h"


char *send_encrypted(SOCKET s, char* message, std::string key, std::string iv)
{
	std::string str_message;
	str_message = Crypt::encrypt(std::string(message), key, iv);
	send(s, str_message.c_str(), 200, 0);

}


std::string recv_decrypt(SOCKET s, char * buffer, std::string key, std::string iv)
{
	std::string str_message;
	recv(s, buffer, 200, 0);
	str_message = Crypt::decrypt(std::string(buffer), key, iv);
	return str_message;
}