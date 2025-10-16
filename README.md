📖 Description

AI Workout Tracker is a simple yet smart C++ console application that lets you log your workouts, calculate total calories burned, and receive AI-based workout suggestions based on your recent training history.

The project demonstrates Object-Oriented Programming (OOP) principles, file handling, and a touch of AI logic — making it perfect for a GitHub portfolio or C++ course project.

🚀 Features

🧩 OOP Design: Uses Exercise, Workout, and Tracker classes.

💾 File Storage: All workouts are saved locally in workouts.txt.

🔥 AI Suggestion System: Suggests your next muscle group based on your last workouts.

🧮 Calorie Tracking: Automatically sums up calories for each session.

🖥️ Easy CLI Interface: Clean and simple terminal interaction.

💡 No Dependencies: Pure C++17 — no external libraries needed.

🧱 Project Structure
AIWorkoutTracker/
│
├── main.cpp
└── workouts.txt    # Automatically created after first run

⚙️ How to Build & Run
Compile:
g++ -std=c++17 main.cpp -o tracker

Run:
./tracker

💬 Example Output
=== AI WORKOUT TRACKER ===

1. Add new workout
2. View workout history
3. Get AI suggestion
4. Exit
Choice: 1

How many exercises do you want to log? 2
Exercise 1 name: BenchPress
Muscle group (Chest/Back/Legs/Arms/...): Chest
Sets: 4
Reps: 10
Estimated calories: 120
Exercise 2 name: Pushups
Muscle group (Chest)
Sets: 3
Reps: 15
Estimated calories: 80
Workout saved!

1. Add new workout
2. View workout history
3. Get AI suggestion
4. Exit
Choice: 3

Last muscle group: Chest → Suggested: Legs.

🧠 How the AI Suggestion Works

The tracker looks at your last 3 workouts and identifies which muscle group you trained most often.
Then it recommends a different group to balance your routine:

Last Muscle Group	Suggested Next
Chest	Legs
Back	Arms
Legs	Shoulders
Arms	Back
Other	Cardio
📂 Saved Data Format (workouts.txt)

Example file content:

BenchPress|Chest|4|10|120
Pushups|Chest|3|15|80

Squat|Legs|4|10|150
Lunges|Legs|3|12|100

🧑‍💻 Author

Murat Can Nergiz
C++ Developer & Computer Engineering Student
📍 Poland | 🧠 Focus: OOP, AI, and Clean Code
