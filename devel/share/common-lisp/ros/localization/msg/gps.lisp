; Auto-generated. Do not edit!


(cl:in-package localization-msg)


;//! \htmlinclude gps.msg.html

(cl:defclass <gps> (roslisp-msg-protocol:ros-message)
  ((FPD_Header
    :reader FPD_Header
    :initarg :FPD_Header
    :type cl:string
    :initform "")
   (FPD_GPSWeek
    :reader FPD_GPSWeek
    :initarg :FPD_GPSWeek
    :type cl:string
    :initform "")
   (FPD_GPSTime
    :reader FPD_GPSTime
    :initarg :FPD_GPSTime
    :type cl:string
    :initform "")
   (Heading
    :reader Heading
    :initarg :Heading
    :type cl:string
    :initform "")
   (Pitch
    :reader Pitch
    :initarg :Pitch
    :type cl:string
    :initform "")
   (Roll
    :reader Roll
    :initarg :Roll
    :type cl:string
    :initform "")
   (Lattitude
    :reader Lattitude
    :initarg :Lattitude
    :type cl:string
    :initform "")
   (Longitude
    :reader Longitude
    :initarg :Longitude
    :type cl:string
    :initform "")
   (Altitude
    :reader Altitude
    :initarg :Altitude
    :type cl:string
    :initform "")
   (Ve
    :reader Ve
    :initarg :Ve
    :type cl:string
    :initform "")
   (Vn
    :reader Vn
    :initarg :Vn
    :type cl:string
    :initform "")
   (Vu
    :reader Vu
    :initarg :Vu
    :type cl:string
    :initform "")
   (Baseline
    :reader Baseline
    :initarg :Baseline
    :type cl:string
    :initform "")
   (NSV1
    :reader NSV1
    :initarg :NSV1
    :type cl:string
    :initform "")
   (NSV2
    :reader NSV2
    :initarg :NSV2
    :type cl:string
    :initform "")
   (Status
    :reader Status
    :initarg :Status
    :type cl:string
    :initform "")
   (FPD_Cs
    :reader FPD_Cs
    :initarg :FPD_Cs
    :type cl:string
    :initform "")
   (IMU_Header
    :reader IMU_Header
    :initarg :IMU_Header
    :type cl:string
    :initform "")
   (IMU_GPSWeek
    :reader IMU_GPSWeek
    :initarg :IMU_GPSWeek
    :type cl:string
    :initform "")
   (IMU_GPSTime
    :reader IMU_GPSTime
    :initarg :IMU_GPSTime
    :type cl:string
    :initform "")
   (GyroX
    :reader GyroX
    :initarg :GyroX
    :type cl:string
    :initform "")
   (GyroY
    :reader GyroY
    :initarg :GyroY
    :type cl:string
    :initform "")
   (GyroZ
    :reader GyroZ
    :initarg :GyroZ
    :type cl:string
    :initform "")
   (AccX
    :reader AccX
    :initarg :AccX
    :type cl:string
    :initform "")
   (AccY
    :reader AccY
    :initarg :AccY
    :type cl:string
    :initform "")
   (AccZ
    :reader AccZ
    :initarg :AccZ
    :type cl:string
    :initform "")
   (Tpr
    :reader Tpr
    :initarg :Tpr
    :type cl:string
    :initform "")
   (IMU_Cs
    :reader IMU_Cs
    :initarg :IMU_Cs
    :type cl:string
    :initform "")
   (x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0))
)

(cl:defclass gps (<gps>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <gps>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'gps)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name localization-msg:<gps> is deprecated: use localization-msg:gps instead.")))

(cl:ensure-generic-function 'FPD_Header-val :lambda-list '(m))
(cl:defmethod FPD_Header-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:FPD_Header-val is deprecated.  Use localization-msg:FPD_Header instead.")
  (FPD_Header m))

(cl:ensure-generic-function 'FPD_GPSWeek-val :lambda-list '(m))
(cl:defmethod FPD_GPSWeek-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:FPD_GPSWeek-val is deprecated.  Use localization-msg:FPD_GPSWeek instead.")
  (FPD_GPSWeek m))

(cl:ensure-generic-function 'FPD_GPSTime-val :lambda-list '(m))
(cl:defmethod FPD_GPSTime-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:FPD_GPSTime-val is deprecated.  Use localization-msg:FPD_GPSTime instead.")
  (FPD_GPSTime m))

(cl:ensure-generic-function 'Heading-val :lambda-list '(m))
(cl:defmethod Heading-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:Heading-val is deprecated.  Use localization-msg:Heading instead.")
  (Heading m))

(cl:ensure-generic-function 'Pitch-val :lambda-list '(m))
(cl:defmethod Pitch-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:Pitch-val is deprecated.  Use localization-msg:Pitch instead.")
  (Pitch m))

(cl:ensure-generic-function 'Roll-val :lambda-list '(m))
(cl:defmethod Roll-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:Roll-val is deprecated.  Use localization-msg:Roll instead.")
  (Roll m))

(cl:ensure-generic-function 'Lattitude-val :lambda-list '(m))
(cl:defmethod Lattitude-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:Lattitude-val is deprecated.  Use localization-msg:Lattitude instead.")
  (Lattitude m))

(cl:ensure-generic-function 'Longitude-val :lambda-list '(m))
(cl:defmethod Longitude-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:Longitude-val is deprecated.  Use localization-msg:Longitude instead.")
  (Longitude m))

(cl:ensure-generic-function 'Altitude-val :lambda-list '(m))
(cl:defmethod Altitude-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:Altitude-val is deprecated.  Use localization-msg:Altitude instead.")
  (Altitude m))

(cl:ensure-generic-function 'Ve-val :lambda-list '(m))
(cl:defmethod Ve-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:Ve-val is deprecated.  Use localization-msg:Ve instead.")
  (Ve m))

(cl:ensure-generic-function 'Vn-val :lambda-list '(m))
(cl:defmethod Vn-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:Vn-val is deprecated.  Use localization-msg:Vn instead.")
  (Vn m))

(cl:ensure-generic-function 'Vu-val :lambda-list '(m))
(cl:defmethod Vu-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:Vu-val is deprecated.  Use localization-msg:Vu instead.")
  (Vu m))

(cl:ensure-generic-function 'Baseline-val :lambda-list '(m))
(cl:defmethod Baseline-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:Baseline-val is deprecated.  Use localization-msg:Baseline instead.")
  (Baseline m))

(cl:ensure-generic-function 'NSV1-val :lambda-list '(m))
(cl:defmethod NSV1-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:NSV1-val is deprecated.  Use localization-msg:NSV1 instead.")
  (NSV1 m))

(cl:ensure-generic-function 'NSV2-val :lambda-list '(m))
(cl:defmethod NSV2-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:NSV2-val is deprecated.  Use localization-msg:NSV2 instead.")
  (NSV2 m))

(cl:ensure-generic-function 'Status-val :lambda-list '(m))
(cl:defmethod Status-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:Status-val is deprecated.  Use localization-msg:Status instead.")
  (Status m))

(cl:ensure-generic-function 'FPD_Cs-val :lambda-list '(m))
(cl:defmethod FPD_Cs-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:FPD_Cs-val is deprecated.  Use localization-msg:FPD_Cs instead.")
  (FPD_Cs m))

(cl:ensure-generic-function 'IMU_Header-val :lambda-list '(m))
(cl:defmethod IMU_Header-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:IMU_Header-val is deprecated.  Use localization-msg:IMU_Header instead.")
  (IMU_Header m))

(cl:ensure-generic-function 'IMU_GPSWeek-val :lambda-list '(m))
(cl:defmethod IMU_GPSWeek-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:IMU_GPSWeek-val is deprecated.  Use localization-msg:IMU_GPSWeek instead.")
  (IMU_GPSWeek m))

(cl:ensure-generic-function 'IMU_GPSTime-val :lambda-list '(m))
(cl:defmethod IMU_GPSTime-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:IMU_GPSTime-val is deprecated.  Use localization-msg:IMU_GPSTime instead.")
  (IMU_GPSTime m))

(cl:ensure-generic-function 'GyroX-val :lambda-list '(m))
(cl:defmethod GyroX-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:GyroX-val is deprecated.  Use localization-msg:GyroX instead.")
  (GyroX m))

(cl:ensure-generic-function 'GyroY-val :lambda-list '(m))
(cl:defmethod GyroY-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:GyroY-val is deprecated.  Use localization-msg:GyroY instead.")
  (GyroY m))

(cl:ensure-generic-function 'GyroZ-val :lambda-list '(m))
(cl:defmethod GyroZ-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:GyroZ-val is deprecated.  Use localization-msg:GyroZ instead.")
  (GyroZ m))

(cl:ensure-generic-function 'AccX-val :lambda-list '(m))
(cl:defmethod AccX-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:AccX-val is deprecated.  Use localization-msg:AccX instead.")
  (AccX m))

(cl:ensure-generic-function 'AccY-val :lambda-list '(m))
(cl:defmethod AccY-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:AccY-val is deprecated.  Use localization-msg:AccY instead.")
  (AccY m))

(cl:ensure-generic-function 'AccZ-val :lambda-list '(m))
(cl:defmethod AccZ-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:AccZ-val is deprecated.  Use localization-msg:AccZ instead.")
  (AccZ m))

(cl:ensure-generic-function 'Tpr-val :lambda-list '(m))
(cl:defmethod Tpr-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:Tpr-val is deprecated.  Use localization-msg:Tpr instead.")
  (Tpr m))

(cl:ensure-generic-function 'IMU_Cs-val :lambda-list '(m))
(cl:defmethod IMU_Cs-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:IMU_Cs-val is deprecated.  Use localization-msg:IMU_Cs instead.")
  (IMU_Cs m))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:x-val is deprecated.  Use localization-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <gps>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader localization-msg:y-val is deprecated.  Use localization-msg:y instead.")
  (y m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <gps>) ostream)
  "Serializes a message object of type '<gps>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'FPD_Header))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'FPD_Header))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'FPD_GPSWeek))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'FPD_GPSWeek))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'FPD_GPSTime))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'FPD_GPSTime))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'Heading))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'Heading))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'Pitch))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'Pitch))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'Roll))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'Roll))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'Lattitude))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'Lattitude))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'Longitude))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'Longitude))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'Altitude))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'Altitude))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'Ve))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'Ve))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'Vn))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'Vn))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'Vu))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'Vu))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'Baseline))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'Baseline))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'NSV1))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'NSV1))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'NSV2))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'NSV2))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'Status))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'Status))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'FPD_Cs))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'FPD_Cs))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'IMU_Header))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'IMU_Header))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'IMU_GPSWeek))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'IMU_GPSWeek))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'IMU_GPSTime))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'IMU_GPSTime))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'GyroX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'GyroX))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'GyroY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'GyroY))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'GyroZ))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'GyroZ))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'AccX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'AccX))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'AccY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'AccY))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'AccZ))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'AccZ))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'Tpr))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'Tpr))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'IMU_Cs))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'IMU_Cs))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <gps>) istream)
  "Deserializes a message object of type '<gps>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'FPD_Header) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'FPD_Header) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'FPD_GPSWeek) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'FPD_GPSWeek) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'FPD_GPSTime) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'FPD_GPSTime) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Heading) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'Heading) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Pitch) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'Pitch) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Roll) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'Roll) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Lattitude) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'Lattitude) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Longitude) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'Longitude) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Altitude) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'Altitude) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Ve) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'Ve) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Vn) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'Vn) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Vu) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'Vu) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Baseline) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'Baseline) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'NSV1) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'NSV1) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'NSV2) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'NSV2) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Status) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'Status) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'FPD_Cs) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'FPD_Cs) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'IMU_Header) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'IMU_Header) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'IMU_GPSWeek) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'IMU_GPSWeek) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'IMU_GPSTime) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'IMU_GPSTime) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'GyroX) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'GyroX) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'GyroY) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'GyroY) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'GyroZ) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'GyroZ) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'AccX) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'AccX) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'AccY) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'AccY) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'AccZ) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'AccZ) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Tpr) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'Tpr) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'IMU_Cs) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'IMU_Cs) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<gps>)))
  "Returns string type for a message object of type '<gps>"
  "localization/gps")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'gps)))
  "Returns string type for a message object of type 'gps"
  "localization/gps")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<gps>)))
  "Returns md5sum for a message object of type '<gps>"
  "6cefa42fc634a5edcdb1a380b1794e86")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'gps)))
  "Returns md5sum for a message object of type 'gps"
  "6cefa42fc634a5edcdb1a380b1794e86")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<gps>)))
  "Returns full string definition for message of type '<gps>"
  (cl:format cl:nil "string FPD_Header~%string FPD_GPSWeek~%string FPD_GPSTime~%string Heading~%string Pitch~%string Roll~%string Lattitude~%string Longitude~%string Altitude~%string Ve~%string Vn~%string Vu~%string Baseline~%string NSV1~%string NSV2~%string Status~%string FPD_Cs~%~%string IMU_Header~%string IMU_GPSWeek~%string IMU_GPSTime~%string GyroX~%string GyroY~%string GyroZ~%string AccX~%string AccY~%string AccZ~%string Tpr~%string IMU_Cs~%float64 x ~%float64 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'gps)))
  "Returns full string definition for message of type 'gps"
  (cl:format cl:nil "string FPD_Header~%string FPD_GPSWeek~%string FPD_GPSTime~%string Heading~%string Pitch~%string Roll~%string Lattitude~%string Longitude~%string Altitude~%string Ve~%string Vn~%string Vu~%string Baseline~%string NSV1~%string NSV2~%string Status~%string FPD_Cs~%~%string IMU_Header~%string IMU_GPSWeek~%string IMU_GPSTime~%string GyroX~%string GyroY~%string GyroZ~%string AccX~%string AccY~%string AccZ~%string Tpr~%string IMU_Cs~%float64 x ~%float64 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <gps>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'FPD_Header))
     4 (cl:length (cl:slot-value msg 'FPD_GPSWeek))
     4 (cl:length (cl:slot-value msg 'FPD_GPSTime))
     4 (cl:length (cl:slot-value msg 'Heading))
     4 (cl:length (cl:slot-value msg 'Pitch))
     4 (cl:length (cl:slot-value msg 'Roll))
     4 (cl:length (cl:slot-value msg 'Lattitude))
     4 (cl:length (cl:slot-value msg 'Longitude))
     4 (cl:length (cl:slot-value msg 'Altitude))
     4 (cl:length (cl:slot-value msg 'Ve))
     4 (cl:length (cl:slot-value msg 'Vn))
     4 (cl:length (cl:slot-value msg 'Vu))
     4 (cl:length (cl:slot-value msg 'Baseline))
     4 (cl:length (cl:slot-value msg 'NSV1))
     4 (cl:length (cl:slot-value msg 'NSV2))
     4 (cl:length (cl:slot-value msg 'Status))
     4 (cl:length (cl:slot-value msg 'FPD_Cs))
     4 (cl:length (cl:slot-value msg 'IMU_Header))
     4 (cl:length (cl:slot-value msg 'IMU_GPSWeek))
     4 (cl:length (cl:slot-value msg 'IMU_GPSTime))
     4 (cl:length (cl:slot-value msg 'GyroX))
     4 (cl:length (cl:slot-value msg 'GyroY))
     4 (cl:length (cl:slot-value msg 'GyroZ))
     4 (cl:length (cl:slot-value msg 'AccX))
     4 (cl:length (cl:slot-value msg 'AccY))
     4 (cl:length (cl:slot-value msg 'AccZ))
     4 (cl:length (cl:slot-value msg 'Tpr))
     4 (cl:length (cl:slot-value msg 'IMU_Cs))
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <gps>))
  "Converts a ROS message object to a list"
  (cl:list 'gps
    (cl:cons ':FPD_Header (FPD_Header msg))
    (cl:cons ':FPD_GPSWeek (FPD_GPSWeek msg))
    (cl:cons ':FPD_GPSTime (FPD_GPSTime msg))
    (cl:cons ':Heading (Heading msg))
    (cl:cons ':Pitch (Pitch msg))
    (cl:cons ':Roll (Roll msg))
    (cl:cons ':Lattitude (Lattitude msg))
    (cl:cons ':Longitude (Longitude msg))
    (cl:cons ':Altitude (Altitude msg))
    (cl:cons ':Ve (Ve msg))
    (cl:cons ':Vn (Vn msg))
    (cl:cons ':Vu (Vu msg))
    (cl:cons ':Baseline (Baseline msg))
    (cl:cons ':NSV1 (NSV1 msg))
    (cl:cons ':NSV2 (NSV2 msg))
    (cl:cons ':Status (Status msg))
    (cl:cons ':FPD_Cs (FPD_Cs msg))
    (cl:cons ':IMU_Header (IMU_Header msg))
    (cl:cons ':IMU_GPSWeek (IMU_GPSWeek msg))
    (cl:cons ':IMU_GPSTime (IMU_GPSTime msg))
    (cl:cons ':GyroX (GyroX msg))
    (cl:cons ':GyroY (GyroY msg))
    (cl:cons ':GyroZ (GyroZ msg))
    (cl:cons ':AccX (AccX msg))
    (cl:cons ':AccY (AccY msg))
    (cl:cons ':AccZ (AccZ msg))
    (cl:cons ':Tpr (Tpr msg))
    (cl:cons ':IMU_Cs (IMU_Cs msg))
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
))
