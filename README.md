# anubis
anubis is a mod menu for gd (geometry dash), made by me, zVaiku.

## prerequisites
* [cmake](https://cmake.org/)
* [vs2022](https://visualstudio.microsoft.com/)
    - in bootstrapper, select 'desktop development with c++', or else msvc will not install.

## building
first, clone the repository by using this:
```
git clone https://github.com/xodys10/anubis
```

now, we gotta go into the repo by doing `cd anubis`.<br>

### HOLD UP &ndash; we need vc vars
open file explorer, and paste this in:
<br>
 ```C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat x64```

then, we need to generate build files with cmake:
```
cmake -G "Visual Studio 17 2022" -A x64 .
cmake --build . --config Debug

```

we're done????