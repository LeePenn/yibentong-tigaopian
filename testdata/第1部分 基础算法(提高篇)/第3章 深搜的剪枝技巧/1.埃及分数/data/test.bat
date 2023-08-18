@echo off
if "%1"=="" goto loop
echo TEST
echo Test%1
copy fraction%1.in fraction.in >nul
time <enter
fraction
time <enter
fc fraction%1.out fraction.out
pause
del fraction.in
del fraction.out
goto end
:loop
  for %%i in (0 1 2 3 4 5 6 7 8 9) do call %0 %%i
:end