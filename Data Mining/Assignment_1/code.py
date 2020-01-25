#!/usr/bin/env python
# coding: utf-8

# ## Data Mining Assignment 1
# 
# *Anjishnu Mukherjee [510517086(B05-511017020)]*

# The following class Iris defines each of the functions separately as mentioned in the assignment sheet.

# In[1]:


import pandas as pd
import numpy as np
import sys
import seaborn as sns
import matplotlib.pyplot as plt
get_ipython().run_line_magic('matplotlib', 'inline')

class Iris:

    def __init__(self,k):
        self.m = 150
        self.n = 4
        self.k = k

    def getK(self):
        return self.k

    def getData(self):

        try:
            data = np.genfromtxt('data/iris.csv', delimiter=',')
            print("Data source available.")
        except IOError:
            print("Missing dataset! Run:")
            print(
                "wget http://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data")
            exit(0)
        print("Shape of original data : " + str(len(data)) +
              ", " + str(len(data[0])))
        return data

    def normalizeData(self, data):
        print("Normalizing the data to to range [0,1] now...")
        low, high = np.amin(data, axis=0), np.amax(data, axis=0)
        for j in range(self.n):
            minimum, maximum = low[j], high[j]
            for i in range(self.m):
                data[i][j] = (data[i][j] - minimum)/(maximum - minimum)
        print("Shape of the normalized data : " +
              str(len(data)) + ", " + str(len(data[0])))
        return data

    def getDissimilarityMatrix(self, data):
        print("Preparing dissimilarity matrix...")
        mat = np.zeros(shape=(self.m, self.m))
        for i in range(self.m):
            for j in range(self.m):
                mat[i, j] = ((data[i][0] - data[j][0])**2 + (data[i][1] - data[j][1]
                                                             )**2 + (data[i][2] - data[j][2])**2 + (data[i][3] - data[j][3])**2)**0.5
        print("Shape of the Dissimilarity Matrix : " +
              str(len(mat)) + ", " + str(len(mat[0])))
        return mat

    def cluster(self, mat):
        print("Calculating average dissimilarity values for each object...")
        avg = np.mean(mat, axis=0)
        print("Primary clustering...")
        clusters = []
        for i in range(self.m):
            cluster = []
            for j in range(self.m):
                if(mat[i][j] < avg[i]):
                    cluster.append(j)
            clusters.append(cluster)
        print(str(len(clusters)) + " primary clusters formed.")
        print("---------------------------------------------------------------")
        return clusters

    def removeSubsetClusters(self, clusters):
        print("Removing clusters which are a subset of other clusters...")
        num_clusters = len(clusters)
        i = 0
        while i < num_clusters:
            j = 0
            while j < num_clusters:
                if i != j:
                    if (set(clusters[i]).issubset(set(clusters[j]))):
                        clusters.remove(clusters[i])
                        num_clusters -= 1
                        i -= 1
                        break
                j += 1
            i += 1
        return clusters

    def getSimilarityMatrix(self, clusters):
        print("Creating similarity matrix...")
        p = len(clusters)
        sim = np.zeros(shape=(p, p))
        for i in range(p):
            for j in range(p):
                sim[i, j] = len(list(set(clusters[i]) & set(clusters[j]))) /                     len(list(set(clusters[i]) | set(clusters[j])))
        print("Shape of the Similarity Matrix : " +
              str(len(sim)) + ", " + str(len(sim[0])))
        return sim

    def mergeMaxSimilarityClusters(self, sim, clusters):
        print("Merging clusters having maximum similarity...")
        print(print(str(len(clusters)) + " clusters found."))
        val = 0
        idx_k = -1
        idx_l = -1
        p = len(clusters)
        for i in range(p):
            for j in range(p):
                if(i != j):
                    if(sim[i, j] >= val):
                        val = sim[i, j]
                        idx_k = i
                        idx_l = j

        clusters[idx_k] = list(set(clusters[idx_k]) | set(clusters[idx_l]))
        clusters.remove(clusters[idx_l])

        print(str(val) + " is the maximum similarity value and clusters " +
              str(idx_k) + ", " + str(idx_l) + " are the most similar.")
        print(str(len(clusters)) + " clusters left after this iteration.")
        print("---------------------------------------------------------------")
        if(len(clusters) == self.k):
            if (self.k==3):
                print(str(len(clusters[0])) + ", " + str(len(clusters[1])) + ", " +
                    str(len(clusters[2])) + " are the sizes of the three clusters.")
            if(self.k==2):
                print(str(len(clusters[0])) + ", " + str(len(clusters[1])) + " are the sizes of the three clusters.")

        return clusters

    @classmethod
    def similarity_measure(cls, num1, num2):
        return abs(num1-num2)

    def notkMeansClustering(self, clusters, data):
        prob = []
        for i in range(self.m):
            temp = []
            for j in range(len(clusters)):
                temp.append(0)
            prob.append(temp)

        mean = []
        for i in range(len(clusters)):
            x = len(clusters[i])
            sumtemp = []
            for k in range(self.n):
                z = 0
                for j in range(x):
                    z += data[clusters[i][j]][k]
                    prob[clusters[i][j]][i] = 1
                z = z/x
                sumtemp.append(z)
            mean.append(sumtemp)

        dummy = [[]for _ in range(len(clusters))]
        dummy[0].append(0)
        for i in range(self.m):
            if (i == 0):
                continue
            len1 = 10000000.0
            meanind = 0
            for j in range(len(clusters)):
                if(prob[i][j] == 0):
                    continue
                else:
                    tempmean = 0
                    for k in range(self.n):
                        tempmean += (data[i][k]-mean[j][k])**2
                    tempmean = tempmean**0.5
                    if len1 > (tempmean):
                        len1 = tempmean
                        meanind = j
            dummy[meanind].append(i)
        clusters = dummy
        
        if(self.k==3):
            print(str(len(clusters[0])) + ", " + str(len(clusters[1])) + ", " +
                str(len(clusters[2])) + " are the sizes of the three final clusters.\n")
            print("Cluster 1 : \n")
            print(clusters[0])
            print("\n")
            print("Cluster 2 : \n")
            print(clusters[1])
            print("\n")
            print("Cluster 3 : \n")
            print(clusters[2])
            print("\n")

        if(self.k==2):
            print(str(len(clusters[0])) + ", " + str(len(clusters[1])) + " are the sizes of the two final clusters.\n")
            print("Cluster 1 : \n")
            print(clusters[0])
            print("\n")
            print("Cluster 2 : \n")
            print(clusters[1])
            print("\n")

        return clusters
    
    @classmethod
    def label(cls, clusters):
        # y_pred will contain the predicted class labels for the objects
        y_pred = []
        for i in range(150):
            # y[i] will indicate that i belongs to cluster-j
            obj = i
            for j in range(len(clusters)):
                for k in range(len(clusters[j])):
                    if clusters[j][k] == obj:
                        y_pred.append(j)

        # y_true has the true class labels corresponding to each object
        y_true = []
        for i in range(150):
            if len(clusters) == 3:
                if i in range(0,51):
                    y_true.append(0)
                elif i in range(51,101):
                    y_true.append(1)
                else :
                    y_true.append(2)
            else:
                if i in range(0,76):
                    y_true.append(0)
                else:
                    y_true.append(1)

        return y_true, y_pred

    def plot(self, clusters, i , j):
        print("Considering features " + str(i) + " and " + str(j))
        y_true, y_pred = Iris.label(clusters)
        data = np.genfromtxt('data/iris.csv', delimiter=',')
        df_true = pd.DataFrame({'Feature_X': data[:, i], 'Feature_Y': data[:, j], 'true class': y_true})
        df_pred = pd.DataFrame({'Feature_X': data[:, i], 'Feature_Y': data[:, j], 'predicted class': y_pred})
        true_plot = sns.lmplot(data=df_true, x='Feature_X', y='Feature_Y', hue='true class', fit_reg=False, legend=True, legend_out=True)
        predicted_plot = sns.lmplot(data=df_pred, x='Feature_X', y='Feature_Y', hue='predicted class', fit_reg=False, legend=True, legend_out=True)
        print("----------------------------------------------------------------------------------------------------------------------------------")
        return

    def pair_plot_true(self, clusters):
        y_true, _ = Iris.label(clusters)
        data = np.genfromtxt('data/iris.csv', delimiter=',')
        df_true = pd.DataFrame({'sepal length': data[:, 0], 'sepal width': data[:, 1], 'petal length': data[:, 2], 'petal width': data[:, 3], 'True class': y_true})
        sns.pairplot(df_true, vars=df_true.columns[:-1], hue='True class')
        return

    def pair_plot_pred(self, clusters):
        y_true, y_pred = Iris.label(clusters)
        data = np.genfromtxt('data/iris.csv', delimiter=',')
        df_pred = pd.DataFrame({'sepal length': data[:, 0], 'sepal width': data[:, 1], 'petal length': data[:, 2], 'petal width': data[:, 3], 'Predicted class': y_pred})
        sns.pairplot(df_pred, vars=df_pred.columns[:-1], hue='Predicted class')
        return

model = Iris(3)
data = Iris.getData(model)
data = Iris.normalizeData(model, data)
mat = Iris.getDissimilarityMatrix(model, data)
clusters = Iris.cluster(model, mat)
cluster_original = clusters
while(len(clusters) != Iris.getK(model)):
    clusters = Iris.removeSubsetClusters(model, clusters)
    sim = Iris.getSimilarityMatrix(model, clusters)
    clusters = Iris.mergeMaxSimilarityClusters(model, sim, clusters)
clusters = Iris.notkMeansClustering(model, clusters, data)


# Now, we instantiate the model for the case of k=3 and run all the clustering steps.

# In[ ]:


model = Iris(3)
data = Iris.getData(model)
data = Iris.normalizeData(model, data)
mat = Iris.getDissimilarityMatrix(model, data)
clusters = Iris.cluster(model, mat)
cluster_original = clusters
while(len(clusters) != Iris.getK(model)):
    clusters = Iris.removeSubsetClusters(model, clusters)
    sim = Iris.getSimilarityMatrix(model, clusters)
    clusters = Iris.mergeMaxSimilarityClusters(model, sim, clusters)
clusters = Iris.notkMeansClustering(model, clusters, data)


# We plot graphs between each pair of features as per original data points

# In[2]:


Iris.pair_plot_true(model, clusters)


# We plot graphs between each pair of features as per predicted data points in the clusters

# In[3]:


Iris.pair_plot_pred(model, clusters)


# Now, we instantiate the model for the case of k=2 and run all the clustering steps.

# In[4]:


model = Iris(2)
data = Iris.getData(model)
data = Iris.normalizeData(model, data)
mat = Iris.getDissimilarityMatrix(model, data)
clusters = Iris.cluster(model, mat)
cluster_original = clusters
while(len(clusters) != Iris.getK(model)):
    clusters = Iris.removeSubsetClusters(model, clusters)
    sim = Iris.getSimilarityMatrix(model, clusters)
    clusters = Iris.mergeMaxSimilarityClusters(model, sim, clusters)
clusters = Iris.notkMeansClustering(model, clusters, data)


# We plot graphs between each pair of features as per original data points

# In[5]:


Iris.pair_plot_true(model, clusters)


# We plot graphs between each pair of features as per predicted data points in the clusters

# In[6]:


Iris.pair_plot_pred(model, clusters)


# Clearly from all these graphs, it becomes evident that cluster-0 (Iris-setosa) is linearly separable from the other two clusters, which are not linearly separable. Also, the algorithm developed is very effective in predictions, because the final predictions are very similar in nature to the actual data points.

# 
