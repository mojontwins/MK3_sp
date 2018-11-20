@echo off

SET game=otro_bosque
..\utils\texts2array2.exe ..\texts\dialogue_sp.txt ..\dev\assets\ob_texts.h texts0 19
..\utils\mkts_om.exe platform=cpc mode=pals in=..\ports\cpc\gfx\pal.png prefix=my_inks out=assets\pal.h silent

if [%1]==[tape] goto :tape

:disc
echo *** DSK version ***

echo ### COMPILING ###
zcc +cpc -vn -O3 -unsigned -zorg=1024 -lcpcrslib -DCPC -o %game%.bin tilemap_conf.asm mk3.c > nul 
rem zcc +cpc -vn -O3 -unsigned -m -notemp -zorg=1024 -lcpcrslib -DCPC -o %game%.bin tilemap_conf.asm mk3.c

echo ### MAKING DSK ###
copy %game%.bin game.bin > nul 
copy ..\ports\cpc\base.dsk %game%.dsk > nul 
copy ..\ports\cpc\arkos_sfx.c.bin arkos.bin > nul 
rem copy ..\ports\cpc\bin\loading.bin loading.bin > nul
..\utils\CPCDiskXP\CPCDiskXP.exe -File game.bin -AddAmsDosHeader 400 -AddToExistingDsk %game%.dsk
..\utils\CPCDiskXP\CPCDiskXP.exe -File arkos.bin -AddAmsDosHeader 7DFA -AddToExistingDsk %game%.dsk
rem ..\utils\CPCDiskXP\CPCDiskXP.exe -File loading.bin -AddAmsDosHeader C000 -AddToExistingDsk %game%.dsk

echo ### LIMPIANDO ###
del %game%.bin  > nul 
del game.bin > nul
del arkos.bin > nul 
del loading.bin > nul 2> nul
del zcc_opt.def  > nul 
goto :fin

:tape
echo *** CDT version ***
echo ### COMPILING ###
zcc +cpc -vn -O3 -unsigned -zorg=1024 -lcpcrslib -DCPC -DTAPE -o %game%.bin tilemap_conf.asm mk3.c > nul 

echo ### MAKING TAP ###

..\utils\apack.exe %game%.bin gamec.bin
..\utils\apack.exe ..\ports\cpc\bin\loading.bin scrc.bin
copy ..\ports\cpc\arkos_sfx.c.bin arkos_sfx.c.bin > nul 

..\utils\imanol.exe in=loader\loadercpc.asm-orig out=loader\loader.asm binsize=?%game%.bin  scrc_size=?scrc.bin mainbin_size=?gamec.bin arkos_c_size=?arkos_sfx.c.bin > nul
..\utils\pasmo.exe loader\loader.asm loader.bin  > nul
rem copy ..\ports\cpc\bin\arkos.bin .  > nul
rem copy ..\ports\cpc\bin\sfx.bin .  > nul


..\utils\2cdt.exe -n -r cheril -s 1 -X $a300 -L $a300 loader.bin otro_bosque.cdt  > nul
..\utils\2cdt.exe -r scr -s 1 -m 2 scrc.bin otro_bosque.cdt  > nul
..\utils\2cdt.exe -r game -s 1 -m 2 gamec.bin otro_bosque.cdt  > nul
..\utils\2cdt.exe -r arkos -s 1 -m 2 arkos_sfx.c.bin otro_bosque.cdt  > nul

echo ### LIMPIANDO ###
rem del loader\loader.asm > nul
rem del loader.bin > nul 
del %game%.bin  > nul 
del gamec.bin > nul
del arkos_sfx.c.bin > nul 
del loading.bin > nul 2> nul
del zcc_opt.def  > nul 

:fin
