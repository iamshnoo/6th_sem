import numpy as np
import math
from sklearn.datasets import load_iris
from sklearn import datasets, linear_model, metrics
import random
import matplotlib.pyplot as plt
import networkx as nx

dataset=load_iris()
data=dataset.data
sl=np.zeros(150)
sw=np.zeros(150)
pl=np.zeros(150)
pw=np.zeros(150)

n=150

# storing all attributes in lists
for i in range (n):
    sl[i]=data[i,0]
    sw[i]=data[i,1]
    pl[i]=data[i,2]
    pw[i]=data[i,3]

def getKPCF(x,y):
    sum_x=np.sum(x)
    sum_y=np.sum(y)

    sum_x_sq=np.sum(np.square(x))
    sum_y_sq=np.sum(np.square(y))

    sum_x_y=np.sum(np.multiply(x,y))

    r_x_y=(n*sum_x_y-(sum_x*sum_y))/(math.sqrt(n*sum_x_sq-(sum_x**2))*math.sqrt(n*sum_y_sq-(sum_y**2)))
    return r_x_y

r_sl_sw=getKPCF(sl,sw)
r_sl_pl=getKPCF(sl,pl)
r_sl_pw=getKPCF(sl,pw)
r_sw_pl=getKPCF(sw,pl)
r_sw_pw=getKPCF(sw,pw)
r_pl_pw=getKPCF(sl,pw)

print("Karl Pearson Correlation Cfts: ")
print(r_sl_sw)
print(r_sl_pl)
print(r_sl_pw)
print(r_sw_pl)
print(r_sw_pw)
print(r_pl_pw)

# ================================ Graph ===============================

def getImportance(G):
    lst=G.adj.items()
    importance_dict={}
    for n,nbrs in lst:
        sum=0
        for nbr,eattr in nbrs.items():
            sum+=eattr['weight']
        importance_dict[n]=sum
    return importance_dict

G=nx.Graph()

G.add_edge('sl','sw',weight=r_sl_sw)
G.add_edge('sl','pl',weight=r_sl_pl)
G.add_edge('sl','pw',weight=r_sl_pw)
G.add_edge('sw','pl',weight=r_sw_pl)
G.add_edge('sw','pw',weight=r_sw_pw)
G.add_edge('pl','pw',weight=r_pl_pw)

# Nodes and edges in the beginning
print()
print("In the beginning:")
print(G.nodes)
print(G.edges)

elarge=[(u, v) for (u, v, d) in G.edges(data=True) if d['weight'] > 0]
esmall=[(u, v) for (u, v, d) in G.edges(data=True) if d['weight'] <= 0]

# Drawing Graph
pos=nx.spring_layout(G) # positions for all nodes
nx.draw_networkx_nodes(G,pos,node_size=700)
nx.draw_networkx_edges(G,pos,edgelist=elarge,width=6)
nx.draw_networkx_edges(G,pos,edgelist=esmall,width=6,alpha=0.5,edge_color='b',style='dashed')
nx.draw_networkx_labels(G, pos, font_size=20, font_family='sans-serif',font_color='yellow')
plt.axis('off')
plt.show()

# Remove edges below threshold value
for edge in esmall:
    G.remove_edge(edge[0],edge[1])

# Nodes and edges after above step
print()
print("After removing edges with weights below threshold:")
print(G.nodes)
print(G.edges)

# Drawing Graph
pos=nx.spring_layout(G) # positions for all nodes
nx.draw_networkx_nodes(G,pos,node_size=700)
nx.draw_networkx_edges(G,pos,edgelist=G.edges,width=6)
nx.draw_networkx_labels(G, pos, font_size=20, font_family='sans-serif',font_color='yellow')
plt.axis('off')
plt.show()

# Recursively removing nodes
while(G.number_of_edges()!=0):
    dct=getImportance(G)
    max=0
    for k,v in dct.items():
        if max<v:
            max=v
            node_to_remove=k
    # Remove this node
    G.remove_node(node_to_remove)
    # Nodes and edges after above step
    print()
    print("After removing node "+node_to_remove)
    print(G.nodes)
    print(G.edges)

# Print the nodes which are remaining
print()
print("Finally, remaining feature nodes in the null graph:")
print(G.nodes)

# Drawing Graph
pos=nx.spring_layout(G) # positions for all nodes
nx.draw_networkx_nodes(G,pos,node_size=700)
nx.draw_networkx_edges(G,pos,edgelist=G.edges,width=6)
nx.draw_networkx_labels(G, pos, font_size=20, font_family='sans-serif',font_color='yellow')
plt.axis('off')
plt.show()
