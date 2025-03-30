#define UNW_LOCAL_ONLY
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <libunwind.h>
#include <elfutils/libdwfl.h>

void DebugInfo(FILE *out, const void *ip) {
    char *debuginfo_path = NULL;
    Dwfl_Callbacks callbacks;
    callbacks.find_elf = dwfl_linux_proc_find_elf;
    callbacks.find_debuginfo = dwfl_standard_find_debuginfo;
    callbacks.debuginfo_path = &debuginfo_path;
    Dwfl *dwfl = dwfl_begin(&callbacks);
    assert(dwfl != NULL);

    assert(dwfl_linux_proc_report(dwfl, getpid()) == 0);
    assert(dwfl_report_end (dwfl, NULL, NULL) == 0);

    Dwarf_Addr addr = (uintptr_t)ip;
    Dwfl_Module *module = dwfl_addrmodule(dwfl, addr);
    const char *function_name = dwfl_module_addrname(module, addr);
    // 调用c++file命令还原函数名称
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "c++filt %s", function_name);
    FILE *fp = popen(cmd, "r");
    char result[1024];
    fgets(result, sizeof(result), fp);
    result[strlen(result) - 1] = '\0';
    fprintf(out, "%s(", result);
    pclose(fp);

    Dwfl_Line *line = dwfl_getsrc(dwfl, addr);
    if (line != NULL) {
        int nline;
        Dwarf_Addr addr;
        const char *filename = dwfl_lineinfo(line, &addr, &nline, NULL, NULL, NULL);
        fprintf(out, "%s:%d", strrchr(filename, '/') + 1, nline);
    } else {
        fprintf(out, "%p", ip);
    }
}

void PrintStackTrace(FILE *out, int skip) {
    unw_context_t uc;
    unw_getcontext(&uc);
    unw_cursor_t cursor;
    unw_init_local(&cursor, &uc);

    while (unw_step(&cursor) > 0) {
        unw_word_t ip;
        unw_get_reg(&cursor, UNW_REG_IP, &ip);
        unw_word_t offset;
        char name[32];
        assert(unw_get_proc_name(&cursor, name, sizeof(name), &offset) == 0);

        printf("(%s+0x%lx) ", name, (long)offset);

        if (skip <= 0) {
            fprintf(out, "\tat ");
            DebugInfo(out, (void*)(ip - 4));
            fprintf(out, ")\n");
        }

        if (strcmp(name, "main") == 0) {
            break;
        }
        skip--;
    }
}
