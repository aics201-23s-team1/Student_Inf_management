# Environment

Json-c : [json-c](https://github.com/json-c/json-c)

OS

1. Linux ✅
2. Macos ✅
3. Windows ❓


# Build MacOS

only GCC Compile
```
gcc -o -Wl,-L/usr/local/lib,-I/usr/local/include/json-c -ljson-c -o main main.c
```

