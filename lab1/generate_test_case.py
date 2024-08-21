import random
from ctypes import *

    # n ranges from 1 to the biggest number of integers
with open('./data/testcase.txt', 'w') as f:
    n = random.randint(1 << 8, 1 << 12)
    f.write(str(n) + '\n')
    for i in range(n):
        f.write(str(random.randint(1, 1 << 10)) + ' ')
    f.write('\n')
    m = random.randint(1, 1 << 12)
    f.write(str(m) + '\n')
    f.close()