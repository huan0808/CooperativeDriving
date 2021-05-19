;; Auto-generated. Do not edit!


(when (boundp 'algorithm::algorithm)
  (if (not (find-package "ALGORITHM"))
    (make-package "ALGORITHM"))
  (shadow 'algorithm (find-package "ALGORITHM")))
(unless (find-package "ALGORITHM::ALGORITHM")
  (make-package "ALGORITHM::ALGORITHM"))

(in-package "ROS")
;;//! \htmlinclude algorithm.msg.html


(defclass algorithm::algorithm
  :super ros::object
  :slots (_CurrentSteeringAngle _LongitudinalAccel ))

(defmethod algorithm::algorithm
  (:init
   (&key
    ((:CurrentSteeringAngle __CurrentSteeringAngle) 0.0)
    ((:LongitudinalAccel __LongitudinalAccel) 0.0)
    )
   (send-super :init)
   (setq _CurrentSteeringAngle (float __CurrentSteeringAngle))
   (setq _LongitudinalAccel (float __LongitudinalAccel))
   self)
  (:CurrentSteeringAngle
   (&optional __CurrentSteeringAngle)
   (if __CurrentSteeringAngle (setq _CurrentSteeringAngle __CurrentSteeringAngle)) _CurrentSteeringAngle)
  (:LongitudinalAccel
   (&optional __LongitudinalAccel)
   (if __LongitudinalAccel (setq _LongitudinalAccel __LongitudinalAccel)) _LongitudinalAccel)
  (:serialization-length
   ()
   (+
    ;; float64 _CurrentSteeringAngle
    8
    ;; float64 _LongitudinalAccel
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _CurrentSteeringAngle
       (sys::poke _CurrentSteeringAngle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _LongitudinalAccel
       (sys::poke _LongitudinalAccel (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _CurrentSteeringAngle
     (setq _CurrentSteeringAngle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _LongitudinalAccel
     (setq _LongitudinalAccel (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get algorithm::algorithm :md5sum-) "9844dd521b673e544e6966cec9aa7917")
(setf (get algorithm::algorithm :datatype-) "algorithm/algorithm")
(setf (get algorithm::algorithm :definition-)
      "float64 CurrentSteeringAngle
float64 LongitudinalAccel

")



(provide :algorithm/algorithm "9844dd521b673e544e6966cec9aa7917")


