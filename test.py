import numpy as np
import pandas as pd
from scipy import optimize, stats, special, integrate
import matplotlib.pyplot as plt

import ars, time

t0 = time.time()
samples = ars.get_gamma(5.0, 2.0, 20000)
print('time',time.time() - t0)

print(samples.shape)
print(samples.dtype)
print(samples.min())
print(samples.max())



fig = plt.figure(figsize=(15, 8))
xpts = np.linspace(0.0, 7, 1001)
xdiff = xpts[1]-xpts[0]

kde = stats.gaussian_kde(samples, bw_method=0.04)

y1 = stats.gamma(5, scale=1/2).pdf(xpts)
y2 = kde(xpts)

plt.figure(figsize=(15, 8))
plt.plot(xpts, y1, color='r', label='gamma(2,2)')
plt.plot(xpts, y2, color='b', label='smooth')
plt.grid(True)
plt.legend(loc='upper right')
#plt.xlim(-20,2)



