import pandas as pd
import os
import numpy as np
import seaborn as sns

data = pd.read_csv('iris.csv')
data['sepal length in cm'].plot(kind='hist')

bins = [4,5,6,7]
bins = pd.cut(data['sepal length in cm'], bins, retbins=True)
#print(data['bins'].value_counts())
#print(bins.value_counts())