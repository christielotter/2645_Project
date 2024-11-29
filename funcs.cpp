#include <iostream>
#include <string>
#include <limits>
#include <map>
#include <vector>
#include <cmath>
#include "funcs.h"
#include <algorithm> // For std::transform
#include "funcs.h"

float inverting_input_voltage;
float non_inverting_input_voltage;
float feedback_resistor;
float input_resistor;
float ground_resistor;
float gain;

void clearscreen() {
#ifdef _WIN32
    system("cls");
#endif // !Win32

}
bool validate_positive_input(float &value, const std::string &prompt) {
    std::cout << prompt;
    std::cin >> value;
    if (std::cin.fail() || value <= 0) {
        std::cin.clear(); // Clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cerr << "Error: Value must be a positive number.\n";
        return false;
    }
    return true;
}

void go_back_to_main() {
  std::string input;
  do {
    std::cout << "\nEnter 'b' or 'B' to go back to main menu: ";
    std::cin >> input;
    clearscreen();

  } while (input != "b" && input != "B");
}

void menu_item_1() {
    clearscreen();
    int choice;
    do {
        std::cout << "\n--- Resistor Calculator ---\n";
        std::cout << "1. Calculate resistance from color codes\n";
        std::cout << "2. Solve Resistor Network\n";
        std::cout << "3. Find nearest NPV resistor\n";
        std::cout << "4. Get NPV value and color code for a resistor\n";  // New option
        std::cout << "5. Back to main menu\n";
        std::cout << "Select an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                calculate_resistor_from_color_code();
                break;
            case 2:
                combine_resistors();
                break;
            case 3:
                find_nearest_npv_resistor();
                break;
            case 4: {
                double resistor_value;
                std::cout << "Enter resistor value (in ohms): ";
                std::cin >> resistor_value;
                get_npv_and_color_code_for_resistor(resistor_value);  // Call the new function
                break;
            }
            case 5:
                std::cout << "Returning to main menu...\n";
                break;
            default:
                std::cout << "Invalid option. Try again.\n";
        }
    } while (choice != 5);
}
void calculate_resistor_from_color_code() {
    // Define color-to-value and multiplier maps
    std::map<std::string, int> color_code = {
        {"black", 0}, {"brown", 1}, {"red", 2}, {"orange", 3}, {"yellow", 4},
        {"green", 5}, {"blue", 6}, {"violet", 7}, {"gray", 8}, {"white", 9}
    };
    std::map<std::string, double> multipliers = {
        {"black", 1}, {"brown", 10}, {"red", 100}, {"orange", 1000}, {"yellow", 10000},
        {"green", 100000}, {"blue", 1000000}, {"gold", 0.1}, {"silver", 0.01}
    };

    // Helper lambda to convert a string to lowercase
    auto to_lower = [](std::string &str) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    };

    std::string band1, band2, multiplier;
    std::cout << "Enter first color band: ";
    std::cin >> band1;
    to_lower(band1); // Convert to lowercase
    std::cout << "Enter second color band: ";
    std::cin >> band2;
    to_lower(band2); // Convert to lowercase
    std::cout << "Enter multiplier band: ";
    std::cin >> multiplier;
    to_lower(multiplier); // Convert to lowercase

    // Validate the color bands
    if (color_code.find(band1) == color_code.end() || 
        color_code.find(band2) == color_code.end() || 
        multipliers.find(multiplier) == multipliers.end()) {
        std::cout << "Invalid color code entered. Please try again.\n";
        return;
    }

    // Calculate the resistance
    int significant_digits = color_code[band1] * 10 + color_code[band2];
    double resistance = significant_digits * multipliers[multiplier];
    std::cout << "Resistance: " << resistance << " ohms\n";
}

void combine_resistors() {
    int num_series, num_parallel;

    // Input for series resistors
    std::cout << "Enter the number of resistors in series: ";
    std::cin >> num_series;

    std::vector<double> series_resistances(num_series);
    double total_series_resistance = 0;

    for (int i = 0; i < num_series; i++) {
        std::cout << "Enter value of series resistor " << i + 1 << " (in ohms): ";
        std::cin >> series_resistances[i];
        total_series_resistance += series_resistances[i]; // Sum up for series
    }
    std::cout << "Total resistance of resistors in series: " << total_series_resistance << " ohms\n";

    // Input for parallel resistors
    std::cout << "Enter the number of resistors in parallel: ";
    std::cin >> num_parallel;

    std::vector<double> parallel_resistances(num_parallel);
    double total_inverse_parallel = 0;

    for (int i = 0; i < num_parallel; i++) {
        std::cout << "Enter value of parallel resistor " << i + 1 << " (in ohms): ";
        std::cin >> parallel_resistances[i];
        if (parallel_resistances[i] == 0) {
            std::cout << "Error: Resistor value cannot be zero in parallel combination.\n";
            return;
        }
        total_inverse_parallel += 1 / parallel_resistances[i]; // Sum of inverses for parallel
    }

    double total_parallel_resistance = 1 / total_inverse_parallel;
    std::cout << "Total resistance of resistors in parallel: " << total_parallel_resistance << " ohms\n";

    // Combine the two results
    int combination_type;
    std::cout << "Enter 1 to combine the series and parallel resistances in series, or 2 to combine them in parallel: ";
    std::cin >> combination_type;

    if (combination_type == 1) {
        // Combine in series
        double combined_resistance = total_series_resistance + total_parallel_resistance;
        std::cout << "Total combined resistance (series): " << combined_resistance << " ohms\n";
    } else if (combination_type == 2) {
        // Combine in parallel
        double combined_inverse = (1 / total_series_resistance) + (1 / total_parallel_resistance);
        double combined_resistance = 1 / combined_inverse;
        std::cout << "Total combined resistance (parallel): " << combined_resistance << " ohms\n";
    } else {
        std::cout << "Invalid combination type. Try again.\n";
    }
}

void find_nearest_npv_resistor() {
    std::vector<double> npv_resistors = {
        1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2,
        10, 12, 15, 18, 22, 27, 33, 39, 47, 56, 68, 82,
        100, 120, 150, 180, 220, 270, 330, 390, 470, 560, 680, 820,
        1000, 1200, 1500, 1800, 2200, 2700, 3300, 3900, 4700, 5600, 6800, 8200,
        10000 // Expandable for other series (E24, E48, etc.)
    };

    double target_resistance;
    std::cout << "Enter target resistance (in ohms): ";
    std::cin >> target_resistance;

    if (target_resistance <= 0) {
        std::cout << "Invalid resistance value. Must be greater than zero.\n";
        return;
    }

    double closest_resistor = npv_resistors[0];
    double min_difference = std::abs(target_resistance - closest_resistor);

    for (double resistor : npv_resistors) {
        double difference = std::abs(target_resistance - resistor);
        if (difference < min_difference) {
            closest_resistor = resistor;
            min_difference = difference;
        }
    }

    std::cout << "Nearest NPV resistor: " << closest_resistor << " ohms\n";

    // Suggest combination if exact match is not found
    if (closest_resistor != target_resistance) {
        std::cout << "Suggested combinations: \n";
        for (double r1 : npv_resistors) {
            for (double r2 : npv_resistors) {
                if (std::abs((r1 + r2) - target_resistance) < min_difference) {
                    std::cout << "Series: " << r1 << " ohms + " << r2 << " ohms\n";
                }
                if (std::abs((1 / ((1 / r1) + (1 / r2))) - target_resistance) < min_difference) {
                    std::cout << "Parallel: " << r1 << " ohms || " << r2 << " ohms\n";
                }
            }
        }
    }

}
void get_npv_and_color_code_for_resistor(double resistance) {
    // Define the E12 series (preferred values)
    std::vector<double> npv_resistors = {
        1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2,
        10, 12, 15, 18, 22, 27, 33, 39, 47, 56, 68, 82,
        100, 120, 150, 180, 220, 270, 330, 390, 470, 560, 680, 820,
        1000, 1200, 1500, 1800, 2200, 2700, 3300, 3900, 4700, 5600, 6800, 8200,
        10000 // Extendable for other series
    };

    std::map<int, std::string> digit_to_color = {
        {0, "black"}, {1, "brown"}, {2, "red"}, {3, "orange"}, {4, "yellow"},
        {5, "green"}, {6, "blue"}, {7, "violet"}, {8, "gray"}, {9, "white"}
    };

    std::map<int, std::string> multiplier_to_color = {
        {0, "black"}, {1, "brown"}, {2, "red"}, {3, "orange"}, {4, "yellow"},
        {5, "green"}, {6, "blue"}, {-1, "gold"}, {-2, "silver"}
    };

    // Find the closest NPV resistor
    double closest_resistor = npv_resistors[0];
    double min_difference = std::abs(resistance - closest_resistor);

    for (double resistor : npv_resistors) {
        double difference = std::abs(resistance - resistor);
        if (difference < min_difference) {
            closest_resistor = resistor;
            min_difference = difference;
        }
    }

    std::cout << "Nearest NPV resistor: " << closest_resistor << " ohms\n";

    // Calculate color code
    int magnitude = static_cast<int>(std::log10(closest_resistor));
    int significant_value = static_cast<int>(closest_resistor / std::pow(10, magnitude));

    int first_digit = significant_value / 10;
    int second_digit = significant_value % 10;

    if (first_digit >= 0 && first_digit <= 9 && second_digit >= 0 && second_digit <= 9) {
        std::string first_band = digit_to_color[first_digit];
        std::string second_band = digit_to_color[second_digit];
        std::string multiplier_band = multiplier_to_color[magnitude];

        std::cout << "Color Code: [" << first_band << ", " << second_band << ", " << multiplier_band << "]\n";
    } else {
        std::cout << "Error: Unable to calculate color code for this resistor.\n";
    }
}

void menu_item_2() {
    clearscreen();
  std::cout << "\n>> The Op-Amp \n";
  int choice;

  // Display a submenu for selecting the op-amp configuration
  std::cout << "\nOp-Amp Configuration:\n";
  std::cout << "1. Inverting Op-Amp\n";
  std::cout << "2. Non-Inverting Op-Amp\n";
  std::cout << "3. Back to main menu\n";
  std::cout << "Select choice: ";
  std::cin >> choice;

  // Perform calculations based on the user's choice
  if (choice == 1) {
    // Inverting Op-Amp
    std::cout << "\n>> Inverting Op-Amp Configuration\n";

    // Validate each input
    if (!validate_positive_input(inverting_input_voltage, "Enter the inverting input voltage (volts): "))
        return;
    if (!validate_positive_input(feedback_resistor, "Enter the feedback resistor value (ohms): "))
        return;
    if (!validate_positive_input(input_resistor, "Enter the input resistor value (ohms): "))
        return;

    gain = -feedback_resistor / input_resistor;
    float output_voltage = gain * inverting_input_voltage;

    std::cout << "\nThe gain of the inverting op-amp is: " << gain <<"\n";
    std::cout << "The output voltage is: " << output_voltage << " V\n";

  } else if (choice == 2) {
    // Non-Inverting Op-Amp
    std::cout << "\n>> Non-Inverting Op-Amp Configuration\n";

    // Validate each input
    if (!validate_positive_input(non_inverting_input_voltage, "Enter the non-inverting input voltage (volts): "))
        return;
    if (!validate_positive_input(feedback_resistor, "Enter the feedback resistor value (ohms): "))
        return;
    if (!validate_positive_input(ground_resistor, "Enter the ground resistor value (ohms): "))
        return;

    gain = 1 + (feedback_resistor / ground_resistor);
    float output_voltage = gain * non_inverting_input_voltage;

    std::cout << "\nThe gain of the non-inverting op-amp is: " << gain << "\n";
    std::cout << "The output voltage is: " << output_voltage << " V\n";

  } else if (choice ==3) {
    return; // Exit this function
  }
}

void menu_item_3() {
    clearscreen();
  std::cout << "\n>> Menu 3\n";
  std::cout << "\nSome code here does something useful\n";
  // you can call a function from here that handles menu 3
}
void menu_item_4() {
    clearscreen();

  // you can call a function from here that handles menu 4
}
