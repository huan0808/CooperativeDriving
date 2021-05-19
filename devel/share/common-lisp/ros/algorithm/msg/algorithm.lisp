; Auto-generated. Do not edit!


(cl:in-package algorithm-msg)


;//! \htmlinclude algorithm.msg.html

(cl:defclass <algorithm> (roslisp-msg-protocol:ros-message)
  ((CurrentSteeringAngle
    :reader CurrentSteeringAngle
    :initarg :CurrentSteeringAngle
    :type cl:float
    :initform 0.0)
   (LongitudinalAccel
    :reader LongitudinalAccel
    :initarg :LongitudinalAccel
    :type cl:float
    :initform 0.0))
)

(cl:defclass algorithm (<algorithm>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <algorithm>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'algorithm)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name algorithm-msg:<algorithm> is deprecated: use algorithm-msg:algorithm instead.")))

(cl:ensure-generic-function 'CurrentSteeringAngle-val :lambda-list '(m))
(cl:defmethod CurrentSteeringAngle-val ((m <algorithm>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader algorithm-msg:CurrentSteeringAngle-val is deprecated.  Use algorithm-msg:CurrentSteeringAngle instead.")
  (CurrentSteeringAngle m))

(cl:ensure-generic-function 'LongitudinalAccel-val :lambda-list '(m))
(cl:defmethod LongitudinalAccel-val ((m <algorithm>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader algorithm-msg:LongitudinalAccel-val is deprecated.  Use algorithm-msg:LongitudinalAccel instead.")
  (LongitudinalAccel m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <algorithm>) ostream)
  "Serializes a message object of type '<algorithm>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'CurrentSteeringAngle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'LongitudinalAccel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <algorithm>) istream)
  "Deserializes a message object of type '<algorithm>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'CurrentSteeringAngle) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'LongitudinalAccel) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<algorithm>)))
  "Returns string type for a message object of type '<algorithm>"
  "algorithm/algorithm")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'algorithm)))
  "Returns string type for a message object of type 'algorithm"
  "algorithm/algorithm")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<algorithm>)))
  "Returns md5sum for a message object of type '<algorithm>"
  "9844dd521b673e544e6966cec9aa7917")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'algorithm)))
  "Returns md5sum for a message object of type 'algorithm"
  "9844dd521b673e544e6966cec9aa7917")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<algorithm>)))
  "Returns full string definition for message of type '<algorithm>"
  (cl:format cl:nil "float64 CurrentSteeringAngle~%float64 LongitudinalAccel~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'algorithm)))
  "Returns full string definition for message of type 'algorithm"
  (cl:format cl:nil "float64 CurrentSteeringAngle~%float64 LongitudinalAccel~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <algorithm>))
  (cl:+ 0
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <algorithm>))
  "Converts a ROS message object to a list"
  (cl:list 'algorithm
    (cl:cons ':CurrentSteeringAngle (CurrentSteeringAngle msg))
    (cl:cons ':LongitudinalAccel (LongitudinalAccel msg))
))
