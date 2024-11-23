#include <iostream>
#include <string>

#include "funcs.h"

float inverting_input_voltage;
float non_inverting_input_voltage;
float feedback_resistor;
float input_resistor;
float ground_resistor;
float gain;

void menu_item_1() {
  std::cout << "\n>> Menu 1\n";
  std::cout << "\nSome code here does something useful\n";
  // you can call a function from here that handles menu 1
}
void menu_item_2() {
  std::cout << "\n>> The Op-Amp \n";
  int choice;

  // Display a submenu for selecting the op-amp configuration
  std::cout << "\nSelect Op-Amp Configuration:\n";
  std::cout << "1. Inverting Op-Amp\n";
  std::cout << "2. Non-Inverting Op-Amp\n";
  std::cin >> choice;

  // Perform calculations based on the user's choice
  if (choice == 1) {
    // Inverting Op-Amp

    std::cout << "\n>>Inverting Op-Amp Configuration\n";
    std::cout << "Enter the inverting input voltage: ";
    std::cin >> inverting_input_voltage;
    std::cout << "Enter the feedback resistor value (ohms): ";
    std::cin >> feedback_resistor;
    std::cout << "Enter the input resistor value (ohms): ";
    std::cin >> input_resistor;

    gain = -feedback_resistor / input_resistor;
    float output_voltage = gain * inverting_input_voltage;

    std::cout << "\nThe gain of the inverting op-amp is: " << gain << "\n";
    std::cout << "The output voltage is: " << output_voltage << " V\n";

  } else if (choice == 2) {
    // Non-Inverting Op-Amp

    std::cout << "\n>> Non-Inverting Op-Amp Configuration\n";
    std::cout << "Enter the non-inverting input voltage: ";
    std::cin >> non_inverting_input_voltage;
    std::cout << "Enter the feedback resistor value (ohms): ";
    std::cin >> feedback_resistor;
    std::cout << "Enter the ground resistor value (ohms): ";
    std::cin >> ground_resistor;

    gain = 1 + (feedback_resistor / ground_resistor);
    float output_voltage = gain * non_inverting_input_voltage;

    std::cout << "\nThe gain of the non-inverting op-amp is: " << gain << "\n";
    std::cout << "The output voltage is: " << output_voltage << " V\n";

  } else {
    // Invalid choice handling
    std::cout << "\nInvalid choice! Returning to the main menu.\n";
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
