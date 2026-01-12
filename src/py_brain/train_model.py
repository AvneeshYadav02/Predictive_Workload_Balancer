import pandas as pd
import os
import sklearn
import pickle
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import r2_score

script_dir = os.path.dirname(os.path.abspath(__file__))
dataset_path = os.path.join(script_dir, "../../data/raw_logs.csv")

df = pd.read_csv(dataset_path)

X = df[["Input_Data"]]
y = df["Execution_Time"]

X_train, X_test, y_train, y_test = train_test_split(X,y, test_size=0.2, random_state=42)

model = LinearRegression()
model.fit(X_train, y_train)

predictions = model.predict(X_test)
print(f"Model Accureacy (R2 Score): {r2_score(y_test, predictions)}")

model_path = os.path.join(script_dir, "model.pkl")
with open(model_path, 'wb') as file:
    pickle.dump(model, file)
print(f"Model saved to: {model_path}")

# When we fit our X_train and y_train on the Linear Regression model it calculates two coefficients and one intercept
#  TIME = (Coef x Input_Data) + Intercept
# To get an estimated time in our final steps in C we will directly use these coefficients and the intercepts.
print(f"Formula: ({model.coef_[0]:.4f} * Input_Data) + ({model.intercept_:.4f})")