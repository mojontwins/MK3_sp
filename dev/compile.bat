@echo off

SET game=ninjajar_m

echo ### COMPILING ###
rem zcc +zx -vn mk3.c -m -notemp -o %game%.bin -lsplib2 -zorg=24200 > nul
zcc +zx -vn mk3.c -o %game%.bin -lsplib2 -zorg=24000 > nul 
echo ### MAKING TAP ###
..\utils\imanol.exe in=loader\loader.asm-orig out=loader\loader.asm binsize=?%game%.bin
..\utils\pasmo.exe loader\loader.asm loader.bin

..\utils\GenTape.exe ninjajar_m.tap ^
	basic 'NINJAJAR' 10 loader.bin ^
	data                ..\bin\loading.bin ^
	data                %game%.bin

echo ### LIMPIANDO ###
del loader\loader.asm > nul
del loader.bin > nul
del %game%.bin > nul
echo ### DONE ###
