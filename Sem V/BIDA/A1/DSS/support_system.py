import tkinter as tk
from tkinter import messagebox as mb
import pandas as pd
from pandas import DataFrame
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, r2_score
import pickle

root = tk.Tk()
root.minsize(500,400)
root.maxsize(500,400)
data = []
regressor = LinearRegression()

# Check the acceptance probability
def checkAcceptance():
    # Append data
    data.append(float(gre_entry.get()))
    data.append(float(toefl_entry.get()))
    data.append(float(unirank_entry.get()))
    data.append(float(sop_entry.get()))
    data.append(float(lor_entry.get()))
    data.append(float(cgpa_entry.get()))
    data.append(float(research_entry.get()))

    # Regression algorithm
    calculator(data)

    # Clear list
    data.clear()

    # Clear entry fields
    gre_entry.delete(0,tk.END)
    toefl_entry.delete(0,tk.END)
    unirank_entry.delete(0,tk.END)
    sop_entry.delete(0,tk.END)
    lor_entry.delete(0,tk.END)
    cgpa_entry.delete(0,tk.END)
    research_entry.delete(0,tk.END)

# Calculate probability
def calculator(data1):
    # load the model from disk
    filename = 'trained_model.sav'
    regressor = pickle.load(open(filename, 'rb'))
    
    # find the probability
    studentData = []
    studentData.append(data1)
    y_pred = regressor.predict(studentData)
    msg = "The probability of your acceptance : "
    prob = ' '.join(str(float("{:.2f}".format(item))) for item in y_pred)
    mb.showinfo(title="Chance of Admission", message=msg+prob)

# Canvas
canvas = tk.Canvas(
    root,
    width=500,
    height=400,
    background="cyan"
)
canvas.pack(fill=tk.BOTH,expand=True)

# Creating a frame for organizing the widgets in a better way
frame = tk.Frame(
    root,
    background="white",
)
frame.place(relheight=0.8,relwidth=0.8,relx=0.1,rely=0.1)

# Dummy labels for spacing
dummy1 = tk.Label(
    master=frame,
    width=25,
    background="white"
)
dummy1.grid(row=0, column=0, padx=5, pady=5)

# Label and entry for GRE score (out of 340)
gre = tk.Label(
    master=frame,
    text="GRE score",
    width=25,
    background="white"
)
gre.grid(row=1, column=0, padx=5, pady=5)

gre_entry = tk.Entry(
    master=frame,
    text="Enter your GRE score",
    width=25,
    background="white"
)
gre_entry.grid(row=1, column=1, padx=5, pady=5)

# Label and entry for TOEFL score (out of 340)
toefl = tk.Label(
    master=frame,
    text="TOEFL score",
    width=25,
    background="white"
)
toefl.grid(row=2, column=0, padx=5, pady=5)

toefl_entry = tk.Entry(
    master=frame,
    text="Enter your TOEFL score",
    width=25,
    background="white"
)
toefl_entry.grid(row=2, column=1, padx=5, pady=5)

# Label and entry for University Rank (out of 5)
unirank = tk.Label(
    master=frame,
    text="University Rank",
    width=25,
    background="white"
)
unirank.grid(row=3, column=0, padx=5, pady=5)

unirank_entry = tk.Entry(
    master=frame,
    text="Enter your University Rank",
    width=25,
    background="white"
)
unirank_entry.grid(row=3, column=1, padx=5, pady=5)

# Label and entry for SOP (out of 5)
sop = tk.Label(
    master=frame,
    text="SOP",
    width=25,
    background="white"
)
sop.grid(row=4, column=0, padx=5, pady=5)

sop_entry = tk.Entry(
    master=frame,
    text="Enter your SOP",
    width=25,
    background="white"
)
sop_entry.grid(row=4, column=1, padx=5, pady=5)

# Label and entry for LOR (out of 5)
lor = tk.Label(
    master=frame,
    text="LOR",
    width=25,
    background="white"
)
lor.grid(row=5, column=0, padx=5, pady=5)

lor_entry = tk.Entry(
    master=frame,
    text="Enter your LOR",
    width=25,
    background="white"
)
lor_entry.grid(row=5, column=1, padx=5, pady=5)

# Label and entry for CGPA (out of 10)
cgpa = tk.Label(
    master=frame,
    text="CGPA",
    width=25,
    background="white"
)
cgpa.grid(row=6, column=0, padx=5, pady=5)

cgpa_entry = tk.Entry(
    master=frame,
    text="Enter your CGPA",
    width=25,
    background="white"
)
cgpa_entry.grid(row=6, column=1, padx=5, pady=5)

# Label and entry for research (0 or 1)
research = tk.Label(
    master=frame,
    text="Research",
    width=25,
    background="white"
)
research.grid(row=7, column=0, padx=5, pady=5)

research_entry = tk.Entry(
    master=frame,
    text="Enter your research",
    width=25,
    background="white"
)
research_entry.grid(row=7, column=1, padx=5, pady=5)

# Dummy label for spacing
dummy2 = tk.Label(
    master=frame,
    width=25,
    background="white"
)
dummy2.grid(row=8, column=0, padx=5, pady=5)

# Button to submit values and get acceptance probability (from 0 to 100)
submitbutton = tk.Button(
    master=frame,
    text="Check acceptance",
    width=25,
    background="white",
    command=checkAcceptance
)
submitbutton.grid(row=9, column=1, padx=5, pady=10)

# Dummy label for spacing
dummy3 = tk.Label(
    master=frame,
    width=25,
    background="white"
)
dummy3.grid(row=10, column=0, padx=5, pady=5)

root.mainloop()