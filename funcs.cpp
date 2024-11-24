#include <iostream>
#include <string>
#include <limits>

#include "funcs.h"

float inverting_input_voltage;
float non_inverting_input_voltage;
float feedback_resistor;
float input_resistor;
float ground_resistor;
float gain;

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
  } while (input != "b" && input != "B");
}

void menu_item_1() {
  std::cout << "\n>> Menu 1\n";
  std::cout << "\nSome code here does something useful\n";
  // you can call a function from here that handles menu 1
}
void menu_item_2() {
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
  std::cout << "\n>> Menu 3\n";
  std::cout << "\nSome code here does something useful\n";
  // you can call a function from here that handles menu 3
}
void menu_item_4() {
  std::cout << "\n>> Menu 4\n";
  std::cout << "\nSome code here does something useful\n";
  // you can call a function from here that handles menu 4
}

