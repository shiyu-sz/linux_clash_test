#include <libunwind.h>
#include <stdio.h>

void print_stacktrace() {
    
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
