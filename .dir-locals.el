;;; Directory Local Variables
;;; For more information see (info "(emacs) Directory Variables")

((c++-mode
  (flycheck-clang-language-standard . "c++11")
  (company-clang-arguments . ("-std=c++11" "-I./lib" "-L./lib"))
  (flycheck-clang-include-path "./lib" "/usr/include/c++/6.2.1/")))
