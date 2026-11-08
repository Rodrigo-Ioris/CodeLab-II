#include <iostream>
#include <string>
using namespace std;

// Gets the journey distance in miles.
double getDistance()
{
    double distance;
    cout << "Enter the journey distance in miles: ";
    cin >> distance;

    while (distance <= 0)
    {
        cout << "Please enter a distance greater than zero: ";
        cin >> distance;
    }

    return distance;
}

// Gets the fuel type from the user.
string getFuelType()
{
    int choice;
    cout << "\nChoose the fuel type:\n";
    cout << "1. Diesel\n";
    cout << "2. Petrol\n";
    cout << "Enter 1 or 2: ";
    cin >> choice;

    while (choice != 1 && choice != 2)
    {
        cout << "Invalid choice. Enter 1 for Diesel or 2 for Petrol: ";
        cin >> choice;
    }

    if (choice == 1)
        return "Diesel";

    return "Petrol";
}

// Calculates emissions using the values supplied in the assessment brief.
double calculateCO2(double distance, string fuelType)
{
    const double litresPer100Miles = 9.66;
    double emissionsPerLitre;

    if (fuelType == "Diesel")
        emissionsPerLitre = 2.68;
    else
        emissionsPerLitre = 2.31;

    double litresUsed = (distance / 100.0) * litresPer100Miles;
    return litresUsed * emissionsPerLitre;
}

int main()
{
    cout << "Car Journey CO2 Calculator\n\n";

    double distance = getDistance();
    string fuelType = getFuelType();
    double emissions = calculateCO2(distance, fuelType);

    cout << "\nFuel type: " << fuelType << endl;
    cout << "Estimated CO2 emissions: " << emissions << " kg\n";

    return 0;
}
