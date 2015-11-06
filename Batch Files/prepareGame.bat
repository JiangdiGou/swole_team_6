ECHO OFF
ECHO Preparing Game Assets 
ECHO Moving dlls

copy ..\GAM200_Project\Depends\*.dll ..\GAM200_Project\Debug
copy ..\GAM200_Project\Depends\*.dll ..\GAM200_Project\Release

PAUSE