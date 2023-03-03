# importing tkinter for gui
import tkinter as tk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import IHM_utils
import time

# creating window
window = tk.Tk()
# setting attribute
window.attributes('-fullscreen', True) 
window.title("Sensors data")
# creating text label to display on window screen
label = tk.Label(window, text="Hello Tkinter!")
label.pack()
# Bind the ESC key with the callback function
window.bind('<Escape>', lambda e: IHM_utils.close_win(e,window))

XList=[0,1,2,10,3,2,7,8]
YList=[720,230,150,300,]

fig, axes = plt.subplots(1, 2)

axes[0].plot(XList)
axes[0].set_title("sensor1")
axes[1].plot(YList)
axes[1].set_title("sensor2")


graph = FigureCanvasTkAgg(fig, master=window) 
graph.get_tk_widget().pack()


graph.draw() 
time.sleep(1) 



window.mainloop()




