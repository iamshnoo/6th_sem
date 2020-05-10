# Assignment 4

## Anjishnu Mukherjee B05-511017020 (510517086)

## May 2020

### Datasets Used

- [Iris Dataset](https://archive.ics.uci.edu/ml/datasets/iris)
- [Wine Dataset](https://archive.ics.uci.edu/ml/datasets/wine)
- [Seeds Dataset](https://archive.ics.uci.edu/ml/datasets/seeds)
- [Breast Cancer Wisconsin Dataset](https://www.kaggle.com/uciml/breast-cancer-wisconsin-data)
- [Haberman's Survival Dataset](https://archive.ics.uci.edu/ml/datasets/Haberman's+Survival)
- [Pima Indian Diabetes Dataset](https://archive.ics.uci.edu/ml/support/diabetes)
- [BankNote Authentication Dataset](https://archive.ics.uci.edu/ml/datasets/banknote+authentication)

All the datasets are taken from the well-known UCI Machine Learning repository.

### Task 1 - Cluster Analysis

DBSCAN and Infomap don't work too well with the Seeds Dataset and thus we use
the Wine Dataset in its place for those 2 algorithms. The Iris Dataset and the
Breast Cancer Wisconsin Dataset has been used for all clustering algorithms.

#### K-Means Algorithm

- **Iris Dataset**

  Cluster 1 -> Length = 50 <br>
  Cluster 2 -> Length = 53 <br>
  Cluster 3 -> Length = 47 <br>

  Cluster validation Indices (rounded to 4 decimal places): <br>
  Silhouette Index = 0.5059 <br>
  Davies Bouldin Index = 0.8354 <br>
  Dunne Index = 0.5303 <br>

- **Breast Cancer Wisconsin Dataset**

  Cluster 1 -> Length = 230 <br>
  Cluster 2 -> Length = 453 <br>

  Cluster validation Indices (rounded to 4 decimal places): <br>
  Silhouette Index = 0.5939 <br>
  Davies Bouldin Index = 0.8200 <br>
  Dunne Index = 0.6417 <br>

- **Seeds Dataset**

  Cluster 1 -> Length = 67 <br>
  Cluster 2 -> Length = 71 <br>
  Cluster 3 -> Length = 72 <br>

  Cluster validation Indices (rounded to 4 decimal places): <br>
  Silhouette Index = 0.4506 <br>
  Davies Bouldin Index = 0.9279 <br>
  Dunne Index = 0.5000 <br>

#### DBSCAN Algorithm

Graph for determining optimum epsilon value using grid search.

<p align="center">
  <img src="graphs/determine_epsilon.png" width="300" height="200"
</p>

- **Iris Dataset**

  Cluster 1 -> Length = 5 <br>
  Cluster 2 -> Length = 50 <br>
  Cluster 3 -> Length = 95 <br>

  Cluster validation Indices (rounded to 4 decimal places): <br>
  Silhouette Index = 0.5336 <br>
  Davies Bouldin Index = 0.5262 <br>
  Dunne Index = 0.5813 <br>

- **Breast Cancer Wisconsin Dataset**

  Cluster 1 -> Length = 183 <br>
  Cluster 2 -> Length = 35 <br>
  Cluster 3 -> Length = 351 <br>

  Cluster validation Indices (rounded to 4 decimal places): <br>
  Silhouette Index = 0.2712 <br>
  Davies Bouldin Index = 2.5451 <br>
  Dunne Index = 0.0556 <br>

- **Wine Dataset**

  Cluster 1 -> Length = 23 <br>
  Cluster 2 -> Length = 104 <br>
  Cluster 3 -> Length = 51 <br>

  Cluster validation Indices (rounded to 4 decimal places): <br>
  Silhouette Index = - 0.0554 <br>
  Davies Bouldin Index = 3.0640 <br>
  Dunne Index = 0.0148 <br>

#### Infomap Algorithm

Infomap is a graph-based clustering algorithm where each data point can be
treated as a node with edges connecting pairs of them. The weight of an edge
corresponds to the euclidean distance between them.

For the implementation, an average value of edge weights is determined and
all edges with weights less than that are dropped. The final set of edges
(in a .gml file) is given as input to ​igraph’s community_infomap.​

- **Iris Dataset**

  Cluster 1 -> Length = 52 <br>
  Cluster 2 -> Length = 97 <br>
  Cluster 3 -> Length = 1 <br>

  Cluster validation Indices (rounded to 4 decimal places):
  Silhouette Index = 0.4218 <br>
  Davies Bouldin Index = 0.4220 <br>
  Dunne Index = 0.4664 <br>

- **Breast Cancer Wisconsin Dataset**

  Cluster 1 -> Length = 460 <br>
  Cluster 2 -> Length = 216 <br>
  Cluster 3 -> Length = 6 <br>
  Cluster 4 -> Length = 1 <br>

  Cluster validation Indices (rounded to 4 decimal places): <br>
  Silhouette Index = 0.3982 <br>
  Davies Bouldin Index = 1.0675 <br>
  Dunne Index = 0.4026 <br>

- **Wine Dataset**

  Cluster 1 -> Length = 47 <br>
  Cluster 2 -> Length = 131 <br>

  Cluster validation Indices (rounded to 4 decimal places): <br>
  Silhouette Index = 0.6572 <br>
  Davies Bouldin Index = 0.4565 <br>
  Dunne Index = 0.8579 <br>

#### Clustering Algorithm developed in Assignment-1

- **Iris Dataset**

  Cluster 1 -> Length = 86 <br>
  Cluster 2 -> Length = 50 <br>
  Cluster 3 -> Length = 14 <br>

  Cluster validation Indices (rounded to 4 decimal places): <br>
  Silhouette Index = 0.0309 <br>
  Davies Bouldin Index = 2.2610 <br>
  Dunne Index = 0.1293 <br>

- **Breast Cancer Wisconsin Dataset**

  Only the first 200 data points are used to reduce the extensive computation
  time needed by this algorithm.

  Cluster 1 -> Length = 135 <br>
  Cluster 2 -> Length = 63 <br>

  Cluster validation Indices (rounded to 4 decimal places): <br>
  Silhouette Index = 0.4415 <br>
  Davies Bouldin Index = 1.0738 <br>
  Dunne Index = 0.4662 <br>

- **Seeds Dataset**

  Cluster 1 -> Length = 39 <br>
  Cluster 2 -> Length = 58 <br>
  Cluster 3 -> Length = 113 <br>

  Cluster validation Indices (rounded to 4 decimal places): <br>
  Silhouette Index = 0.3599 <br>
  Davies Bouldin Index = 1.1377 <br>
  Dunne Index = 0.3642 <br>

### Task-2 : Classification Analysis

10 fold cross validation is done for all cases. The intermediate results are not
presented here for brevity, only the final results are given for each case.

#### Decision Tree

- **BankNote Authentication Dataset**

  Accuracy:  0.982497619803237 <br>
  Specificity:  0.9828352222510384 <br>
  Sensitivity:  0.9820866935483871 <br>
  Precision:  0.9789299717514691 <br>
  F-measure:  0.9803762035555337 <br>
  Prediction:  760   612 <br>
  Actual Class label:  762   610 <br>

  <p align="center">
    <img src="graphs/idc_bank.png" width="300" height="200"
  </p>

- **Breast Cancer Wisconsin Dataset**

  Accuracy:  0.9501705029838023 <br>
  Specificity:  0.9614337520630845 <br>
  Sensitivity:  0.930331616853356 <br>
  Precision:  0.9305259595476987 <br>
  F-measure:  0.9290235519235841 <br>
  Prediction:  444   239 <br>
  Actual Class label:  444   239 <br>

  <p align="center">
    <img src="graphs/idc_breast.png" width="300" height="200"
  </p>

- **Haberman's Survival Dataset**

  Accuracy:  0.666236559139785 <br>
  Specificity:  0.7749470217044588 <br>
  Sensitivity:  0.4202633477633477 <br>
  Precision:  0.37238095238095237 <br>
  F-measure:  0.3753861369109047 <br>
  Prediction:  225   81 <br>
  Actual Class label:  225   81 <br>

  <p align="center">
    <img src="graphs/idc_haberman.png" width="300" height="200"
  </p>

- **Pima Indian Diabetes Dataset**

  Accuracy:  0.7031100478468899 <br>
  Specificity:  0.7805294970986459 <br>
  Sensitivity:  0.5661191805715133 <br>
  Precision:  0.5792382641253608 <br>
  F-measure:  0.5662043283931991 <br>
  Prediction:  508   260 <br>
  Actual Class label:  500   268 <br>

  <p align="center">
    <img src="graphs/idc_indian.png" width="300" height="200"
  </p>

#### Naïve Bayes

- **BankNote Authentication Dataset**

  Accuracy:  0.8389664656722733 <br>
  Specificity:  0.8787525628364371 <br>
  Sensitivity:  0.7926724168785175 <br>
  Precision:  0.8386117247270881 <br>
  F-measure:  0.8132050044960154 <br>
  Prediction:  797   575 <br>
  Actual Class label:  762   610 <br>

  <p align="center">
    <img src="graphs/nb_bank.png" width="300" height="200"
  </p>

- **Breast Cancer Wisconsin Dataset**

  Accuracy:  0.9633205456095482 <br>
  Specificity:  0.9558769143796896 <br>
  Sensitivity:  0.9802900137232973 <br>
  Precision:  0.9233205240813935 <br>
  F-measure:  0.9488355568988098 <br>
  Prediction:  429   254 <br>
  Actual Class label:  444   239 <br>

  <p align="center">
    <img src="graphs/nb_breast.png" width="300" height="200"
  </p>

- **Haberman's Survival Dataset**

  Accuracy:  0.7450537634408602 <br>
  Specificity:  0.9385720873329569 <br>
  Sensitivity:  0.211019536019536 <br>
  Precision:  0.5511904761904762 <br>
  F-measure:  0.28564102564102567 <br>
  Prediction:  275   31 <br>
  Actual Class label:  225   81 <br>

  <p align="center">
    <img src="graphs/nb_haberman.png" width="300" height="200"
  </p>

- **Pima Indian Diabetes Dataset**

  Accuracy:  0.7592105263157896 <br>
  Specificity:  0.8425872995663299 <br>
  Sensitivity:  0.6082767775518201 <br>
  Precision:  0.6692941963084392 <br>
  F-measure:  0.6330167235470293 <br>
  Prediction:  527   241 <br>
  Actual Class label:  500   268 <br>

  <p align="center">
    <img src="graphs/nb_indian.png" width="300" height="200"
  </p>

#### KNN

- **BankNote Authentication Dataset**

  Accuracy:  0.9956310166084841 <br>
  Specificity:  0.9921013090555345 <br>
  Sensitivity:  1.0 <br>
  Precision:  0.9904764638346727 <br>
  F-measure:  0.9951569442389516 <br>
  Prediction:  756   616 <br>
  Actual Class label:  762   610 <br>

  <p align="center">
    <img src="graphs/knn_bank.png" width="300" height="200"
  </p>

- **Breast Cancer Wisconsin Dataset**

  Accuracy:  0.9663682864450127 <br>
  Specificity:  0.9748283800563758 <br>
  Sensitivity:  0.9536729797979799 <br>
  Precision:  0.956188961900169 <br>
  F-measure:  0.9538943469414246 <br>
  Prediction:  445   238 <br>
  Actual Class label:  444   239 <br>

  <p align="center">
    <img src="graphs/knn_breast.png" width="300" height="200"
  </p>

- **Haberman's Survival Dataset**

  Accuracy:  0.725268817204301 <br>
  Specificity:  0.9324858886346302 <br>
  Sensitivity:  0.16428571428571428 <br>
  Precision:  0.44000000000000006 <br>
  F-measure:  0.22576923076923078 <br>
  Prediction:  279   27 <br>
  Actual Class label:  225   81 <br>

  <p align="center">
    <img src="graphs/knn_haberman.png" width="300" height="200"
  </p>

- **Pima Indian Diabetes Dataset**

  Accuracy:  0.7345181134654819 <br>
  Specificity:  0.8537733948309499 <br>
  Sensitivity:  0.505056462056462 <br>
  Precision:  0.654110233778426 <br>
  F-measure:  0.5661286781167465 <br>
  Prediction:  560   208 <br>
  Actual Class label:  500   268 <br>

  <p align="center">
    <img src="graphs/knn_indian.png" width="300" height="200"
  </p>

#### SVM

- **BankNote Authentication Dataset**

  Accuracy:  1.0 <br>
  Specificity:  1.0 <br>
  Sensitivity:  1.0 <br>
  Precision:  1.0 <br>
  F-measure:  1.0 <br>
  Prediction:  762   610 <br>
  Actual Class label:  762   610 <br>

  <p align="center">
    <img src="graphs/svm_bank.png" width="300" height="200"
  </p>

- **Breast Cancer Wisconsin Dataset**

  Accuracy:  0.9706947996589939 <br>
  Specificity:  0.9674638205531718 <br>
  Sensitivity:  0.9758705647176411 <br>
  Precision:  0.94581223893066 <br>
  F-measure:  0.9598474346492758 <br>
  Prediction:  436   247 <br>
  Actual Class label:  444   239 <br>

  <p align="center">
    <img src="graphs/svm_breast.png" width="300" height="200"
  </p>

- **Haberman's Survival Dataset**

  Accuracy:  0.738279569892473 <br>
  Specificity:  0.9280952380952382 <br>
  Sensitivity:  0.21119047619047623 <br>
  Precision:  0.5516666666666665 <br>
  F-measure:  0.293005883005883 <br>
  Prediction:  273   33 <br>
  Actual Class label:  225   81 <br>

  <p align="center">
    <img src="graphs/svm_haberman.png" width="300" height="200"
  </p>

- **Pima Indian Diabetes Dataset**

  Accuracy:  0.7578092959671907 <br>
  Specificity:  0.8717053464237511 <br>
  Sensitivity:  0.5382652975089014 <br>
  Precision:  0.6884103608868742 <br>
  F-measure:  0.6008505361904428 <br>
  Prediction:  558   210 <br>
  Actual Class label:  500   268 <br>

  <p align="center">
    <img src="graphs/svm_indian.png" width="300" height="200"
  </p>

#### Bagging

- **BankNote Authentication Dataset**

  Accuracy:  0.9890722521950703 <br>
  Specificity:  0.9896917509541462 <br>
  Sensitivity:  0.9877610134963074 <br>
  Precision:  0.9864901343593644 <br>
  F-measure:  0.9870368301341568 <br>
  Prediction:  761   611 <br>
  Actual Class label:  762   610 <br>

  <p align="center">
    <img src="graphs/bag_bank.png" width="300" height="200"
  </p>

- **Breast Cancer Wisconsin Dataset**

  Accuracy:  0.954688832054561 <br>
  Specificity:  0.9653364376651545 <br>
  Sensitivity:  0.9291794364314386 <br>
  Precision:  0.9425795315795316 <br>
  F-measure:  0.9340692263711133 <br>
  Prediction:  445   238 <br>
  Actual Class label:  444   239 <br>

  <p align="center">
    <img src="graphs/bag_breast.png" width="300" height="200"
  </p>

- **Haberman's Survival Dataset**

  Accuracy:  0.6762365591397849 <br>
  Specificity:  0.8227567441084066 <br>
  Sensitivity:  0.2894993894993895 <br>
  Precision:  0.3866666666666666 <br>
  F-measure:  0.30789904539904545 <br>
  Prediction:  244   62 <br>
  Actual Class label:  225   81 <br>

  <p align="center">
    <img src="graphs/bag_haberman.png" width="300" height="200"
  </p>

- **Pima Indian Diabetes Dataset**

  Accuracy:  0.7435577580314423 <br>
  Specificity:  0.8529084524070729 <br>
  Sensitivity:  0.5348681311816619 <br>
  Precision:  0.6604950540602714 <br>
  F-measure:  0.5862814191475204 <br>
  Prediction:  549   219 <br>
  Actual Class label:  500   268 <br>

  <p align="center">
    <img src="graphs/bag_indian.png" width="300" height="200"
  </p>

---

For each classifier, I have computed the following performance measure metrics
using 10-fold cross validation.

1. Accuracy
2. Specificity
3. Sensitivity
4. Precision
5. Recall
6. F-Measure

Also, I have included the number of samples predicted as belonging to each class
versus actually belonging to each class in the displayed output. And I have
drawn the ROC curves for each case as well.

Four different datasets have been used for testing each of the five classifiers.

1. BankNote Authentication Dataset
2. Breast Cancer Wisconsin Dataset
3. Haberman's Survival Dataset
4. Pima Indian Diabetes Dataset

---

On the basis of all the analysis performed, one general conclusion that I can
draw is that the BankNote Authentication Dataset and the Breast Cancer Wisconsin
Dataset seem relatively easily to classify or cluster because all algorithms
achieve nearly perfect results for these 2 cases. Whereas for the other
datasets, the algorithms only have average performance.

---
