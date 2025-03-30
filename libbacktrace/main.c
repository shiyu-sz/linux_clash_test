#include <stdio.h>
#include <signal.h>	    /* for signal */
#include <backtrace.h>
#include <backtrace-supported.h>

struct backtrace_state *state = NULL;

struct bt_ctx {
  struct backtrace_state *state;
  int error;
};

static void error_callback(void *data, const char *msg, int errnum)
{
  struct bt_ctx *ctx = (struct bt_ctx *)data;
  fprintf(stderr, "ERROR: %s (%d)", msg, errnum);
  ctx->error = 1;
}

static void syminfo_callback (void *data, uintptr_t pc, const char *symname, uintptr_t symval, uintptr_t symsize)
{
  //struct bt_ctx *ctx = data;
  if (symname) {
    printf("%lx %s ??:0\n", (unsigned long)pc, symname);
  } else {
    printf("%lx ?? ??:0\n", (unsigned long)pc);
  }
}

static int full_callback(void *data, uintptr_t pc, const char *filename, int lineno, const char *function)
{
  struct bt_ctx *ctx = (struct bt_ctx *)data;
  if (function) {
    printf("%lx %s %s:%d\n", (unsigned long)pc, function, filename?filename:"??", lineno);
  } else {
    backtrace_syminfo (ctx->state, pc, syminfo_callback, error_callback, data);
  }
  return 0;
}

static int simple_callback(void *data, uintptr_t pc)
{
  struct bt_ctx *ctx = (struct bt_ctx *)data;
  backtrace_pcinfo(ctx->state, pc, full_callback, error_callback, data);
  return 0;
}

static inline void bt(struct backtrace_state *state)
{
  struct bt_ctx ctx = {state, 0};
//   backtrace_print(state, 0, stdout);
  backtrace_simple(state, 0, simple_callback, error_callback, &ctx);
}

void signal_handler(int signo)
{
    bt(state);
 
	signal(signo, SIG_DFL); /* 恢复信号默认处理 */
	raise(signo);           /* 重新发送信号 */
}

int fun2(int num)
{
	int ret = 0x00;
	int *pTemp = NULL;
	
	*pTemp = 0x01;  /* 这将导致一个段错误，致使程序崩溃退出 */
	
	ret = num + *pTemp;
	
	return ret;
}
 
int fun1(int num)
{
	int ret = 0x00;
 
	ret = fun2(num);
	
	return ret;
}

int main(int argc, char *argv[])
{
    signal(SIGSEGV, signal_handler);  /* 为SIGSEGV信号安装新的处理函数 */

    state = backtrace_create_state (argv[0], BACKTRACE_SUPPORTS_THREADS, error_callback, NULL);

	int sum = fun1(sum);
	
	printf(" sum = %d \n", sum);

    return 0;
}