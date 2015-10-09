#!/bin/bash
echo `PWD`
#global vars
#SCRIPT=$(readlink -f "$0")
SCRIPTPATH="`PWD`"

#helpers
function pause(){
   read -p "$*"
}

inputDir="$SCRIPTPATH/../GAM200_Project/resources/textures"
inputFlags="/il:"

#eval "`cygpath -w "$SCRIPTPATH/../GAM200_Project/resources/SpriteSheetPacker/sspack.exe"`"
CMD="$SCRIPTPATH/../GAM200_Project/resources/SpriteSheetPacker/sspack.exe"
echo "Haider"
#eval $CMD
#eval $("$SCRIPTPATH/../GAM200_Project/resources/SpriteSheetPacker/sspack.exe") #"$inputFlags $inputDir"
#$("$SCRIPTPATH/../GAM200_Project/resources/SpriteSheetPacker/sspack.exe")
$(CMD)
 
# ...
# call it
pause 'Press [Enter] key to continue...'
echo 
