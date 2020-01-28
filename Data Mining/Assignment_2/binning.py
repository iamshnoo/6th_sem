import numpy as np
import matplotlib.pyplot as plt

# import the data and normalize it
# use first column as input data
# Step 1 : Sort the data
# Step 2 : Create 30 equidepth bins (Divide range [0,150] into 30 intervals, each containing 5 samples(depth=5))
# Step 3 : Fill up bin values by one of three methods - bin means, bin medians, bin boundaries.


def preprocess():
    dataset = np.genfromtxt("data/iris.csv", delimiter=",")
    low, high = np.amin(dataset, axis=0), np.amax(dataset, axis=0)
    for j in range(4):
        minimum, maximum = low[j], high[j]
        for i in range(150):
            dataset[i][j] = (dataset[i][j] - minimum)/(maximum - minimum)
    data = dataset[:, 0]
    data = np.sort(data)
    return data


def bin_mean(data):
    bucket = np.zeros(shape=(30, 5))
    means = []
    for i in range(0, 150, 5):
        mean = (data[i] + data[i+1] + data[i+2] + data[i+3] + data[i+4]) / 5
        means.append(mean)
    for i in range(30):
        for j in range(5):
            bucket[i][j] = means[i]

    print("\nOutput from method of binning using means : \n")
    print(bucket)
    print("----------------------------------------------------------")
    return bucket


def bin_median(data):
    bucket = np.zeros(shape=(30, 5))
    medians = []
    for i in range(0, 150, 5):
        median = data[i+2]
        medians.append(median)
    for i in range(30):
        for j in range(5):
            bucket[i][j] = medians[i]
    print("\nOutput from method of binning using medians : \n")
    print(bucket)
    print("----------------------------------------------------------")
    return bucket


def bin_boundary(data):
    bucket = np.zeros(shape=(30, 5))
    for i in range(0, 150, 5):
        k = int(i/5)
        for j in range(5):
            if (data[i+j]-data[i]) < (data[i+4]-data[i+j]):
                bucket[k, j] = data[i]
            else:
                bucket[k, j] = data[i+4]

    print("\nOutput from method of binning using Bin Boundaries : \n")
    print(bucket)
    print("----------------------------------------------------------")
    return bucket


if __name__ == "__main__":
    data = preprocess()
    meanBins = bin_mean(data)
    medianBins = bin_median(data)
    boundaryBins = bin_boundary(data)
