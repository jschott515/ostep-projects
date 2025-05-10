# Summary of Changes

### `src/syscall.h`
Added define for new syscall.
```c
#define SYS_getreadcount 22
```

### `src/syscall.c`
Added new syscall to list of syscalls.
```c
static int (*syscalls[])(void) = {
...
[SYS_getreadcount] sys_getreadcount,
};
```

### `src/user.h`
Added user stub for the syscall.
```c
int getreadcount(void);
```

### `src/usys.S`
Wrapped user stub with `SYSCALL` macro.
```c
SYSCALL(getreadcount)
```

### `src/sysfile.c`
Created static global integer to track the number of times `read()` is called.
Modifed `sys_read()` to increment `readcount`.
Implemented syscall `sys_getreadcount()` to return the value of `readcount`.
```c
static int readcount = 0;

int
sys_read(void)
{
...
    readcount++;
...
}

int
sys_getreadcount(void)
{
  return readcount;
}
```