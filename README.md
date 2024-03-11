# Philosphers
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

