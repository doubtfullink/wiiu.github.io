#include "dumpiine.h"

#if VER == 532
    #include "menu532.h"
    #include "loader532.h"

    // Function definitions
    #define memcpy ((void * (*)(void * dest, const void * src, int num))0x1035a6c)
    #define DCFlushRange ((void (*)(const void*, int))0x01023ee8)
    #define _Exit ((void (*)(void))0x0101cd70)
    #define OSEffectiveToPhysical ((void* (*)(const void*))0x0101f510)
    #define OSFatal ((void (*)(char* msg))0x1031368)

    // Install addresses
    #define INSTALL_MENU_ADDR           0x011dd000  // where the menu code is copied in memory
    #define INSTALL_LOADER_ADDR         0x011df000  // where the loader code is copied in memory

#endif

/* Install functions */
static void InstallMenu();
static void InstallLoadiine();

/* main function */
void start() {
    /* Load a good stack */
    asm(
        "lis %r1, 0x1ab5 ;"
        "ori %r1, %r1, 0xd138 ;"
    );

    /* Check if kernel exploit is well installed */
    if (OSEffectiveToPhysical((void *)0xa0000000) != (void *)0x10000000)
    {
        if (OSEffectiveToPhysical((void *)0xa0000000) == (void *)0x31000000)
            OSFatal("Not the good kexploit");
        else
            OSFatal("No kexploit");
    }
    else
    {
        /* ****************************************************************** */
        /*                        Dumpiine installation                       */
        /* ****************************************************************** */

        InstallMenu();
        InstallLoadiine();
    }

quit:
    _Exit();
}

/* ****************************************************************** */
/*                              INSTALL MENU                          */
/* ****************************************************************** */
static void InstallMenu()
{
    /* Install codehandler */
    memcpy((void*)0xC1000000 + INSTALL_MENU_ADDR, menu_text_bin, menu_text_bin_len);

    /* Patch coreinit - on 5.3.2 coreinit.rpl starts at 0x101c400 */
    int jump_length = INSTALL_MENU_ADDR - 0x0101c55c;                       // => jump to (101C55C + 1C0AA4) = 11DD000 which is the codehandler
    *((uint32_t *)(0xC1000000 + 0x0101c55c)) = 0x48000001 | jump_length;    // 0x481c0aa5 => bl 0x1C0AA4  => write at 0x15C in coreinit file => end of the coreinit_start function
}

/* ****************************************************************** */
/*                              INSTALL LOADER                        */
/* Copy code and replace loader instruction by call to our functions  */
/* ****************************************************************** */
static void InstallLoadiine()
{
    /* Patch for GetNextBounce function (loader) */
    /* we dont want instructions to use r9/r11 registers, as it is modified by gcc prologue/epilogue when calling our functions */
    *((uint32_t *)(0xC1000000 + 0x0100b720)) = 0x3c800040; // lis r11, 0x40      (0x3d600040) => lis r4, 0x40       (0x3c800040)
    *((uint32_t *)(0xC1000000 + 0x0100b718)) = 0x7ca95214; // add r9, r9, r10    (0x7d295214) => add r5, r9, r10    (0x7ca95214)
//  *((uint32_t *)(0xC1000000 + 0x0100b728)) = 0x7c0a2040; // cmplw r10, r11     (0x7c0a5840) => cmplw r10, r4      (0x7c0a2040) // function call
    *((uint32_t *)(0xC1000000 + 0x0100b738)) = 0x90be0090; // stw r9, 0x90(r30)  (0x913e0090) => stw r5, 0x90(r30)  (0x90be0090)

    *((uint32_t *)(0xC1000000 + 0x0100b75c)) = 0x38800001; // li r11, 1          (0x39600001) => li r4, 1           (0x38800001)
    *((uint32_t *)(0xC1000000 + 0x0100b764)) = 0x909e0078; // stw r11, 0x78(r30) (0x917e0078) => stw r4, 0x78(r30)  (0x909e0078)
    *((uint32_t *)(0xC1000000 + 0x0100b770)) = 0x3c800040; // lis r11, 0x40      (0x3d600040) => lis r4, 0x40       (0x3c800040)
    *((uint32_t *)(0xC1000000 + 0x0100b778)) = 0x7ca95214; // add r9, r9, r10    (0x7d295214) => add r5, r9, r10    (0x7ca95214)
//  *((uint32_t *)(0xC1000000 + 0x0100b780)) = 0x7c0a2040; // cmplw r10, r11     (0x7c0a5840) => cmplw r10, r4      (0x7c0a2040) // function call
    *((uint32_t *)(0xC1000000 + 0x0100b794)) = 0x90be0090; // stw r9, 0x90(r30)  (0x913e0090) => stw r5, 0x90(r30)  (0x90be0090)
    
    /* Copy loader code in memory */
    /* - virtual address 0xA0000000 is at physical address 0x10000000 (with read/write access) */
    /* - virtual address range 0x01xxxxxx starts at physical address 0x32000000 */
    /* - we want to copy the code at INSTALL_ADDR (0x011de000), this memory range is the for cafeOS app and libraries, but is write protected */
    /* - in order to have the rights to write into memory in this address range we need to use the 0xA0000000 virtual address range */
    /* - so start virtual address is : (0xA0000000 + (0x32000000 - 0x10000000 + 0x01000000)) = 0xC1000000 */
    memcpy((void*)(INSTALL_LOADER_ADDR + 0xC1000000), loader_text_bin, loader_text_bin_len);

    /* Copy original loader instructions in memory for when we want to restore the loader at his original state */
    // TODO: copy original instructions in order to restore them later to have a clean loader state
    // we'll have to hook the "quit" function to restore the original instructions

    /* Get our functions */
    struct magic_t
    {
        const void* func; // our replacement function which is called
        const void* call; // address where to place the jump to our function
        uint        orig_instr;
    } *magic = (struct magic_t *)loader_magic_bin;
    int magic_len = sizeof(loader_magic_bin) / sizeof(struct magic_t);

    /* Replace loader instructions */
    /* Loop to replace instructions in loader code by a "bl"(jump) instruction to our replacement function */
    int i;
    for (i = 0; i < magic_len; i ++)
    {
        int func_addr  = (int)magic[i].func;
        int call_addr  = (int)magic[i].call;
        int orig_instr = (int)magic[i].orig_instr;

        // Install function hook
        int jump_addr = func_addr - call_addr; // Compute jump length to jump from current instruction address to our function address
        *((uint32_t *)(0xC1000000 + call_addr)) = 0x48000001 | jump_addr; // Replace the instruction in the loader by the jump to our function
    }
}
