
(defun ab/find-another-users-file()
(find-file
(helm-comp-read "Choose:"
 (-filter 'file-exists-p 
  (let ((users (-filter (lambda(x) (< 4 (length x))  ) (directory-files (directory-file-name (s-concat (getenv "HOME") "/../")))))) 
   (-map (lambda(user)
	   (s-replace (getenv "HOME") (s-concat (getenv "HOME") "/../" user "/" ) (buffer-file-name))
	   )
    users
    )
   )
 )
 )))
 

