# CooperativeDriving
**本项目为人机共驾项目相关代码**


## 1.  运行方式：

### 宿主机环境编译
```
mkdir -p catkin_ws/src && cd src && git clone git@github.com:huan0808/CooperativeDriving.git
cd .. &&  catkin_make
```
### docker环境编译
```
./make_container.sh cooperative
./start_container.sh cooperative  cooperative_container
mkdir -p catkin_ws/src && cd src && git clone git@github.com:huan0808/CooperativeDriving.git
cd .. &&  catkin_make
```

### 运行：
```
roslaunch launcher start_drive.launch
```


## 2. 模块说明
![Alt text](https://github.com/huan0808/CooperativeDriving/blob/main/backup/%E9%A1%B9%E7%9B%AE%E7%9B%B8%E5%85%B3%20(2).jpg
"软件框架")

localization: 负责与gps/imu通信，采用两个线程，一个线程读取usb字符设备ttyACM0并对字符串进行解析，一个线程发布定位信息（x、y、heading等）到topic GPS_INFO

canbus: 负责与CAN总线通信，采用两个线程，一个线程通过socket读取网络设备can0并对CAN报文进行解析，一个线程发布改装线控与底盘信息（方向盘角度、方向盘力矩和车速等）到topic CAN_INFO

control: 负责车辆的控制，采用两个线程，一个线程订阅GPS_INFO和CAN_INFO，一个线程实时计算方向盘力矩命令并将其编码成CAN报文，通过CAN总线发送至改装线控，实现基于力反馈的人机共驾

## 3. 算法说明
![Alt text](https://raw.githubusercontent.com/huan0808/CooperativeDriving/main/backup/algorithm.png)
