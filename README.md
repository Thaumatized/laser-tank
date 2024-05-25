# laser tank
This repo is used to test SDL2 and quite possible is the beginnings of a custom game engine.  
Why do things the easy way?  
  
Anways, since the best way to do both of these things is to make a game, this will be a wavedefense game. Enjoy!  

## Linux compilation (mint)
### Prerequisites:
> sudo apt install libsdl2-dev;  
> sudo apt install libsdl2-image-dev;  

also make sure to have python3 and pillow installed.
  
### compile && run:  
> make; ./bin/laser-tank  

## Windows compilation
### Prerequisites:
1. Install mingw64 to get access to gcc  
I am using mingw-builds-binaries .  
https://www.mingw-w64.org/downloads/#mingw-builds  
https://github.com/niXman/mingw-builds-binaries/releases (x86_64-13.2.0-release-win32-seh-ucrt-rt_v11-rev1.7z)  
  
2. install SDL2  
https://github.com/libsdl-org/SDL/releases/tag/release-2.30.3 (SDL2-devel-2.30.3-mingw.zip)  
https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/mingw/index.php  
  
3. install SDL2-image  
https://github.com/libsdl-org/SDL_image/releases (SDL2_image-devel-2.8.2-mingw.zip)  

### compile && run:  
Haven't bothered with make for windows yet.
Sprites:
> mkdir -p bin/sprites/; python3 sprites/spritecombiner.py; python3 sprites/shadowmaker.py;
Program:
gcc main.c -o bin/laser-tank -lmingw32 -lSDL2main -lSDL2_image;
