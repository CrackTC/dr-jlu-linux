#include "./dogcom/login.h"
#include <cstdio>

// 登录信息
struct tagLogInfo logInfo{"<username>", "<password>"};
const char* strBuf = "xxxxxxxxxxxx"; // mac address

int status = OFFLINE;

// 收到的报文中的ip地址
unsigned char receivedIp[4];


char getCharFromInt(int x) {
	if (x <= 9 && x >= 0) return (char)(x + '0');
	return (char)(x - 10 + 'a');
}
int getIntFromChar(char x) {
	if (x <= '9' && x >= '0') return x - '0';
	return x - 'a' + 10;
}


void load() {
    std::printf("load account: %s\n", logInfo.account);
	std::printf("load pass: %s\n", logInfo.pass);
	std::printf("load mac: %s\n", strBuf);
	for (int i = 0; i < 6; i++) {
		logInfo.mac[i] = (unsigned char)((getIntFromChar(strBuf[2 * i]) << 4)
						| getIntFromChar(strBuf[2 * i + 1]));
	}
}

int main()
{
    load();
    login(logInfo.account, logInfo.pass, logInfo.mac);
}
