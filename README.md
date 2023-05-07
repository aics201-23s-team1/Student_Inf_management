# Build MacOS

gcc -o -Wl,-L/usr/local/lib,-I/usr/local/include/json-c -ljson-c -o main main.c