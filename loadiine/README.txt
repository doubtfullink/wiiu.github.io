/******************************************************************************/
/*                                                                            */
/*                  _                     _ _ _                               */
/*                 | |                   | (_(_)                              */
/*                 | |     ___   __ _  __| |_ _ _ __   ___                    */
/*                 | |    / _ \ / _` |/ _` | | | '_ \ / _ \                   */
/*                 | |___| (_) | (_| | (_| | | | | | |  __/                   */
/*                 ______/\___/ \__,_|\__,_|_|_|_| |_|\___| v1.0              */
/*                                                                            */
/*                    RPX/RPL and File Replacement Tool                       */
/*                                                                            */
/******************************************************************************/

- 1......Requirements 

- 2......How to Use 

- 3......Preparing the SD Card 

/******************************************************************************/
/*                              Requirements                                  */
/******************************************************************************/

- Wii U FW 5.3.2
- SD(HC) Card (Up to 32GB, 64GB Untested)
- Super Smash Bros for Wii U (Disc)


/******************************************************************************/
/*                               How to Use                                   */
/******************************************************************************/

- 1. Setup your SD Card (see below)

- 2. In the Internet Browser, Launch the included kernel exploit (www/kexploit)
(You need a modified kernel exploit that sets 0xA0000000 virtual memory range to 0x10000000 physical memory address)

- 3. Relaunch the Internet Browser

- 4. Launch loadiine (www/loadiine-532), it should return to the Pause Menu. Exit to Home Menu.

- 5. Insert your SD Card into the Wii U, if it's not already done.

- 6. Launch Mii Maker. The loadiine menu should open. Now, Select your App/Game using the D-Pad and press A.

- 7. Mii Maker will finish loading. Quit the application.

- 8. Launch Super Smash Bros and wait for your Game/Application to load.

- 9. Enjoy

- Note: When exiting the Game/Application, you must relaunch the Mii Maker and select the game again.
        If you don't, launching Super Smash Bros will result in a crash.


/******************************************************************************/
/* Preparing the SD Card / How to add a Game or Application                   */
/******************************************************************************/

Note: You may add multiple Games/Applications, but ALL STEPS are REQUIRED

-------------------------------------------------------------------------------

Setting Up RPX Files

1. Create a folder named "_RPX" in the root of the SD Card.
    - ex : SDCARD/_RPX

2. In "_RPX", create a new folder with the name of your app
    - ex : SDCARD/_RPX/MyApplication/

3. Copy the game/homebrew RPX file to the application folder
    - The RPX name MUST BE 4 characters long
    - ex : SDCARD/_RPX/MyApplication/mapp.rpx

4. If your game/homebrew has RPL files, copy them to the application folder
    - Do not rename RPL files
    - ex : SDCARD/_RPX/MyApplication/library1.rpl
    - ex : SDCARD/_RPX/MyApplication/library2.rpl

-------------------------------------------------------------------------------

Setting Up Data Files

1. Create a folder with the name of the RPX you want to add files for in the root of your SD Card.
    - ex : SDCARD/mapp/

2. Copy all Files and Folders from the content folder of your Game/Application (... /vol/content/*)
    - ex : H:/MyApplication/vol/content/data.bin -> SDCARD/mapp/data.bin
    - ex : H:/MyApplication/vol/content/datab/datab.bin -> SDCARD/mapp/datab/datab.bin

-------------------------------------------------------------------------------

Setting Up Sava Data

1. Create a folder with the name "_SAV" on the Root of your SD Card.
   - ex : SDCARD/_SAV

2. In "_SAV", create a folder with the name of the RPX you want Save Data for.
   - In this folder, create two empty folders : "u" and "c"
   - ex : SDCARD/_SAV/mapp
   - ex : SDCard/_SAV/mapp/u
   - ex : SDCard/_SAV/mapp/c

-------------------------------------------------------------------------------

Summary

Your file structure should look like this if the above information was used :

- SDCARD/_RPX/MyApplication/mapp.rpx
- SDCARD/_RPX/MyApplication/*.rpl [only if application contains .rpl files]
- SDCARD/_SAV/mapp/u
- SDCARD/_SAV/mapp/c
- SDCARD/mapp/[content files/folders]


/******************************************************************************/
/* Limitations :                                                              */
/******************************************************************************/

- The total size of RPX and RPL files must be less than 20 MB
- Don't go in the wiiu settings it breaks everything


/******************************************************************************/
/* Notes :                                                                    */
/******************************************************************************/

- If you have problems with saves, try delete your Smash Bros saves.


/******************************************************************************/
/* Using the server (optional) :                                              */
/******************************************************************************/

You can use the loadiine server to log the files opened by your application

- To do so, in "installer/launcher.c" :
    - set USE_SERVER to 1 
    - set SERVER_IP to your address ip in hex
    - compile the project

OR if you don't want to compile the project :

- You can edit the /www-for-server/loadiine-532/payload532.html file
    - look for text : "%uc0a8%u614a%u010a"
    - replace the corresponding number in hexadecimnal :
        - %uc0a8 :
            - c0 => 192 in decimal
            - a8 => 168 in decimal
        - %u010a :
            - 01 => 1   in decimal
            - 0a => 10  in decimal
    - ex : if you want to set PC IP address 192.168.100.164 :
        - "%uc0a8%u614a%u60a4"

Note : Launch the server before launching loadiine, otherwise it will wait for it


/******************************************************************************/
/* Special thanks :                                                           */
/******************************************************************************/

- To everyone involved in libwiiu and webkit/kernel exploit !
- To the testers !


Feel free to modify and improve this software.

Golden45.
