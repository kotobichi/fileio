# File IO

I often just need to read and parse a lot data off of files within the same working directory, specially when just prototyping something, I just want something real quick and fast, and so I often just copy-paste functions around projects, but now I decided to just make it as a header file. Is it better? idk, probably not, maybe if had more utility functions it would make much more sense.

## Use

``` c
#define FIO_IMPLEMENTATION // <-- define once only
#include "fileio.h"
```

``` c
char *content;
size_t length;
    
FIO_read("your_mom.obj", &content, &length);
```

``` c
printf("File size: %zu bytes\n", length);
printf("Content:\n%s\n", content);
```

output:
```
File size: 4294967296 bytes
Content: is thick
```

remember to free mem:
``` c 
free(content); 
```

here's what `FIO_read()` can return:
``` c
typedef enum {
    FIO_SUCCESS,
    FIO_INVALID_ARGS,
    FIO_FILE_NOT_FOUND,
    FIO_EMPTY_FILE,
    FIO_ALLOCATION_FAILED,
    FIO_READ_FAILED,
} FIO_status_e;
```

handle errors properly:
``` c
FIO_status_e status = FIO_read("your_mom.obj", &content, &length);
switch (status) {
    case FIO_INVALID_ARGS:   /** ... */ break;
    case FIO_EMPTY_FILE:     /** ... */ break;
    // ...
}
```