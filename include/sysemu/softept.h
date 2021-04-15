#ifndef QEMU_SOFTEPT_H
#define QEMU_SOFTEPT_H

#include "qemu/osdep.h"
#include "qemu/main-loop.h"
#include "cpu.h"
#include "exec/exec-all.h"
#include "exec/memory.h"
#include "exec/address-spaces.h"
#include "exec/cpu_ldst.h"
#include "exec/cputlb.h"
#include "exec/memory-internal.h"
#include "exec/ram_addr.h"
#include "qemu/queue.h"
#include "exec/tb-hash.h"
#include "translate-all.h"
#include "qemu/bitmap.h"
#include "qemu/error-report.h"
#include "qemu/qemu-print.h"
#include "qemu/timer.h"
#include "exec/log.h"
#include "sysemu/cpus.h"
#include "sysemu/tcg.h"

#include <sys/ioctl.h>

struct HelperElem{
    CPUArchState *env;
    target_ulong addr;
    TCGMemOpIdx oi;
    uintptr_t retaddr;
    MemOp op;
    bool code_read;
    bool is_load;
    uint64_t write_val;
};

struct SofteptEntry{
    union{
        struct{
            hwaddr gpa;
            uintptr_t hva;
        }set_entry;
        struct{
            hwaddr *list;
            int size;
        }flush_entry;
    };
};
struct SofteptState{
    int fd;
    int pid;

    //here use vector to avoid the cost of copy_to_kernel
    //if we use list, the cost will be quite high
    struct SofteptEntryVector{
        hwaddr *gpa_list;
        int capacity;
        int size;
    }softept_entry_vector;
};

#define SOFTEPTIO 0xAF

#define SOFTEPT_INIT _IOWR(SOFTEPTIO, 0x1, int)
#define SOFTEPT_SET_ENTRY _IOWR(SOFTEPTIO, 0x2, struct SofteptEntry)
#define SOFTEPT_FLUSH_ENTRY _IOWR(SOFTEPTIO, 0x3, struct SofteptEntry)

void softept_entry_list_insert(hwaddr elem);

int softept_entry_flush_all(void);

int softept_ioctl(int type, ...);

int softept_init(void);

bool gva_to_gpa(CPUState *cs, vaddr addr, int size,
                      MMUAccessType access_type, int mmu_idx,
                      bool probe, uintptr_t retaddr, hwaddr *gpa);

#endif
