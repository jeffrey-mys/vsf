#ifndef __VSF_LINUX_MMAN_H__
#define __VSF_LINUX_MMAN_H__

#include "shell/sys/linux/vsf_linux_cfg.h"

// for VSF_FILE_ATTR_XXXX
#include "component/fs/vsf_fs_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

#if VSF_LINUX_CFG_WRAPPER == ENABLED
#define mmap                VSF_LINUX_WRAPPER(mmap)
#define munmap              VSF_LINUX_WRAPPER(munmap)
#define mprotect            VSF_LINUX_WRAPPER(mprotect)
#endif

#define PROT_NONE       0
#define PROT_READ       VSF_FILE_ATTR_READ
#define PROT_WRITE      VSF_FILE_ATTR_WRITE
#define PROT_EXEC       VSF_FILE_ATTR_EXECUTE
#define MAP_32BIT       0

#define MAP_FILE        0
#define MAP_SHARED      1
#define MAP_PRIVATE     2
#define MAP_TYPE        0xf
#define MAP_FIXED       0x10
#define MAP_ANONYMOUS   0x20
#define MAP_ANON        MAP_ANONYMOUS

#define MAP_FAILED      ((void *)-1)

#define MS_ASYNC        1
#define MS_SYNC         2
#define MS_INVALIDATE   4

#if VSF_LINUX_APPLET_USE_SYS_MMAP == ENABLED
typedef struct vsf_linux_sys_mmap_vplt_t {
    vsf_vplt_info_t info;
} vsf_linux_sys_mmap_vplt_t;
#   ifndef __VSF_APPLET__
extern __VSF_VPLT_DECORATOR__ vsf_linux_sys_mmap_vplt_t vsf_linux_sys_mmap_vplt;
#   endif
#endif

#if defined(__VSF_APPLET__) && VSF_LINUX_APPLET_USE_SYS_MMAP == ENABLED

#ifndef VSF_LINUX_APPLET_SYS_MMAP_VPLT
#   if VSF_LINUX_USE_APPLET == ENABLED
#       define VSF_LINUX_APPLET_SYS_MMAP_VPLT                                   \
            ((vsf_linux_sys_mmap_vplt_t *)(VSF_LINUX_APPLET_VPLT->sys_mmap))
#   else
#       define VSF_LINUX_APPLET_SYS_MMAP_VPLT                                   \
            ((vsf_linux_sys_mmap_vplt_t *)vsf_vplt((void *)0))
#   endif
#endif

#else       // __VSF_APPLET__ && VSF_LINUX_APPLET_USE_SYS_MMAP

void * mmap(void *addr, size_t len, int prot, int flags, int fildes, off_t off);
int munmap(void *addr, size_t len);
int mprotect(void *addr, size_t len, int prot);
int msync(void *addr, size_t len, int flags);

#endif      // __VSF_APPLET__ && VSF_LINUX_APPLET_USE_SYS_MMAP

static inline int mlock(const void *addr, size_t len) { return 0; }
static inline int mlock2(const void *addr, size_t len, unsigned int flags) { return 0; }
static inline int munlock(const void *addr, size_t len) { return 0; }
static inline int mlockall(int flags) { return 0; }
static inline int munlockall(void) { return 0; }

#ifdef __cplusplus
}
#endif

#endif
