@echo off

:GetInput
set /P choice=Do you want do add(A) or delete(D) the app from startup: 

:: See if the input is valid
set TRUE=
IF %choice% EQU A set TRUE=1
IF %choice% EQU a set TRUE=1
IF %choice% EQU D set TRUE=1
IF %choice% EQU d set TRUE=1


:: If the input is invalid, retry
IF NOT defined TRUE (
    echo Wrong input! Try again
    goto GetInput
)

:: Add the center app to startup
IF %choice% EQU a powershell "$s=(New-Object -COM WScript.Shell).CreateShortcut('%userprofile%\Start Menu\Programs\Startup\Recenterer.lnk');$s.TargetPath='CenterApplication.exe';$s.Save()"
IF %choice% EQU A powershell "$s=(New-Object -COM WScript.Shell).CreateShortcut('%userprofile%\Start Menu\Programs\Startup\Recenterer.lnk');$s.TargetPath='CenterApplication.exe';$s.Save()"

:: Delte the center app from startup
IF %choice% EQU d del "%userprofile%\Start Menu\Programs\Startup\Recenterer.lnk"
IF %choice% EQU D del "%userprofile%\Start Menu\Programs\Startup\Recenterer.lnk"

:: End the program
echo Done
pause