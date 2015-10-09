@echo off
@echo Trying to pack sprites into a sheet
@echo "%cd%"
@cd "..\GAM200_Project\resources\Textures"

dir /b "..\Textures" > fileList.txt

"spriteSheetPacker/sspack.exe" /image:out.png /il:fileList.txt /r
pause