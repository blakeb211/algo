setwd("~/wrk/algo/point-in-polygon/")
rm(list = ls())
library(ggplot2)
library(purrr)

# 2d vector cross product function
cross = function(a, b) {
  ## positive = b turns left if placed from head of a
  ## zero     = b does not turn, its same angle as a
  ## negative = b turns right if placed from head of a
  a[[1]] * b[[2]] - a[[2]] * b[[1]]
}

# determine if a point is on left of a line
is_on_left = function(p,s1,s2) {
  if (cross(p-s1,p-s2) > 0) return(true) 
}
# determine if a point is on right of a line
is_on_right = function(p,s1,s2) {
  if (cross(p-s1,p-s2) < 0) return(true) 
}

two.segment.intersect = function(a, b,c,d) {
  ## line segment intersection test
  # The two segments are a-b and c-d
  # Case 1: two segments lie on same line and intersect infinitely many points
  # Case 2: segments have a common vertex that is the only intersection points
  # Case 3: there is one intersection point that is not a vertex of
  #         any line segment
  stopifnot(length(a) == length(b) && length(b)== length(c) 
            && length(c) == length(d) && length(a) == 2)
  case1 = FALSE
  case2 = FALSE
  case3 = FALSE
  EPSILON = 1e-9
  # Case 1
  # do vec cross product
  # sort points by x and y
  # check if other segment's point occurs before second point
  # of first segment
  if (abs(cross(b-a, d-c)) < EPSILON) {
    pts = rbind(a,b,c,d) 
    sort(pts)
    print(pts)
  }
  
}

#######################################
# Setup the data
#######################################
xsegs1 = c(1, 3)
ysegs1 = c(1, 3)
df1 = cbind(xsegs1, ysegs1) %>% data.frame
xsegs2 = c(2, 4)
ysegs2 = c(2, 4)
df2 = cbind(xsegs2, ysegs2) %>% data.frame

xlonepoint = c(2.5)
ylonepoint = c(4)
df3 = c(xlonepoint,ylonepoint) %>% t %>% data.frame
colnames(df3) = c("xlonepoint","ylonepoint")

xpoly = c(1, 1, 1, 1)
ypoly = c(1, 1, 1, 1)

#######################################
# Visualize result
#######################################
ptcol = c("1" = "springgreen3", "2" = "blue4", "3" = "orangered3")
ggplot() +
  xlim(c(0, 10)) +
  ylim(c(0, 10)) +
  layer(
    data = df1,
    mapping = aes(x = xsegs1, y = ysegs1, color = "1"),
    stat = "identity",
    position = "identity",
    geom = "path"
  ) + geom_point(aes(x = xsegs1, y = ysegs1, color = "1")) +
  geom_point(aes(x = xlonepoint, y = ylonepoint, color = "3")) +
  layer(
    data = df2,
    stat = "identity",
    position = "identity",
    geom = "path",
    mapping = aes(x = xsegs2, y = ysegs2, color = "2"),
  ) + geom_point(aes(x = xsegs2, y = ysegs2, color = "2")) +
  theme(legend.position = "none") +
  xlab("x coord") + ylab("y coord") +
  scale_color_manual(values = ptcol) 
