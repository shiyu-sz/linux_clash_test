#ifndef TRACE_H_
#define TRACE_H_

#include <stdio.h>
void DebugInfo(FILE *out, const void *ip);
void __attribute__((noinline)) PrintStackTrace(FILE *out, int skip);
void FuncC(void);
void FuncB(void);
void FuncA(void);
#endif