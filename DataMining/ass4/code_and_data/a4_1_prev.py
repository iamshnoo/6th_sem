# importing requisites
import math
import random
from urllib.request import urlretrieve
import pandas as pd
import numpy as np
from sklearn import datasets
from sklearn.metrics import davies_bouldin_score

# loading dataset
# dataset_name= 'http://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data'
# urlretrieve(dataset_name)

# helper functions
def removeSublist(lst):
    res=lst[:]
    l=len(res)
    i=0
    while i<l:
        j=0
        while j<l:
            if i!=j:
                if set(res[i]).issubset(set(res[j])):
                    res.remove(res[i])
                    l-=1
                    i-=1
                    break
            j+=1
        i+=1
    return res

def intersect(lst,lst1):
    return len(set(lst)&set(lst1))

def union(lst,lst1):
    return len(set(lst)|set(lst1))

def getMean(df,clust,num_attrs):
    sum=[]
    for i in range(num_attrs):
        sum.append(0)
    packed_res=[]
    for v in clust:
        for x in range(num_attrs):
            sum[x]+=df.iloc[v,x]
    for i in range(num_attrs):
        packed_res.append(sum[i]/len(clust))
    return packed_res

def getInverseDist(p1,p2,num_attrs):
    sum=0
    for i in range(num_attrs):
        sum+=(p1[i]-p2[i])**2
    return 1/math.sqrt(sum)

# clustering function
def clusterPrev(df,reqd_clusters,num_instances,num_attrs):
    # form diss_mat
    diss_mat=[]
    for i in range(num_instances):
        temp=[]
        for j in range(num_instances):
            temp.append(0)
        diss_mat.append(temp)
    for i in range(num_instances):
        for j in range(i+1,num_instances):
            dist=0
            for k in range(num_attrs):
                dist+=(df.iloc[i,k]-df.iloc[j,k])**2
            dist=math.sqrt(dist)
            diss_mat[i][j]=dist
            diss_mat[j][i]=dist

    # avg dissimilarity
    avg_diss=[]
    for i in range(num_instances):
        sum=0
        for j in range(num_instances):
            sum+=diss_mat[i][j]
        avg_diss.append(sum/num_instances)

    # initial clusters
    clusters=[]
    for i in range(num_instances):
        cluster=[]
        cluster.append(i)
        for j in range(0,i):
            if diss_mat[i][j]<avg_diss[i]:
                cluster.append(j)
        for j in range(i+1,num_instances):
            if diss_mat[i][j]<avg_diss[i]:
                cluster.append(j)
        clusters.append(cluster)

    # merging clusters
    count=num_instances
    new_clusters=[]
    while count!=reqd_clusters:
        clusters_after_removal=removeSublist(clusters)

        num_clusters=len(clusters_after_removal)
        sim_matrix=[[1 for x in range(num_clusters)] for y in range(num_clusters)]

        #fill up this matrix
        for i in range(num_clusters):
            for j in range(i,num_clusters):
                sim_matrix[i][j]=intersect(clusters_after_removal[i],clusters_after_removal[j])/union(clusters_after_removal[i],clusters_after_removal[j])
                if i==j:
                    continue
                sim_matrix[j][i]=sim_matrix[i][j]

        #find max sim_matrix[i][j] and merge clusters[i] and clusters[j]
        max=0
        for lst in sim_matrix:
            for x in lst:
                if x>max:
                    max=x
        max_value_locs=np.argwhere(np.array(sim_matrix)==max)
        random_loc=random.choice(max_value_locs)

        #merge Ci and Cj where i and j are given in random_loc
        new_clusters=clusters_after_removal[:]
        i=random_loc[0]
        j=random_loc[1]
        for cluster_val in clusters_after_removal[j]:
            if cluster_val not in new_clusters[i]:
                new_clusters[i].append(cluster_val)
        del new_clusters[j]
        count=len(new_clusters)

        clusters=new_clusters[:]

    # last step
    x=[]
    for i in range(num_attrs):
        temp=[]
        for j in range(num_instances):
            temp.append(0)
        x.append(temp)
    for i in range(num_attrs):
        for j in range(num_instances):
            x[i][j]=df.iloc[j,i]

    # final clusters
    clustern=[]
    for i in range(reqd_clusters):
        clustern.append([])

    # means
    m=[]
    for i in range(reqd_clusters):
        m.append(getMean(df,clusters[i],num_attrs))

    for i in range(num_instances):
        coords_of_i=[]
        dist=[]
        for i1 in range(reqd_clusters):
            dist.append(0)
        max=-99999
        for i1 in range(num_attrs):
            coords_of_i.append(x[i1][i])
        for i1 in range(reqd_clusters):
            if i in clusters[i1]:
                dist[i1]=getInverseDist(coords_of_i,m[i1],num_attrs)
        insert_here=0
        for i1 in range(reqd_clusters):
            if dist[i1]>max:
                max=dist[i1]
                insert_here=i1
        clustern[insert_here].append(i)

    # # printing result
    # for i in range(reqd_clusters):
    #     print("\nCluster ",i," :")
    #     print(clustern[i])
    # print("\nSizes: \n")
    # for i in range(reqd_clusters):
    #     print(str(len(clustern[i])))

    # build the result to be returned
    labels=[]
    for i in range(num_instances):
        labels.append(0)
    for i in range(reqd_clusters):
        for val in clustern[i]:
            labels[val]=i
    return labels

# Silhoutte index
def getSilhoutteIndex(clusters,cols_to_be_ignored):
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
def getDunnIndex(clusters,cols_to_be_ignored):
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

# normalize and call clustering algo
reqd_clusters=3
dataset_name="iris.csv"
df=pd.read_csv(dataset_name)
df_n=df.drop(['class'],1).astype(float)
num_instances=df_n.shape[0]
num_attrs=df_n.shape[1] # apart from class label
min_values=df_n.min()
max_values=df_n.max()
for index,row in df_n.iterrows():
    for ind in range(num_attrs):
        df_n.iloc[index,ind]=(df_n.iloc[index,ind]-min_values[ind])/(max_values[ind]-min_values[ind])
labels=clusterPrev(df_n,reqd_clusters,num_instances,num_attrs)
X=np.array(df_n)

reqd_clusters1=2
dataset_name1="bcw.csv"
df1=pd.read_csv(dataset_name1)
df_n1=df1.drop(['class'],1).astype(float)
num_instances1=df_n1.shape[0]
num_attrs1=df_n1.shape[1] # apart from class label
min_values1=df_n1.min()
max_values1=df_n1.max()
for index,row in df_n1.iterrows():
    for ind in range(num_attrs1):
        df_n1.iloc[index,ind]=(df_n1.iloc[index,ind]-min_values1[ind])/(max_values1[ind]-min_values1[ind])
# using only first 200
labels1=clusterPrev(df_n1,reqd_clusters1,num_instances1,num_attrs1)
X1=np.array(df_n1)

reqd_clusters2=3
dataset_name2="seeds_dataset.csv"
df2=pd.read_csv(dataset_name2)
df_n2=df2.drop(['class'],1).astype(float)
num_instances2=df_n2.shape[0]
num_attrs2=df_n2.shape[1] # apart from class label
min_values2=df_n2.min()
max_values2=df_n2.max()
for index,row in df_n2.iterrows():
    for ind in range(num_attrs2):
        df_n2.iloc[index,ind]=(df_n2.iloc[index,ind]-min_values2[ind])/(max_values2[ind]-min_values2[ind])
labels2=clusterPrev(df_n2,reqd_clusters2,num_instances2,num_attrs2)
X2=np.array(df_n2)

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
print("BCW:")
for item in clusters1:
    print()
    print("Cluster ",item)
    print("Length: ",len(clusters1[item]))
    # for i in clusters1[item]:
    #     print(i)

print()
print("Seeds:")
for item in clusters2:
    print()
    print("Cluster ",item)
    print("Length: ",len(clusters2[item]))
    # for i in clusters2[item]:
    #     print(i)

# printing the indices
print()
print(getSilhoutteIndex(clusters,[4]))
print(getDBIndex(X,labels))
print(getDunnIndex(clusters,[4]))

print()
print(getSilhoutteIndex(clusters1,[9]))
print(getDBIndex(X1,labels1))
print(getDunnIndex(clusters1,[9]))

print()
print(getSilhoutteIndex(clusters2,[7]))
print(getDBIndex(X2,labels2))
print(getDunnIndex(clusters2,[7]))