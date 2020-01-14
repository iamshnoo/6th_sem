import numpy as np
import sys

class Iris:

    def __init__(self):
        self.m = 150
        self.n = 4
        self.k = 3

    def getK(self):
        return self.k

    def getData(self):

        try:
            data = np.genfromtxt('iris.csv', delimiter=',')
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
                # mat[i, j]= np.linalg.norm(data[i] - data[j]) --> this is slow
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
                sim[i, j] = len(list(set(clusters[i]) & set(clusters[j]))) / \
                    len(list(set(clusters[i]) | set(clusters[j])))
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
        if(len(clusters)==self.k):
            print(str(len(clusters[0])) + ", " + str(len(clusters[1])) + ", " +
                  str(len(clusters[2])) + " are the sizes of the three clusters.")
            
        return clusters

    @classmethod
    def similarity_measure(cls,num1,num2):
        return abs(np.log(num1)-np.log(num2))
     
    def kMeansClustering(self, clusters):
        print("---------------------------------------------------------------")
        print("Now removing duplicates in clusters by re-clustering based on similarity to mean of the clusters formed.")
        mean = []
        for i in range(self.k):
            sum = 0
            for j in range(len(clusters[i])):
                sum += clusters[i][j]
            mean.append(sum/len(clusters[i]))
   
        locations = [[] for _ in range(self.m)]
        for i in range(self.m):
            for j in range(len(clusters)):
                for k in range(len(clusters[j])):
                    if (clusters[j][k] == i):
                        locations[i].append(j)
                        break

        dummy = [[] for _ in range(len(clusters))]
        for i in range(self.m):
            # to suppress warning in similarity function 
            # RuntimeWarning: divide by zero encountered in log
            if (i==0):
                dummy[i].append(i)
            else:
                obj = i
                max_similarity = 0
                max_similarity_idx = -1  
                for j in range(len(locations[i])):
                    location = locations[i][j]  
                    for k in range(len(clusters[location])):                  
                        if (clusters[location][k] == obj):                      
                            num1 = clusters[location][k]
                            num2 = mean[location]
                            similarity = Iris.similarity_measure(num1, num2) 
                            if (similarity > max_similarity):
                                max_similarity = similarity
                                max_similarity_idx = location
                            break
                dummy[max_similarity_idx].append(i)

        clusters = dummy
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
        return clusters

if __name__ == "__main__":
    model = Iris()
    data = Iris.getData(model)
    data = Iris.normalizeData(model, data)
    mat = Iris.getDissimilarityMatrix(model, data)
    clusters = Iris.cluster(model, mat)
    cluster_original = clusters
    while(len(clusters) != Iris.getK(model)):
        clusters = Iris.removeSubsetClusters(model, clusters)
        sim = Iris.getSimilarityMatrix(model, clusters)
        clusters = Iris.mergeMaxSimilarityClusters(model, sim, clusters)
    clusters = Iris.kMeansClustering(model, clusters)
    exit(0)
