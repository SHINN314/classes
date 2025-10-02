# set data
set.seed(1)
dat <- scale(cbind(swiss[, -3], swiss[, 1] + runif(47) * 0.1, swiss[, 3]))
colnames(dat) <- c("x1", "x2", "x3", "x4", "x5", "x6", "y")
x <- as.matrix(dat[, 1:6])
y <- as.vector(dat[, 7])

X <- cbind(1, x)

# Print the first 6 rows of the data used for analysis
print("--- 分析に使用するデータ（dat）の先頭6行 ---")
print(head(dat))

# OLS and Ridge regression
beta_ols <- solve(t(X) %*% X) %*% t(X) %*% y

rownames(beta_ols) <- c("Intercept", "x1", "x2", "x3", "x4", "x5", "x6")
colnames(beta_ols) <- "OLS_estimate"

lambda <- 1
p <- ncol(X)
I <- diag(p)

I[1, 1] <- 0

# Ridge regression
beta_ridge <- solve(t(X) %*% X + lambda * I) %*% t(X) %*% y

rownames(beta_ridge) <- c("Intercept", "x1", "x2", "x3", "x4", "x5", "x6")
colnames(beta_ridge) <- "Ridge_estimate"

# Output results
print("--- 最小二乗推定量 (OLS) ---")
print(beta_ols)

print("--- 正則化最小二乗推定量 (Ridge, λ=1) ---")
print(beta_ridge)