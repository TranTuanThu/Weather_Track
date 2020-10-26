from tkinter import ttk
from tkinter import messagebox as mb
import tkinter as tk
import tkinter.font as tkFont

font14 = int(14)
font18 = int(18)
font26 = int(26)

window = tk.Tk()
window.title("Weather")
tabControl = ttk.Notebook(window)

home = tk.Frame(master=tabControl, width=700, height=400, bg="white")
admin = tk.Frame(master=tabControl, width=700, height=400, bg="white")

tabControl.add(home, text="Home")
tabControl.add(admin, text="Admin")
tabControl.pack(fill="both", expand=True)


labelWeather = tk.Label(master=home, text="Weather", bg="white", font=tkFont.Font(size=font26))
labelWeather.place(x=300, y=0)

buttonRefresh = tk.Button(master=home, text="Refresh", bg="green", font=tkFont.Font(size=font18))
buttonRefresh.place(x=310, y=40)

labelTempt = tk.Label(master=home, text="Tempt[℃]", bg="white", font=tkFont.Font(size=font14))
labelTempt.place(x=30, y=100)

labelTemptRe = tk.Label(master=home, text=30, bg="white", font=tkFont.Font(size=font14))
labelTemptRe.place(x=200, y=100)

labelHumid = tk.Label(master=home, text="Humid[%RH]", bg="white", font=tkFont.Font(size=font14))
labelHumid.place(x=30, y=130)

labelHumidRe = tk.Label(master=home, text=60, bg="white", font=tkFont.Font(size=font14))
labelHumidRe.place(x=200, y=130)

labelLight = tk.Label(master=home, text="Light[lux]", bg="white", font=tkFont.Font(size=font14))
labelLight.place(x=30, y=160)

labelLightRe = tk.Label(master=home, text=60, bg="white", font=tkFont.Font(size=font14))
labelLightRe.place(x=200, y=160)








window.mainloop()