
(defun inverse-matrix-rec (mx r)
  (if (null (car mx))
    r
    (inverse-matrix-rec
      (mapcar (lambda (e) (cdr e)) mx)
      (cons (mapcar (lambda (e) (car e)) mx) r))))

(defun scalar-product (vo vi)
  (apply #'+ (mapcar #'* vo vi)))
