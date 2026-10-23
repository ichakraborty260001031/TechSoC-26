from decision_tree import Tree
import numpy as np

x = np.array([
    # Weather, Temperature, Wind, Humidity, Has umbrella, Study hours
    ["Sunny", 30, "Weak",   40, "No",  8],
    ["Sunny", 32, "Strong", 45, "No",  7],
    ["Rainy", 18, "Weak",   90, "Yes", 2],
    ["Rainy", 20, "Strong", 85, "Yes", 3],
    ["Cloudy", 24, "Weak",  60, "No",  6],
    ["Cloudy", 22, "Strong",70, "Yes", 5],
    ["Sunny", 25, "Weak",   50, "No",  9],
    ["Rainy", 16, "Weak",   95, "Yes", 1],
    ["Cloudy", 28, "Strong",55, "No",  7],
    ["Sunny", 27, "Strong", 48, "No",  6],

    ["Rainy", 23, "Weak",   80, "Yes", 4],
    ["Cloudy", 26, "Weak",  65, "No",  8],
    ["Sunny", 19, "Strong", 55, "No",  2],
    ["Rainy", 29, "Strong", 75, "Yes", 6],
    ["Cloudy", 17, "Weak",  85, "Yes", 3],
    ["Sunny", 21, "Weak",   45, "No",  7],
    ["Rainy", 26, "Strong", 90, "Yes", 5],
    ["Cloudy", 31, "Strong",50, "No",  9],
    ["Sunny", 23, "Strong", 60, "No",  4],
    ["Rainy", 22, "Weak",   88, "Yes", 2],

    ["Cloudy", 20, "Strong",75, "Yes", 4],
    ["Sunny", 28, "Weak",   42, "No",  8],
    ["Rainy", 19, "Weak",   92, "Yes", 3],
    ["Cloudy", 25, "Strong",58, "No",  6],
    ["Sunny", 17, "Weak",   50, "No",  2],
    ["Rainy", 31, "Strong", 70, "No",  8],
    ["Cloudy", 23, "Weak",  68, "No",  5],
    ["Sunny", 26, "Strong", 47, "No",  7],
    ["Rainy", 24, "Strong", 82, "Yes", 4],
    ["Cloudy", 29, "Weak",  52, "No",  8],

    ["Sunny", 22, "Weak",   43, "No",  6],
    ["Rainy", 17, "Strong", 96, "Yes", 1],
    ["Cloudy", 19, "Weak",  80, "Yes", 2],
    ["Sunny", 31, "Strong", 40, "No",  9],
    ["Rainy", 21, "Weak",   89, "Yes", 3],
    ["Cloudy", 27, "Strong",62, "No",  7],
    ["Sunny", 18, "Weak",   49, "No",  3],
    ["Rainy", 28, "Weak",   78, "Yes", 6],
    ["Cloudy", 21, "Strong",73, "Yes", 4],
    ["Sunny", 24, "Strong", 54, "No",  5],

    ["Rainy", 25, "Weak",   86, "Yes", 5],
    ["Cloudy", 18, "Strong",88, "Yes", 2],
    ["Sunny", 20, "Weak",   46, "No",  4],
    ["Rainy", 30, "Strong", 74, "No",  8],
    ["Cloudy", 30, "Weak",  56, "No",  7],
    ["Sunny", 29, "Strong", 44, "No",  8],
    ["Rainy", 27, "Weak",   84, "Yes", 6],
    ["Cloudy", 16, "Strong",91, "Yes", 1],
    ["Sunny", 16, "Weak",   51, "No",  1],
    ["Rainy", 32, "Strong", 69, "No",  9],

    ["Cloudy", 32, "Weak",  48, "No",  8],
    ["Sunny", 30, "Strong", 41, "No",  6],
    ["Rainy", 18, "Strong", 93, "Yes", 4],
    ["Cloudy", 24, "Strong",66, "No",  7],
    ["Sunny", 25, "Strong", 52, "No",  5],
    ["Rainy", 16, "Strong", 97, "Yes", 2],
    ["Cloudy", 28, "Weak",  57, "No",  9],
    ["Sunny", 27, "Weak",   46, "No",  6],
    ["Rainy", 23, "Strong", 81, "Yes", 3],
    ["Cloudy", 26, "Strong",63, "No",  8],

    ["Sunny", 19, "Weak",   53, "No",  3],
    ["Rainy", 29, "Weak",   76, "Yes", 7],
    ["Cloudy", 17, "Strong",86, "Yes", 2],
    ["Sunny", 21, "Strong", 48, "No",  6],
    ["Rainy", 26, "Weak",   87, "Yes", 4],
    ["Cloudy", 31, "Weak",  51, "No",  8],
    ["Sunny", 23, "Weak",   58, "No",  5],
    ["Rainy", 22, "Strong", 90, "Yes", 3],
    ["Cloudy", 20, "Weak",  77, "Yes", 3],
    ["Sunny", 28, "Strong",43, "No",  9],

    ["Rainy", 19, "Strong", 94, "Yes", 1],
    ["Cloudy", 25, "Weak",  61, "No",  7],
    ["Sunny", 17, "Strong", 52, "No",  2],
    ["Rainy", 31, "Weak",   72, "No",  8],
    ["Cloudy", 23, "Strong",69, "No",  6],
    ["Sunny", 26, "Weak",   45, "No",  8],
    ["Rainy", 24, "Weak",   83, "Yes", 5],
    ["Cloudy", 29, "Strong",54, "No",  7],
    ["Sunny", 22, "Strong", 47, "No",  3],
    ["Rainy", 17, "Weak",   98, "Yes", 2],

    ["Cloudy", 19, "Strong",82, "Yes", 3],
    ["Sunny", 31, "Weak",   39, "No",  8],
    ["Rainy", 21, "Strong",91, "Yes", 4],
    ["Cloudy", 27, "Weak",  59, "No",  6],
    ["Sunny", 18, "Strong", 50, "No",  2],
    ["Rainy", 28, "Strong",79, "Yes", 7],
    ["Cloudy", 21, "Weak",  74, "Yes", 4],
    ["Sunny", 24, "Weak",   55, "No",  6],
    ["Rainy", 25, "Strong", 85, "Yes", 5],
    ["Cloudy", 18, "Weak",  89, "Yes", 1],

    ["Sunny", 20, "Strong", 49, "No",  5],
    ["Rainy", 30, "Weak",   73, "No",  8],
    ["Cloudy", 30, "Strong",57, "No",  9],
    ["Sunny", 29, "Weak",   42, "No",  7],
    ["Rainy", 27, "Strong", 80, "Yes", 6],
    ["Cloudy", 16, "Weak",  94, "Yes", 2],
    ["Sunny", 16, "Strong", 53, "No",  1],
    ["Rainy", 32, "Weak",   68, "No",  9],
    ["Cloudy", 32, "Strong",49, "No",  8],
    ["Sunny", 30, "Weak",   44, "No",  7],
], dtype=object)

y = np.array([
    1, 1, 0, 0, 1, 1, 1, 0, 1, 1,
    0, 1, 0, 1, 0, 1, 0, 1, 1, 0,
    0, 1, 0, 1, 0, 1, 1, 1, 0, 1,
    1, 0, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
    1, 1, 0, 1, 1, 0, 1, 1, 0, 1,
    0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 1, 0, 1, 1, 1, 0, 1, 0, 0,
    1, 0, 1, 0, 0, 1, 0, 1, 0, 1,
    0, 1, 1, 1, 0, 0, 0, 1, 1, 1
])
val_x = np.array([
    ["Sunny", 28, "Weak",   42, "No",  8],
    ["Rainy", 18, "Strong", 94, "Yes", 2],
    ["Cloudy", 25, "Weak",  60, "No",  6],
    ["Rainy", 30, "Weak",   73, "No",  8],
    ["Sunny", 17, "Strong", 52, "No",  2],
    ["Cloudy", 20, "Weak",  77, "Yes", 3],
    ["Rainy", 24, "Strong", 82, "Yes", 4],
    ["Sunny", 31, "Weak",   39, "No",  9],
    ["Cloudy", 29, "Strong",54, "No",  7],
    ["Rainy", 16, "Weak",   95, "Yes", 1],
    ["Sunny", 23, "Strong", 60, "No",  5],
    ["Cloudy", 32, "Weak",  48, "No",  8],
    ["Rainy", 27, "Strong", 80, "Yes", 6],
    ["Sunny", 20, "Weak",   46, "No",  4],
    ["Cloudy", 18, "Strong",88, "Yes", 2],
    ["Rainy", 32, "Strong",69, "No",  9],
    ["Sunny", 29, "Strong",44, "No",  7],
    ["Cloudy", 23, "Weak",  68, "No",  5],
    ["Rainy", 25, "Weak",   86, "Yes", 5],
    ["Sunny", 18, "Weak",   49, "No",  3]
], dtype=object)

val_y = np.array([
    1, 0, 1, 1, 0,
    0, 0, 1, 1, 0,
    1, 1, 0, 0, 0,
    1, 1, 1, 0, 0
])

feature_names = [
    "Weather", "Temperature", "Wind",
    "Humidity", "Has umbrella", "Study hours"
]

feature_types = [
    "Categorical", "Numerical", "Categorical",
    "Numerical", "Categorical", "Numerical"
]


tree = Tree(x, y,feature_types)
tree.build_tree()
correctC=0
totalC=0
for i in range(len(x)):
    if tree.predict(np.array(x[i,:], dtype=object))==y[i]:
        correctC=correctC+1
    totalC=totalC+1
print(f"Training Accuracy: {correctC/totalC}")
correctC=0
totalC=0
for i in range(len(val_x)):
    if tree.predict(np.array(val_x[i,:], dtype=object))==val_y[i]:
        correctC=correctC+1
    totalC=totalC+1
print(f"Validation Accuracy: {correctC/totalC}")

