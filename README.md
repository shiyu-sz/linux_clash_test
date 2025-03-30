### 测试linux应用crash问题  

#### execinfo  
使用backtrace和backtrace_symbols获得调用栈  
编译程序，保留调试信息：  
gcc -ggdb3 -Wall main.c -o main -rdynamic  
获得函数的首地址：  
readelf -sW ./main | grep foo  
首地址加上偏移定位到代码：  
addr2line -e main "首地址+偏移" -f  

#### libbacktrace  
教程：https://zhuanlan.zhihu.com/p/658352901
apt-get install libbacktrace-dev  
gcc -rdynamic -g -O0 main.c -o main -lbacktrace

#### libunwind_libdwfl  
教程：https://bishuiliuyun.github.io/post/backtrace/
使用libunwind获得调用栈，使用libdwfl定位到代码，C和C++都可以  
apt-get install libunwind-dev  
apt-get install libdw-dev  

#### boost_stacktrace
apt-get install libboost-all-dev  
g++ -ggdb3 -no-pie -fno-pie -rdynamic main.cpp -o main -lboost_system -lboost_filesystem -ldl -DBOOST_STACKTRACE_USE_ADDR2LINE  
