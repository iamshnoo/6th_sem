# importing requisites
import math
import random
from urllib.request import urlretrieve
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from sklearn import datasets
from sklearn.preprocessing import normalize,StandardScaler
from sklearn.model_selection import KFold
from sklearn.model_selection import train_test_split
from sklearn import tree
from sklearn.ensemble import BaggingClassifier
import sklearn.metrics as metrics
import matplotlib.pyplot as plt

# loading dataset
# dataset_name= 'http://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data'
# urlretrieve(dataset_name)

# Bagging function
def doBagging(XY,X,Y,class_label_list,num_folds):
    total_classes=len(class_label_list)
    overall_accuracy=0
    overall_specificity=0
    overall_sensitivity=0
    overall_precision=0
    overall_fmeasure=0
    counta=0
    countb=0
    actual_counta=0
    actual_countb=0
    # performing operation on each of the 10 different combinations
    k_fold=KFold(num_folds,True,None)
    for train,test in k_fold.split(XY):
        X_new=[] # train data
        X1_new=[] # test data
        Y_new=[] # train class
        Y1_new=[] # test class
        for index in train:
            X_new.append(X[index])
            Y_new.append(Y[index])
        for index in test:
            X1_new.append(X[index])
            Y1_new.append(Y[index])
        X_new=np.array(X_new)
        Y_new=np.array(Y_new)
        X1_new=np.array(X1_new)
        Y1_new=np.array(Y1_new)

        # classify
        bag=BaggingClassifier(random_state=42)
        bag=bag.fit(X_new,Y_new)

        # print("\nHere's the prediction: \n")
        predicted_classes=bag.predict(X1_new)
        # counting prediction results for each of the 10 folds
        temp_counta=counta
        temp_countb=countb
        counta=0
        countb=0
        for pr in predicted_classes:
            if pr==class_label_list[0]:
                counta+=1
            else:
                countb+=1
        counta+=temp_counta
        countb+=temp_countb
        # counting actual class labels for each fold
        temp_actual_counta=actual_counta
        temp_actual_countb=actual_countb
        actual_counta=0
        actual_countb=0
        for pr in Y1_new:
            if pr==class_label_list[0]:
                actual_counta+=1
            else:
                actual_countb+=1
        actual_counta+=temp_actual_counta
        actual_countb+=temp_actual_countb
        # print(predicted_classes) # predicted class for all test samples
        # print("\nAnd here's the reality: \n")
        # print(Y1_new) # actual class labels of test samples
        # print()

        # calculate accuracy
        total_test_samples=len(Y1_new)
        accurate=0
        for i in range(total_test_samples):
            if predicted_classes[i]==Y1_new[i]:
                accurate+=1
        accuracy=accurate/total_test_samples
        overall_accuracy+=accuracy
        print("Accuracy: ",accuracy)
        print()

        # confusion matrix (will be 2X2 here for binary classification)
        confusion=[]
        # we will be creating a confusion matrix here; classes will be labelled from 0
        for class_label in class_label_list:
            temp=[]
            for i in range(total_classes):
                temp.append(0)
            # count predicted class for this actual class_label
            for i in range(total_test_samples):
                # we found a sample with this class label
                if Y1_new[i]==class_label:
                    # find the predicted class label of this
                    predicted_label_here=predicted_classes[i]
                    # find the actual index
                    col_index=class_label_list.index(predicted_label_here)
                    temp[col_index]+=1
            confusion.append(temp)

        # specificity
        num=confusion[0][0]
        den=confusion[0][0]+confusion[0][1]
        specificity=0
        if den!=0:
            specificity=num/den
        overall_specificity+=specificity
        print("Specificity: ",specificity)
        print()

        # sensitivity aka recall
        num=confusion[1][1]
        den=confusion[1][0]+confusion[1][1]
        sensitivity=0
        if den!=0:
            sensitivity=num/den
        overall_sensitivity+=sensitivity
        print("Sensitivity: ",sensitivity)
        print()

        # precision
        num=confusion[1][1]
        den=confusion[0][1]+confusion[1][1]
        precision=0
        if den!=0:
            precision=num/den
        overall_precision+=precision
        print("Precision: ",precision)
        print()

        # f-measure
        den=precision+sensitivity
        fmeasure=0
        if den!=0:
            fmeasure=2*precision*sensitivity/(precision+sensitivity)
        overall_fmeasure+=fmeasure
        print("F-measure: ",fmeasure)
        print("------------------------------------------")
        print()

    # overall measures for k folds
    overall_accuracy/=num_folds
    overall_specificity/=num_folds
    overall_sensitivity/=num_folds
    overall_precision/=num_folds
    overall_fmeasure/=num_folds
    print("Overall results: \n")
    print("Accuracy: ",overall_accuracy)
    print("Specificity: ",overall_specificity)
    print("Sensitivity: ",overall_sensitivity)
    print("Precision: ",overall_precision)
    print("F-measure: ",overall_fmeasure)
    print("Prediction: ",counta," ",countb)
    print("Actual Class label: ",actual_counta," ",actual_countb)

# draw ROC curve
def drawROC(XY,X,Y,class_label_list):
    X_new,X1_new,Y_new,Y1_new=train_test_split(X,Y,test_size=0.25,random_state=42)

    # classify
    bag=BaggingClassifier(random_state=42)
    bag=bag.fit(X_new,Y_new)

    # find out required params
    predicted_classes=bag.predict_proba(X1_new)
    fpr,tpr,threshold=metrics.roc_curve(Y1_new,predicted_classes[:,1],pos_label=class_label_list[len(class_label_list)-1])
    roc_auc=metrics.auc(fpr,tpr)

    # plot
    plt.title('Receiver Operating Characteristic')
    plt.plot(fpr, tpr, 'b', label = 'AUC = %0.2f' % roc_auc)
    plt.legend(loc = 'lower right')
    plt.plot([0, 1], [0, 1],'r--')
    plt.xlim([0, 1])
    plt.ylim([0, 1])
    plt.ylabel('True Positive Rate')
    plt.xlabel('False Positive Rate')
    plt.show()

# prepare for classification
dataset_name="data_banknote_authentication.csv"
print("\n============ "+dataset_name+" =============")
df=pd.read_csv(dataset_name)
XY=np.array(df)
# splitting vertically into class label and attrs
scaler=StandardScaler()
X=np.array(scaler.fit_transform(df.drop(["class"],1).astype(float)))
Y=np.array(df[['class']].astype(float))
Y_mod=[]
for val in Y:
    Y_mod.append(val[0])
Y=np.array(Y_mod)
# call Bagging
doBagging(XY,X,Y,[0,1],10)
drawROC(XY,X,Y,[0,1])

# prepare for classification
dataset_name="bcw.csv"
print("\n============ "+dataset_name+" =============")
df=pd.read_csv(dataset_name)
# overall dataset
XY=np.array(df)
# splitting vertically into class label and attrs
scaler=StandardScaler()
X=np.array(scaler.fit_transform(df.drop(["class"],1).astype(float)))
Y=np.array(df[['class']].astype(float))
Y_mod=[]
for val in Y:
    Y_mod.append(val[0])
Y=np.array(Y_mod)
# call Bagging
doBagging(XY,X,Y,[2,4],10)
drawROC(XY,X,Y,[2,4])

# prepare for classification
dataset_name="haberman.csv"
print("\n============ "+dataset_name+" =============")
df=pd.read_csv(dataset_name)
# overall dataset
XY=np.array(df)
# splitting vertically into class label and attrs
scaler=StandardScaler()
X=np.array(scaler.fit_transform(df.drop(["class"],1).astype(float)))
Y=np.array(df[['class']].astype(float))
Y_mod=[]
for val in Y:
    Y_mod.append(val[0])
Y=np.array(Y_mod)
# call Bagging
doBagging(XY,X,Y,[1,2],10)
drawROC(XY,X,Y,[1,2])

# prepare for classification
dataset_name="pima-indians-diabetes.csv"
print("\n============ "+dataset_name+" =============")
df=pd.read_csv(dataset_name)
# overall dataset
XY=np.array(df)
# splitting vertically into class label and attrs
scaler=StandardScaler()
X=np.array(scaler.fit_transform(df.drop(["class"],1).astype(float)))
Y=np.array(df[['class']].astype(float))
Y_mod=[]
for val in Y:
    Y_mod.append(val[0])
Y=np.array(Y_mod)
# call Bagging
doBagging(XY,X,Y,[0,1],10)
drawROC(XY,X,Y,[0,1])