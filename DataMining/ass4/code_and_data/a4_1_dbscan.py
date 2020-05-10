# importing requisites
import math 
import random
from urllib.request import urlretrieve
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from sklearn import datasets
from sklearn.cluster import DBSCAN
from sklearn.metrics import davies_bouldin_score
from sklearn.preprocessing import normalize,StandardScaler,MinMaxScaler
from sklearn.neighbors import NearestNeighbors

# loading dataset
# dataset_name= 'http://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data'
# urlretrieve(dataset_name)

# DBSCAN
def clusterDBSCAN(X,epsilon,minimum_samples):
    dbscan_clust=DBSCAN(eps=epsilon,min_samples=minimum_samples).fit(X) 
    labels=dbscan_clust.labels_ 
    return labels

# Silhoutte index
def getSilhoutteIndex(clusters,cols_to_be_ignored=[]):
    overall_sil_ind=0
    total_points=0
    for cluster_key in clusters:
        this_cluster=clusters[cluster_key]
        this_cluster_len=len(this_cluster)
        total_points+=this_cluster_len
        for data in this_cluster:
            sum_dists=0
            # we have to find a and b here
            for other_data in this_cluster:
                # get euclidean dist here between data and other_data
                dist=0
                for dim in range(len(data)):
                    if dim not in cols_to_be_ignored:
                        dist+=(data[dim]-other_data[dim])**2
                dist=math.sqrt(dist)
                sum_dists+=dist
            if this_cluster_len==1:
                a=0
            else:
                a=sum_dists/(this_cluster_len-1)
            # time to find b
            b=999999999
            for other_cluster_key in clusters:
                if other_cluster_key==cluster_key:
                    continue
                other_cluster=clusters[other_cluster_key]
                other_cluster_len=len(other_cluster)
                sum_dists1=0
                for other_cluster_data in other_cluster:
                    dist=0
                    for dim in range(len(data)):
                        if dim not in cols_to_be_ignored:
                            dist+=(data[dim]-other_cluster_data[dim])**2
                    dist=math.sqrt(dist)
                    sum_dists1+=dist
                b=min(b,sum_dists1/other_cluster_len)
            sil_ind=0
            if a!=b:
                sil_ind=(b-a)/max(a,b)
            overall_sil_ind+=sil_ind
    overall_sil_ind=overall_sil_ind/total_points
    return overall_sil_ind

# helper function (cluster is a list of np arrays; each np array containing attributes of that point)
def getCentroid(cluster):
    length=len(cluster)
    centroid=[]
    first=True
    for data in cluster:
        if first:
            first=False
            for i in range(len(data)):
                if np.isreal(data[i]):
                    centroid.append(data[i])
                else:
                    centroid.append(0)
            continue
        for i in range(len(data)):
            if np.isreal(data[i]):
                centroid[i]+=data[i]
            else:
                centroid[i]+=0
    centroid=np.asarray(centroid)
    centroid=centroid/length
    return centroid

# DB Index
def getDBIndex(X,labels):
    return davies_bouldin_score(X,labels)

# Dunn Index
def getDunnIndex(clusters,cols_to_be_ignored=[]):
    min_inter_clusters=9999999
    for cluster_key in clusters:
        prototype=getCentroid(clusters[cluster_key])
        for cluster_key1 in clusters:
            if cluster_key==cluster_key1:
                continue
            prototype1=getCentroid(clusters[cluster_key1])
            dist=0
            for dim in range(len(prototype)):
                if dim not in cols_to_be_ignored:
                    dist+=(prototype[dim]-prototype1[dim])**2
            dist=math.sqrt(dist)
            if min_inter_clusters>dist:
                min_inter_clusters=dist
    overall_max_intra_cluster=0
    for cluster_key in clusters:
        max_intra_cluster=0
        this_cluster=clusters[cluster_key]
        for data in this_cluster:
            for data1 in this_cluster:
                dist=0
                for dim in range(len(data)):
                    if dim not in cols_to_be_ignored:
                        dist+=(data[dim]-data1[dim])**2
                dist=math.sqrt(dist)
                if dist>max_intra_cluster:
                    max_intra_cluster=dist
        if max_intra_cluster>overall_max_intra_cluster:
            overall_max_intra_cluster=max_intra_cluster
    return min_inter_clusters/overall_max_intra_cluster

# call DBSCAN
dataset_name="iris.csv"
df=pd.read_csv(dataset_name)
scaler=MinMaxScaler() 
X=np.array(df.drop(["class"],1).astype(float))
# # helper code segment to determine epsilon
# # ==============start===============
# ns=4
# nbrs=NearestNeighbors(n_neighbors=ns).fit(X)
# distances,indices=nbrs.kneighbors(X)
# distanceDec=sorted(distances[:,ns-1],reverse=True)
# plt.plot(list(range(1,X.shape[0]+1)), distanceDec)
# plt.show()
# # ==============end==================
labels=clusterDBSCAN(X,0.8,10)

dataset_name1="wine.csv"
df1=pd.read_csv(dataset_name1)
scaler1=MinMaxScaler()
X1=np.array(scaler1.fit_transform(df1.drop(["class"],1).astype(float)))
labels1=clusterDBSCAN(X1,0.5,5)

dataset_name2="wdbc.csv"
df2=pd.read_csv(dataset_name2)
scaler2=MinMaxScaler() 
X2=np.array(scaler2.fit_transform(df2.drop(['class'],1).astype(float)))
labels2=clusterDBSCAN(X2,0.4,14)

# storing results
# format of results:
#   a dictionary with key as cluster number and,
#   value as a list of points in that cluster (each point is a np array of attributes)
clusters={}
n=0
for item in labels:
    if item in clusters:
        clusters[item].append(df.iloc[n].values)
    else:
        clusters[item]=[df.iloc[n].values]
    n+=1

clusters1={}
n1=0
for item in labels1:
    if item in clusters1:
        clusters1[item].append(df1.iloc[n1].values)
    else:
        clusters1[item]=[df1.iloc[n1].values]
    n1+=1

clusters2={}
n2=0
for item in labels2:
    if item in clusters2:
        clusters2[item].append(df2.iloc[n2].values)
    else:
        clusters2[item]=[df2.iloc[n2].values]
    n2+=1

# printing results
print("Iris:")
for item in clusters:
    print()
    print("Cluster ",item)
    print("Length: ",len(clusters[item]))
    # for i in clusters[item]:
    #     print(i)

print()
print("Wine:")
for item in clusters1:
    print()
    print("Cluster ",item)
    print("Length: ",len(clusters1[item]))
    # for i in clusters1[item]:
    #     print(i)

print()
print("WDBC:")
for item in clusters2:
    print()
    print("Cluster ",item)
    print("Length: ",len(clusters2[item]))
    # for i in clusters1[item]:
    #     print(i)

# deal with -1 index clusters before evaluating performance
del clusters[-1]
to_remove=[]
for i in range(len(labels)):
    if labels[i]==-1:
        to_remove.append(i)
X=np.delete(X,to_remove,0)
labels=np.delete(labels,to_remove)

del clusters1[-1]
to_remove1=[]
for i in range(len(labels1)):
    if labels1[i]==-1:
        to_remove1.append(i)
X1=np.delete(X1,to_remove1,0)
labels1=np.delete(labels1,to_remove1)

del clusters2[-1]
to_remove2=[]
for i in range(len(labels2)):
    if labels2[i]==-1:
        to_remove2.append(i)
X2=np.delete(X2,to_remove2,0)
labels2=np.delete(labels2,to_remove2)

# printing the indices
print()
print(getSilhoutteIndex(clusters,[4]))
print(getDBIndex(X,labels))
print(getDunnIndex(clusters,[4]))

print()
print(getSilhoutteIndex(clusters1,[0]))
print(getDBIndex(X1,labels1))
print(getDunnIndex(clusters1,[0]))

print()
print(getSilhoutteIndex(clusters2,[0]))
print(getDBIndex(X2,labels2))
print(getDunnIndex(clusters2,[0]))