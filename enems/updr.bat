@echo off
if [%1]==[] goto :mal
goto :bien
:mal
echo "$ updr.bat cpc|zx"
goto :fin
:bien
copy ..\ports\%1\gfx\ts*.png > nul
copy ..\map\level*.map > nul
echo DONE
:fin
