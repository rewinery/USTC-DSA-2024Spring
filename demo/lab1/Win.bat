@rem This bat script is used for Windows Users
@echo off  
gcc yourcode.c -o yourcode.exe  
for /L %%i in (1,1,5) do (
    echo Test case %%i
    python generate_test_case.py  
    ans.exe > output\ans.txt  
    yourcode.exe > output\your_output.txt  
    python judge.py  
)
pause