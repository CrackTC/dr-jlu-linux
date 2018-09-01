#ifndef AUTH_H_
#define AUTH_H_

enum {
	// DrЭ�鲿��
	CHECK_MAC = 0x01,
	SERVER_BUSY = 0x02,
	WRONG_PASS = 0x03,
	NOT_ENOUGH = 0x04,
	FREEZE_UP = 0x05,
	NOT_ON_THIS_IP = 0x07,
	NOT_ON_THIS_MAC = 0x0B,
	TOO_MUCH_IP = 0x14,
	UPDATE_CLIENT = 0x15,
	NOT_ON_THIS_IP_MAC = 0x16,
	MUST_USE_DHCP = 0x17,

	// �Զ��岿��
	UNKNOWN_ERROR = 0x18,

	// dogcom()����
	INIT_ERROR		 = 0x19, // WSAStartup(sockVersion, &wsaData) != 0ʧ��
	CREATE_SOCKET	 = 0x20, // create socketʧ��
	BIND_SOCKET		 = 0x21, // bind socketʧ��
	SET_SOCK_OPT	 = 0x22, // set sock optʧ��
	CHALLENGE_ERROR	 = 0x23, // challengeʧ��
	USER_TERMINATED  = 0x24  // �û�ȡ������
};

//  �����־
void print_packet(const char msg[10], const unsigned char *packet, int length);

int dhcp_login(int sockfd, struct sockaddr_in addr, unsigned char seed[], unsigned char auth_information[]);
int dogcom();
void get_lasterror(const char *msg);

#endif // AUTH_H_