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


bool gva_to_gpa(CPUState *cs, vaddr addr, int size,
                      MMUAccessType access_type, int mmu_idx,
                      bool probe, uintptr_t retaddr, hwaddr *gpa);

#endif
