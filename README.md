# Tears_Library ![alt_text](/TearsLibraryIcon.png) <br/>

**C++ Graphics Library.** <br/>

-Unique header library.<br/>
-Quick to use.<br/>
-GDI+ and OpenGL API. <br/>
-Raw OpenGL context for 3D. <br/>
-Open Source (zlib).<br/>
-Linux and Windows.<br/>
-C++.<br/>

For linux can be necessary install: libx11-dev, libxrandr-dev, libgl1-mesa-dev<br/>

For compile in Windows: -lopengl32 -lgdi32 -lgdiplus <br/>
For compile in Linux:   -lX11 -lXrandr -lGL <br/>

**Exemple:**<br/>
```C++
#include"tears_library.h"
int main(){
    TWindow w;
    while(!vk_escape){
        w.show();
    }
    w.shutdown();
}
```

***by: Gabriel Sevilha <3***
