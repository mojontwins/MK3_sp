@echo off
del ..\bin\*.bin /q /s
del ..\bin\*.h /q /s
mkdir ..\bin 2> nul

echo Building binary assets
echo ======================

echo Loading screen
..\utils\png2scr.exe ..\gfx\loading.png ..\bin\loading.bin

echo General assets
..\utils\mkts_sp.exe mode=chars in=..\gfx\font.png out=..\bin\font size=32,2 silent
..\utils\mkts_sp.exe mode=sprites in=..\gfx\ssmain.png out=..\bin\ssmain size=8,1 silent
..\utils\mkts_sp.exe mode=sprites in=..\gfx\ssextra.png out=..\bin\ssextra size=1,1 silent
..\utils\mkts_sp.exe mode=sprites in=..\gfx\sssmall.png out=..\bin\sssmall size=3,1 metasize=1,1 silent

echo Level 0 assets
mkdir ..\bin\level0 2> nul
..\utils\mkts_sp.exe mode=sprites in=..\gfx\ss0.png out=..\bin\level0\ss size=8,1 silent
..\utils\mkts_sp.exe mode=mapped in=..\gfx\ts0.png out=..\bin\level0\ts size=16,2 tmapoffs=64 metasize=2,2 silent
..\utils\packmap_sp.exe in=..\map\level0.map out=..\bin\level0\ size=10,2 fixmappy nodecos noindex
..\utils\eneexp3c_sp.exe in=..\enems\level0.ene out=..\bin\level0\ yadjust=1
..\utils\list2bin.exe  ..\gfx\ts0.behs ..\bin\level0\behs.bin

echo Level 1 assets
mkdir ..\bin\level1 2> nul
..\utils\mkts_sp.exe mode=sprites in=..\gfx\ss1.png out=..\bin\level1\ss size=8,1 silent
..\utils\mkts_sp.exe mode=mapped in=..\gfx\ts1.png out=..\bin\level1\ts size=16,2 tmapoffs=64 metasize=2,2 silent
..\utils\packmap_sp.exe in=..\map\level1.map out=..\bin\level1\ size=10,2 fixmappy nodecos noindex
..\utils\eneexp3c_sp.exe in=..\enems\level1.ene out=..\bin\level1\ yadjust=1
..\utils\list2bin.exe  ..\gfx\ts1.behs ..\bin\level1\behs.bin

echo Level 2 assets
mkdir ..\bin\level2 2> nul
..\utils\mkts_sp.exe mode=mapped in=..\gfx\ts2.png out=..\bin\level2\ts size=16,2 tmapoffs=64 metasize=2,2 silent
..\utils\packmap_sp.exe in=..\map\level2.map out=..\bin\level2\ size=12,1 nodecos noindex
..\utils\eneexp3c_sp.exe in=..\enems\level2.ene out=..\bin\level2\ yadjust=1
..\utils\list2bin.exe  ..\gfx\ts2.behs ..\bin\level2\behs.bin

echo.
echo Compressing some
echo ================
echo Level 0 assets
for %%f in (..\bin\level0\*.bin) do ..\utils\apack.exe "%%~pf%%~nf.bin" "%%~pf%%~nf.c.bin"  >nul

echo Level 1 assets
for %%f in (..\bin\level1\*.bin) do ..\utils\apack.exe "%%~pf%%~nf.bin" "%%~pf%%~nf.c.bin"  >nul

echo Level 2 assets
for %%f in (..\bin\level2\*.bin) do ..\utils\apack.exe "%%~pf%%~nf.bin" "%%~pf%%~nf.c.bin"  >nul

echo.
echo The Librarian!
echo ==============
..\utils\librarian_48.exe list=library.txt librarian=util\librarian.h library=assets\library.h pathprefix=..\bin removebin
