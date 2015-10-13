#include "menu.h"
#include "../common/common.h"

/* Utils for the display */
#define PRINT_TEXT1(x, y, str) { OSScreenPutFontEx(1, x, y, str); }
#define PRINT_TEXT2(x, y, _fmt, ...) { __os_snprintf(msg, 80, _fmt, __VA_ARGS__); OSScreenPutFontEx(1, x, y, msg); }
#define BTN_PRESSED (BUTTON_LEFT | BUTTON_RIGHT | BUTTON_UP | BUTTON_DOWN | BUTTON_A | BUTTON_B)

/* Entry point */
int _start(int argc, char *argv[])
{
    /* ****************************************************************** */
    /*                              MENU CHECK                            */
    /* ****************************************************************** */

    // mii maker is our menu :), if it's another app, continue coreinit process
    if (title_id != 0x000500101004A200 && // mii maker eur
        title_id != 0x000500101004A100 && // mii maker usa
        title_id != 0x000500101004A000)   // mii maker jpn
    {
        return main(argc, argv);
    }

    /* ****************************************************************** */
    /*                              Init Memory                           */
    /* ****************************************************************** */

    char* msg = (char*) malloc(80);
    char* mount_path = (char*) malloc(FS_MAX_MOUNTPATH_SIZE);
    char* path = (char*)malloc(FS_MAX_MOUNTPATH_SIZE);

    memset(mount_path, 0, FS_MAX_MOUNTPATH_SIZE);
    memset(path, 0, FS_MAX_MOUNTPATH_SIZE);

    /* ****************************************************************** */
    /*                              Init Screen                           */
    /* ****************************************************************** */

    // Prepare screen
    int screen_buf0_size = 0;
    int screen_buf1_size = 0;
    uint screen_color = 0; // (r << 24) | (g << 16) | (b << 8) | a;

    // Init screen and screen buffers
    OSScreenInit();
    screen_buf0_size = OSScreenGetBufferSizeEx(0);
    screen_buf1_size = OSScreenGetBufferSizeEx(1);
    OSScreenSetBufferEx(0, (void *) 0xF4000000);
    OSScreenSetBufferEx(1, (void *) 0xF4000000 + screen_buf0_size);

    // Clear screens
    OSScreenClearBufferEx(0, screen_color);
    OSScreenClearBufferEx(1, screen_color);

    // Flush the cache
    DCFlushRange((void *) 0xF4000000, screen_buf0_size);
    DCFlushRange((void *) 0xF4000000 + screen_buf0_size, screen_buf1_size);

    // Flip buffers
    OSScreenFlipBuffersEx(0);
    OSScreenFlipBuffersEx(1);

    /* ****************************************************************** */
    /*                              Init SDCARD                           */
    /* ****************************************************************** */

    int sd_status = 0;
    FSMountSource mountSrc;

    // Create client and cmd block
    FSClient* pClient = (FSClient*) malloc(sizeof (FSClient));
    FSCmdBlock* pCmd = (FSCmdBlock*) malloc(sizeof (FSCmdBlock));

    if (pClient && pCmd)
    {
        // Add client to FS.
        FSAddClient(pClient, FS_RET_NO_ERROR);

        // Init command block.
        FSInitCmdBlock(pCmd);

        // Mount sdcard
        if (FSGetMountSource(pClient, pCmd, FS_SOURCETYPE_EXTERNAL, &mountSrc, FS_RET_NO_ERROR) == FS_STATUS_OK)
        {
            if (FSMount(pClient, pCmd, &mountSrc, mount_path, FS_MAX_MOUNTPATH_SIZE, FS_RET_UNSUPPORTED_CMD) == FS_STATUS_OK)
            {
                // Set SD as mounted
                sd_status = 1;
            }
        }
    }

    /* ****************************************************************** */
    /*                              Get dump data                         */
    /* ****************************************************************** */
    int size_copied = 0;

    /* ****************************************************************** */
    /*                              Display MENU                          */
    /* ****************************************************************** */

    char buf_title[16] = {'-', '-', ' ', 'D', 'U', 'M', 'P', 'I', 'I', 'N', 'E', ' ', '-', '-', '\0'};
    char buf_sd_status[40] = {'s', 'd', ' ', 'c', 'a', 'r', 'd', ' ', 'n', 'o', 't', ' ', 'f', 'o', 'u', 'n', 'd', ' ', 'o', 'r', ' ', 'c', 'a', 'n', 'n', 'o', 't', ' ', 'b', 'e', ' ', 'm', 'o', 'u', 'n', 't', 'e', 'd', '\0'};
    char buf_name_and_nb_bytes[15] = {'%', 's', ' ', ':', ' ', '%', 'd', ' ', 'b', 'y', 't', 'e', 's', '\0'};
    char buf_error[19] = {'C', 'a', 'n', '\'', 't', ' ', 'c', 'o', 'p', 'y', ' ', 'f', 'i', 'l', 'e', 's', '!', '\0'};
    char buf_press[34] = {'P', 'r', 'e', 's', 's', ' ', 'A', ' ', 't', 'o', ' ', 'c', 'o', 'p', 'y', ' ', 'f', 'i', 'l', 'e', 's', ' ', 't', 'o', ' ', 's', 'd', ' ', 'c', 'a', 'r', 'd', '\0'};
    char buf_exit[20] = {'P', 'r', 'e', 's', 's', ' ', 'H', 'o', 'm', 'e', ' ', 't', 'o', ' ', 'e', 'x', 'i', 't', '\0'};
    char buf_mode[3] = {'w', '\0' };
    char buf_nb_bytes_copied[22] = {'%', 'd', ' ', 'b', 'y', 't', 'e', 's', ' ', 'c', 'o', 'p', 'i', 'e', 'd' ,'\0'};
    char buf_nb_rpx_rpl[33] = {'%', 'd', ' ', 'r', 'p', 'x', ',', ' ', '%', 'd', ' ', 'r', 'p', 'l', ',', ' ', 't', 'o', 't', 'a', 'l', ' ', 's', 'i', 'z', 'e', ':', '%', 'd', 'M', 'B', '\0'};
    char buf_sel[4] = {'=', '>', '\0'};

    int     entry_index = 0;
    int     entry_sel = 0;
    uint8_t button_pressed = 1;
    uint8_t first_pass = 1;
    uint8_t launched = 0;
    int error;

    int nb_rpx = *(int*)(RPX_ENTRY_COUNT);
    int nb_rpl = *(int*)(RPL_ENTRY_COUNT);
    int nb_entries = (nb_rpx == 1) ? (1 + nb_rpl) : 0;
    int total_size = *(int*)(MEM_OFFSET);
    int total_size_mb = total_size / 1024 / 1024;

    VPADData vpad_data;
    VPADRead(0, &vpad_data, 1, &error); //Read initial vpad status
    while (1)
    {
        // Refresh screen
        OSScreenFlipBuffersEx(1);
        OSScreenClearBufferEx(1, 0);

        // Read vpad
        VPADRead(0, &vpad_data, 1, &error);

        // Title : "-- DUMPIINE --"
        PRINT_TEXT1(24, 1, buf_title);

        if (!sd_status)
        {
            // Print sd card status : "sd card not found or cannot be mounted"
            PRINT_TEXT1(0, 5, buf_sd_status);
        }
        else
        {
            // Compute index
            int mid_page = MAX_ENTRY_ON_PAGE / 2;
            if (entry_sel > mid_page)
                entry_index = entry_sel - mid_page;
            else
                entry_index = 0;
            if (nb_entries > mid_page)
            {
                if (entry_index > (nb_entries - mid_page))
                    entry_index = (nb_entries - mid_page);
            }
            
            if (!launched)
            {
                // Press A to copy files 
                PRINT_TEXT1(0, 16, buf_press);
            }
            else
            {
                // Press Home to exit
                PRINT_TEXT1(0, 16, buf_exit);
            }

            // Nb rpx rpl : "%d rpx, %d rpl"
            PRINT_TEXT2(0, 17, buf_nb_rpx_rpl, nb_rpx, nb_rpl, total_size_mb);

            for (int i = 0; (i < MAX_ENTRY_ON_PAGE) && ((entry_index + i) < nb_entries); i++)
            {
                s_rpx_rpl *entry = (s_rpx_rpl*)(RPX_RPL_ARRAY + (entry_index + i) * sizeof(s_rpx_rpl));

                PRINT_TEXT2(3, 3 + i, buf_name_and_nb_bytes, entry->name, entry->size);
            }

            // Print selector
            PRINT_TEXT1(0, 3 + entry_sel - entry_index, buf_sel);

            // Check buttons
            if (!button_pressed)
            {
                if (vpad_data.btn_hold & BUTTON_UP  ) entry_sel = (entry_sel <= 0) ? nb_entries - 1 : entry_sel - 1;
                if (vpad_data.btn_hold & BUTTON_DOWN) entry_sel = ((entry_sel + 1) % nb_entries);

                if (vpad_data.btn_hold & BUTTON_A && !launched)
                {
                    launched = 1;

                    for (int ent_nb = 0; ent_nb < nb_entries; ent_nb++)
                    {
                        // Get corresponding entry
                        s_rpx_rpl *entry = (s_rpx_rpl*)(RPX_RPL_ARRAY + ent_nb * sizeof(s_rpx_rpl));

                        // Copy mount path
                        memcpy(path, mount_path, FS_MAX_MOUNTPATH_SIZE);

                        // Get length
                        int idx = 0;
                        while (path[idx])
                            idx++;

                        // Concatenate rpx/rpl name
                        path[idx++] = '/';

                        int i = 0;
                        while (entry->name[i])
                            path[idx++] = entry->name[i++];
                        
                        // Add .rpl extension
                        if (ent_nb > 0)
                        {
                            path[idx++] = '.';
                            path[idx++] = 'r';
                            path[idx++] = 'p';
                            path[idx++] = 'l';
                        }

                        path[idx++] = '\0';

                        // Open file
                        int fd = 0;
                        if (FSOpenFile(pClient, pCmd, path, buf_mode, &fd, FS_RET_ALL_ERROR) == FS_STATUS_OK)
                        {
                            char* buffer = memalign(0x1000, 0x40);
                            int size = entry->size;
                            int offset = 0;

                            while (size > 0)
                            {
                                int cur_size = (size > 0x1000) ? 0x1000 : size;
                                void* base = (void*)(entry->address + offset);
                                memcpy(buffer, base, cur_size);

                                FSWriteFile(pClient, pCmd, (void*)(buffer), 1, cur_size, fd, 0, FS_RET_ALL_ERROR);

                                size -= cur_size;
                                offset += cur_size;
                            }
                            size_copied += offset;

                            // close file and free memory
                            FSCloseFile(pClient, pCmd, fd, FS_RET_NO_ERROR);
                            free(buffer);
                        }
                    }
                }
            }
        }

        // Check launch
        if (launched) {
            if (size_copied != total_size)
                PRINT_TEXT1(45, 17, buf_error);
            PRINT_TEXT2(40, 16, buf_nb_bytes_copied, size_copied);
        }

        // Update screen
        if (first_pass) {
            OSScreenFlipBuffersEx(1);
            OSScreenClearBufferEx(1, 0);
            first_pass = 0;
        }

        // Check buttons
        if (vpad_data.btn_hold & BUTTON_HOME)
            break;

        // Button pressed ?
        button_pressed = ((vpad_data.btn_hold & BTN_PRESSED) ? 1 : 0);
    }

    /* ****************************************************************** */
    /*                           Return to app start                      */
    /* ****************************************************************** */

    return main(argc, argv);
}
