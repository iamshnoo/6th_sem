import math
f = open("final.data","r")
matrix = []
count = 0
for x in f:
    x.rstrip('\n')
    a = x.split(',')
    matrix.append(a)
    count+=1
count-=1

for i in range(count):
    for j in range(4):
        matrix[i][j]=float(matrix[i][j])

for j in range(4):
    min = 1000000.0
    max = -1.0
    for i in range(count):
        a = (matrix[i][j])
        if a < min:
            min = a
        if a > max:
            max = a
    for i in range(count):
        matrix[i][j]-=min
        matrix[i][j] = (matrix[i][j])/(max-min)

euc = []

for i in range(count):
    a = []
    for j in range(count):
        ans = 0.0
        for k in range(4):
            ans+= (matrix[i][k]-matrix[j][k])*(matrix[i][k]-matrix[j][k])
        a.append(math.sqrt(ans))
    euc.append(a)
cluster = []
for i in range(count):
    sum = 0.0
    a = []
    for j in range(count):
        sum+=euc[i][j]
    sum = sum/(count)
    for j in range(count):
        if euc[i][j]<sum:
            a.append(j+1)
    cluster.append(a)
clust1 = []
p = 0
count = len(euc)
#print(cluster)
def q6(count,cluster):
    cluster1 = cluster
    newclust = []
    for i in range(count):
        flag = 0
        for j in range(count):
            if i==j:
                continue
            if(set(cluster1[i]).issubset(set(cluster1[j]))):
                flag = 1
                break
        if flag==0:
            newclust.append(cluster1[i])
    cluster = newclust
    #print(newclust)
    return newclust


def q7(count,cluster):
    similarity = []
    for i in range(count):
        array = []
        for j in range(count):
            union = list(set(cluster[i])| set(cluster[j]))
            intersect = list(set(cluster[i])& set(cluster[j]))
            array.append(len(intersect)/len(union))
        similarity.append(array)
    #print(similarity)
    return similarity
def q8(count,similarity,cluster):
    max3 = 0
    max2 = 0
    max = -100
    temp = []
    for i in range(count):
        for j in range(count):
            if i==j:
                continue
            if similarity[i][j]>max:
                max = similarity[i][j]
                max3 = i
                max2 = j
    newclust = []
    for i in range(count):
        if i==max2 or i==max3:
            continue
        newclust.append(cluster[i])
    newclust.append(list(set(cluster[max3])|set(cluster[max2])))
    print(len(newclust),max2,max3)
    return newclust

a = 0
while(len(cluster)>3):
    count = len(cluster)
    cluster = q6(count,cluster)
    count = len(cluster)
    similarity = q7(count,cluster)
    count = len(similarity)
    cluster = q8(count,similarity,cluster)
    count = len(cluster)
    a+=1
prob =[]
for i in range(150):
    temp = []
    for j in range(3):
        temp.append(0)
    prob.append(temp)
mean = []
for i in range(3):
    x = len(cluster[i])
    sumtemp = []
    #print(x)
    for k in range(4):
        z = 0
        for j in range(x):
            z+=matrix[cluster[i][j]-1][k]
            prob[cluster[i][j]-1][i]=1;
        z = z/x
        sumtemp.append(z)
    mean.append(sumtemp)

dummy = [[]for _ in range(3)]
for i in range(151):
    if i==0:
        continue
    len1 = 10000000.0
    meanind = 0
    for j in range(3):
        if(prob[i-1][j]==0):
            continue
        else:
            tempmean = 0
            for k in range(4):
                tempmean+=(matrix[i-1][k]-mean[j][k])*(matrix[i-1][k]-mean[j][k])
            tempmean = math.sqrt(tempmean)
            if len1>(tempmean):
                len1 = tempmean
                meanind = j
    dummy[meanind].append(i)
cluster = dummy
for i in range(3):
    print(len(cluster[i]))
print(cluster)
