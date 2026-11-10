/*
 * Course: COEN 2210 - Introduction to Programming
 * Name: [Your Full Name]
 * Lab: 12 - Search, Sorting and Statistics
 * Description: [What this specific file does]
 * Due Date: [Date]
 */

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Inspection {
    int id = 0;
    string area;
    double vibration = 0.0;
    bool isEmpty = true;
};

int findInspectionById(const Inspection inspections[], int capacity, int targetId);
int displayInspectionsByArea(const Inspection inspections[], int capacity, string targetArea);
int copyVibrations(const Inspection inspections[], int capacity, double values[]);
void selectionSort(double values[], int count);
double calculateMean(const double values[], int count);
double calculateMedian(const double sortedValues[], int count);
void displayModes(const double sortedValues[], int count);
void displayInspection(Inspection inspection);

int main() {
    const int CAPACITY = 6;

    Inspection inspections[CAPACITY] = {
        {101, "Assembly", 0.30, false},
        {104, "Power", 0.15, false},
        {109, "Assembly", 0.30, false},
        {115, "Thermal", 0.45, false},
        {118, "Power", 0.10, false},
        {123, "Assembly", 0.15, false}
    };

    double sortedVibrations[CAPACITY] = {};
    int menuChoice = 0;

    cout << fixed << setprecision(2);

    do {
        cout << "\nInspection Analysis\n";
        cout << "1. Find inspection by ID\n";
        cout << "2. List inspections by area\n";
        cout << "3. Analyze vibration readings\n";
        cout << "4. Exit\n";
        cout << "Enter option number: ";
        cin >> menuChoice;

        if (menuChoice == 1) {
            int targetId = 0;

            cout << "Enter inspection ID: ";
            cin >> targetId;

            int foundIndex =
                findInspectionById(inspections, CAPACITY, targetId);

            if (foundIndex == -1) {
                cout << "Inspection not found." << endl;
            } else {
                displayInspection(inspections[foundIndex]);
            }
        }
        else if (menuChoice == 2) {
            string targetArea;

            cout << "Enter area: ";
            getline(cin >> ws, targetArea);

            int matchCount =
                displayInspectionsByArea(
                    inspections,
                    CAPACITY,
                    targetArea
                );

            cout << "Matches: "
                 << matchCount
                 << endl;
        }
        else if (menuChoice == 3) {
            int valueCount =
                copyVibrations(
                    inspections,
                    CAPACITY,
                    sortedVibrations
                );

            if (valueCount == 0) {
                cout << "No readings available for statistics."
                     << endl;
            } else {
                selectionSort(
                    sortedVibrations,
                    valueCount
                );

                cout << "Values used: "
                     << valueCount
                     << endl;

                cout << "Mean: "
                     << calculateMean(
                            sortedVibrations,
                            valueCount
                        )
                     << endl;

                cout << "Median: "
                     << calculateMedian(
                            sortedVibrations,
                            valueCount
                        )
                     << endl;

                cout << "Mode: ";
                displayModes(
                    sortedVibrations,
                    valueCount
                );
            }
        }
        else if (menuChoice != 4) {
            cout << "Invalid option." << endl;
        }

    } while (menuChoice != 4);

    return 0;
}

void displayInspection(Inspection inspection) {
    cout << "ID: " << inspection.id
         << " | Area: " << inspection.area
         << " | Vibration: " << inspection.vibration
         << endl;
}

int findInspectionById(
    const Inspection inspections[],
    int capacity,
    int targetId
) {
    for (int index = 0; index < capacity; index++) {
        if (!inspections[index].isEmpty &&
            inspections[index].id == targetId) {
            return index;
        }
    }

    return -1;
}

int displayInspectionsByArea(
    const Inspection inspections[],
    int capacity,
    string targetArea
) {
    int matchCount = 0;

    for (int index = 0; index < capacity; index++) {
        if (!inspections[index].isEmpty &&
            inspections[index].area == targetArea) {

            displayInspection(inspections[index]);
            matchCount++;
        }
    }

    return matchCount;
}

int copyVibrations(
    const Inspection inspections[],
    int capacity,
    double values[]
) {
    int valueCount = 0;

    for (int index = 0; index < capacity; index++) {
        if (!inspections[index].isEmpty) {
            values[valueCount] =
                inspections[index].vibration;

            valueCount++;
        }
    }

    return valueCount;
}

void selectionSort(double values[], int count) {
    for (int start = 0; start < count - 1; start++) {
        int minIndex = start;

        for (int index = start + 1;
             index < count;
             index++) {

            if (values[index] < values[minIndex]) {
                minIndex = index;
            }
        }

        double temp = values[start];
        values[start] = values[minIndex];
        values[minIndex] = temp;
    }
}

double calculateMean(
    const double values[],
    int count
) {
    double total = 0.0;

    for (int index = 0; index < count; index++) {
        total += values[index];
    }

    return total / count;
}

double calculateMedian(
    const double sortedValues[],
    int count
) {
    if (count % 2 == 1) {
        return sortedValues[count / 2];
    }
    else {
        return (
            sortedValues[count / 2 - 1]
            + sortedValues[count / 2]
        ) / 2.0;
    }
}

void displayModes(
    const double sortedValues[],
    int count
) {
    int maxFrequency = 1;
    int currentFrequency = 1;

    for (int index = 1; index < count; index++) {

        if (sortedValues[index] ==
            sortedValues[index - 1]) {

            currentFrequency++;
        }
        else {
            if (currentFrequency > maxFrequency) {
                maxFrequency = currentFrequency;
            }

            currentFrequency = 1;
        }
    }

    if (currentFrequency > maxFrequency) {
        maxFrequency = currentFrequency;
    }

    if (maxFrequency == 1) {
        cout << "N/A" << endl;
        return;
    }

    currentFrequency = 1;

    for (int index = 1; index <= count; index++) {

        if (index < count &&
            sortedValues[index] ==
            sortedValues[index - 1]) {

            currentFrequency++;
        }
        else {

            if (currentFrequency == maxFrequency) {
                cout << sortedValues[index - 1]
                     << " ";
            }

            currentFrequency = 1;
        }
    }

    cout << endl;
}