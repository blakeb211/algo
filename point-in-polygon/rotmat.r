library(MASS)
library(magrittr)
rotmat = function(theta) {
  res = matrix(
    data = c(cos(theta), -sin(theta),
             sin(theta), cos(theta)),
    nrow = 2,
    byrow = TRUE
  )
  
  res 
}
rotmat(0.01)
