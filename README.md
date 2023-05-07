# Environment

Json-c : json-c[https://github.com/json-c/json-c]

# Build MacOS

gcc -o -Wl,-L/usr/local/lib,-I/usr/local/include/json-c -ljson-c -o main main.c