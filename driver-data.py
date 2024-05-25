import matplotlib.pyplot as plt
import pandas as pd
import numpy as np 
import seaborn as sns
df = pd.read_csv("output.csv")
sns.scatterplot(x=df.mean_dist_day, y=df.mean_over_speed_perc, 
                hue=df.cluster_value, 
                palette=sns.color_palette("hls", n_colors=3))
plt.xlabel("Distance")
plt.ylabel("Speed")
plt.title("Clustered: Distance (x) vs Speed (y)")

plt.show()