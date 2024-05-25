import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns


data1 = pd.read_csv("output.csv")
sns.scatterplot(x=data1.Income,y=data1.Score,
                hue=data1. cluster,
                palette=sns.color_palette("bright",n_colors=3))
plt.xlabel("Income")
plt.ylabel("Score")

plt.show()