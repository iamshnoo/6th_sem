from numpy import *
import sys

points = genfromtxt("data.csv", delimiter=",")
learning_rate = 0.0001
b = 0  # initial y-intercept guess
m = 0  # initial slope guess
num_iterations = 10000


def gradient_descent():
    b_current = b
    m_current = m
    for _ in range(num_iterations):
        b_gradient = 0
        m_gradient = 0
        N = float(len(points))
        for i in range(0, len(points)):
            x = points[i, 0]
            y = points[i, 1]
            b_gradient += -(2/N) * (y - ((m_current * x) + b_current))
            m_gradient += -(2/N) * x * (y - ((m_current * x) + b_current))
        new_b = b_current - (learningRate * b_gradient)
        new_m = m_current - (learningRate * m_gradient)
        b_current = new_b
        m_current = new_m
    b = b_current
    m = m_current
    return b, m


'''
6.7, 3.1
6.9, 3.1
5.8, 2.7
6.8, 3.2
6.7, 3.3
6.7, 3.0
6.3, 2.5
6.5, 3.0
6.2, 3.4
5.9, 3.0
'''

if __name__ == '__main__':
    # run()
    b_, m_ = gradient_descent()
