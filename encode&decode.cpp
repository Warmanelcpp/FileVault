#include <iostream>
#include <fstream>
#include <string>
#include <limits>  // cin.ignore düzeltmesi için

using namespace std;

// XOR şifreleme/şifre çözme fonksiyonu
void processFile(const string& inputFileName, const string& outputFileName, char key) {
    cout << "[DEBUG] Opening input file: " << inputFileName << endl;

    ifstream inputFile;
    inputFile.open(inputFileName.c_str(), ios::binary);
    if (!inputFile.is_open()) {
        cerr << "Error: Cannot open input file!" << endl;
        return;
    }

    ofstream outputFile;
    outputFile.open(outputFileName.c_str(), ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Error: Cannot create output file!" << endl;
        inputFile.close();
        return;
    }

    char byte;
    while (inputFile.get(byte)) {
        byte ^= key; // XOR işlemi
        outputFile.put(byte);
    }

    inputFile.close();
    outputFile.close();
    cout << "Process completed successfully: " << outputFileName << endl;
}

// Ana menüyü görüntüle
void showMenu() {
    cout << "\nFile Encryption and Decryption Tool" << endl;
    cout << "--------------------------------------" << endl;
    cout << "1. Encrypt a file" << endl;
    cout << "2. Decrypt a file" << endl;
    cout << "3. Exit" << endl;
    cout << "Select an option: ";
}

int main() {
    int choice;
    string inputFileName, outputFileName;
    char key;

    do {
        showMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Geçici belleği temizle

        switch (choice) {
            case 1:
                cout << "\nEnter the name of the file to encrypt: ";
                getline(cin, inputFileName);
                cout << "Enter the name for the encrypted output file: ";
                getline(cin, outputFileName);
                cout << "Enter a single character as the key: ";
                cin >> key;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                processFile(inputFileName, outputFileName, key);
                break;

            case 2:
                cout << "\nEnter the name of the file to decrypt: ";
                getline(cin, inputFileName);
                cout << "Enter the name for the decrypted output file: ";
                getline(cin, outputFileName);
                cout << "Enter the decryption key (same used for encryption): ";
                cin >> key;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                processFile(inputFileName, outputFileName, key);
                break;

            case 3:
                cout << "Exiting the program. Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice! Please select 1, 2, or 3." << endl;
        }

    } while (choice != 3);

    return 0;
}
