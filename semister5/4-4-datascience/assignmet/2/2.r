# Remove the 6th column (x6) from the data
dat_rm <- dat[, -6]

# Prepare the explanatory variables as a matrix (x1 to x5)
x <- as.matrix(dat_rm[, 1:5])

# Run the linear model (lm) and output the summary of the results
model_summary <- summary(lm(y ~ x))

# Print the summary of the linear model
print(model_summary)