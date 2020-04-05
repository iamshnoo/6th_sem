import math
import networkx as nx
import matplotlib.pyplot as plt

def avg(x):
  '''[Calculates average of elements in a 1D array.]

  Args:
      x ([1d array]): [input array of length > 0]

  Returns:
      [float]: [average of array elements]
  '''
  assert len(x) > 0
  return float(sum(x)/len(x))

def pearson(x,y):
  '''[Calculate pearson correlation coefficient for a sample]

  Reference:
      https://en.wikipedia.org/wiki/Pearson_correlation_coefficient#Definition

  Args:
      x ([1d array]): [x1, x2, ..., xn]
      y ([1d array]): [y1, y2, ..., yn]

  Returns:
      [float]: [description]

  '''
  assert len(x) == len(y)
  assert len(x) > 0
  n = len(x)

  X_avg = avg(x)
  Y_avg = avg(y)

  diffprod = 0
  xdiff_squared = 0
  ydiff_squared = 0

  for i in range(n):
    xdiff = x[i] - X_avg
    ydiff = y[i] - Y_avg

    diffprod += xdiff * ydiff
    xdiff_squared += xdiff * xdiff
    ydiff_squared += ydiff * ydiff

  return diffprod / math.sqrt(xdiff_squared * ydiff_squared)

def create_graph(n):
  '''[summary]

  Args:
      n (int): [number of features in dataset]
  '''

  g  = nx.Graph()
  k5 = nx.complete_graph(n)
  g.add_nodes_from(k5)

  # node_list = [0,1,2,...,n]
  node_list = g.nodes()

  pos = nx.circular_layout(g)
  nx.draw_networkx_nodes(g,pos,node_color='green',node_size=7500)

  labels = {}
  for node_name in node_list:
      labels[str(node_name)] =str(node_name)
  nx.draw_networkx_labels(g,pos,labels,font_size=16)

  # add edges
  for i in node_list:
    for j in node_list:
      if i!=j:
        g.add_edge(node_list[i],node_list[j],
                    weight=pearson(node_list[i],node_list[j]))
