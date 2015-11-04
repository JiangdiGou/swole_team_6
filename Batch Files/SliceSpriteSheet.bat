ECHO OFF
ECHO -----------------------
ECHO Slicing textures in SliceInput into SliceOutput 
ECHO -----------------------

REM Gets inputs from user
SET /p outputName=What would you like the base name of output sprites to be?
SET /p tileWidth=What is the width of tiles in the file?
SET /p tileHeight=What is the height of tiles in the file? 

REM Tells user what it's about to do 
ECHO -----------------------
ECHO Slicing the contents of SliceInput.
ECHO Tiles are %tileWidth%x%tileHeight% and named %outputName%-#.png 
ECHO -----------------------

REM Moves to input directory
CD "..\GAM200_Project\resources\Textures\SliceInput"

REM Slices 
SET ouputName="..\SliceOutput\%outputName%.png"
convert *png -crop %tileWidth%x%tileHeight% %ouputName%
PAUSE