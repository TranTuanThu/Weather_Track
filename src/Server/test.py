import tkinter as tk
import tkinter.font as tkFont
from tkinter import messagebox as mb
from tkinter import ttk

def LoginAdmin():
    

    frameLogin = tk.Frame(width=300, height=150)
    frameLogin.place(x=200, y=110)

    fontHead = tkFont.Font(size=24)
    fontBody = tkFont.Font(size=14)

    labelLogin = tk.Label(master=frameLogin, text="Login", bg="white", font=fontHead)
    labelLogin.place(x=120, y=0)

    labelUsename = tk.Label(master=frameLogin, text="Usename:", bg="white", font=fontBody)
    labelUsename.place(x=0, y=40)

    entryUsename = tk.Entry(master=frameLogin, font=fontBody)
    entryUsename.place(x=80, y=40)
    entryUsename.get()

def answer():
    mb.showerror("Answer", "Sorry, no answer available")

def callback():
    if mb.askyesno('Verify', 'Really quit?'):
        mb.showwarning('Yes', 'Not yet implemented')
    else:
        mb.showinfo('No', 'Quit has been cancelled')




a = int(30)

window = tk.Tk()
window.title("Weather")

frame = tk.Frame(width=700,height=400, bg="white")
# frame1 = tk.Frame(width=75,height=75, bg="blue")
frame.pack(fill=tk.BOTH, expand=True)

fontWeather = tkFont.Font(size=26)
labelWeather = tk.Label(master=frame, text="Weather", bg="white", font=fontWeather)
labelWeather.place(x=300, y=0)

fontButton = tkFont.Font(size=18)

buttonRefresh = tk.Button(master=frame, text="Refresh", bg="green", font=fontButton)
buttonRefresh.place(x=250, y=35)

buttonAdmin = tk.Button(master=frame, text="Admin", bg="green", font=fontButton, command=callback)
buttonAdmin.place(x=370, y=35)

fontTHL = tkFont.Font(size=14)

labelTempt = tk.Label(master=frame, text="Tempt[℃]", bg="white", font=fontTHL)
labelTempt.place(x=30, y=100)

labelTemptRe = tk.Label(master=frame, text=a, bg="white", font=fontTHL)
labelTemptRe.place(x=200, y=100)

labelHumid = tk.Label(master=frame, text="Humid[%RH]", bg="white", font=fontTHL)
labelHumid.place(x=30, y=130)

labelHumidRe = tk.Label(master=frame, text=60, bg="white", font=fontTHL)
labelHumidRe.place(x=200, y=130)

labelLight = tk.Label(master=frame, text="Light[lux]", bg="white", font=fontTHL)
labelLight.place(x=30, y=160)

labelLightRe = tk.Label(master=frame, text=a, bg="white", font=fontTHL)
labelLightRe.place(x=200, y=160)



window.mainloop()