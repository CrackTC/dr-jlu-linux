#include <cstring>
#include "auth.h"
#include "configparse.h"
#include "login.h"

struct config drcom_config;
char *err_msg;
InterruptibleSleeper sleeper;

int threadLogin() {
	// 返回值非0即为登录失败
	status = LOGGING;
	std::printf(("status状态变为LOGGING\n"));
	int result = dogcom();
	std::printf(("\nresult = %d\n"), result);
	switch (result) {
	case 0:
		break;
	case CHECK_MAC:
		err_msg = (char*)"[Tips] 有人正在用该MAC地址使用此账号";
		break;
	case SERVER_BUSY:
		err_msg = (char*)("[Tips] 服务器繁忙，请重试");
		break;
	case WRONG_PASS:
		err_msg = (char*)("[Tips] 账号或密码错误");
		break;
	case NOT_ENOUGH:
		err_msg = (char*)("[Tips] 该账号使用时长或流量超限");
		break;
	case FREEZE_UP:
		err_msg = (char*)("[Tips] 该账号被冻结");
		break;
	case NOT_ON_THIS_IP:
		err_msg = (char*)("[Tips] IP地址不匹配，该账号只能用于指定IP");
		break;
	case NOT_ON_THIS_MAC:
		err_msg = (char*)("[Tips] MAC地址不匹配，该账号只能用于指定的MAC地址");
		break;
	case TOO_MUCH_IP:
		err_msg = (char*)("[Tips] 该账号对应多个IP地址");
		break;
	case UPDATE_CLIENT:
		err_msg = (char*)("[Tips] 客户端版本号错误，请升级客户端");
		break;
	case NOT_ON_THIS_IP_MAC:
		err_msg = (char*)("[Tips] 该账号只可用于指定的IP和MAC地址");
		break;
	case MUST_USE_DHCP:
		err_msg = (char*)("[Tips] 请将计算机的TCP/IPv4属性设置为DHCP");
		break;
	case INIT_ERROR:
		err_msg = (char*)("[Tips] 程序初始化失败");
		break;
	case CREATE_SOCKET:
		err_msg = (char*)("[Tips] 创建socket失败");
		break;
	case BIND_SOCKET:
		err_msg = (char*)("[Tips] 绑定socket失败 请检查是否有其他客户端占用了端口");
		break;
	case SET_SOCK_OPT:
		err_msg = (char*)("[Tips] 设置socket选项失败");
		break;
	case CHALLENGE_ERROR:
		err_msg = (char*)("[Tips] 与服务器握手失败");
		break;
	case USER_TERMINATED:
		err_msg = (char*)("[Tips] 用户注销");
		break;
	case UNKNOWN_ERROR:
	default:
		err_msg = (char*)("[Tips] 未知错误");
		break;
	}
	if (!result)
		std::printf(("%s\n"), err_msg);
	// 只要是返回过来了一定是失败了
	status = OFFLINE;
	std::printf(("status状态变为OFFLINE\n"));
    std::printf("已离线\n");
    if (!std::strcmp(err_msg, "[Tips] 账号或密码错误")) {
        std::printf("账号或密码错误，已清除保存的密码\n");
    }
	return 0;
}

void login(const char *account, const char *password, const unsigned char mac[6]) {
	fillConfig(account, password, mac);
	std::printf(("填充完成\n"));
	sleeper.reset();
	threadLogin();
}

void logout() {
	sleeper.interrupt();
}
