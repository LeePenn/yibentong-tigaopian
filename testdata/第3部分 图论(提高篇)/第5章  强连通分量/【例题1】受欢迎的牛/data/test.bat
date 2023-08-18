@echo off
if "%1"=="" goto loop
echo TEST
echo Test%1
copy popular%1.in popular.in >nul
time <enter
popular
time <enter
fc popular%1.out popular.out
pause
del popular.in
del popular.out
goto end
:loop
  for %%i in (0 1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end