@echo off
if "%1"=="" goto loop
copy tsgl%1.in tsgl.in >nul
echo tsgl TEST
echo Data %1
time<enter
tsgl
time<enter
fc tsgl.out tsgl%1.out
del tsgl.in
del tsgl.out
pause
goto end
:loop
for %%i in (0 1 2 3 4 5 6 7 8 9) do call %0 %%i
:end
