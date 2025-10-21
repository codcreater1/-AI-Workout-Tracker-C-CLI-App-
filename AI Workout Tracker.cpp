#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>





 
struct Exercise {
    std::string name;
    std::string muscleGroup;
    int sets;
    int reps;
    double calories;

    std::string serialize() const {
        std::ostringstream oss;
        oss << name << "|" << muscleGroup << "|" << sets << "|" << reps << "|" << calories;
        return oss.str();
    }

    static Exercise deserialize(const std::string& line) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> parts;
        while (std::getline(iss, token, '|')) parts.push_back(token);
        Exercise e;
        if (parts.size() >= 5) {
            e.name = parts[0];
            e.muscleGroup = parts[1];
            e.sets = std::stoi(parts[2]);
            e.reps = std::stoi(parts[3]);
            e.calories = std::stod(parts[4]);
        }
        return e;
    }
};

struct Workout {
    std::vector<Exercise> exercises;

    double totalCalories() const {
        double total = 0;
        for (auto& e : exercises) total += e.calories;
        return total;
    }

    std::string serialize() const {
        std::ostringstream oss;
        for (auto& e : exercises)
            oss << e.serialize() << "\n";
        oss << "\n";
        return oss.str();
    }
};

class Tracker {
    std::vector<Workout> history;
    std::string dataFile = "workouts.txt";

public:
    Tracker() { load(); }

    void addWorkout(const Workout& w) {
        history.push_back(w);
        save();
    }

    void listWorkouts() const {
        if (history.empty()) {
            std::cout << "No workouts logged yet.\n";
            return;
        }
        int i = 1;
        for (auto& w : history) {
            std::cout << "=== Workout " << i++ << " | Total Calories: "
                << w.totalCalories() << " ===\n";
            for (auto& e : w.exercises)
                std::cout << "- " << e.name << " (" << e.muscleGroup << ") "
                << e.sets << "x" << e.reps << " | " << e.calories << " kcal\n";
            std::cout << "\n";
        }
    }

    std::string suggestNext() const {
        if (history.empty()) return "No history found. Try a Full Body session.";
        std::map<std::string, int> count;
        int lookBack = std::min(3, (int)history.size());
        for (int i = history.size() - lookBack; i < history.size(); ++i) {
            for (auto& e : history[i].exercises)
                count[e.muscleGroup]++;
        }

        std::string lastGroup;
        if (!history.back().exercises.empty())
            lastGroup = history.back().exercises.front().muscleGroup;

        std::string suggestion = "Full Body";
        if (lastGroup == "Chest") suggestion = "Legs";
        else if (lastGroup == "Back") suggestion = "Arms";
        else if (lastGroup == "Legs") suggestion = "Shoulders";
        else if (lastGroup == "Arms") suggestion = "Back";
        else suggestion = "Cardio";

        return "Last muscle group: " + lastGroup + " → Suggested: " + suggestion + ".";
    }

private:
    void save() const {
        std::ofstream ofs(dataFile, std::ios::trunc);
        for (auto& w : history)
            ofs << w.serialize();
    }

    void load() {
        history.clear();
        std::ifstream ifs(dataFile);
        if (!ifs) return;
        std::string line;
        std::vector<std::string> block;
        while (std::getline(ifs, line)) {
            if (line.empty()) {
                if (!block.empty()) {
                    Workout w;
                    for (auto& l : block)
                        w.exercises.push_back(Exercise::deserialize(l));
                    history.push_back(w);
                    block.clear();
                }
            }
            else block.push_back(line);
        }
        if (!block.empty()) {
            Workout w;
            for (auto& l : block)
                w.exercises.push_back(Exercise::deserialize(l));
            history.push_back(w);
        }
    }
};

int main() {
    Tracker tracker;
    std::cout << "=== AI WORKOUT TRACKER ===\n";

    while (true) {
        std::cout << "\n1. Add new workout\n"
            << "2. View workout history\n"
            << "3. Get AI suggestion\n"
            << "4. Exit\n"
            << "Choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            Workout w;
            std::cout << "How many exercises do you want to log? ";
            int n;
            std::cin >> n;
            for (int i = 0; i < n; ++i) {
                Exercise e;
                std::cout << "Exercise " << i + 1 << " name: ";
                std::cin >> e.name;
                std::cout << "Muscle group (Chest/Back/Legs/Arms/...): ";
                std::cin >> e.muscleGroup;
                std::cout << "Sets: ";
                std::cin >> e.sets;
                std::cout << "Reps: ";
                std::cin >> e.reps;
                std::cout << "Estimated calories: ";
                std::cin >> e.calories;
                w.exercises.push_back(e);
            }
            tracker.addWorkout(w);
            std::cout << "Workout saved!\n";
        }

        else if (choice == 2) {
            tracker.listWorkouts();
        }

        else if (choice == 3) {
            std::cout << tracker.suggestNext() << "\n";
        }

        else if (choice == 4) {
            std::cout << "Exiting...\n";
            break;
        }

        else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}

