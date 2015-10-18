ECHO OFF
ECHO -----------------------
ECHO Packing textures in AtlasInput folder into atlas
ECHO WARNING if Atlas\name exists, it will be deleted. 
ECHO -----------------------

REM sets vars based on what you want to name the atlas 
SET /p outputName=What would you like to name this atlas?
SET textureList=tList_%outputName%.txt
REM Moves from batch dir to texture dir 
CD "..\GAM200_Project\resources\Textures\AtlasInput"

set outputName="..\Atlas\%outputName%.png"
set textureList="..\%textureList%"

REM deletes files that this generates if they exist
IF EXIST %textureList%  DEL /F %textureList%
IF EXIST %outputName% DEL /F  %outputName%

REM puts all of the filenames in a text file 
DIR /b *png > %textureList%

REM Moves out of the atlasInput directory
ECHO -----------------------
echo Generating atlas: %outputName%
echo Generating map: %textureList%
ECHO -----------------------

REM packs the files into an atas
"..\spriteSheetPacker\sspack.exe" /image:%outputName% /il:%textureList% /map:%textureList% /r /pow2 /sqr
PAUSE
