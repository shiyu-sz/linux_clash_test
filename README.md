### 测试linux应用crash问题  

#### execinfo  
使用backtrace和backtrace_symbols获得调用栈  

#### libbacktrace  
apt-get install libbacktrace-dev  

#### libunwind_libdwfl  
使用libunwind获得调用栈，使用libdwfl定位到代码，C和C++都可以  
apt-get install libunwind-dev  
apt-get install libdw-dev  