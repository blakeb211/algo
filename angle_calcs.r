rm(list = ls())
NUMPT = 12
pts = list()
length(pts) = NUMPT
library(magrittr)
library(ggplot2)

rnd = function() {
 sample(25:125,1)  
}

generate_rand_2vecs = function(pts) {
  for(i in 1:NUMPT) {
    pts[[i]] = c(rnd(),rnd()) %>% matrix
  }
  pts
}
pts = generate_rand_2vecs(pts)
df = data.frame(data=pts)
df = df %>% t
rownames(df) = 1:12
colnames(df) = c("x","y")
print(df)
df = data.frame(df)
ggplot() + 
  layer(data=df, 
        mapping = aes(x = x, y = y), 
        stat="identity", 
        position = "identity", 
        geom="point") + 
        xlim(c(0,150)) +   
        ylim(c(0,150)) 


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

