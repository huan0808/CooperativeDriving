;; Auto-generated. Do not edit!


(when (boundp 'localization::gps)
  (if (not (find-package "LOCALIZATION"))
    (make-package "LOCALIZATION"))
  (shadow 'gps (find-package "LOCALIZATION")))
(unless (find-package "LOCALIZATION::GPS")
  (make-package "LOCALIZATION::GPS"))

(in-package "ROS")
;;//! \htmlinclude gps.msg.html


(defclass localization::gps
  :super ros::object
  :slots (_FPD_Header _FPD_GPSWeek _FPD_GPSTime _Heading _Pitch _Roll _Lattitude _Longitude _Altitude _Ve _Vn _Vu _Baseline _NSV1 _NSV2 _Status _FPD_Cs _IMU_Header _IMU_GPSWeek _IMU_GPSTime _GyroX _GyroY _GyroZ _AccX _AccY _AccZ _Tpr _IMU_Cs _x _y ))

(defmethod localization::gps
  (:init
   (&key
    ((:FPD_Header __FPD_Header) "")
    ((:FPD_GPSWeek __FPD_GPSWeek) "")
    ((:FPD_GPSTime __FPD_GPSTime) "")
    ((:Heading __Heading) "")
    ((:Pitch __Pitch) "")
    ((:Roll __Roll) "")
    ((:Lattitude __Lattitude) "")
    ((:Longitude __Longitude) "")
    ((:Altitude __Altitude) "")
    ((:Ve __Ve) "")
    ((:Vn __Vn) "")
    ((:Vu __Vu) "")
    ((:Baseline __Baseline) "")
    ((:NSV1 __NSV1) "")
    ((:NSV2 __NSV2) "")
    ((:Status __Status) "")
    ((:FPD_Cs __FPD_Cs) "")
    ((:IMU_Header __IMU_Header) "")
    ((:IMU_GPSWeek __IMU_GPSWeek) "")
    ((:IMU_GPSTime __IMU_GPSTime) "")
    ((:GyroX __GyroX) "")
    ((:GyroY __GyroY) "")
    ((:GyroZ __GyroZ) "")
    ((:AccX __AccX) "")
    ((:AccY __AccY) "")
    ((:AccZ __AccZ) "")
    ((:Tpr __Tpr) "")
    ((:IMU_Cs __IMU_Cs) "")
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    )
   (send-super :init)
   (setq _FPD_Header (string __FPD_Header))
   (setq _FPD_GPSWeek (string __FPD_GPSWeek))
   (setq _FPD_GPSTime (string __FPD_GPSTime))
   (setq _Heading (string __Heading))
   (setq _Pitch (string __Pitch))
   (setq _Roll (string __Roll))
   (setq _Lattitude (string __Lattitude))
   (setq _Longitude (string __Longitude))
   (setq _Altitude (string __Altitude))
   (setq _Ve (string __Ve))
   (setq _Vn (string __Vn))
   (setq _Vu (string __Vu))
   (setq _Baseline (string __Baseline))
   (setq _NSV1 (string __NSV1))
   (setq _NSV2 (string __NSV2))
   (setq _Status (string __Status))
   (setq _FPD_Cs (string __FPD_Cs))
   (setq _IMU_Header (string __IMU_Header))
   (setq _IMU_GPSWeek (string __IMU_GPSWeek))
   (setq _IMU_GPSTime (string __IMU_GPSTime))
   (setq _GyroX (string __GyroX))
   (setq _GyroY (string __GyroY))
   (setq _GyroZ (string __GyroZ))
   (setq _AccX (string __AccX))
   (setq _AccY (string __AccY))
   (setq _AccZ (string __AccZ))
   (setq _Tpr (string __Tpr))
   (setq _IMU_Cs (string __IMU_Cs))
   (setq _x (float __x))
   (setq _y (float __y))
   self)
  (:FPD_Header
   (&optional __FPD_Header)
   (if __FPD_Header (setq _FPD_Header __FPD_Header)) _FPD_Header)
  (:FPD_GPSWeek
   (&optional __FPD_GPSWeek)
   (if __FPD_GPSWeek (setq _FPD_GPSWeek __FPD_GPSWeek)) _FPD_GPSWeek)
  (:FPD_GPSTime
   (&optional __FPD_GPSTime)
   (if __FPD_GPSTime (setq _FPD_GPSTime __FPD_GPSTime)) _FPD_GPSTime)
  (:Heading
   (&optional __Heading)
   (if __Heading (setq _Heading __Heading)) _Heading)
  (:Pitch
   (&optional __Pitch)
   (if __Pitch (setq _Pitch __Pitch)) _Pitch)
  (:Roll
   (&optional __Roll)
   (if __Roll (setq _Roll __Roll)) _Roll)
  (:Lattitude
   (&optional __Lattitude)
   (if __Lattitude (setq _Lattitude __Lattitude)) _Lattitude)
  (:Longitude
   (&optional __Longitude)
   (if __Longitude (setq _Longitude __Longitude)) _Longitude)
  (:Altitude
   (&optional __Altitude)
   (if __Altitude (setq _Altitude __Altitude)) _Altitude)
  (:Ve
   (&optional __Ve)
   (if __Ve (setq _Ve __Ve)) _Ve)
  (:Vn
   (&optional __Vn)
   (if __Vn (setq _Vn __Vn)) _Vn)
  (:Vu
   (&optional __Vu)
   (if __Vu (setq _Vu __Vu)) _Vu)
  (:Baseline
   (&optional __Baseline)
   (if __Baseline (setq _Baseline __Baseline)) _Baseline)
  (:NSV1
   (&optional __NSV1)
   (if __NSV1 (setq _NSV1 __NSV1)) _NSV1)
  (:NSV2
   (&optional __NSV2)
   (if __NSV2 (setq _NSV2 __NSV2)) _NSV2)
  (:Status
   (&optional __Status)
   (if __Status (setq _Status __Status)) _Status)
  (:FPD_Cs
   (&optional __FPD_Cs)
   (if __FPD_Cs (setq _FPD_Cs __FPD_Cs)) _FPD_Cs)
  (:IMU_Header
   (&optional __IMU_Header)
   (if __IMU_Header (setq _IMU_Header __IMU_Header)) _IMU_Header)
  (:IMU_GPSWeek
   (&optional __IMU_GPSWeek)
   (if __IMU_GPSWeek (setq _IMU_GPSWeek __IMU_GPSWeek)) _IMU_GPSWeek)
  (:IMU_GPSTime
   (&optional __IMU_GPSTime)
   (if __IMU_GPSTime (setq _IMU_GPSTime __IMU_GPSTime)) _IMU_GPSTime)
  (:GyroX
   (&optional __GyroX)
   (if __GyroX (setq _GyroX __GyroX)) _GyroX)
  (:GyroY
   (&optional __GyroY)
   (if __GyroY (setq _GyroY __GyroY)) _GyroY)
  (:GyroZ
   (&optional __GyroZ)
   (if __GyroZ (setq _GyroZ __GyroZ)) _GyroZ)
  (:AccX
   (&optional __AccX)
   (if __AccX (setq _AccX __AccX)) _AccX)
  (:AccY
   (&optional __AccY)
   (if __AccY (setq _AccY __AccY)) _AccY)
  (:AccZ
   (&optional __AccZ)
   (if __AccZ (setq _AccZ __AccZ)) _AccZ)
  (:Tpr
   (&optional __Tpr)
   (if __Tpr (setq _Tpr __Tpr)) _Tpr)
  (:IMU_Cs
   (&optional __IMU_Cs)
   (if __IMU_Cs (setq _IMU_Cs __IMU_Cs)) _IMU_Cs)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:serialization-length
   ()
   (+
    ;; string _FPD_Header
    4 (length _FPD_Header)
    ;; string _FPD_GPSWeek
    4 (length _FPD_GPSWeek)
    ;; string _FPD_GPSTime
    4 (length _FPD_GPSTime)
    ;; string _Heading
    4 (length _Heading)
    ;; string _Pitch
    4 (length _Pitch)
    ;; string _Roll
    4 (length _Roll)
    ;; string _Lattitude
    4 (length _Lattitude)
    ;; string _Longitude
    4 (length _Longitude)
    ;; string _Altitude
    4 (length _Altitude)
    ;; string _Ve
    4 (length _Ve)
    ;; string _Vn
    4 (length _Vn)
    ;; string _Vu
    4 (length _Vu)
    ;; string _Baseline
    4 (length _Baseline)
    ;; string _NSV1
    4 (length _NSV1)
    ;; string _NSV2
    4 (length _NSV2)
    ;; string _Status
    4 (length _Status)
    ;; string _FPD_Cs
    4 (length _FPD_Cs)
    ;; string _IMU_Header
    4 (length _IMU_Header)
    ;; string _IMU_GPSWeek
    4 (length _IMU_GPSWeek)
    ;; string _IMU_GPSTime
    4 (length _IMU_GPSTime)
    ;; string _GyroX
    4 (length _GyroX)
    ;; string _GyroY
    4 (length _GyroY)
    ;; string _GyroZ
    4 (length _GyroZ)
    ;; string _AccX
    4 (length _AccX)
    ;; string _AccY
    4 (length _AccY)
    ;; string _AccZ
    4 (length _AccZ)
    ;; string _Tpr
    4 (length _Tpr)
    ;; string _IMU_Cs
    4 (length _IMU_Cs)
    ;; float64 _x
    8
    ;; float64 _y
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _FPD_Header
       (write-long (length _FPD_Header) s) (princ _FPD_Header s)
     ;; string _FPD_GPSWeek
       (write-long (length _FPD_GPSWeek) s) (princ _FPD_GPSWeek s)
     ;; string _FPD_GPSTime
       (write-long (length _FPD_GPSTime) s) (princ _FPD_GPSTime s)
     ;; string _Heading
       (write-long (length _Heading) s) (princ _Heading s)
     ;; string _Pitch
       (write-long (length _Pitch) s) (princ _Pitch s)
     ;; string _Roll
       (write-long (length _Roll) s) (princ _Roll s)
     ;; string _Lattitude
       (write-long (length _Lattitude) s) (princ _Lattitude s)
     ;; string _Longitude
       (write-long (length _Longitude) s) (princ _Longitude s)
     ;; string _Altitude
       (write-long (length _Altitude) s) (princ _Altitude s)
     ;; string _Ve
       (write-long (length _Ve) s) (princ _Ve s)
     ;; string _Vn
       (write-long (length _Vn) s) (princ _Vn s)
     ;; string _Vu
       (write-long (length _Vu) s) (princ _Vu s)
     ;; string _Baseline
       (write-long (length _Baseline) s) (princ _Baseline s)
     ;; string _NSV1
       (write-long (length _NSV1) s) (princ _NSV1 s)
     ;; string _NSV2
       (write-long (length _NSV2) s) (princ _NSV2 s)
     ;; string _Status
       (write-long (length _Status) s) (princ _Status s)
     ;; string _FPD_Cs
       (write-long (length _FPD_Cs) s) (princ _FPD_Cs s)
     ;; string _IMU_Header
       (write-long (length _IMU_Header) s) (princ _IMU_Header s)
     ;; string _IMU_GPSWeek
       (write-long (length _IMU_GPSWeek) s) (princ _IMU_GPSWeek s)
     ;; string _IMU_GPSTime
       (write-long (length _IMU_GPSTime) s) (princ _IMU_GPSTime s)
     ;; string _GyroX
       (write-long (length _GyroX) s) (princ _GyroX s)
     ;; string _GyroY
       (write-long (length _GyroY) s) (princ _GyroY s)
     ;; string _GyroZ
       (write-long (length _GyroZ) s) (princ _GyroZ s)
     ;; string _AccX
       (write-long (length _AccX) s) (princ _AccX s)
     ;; string _AccY
       (write-long (length _AccY) s) (princ _AccY s)
     ;; string _AccZ
       (write-long (length _AccZ) s) (princ _AccZ s)
     ;; string _Tpr
       (write-long (length _Tpr) s) (princ _Tpr s)
     ;; string _IMU_Cs
       (write-long (length _IMU_Cs) s) (princ _IMU_Cs s)
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _FPD_Header
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _FPD_Header (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _FPD_GPSWeek
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _FPD_GPSWeek (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _FPD_GPSTime
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _FPD_GPSTime (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _Heading
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _Heading (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _Pitch
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _Pitch (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _Roll
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _Roll (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _Lattitude
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _Lattitude (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _Longitude
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _Longitude (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _Altitude
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _Altitude (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _Ve
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _Ve (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _Vn
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _Vn (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _Vu
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _Vu (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _Baseline
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _Baseline (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _NSV1
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _NSV1 (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _NSV2
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _NSV2 (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _Status
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _Status (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _FPD_Cs
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _FPD_Cs (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _IMU_Header
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _IMU_Header (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _IMU_GPSWeek
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _IMU_GPSWeek (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _IMU_GPSTime
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _IMU_GPSTime (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _GyroX
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _GyroX (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _GyroY
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _GyroY (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _GyroZ
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _GyroZ (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _AccX
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _AccX (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _AccY
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _AccY (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _AccZ
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _AccZ (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _Tpr
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _Tpr (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _IMU_Cs
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _IMU_Cs (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get localization::gps :md5sum-) "6cefa42fc634a5edcdb1a380b1794e86")
(setf (get localization::gps :datatype-) "localization/gps")
(setf (get localization::gps :definition-)
      "string FPD_Header
string FPD_GPSWeek
string FPD_GPSTime
string Heading
string Pitch
string Roll
string Lattitude
string Longitude
string Altitude
string Ve
string Vn
string Vu
string Baseline
string NSV1
string NSV2
string Status
string FPD_Cs

string IMU_Header
string IMU_GPSWeek
string IMU_GPSTime
string GyroX
string GyroY
string GyroZ
string AccX
string AccY
string AccZ
string Tpr
string IMU_Cs
float64 x 
float64 y

")



(provide :localization/gps "6cefa42fc634a5edcdb1a380b1794e86")


