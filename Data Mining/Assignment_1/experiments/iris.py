import numpy as np

'''
Collect any dataset without decision attribute. The dataset may be collected from UCI machine
learning repository.

wget http://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data   
'''
data = np.genfromtxt('iris.csv', delimiter=',')

'''
Let the dataset has m rows and n columns where, each row is an object and each column is an
attribute or feature of the object in the dataset. So you can consider the dataset as an mn matrix.
'''
m = 150
n = 4

'''
Normalize the attribute values within the range [0,1] using any normalization technique to give all
the attributes an equal importance.
'''
low = np.amin(data, axis=0)
high = np.amax(data, axis=0)
for j in range(n):
    minimum = low[j]
    maximum = high[j]
    for i in range(m):
        data[i][j] = (data[i][j] - minimum)/(maximum - minimum)

'''
Create a similarity matrixSof size m*m where, each (i, j)-th entry in the matrix gives the
dissimilarity measurement between i-th and j-th objects. Use Eucledian distance to measure the
dissimilarity.
'''

mat = np.zeros(shape=(m, m))
for i in range(m):
    for j in range(m):
        mat[i, j] = ((data[i][0] - data[j][0])**2 + (data[i][1] - data[j][1]
                                                     )**2 + (data[i][2] - data[j][2])**2 + (data[i][3] - data[j][3])**2)
        mat[i, j] = mat[i, j]**0.5


'''
The i-th row indicates similarity of i-th object with all other objects. Find the average dissimilarity
of i-th object with other objects and form a cluster Ci with i-th object and objects having dissimilarity
less than the average similarity. Repeat this process for all rows of the similarity matrix. Thus, you
have now m clusters.
'''
avg = np.zeros(shape=(m))
for i in range(m):
    for j in range(m):
        avg[i] += mat[i][j]
    avg[i] = avg[i] / m

clusters = []
for i in range(m):
    cluster = []
    for j in range(m):
        if(mat[i][j] < avg[j]):
            cluster.append(j)
    clusters.append(cluster)
clusters = np.asarray(clusters)
# storing a copy of the orginal, in case it is needed later
cluster_original = clusters

'''
Remove the clusters (if any) which are subset of some other clusters. As a result you have now say,
p (<m) clusters.
'''

idx = []
for i in range(m):
    for j in range(m):
        if(i != j):
            if(len(np.setdiff1d(clusters[i], clusters[j])) == 0):
                for k in range(len(clusters[j])):
                    clusters[j][k] = 0
                idx.append(j)
idx = np.unique(idx)
clusters = np.delete(clusters, idx, 0)

'''
Create a similarity matrix C of size pXp where, each (i, j)-th entry in the matrix gives the similarity
measurement between i-th cluster Ci and j-th cluster Cj using following similarity measure.
Cij =|Ci ∩ Cj|/|Ci ∪ Cj|
'''
p = len(clusters)
sim = np.zeros(shape=(p, p))
for i in range(p):
    for j in range(p):
        sim[i, j] = len(np.intersect1d(clusters[i], clusters[j])
                        ) / len(np.union1d(clusters[i], clusters[j]))

'''
Out of all p*p entries in matrix C, find out the maximum value. If multiple maximum values occur,
choose any one randomly. Let, Ckl is the maximum value selected, that implies clusters Ck and Cl are
the most similar clusters among all p clusters. Merge these two clusters Ck and Cl to get a new cluster
Ckl, i.e. Ckl = Ck U Cl.
'''
val = 0
idx_k = 0
idx_l = 0
for i in range(p):
    for j in range(p):
        if(i != j):
            if(sim[i, j] > val):
                val = sim[i, j]
                idx_k = i
                idx_l = j

merged_clusters = np.union1d(clusters[idx_k], clusters[idx_l])
ids = [idx_k, idx_l]
clusters = np.delete(clusters, ids, 0)
# clusters.append(merged_clusters) --> does not work
dummy = [[] for _ in range(len(clusters))]
for i in range(len(clusters)):
    for j in range(len(clusters[i])):
        dummy[i].append(clusters[i][j])
dummy.append(merged_clusters)
clusters = dummy
