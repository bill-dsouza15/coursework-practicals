import pandas as pd
from pandas import DataFrame
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, r2_score
import pickle

regressor = LinearRegression()

# Train the regression model


def regressionAlgo():
    dataset = pd.read_csv('A1\\Dataset\\grad_admit_dataset.csv')
    X = dataset.iloc[:, :-1].values
    y = dataset.iloc[:, -1].values

    # Splitting dataset to get test and trainig data
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=1/5, random_state=0)

    # Fit the linear regression model
    regressor.fit(X_train, y_train)
    y_pred = regressor.predict(X)

    # Root mean squared error and R2 score
    rmse = mean_squared_error(y, y_pred)
    print("Root Mean Squared Error: ", rmse)
    r2 = r2_score(y, y_pred)
    print("Accuracy of the model is:", r2)

    # Save the model to disk
    filename = 'A1\\Dataset\\trained_model.sav'
    pickle.dump(regressor, open(filename, 'wb'))


# Call the regressionAlgo function to train model
regressionAlgo()
