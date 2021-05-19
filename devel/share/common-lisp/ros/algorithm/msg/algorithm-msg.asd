
(cl:in-package :asdf)

(defsystem "algorithm-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "algorithm" :depends-on ("_package_algorithm"))
    (:file "_package_algorithm" :depends-on ("_package"))
  ))