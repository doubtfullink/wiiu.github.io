#include "loader.h"
#include "../common/common.h"

/* Checks if the current rpl is an rpl from CafeOS libraries */
/* Dirrrrrrrrrtyyy tree check */

static int IsAdditionalRPL(char* rpl)
{
    // avm
    if (rpl[0] == 'a')
    {
        if (rpl[1] == 'v' && rpl[2] == 'm' && rpl[3] == '\0') return 0;
    }
    // dc / dmae / drmapp
    else if (rpl[0] == 'd')
    {
        if (rpl[1] == 'c' && rpl[2] == '\0') return 0;
        if (rpl[1] == 'm' && rpl[2] == 'a' && rpl[3] == 'a' && rpl[4] == '\0') return 0;
        if (rpl[1] == 'r' && rpl[2] == 'm' && rpl[3] == 'a' && rpl[4] == 'p' && rpl[5] == 'p' && rpl[6] == '\0') return 0;
    }
    // erreula
    else if (rpl[0] == 'e')
    {
        if (rpl[1] == 'r' && rpl[2] == 'r' && rpl[3] == 'e' && rpl[4] == 'u' && rpl[5] == 'l' && rpl[6] == 'a' && rpl[7] == '\0') return 0;
    }
    // gx2
    else if (rpl[0] == 'g')
    {
        if (rpl[1] == 'x' && rpl[2] == '2' && rpl[3] == '\0') return 0;
    }
    // h264
    else if (rpl[0] == 'h')
    {
        if (rpl[1] == '2' && rpl[2] == '6' && rpl[3] == '4' && rpl[4] == '\0') return 0;
    }
    // lzma920
    else if (rpl[0] == 'l')
    {
        if (rpl[1] == 'z' && rpl[2] == 'm' && rpl[3] == 'a' && rpl[4] == '9' && rpl[5] == '2' && rpl[6] == '0' && rpl[7] == '\0') return 0;
    }
    // mic
    else if (rpl[0] == 'm')
    {
        if (rpl[1] == 'i' && rpl[2] == 'c' && rpl[3] == '\0') return 0;
    }
    // nfc / nio_prof / nlibcurl / nlibnss / nlibnss2 / nn_ac / nn_acp / nn_act / nn_aoc / nn_boss / nn_ccr / nn_cmpt
    // nn_ec / nn_fp / nn_hai / nn_hpad / nn_idbe / nn_ndm / nn_nets2 / nn_nfp / nn_nim / nn_olv / nn_pdm / nn_save
    // nn_sl / nn_spm / nn_temp / nn_uds / nn_vctl / nsysccr / nsyshid / nsyskbd / nsysnet / nsysuhs / nsysuvd / ntag
    else if (rpl[0] == 'n')
    {
        // nfc
        if (rpl[1] == 'f')
        {
            if (rpl[2] == 'c' && rpl[3] == '\0') return 0;
        }
        // nio_prof
        else if (rpl[1] == 'i')
        {
            if (rpl[2] == 'o' && rpl[3] == '_' && rpl[4] == 'p' && rpl[5] == 'r' && rpl[6] == 'o' && rpl[7] == 'f' && rpl[8] == '\0') return 0;
        }
        // nlibcurl / nlibnss / nlibnss2
        else if (rpl[1] == 'l')
        {
            if (rpl[2] == 'i' && rpl[3] == 'b')
            {
                if (rpl[4] == 'c' && rpl[5] == 'u' && rpl[6] == 'r' && rpl[7] == 'l' && rpl[8] == '\0') return 0;
                if (rpl[4] == 'n' && rpl[5] == 's' && rpl[6] == 's' && rpl[7] == '\0') return 0;
                if (rpl[4] == 'n' && rpl[5] == 's' && rpl[6] == 's' && rpl[7] == '2' && rpl[8] == '\0') return 0;
            }
        }
        // nn_*
        else if (rpl[1] == 'n')
        {
            if (rpl[2] == '_')
            {
                // nn_ac / nn_acp / nn_act / nn_aoc
                if (rpl[3] == 'a')
                {
                    if (rpl[4] == 'c' && rpl[5] == '\0') return 0;
                    if (rpl[4] == 'c' && rpl[5] == 'p' && rpl[6] == '\0') return 0;
                    if (rpl[4] == 'c' && rpl[5] == 't' && rpl[6] == '\0') return 0;
                    if (rpl[4] == 'o' && rpl[5] == 'c' && rpl[6] == '\0') return 0;
                }
                // nn_boss
                else if (rpl[3] == 'b')
                {
                    if (rpl[4] == 'o' && rpl[5] == 's' && rpl[6] == 's' && rpl[7] == '\0') return 0;
                }
                // nn_ccr / nn_cmpt
                else if (rpl[3] == 'c')
                {
                    if (rpl[4] == 'c' && rpl[5] == 'r' && rpl[6] == '\0') return 0;
                    if (rpl[4] == 'm' && rpl[5] == 'p' && rpl[6] == 't' && rpl[7] == '\0') return 0;
                }
                // nn_ec
                else if (rpl[3] == 'e')
                {
                    if (rpl[4] == 'c' && rpl[5] == '\0') return 0;
                }
                // nn_fp
                else if (rpl[3] == 'f')
                {
                    if (rpl[4] == 'p' && rpl[5] == '\0') return 0;
                }
                // nn_hai / nn_hpad
                else if (rpl[3] == 'h')
                {
                    if (rpl[4] == 'a' && rpl[5] == 'i' && rpl[6] == '\0') return 0;
                    if (rpl[4] == 'p' && rpl[5] == 'a' && rpl[6] == 'd' && rpl[7] == '\0') return 0;
                }
                // nn_idbe
                else if (rpl[3] == 'i')
                {
                    if (rpl[4] == 'd' && rpl[5] == 'b' && rpl[6] == 'e' && rpl[7] == '\0') return 0;
                }
                // nn_ndm / nn_nets2 / nn_nfp / nn_nim
                else if (rpl[3] == 'n')
                {
                    if (rpl[4] == 'd' && rpl[5] == 'm' && rpl[6] == '\0') return 0;
                    if (rpl[4] == 'e' && rpl[5] == 't' && rpl[6] == 's' && rpl[7] == '2' && rpl[8] == '\0') return 0;
                    if (rpl[4] == 'f' && rpl[5] == 'p' && rpl[6] == '\0') return 0;
                    if (rpl[4] == 'i' && rpl[5] == 'm' && rpl[6] == '\0') return 0;
                }
                // nn_olv
                else if (rpl[3] == 'o')
                {
                    if (rpl[4] == 'l' && rpl[5] == 'v' && rpl[6] == '\0') return 0;
                }
                // nn_pdm
                else if (rpl[3] == 'p')
                {
                    if (rpl[4] == 'd' && rpl[5] == 'm' && rpl[6] == '\0') return 0;
                }
                // nn_save / nn_sl / nn_spm
                else if (rpl[3] == 's')
                {
                    if (rpl[4] == 'a' && rpl[5] == 'v' && rpl[6] == 'e' && rpl[7] == '\0') return 0;
                    if (rpl[4] == 'l' && rpl[5] == '\0') return 0;
                    if (rpl[4] == 'p' && rpl[5] == 'm' && rpl[6] == '\0') return 0;
                }
                // nn_temp
                else if (rpl[3] == 't')
                {
                    if (rpl[4] == 'e' && rpl[5] == 'm' && rpl[6] == 'p' && rpl[7] == '\0') return 0;
                }
                // nn_uds
                else if (rpl[3] == 'u')
                {
                    if (rpl[4] == 'd' && rpl[5] == 's' && rpl[6] == '\0') return 0;
                }
                // nn_vctl
                else if (rpl[3] == 'v')
                {
                    if (rpl[4] == 'c' && rpl[5] == 't' && rpl[6] == 'l' && rpl[7] == '\0') return 0;
                }
            }
        }
        // nsysccr / nsyshid / nsyskbd / nsysnet / nsysuhs / nsysuvd
        else if (rpl[1] == 's')
        {
            if (rpl[2] == 'y' && rpl[3] == 's')
            {
                // nsysccr
                if (rpl[4] == 'c')
                {
                    if (rpl[5] == 'c' && rpl[6] == 'r' && rpl[7] == '\0') return 0;
                }
                // nsyshid
                else if (rpl[4] == 'h')
                {
                    if (rpl[5] == 'i' && rpl[6] == 'd' && rpl[7] == '\0') return 0;
                }
                // nsyskbd
                else if (rpl[4] == 'k')
                {
                    if (rpl[5] == 'b' && rpl[6] == 'd' && rpl[7] == '\0') return 0;
                }
                // nsysnet
                else if (rpl[4] == 'n')
                {
                    if (rpl[5] == 'e' && rpl[6] == 't' && rpl[7] == '\0') return 0;
                }
                // nsysuhs / nsysuvd
                else if (rpl[4] == 'u')
                {
                    if (rpl[5] == 'h' && rpl[6] == 's' && rpl[7] == '\0') return 0;
                    if (rpl[5] == 'v' && rpl[6] == 'd' && rpl[7] == '\0') return 0;
                }
            }
        }
        // ntag
        else if (rpl[1] == 't')
        {
            if (rpl[2] == 'a' && rpl[3] == 'g' && rpl[4] == '\0') return 0;
        }
    }
    // padscore / proc_ui
    else if (rpl[0] == 'p')
    {
        if (rpl[1] == 'a' && rpl[2] == 'd' && rpl[3] == 's' && rpl[4] == 'c' && rpl[5] == 'o' && rpl[6] == 'r' && rpl[7] == 'e' && rpl[8] == '\0') return 0;
        if (rpl[1] == 'r' && rpl[2] == 'o' && rpl[3] == 'c' && rpl[4] == '_' && rpl[5] == 'u' && rpl[6] == 'i' && rpl[7] == '\0') return 0;
    }
    // snd_core / snd_user / sndcore2 / snduser2 / swkbd / sysapp
    else if (rpl[0] == 's')
    {
        // snd_core / snd_user / sndcore2 / snduser2
        if (rpl[1] == 'n' && rpl[2] == 'd')
        {
            if (rpl[3] == '_' && rpl[4] == 'c' && rpl[5] == 'o' && rpl[6] == 'r' && rpl[7] == 'e' && rpl[8] == '\0') return 0;
            if (rpl[3] == '_' && rpl[4] == 'u' && rpl[5] == 's' && rpl[6] == 'e' && rpl[7] == 'r' && rpl[8] == '\0') return 0;
            if (rpl[3] == 'c' && rpl[4] == 'o' && rpl[5] == 'r' && rpl[6] == 'e' && rpl[7] == '2' && rpl[8] == '\0') return 0;
            if (rpl[3] == 'u' && rpl[4] == 's' && rpl[5] == 'e' && rpl[6] == 'r' && rpl[7] == '2' && rpl[8] == '\0') return 0;

        }
        // swkbd / sysapp
        else
        {
           if (rpl[1] == 'w' && rpl[2] == 'k' && rpl[3] == 'b' && rpl[4] == 'd' && rpl[5] == '\0') return 0;
           if (rpl[1] == 'y' && rpl[2] == 's' && rpl[3] == 'a' && rpl[4] == 'p' && rpl[5] == 'p' && rpl[6] == '\0') return 0;
        }
    }
    // tcl / tve
    else if (rpl[0] == 't')
    {
        if (rpl[1] == 'c' && rpl[2] == 'l' && rpl[3] == '\0') return 0;
        if (rpl[1] == 'v' && rpl[2] == 'e' && rpl[3] == '\0') return 0;
    }
    // uac / uac_rpl / usb_mic / uvc / uvd
    else if (rpl[0] == 'u')
    {
        if (rpl[1] == 'a' && rpl[2] == 'c' && rpl[3] == '\0') return 0;
        if (rpl[1] == 'a' && rpl[2] == 'c' && rpl[3] == '_' && rpl[4] == 'r' && rpl[5] == 'p' && rpl[6] == 'l' && rpl[7] == '\0') return 0;
        if (rpl[1] == 's' && rpl[2] == 'b' && rpl[3] == '_' && rpl[4] == 'm' && rpl[5] == 'i' && rpl[6] == 'c' && rpl[7] == '\0') return 0;
        if (rpl[1] == 'v' && rpl[2] == 'c' && rpl[3] == '\0') return 0;
        if (rpl[1] == 'v' && rpl[2] == 'd' && rpl[3] == '\0') return 0;
    }
    // vpad / vpadbase
    else if (rpl[0] == 'v')
    {
        if (rpl[1] == 'p' && rpl[2] == 'a' && rpl[3] == 'd' && rpl[4] == '\0') return 0;
        if (rpl[1] == 'p' && rpl[2] == 'a' && rpl[3] == 'd' && rpl[4] == 'b' && rpl[5] == 'a' && rpl[6] == 's' && rpl[7] == 'e' && rpl[8] == '\0') return 0;
    }
    // zlib125
    else if (rpl[0] == 'z')
    {
        if (rpl[1] == 'l' && rpl[2] == 'i' && rpl[3] == 'b' && rpl[4] == '1' && rpl[5] == '2' && rpl[6] == '5' && rpl[7] == '\0') return 0;
    }

    return 1;
}



/* LOADER_Start ****************************************************************
 * - instruction address = 0x01003e60
 * - original instruction = 0x5586103a : "slwi r6, r12, 2"
 * - entry point of the loader
 */
void LOADER_Start(void)
{
    // Save registers
    int r4, r6, r12;
    asm("mr %0, 4\n"
        "mr %1, 6\n"
        "mr %2, 12\n"
        :"=r"(r4), "=r"(r6), "=r"(r12)
        :
        :"memory", "ctr", "lr", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"
    );

    if (((*(int*)0xEFE00000) != RPX_MIIMAKER_NAME) && ((*(int*)0xEFE00000) != RPX_HOME_NAME))
    {
        // Reset flags
        *(int *)(DATA_INDEX_ADDR) = 0;          // Reset log index
        *(int *)(IS_ACTIVE_ADDR) = 1;           // Dump ON for .rpx
        *(int *)(MEM_SIZE) = 0;                 // Reset memory size
        *(int *)(MEM_OFFSET) = 0;               // Reset memory offset
        *(int *)(MEM_PART) = 0;                 // Reset memory part
        *(int *)(RPL_FOUND_ADDR) = 0;           // Reset found rpl

        // Reset rpx/rpl entry count
        *(int *)(RPX_RPL_CUR_ENTRY) = 0;        // Cur entry
        *(int *)(RPX_ENTRY_COUNT) = 0;          // Entry 0
        *(int *)(RPL_ENTRY_COUNT) = 0;          // Entry 1 + rpl number

        // Reset first rpx entry
        s_rpx_rpl *rpx_struct = (s_rpx_rpl*)(RPX_RPL_ARRAY);
        rpx_struct->address = 0;
        rpx_struct->size = 0;
        rpx_struct->offset = 0;
        for (int i = 0; i < RPX_RPL_NAME_SIZE; i++)
            rpx_struct->name[i] = '\0';
    }

    // return properly
    asm("mr 4, %0\n"
        "mr 6, %1\n"
        "mr 12, %2\n"
        :
        :"r"(r4), "r"(r6), "r"(r12)
        :"memory", "ctr", "lr", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"
    );
    asm("slwi 6, 12, 2\n");
}

/* LOADER_Entry ****************************************************************
 * - instruction address = 0x01002938
 * - original instruction = 0x835e0000 : "lwz r26, 0(r30)"
 */
void LOADER_Entry(void)
{
    // Save registers
    int r30, r3;
    asm("mr %0, 30\n"
        "mr %1, 3\n"
        :"=r"(r30), "=r"(r3)
        :
        :"memory", "ctr", "lr", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "12"
    );

    if (((*(int*)0xEFE00000) != RPX_MIIMAKER_NAME) && ((*(int*)0xEFE00000) != RPX_HOME_NAME))
    {
        // Reset flags
        *(int *)(IS_ACTIVE_ADDR) = 1;           // Dump ON for .rpl
        *(int *)(MEM_SIZE) = 0;                 // Reset memory size
        *(int *)(MEM_PART) = 0;                 // Reset memory part
        *(int *)(RPL_FOUND_ADDR) = 0;           // Reset found rpl
    }

    // return properly
    asm("mr 30, %0\n"
        "lwz 26, 0(30)\n"
        :
        :"r"(r30)
        :"memory", "ctr", "lr", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "12"
    );
}

/* LOADER_Prep *****************************************************************
 * - instruction address = 0X0100A024
 * - original instruction = 0x3f00fff9 : "lis r24, -7"
 */
void LOADER_Prep(void)
{
    // Save registers
    int r29;
    asm("mr %0, 29\n"
        :"=r"(r29)
        :
        :"memory", "ctr", "lr", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"
    );

    if (((*(int*)0xEFE00000) != RPX_MIIMAKER_NAME) && ((*(int*)0xEFE00000) != RPX_HOME_NAME))
    {
        if (*(int *)(IS_ACTIVE_ADDR) == 1)
        {
            // Check if it is an rpl we want, look for rpl name
            char* rpl_name = (char*)(*(int*)(r29 + 0x08));
            int len = 0;
            while (rpl_name[len])
                len++;

            // Get rpl entry
            int rpl_entry_nb = 1 + *(int*)(RPL_ENTRY_COUNT);
            s_rpx_rpl *entry = (s_rpx_rpl*)(RPX_RPL_ARRAY + rpl_entry_nb * sizeof(s_rpx_rpl));

            // Fill rpl entry with name
            for (int k = 0; k < len; k++)
                entry->name[k] = rpl_name[k];
            entry->name[len] = '\0';

            // Set current rpl entry
            *(int *)(RPX_RPL_CUR_ENTRY) = rpl_entry_nb;

            // Set found rpl
            *(int *)(RPL_FOUND_ADDR) = 1;
        }
    }

    // return properly
    asm("lis 24, -7\n");
}

/* LiLoadRPLBasics_in_1 ********************************************************
 * - instruction address = 0x010092E4
 * - original instruction = 0x7EE3BB78 : "mr r3, r23"
 */
void LiLoadRPLBasics_in_1(void)
{
    // save registers
    int r23, r3;
    asm("mr %0, 23\n"
        "mr %1, 3\n"
        :"=r"(r23), "=r"(r3)
        :
        :"memory", "ctr", "lr", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"
    );

    if (((*(int*)0xEFE00000) != RPX_MIIMAKER_NAME) && ((*(int*)0xEFE00000) != RPX_HOME_NAME))
    {
        s_rpx_rpl *entry = 0;

        // Check if it is an rpx, look for rpx name, if it is rpl, it is already marked
        int interested = 0;
        int is_rpx = 0;
        int entry_nb = 0;

        // Check if rpl is already marked
        if (*(int *)(RPL_FOUND_ADDR) == 1)
        {
            entry_nb = *(int *)(RPX_RPL_CUR_ENTRY);
            entry = (s_rpx_rpl*)(RPX_RPL_ARRAY + entry_nb * sizeof(s_rpx_rpl));

            // Check if it is an additional rpl
            if (IsAdditionalRPL(entry->name))
            {
                interested = 1;

                // Increment rpl entry count
                *(int*)(RPL_ENTRY_COUNT) = entry_nb;
            }
        }
        else
        {
            // Look for rpx name
            for (int i = 0x100; i < 0x4000; i++)
            {
                int val = *(int*)(0xF6000000 + i);
                if (val == 0x2e727078) // ".rpx"
                {
                    // Get full rpx/rpl name
                    int start = 0;
                    int len = 0;
                    for (int j = i; j > (i - 0x40); j--)
                    {
                        char c = *(char*)(0xF6000000 + j);
                        if (c == '\\')
                        {
                            start = 0xF6000000 + j + 1;
                            len = i - (j + 1) + 4;
                            break;
                        }
                    }

                    // Fill rpx name and set that we are interested
                    if (start != 0)
                    {
                        //s_rpx_rpl *entry = (s_rpx_rpl*)(RPX_RPL_ARRAY);
                        entry = (s_rpx_rpl*)(RPX_RPL_ARRAY);
                        char* rpx_name = (char*)(start);
                        for (int k = 0; k < len; k++)
                            entry->name[k] = rpx_name[k];
                        entry->name[len] = '\0';

                        interested = 1;
                        is_rpx = 1;
                        entry_nb = 0;

                        *(int*)(RPX_ENTRY_COUNT) = 1;
                    }
                }
            }
        }

        if (interested)
        {
            int size = is_rpx ? *(int*)(0xEFE05790) : *(int*)(0xEFE0647C);
            if (size > 0x400000)
                size = 0x400000;

            int mem_offset = *(int *)(MEM_OFFSET);

            // Copy rpx/rpl size and offset in the corresponding entry
            entry->size = size;
            entry->offset = size;
            entry->address = (int)MEM_BASE + mem_offset;

            // Check if we still have memory to copy rpl (at this step if it is rpx, it's no more than 4mB so it's ok)
            if ((mem_offset + size) < MEM_LIMIT)
            {
                // Copy data
                for (int x = 0; x < size; x = x + 4)
                {
                    *(int*)(MEM_BASE + mem_offset + x)= *(int*)(0xF6000000 + x);
                }
            }

            // Increment MEM_OFFSET
            *(int *)(MEM_OFFSET) += size;
        }
    }

    // return properly
    asm("mr 3, 23\n"
        :
        :"r"(r23)
    );
}

/* GetNextBounce_1 **************************************************************
 * - instruction address = 0x0100b728
 * - original instruction = 0x7c0a2040 : "cmplw r10, r4" (instruction is originaly "cmplw r10, r11" but we path it because of the gcc proploge overwriting r11)
 */
void GetNextBounce_1(void)
{
    // Save registers
    int r10;    // size read, max 0x400000, or less if it is end of stream
    asm("mr %0, 10\n"
        :"=r"(r10)
        :
        :"memory", "ctr", "lr", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "12"
    );

    if (((*(int*)0xEFE00000) != RPX_MIIMAKER_NAME) && ((*(int*)0xEFE00000) != RPX_HOME_NAME))
    {
        if (*(int *)(IS_ACTIVE_ADDR) == 1)
        {
            // Bounce flag on and set memory size
            *(int *)(BOUNCE_FLAG_ADDR) = 1;
            *(int *)(MEM_SIZE) = r10;
            
            // Set memory part
            *(int *)(MEM_PART) = 1;
        }
    }

    // return properly
    asm("mr 10, %0\n"
        "cmplw 10, 4\n"
        :
        :"r"(r10)
        :"memory", "ctr", "lr", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "12"
    );
}

/* GetNextBounce_2 **************************************************************
 * - instruction address = 0x0100b780
 * - original instruction = 0x7c0a2040 : "cmplw r10, r4" (instruction is originaly "cmplw r10, r11" but we path it because of the gcc proploge overwriting r11)
 */
void GetNextBounce_2(void)
{
    // Save registers
    int r10; // size read, max 0x400000, or less if it is end of stream
    asm("mr %0, 10\n"
        :"=r"(r10)
        :
        :"memory", "ctr", "lr", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "12"
    );

    if (((*(int*)0xEFE00000) != RPX_MIIMAKER_NAME) && ((*(int*)0xEFE00000) != RPX_HOME_NAME))
    {
        if (*(int *)(IS_ACTIVE_ADDR) == 1)
        {
            // Bounce flag on and set memory size
            *(int *)(BOUNCE_FLAG_ADDR) = 1;
            *(int *)(MEM_SIZE) = r10;

            // Set memory part
            *(int *)(MEM_PART) = 0;
        }
    }

    // return properly
    asm("mr 10, %0\n"
        "cmplw 10, 4\n"
        :
        :"r"(r10)
        :"memory", "ctr", "lr", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "12"
    );
}

/* LiRefillBounceBufferForReading_af_getbounce *********************************
 * - instruction address = 0x0100BA28
 * - original instruction = 0x2C030000 : "cmpwi r3, 0"
 */
void LiRefillBounceBufferForReading_af_getbounce(void)
{
    if (((*(int*)0xEFE00000) != RPX_MIIMAKER_NAME) && ((*(int*)0xEFE00000) != RPX_HOME_NAME))
    {
        if (*(int *)(IS_ACTIVE_ADDR) == 1)
        {
            int is_bounce_flag_on = *(int*)(BOUNCE_FLAG_ADDR);
            if (is_bounce_flag_on)
            {
                // Get remaining size of rpx to copy and truncate it to 0x400000 bytes
                int size = *(int*)(MEM_SIZE);
                if (size > 0x400000)
                    size = 0x400000;

                // Get corresponding entry
                int entry_nb = *(int*)(RPX_RPL_CUR_ENTRY);
                s_rpx_rpl *entry = (s_rpx_rpl*)(RPX_RPL_ARRAY + entry_nb * sizeof(s_rpx_rpl));

                // Get where rpx/rpl code needs to be copied
                int base = 0xF6000000 + (*(int *)(MEM_PART) * 0x400000);

                // Check if we still have memory to copy rpx/rpl
                int mem_offset = *(int *)(MEM_OFFSET);
                if ((mem_offset + size) < MEM_LIMIT)
                {
                    // Copy rpx
                    int offset = entry->address + entry->size;
                    for (int i = 0; i < (size / 4); i++)
                    {
                        *(int *)(offset + i * 4) = *(int *)(base + i * 4);
                    }
                }

                // Increase size, offset, and set next memory part
                entry->size += size;
                entry->offset += size;

                // Increment MEM_OFFSET
                *(int *)(MEM_OFFSET) = mem_offset + size;

                // Bounce flag OFF
                *(int *)(BOUNCE_FLAG_ADDR) = 0;
            }
        }
    }

    // return properly
    asm("cmpwi 3, 0\n");
}

/* LiSetupOneRPL_after *********************************************************
 * - instruction address = 0x0100CDC0
 * - original instruction = 0x7FC3F378 : "mr r3, r30"
 */
void LiSetupOneRPL_after(void)
{
    // Save registers
    int r30;
    asm(
        "mr %0, 30\n"
        :"=r"(r30)
        :
        :"memory", "ctr", "lr", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "23", "29"
    );

    if (((*(int*)0xEFE00000) != RPX_MIIMAKER_NAME) && ((*(int*)0xEFE00000) != RPX_HOME_NAME))
    {
        if (*(int *)(IS_ACTIVE_ADDR) == 1)
        {
            // Dump OFF
            *(int *)(IS_ACTIVE_ADDR) = 0;
        }
    }

    // Return properly
    asm("mr 3, %0\n"
        :
        :"r"(r30)
        );
    return;
}

// Some magic used to store :
// - function address
// - address where to replace the instruction
// - original instruction
#define MAKE_MAGIC(x, orig_instr) { x, addr_ ## x, orig_instr}

// For every replaced functions :
struct magic_t {
    const void* func; // our replacement function which is called
    const void* call; // address where to place the jump to the our function
    uint        orig_instr;
} methods[] __attribute__((section(".magic"))) = {
    MAKE_MAGIC(LOADER_Start,                                0x5586103a),
    MAKE_MAGIC(LOADER_Entry,                                0x835e0000),
    MAKE_MAGIC(LOADER_Prep,                                 0x3f00fff9),

    MAKE_MAGIC(GetNextBounce_1,                             0x7c0a2040),
    MAKE_MAGIC(GetNextBounce_2,                             0x7c0a2040),

    MAKE_MAGIC(LiLoadRPLBasics_in_1,                        0x7EE3BB78),
    MAKE_MAGIC(LiRefillBounceBufferForReading_af_getbounce, 0x2C030000),
    MAKE_MAGIC(LiSetupOneRPL_after,                         0x7FC3F378),
};
