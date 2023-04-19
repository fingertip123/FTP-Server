#include "function.h"

int get_file_md5(const std::string &file_name, std::string &md5_value)
{
	md5_value.clear();

	std::ifstream file(file_name.c_str(), std::ifstream::binary);
	if (!file)
	{
		return -1;
	}

	MD5_CTX md5Context;
	MD5_Init(&md5Context);//初始化MD5_CTX结构体指针

	char buf[1024 * 16];
	while (file.good())//当前流是否正常
	{
		file.read(buf, sizeof(buf));
		MD5_Update(&md5Context, buf, file.gcount());//读取实际read的字符数
	}

	unsigned char result[MD5_DIGEST_LENGTH];
	MD5_Final(result, &md5Context);

	char hex[35];//转成16进制
	memset(hex, 0, sizeof(hex));
	for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
	{
		sprintf(hex + i * 2, "%02x", result[i]);//以16进制形式输出，02表示不足两位，前面补0输出
	}
	hex[32] = '\0';
	md5_value = string(hex);

	return 0;
}


