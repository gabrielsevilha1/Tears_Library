# Tears_Library ![alt_text](/TearsLibraryIcon.png)

-Unique header library.<br/>
-Quick to use.<br/>
-Open Source (zlib).<br/>
-Linux and Windows.<br/>
-C++.<br/>

For compile in Windows: -lopengl32 -lgdi32 -lgdiplus <br/>
For compile in Linux: -lX11 -lXrandr -lGL

Exemple:<br/>
```#include"tears_library.h"
int main(){
TWindow w;
    while(!vk_escape){
        w.show();
    }
}```

***by: Gabriel Sevilha <3***
