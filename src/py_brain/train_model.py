import pandas as pd
import os
from sklearn.linear_model import LinearRegression

#Absolute path for the files regardless the system
script_dir = os.path.dirname(os.path.abspath(__file__))
dataset_path = os.path.join(script_dir, "../../data/raw_logs.csv")

df = pd.read_csv(dataset_path)

# {unque_tasks = [0,1,2,3]}, these are the task ID's we'll use to
# classify the dataset to train 4 seperate models for each type 
# of task. 
unique_tasks = df["Task_ID"].unique()

for task_id in unique_tasks:
    current_task_df = df[df["Task_ID"] == task_id]

    X = current_task_df[["Input_Data"]]
    y = current_task_df["Execution_Time"]

    #fit_intercept=False, this sets c = 0 in the equation y= mx + c 
    model = LinearRegression(fit_intercept=False)
    model.fit(X,y)

    #predicted_time = input_size * model_coefficient + intercept
    slope = model.coef_[0]

    task_name = current_task_df["Task_Name"].unique()[0]

    print(F"COEFF_{task_name} {slope:.4f}")