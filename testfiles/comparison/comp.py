import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

phi0 = 2.067833848E-15

f1 = 10E-3
f2 = 10e6

# msfn = lambda A,alpha,f1,f2 : A*(-f1**(1+alpha)+f2**(1-alpha))/(1+alpha)*10**-12
msfn = lambda A,alpha,f1,f2 : (A * (f1 * f2)**(-alpha) * (-f1**alpha * f2 + f1 * f2**alpha))/(-1+alpha) * 10**-12
""" 
spectrum for d1: 

alpha = 0.96

SQRT A = 14.5

"""
simA = 4.67775e-10
typeD1_A = 14.5 ** 2
typeD1_alpha = 0.96

print(f"type D1 msfn: {msfn(typeD1_A,typeD1_alpha,f1,f2)}, noise ex module {simA}")

"""
Spectrum for f1

alpha = 0.67

SQRT A = 8

(A (-f1^(1 + [Alpha]) + f2^(1 +[Alpha])))/(1 + [Alpha])
"""

simF = 2.70796e-09
typef1_A = 8**2
typef1_alpha =  0.67


print(f"type f1 msfn integral: {msfn(typef1_A,typef1_alpha,f1,f2)}, noise ex module {simF}")


