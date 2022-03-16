library(magrittr)
library(ggplot2)
# clear objects
rm(list = ls())
pts = list()
length(pts) = 60 

rnd = function() {
  # random number in specified range
  sample(25:125, 1)
}

generate_rand_2vecs = function(pts) {
  for (i in 1:length(pts)) {
    pts[[i]] = c(rnd(), rnd()) %>% matrix
  }
  pts
}
pts = generate_rand_2vecs(pts)
df = data.frame(data = pts)
df = df %>% t
rownames(df) = 1:length(pts)
colnames(df) = c("x", "y")
rm(pts)
print(df)
df = data.frame(df)


selectV2 = function(df, i) {
  df[i, ] %>% t %>% as.vector(.,mode="double")
}
norm_vec <- function(x) { sqrt(sum(x^2)) }
deg2rad = function(x) {
  x * pi / 180.0 
}
rad2deg = function(x) {
  x * 180.0 / pi 
}
rotMat = function(ang) {
  # create clockwise rotation matrix given an angle in degrees
  # 1st convert degrees to radians
  ang = deg2rad(ang)
  # since the below is a counterclockwise rotation matrix,
  # convert to angle from ccw to cw
  ang = 2 * pi - ang
  res = matrix(c(cos(ang), -sin(ang), sin(ang),
                 cos(ang)), ncol = 2, byrow = TRUE)
  return(res)
}
sort.less.than = function(df) {
  #return(df[order(df$x,df$y),])
  df = df[order(df$y,decreasing = TRUE),]
  df = df[order(df$x),]
  return(df)
  #return(df[order(df$x,df$y),])
}
sort.greater.than = function(pts) {
  df = df[order(df$y, decreasing = FALSE),]
  df = df[order(df$x, decreasing = TRUE),]
  return(df)
  #return(df[order(df$x,df$y,decreasing = TRUE),])
}
angle.formed = function(a,b,c) {
  # angle in degrees formed by three 2-vectors
  stopifnot(length(a) == 2 && typeof(a) == "double")   
  stopifnot(length(b) == 2 && typeof(b) == "double")   
  stopifnot(length(c) == 2 && typeof(c) == "double")   
  ba = (a - b) %>% as.matrix
  bc = (c - b) %>% as.matrix
  dp = crossprod(ba,bc) 
  angRad = acos(dp / norm_vec(ba) / norm_vec(bc))
  return(angRad %>% rad2deg)
}
is.left.turn = function(a,b,c) {
  ab = b - a
  rotated = rotMat(90) %*% ab
  d = rotated + b
  return(angle.formed(d,b,c) > 90.0)
}
add.pt = function(df, soln, currIndex) {
  rbind(soln, selectV2(df,currIndex)) 
}

solve.convex.hull = function(upper=TRUE) {
  soln = matrix(ncol=2,nrow=0)
  # sort by decreasing to create the top of the hull
  if (upper==TRUE){
  df = sort.less.than(df)
  } else {
  df = sort.greater.than(df)
  }
  # add first two points
  for(i in 1:2) { soln = add.pt(df, soln,i) }
  # keep track of the next point from the sorted set to add to
  # the solution.
  curridx = 3
  
  
  # solve top of hull
  # add a point
  # check if left turn
  # if left turn, remove 2nd to last point in soln
  last.pt.added.to.soln = c(-1,-1)
  while (curridx <= length(df[, 1])) {
    soln = add.pt(df, soln, curridx)
    last.pt.added.to.soln = soln[length(soln[,1]),]
    # Remove 2nd to last point if a left hand turn is 
    # formed by the last 3 points in the solution.
    # Continue removing until either they form a right hand turn
    # or there are only 2 points in the solution.
    while (1) {
      lenSoln = length(soln[, 1])
      if (lenSoln < 3) break;
      removeFlag = is.left.turn(soln[lenSoln - 2, ],
                                soln[lenSoln - 1, ],
                                soln[lenSoln - 0, ])
      if (!removeFlag) break;
        # remove 2nd to last point
        soln = soln[-(lenSoln - 1), ]
    }
    curridx = curridx + 1
  }
  colnames(soln) = c("x", "y")
  if (upper==FALSE) {
  print(last.pt.added.to.soln)
  }
  data.frame(soln)
}



test.convex.hull = function() {
  soln = matrix(ncol=2,nrow=0)
  a = c(1,2); b = c(2,3.5); c = c(1.5,4.5);
  soln = rbind(soln,a)
  soln = rbind(soln,b)
  soln = rbind(soln,c)
  angle.formed(soln[1,],soln[2,],soln[3,])
  is.left.turn(soln[1,],soln[2,],soln[3,])
  
  soln
  lenSoln = length(soln[,1])
  data.frame(soln)
}

#test.convex.hull()
soln.upper = solve.convex.hull(upper=TRUE)
soln.lower = solve.convex.hull(upper=FALSE)

cols = c("blue" = "blue")
# plotting the result
ggplot() +
  layer(
    data = df,
    mapping = aes(x = x, y = y),
    stat = "identity",
    position = "identity",
    geom = "point"
  ) +
  xlim(c(0, 150)) +
  ylim(c(0, 150)) + 
  layer(
    data = soln.upper, 
    stat = "identity",
    position = "identity",
    geom = "path",
    mapping = aes(x = x, y = y),
  ) + 
  layer(
    data = soln.lower, 
    mapping = aes(x = x, y = y),
    stat = "identity",
    position = "identity",
    geom = c("path")
  ) 
