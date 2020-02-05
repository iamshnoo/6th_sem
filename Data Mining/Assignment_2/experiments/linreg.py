# Simple Linear Regression(y= β0 + β1x +Ɛ) -> Ordinary Least Square method
# using the GPA vs SAT score dataset

import numpy as np
import sys
import matplotlib.pyplot as plt

'''
dataset = np.genfromtxt("data/linreg.csv", delimiter=",")
data = dataset[:, [0, 1]]
training_data = data[1:75, :]
test_data = data[75:85, :]
X_train, y_train = training_data[:, 0], training_data[:, 1]
'''

np.random.seed(0)
x = np.random.rand(100, 1)
y = 2 + 3 * x + np.random.rand(100, 1)
X_train, y_train = x, y

mu, sigma = 0, 0.1
epsilon = np.random.normal(mu, sigma)
beta_0 = epsilon    # intercept
beta_1 = 0          # slope
mean_x = np.mean(X_train)
mean_y = np.mean(y_train)
num_train_samples = len(X_train)

# Using derived formula to calculate beta_1 and beta_0
numer = 0
denom = 0
for i in range(num_train_samples):
    numer += (X_train[i] - mean_x) * (y_train[i] - mean_y)
    denom += (X_train[i] - mean_x) ** 2
beta_1 = numer / denom
beta_0 = mean_y - (beta_1 * mean_x)
print(beta_0)
print(beta_1)

plt.scatter(X_train, y_train)
y = beta_0 + beta_1 * X_train
fig = plt.plot(X_train, y, lw=4, c='orange', label='Regression Line')
plt.xlabel('SAT', fontsize='20')
plt.ylabel('GPA', fontsize='20')
plt.show()
