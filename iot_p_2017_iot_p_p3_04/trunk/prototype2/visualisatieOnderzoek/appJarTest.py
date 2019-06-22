from appJar import gui

app = gui("Login")

app.addLabel("title","Welcome")
app.setLabelBg("title","lightBlue")

car1Speed = 100
nrOfCars = 0
nrOfCarsExists = 0

def makeLabels():
    global nrOfCarsExists
    global nrOfCars
    for x in range(0,nrOfCarsExists):
        app.setLabel("car"+str(x)+"Speed","Speed car "+str(x)+": "+str(car1Speed))
    for x in range(nrOfCarsExists,nrOfCars):
        app.addLabel("car"+str(x)+"Speed","New car "+str(x)+": "+str(car1Speed))
    nrOfCarsExists = nrOfCars

def press(button):
    global nrOfCars
    global car1Speed
    if button == "Exit":
        app.stop()
    elif button == "addSpeed":
        car1Speed += 100
        makeLabels()
    elif button == "addCar": 
        nrOfCars += 1
        makeLabels()

app.addButtons(["addSpeed","addCar","Exit"],press)
makeLabels()
app.go()
