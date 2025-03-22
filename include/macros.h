#ifndef _MACROS_H
#define _MACROS_H

#define ARRAYCOUNT(a) (sizeof(a) / sizeof(a[0]))
#define OFFSETOF(type, field) ((size_t)&(((type*)0)->field))

#endif
