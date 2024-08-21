import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))

with open("./output/ans.txt") as f:
    with open("./output/your_output.txt") as g:
        ans = f.read()
        your_output = g.read()
        ans = list(map(int, ans.split()))
        your_output = list(map(int, your_output.split()))
        if ans == your_output:
            print("AC")
        else:
            print("WA")

