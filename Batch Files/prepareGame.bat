ECHO OFF
ECHO .
ECHO -----
ECHO WILL COPY DLLS UPON INPUT
ECHO -----
PAUSE

REM uses a for loop since copy and move dont like using wildcards 
FOR %%i IN (..\GAM200_Project\Depends\*.dll) DO (
ECHO Copying %%i to Debug and Release
COPY /V /Y %%i ..\GAM200_Project\Debug
COPY /V /Y %%i ..\GAM200_Project\Release
) 

ECHO .
ECHO -----
ECHO WILL COPY RESOURCES FOLDER UPON INPUT 
ECHO -----
PAUSE 

REM copies resources folder with xcopy
XCOPY /S /Y /I ..\GAM200_Project\resources ..\GAM200_Project\Debug\resources
XCOPY /S /Y /I ..\GAM200_Project\resources ..\GAM200_Project\Release\resources

ECHO .
ECHO -----
ECHO WILL COPY SCRIPTS FOLDER UPON INPUT 
ECHO -----
PAUSE 

REM copies scripts folder with xcopy
XCOPY /S /Y /I ..\GAM200_Project\Scripts ..\GAM200_Project\Debug\Scripts
XCOPY /S /Y /I ..\GAM200_Project\Scripts ..\GAM200_Project\Release\Scripts

ECHO .
ECHO -----
ECHO WILL DELETE OBJET FILES UPON INPUT
ECHO -----

DEL ..\GAM200_Project\Debug\*.obj
DEL ..\GAM200_Project\Release\*.obj

PAUSE 
