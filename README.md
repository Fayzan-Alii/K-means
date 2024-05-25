# K-means
K-means Clustering C++

# How it works
The program starts by reading the data from a CSV file. The data is stored in a 2D array. The K-means algorithm is then applied to this data. The algorithm starts by randomly assigning centroids. It then assigns each data point to the nearest centroid, and recalculates the centroids by taking the mean of all data points in the cluster. This process is repeated until the centroids no longer change.

Once the clustering is complete, the program writes the data, along with the cluster each data point belongs to, to an output CSV file.

You can plot the output CSV files using the python scripts.