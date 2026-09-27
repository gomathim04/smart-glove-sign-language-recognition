import pandas as pd
import joblib

from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report

# ==========================================
# 1. LOAD DATASET
# ==========================================

data = pd.read_csv("ABCD_combined.csv")

print("Dataset loaded!")
print("Total samples:", len(data))

# ==========================================
# 2. SELECT SENSOR FEATURES
# ==========================================

X = data[[
    "F1",
    "F2",
    "F3",
    "F4",
    "X",
    "Y",
    "Z"
]]

# Letter we want to predict
y = data["LABEL"]

# ==========================================
# 3. SPLIT DATA
# ==========================================

X_train, X_test, y_train, y_test = train_test_split(
    X,
    y,
    test_size=0.20,
    random_state=42,
    stratify=y
)

print("Training samples:", len(X_train))
print("Testing samples:", len(X_test))

# ==========================================
# 4. CREATE RANDOM FOREST MODEL
# ==========================================

model = RandomForestClassifier(
    n_estimators=100,
    random_state=42
)

# ==========================================
# 5. TRAIN MODEL
# ==========================================

print("\nTraining model...")

model.fit(X_train, y_train)

print("Training completed!")

# ==========================================
# 6. TEST MODEL
# ==========================================

y_pred = model.predict(X_test)

accuracy = accuracy_score(y_test, y_pred)

print("\n==============================")
print("       MODEL ACCURACY")
print("==============================")

print(f"Accuracy: {accuracy * 100:.2f}%")

# ==========================================
# 7. CLASSIFICATION REPORT
# ==========================================

print("\nClassification Report:")
print(classification_report(y_test, y_pred))

# ==========================================
# 8. SAVE TRAINED MODEL
# ==========================================

joblib.dump(model, "smart_glove_model.pkl")

print("\n==============================")
print("MODEL SAVED SUCCESSFULLY!")
print("==============================")

print("File: smart_glove_model.pkl")