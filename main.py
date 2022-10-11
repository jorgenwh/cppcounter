import numpy as np

import cppcounter as cc

keys = np.load("../cucounter/data/npy/uniquekmers.npy")
counter = cc.Counter(keys=keys)
print(counter)

