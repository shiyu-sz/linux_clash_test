#ifndef TRACE_H_
#define TRACE_H_

#include <stdio.h>
void DebugInfo(FILE *out, const void *ip);
void PrintStackTrace(FILE *out, int skip);

#endif