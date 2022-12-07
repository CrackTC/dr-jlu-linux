#ifndef LOGIN_H
#define LOGIN_H
#include <condition_variable>

void login(const char *account, const char *password, const unsigned char mac[6]);
void logout();

struct tagLogInfo {
	char account[48];
	char pass[48];
	unsigned char mac[6];
};

class InterruptibleSleeper {
public:
	// returns false if killed:
	template<typename R, typename P>
	bool wait_for(std::chrono::duration<R, P> const& time) {
		std::unique_lock<std::mutex> lock(m);
		return !cv.wait_for(lock, time, [&] {return terminate; });
	}
	void interrupt() {
		std::unique_lock<std::mutex> lock(m);
		terminate = true;
		cv.notify_all();
	}
	void reset() {
		terminate = false;
	}
private:
	std::condition_variable cv;
	std::mutex m;
	bool terminate = false;
};

extern InterruptibleSleeper sleeper;

extern struct tagLogInfo logInfo;
extern int status;
extern char *err_msg;
extern unsigned char receivedIp[4];

enum {
	OFFLINE = 1,
	LOGGING = 2,
	LOGGEDIN = 3
};
#endif // LOGIN_H
