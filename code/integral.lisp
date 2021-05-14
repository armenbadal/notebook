
(defconstant +epsilon+ 0.000001)

(defun trapezoid (b0 b1 h)
    (* h (/ (+ b0 b1) 2.0)))

(defun integral (a b f)
    (let ((d (- b a)))
        (if (< d +epsilon+)
            0.0
            (+ (trapezoid (funcall f a) (funcall f (+ a d)) d)
               (integral (+ a d) b f)))))




(print (integral 0.0 2.0 #'(lambda (x) (* x x))))

(terpri)(quit)
