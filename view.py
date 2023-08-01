import tkinter as tk
from tkinter import filedialog
import pandas as pd

def browse_file():
    file_path = filedialog.askopenfilename(filetypes=[("CSV files", "*.csv")])
    if file_path:
        display_csv(file_path)

def display_csv(file_path):
    try:
        data = pd.read_csv(file_path)
        text.delete(1.0, tk.END)
        text.insert(tk.END, data.to_string(index=False))
    except Exception as e:
        text.delete(1.0, tk.END)
        text.insert(tk.END, f"Error: {e}")

# Create the main application window
root = tk.Tk()
root.title("CSV File Viewer")
root.configure(bg="black")

# Create a blue frame to display the CSV data
frame = tk.Frame(root, bg="Black", padx=10, pady=10)
frame.pack(fill=tk.BOTH, expand=True)

# Create a text widget inside the frame to display the CSV data
text = tk.Text(frame, bg="deep sky blue", fg="white", font=("Courier", 10))
text.pack(fill=tk.BOTH, expand=True)

# Create a button to browse and open the CSV file
button = tk.Button(root, text="Open CSV File", command=browse_file, bg="deep sky blue", fg="black")
button.pack(pady=10)

root.mainloop()
