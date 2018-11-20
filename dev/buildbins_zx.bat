@echo off

mkdir ..\ports\zx\bin 2> nul
del ..\ports\zx\bin\*.bin /q /s
del ..\ports\zx\bin\*.h /q /s

echo.
echo Building binary assets
echo ======================

echo.
echo Loading screen
echo --------------
..\utils\png2scr.exe ..\ports\zx\gfx\loading.png ..\ports\zx\bin\loading.bin > nul

echo.
echo General assets
echo --------------
..\utils\mkts_om.exe platform=zx mode=sprites in=..\ports\zx\gfx\ssch.png out=..\ports\zx\bin\ssch size=5,5 max=21 metasize=2,3 silent
..\utils\mkts_om.exe platform=zx mode=sprites in=..\ports\zx\gfx\ssen.png out=..\ports\zx\bin\ssen size=8,1 metasize=2,2 silent
..\utils\mkts_om.exe platform=zx mode=sprites in=..\ports\zx\gfx\sssmall.png out=..\ports\zx\bin\sssmall size=1,1 metasize=1,1 silent

echo.
echo Fixed screens
echo -------------

echo.
echo Level 0 assets
echo --------------
rem mkdir ..\ports\zx\bin\level0 2> nul
..\utils\rle44map_sp.exe in=..\map\level0.map out=..\ports\zx\bin\ size=5,7 tlock=15 fixmappy nodecos noindex scrsize=16,12
..\utils\eneexp3b_sp.exe in=..\enems\level0.ene out=..\ports\zx\bin\ yadjust=1 prefix=0
..\utils\list2bin.exe  ..\ports\zx\gfx\ts.behs ..\ports\zx\bin\behs.bin

echo.
echo Creating main pattern set and level-based tilemaps
echo --------------------------------------------------
cd ..\ports\zx\gfx
..\..\..\utils\mkts_om.exe platform=zx mode=scripted in=ts.spt silent
cd ..\..\..\dev

echo.
echo The Librarian!
echo ==============
..\utils\librarian_48.exe list=library_zx.txt librarian=util\librarian.h library=assets\library_speccy.h pathprefix=..\ports\zx\bin removebin
