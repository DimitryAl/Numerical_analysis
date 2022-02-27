import matplotlib.pyplot as plt

import math

#Заданная функция
def func(x):
  return math.pow( math.log(x), 13/4)
#Полином Лагранжа
def Lag(x, xi, n):
  result = 0
  for i in range(n):
    basis = 1
    for j in range(n):
      if j != i:
        basis *= (x-xi[j])/(xi[i] - xi[j])
    result += basis * func(xi[i])
  return result

a = 2.5
x = [2, 3, 4]
n = len(x)

aX = []
aFunc = []
aLag = []
for i in range(101):
  aX.append(x[0] + (x[n-1] - x[0])/100 * i)
  aFunc.append(func(aX[i]))
for i in range(101):
  aLag.append(Lag(aX[i], aX, len(aX)))

plt.plot(aX, aLag, label = "Lagrange")
plt.plot(aX, aFunc, label = "log(x)^(13/4)")

print("ln(", a, ") =\t", func(a))
print("Полином лагранжа\t", Lag(a, x, n))

plt.legend()
plt.show()
