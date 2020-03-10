import scipy.interpolate

x = [1,3,5]
y = [4,3,8]

y_interp = scipy.interpolate.interp1d(x, y)
print (y_interp(4.5))