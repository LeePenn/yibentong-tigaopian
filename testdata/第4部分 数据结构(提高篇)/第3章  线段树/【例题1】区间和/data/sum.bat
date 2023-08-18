@echo off
if "%1"=="" goto loop
copy sum%1.in sum.in>nul
echo sum TEST
echo Data %1
time<enter
sum
time<enter
fc sum%1.out sum.out
pause
del sum.in
del sum.out
goto end
:loop
for %%i in (0 1 2 3 4 5 6 7 8 9 10 11 12 13) do call %0 %%i
:end
