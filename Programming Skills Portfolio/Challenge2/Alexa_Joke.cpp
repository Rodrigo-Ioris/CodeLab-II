#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
using namespace std;

string trim(string text)
{
    size_t first = text.find_first_not_of(" \t");
    if (first == string::npos)
        return "";

    size_t last = text.find_last_not_of(" \t");
    return text.substr(first, last - first + 1);
}

int main()
{
    ifstream inputFile("randomJokes.txt");
    vector<string> setups;
    vector<string> punchlines;
    string line;

    if (!inputFile.is_open())
    {
        cout << "Could not open randomJokes.txt. Check that it is in the program folder.\n";
        return 1;
    }

    // Each line contains a setup and punchline separated by a question mark.
    while (getline(inputFile, line))
    {
        size_t separator = line.find('?');

        if (separator != string::npos)
        {
            setups.push_back(trim(line.substr(0, separator + 1)));
            punchlines.push_back(trim(line.substr(separator + 1)));
        }
    }
    inputFile.close();

    if (setups.empty())
    {
        cout << "No valid jokes were found in the file.\n";
        return 1;
    }

    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> pick(0, static_cast<int>(setups.size()) - 1);

    string command;
    cout << "Type 'Alexa, tell me a joke' to hear a joke, or 'quit' to finish.\n";

    while (true)
    {
        cout << "\nYour command: ";
        getline(cin, command);

        if (command == "quit" || command == "Quit")
            break;

        if (command == "Alexa, tell me a joke")
        {
            int number = pick(generator);
            cout << "\n" << setups[number] << endl;
            cout << "Press Enter to hear the punchline...";
            getline(cin, command);
            cout << punchlines[number] << endl;
        }
        else
        {
            cout << "Please use the exact prompt: Alexa, tell me a joke\n";
        }
    }

    cout << "Goodbye!\n";
    return 0;
}