# CooperativeDriving
**本项目为人机共驾项目相关代码**

## 1.  编译方式：
将本项目的三个模块 canbus，localization,control复制到 ros的catkin_ws/src文件夹下，在ros的catkin_ws目录下运行进行编译
```
catkin_make
```
运行：
打开新的终端运行启动文件
```
roslaunch canbus main.launch
```

## 2. 模块说明

localization: 负责与gps/imu通信，发布定位信息（x、y、heading等）

canbus: 负责与CAN总线通信，发布改装线控与底盘信息（方向盘角度、方向盘力矩和车速等）

control: 订阅localization和canbus，实时计算方向盘力矩命令并发送至改装线控，实现基于力反馈的人机共驾

## 3. 算法说明
![Alt text](https://raw.githubusercontent.com/huan0808/CooperativeDriving/main/backup/algorithm.png)
