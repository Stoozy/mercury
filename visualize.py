import pandas as pd
import matplotlib.pyplot as plt
import csv

df = pd.read_csv("build/output.csv")
df[["LTA", "STA", "Price"]].plot()
plt.show()
