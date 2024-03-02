# dr-jlu-linux
吉大Linux端Dr校园网登录客户端

移植自 https://github.com/code4lala/dr-jlu-win32

# Installation

1. clone this repository
```shell
git clone https://github.com/CrackTC/dr-jlu-linux.git
```

2. edit `Login/main.cpp`, update `logInfo` with your username and password,
 and `strBuf` with your MAC address (**LOWER CASE**)
```cpp
struct tagLogInfo logInfo{"xiaoming", "123456"};
const char* strBuf = "1a2b3c4d5e6f";
```

3. compile
```shell
make build
```

4. run
```shell
make run
```
