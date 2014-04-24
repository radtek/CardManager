@echo off

set mode=
set /p mode=Please choose deploy mode(1-Debug 2-Release):
set dirName=
if "%mode%"=="1" (set dirName=Debug) else (set dirName=Release) 

set dir=.\CardInterface_%date:~0,2%%date:~3,2%%date:~6,4%
echo %dir%
md %dir%

copy /y ..\%dirName%\CardOCX.dll             %dir%
copy /y ..\%dirName%\CardInterface.dll       %dir%
copy /y ..\%dirName%\iomem.dll               %dir%
copy /y ..\%dirName%\CardManager.exe         %dir%
copy /y .\InstallOCX.bat                     %dir%
copy /y .\UninstallOCX.bat                   %dir%

pause

