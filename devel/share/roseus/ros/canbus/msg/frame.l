;; Auto-generated. Do not edit!


(when (boundp 'canbus::frame)
  (if (not (find-package "CANBUS"))
    (make-package "CANBUS"))
  (shadow 'frame (find-package "CANBUS")))
(unless (find-package "CANBUS::FRAME")
  (make-package "CANBUS::FRAME"))

(in-package "ROS")
;;//! \htmlinclude frame.msg.html


(defclass canbus::frame
  :super ros::object
  :slots (_VI_GearInfo _VI_BrakeInfo _VI_Button1 _VI_Button2 _VI_HandBrakeSt _VI_JerkSt _VI_AccelPedalPosition _VI_FrontSteeringAngle _VI_RemainingTimes _VI_VehicleSpeed _SI2_LongitudinalAccel _SI2_LateralAccel _SI2_YawRate _SR_CurrentSteeringAngle _SR_CurrentSteeringSpeed _SR_HandTorque _SR_HandTorqueSign _SR_WorkMode _SR_HandTorqueLimit _SR_Error _SR_Warning _SR_LiveCounter ))

(defmethod canbus::frame
  (:init
   (&key
    ((:VI_GearInfo __VI_GearInfo) 0)
    ((:VI_BrakeInfo __VI_BrakeInfo) 0)
    ((:VI_Button1 __VI_Button1) 0)
    ((:VI_Button2 __VI_Button2) 0)
    ((:VI_HandBrakeSt __VI_HandBrakeSt) 0)
    ((:VI_JerkSt __VI_JerkSt) 0)
    ((:VI_AccelPedalPosition __VI_AccelPedalPosition) 0.0)
    ((:VI_FrontSteeringAngle __VI_FrontSteeringAngle) 0.0)
    ((:VI_RemainingTimes __VI_RemainingTimes) 0.0)
    ((:VI_VehicleSpeed __VI_VehicleSpeed) 0.0)
    ((:SI2_LongitudinalAccel __SI2_LongitudinalAccel) 0.0)
    ((:SI2_LateralAccel __SI2_LateralAccel) 0.0)
    ((:SI2_YawRate __SI2_YawRate) 0.0)
    ((:SR_CurrentSteeringAngle __SR_CurrentSteeringAngle) 0.0)
    ((:SR_CurrentSteeringSpeed __SR_CurrentSteeringSpeed) 0.0)
    ((:SR_HandTorque __SR_HandTorque) 0.0)
    ((:SR_HandTorqueSign __SR_HandTorqueSign) 0.0)
    ((:SR_WorkMode __SR_WorkMode) 0)
    ((:SR_HandTorqueLimit __SR_HandTorqueLimit) 0.0)
    ((:SR_Error __SR_Error) 0)
    ((:SR_Warning __SR_Warning) 0)
    ((:SR_LiveCounter __SR_LiveCounter) 0.0)
    )
   (send-super :init)
   (setq _VI_GearInfo (round __VI_GearInfo))
   (setq _VI_BrakeInfo (round __VI_BrakeInfo))
   (setq _VI_Button1 (round __VI_Button1))
   (setq _VI_Button2 (round __VI_Button2))
   (setq _VI_HandBrakeSt (round __VI_HandBrakeSt))
   (setq _VI_JerkSt (round __VI_JerkSt))
   (setq _VI_AccelPedalPosition (float __VI_AccelPedalPosition))
   (setq _VI_FrontSteeringAngle (float __VI_FrontSteeringAngle))
   (setq _VI_RemainingTimes (float __VI_RemainingTimes))
   (setq _VI_VehicleSpeed (float __VI_VehicleSpeed))
   (setq _SI2_LongitudinalAccel (float __SI2_LongitudinalAccel))
   (setq _SI2_LateralAccel (float __SI2_LateralAccel))
   (setq _SI2_YawRate (float __SI2_YawRate))
   (setq _SR_CurrentSteeringAngle (float __SR_CurrentSteeringAngle))
   (setq _SR_CurrentSteeringSpeed (float __SR_CurrentSteeringSpeed))
   (setq _SR_HandTorque (float __SR_HandTorque))
   (setq _SR_HandTorqueSign (float __SR_HandTorqueSign))
   (setq _SR_WorkMode (round __SR_WorkMode))
   (setq _SR_HandTorqueLimit (float __SR_HandTorqueLimit))
   (setq _SR_Error (round __SR_Error))
   (setq _SR_Warning (round __SR_Warning))
   (setq _SR_LiveCounter (float __SR_LiveCounter))
   self)
  (:VI_GearInfo
   (&optional __VI_GearInfo)
   (if __VI_GearInfo (setq _VI_GearInfo __VI_GearInfo)) _VI_GearInfo)
  (:VI_BrakeInfo
   (&optional __VI_BrakeInfo)
   (if __VI_BrakeInfo (setq _VI_BrakeInfo __VI_BrakeInfo)) _VI_BrakeInfo)
  (:VI_Button1
   (&optional __VI_Button1)
   (if __VI_Button1 (setq _VI_Button1 __VI_Button1)) _VI_Button1)
  (:VI_Button2
   (&optional __VI_Button2)
   (if __VI_Button2 (setq _VI_Button2 __VI_Button2)) _VI_Button2)
  (:VI_HandBrakeSt
   (&optional __VI_HandBrakeSt)
   (if __VI_HandBrakeSt (setq _VI_HandBrakeSt __VI_HandBrakeSt)) _VI_HandBrakeSt)
  (:VI_JerkSt
   (&optional __VI_JerkSt)
   (if __VI_JerkSt (setq _VI_JerkSt __VI_JerkSt)) _VI_JerkSt)
  (:VI_AccelPedalPosition
   (&optional __VI_AccelPedalPosition)
   (if __VI_AccelPedalPosition (setq _VI_AccelPedalPosition __VI_AccelPedalPosition)) _VI_AccelPedalPosition)
  (:VI_FrontSteeringAngle
   (&optional __VI_FrontSteeringAngle)
   (if __VI_FrontSteeringAngle (setq _VI_FrontSteeringAngle __VI_FrontSteeringAngle)) _VI_FrontSteeringAngle)
  (:VI_RemainingTimes
   (&optional __VI_RemainingTimes)
   (if __VI_RemainingTimes (setq _VI_RemainingTimes __VI_RemainingTimes)) _VI_RemainingTimes)
  (:VI_VehicleSpeed
   (&optional __VI_VehicleSpeed)
   (if __VI_VehicleSpeed (setq _VI_VehicleSpeed __VI_VehicleSpeed)) _VI_VehicleSpeed)
  (:SI2_LongitudinalAccel
   (&optional __SI2_LongitudinalAccel)
   (if __SI2_LongitudinalAccel (setq _SI2_LongitudinalAccel __SI2_LongitudinalAccel)) _SI2_LongitudinalAccel)
  (:SI2_LateralAccel
   (&optional __SI2_LateralAccel)
   (if __SI2_LateralAccel (setq _SI2_LateralAccel __SI2_LateralAccel)) _SI2_LateralAccel)
  (:SI2_YawRate
   (&optional __SI2_YawRate)
   (if __SI2_YawRate (setq _SI2_YawRate __SI2_YawRate)) _SI2_YawRate)
  (:SR_CurrentSteeringAngle
   (&optional __SR_CurrentSteeringAngle)
   (if __SR_CurrentSteeringAngle (setq _SR_CurrentSteeringAngle __SR_CurrentSteeringAngle)) _SR_CurrentSteeringAngle)
  (:SR_CurrentSteeringSpeed
   (&optional __SR_CurrentSteeringSpeed)
   (if __SR_CurrentSteeringSpeed (setq _SR_CurrentSteeringSpeed __SR_CurrentSteeringSpeed)) _SR_CurrentSteeringSpeed)
  (:SR_HandTorque
   (&optional __SR_HandTorque)
   (if __SR_HandTorque (setq _SR_HandTorque __SR_HandTorque)) _SR_HandTorque)
  (:SR_HandTorqueSign
   (&optional __SR_HandTorqueSign)
   (if __SR_HandTorqueSign (setq _SR_HandTorqueSign __SR_HandTorqueSign)) _SR_HandTorqueSign)
  (:SR_WorkMode
   (&optional __SR_WorkMode)
   (if __SR_WorkMode (setq _SR_WorkMode __SR_WorkMode)) _SR_WorkMode)
  (:SR_HandTorqueLimit
   (&optional __SR_HandTorqueLimit)
   (if __SR_HandTorqueLimit (setq _SR_HandTorqueLimit __SR_HandTorqueLimit)) _SR_HandTorqueLimit)
  (:SR_Error
   (&optional __SR_Error)
   (if __SR_Error (setq _SR_Error __SR_Error)) _SR_Error)
  (:SR_Warning
   (&optional __SR_Warning)
   (if __SR_Warning (setq _SR_Warning __SR_Warning)) _SR_Warning)
  (:SR_LiveCounter
   (&optional __SR_LiveCounter)
   (if __SR_LiveCounter (setq _SR_LiveCounter __SR_LiveCounter)) _SR_LiveCounter)
  (:serialization-length
   ()
   (+
    ;; int32 _VI_GearInfo
    4
    ;; int32 _VI_BrakeInfo
    4
    ;; int32 _VI_Button1
    4
    ;; int32 _VI_Button2
    4
    ;; int32 _VI_HandBrakeSt
    4
    ;; int32 _VI_JerkSt
    4
    ;; float64 _VI_AccelPedalPosition
    8
    ;; float64 _VI_FrontSteeringAngle
    8
    ;; float64 _VI_RemainingTimes
    8
    ;; float64 _VI_VehicleSpeed
    8
    ;; float64 _SI2_LongitudinalAccel
    8
    ;; float64 _SI2_LateralAccel
    8
    ;; float64 _SI2_YawRate
    8
    ;; float64 _SR_CurrentSteeringAngle
    8
    ;; float64 _SR_CurrentSteeringSpeed
    8
    ;; float64 _SR_HandTorque
    8
    ;; float64 _SR_HandTorqueSign
    8
    ;; int32 _SR_WorkMode
    4
    ;; float64 _SR_HandTorqueLimit
    8
    ;; int32 _SR_Error
    4
    ;; int32 _SR_Warning
    4
    ;; float64 _SR_LiveCounter
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _VI_GearInfo
       (write-long _VI_GearInfo s)
     ;; int32 _VI_BrakeInfo
       (write-long _VI_BrakeInfo s)
     ;; int32 _VI_Button1
       (write-long _VI_Button1 s)
     ;; int32 _VI_Button2
       (write-long _VI_Button2 s)
     ;; int32 _VI_HandBrakeSt
       (write-long _VI_HandBrakeSt s)
     ;; int32 _VI_JerkSt
       (write-long _VI_JerkSt s)
     ;; float64 _VI_AccelPedalPosition
       (sys::poke _VI_AccelPedalPosition (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _VI_FrontSteeringAngle
       (sys::poke _VI_FrontSteeringAngle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _VI_RemainingTimes
       (sys::poke _VI_RemainingTimes (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _VI_VehicleSpeed
       (sys::poke _VI_VehicleSpeed (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _SI2_LongitudinalAccel
       (sys::poke _SI2_LongitudinalAccel (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _SI2_LateralAccel
       (sys::poke _SI2_LateralAccel (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _SI2_YawRate
       (sys::poke _SI2_YawRate (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _SR_CurrentSteeringAngle
       (sys::poke _SR_CurrentSteeringAngle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _SR_CurrentSteeringSpeed
       (sys::poke _SR_CurrentSteeringSpeed (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _SR_HandTorque
       (sys::poke _SR_HandTorque (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _SR_HandTorqueSign
       (sys::poke _SR_HandTorqueSign (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int32 _SR_WorkMode
       (write-long _SR_WorkMode s)
     ;; float64 _SR_HandTorqueLimit
       (sys::poke _SR_HandTorqueLimit (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int32 _SR_Error
       (write-long _SR_Error s)
     ;; int32 _SR_Warning
       (write-long _SR_Warning s)
     ;; float64 _SR_LiveCounter
       (sys::poke _SR_LiveCounter (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _VI_GearInfo
     (setq _VI_GearInfo (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _VI_BrakeInfo
     (setq _VI_BrakeInfo (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _VI_Button1
     (setq _VI_Button1 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _VI_Button2
     (setq _VI_Button2 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _VI_HandBrakeSt
     (setq _VI_HandBrakeSt (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _VI_JerkSt
     (setq _VI_JerkSt (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _VI_AccelPedalPosition
     (setq _VI_AccelPedalPosition (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _VI_FrontSteeringAngle
     (setq _VI_FrontSteeringAngle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _VI_RemainingTimes
     (setq _VI_RemainingTimes (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _VI_VehicleSpeed
     (setq _VI_VehicleSpeed (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _SI2_LongitudinalAccel
     (setq _SI2_LongitudinalAccel (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _SI2_LateralAccel
     (setq _SI2_LateralAccel (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _SI2_YawRate
     (setq _SI2_YawRate (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _SR_CurrentSteeringAngle
     (setq _SR_CurrentSteeringAngle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _SR_CurrentSteeringSpeed
     (setq _SR_CurrentSteeringSpeed (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _SR_HandTorque
     (setq _SR_HandTorque (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _SR_HandTorqueSign
     (setq _SR_HandTorqueSign (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int32 _SR_WorkMode
     (setq _SR_WorkMode (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _SR_HandTorqueLimit
     (setq _SR_HandTorqueLimit (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int32 _SR_Error
     (setq _SR_Error (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _SR_Warning
     (setq _SR_Warning (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _SR_LiveCounter
     (setq _SR_LiveCounter (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get canbus::frame :md5sum-) "9aaf52d1c4f27f1011105abbe0b2efe7")
(setf (get canbus::frame :datatype-) "canbus/frame")
(setf (get canbus::frame :definition-)
      "int32 VI_GearInfo  
int32 VI_BrakeInfo  
int32 VI_Button1  
int32 VI_Button2  
int32 VI_HandBrakeSt  
int32 VI_JerkSt  
float64 VI_AccelPedalPosition  
float64 VI_FrontSteeringAngle  
float64 VI_RemainingTimes  
float64 VI_VehicleSpeed  
float64 SI2_LongitudinalAccel  
float64 SI2_LateralAccel  
float64 SI2_YawRate  

float64 SR_CurrentSteeringAngle 
float64 SR_CurrentSteeringSpeed 
float64 SR_HandTorque
float64 SR_HandTorqueSign
int32 SR_WorkMode 
float64 SR_HandTorqueLimit 
int32 SR_Error
int32 SR_Warning 
float64 SR_LiveCounter 
")



(provide :canbus/frame "9aaf52d1c4f27f1011105abbe0b2efe7")


