import matplotlib.pyplot as plt
import csv
import os
import sys

# sys.argv[0] is the python file path
with open(sys.argv[1]) as csvfile:
    reader = csv.DictReader(csvfile)
    data = list(reader)

column = [row['x'] for row in data]
rowy = [row['y'] for row in data]
pre_steer = [row['front_steering_angle'] for row in data]


refDatax=[]
refDatay=[]
pre_angle=[]
d=1
for i in range(int(len(column)/100)*100):
    refDatax.append(float(column[i]))
    refDatay.append(float(rowy[i]))
    pre_angle.append(float(pre_steer[i]))


for root, _, files in os.walk(sys.argv[2]):
    i=1
files.sort()
fileLength = len(files)

with open(root + "/" + files[fileLength-sys.argv[3]]) as csvfile:
    reader = csv.DictReader(csvfile)
    data = list(reader)

column = [row['x'] for row in data]
rowy = [row['y'] for row in data]
lateralError = [row['lateral_error'] for row in data]
nowSteer = [row['front_steering_angle'] for row in data]
torqueRow = [row['torque'] for row in data]

testDatax=[]
testDatay=[]
ErrorData=[]
nowAngle =[]
torque =[]

for i in range(int(len(column)/100)*100):
    testDatax.append(float(column[i]))
    testDatay.append(float(rowy[i]))
    if float(lateralError[i]) != -99:
	    ErrorData.append(float(lateralError[i]))
	    nowAngle.append(float(nowSteer[i]))
	    torque.append(float(torqueRow[i]))
    		

print(i)
fig = plt.figure()
ax = fig.add_subplot(2,1,1)
ax.set_title("X Y scotter")
ax.plot(refDatax, refDatay, 'r')
ax.plot(testDatax, testDatay, 'g')
ax.grid()


timenow = list(range(len(torque)))
ax = fig.add_subplot(2,1,2)
ax.plot(timenow, torque, 'r')
ax.grid()
ax.set_title("torque")
plt.show()

time = list(range(len(ErrorData)))
plt.plot(time, ErrorData, 'g')
plt.show()
