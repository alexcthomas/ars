# -*- coding: utf-8 -*-
"""
Created on Tue May 29 12:27:57 2018

@author: alex
"""

import ars, time

t0 = time.time()
ret = ars.GetUniform(200000000)
print('time',time.time() - t0)

print(ret.shape)
print(ret.dtype)
print(ret.min())
print(ret.max())
