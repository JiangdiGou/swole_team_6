@REM Gets rid of some of the output
@ECHO off
@ECHO Packing textures in source into atlas
@ECHO 
set /p outputName=What would you like to name this atlas?

@REM Moves from batch dir to texture dir 
@CD "..\GAM200_Project\resources\Textures"

@REM deletes files that this generates if they exist
IF EXIST textureList.txt  DEL /F textureList.txt
IF EXIST %outputName% DEL /F  %outputName%

cd "Source"

@REM puts all of the filenames in a text file 
DIR /b *png > ../textureList.txt

@REM Moves out of the source directory
echo %outputName%

@REM packs the files into an atas
"../spriteSheetPacker/sspack.exe" /image:%outputName% /il:textureList.txt /r
PAUSE