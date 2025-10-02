# Load necessary libraries
global_model <- lm(y ~ ., data = dat_rm)

# Perform stepwise model selection based on AIC
step(global_model, direction = "backward")

# Print the results of model selection based on AIC
print("--- AICに基づく変数選択の結果 ---")
print(model_selection_results)