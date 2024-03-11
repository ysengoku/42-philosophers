# Philosophers
Program to solve the famous dining pholosophers problem with thread and mutex.

## Authorized functions
### gettimeofday()
```c
#include <sys/time.h>
int gettimeofday(struct timeval *tv, struct timezone *tz);
```
```c
// The tv argument is a struct timeval.

struct timeval
{
  time_t      tv_sec;     /* seconds */
  suseconds_t tv_usec;    /* microseconds */
};

// time_t: Used for time in seconds. According to POSIX, it is an integer type.
// suseconds_t: Used for time in microseconds. It is a signed integer type capable of storing values at least in the range [-1, 1000000].

// We won't use tz(timezone) in this program, so we set it NULL.
```
Example:  
```c
#include <sys/time.h>
#include <stdio.h>

int main(void)
{
    struct timeval  now;
    gettimeofday(&now, NULL);
    printf("Now = %ld seconds and %ld microseconds since the Unix epoch.", now.tv_sec, now.tv_usec);
    return (0);
}

// Output example
// Now = 1710149149 seconds and 849429 microseconds since the Unix epoch.
// * Unix epoch: 00:00:00, January 1, 1970
```

### usleep()
```c
#include <unistd.h>
int usleep(useconds_t usec);

// useconds_t: Used for time in microseconds. It is an unsigned integer type capable of storing values at least in the range [0, 1000000].
```
The  usleep() function suspends execution of the calling thread for (at least) usec microseconds.  
The sleep may be lengthened slightly by any system activity or by the time spent processing the call or by the granularity of system timers.  
*cf. [man usleep(3)](https://man7.org/linux/man-pages/man3/usleep.3.html)*

Example:
```c
#include <stdio.h>
#include <unistd.h>

int main(void)
{
  printf("Sleep in...\n");
  usleep(4200000);
  printf("Awake.\n");
  return (0);
}
```

 
