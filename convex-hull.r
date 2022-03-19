library(magrittr)
library(ggplot2)
library(purrr)
#######################################
# Setup Environment
#######################################
rm(list = ls()) # clear objects
NUMPTS = 30
RNDLOW = 25
RNDHIGH = 125
#######################################
# Functions
#######################################

# Generate a random 2-vector
rnd = function(X) {
  sample(RNDLOW:RNDHIGH, 2, replace = FALSE)
}

# Fill a list with random 2x1 matrices
generate_rand_2vecs = function(pts) {
  pts = map(pts, rnd)
  map(pts, matrix)
}

# Select a point from a Nx2 dataframe and return as 2-vector
selectV2 = function(df, i) {
  df[i,] %>% t %>% as.vector(., mode = "double")
}

# Calculate Euclidean norm of a vector
norm_vec <- function(x) {
  sqrt(sum(x ^ 2))
}

# Convert degrees to radians
deg2rad = function(x) {
  x * pi / 180.0
}

# Convert radians to degrees
rad2deg = function(x) {
  x * 180.0 / pi
}

# Create a clockwise rotation matrix given an angle in degrees
rotMat = function(ang) {
  # First convert degrees to radians
  ang = deg2rad(ang)
  # Since our formula yields a counter-clockwise rotation matrix,
  # convert from counter-clockwise to clockwise
  ang = 2 * pi - ang
  res = matrix(c(cos(ang),-sin(ang), sin(ang),
                 cos(ang)), ncol = 2, byrow = TRUE)
  return(res)
}

# Sort a dataframe primarily by x and secondarily by y.
sort.less.than = function(df) {
  df = df[order(df$y, decreasing = TRUE), ]
  df = df[order(df$x, decreasing = FALSE), ]
  return(df)
}

# Sort a dataframe primarily by x and secondarily by y.
sort.greater.than = function(pts) {
  df = df[order(df$y, decreasing = FALSE), ]
  df = df[order(df$x, decreasing = TRUE), ]
  return(df)
  #return(df[order(df$x,df$y,decreasing = TRUE),])
}

# Calculate angle formed by 3 points
angle.formed = function(a, b, c) {
  # angle in degrees formed by three 2-vectors
  stopifnot(length(a) == 2 && typeof(a) == "double")
  stopifnot(length(b) == 2 && typeof(b) == "double")
  stopifnot(length(c) == 2 && typeof(c) == "double")
  ba = (a - b) %>% as.matrix
  bc = (c - b) %>% as.matrix
  dp = crossprod(ba, bc)
  angRad = acos(dp / norm_vec(ba) / norm_vec(bc))
  return(angRad %>% rad2deg)
}

# Determine if 3 points create a left turn by creating
# a vector from the first two the second point, then rotating
# it 90 degrees to the right to yield a fourth point.
# Whether left hand turn is formed is determined by
# finding the angle between this new fourth point and the
# last two input points. If the angle is > 90 degrees, it is a
# left hand turn.
is.left.turn = function(a, b, c) {
  stopifnot(length(a) == 2 && typeof(a) == "double")
  stopifnot(length(b) == 2 && typeof(b) == "double")
  stopifnot(length(c) == 2 && typeof(c) == "double")
  ab = b - a
  rotated = rotMat(90) %*% ab
  d = rotated + b
  angformed = angle.formed(d, b, c)
  if (is.nan(angformed))
    return(TRUE)
  return(angformed > 90.0)
}

# Add a point from the random point dataframe to the solution
add.pt = function(df, soln, currIndex) {
  rbind(soln, selectV2(df, currIndex))
}

# Find the upper or lower path of the convex hull using Andrew's
# algorithm
solve.convex.hull = function(upper = TRUE) {
  soln = matrix(ncol = 2, nrow = 0)
  # sort by decreasing to create the top of the hull
  if (upper == TRUE) {
    df = sort.less.than(df)
  } else {
    df = sort.greater.than(df)
  }
  # add first two points
  for (i in 1:2) {
    soln = add.pt(df, soln, i)
  }
  # keep track of the next point from the sorted set to add to
  # the solution.
  curridx = 3
  
  # Loop through the sorted points
  # Add a point
  # Check if left turn
  # If left turn, remove 2nd to last point in solution
  # Note: Sometimes we have to remove two points in a row,
  # so left hand turn checking and removal must be done
  # in their own loop.
  while (curridx <= length(df[, 1])) {
    soln = add.pt(df, soln, curridx)
    # Remove 2nd to last point if a left hand turn is
    # formed by the last 3 points in the solution.
    # Continue removing until either they form a right hand turn
    # or there are only 2 points in the solution.
    while (1) {
      lenSoln = length(soln[, 1])
      if (lenSoln < 3)
        break
      removeFlag = FALSE
      removeFlag = is.left.turn(soln[lenSoln - 2,],
                                soln[lenSoln - 1,],
                                soln[lenSoln - 0,])
      if (removeFlag == FALSE)
        break
      
      # remove 2nd to last point
      soln = soln[-(lenSoln - 1),]
    }
    curridx = curridx + 1
  }
  colnames(soln) = c("x", "y")
  data.frame(soln)
}

#######################################
# Main
#######################################

# create a list of random points
pts = list()
length(pts) = NUMPTS
pts = generate_rand_2vecs(pts)

# create a NUMPTSx2 dataframe
df = data.frame(data = pts)
df = df[!duplicated(df), ] # remove duplicates
df = df %>% t
rownames(df) = 1:length(df[, 1])
colnames(df) = c("x", "y")
rm(pts)
print(df)
df = data.frame(df)

# solve convex hull
soln.upper = solve.convex.hull(upper = TRUE)
soln.lower = solve.convex.hull(upper = FALSE)

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
