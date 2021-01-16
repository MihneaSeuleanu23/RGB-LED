from tkinter import *
import serial
import time

ser=serial.Serial('COM6',baudrate=9600,timeout=0)

root=Tk()
root.title("RGB GUI")
root.iconbitmap('color_wheel_16443.ico')


def setvalue():
	pwm_val=E1.get()
	slider_red.config(to_=pwm_val)
	slider_green.config(to_=pwm_val)
	slider_blue.config(to_=pwm_val)
	E1.delete(0,END)

#Entry and OK button
L1 = Label(root, text="PWM")
L1.grid(row=0,column=0)
E1 = Entry(root, bd =5)
E1.grid(row=0,column=1)
Ok_Button=Button(root,text="Ok",command=setvalue)
Ok_Button.grid(row=0,column=2)

commands=["0","0","0","0"]

def red_control(val):
	time.sleep(0.1)
	commands[0]=val

def green_control(val):
	time.sleep(0.1)
	commands[1]=val

def blue_control(val):
	time.sleep(0.1)
	commands[2]=val

#Sliders for R,G,B
#slider_red=Scale(root,from_=0,to=pwm_val,orient=HORIZONTAL)
slider_red=Scale(root,from_=0,to=255,orient=HORIZONTAL,command=red_control)
slider_green=Scale(root,from_=0,to=255,orient=HORIZONTAL,command=green_control)
slider_blue=Scale(root,from_=0,to=255,orient=HORIZONTAL,command=blue_control)

#Label for R,G,B
label_red=Label(root,text="R",fg="red",relief=RAISED)
label_green=Label(root,text="G",fg="green",relief=RAISED)
label_blue=Label(root,text="B",fg="blue",relief=RAISED)

#Set the grid for R,G,B
slider_red.grid(row=1,column=1,columnspan=2)
slider_green.grid(row=2,column=1,columnspan=2)
slider_blue.grid(row=3,column=1,columnspan=2)

label_red.grid(row=1,column=0)
label_green.grid(row=2,column=0)
label_blue.grid(row=3,column=0)


def fade1():
	#ser.write("Porneste Fade1".encode('utf-8'))
	commands[3]=str(1)
	ser.write("<".encode('utf-8'))
	ser.write(commands[0].encode('utf-8'))
	ser.write(",".encode('utf-8'))
	#ser.write("Green: ".encode('utf-8'))
	ser.write(commands[1].encode('utf-8'))
	ser.write(",".encode('utf-8'))
	#ser.write("Blue: ".encode('utf-8'))
	ser.write(commands[2].encode('utf-8'))
	ser.write(",".encode('utf-8'))
	ser.write(commands[3].encode('utf-8'))
	ser.write(">".encode('utf-8'))
	#ser.write(commands[3].encode('utf-8'))
def fade2():
	#ser.write("Porneste Fade2".encode('utf-8'))
	commands[3]=str(2)
	ser.write("<".encode('utf-8'))
	ser.write(commands[0].encode('utf-8'))
	ser.write(",".encode('utf-8'))
	#ser.write("Green: ".encode('utf-8'))
	ser.write(commands[1].encode('utf-8'))
	ser.write(",".encode('utf-8'))
	#ser.write("Blue: ".encode('utf-8'))
	ser.write(commands[2].encode('utf-8'))
	ser.write(",".encode('utf-8'))
	ser.write(commands[3].encode('utf-8'))
	ser.write(">".encode('utf-8'))
	#ser.write(commands[3].encode('utf-8'))
def hue():
	#ser.write("Porneste HUE".encode('utf-8'))
	commands[3]=str(3)
	ser.write("<".encode('utf-8'))
	ser.write(commands[0].encode('utf-8'))
	ser.write(",".encode('utf-8'))
	#ser.write("Green: ".encode('utf-8'))
	ser.write(commands[1].encode('utf-8'))
	ser.write(",".encode('utf-8'))
	#ser.write("Blue: ".encode('utf-8'))
	ser.write(commands[2].encode('utf-8'))
	ser.write(",".encode('utf-8'))
	ser.write(commands[3].encode('utf-8'))
	ser.write(">".encode('utf-8'))
	#ser.write(commands[3].encode('utf-8'))

#Buttons for presets
Fade1_Button=Button(root,text="Fade 1",padx=10,borderwidth=2,command=fade1)
Fade1_Button.grid(row=4,column=0)

Fade2_Button=Button(root,text="Fade 2",padx=10,borderwidth=2,command=fade2)
Fade2_Button.grid(row=4,column=1)

Hue_Button=Button(root,text="HUE",padx=6,borderwidth=2,command=hue)
Hue_Button.grid(row=4,column=2)

#Reset button
def reset():
	slider_red.set(0)
	slider_green.set(0)
	slider_blue.set(0)
	E1.delete(0,END)
	slider_red.config(to_=255)
	slider_green.config(to_=255)
	slider_blue.config(to_=255)

def send():
	commands[3] = '0'
	ser.write("<".encode('utf-8'))
	ser.write(commands[0].encode('utf-8'))
	ser.write(",".encode('utf-8'))
	#ser.write("Green: ".encode('utf-8'))
	ser.write(commands[1].encode('utf-8'))
	ser.write(",".encode('utf-8'))
	#ser.write("Blue: ".encode('utf-8'))
	ser.write(commands[2].encode('utf-8'))
	ser.write(",".encode('utf-8'))
	ser.write(commands[3].encode('utf-8'))
	ser.write(">".encode('utf-8'))


Reset_Button=Button(root,text="Reset",borderwidth=2,command=reset)
Reset_Button.grid(row=5,column=1,columnspan=3,padx=50)

Send_Button=Button(root,text="Send",borderwidth=2,command=send)
Send_Button.grid(row=5, column=0, columnspan=2 )



root.mainloop()

ser.close()