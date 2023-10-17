import pandas as pd
import matplotlib.pyplot as plt
import csv

df = pd.read_csv("build/output.csv")
p = df[["LTA", "STA", "Price"]].plot(title="Strategy Data")
p.set_xlabel("Days")
p.set_ylabel("Price")
plt.show()
