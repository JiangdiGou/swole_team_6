@echo off
@echo Trying to pack sprites into a sheet
@cd "%cd%\..\GAM200_Project\resources\SpriteSheetPacker
sspack.exe /il:"%cd%\..\Textures" /image:"myDummyFiles.png" "DummySheet1.png DummySheet2.png"
pause