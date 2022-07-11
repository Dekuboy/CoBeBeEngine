# CoBeBeEngine

Game Engine Project

----------------------------------------

include/common folder uses:  
glm  
SDL2

include/msvc folder uses:  
AL  
GL

----------------------------------------

BUILD WITH EMSCRIPTEN BY:

IF ON WINDOWS OS: INSTALL MINGW FIRST

emsdk install mingw-4.6.2-32bit  
emsdk activate mingw-4.6.2-32bit

ENTER SOURCE FOLDER IN EMCMDPROMPT.bat AND ENTER:

mkdir ebuild  
cd ebuild  
emcmake cmake ..  
emmake make

HOST PYTHON SERVER AT http://localhost:8000/ BY:

python -m http.server

EXIT PYTHON SERVER BY:

Ctrl + C

----------------------------------------

PRESS ESC TO FORCE QUIT COBEBE WINDOW  
PRESS Q TO LOCK & UNLOCK MOUSE

dungeon executable:

wasd or gamepad directional pad to move  
move mouse to look