Cafiine compatible with 5.3.2 fw

Features :
- list game files
- replace game files
- dump game files

Compilation :
- in order to compile cafiine you need to put the cafiine folder in your libwiiu project
- libwiuu/cafiine/client must be compiled separately (cd libwiuu/cafiine/client ; make)
- libwiiu/cafiine/installer must be compiled like the other libwiiu examples (with the build.py script)

Pre-made version :
- in www/cafiine, it is already compiled, just put the folder in your server
 (don't forget to change "window.location = "cafiine/payload532.html"; in index.html if needed)

Note :
In cafiine you need to provide the cafiine_server ip, in this version of cafiine you can change it directly in the application.
If you want to change the default ip, you need to recompile the installer (cafiine/installer/cafiine.c) and change the value of DEFAULT_SERVER_IP.

How to use :
- launch the kernel exploit in the brower
- open cafiine server in your computer, check your ip
- relaunch browser and launch cafiine app, set cafiine server ip in the application with up/down/left/right, and press A to install cafiine
  -> browser should exit
- launch a game or application
- cafiine now connects on any FS or FSA access and you should be able to see the files used in the game
  - only if a folder in cafiine/server/cafiine_root exists with the title_id of the game (ex: 00050000-1010ED00)

- replace game file :
  - create a folder in cafiine/server/cafiine_root with the title_id of the game and put your new file in the same directory as the game
    - ex : 00050000-1010ED00\vol\content\audio\stream\Title_WU.aa.32.dspadpcm.bfstm to replace the title song of MK8

- dump game file : 
  - create an empty file with the name of the file you want followed by "-request" (or "-request_slow")
    - ex : 00050000-1010ED00\vol\content\audio\stream\Title_WU.aa.32.dspadpcm.bfstm-request to dump the title song of MK8 
    - note : for some files it can crash when file is read, you can try adding "-request_slow" instead of "-request" to read the file slowly
  - when the game open the requested file, the server creates a new file in the same folder with the filename followed by "-dump"
    - ex : 00050000-1010ED00\vol\content\audio\stream\Title_WU.aa.32.dspadpcm.bfstm-dump


    )))
    (((
  +-----+
  |     |]
  `-----'