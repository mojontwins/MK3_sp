@echo off

mkdir ..\ports\cpc\bin 2> nul
del ..\ports\cpc\bin\*.bin /q /s
del ..\ports\cpc\bin\*.h /q /s

echo.
echo Building binary assets
echo ======================

echo.
echo General assets
echo --------------
..\utils\mkts_om.exe platform=cpc brickInput pal=..\ports\cpc\gfx\pal.png  mode=sprites in=..\ports\cpc\gfx\ssch.png out=..\ports\cpc\bin\ssch size=3,5 max=13 metasize=2,3 silent
..\utils\mkts_om.exe platform=cpc brickInput pal=..\ports\cpc\gfx\pal.png  mode=sprites in=..\ports\cpc\gfx\ssge.png out=..\ports\cpc\bin\ssge size=6,1 metasize=2,3 silent
..\utils\mkts_om.exe platform=cpc brickInput pal=..\ports\cpc\gfx\pal.png  mode=sprites in=..\ports\cpc\gfx\ssempty.png out=..\ports\cpc\bin\ssempty size=1,1 metasize=2,3 silent
..\utils\mkts_om.exe platform=cpc brickInput pal=..\ports\cpc\gfx\pal.png  mode=sprites in=..\ports\cpc\gfx\ssen.png out=..\ports\cpc\bin\ssen size=8,1 silent
..\utils\mkts_om.exe platform=cpc brickInput pal=..\ports\cpc\gfx\pal.png  mode=sprites in=..\ports\cpc\gfx\sssmall.png out=..\ports\cpc\bin\sssmall size=1,1 metasize=1,1 silent

echo.
echo Fixed screens
echo -------------
..\utils\mkts_om.exe platform=cpc pal=..\ports\cpc\gfx\pal_loading.png  mode=scr  in=..\ports\cpc\gfx\loading.png out=..\ports\cpc\bin\loading.bin silent

echo.
echo Level 0 assets
echo --------------
rem mkdir ..\ports\cpc\bin\level0 2> nul
..\utils\rle44map_sp.exe in=..\map\level0.map out=..\ports\cpc\bin\ size=5,7 tlock=15 fixmappy nodecos noindex scrsize=16,12
..\utils\eneexp3b_sp.exe in=..\enems\level0.ene out=..\ports\cpc\bin\ yadjust=1 prefix=0
..\utils\list2bin.exe  ..\ports\cpc\gfx\ts.behs ..\ports\cpc\bin\behs.bin

echo.
echo Creating main pattern set and level-based tilemaps
echo --------------------------------------------------
cd ..\ports\cpc\gfx
..\..\..\utils\mkts_om.exe platform=cpc mode=scripted in=ts.spt silent
cd ..\..\..\dev

echo.
echo ARKOS tracker player stuff
echo --------------------------
cd ..\lib\arkos\
echo Assembling player
..\..\utils\pasmo.exe ArkosTrackerPlayer_CPC_MSX.asm ..\..\ports\cpc\bin\arkos.bin arkos.lst
echo Compiling assets
cd ..\..\ports\cpc\ogt\
..\..\..\utils\AKSToBIN.exe -a 32250 Yun_Inbosqued_v1.aks ..\bin\m0.bin
..\..\..\utils\AKSToBIN.exe -s -a 60928 sfx___vol_1.aks ..\bin\sfx.bin
cd ..\..\..\dev\
..\utils\apack.exe ..\ports\cpc\bin\arkos.bin ..\ports\cpc\bin\arkos.c.bin >nul
..\utils\apack.exe ..\ports\cpc\bin\sfx.bin ..\ports\cpc\bin\sfx.c.bin >nul
copy /b ..\ports\cpc\bin\arkos.c.bin + ..\ports\cpc\bin\sfx.c.bin ..\ports\cpc\arkos_sfx.c.bin >nul
..\utils\apack.exe ..\ports\cpc\bin\m0.bin ..\ports\cpc\bin\m0.c.bin >nul

rem echo.
rem echo Compressing some
rem echo ================
rem echo Level 0 assets
rem for %%f in (..\ports\cpc\bin\level0\*.bin) do ..\utils\apack.exe "%%~pf%%~nf.bin" "%%~pf%%~nf.c.bin"  >nul

echo.
echo The Librarian!
echo ==============
..\utils\librarian_48.exe list=library_cpc.txt librarian=util\librarian.h library=assets\library_cpc.h pathprefix=..\ports\cpc\bin removebin
