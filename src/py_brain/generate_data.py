import random 
import pandas as pd

#Custom list to define a 'Menu' of possible tasks
TASK_TEMPLATES = [
    {"name":"OS_Routine", "id":0, "base_time":2, "possible_io": (1,10)},
    {"name":"User_Interaction", "id":1, "base_time":5, "possible_io": (10,100)},
    {"name":"Disk_IO", "id":2, "base_time":10, "possible_io": (50,2000)},
    {"name":"Heavy_Compute", "id":3, "base_time":50, "possible_io": (1000,6000)},
]

data_rows = []

s_no = 0

for i in range(250):
    for template in TASK_TEMPLATES:
        min_io, max_io = template["possible_io"]
        io_data = random.randint(min_io,max_io)
        priority = random.randint(1,10)
        base_exec_time = template["base_time"]
        noise = random.randint(-50,50)
        exec_time = base_exec_time*io_data+noise
        exec_time = max(1, exec_time)
        
        row={
            "Process_ID": 1000+s_no,
            "Task_Name": template["name"],
            "Task_ID": template["id"],
            "Input_Data": io_data,
            "Priority": priority,
            "Execution_Time": exec_time
        }

        data_rows.append(row)

        s_no+=1

random.shuffle(data_rows)

generated_tasks_df = pd.DataFrame(data=data_rows)

print(generated_tasks_df.head(10))

generated_tasks_df.to_csv("data/raw_logs.csv", index=False)