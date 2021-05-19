; Auto-generated. Do not edit!


(cl:in-package canbus-msg)


;//! \htmlinclude frame.msg.html

(cl:defclass <frame> (roslisp-msg-protocol:ros-message)
  ((VI_GearInfo
    :reader VI_GearInfo
    :initarg :VI_GearInfo
    :type cl:integer
    :initform 0)
   (VI_BrakeInfo
    :reader VI_BrakeInfo
    :initarg :VI_BrakeInfo
    :type cl:integer
    :initform 0)
   (VI_Button1
    :reader VI_Button1
    :initarg :VI_Button1
    :type cl:integer
    :initform 0)
   (VI_Button2
    :reader VI_Button2
    :initarg :VI_Button2
    :type cl:integer
    :initform 0)
   (VI_HandBrakeSt
    :reader VI_HandBrakeSt
    :initarg :VI_HandBrakeSt
    :type cl:integer
    :initform 0)
   (VI_JerkSt
    :reader VI_JerkSt
    :initarg :VI_JerkSt
    :type cl:integer
    :initform 0)
   (VI_AccelPedalPosition
    :reader VI_AccelPedalPosition
    :initarg :VI_AccelPedalPosition
    :type cl:float
    :initform 0.0)
   (VI_FrontSteeringAngle
    :reader VI_FrontSteeringAngle
    :initarg :VI_FrontSteeringAngle
    :type cl:float
    :initform 0.0)
   (VI_RemainingTimes
    :reader VI_RemainingTimes
    :initarg :VI_RemainingTimes
    :type cl:float
    :initform 0.0)
   (VI_VehicleSpeed
    :reader VI_VehicleSpeed
    :initarg :VI_VehicleSpeed
    :type cl:float
    :initform 0.0)
   (SI2_LongitudinalAccel
    :reader SI2_LongitudinalAccel
    :initarg :SI2_LongitudinalAccel
    :type cl:float
    :initform 0.0)
   (SI2_LateralAccel
    :reader SI2_LateralAccel
    :initarg :SI2_LateralAccel
    :type cl:float
    :initform 0.0)
   (SI2_YawRate
    :reader SI2_YawRate
    :initarg :SI2_YawRate
    :type cl:float
    :initform 0.0)
   (SR_CurrentSteeringAngle
    :reader SR_CurrentSteeringAngle
    :initarg :SR_CurrentSteeringAngle
    :type cl:float
    :initform 0.0)
   (SR_CurrentSteeringSpeed
    :reader SR_CurrentSteeringSpeed
    :initarg :SR_CurrentSteeringSpeed
    :type cl:float
    :initform 0.0)
   (SR_HandTorque
    :reader SR_HandTorque
    :initarg :SR_HandTorque
    :type cl:float
    :initform 0.0)
   (SR_HandTorqueSign
    :reader SR_HandTorqueSign
    :initarg :SR_HandTorqueSign
    :type cl:float
    :initform 0.0)
   (SR_WorkMode
    :reader SR_WorkMode
    :initarg :SR_WorkMode
    :type cl:integer
    :initform 0)
   (SR_HandTorqueLimit
    :reader SR_HandTorqueLimit
    :initarg :SR_HandTorqueLimit
    :type cl:float
    :initform 0.0)
   (SR_Error
    :reader SR_Error
    :initarg :SR_Error
    :type cl:integer
    :initform 0)
   (SR_Warning
    :reader SR_Warning
    :initarg :SR_Warning
    :type cl:integer
    :initform 0)
   (SR_LiveCounter
    :reader SR_LiveCounter
    :initarg :SR_LiveCounter
    :type cl:float
    :initform 0.0))
)

(cl:defclass frame (<frame>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <frame>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'frame)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name canbus-msg:<frame> is deprecated: use canbus-msg:frame instead.")))

(cl:ensure-generic-function 'VI_GearInfo-val :lambda-list '(m))
(cl:defmethod VI_GearInfo-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:VI_GearInfo-val is deprecated.  Use canbus-msg:VI_GearInfo instead.")
  (VI_GearInfo m))

(cl:ensure-generic-function 'VI_BrakeInfo-val :lambda-list '(m))
(cl:defmethod VI_BrakeInfo-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:VI_BrakeInfo-val is deprecated.  Use canbus-msg:VI_BrakeInfo instead.")
  (VI_BrakeInfo m))

(cl:ensure-generic-function 'VI_Button1-val :lambda-list '(m))
(cl:defmethod VI_Button1-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:VI_Button1-val is deprecated.  Use canbus-msg:VI_Button1 instead.")
  (VI_Button1 m))

(cl:ensure-generic-function 'VI_Button2-val :lambda-list '(m))
(cl:defmethod VI_Button2-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:VI_Button2-val is deprecated.  Use canbus-msg:VI_Button2 instead.")
  (VI_Button2 m))

(cl:ensure-generic-function 'VI_HandBrakeSt-val :lambda-list '(m))
(cl:defmethod VI_HandBrakeSt-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:VI_HandBrakeSt-val is deprecated.  Use canbus-msg:VI_HandBrakeSt instead.")
  (VI_HandBrakeSt m))

(cl:ensure-generic-function 'VI_JerkSt-val :lambda-list '(m))
(cl:defmethod VI_JerkSt-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:VI_JerkSt-val is deprecated.  Use canbus-msg:VI_JerkSt instead.")
  (VI_JerkSt m))

(cl:ensure-generic-function 'VI_AccelPedalPosition-val :lambda-list '(m))
(cl:defmethod VI_AccelPedalPosition-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:VI_AccelPedalPosition-val is deprecated.  Use canbus-msg:VI_AccelPedalPosition instead.")
  (VI_AccelPedalPosition m))

(cl:ensure-generic-function 'VI_FrontSteeringAngle-val :lambda-list '(m))
(cl:defmethod VI_FrontSteeringAngle-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:VI_FrontSteeringAngle-val is deprecated.  Use canbus-msg:VI_FrontSteeringAngle instead.")
  (VI_FrontSteeringAngle m))

(cl:ensure-generic-function 'VI_RemainingTimes-val :lambda-list '(m))
(cl:defmethod VI_RemainingTimes-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:VI_RemainingTimes-val is deprecated.  Use canbus-msg:VI_RemainingTimes instead.")
  (VI_RemainingTimes m))

(cl:ensure-generic-function 'VI_VehicleSpeed-val :lambda-list '(m))
(cl:defmethod VI_VehicleSpeed-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:VI_VehicleSpeed-val is deprecated.  Use canbus-msg:VI_VehicleSpeed instead.")
  (VI_VehicleSpeed m))

(cl:ensure-generic-function 'SI2_LongitudinalAccel-val :lambda-list '(m))
(cl:defmethod SI2_LongitudinalAccel-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:SI2_LongitudinalAccel-val is deprecated.  Use canbus-msg:SI2_LongitudinalAccel instead.")
  (SI2_LongitudinalAccel m))

(cl:ensure-generic-function 'SI2_LateralAccel-val :lambda-list '(m))
(cl:defmethod SI2_LateralAccel-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:SI2_LateralAccel-val is deprecated.  Use canbus-msg:SI2_LateralAccel instead.")
  (SI2_LateralAccel m))

(cl:ensure-generic-function 'SI2_YawRate-val :lambda-list '(m))
(cl:defmethod SI2_YawRate-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:SI2_YawRate-val is deprecated.  Use canbus-msg:SI2_YawRate instead.")
  (SI2_YawRate m))

(cl:ensure-generic-function 'SR_CurrentSteeringAngle-val :lambda-list '(m))
(cl:defmethod SR_CurrentSteeringAngle-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:SR_CurrentSteeringAngle-val is deprecated.  Use canbus-msg:SR_CurrentSteeringAngle instead.")
  (SR_CurrentSteeringAngle m))

(cl:ensure-generic-function 'SR_CurrentSteeringSpeed-val :lambda-list '(m))
(cl:defmethod SR_CurrentSteeringSpeed-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:SR_CurrentSteeringSpeed-val is deprecated.  Use canbus-msg:SR_CurrentSteeringSpeed instead.")
  (SR_CurrentSteeringSpeed m))

(cl:ensure-generic-function 'SR_HandTorque-val :lambda-list '(m))
(cl:defmethod SR_HandTorque-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:SR_HandTorque-val is deprecated.  Use canbus-msg:SR_HandTorque instead.")
  (SR_HandTorque m))

(cl:ensure-generic-function 'SR_HandTorqueSign-val :lambda-list '(m))
(cl:defmethod SR_HandTorqueSign-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:SR_HandTorqueSign-val is deprecated.  Use canbus-msg:SR_HandTorqueSign instead.")
  (SR_HandTorqueSign m))

(cl:ensure-generic-function 'SR_WorkMode-val :lambda-list '(m))
(cl:defmethod SR_WorkMode-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:SR_WorkMode-val is deprecated.  Use canbus-msg:SR_WorkMode instead.")
  (SR_WorkMode m))

(cl:ensure-generic-function 'SR_HandTorqueLimit-val :lambda-list '(m))
(cl:defmethod SR_HandTorqueLimit-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:SR_HandTorqueLimit-val is deprecated.  Use canbus-msg:SR_HandTorqueLimit instead.")
  (SR_HandTorqueLimit m))

(cl:ensure-generic-function 'SR_Error-val :lambda-list '(m))
(cl:defmethod SR_Error-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:SR_Error-val is deprecated.  Use canbus-msg:SR_Error instead.")
  (SR_Error m))

(cl:ensure-generic-function 'SR_Warning-val :lambda-list '(m))
(cl:defmethod SR_Warning-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:SR_Warning-val is deprecated.  Use canbus-msg:SR_Warning instead.")
  (SR_Warning m))

(cl:ensure-generic-function 'SR_LiveCounter-val :lambda-list '(m))
(cl:defmethod SR_LiveCounter-val ((m <frame>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canbus-msg:SR_LiveCounter-val is deprecated.  Use canbus-msg:SR_LiveCounter instead.")
  (SR_LiveCounter m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <frame>) ostream)
  "Serializes a message object of type '<frame>"
  (cl:let* ((signed (cl:slot-value msg 'VI_GearInfo)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'VI_BrakeInfo)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'VI_Button1)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'VI_Button2)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'VI_HandBrakeSt)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'VI_JerkSt)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'VI_AccelPedalPosition))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'VI_FrontSteeringAngle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'VI_RemainingTimes))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'VI_VehicleSpeed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'SI2_LongitudinalAccel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'SI2_LateralAccel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'SI2_YawRate))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'SR_CurrentSteeringAngle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'SR_CurrentSteeringSpeed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'SR_HandTorque))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'SR_HandTorqueSign))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'SR_WorkMode)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'SR_HandTorqueLimit))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'SR_Error)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'SR_Warning)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'SR_LiveCounter))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <frame>) istream)
  "Deserializes a message object of type '<frame>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'VI_GearInfo) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'VI_BrakeInfo) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'VI_Button1) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'VI_Button2) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'VI_HandBrakeSt) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'VI_JerkSt) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'VI_AccelPedalPosition) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'VI_FrontSteeringAngle) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'VI_RemainingTimes) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'VI_VehicleSpeed) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'SI2_LongitudinalAccel) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'SI2_LateralAccel) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'SI2_YawRate) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'SR_CurrentSteeringAngle) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'SR_CurrentSteeringSpeed) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'SR_HandTorque) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'SR_HandTorqueSign) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'SR_WorkMode) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'SR_HandTorqueLimit) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'SR_Error) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'SR_Warning) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'SR_LiveCounter) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<frame>)))
  "Returns string type for a message object of type '<frame>"
  "canbus/frame")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'frame)))
  "Returns string type for a message object of type 'frame"
  "canbus/frame")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<frame>)))
  "Returns md5sum for a message object of type '<frame>"
  "9aaf52d1c4f27f1011105abbe0b2efe7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'frame)))
  "Returns md5sum for a message object of type 'frame"
  "9aaf52d1c4f27f1011105abbe0b2efe7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<frame>)))
  "Returns full string definition for message of type '<frame>"
  (cl:format cl:nil "int32 VI_GearInfo  ~%int32 VI_BrakeInfo  ~%int32 VI_Button1  ~%int32 VI_Button2  ~%int32 VI_HandBrakeSt  ~%int32 VI_JerkSt  ~%float64 VI_AccelPedalPosition  ~%float64 VI_FrontSteeringAngle  ~%float64 VI_RemainingTimes  ~%float64 VI_VehicleSpeed  ~%float64 SI2_LongitudinalAccel  ~%float64 SI2_LateralAccel  ~%float64 SI2_YawRate  ~%~%float64 SR_CurrentSteeringAngle ~%float64 SR_CurrentSteeringSpeed ~%float64 SR_HandTorque~%float64 SR_HandTorqueSign~%int32 SR_WorkMode ~%float64 SR_HandTorqueLimit ~%int32 SR_Error~%int32 SR_Warning ~%float64 SR_LiveCounter ~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'frame)))
  "Returns full string definition for message of type 'frame"
  (cl:format cl:nil "int32 VI_GearInfo  ~%int32 VI_BrakeInfo  ~%int32 VI_Button1  ~%int32 VI_Button2  ~%int32 VI_HandBrakeSt  ~%int32 VI_JerkSt  ~%float64 VI_AccelPedalPosition  ~%float64 VI_FrontSteeringAngle  ~%float64 VI_RemainingTimes  ~%float64 VI_VehicleSpeed  ~%float64 SI2_LongitudinalAccel  ~%float64 SI2_LateralAccel  ~%float64 SI2_YawRate  ~%~%float64 SR_CurrentSteeringAngle ~%float64 SR_CurrentSteeringSpeed ~%float64 SR_HandTorque~%float64 SR_HandTorqueSign~%int32 SR_WorkMode ~%float64 SR_HandTorqueLimit ~%int32 SR_Error~%int32 SR_Warning ~%float64 SR_LiveCounter ~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <frame>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
     8
     8
     8
     8
     8
     8
     8
     8
     8
     8
     8
     4
     8
     4
     4
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <frame>))
  "Converts a ROS message object to a list"
  (cl:list 'frame
    (cl:cons ':VI_GearInfo (VI_GearInfo msg))
    (cl:cons ':VI_BrakeInfo (VI_BrakeInfo msg))
    (cl:cons ':VI_Button1 (VI_Button1 msg))
    (cl:cons ':VI_Button2 (VI_Button2 msg))
    (cl:cons ':VI_HandBrakeSt (VI_HandBrakeSt msg))
    (cl:cons ':VI_JerkSt (VI_JerkSt msg))
    (cl:cons ':VI_AccelPedalPosition (VI_AccelPedalPosition msg))
    (cl:cons ':VI_FrontSteeringAngle (VI_FrontSteeringAngle msg))
    (cl:cons ':VI_RemainingTimes (VI_RemainingTimes msg))
    (cl:cons ':VI_VehicleSpeed (VI_VehicleSpeed msg))
    (cl:cons ':SI2_LongitudinalAccel (SI2_LongitudinalAccel msg))
    (cl:cons ':SI2_LateralAccel (SI2_LateralAccel msg))
    (cl:cons ':SI2_YawRate (SI2_YawRate msg))
    (cl:cons ':SR_CurrentSteeringAngle (SR_CurrentSteeringAngle msg))
    (cl:cons ':SR_CurrentSteeringSpeed (SR_CurrentSteeringSpeed msg))
    (cl:cons ':SR_HandTorque (SR_HandTorque msg))
    (cl:cons ':SR_HandTorqueSign (SR_HandTorqueSign msg))
    (cl:cons ':SR_WorkMode (SR_WorkMode msg))
    (cl:cons ':SR_HandTorqueLimit (SR_HandTorqueLimit msg))
    (cl:cons ':SR_Error (SR_Error msg))
    (cl:cons ':SR_Warning (SR_Warning msg))
    (cl:cons ':SR_LiveCounter (SR_LiveCounter msg))
))
