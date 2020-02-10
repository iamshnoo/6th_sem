import pandas as pd
import os
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
# https://stackoverflow.com/questions/30211923/what-is-the-difference-between-pandas-qcut-and-pandas-cut

data = pd.read_csv('iris.csv')
#data['sepal length in cm'].plot(kind='hist')
#print(data.head())
sns.distplot(data['sepal length in cm'],kde=True,bins=7)
plt.show()
bins = [4,5,6,7]
bins = pd.cut(data['sepal length in cm'], bins, retbins=True)

print(bins.value_counts())