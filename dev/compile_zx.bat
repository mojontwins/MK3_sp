@echo off

SET game=otro_bosque

echo ### PREPARING ###
..\utils\texts2array2.exe ..\texts\dialogue_sp.txt ..\dev\assets\ob_texts.h texts0 19

echo ### COMPILING ###
rem zcc +zx -vn mk3.c -m -notemp -o %game%.bin -lsplib2 -zorg=24200 > nul
zcc +zx -vn mk3.c -o %game%.bin -lsplib2 -zorg=24000 -DSPECCY  > nul  

echo ### MAKING TAP ###
..\utils\apack.exe %game%.bin gamec.bin
..\utils\apack.exe ..\ports\zx\bin\loading.bin scrc.bin
..\utils\imanol.exe in=loader\loaderzx.asm-orig out=loader\loader.asm mainbincompstart=?65000-gamec.bin mainbincomplength=?gamec.bin loadingcompstart=?65000-scrc.bin loadingcomplength=?scrc.bin
..\utils\pasmo.exe loader\loader.asm loader.bin loader.txt
..\utils\GenTape.exe %game%.tap ^
	basic 'CHERIL' 10 loader.bin ^
	data              scrc.bin ^
	data              gamec.bin

echo ### LIMPIANDO ###
del gamec.bin 
del scrc.bin
del loader\loader.asm > nul
rem del loader.bin > nul
del loader.txt > nul
del %game%.bin > nul
del zcc_opt.def > nul

echo ### DONE ###
:fin
