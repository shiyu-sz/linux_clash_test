#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_stacktrace() {
    void *array[10];
    size_t size;
    char **strings;
    size_t i;

    size = backtrace(array, 10);
    strings = backtrace_symbols(array, size);

    // 使用 backtrace_symbols_fd 直接输出到标准错误
    // backtrace_symbols_fd(array, size, STDERR_FILENO);

    printf("Obtained %zd stack frames.\n", size);

    char buf[64] = {0};
    sprintf(buf, "cat /proc/%d/maps", getpid());
    system((const char*)buf);

    for (i = 0; i < size; i++) {
        printf("%s\n", strings[i]);

        // 提取地址部分
        // char *begin = strchr(strings[i], '[');
        // char *end = strchr(strings[i], ']');
        // if (begin && end) {
        //     *end = '\0';
        //     char cmd[256];
        //     snprintf(cmd, sizeof(cmd), "addr2line -e /proc/%d/exe %s", getpid(), begin+1);
        //     system(cmd);
        // }
    }

    free(strings);
}

void foo() {
    print_stacktrace();
}

void bar() {
    foo();
}

int main() {
    bar();
    return 0;
}