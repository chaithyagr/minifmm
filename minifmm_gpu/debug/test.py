import minifmm
import numpy as np

A = np.random.random(30000)
B = np.random.random(10000)

minifmm.minifmm_pybind(10000, A, B)
print("======================== RUN 2 =================")
minifmm.minifmm_pybind(10000, A, B)


print("======================== RUN 3 =================")
minifmm.minifmm_pybind(10000, A, B)
