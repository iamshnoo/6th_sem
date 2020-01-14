from models.model import Iris

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
    clusters = Iris.notkMeansClustering(model, clusters)
    exit(0)
