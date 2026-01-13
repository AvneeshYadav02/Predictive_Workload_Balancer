import pandas as pd
import os
import sklearn
import pickle
from sklearn.linear_model import LinearRegression

script_dir = os.path.dirname(os.path.abspath(__file__))
dataset_path = os.path.join(script_dir, "../../data/raw_logs.csv")

df = pd.read_csv(dataset_path)

unique_tasks = df["Task_ID"].unique()

for task_id in unique_tasks:
    current_task_df = df[df["Task_ID"] == task_id]

    X = current_task_df[["Input_Data"]]
    y = current_task_df["Execution_Time"]

    model = LinearRegression(fit_intercept=False)
    model.fit(X,y)

    slope = model.coef_[0]

    task_name = current_task_df["Task_Name"].unique()[0]

    print(F"COEFF_{task_name} {slope:.4f}")