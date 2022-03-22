setwd("~/wrk/algo/point-in-polygon/")
rm(list = ls())
library(ggplot)
library(purrr)
# 2d vector cross product function
cross = function(a, b) {
  ## positive = b turns left if placed from head of a
  ## zero     = b does not turn, its same angle as a
  ## negative = b turns right if placed from head of a
  a[[1]] * b[[2]] - a[[2]] * b[[1]]
}

two.segment.intersect = function(a,b) {
## line segment intersection test
# Case 1: two segments lie on same line and intersect infinitely many points
# Case 2: segments have a common vertex that is the only intersection points
# Case 3: there is one intersection point that is not a vertex of
#         any line segment  
stopifnot(length(a) == length(b) && length(a) == 2)
  case1 = FALSE
  case2 = FALSE
  case3 = FALSE
  # Case 1
  if (abs(cross(a,b)) <= 1e-9) {
     
  }
  
}
#######################################
# Setup the data
#######################################
xsegs = c(1,1)
ysegs = c(2,3)
xpoly = c(1,1,1,1)
ypoly = c(1,1,1,1)
#######################################
# Visualize result
#######################################
ggplot() +
  layer(
    data = df,
    mapping = aes(x = x, y = y),
    stat = "identity",
    position = "identity",
    geom = "point"
  ) +
  xlim(c(0, 15)) +
  ylim(c(0, 15)) +
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
