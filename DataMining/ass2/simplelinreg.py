#!/usr/bin/env python
# -*- coding: utf-8 -*- 

import matplotlib.pyplot as plt
import numpy as np


def preprocess():
    # import the data and normalize it
    dataset = np.genfromtxt("data/iris.csv", delimiter=",")
    low, high = np.amin(dataset, axis=0), np.amax(dataset, axis=0)
    for j in range(4):
        minimum, maximum = low[j], high[j]
        for i in range(150):
            dataset[i][j] = (dataset[i][j] - minimum)/(maximum - minimum)

    # using first column as X regression variables and 2nd column as Y variable
    data = dataset[:, [0, 1]]
    return data


def test_train_split(data):
    training_data = data[0:120, :]
    X_train, y_train = training_data[:, 0], training_data[:, 1]
    X_train = X_train.reshape((120, 1))
    y_train = y_train.reshape((120, 1))
    return X_train, y_train


def initialize(X_train, y_train):
    # x.shape = (120,2) -> contains 1 column corresponding to X_train and a column of 1's corresponding to bias
    x = np.c_[np.ones((X_train.shape[0], 1)), X_train]
    y = y_train

    # initialize the model parameters
    lr = 0.05
    epochs = 1000
    w = np.random.rand(x.shape[1], 1)
    all_losses = []
    m = x.shape[0]

    return x, y, w, lr, m, epochs, all_losses


def train(x, y, w, lr, m, epochs, all_losses):

    # training loop
    for _ in range(epochs):
        # y_pred corresponds to h(x) = β0 + β1 * X
        y_pred = np.dot(x, w)
        residuals = y_pred - y
        gradient_vector = np.dot(x.T, residuals)
        w -= (lr / m) * gradient_vector
        epoch_loss = np.sum((residuals ** 2)) / (2 * m)
        all_losses.append(epoch_loss)

    return w, all_losses


def write_summary(x, y, w):

    # output summary
    predicted_values = np.dot(x, w)
    beta_0, beta_1 = w[0], w[1]
    rmse = np.sqrt(np.sum((y - predicted_values) ** 2))

    print('The value of β0 is {}'.format(beta_0))
    print('The value of β1 is {}'.format(beta_1))
    print('Root mean squared error of the model is {}.'.format(rmse))

    return predicted_values


def plot(x, y, X_train, predicted_values, all_losses):
    fig, axs = plt.subplots(1, 2, figsize=(10, 4), sharey=False)
    axs[0].scatter(X_train, y)
    axs[0].plot(x, predicted_values, lw=4,
                c='orange', label='Regression Line')
    axs[1].plot(all_losses, label='Losses')
    if plt.get_backend().lower() in ['agg', 'macosx']:
        fig.set_tight_layout(True)
    else:
        fig.tight_layout()
    #fig.savefig('simplelinreg.jpg')
    plt.show()


if __name__ == "__main__":
    data = preprocess()
    X_train, y_train = test_train_split(data)
    x, y, w, lr, m, epochs, all_losses = initialize(X_train, y_train)
    w, all_losses = train(x, y, w, lr, m, epochs, all_losses)
    predicted_values = write_summary(x, y, w)
    plot(x, y, X_train, predicted_values, all_losses)
    exit()
