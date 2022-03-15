deg2rad = function(x) x * pi / 180.0

rotMat = function(ang) {
  # create clockwise rotation matrix given an angle in degrees 
  # 1st convert degrees to radians
  ang = deg2rad(ang)
  # since the below is a counterclockwise rotation matrix, 
  # convert to angle from ccw to cw
  ang = 2*pi - ang
  res = matrix(c(cos(ang),-sin(ang), sin(ang),
                 cos(ang)),ncol=2,byrow=TRUE)
  return(res)
}

a = c(1,2)
b = c(2,3.5)
ab = b-a
rotated = rotMat(90) %*% ab
rotated + b

