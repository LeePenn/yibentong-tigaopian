@echo off
if "%1"=="" goto loop
copy prod%1.in prod.in >nul
echo Problem Test
echo Data %1
time<enter
prod
time<enter
fc prod.out prod%1.out
del prod.in
del prod.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10 11 12) do call %0 %%i
:end
