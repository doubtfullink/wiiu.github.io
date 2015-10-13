#ifndef COMMON_H
#define	COMMON_H

/* DATA_ADDRESS : address where logs and flags start */
#define DATA_ADDR               ((void *)0x011e2900)
#define DATA_INDEX_ADDR         (DATA_ADDR - 0x4)   // saves the current log address
#define LI_SETUP_ACTIVE_ADDR    (DATA_ADDR - 0x8)   // saves if we are in the rpx setup
#define LI_ALLOC_ACTIVE_ADDR    (DATA_ADDR - 0xC)   // are-we in an allocation section
#define BOUNCE_FLAG_ADDR        (DATA_ADDR - 0x10)  // bounce flag
#define IS_ACTIVE_ADDR          (DATA_ADDR - 0x14)  // is dump active
#define RPL_FOUND_ADDR          (DATA_ADDR - 0x18)  // have we found a rpl ?

/* RPX Address : where the rpx is copied or retrieve, depends if we dump or replace */
/* Note : from phys 0x30789C5D to 0x31E20000, memory seems empty (space reserved for root.rpx) which let us approximatly 22.5mB of memory free to put the rpx and additional rpls */
#define MEM_BASE                ((void*)0xC0800000)
#define MEM_SIZE                ((void*)(MEM_BASE - 0x04))
#define MEM_OFFSET              ((void*)(MEM_BASE - 0x08))
#define MEM_PART                ((void*)(MEM_BASE - 0x0C))
#define RPX_NAME                ((void*)(MEM_BASE - 0x10))
#define RPX_NAME_PENDING        ((void*)(MEM_BASE - 0x14))

#define MEM_LIMIT               (0x31E20000 - 0x30800000)

// Note : RPX_RPL_ARRAY contains an array of multiple rpl/rpl structures:
// The first entry is always the one referencing the rpx
#define RPX_RPL_ARRAY           ((void*)0xC07A0000)
#define RPX_RPL_CUR_ENTRY       ((void*)(RPX_RPL_ARRAY - 0x04))
#define RPX_ENTRY_COUNT         ((void*)(RPX_RPL_ARRAY - 0x08))
#define RPL_ENTRY_COUNT         ((void*)(RPX_RPL_ARRAY - 0x0C))

// An rpx_rpl_struct contains :
// - address of rpx/rpl in memory (int)
// - size of rpx/rpl (int)
// - name of the rpl (64 char)

/* RPX Name : from which app/game, our rpx is launched */
#define RPX_MIIMAKER_NAME       0x66666C5F  // 0xEFE00000 contains the rpx name, 0x66666C5F => ffl_ (for mii maker : ffl_app.rpx)
#define RPX_HOME_NAME           0x6D656E2E  // => home rpx ("men.rpx")

/* Union for rpx name */
typedef union uRpxName {
    int name_full;
    char name[4];
} uRpxName;

/* Struct used to organize rpx/rpl data in memory */
#define RPX_RPL_NAME_SIZE 64
typedef struct s_rpx_rpl
{
    int  address;
    int  size;
    int  offset;
    char name[RPX_RPL_NAME_SIZE]; // TODO: maybe set the exact same size than dir_entry->name
} s_rpx_rpl;

#endif	/* COMMON_H */

