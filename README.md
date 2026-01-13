# **Predictive Workload Balancer (PWB)**

![Project Status](https://img.shields.io/badge/Status-Completed-success)
![Language](https://img.shields.io/badge/Languages-C%20%7C%20Python-blue)

## **Overview**
**Predictive Workload balancer (PWB)** is a hybrid system that uses historical data to optimize CPU Scheduling.

Traditional operating systems use **Round Robin Scheduling**, which gives each process a small, fixed time slice (called *quantum*) in a circular queue. When a process's quantum expires, it is moved to the rear of the ready queue and the CPU moves to the next process. While simple, this approach has two major drawback:
* It gives equal priority to each task and ignores their urgency/priority order.
* In case many heavy tasks clog the queue it leads to high average waiting period.

A **PWB** uses analysis from Linear Regression models trained on historical data to predict exactly how long a task will take based on its input size. These tasks are then organised into a Priority Queue using a Binary Search Tree. This allows the system to efficiently sort and retrieve tasks based on their priority levels in real-time.

## **Tech Stack**
* **Core Engine:** C (GCC Compiler)
* **Data Analysis & ML:** Python (Pandas, Scikit-Learn)
* **Data Structure:** Binary Search Tree (BST)
* **Build System:** GNU Make
* **Version Control:** Git & GitHub

## **Project Structure**
```
.
├── Makefile                # Automates Compilation and execution
├── README.md               # Project Documentation 
├── requirements.txt        # Python Dependencies
├── .gitignore              # git file
├── data/                   
│   ├── incoming_tasks.csv  # Tasks waiting to be scheduled
│   └── raw_logs.csv        # Historical data for model training
└── src/
    ├── c_engine/           
    │   ├── bst.c           # Binary Search Tree Implementation
    │   ├── bst.h           # Header file for BST
    │   ├── main.c          # Main balancer engine
    │   └── resources.h     # Header file for basic resources
    └── py_brain/
        ├── generate_data.py
        └──train_model.py
```

## **Architecture**
1.  **Data Generation & Ingestion (Python):**
    * Synthetic logs are generated to simulate a system's historical log data.
2.  **Analysis & Training (Python):**
    * These logs then flow into a Linear Regression Model which calculates specific coefficients required to calculate the execution time of a task.
3.  **Predictive Execution (C):**
    * The C engine uses these coefficients to predict the execution time for the tasks from log data.
    * Tasks are then injected into a **Binary Search Tree (BST)** and sorted based on their priority and predicted execution time.

## **How to run**
### **1. Prerequisites**
Ensure you have `gcc`, `make` and `python3` installed.

### **2. Setup Python Environment**
Install the required libraries
```bash
pip install -r requirements.txt
```

### **3. Generate Data and Train Models**
Run the python scripts to generat data logs and calculate the speed coefficients.
```bash
python3 src/py_brain/generate_data.py
python3 src/py_brain/train_model.py 
```

### **4. Build and run the Balancer**
Use the makefile to compile and the C engine and start the simulation.
```bash
make run
```

## **Future Improvements**
* **Automated Retraining Pipelines**: The C program should be able to save the actual execution time back in a csv which is can be used to update the model.
* **Advanced Model Integration**: Linear Regression assumes the tasks and their execution times are related linearly `(y = mx + c)`. Actual execution times will obviously not fit on just a sinle linear function. We can use more complex models like `decision trees` if data gets messy.
* **Visual Dashboard**: The system currently only has a scrolling terminal to show for GUI. The future implementations include a graph to visualize the a queue in real-time.
* **Real Process Execution:** Transition from simulating tasks (using sleep) to spawning actual system processes (using `fork` and `exec`) to manage real workloads on the host machine.