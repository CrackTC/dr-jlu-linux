#include <csignal>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <cstring>
#include "windows.h"
#include "auth.h"
#include "configparse.h"
#include "../LogUtil.h"
#include "login.h"

struct config drcom_config;
TCHAR *err_msg;
HANDLE hLoginThread;
InterruptibleSleeper sleeper;

DWORD WINAPI threadLogin(LPVOID lpParameter) {
	// ����ֵ��0��Ϊ��¼ʧ��
	status = LOGGING;
	logd(TEXT("status״̬��ΪLOGGING"));
	int result = dogcom();
	logd(TEXT("\nresult = %d\n"), result);
	switch (result) {
	case 0:
		break;
	case CHECK_MAC:
		err_msg = (TCHAR*)TEXT("[Tips] ���������ø�MAC��ַʹ�ô��˺�");
		break;
	case SERVER_BUSY:
		err_msg = (TCHAR*)TEXT("[Tips] ��������æ��������");
		break;
	case WRONG_PASS:
		err_msg = (TCHAR*)TEXT("[Tips] �˺Ż��������");
		break;
	case NOT_ENOUGH:
		err_msg = (TCHAR*)TEXT("[Tips] ���˺�ʹ��ʱ������������");
		break;
	case FREEZE_UP:
		err_msg = (TCHAR*)TEXT("[Tips] ���˺ű�����");
		break;
	case NOT_ON_THIS_IP:
		err_msg = (TCHAR*)TEXT("[Tips] IP��ַ��ƥ�䣬���˺�ֻ������ָ��IP");
		break;
	case NOT_ON_THIS_MAC:
		err_msg = (TCHAR*)TEXT("[Tips] MAC��ַ��ƥ�䣬���˺�ֻ������ָ����MAC��ַ");
		break;
	case TOO_MUCH_IP:
		err_msg = (TCHAR*)TEXT("[Tips] ���˺Ŷ�Ӧ���IP��ַ");
		break;
	case UPDATE_CLIENT:
		err_msg = (TCHAR*)TEXT("[Tips] �ͻ��˰汾�Ŵ����������ͻ���");
		break;
	case NOT_ON_THIS_IP_MAC:
		err_msg = (TCHAR*)TEXT("[Tips] ���˺�ֻ������ָ����IP��MAC��ַ");
		break;
	case MUST_USE_DHCP:
		err_msg = (TCHAR*)TEXT("[Tips] �뽫�������TCP/IPv4��������ΪDHCP");
		break;
	case INIT_ERROR:
		err_msg = (TCHAR*)TEXT("[Tips] �����ʼ��ʧ��");
		break;
	case CREATE_SOCKET:
		err_msg = (TCHAR*)TEXT("[Tips] ����socketʧ��");
		break;
	case BIND_SOCKET:
		err_msg = (TCHAR*)TEXT("[Tips] ��socketʧ�� �����Ƿ��������ͻ���ռ���˶˿�");
		break;
	case SET_SOCK_OPT:
		err_msg = (TCHAR*)TEXT("[Tips] ����socketѡ��ʧ��");
		break;
	case CHALLENGE_ERROR:
		err_msg = (TCHAR*)TEXT("[Tips] �����������ʧ��");
		break;
	case USER_TERMINATED:
		err_msg = (TCHAR*)TEXT("[Tips] �û�ע��");
		break;
	case UNKNOWN_ERROR:
	default:
		err_msg = (TCHAR*)TEXT("[Tips] δ֪����");
		break;
	}
	if (!result)
		logd(TEXT("%s"), err_msg);
	// ֻҪ�Ƿ��ع�����һ����ʧ����
	status = OFFLINE;
	logd(TEXT("status״̬��ΪOFFLINE"));
	SendMessage(FindWindow(szHiddenName, szHiddenTitle), WM_USER_LOGIN_FAILED, 0, 0);
	return 0;
}

void login(const char *account, const char *password, const unsigned char mac[6]) {
	fillConfig(account, password, mac);
	logd(TEXT("������"));
	sleeper.reset();

	// ����һ���̲߳�������߳�
	hLoginThread = CreateThread(nullptr, 0, threadLogin, nullptr, CREATE_SUSPENDED, nullptr);
	// ���ø��̵߳����ȼ�
	SetThreadPriority(hLoginThread, THREAD_PRIORITY_HIGHEST);
	// ִ�и��߳�
	ResumeThread(hLoginThread);
}

void logout() {
	sleeper.interrupt();
}