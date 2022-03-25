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
is_on_left = function(p, s1, s2) {
  if (cross(p - s1, p - s2) > 0)
    return(TRUE)
  return(FALSE)
}

# determine if a point is on right of a line
is_on_right = function(p, s1, s2) {
  if (cross(p - s1, p - s2) < 0)
    return(TRUE)
  return(FALSE)
}

two.segment.intersect = function(a, b, c, d) {
  ## line segment intersection test
  # The two segments are a-b and c-d
  # Case 1: two segments lie on same line and intersect infinitely many points
  # Case 2: segments have a common vertex that is the only intersection points
  # Case 3: there is one intersection point that is not a vertex of
  #         any line segment
  stopifnot(
    length(a) == length(b) && length(b) == length(c)
    && length(c) == length(d) && length(a) == 2
  )
  case1 = FALSE
  case2 = FALSE
  case3 = FALSE
  EPSILON = 1e-9
  # Case 1 - both line segments fall on same line and overlap
  # do vec cross product
  # sort points by x and y
  # check if other segment's point occurs before second point
  # of first segment
  if (abs(cross(b - a, d - c)) < EPSILON) {
    # sort pts
    pts = rbind(a, b, c, d)
    pts = data.frame(pts)
    colnames(pts) = c("x", "y")
    pts = pts[order(pts$y, decreasing = TRUE),]
    pts = pts[order(pts$x, decreasing = TRUE),]
    # check if either first two points or last two points
    # equal the points of one of the line segments
    # @NOTE: this == should be fine since we are doing equality of
    # a float with itself, not a float with a different float
    seg1 = rbind(a, b)
    check1 = sum(seg1 == pts[3:4, ]) == 4 ||
      sum(seg1 == pts[1:2, ]) == 4
    # check if either first two points or last two points
    # equal the points of one of the line segments *in reversed order*
    seg1 = rbind(b, a)
    check2 = sum(seg1 == pts[3:4, ]) == 4 ||
      sum(seg1 == pts[1:2, ]) == 4
    if (check1 || check2 == TRUE) {
      print("case1 intersect not detected")
    } else {
      print("case1 (overlapping segments w/ same angle) intersect detected")
      case1 = TRUE
    }
  } else {
    print("case1 intersect not detected")
  }
  # Case 2: line segments have a common vertex that is
  # the only intersection point
  # check if a == c, a == d, b == c, or b == d
  if (sum(a == c) == 2 ||
      sum(a == d) == 2 || sum(b == c) == 2 || sum(b == d) == 2) {
    print("case2 (shared vertex) intersect detected")
    case2 = TRUE
  } else {
    print("case2 intersect not detected")
  }
  # Case 3: a--b and c--d intersect at exactly one
  # non-vertex point
  # a and b are on diff sides of line c--d. also points c and d are on
  # diff sides of a line through a--b.
  check1 = (is_on_left(a, c, d) && is_on_right(b, c, d)) ||
    (is_on_left(b, c, d) && is_on_right(a, c, d))
  check2 = (is_on_left(c, a, b) && is_on_right(d, a, b)) ||
    (is_on_left(d, a, b) && is_on_right(c, a, b))
  if (check1 && check2) {
    print("case3 non-vertex intersect at single point")
    case3 = TRUE
  } else {
    print("case3 intersect not detected")
  }
  if (case1 || case2 || case3) {
    return(TRUE)
  }
  else {
    return(FALSE)
  }
}

#######################################
# Visualize functions
#######################################

# Draw 2 segments and a lone point for testing segment intersection
# and cross functions. Note that the segments are given in ggplot
# format as lists of xs and ys rather than paired as points.
# This could easily be refactored to pass in a data.frame or a list
# of points instead.
visualize.segments = function(xsegs1,
                              ysegs1,
                              xsegs2,
                              ysegs2,
                              xlonepoint,
                              ylonepoint) {
  df1 = cbind(xsegs1, ysegs1) %>% data.frame
  df2 = cbind(xsegs2, ysegs2) %>% data.frame
  df3 = c(xlonepoint, ylonepoint) %>% t %>% data.frame
  colnames(df3) = c("xlonepoint", "ylonepoint")
  ptcol = c("1" = "springgreen3", "2" = "blue4", "3" = "orangered3")
  ggplot() +
    xlim(c(-3, 10)) +
    ylim(c(-3, 10)) +
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
}

# visualize polygon and several points
# polydf is a data.frame of points with x in the first col and y in the second
# pts is a list of 2-vectors with each point given as (x,y)
visualize.poly = function(polydf, pts) {
  stopifnot(pts %>% class == "list")
  stopifnot(length(pts[[1]]) == 2)
  # change pts data into a data.frame in the right format for ggplot
  pts = data.frame(pts %>% data.frame %>% t)
  colnames(pts) = c("x", "y")
  ptcol = c(
    "1" = "springgreen3",
    "2" = "blue4",
    "3" = "orangered3",
    "4" = "mediumorchid",
    "5" = "khaki4"
  )
  ggplot() +
    xlim(c(-3, 10)) +
    ylim(c(-3, 10)) +
    layer(
      data = polydf,
      mapping = aes(x = xs, y = ys, color = "5"),
      stat = "identity",
      position = "identity",
      geom = "path"
    ) +
    scale_color_manual(values = ptcol) +
    layer(
      data = pts,
      mapping = aes(x = x, y = y, color = "4"),
      stat = "identity",
      position = "identity",
      geom = "point"
    ) +
    theme(legend.position = "none") +
    xlab("x coord") + ylab("y coord")
}
#########################################
# which side of blue line is red
# point on
#########################################
xsegs1 = c(3, 5)
ysegs1 = c(4, 1)
xsegs2 = c(2, 5)
ysegs2 = c(2, 5)
xlonepoint = c(2.5)
ylonepoint = c(4)
p = c(xlonepoint, ylonepoint)
s1 = c(xsegs2[[1]], ysegs2[[1]])
s2 = c(xsegs2[[2]], ysegs2[[2]])
visualize.segments(xsegs1, ysegs1, xsegs2, ysegs2, xlonepoint, ylonepoint)
cat("Demo1: is_on_left(p,s1,s2)\nexpected = TRUE")
cat("result =", is_on_left(p, s1, s2), "\n")
cat("Demo2: is_on_right(p,s1,s2)\nexpected = FALSE")
cat("result =", is_on_right(p, s1, s2), "\n")

########################################
# intersection test - non-vertex intersect
########################################
a = c(xsegs2[[1]], ysegs2[[1]])
b = c(xsegs2[[2]], ysegs2[[2]])
c = c(xsegs1[[1]], ysegs1[[1]])
d = c(xsegs1[[2]], ysegs1[[2]])
two.segment.intersect(a, b, c, d)

########################################
# intersection test - shared vertex
########################################
xsegs1 = c(-1, 6)
ysegs1 = c(0, 4)
xsegs2 = c(-1, 5)
ysegs2 = c(0, 4)
a = c(xsegs2[[1]], ysegs2[[1]])
b = c(xsegs2[[2]], ysegs2[[2]])
c = c(xsegs1[[1]], ysegs1[[1]])
d = c(xsegs1[[2]], ysegs1[[2]])
visualize.segments(xsegs1, ysegs1, xsegs2, ysegs2, xlonepoint, ylonepoint)
two.segment.intersect(a, b, c, d)

########################################
# intersection test  - overlapping, same angle
########################################
xsegs1 = c(0, 2)
ysegs1 = c(0, 2)
xsegs2 = c(1, 3)
ysegs2 = c(1, 3)
a = c(xsegs2[[1]], ysegs2[[1]])
b = c(xsegs2[[2]], ysegs2[[2]])
c = c(xsegs1[[1]], ysegs1[[1]])
d = c(xsegs1[[2]], ysegs1[[2]])
visualize.segments(xsegs1, ysegs1, xsegs2, ysegs2, xlonepoint, ylonepoint)
two.segment.intersect(a, b, c, d)

########################################
# intersection test - non overlapping, same angle
########################################
xsegs1 = c(0, 2)
ysegs1 = c(0, 2)
xsegs2 = c(3, 5)
ysegs2 = c(3, 5)
a = c(xsegs2[[1]], ysegs2[[1]])
b = c(xsegs2[[2]], ysegs2[[2]])
c = c(xsegs1[[1]], ysegs1[[1]])
d = c(xsegs1[[2]], ysegs1[[2]])
visualize.segments(xsegs1, ysegs1, xsegs2, ysegs2, xlonepoint, ylonepoint)
two.segment.intersect(a, b, c, d)


########################################
# Point inside polygon
########################################
xs = strsplit("2 1 4 5 5 3.5 +1 3 0 2", ' ') %>% unlist %>% as.double
ys = strsplit("2 5 4 2 0 1.5 -1 2 0 2", ' ') %>% unlist %>% as.double
polydf = data.frame(cbind(xs, ys))
# test points constructed as xy
p1 = c(4, 2)
p2 = c(1, 0)
visualize.poly(polydf, list(p1, p2))

is.point.inside.poly(poly,pt) {
# Pick arbitrary direction.
# Cast a ray by building a segment from the point in arbitrary direction
# with a very long length.
# Loop through polygon segments and add 1 to a counter for each segment
# that the ray intersects.
# If the counter is 0,2,4, etc then the point is outside the polygon.
# if the counter is 1,3,5, etc then the point is inside the polygon.

}
