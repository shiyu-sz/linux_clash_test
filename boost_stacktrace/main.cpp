#include <iostream>
#include <boost/stacktrace.hpp>
#include <signal.h>	    /* for signal */

void FuncC(void) {
    int ret = 0x00;
	int *pTemp = NULL;
	
	*pTemp = 0x01;  /* 这将导致一个段错误，致使程序崩溃退出 */
	
	ret = 1 + *pTemp;
}

void FuncB(void) {
    FuncC();
}

void FuncA(void) {
    FuncB();
}

void signal_handler(int signo)
{
    std::cout << "Current stack trace:\n" << boost::stacktrace::stacktrace() << '\n';
 
	signal(signo, SIG_DFL); /* 恢复信号默认处理 */
	raise(signo);           /* 重新发送信号 */
}

int main() {
    signal(SIGSEGV, signal_handler);  /* 为SIGSEGV信号安装新的处理函数 */

    FuncA();

    return 0;
}