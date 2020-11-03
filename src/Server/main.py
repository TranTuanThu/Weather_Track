import Process_code_C as pcc
from tkinter import ttk
from tkinter import messagebox as mb
import tkinter as tk
import tkinter.font as tkFont

pcc.initializeConnectBroker()
tempt, humid, bgcolor = pcc.processReceivedData()

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

# Tab Home ---------------------------------------------------------------------------------------------------------->>>>>>>>>>>>>

labelWeather = tk.Label(master=home, text="Weather", bg="white", font=tkFont.Font(size=font26))
labelWeather.place(x=300, y=0)

labelTempt = tk.Label(master=home, text="Tempt[℃]", bg="white", font=tkFont.Font(size=font14))
labelTempt.place(x=30, y=100)

labelTemptRe = tk.Label(master=home, text=tempt, bg="white", font=tkFont.Font(size=font14))
labelTemptRe.place(x=200, y=100)

labelWarning = tk.Label(master=home, bg=bgcolor, width=5, height=1)
labelWarning.place(x=310, y=100)

labelHumid = tk.Label(master=home, text="Humid[%RH]", bg="white", font=tkFont.Font(size=font14))
labelHumid.place(x=30, y=130)

labelHumidRe = tk.Label(master=home, text=humid, bg="white", font=tkFont.Font(size=font14))
labelHumidRe.place(x=200, y=130)

labelLight = tk.Label(master=home, text="Light[lux]", bg="white", font=tkFont.Font(size=font14))
labelLight.place(x=30, y=160)

labelLightRe = tk.Label(master=home, text=60, bg="white", font=tkFont.Font(size=font14))
labelLightRe.place(x=200, y=160)

def catchEventRefresh():
    pcc.initializeConnectBroker()
    labelTemptRe["text"], labelHumidRe["text"], labelWarning["bg"] = pcc.processReceivedData() 

buttonRefresh = tk.Button(master=home, text="Refresh", bg="green", font=tkFont.Font(size=font18), command=catchEventRefresh)
buttonRefresh.place(x=310, y=40)

# Tab Admin ---------------------------------------------------------------------------------------------------------->>>>>>>>>>>>>

labelConfig = tk.Label(master=admin, text="Config threshold", bg="white", font=tkFont.Font(size=font14))
labelConfig.place(x=30, y=100)

labelLowerthres = tk.Label(master=admin, text="Lowerthreshold:", bg="white", font=tkFont.Font(size=font14))
labelLowerthres.place(x=30, y=130)

entryLowerthres = tk.Entry(master=admin)
entryLowerthres.place(x=200, y=130)

labelUpperthres = tk.Label(master=admin, text="Upperthreshold:", bg="white", font=tkFont.Font(size=font14))
labelUpperthres.place(x=30, y=160)

entryUpperthres = tk.Entry(master=admin)
entryUpperthres.place(x=200, y=160)


def catchEventOk():
    low = entryLowerthres.get()
    up = entryUpperthres.get()
    payload = low + up
    if mb.askyesno('Verify', 'Really update?'):
        mb.showwarning('Yes', 'Update successful')
        pcc.processUpdateThreshold(payload)
        print("Update Config: ", payload)
    else:
        mb.showinfo('No', 'Quit has been cancelled')


buttonOK = tk.Button(master=admin, text="Ok", bg="yellow",font=tkFont.Font(size=font14), command=catchEventOk)
buttonOK.place(x=60, y=190)

window.mainloop()