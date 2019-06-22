from Tkinter import *

root = Tk()

nrOfCars = 0
speed = 0


def makeCars():
    global nrOfCars
    global speed
    for x in range(0,nrOfCars):
        w= Label(root,text="Car "+str(x)+" Speed "+str(speed))
        w.grid(row=x+4,column=1)

def addCar():
    global nrOfCars
    global speed
    nrOfCars += 1
    label1.config(text="Car number: "+str(nrOfCars))
    label1.update_idletasks()
    makeCars()

def addSpeed():
    global speed
    speed += 10
    speedLabel.config(text="Car speed: "+str(speed))
    speedLabel.update_idletasks()
    makeCars()

w = Button(root,text="Quit",command=root.quit)
w.grid(row=1,column=1)
w = Button(root,text="Add car",command=addCar)
w.grid(row=1,column=2)

w=Button(root,text="Up the speed",command=addSpeed)
w.grid(row=1,column=3)

label1 = Label(root,text="Car number: "+str(nrOfCars))
label1.grid(row=2,column=1)

speedLabel = Label(root,text="Car speed: "+str(speed))
speedLabel.grid(row=3,column=1)

mainloop()
