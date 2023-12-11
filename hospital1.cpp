#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

class Patient {
private:
    string name;
    int age;
    string gender;
    string disease;

public:
    Patient() {}

    void admitPatient() {
        cout << "Enter patient name: ";
        getline(cin, name);

        cout << "Enter patient age: ";
        cin >> age;

        cin.ignore(); 

        cout << "Enter patient gender: ";
        getline(cin, gender);

        cout << "Enter patient disease: ";
        getline(cin, disease);

        cout << "Patient admitted successfully.\n";
    }

    void display() const {
        cout << "Patient Name: " << name << "\nAge: " << age << "\nGender: " << gender
             << "\nDisease: " << disease << endl;
    }

    string getName() const {
        return name;
    }
};

class Doctor {
private:
    string name;
    string specialization;

public:
    Doctor(const string& newName, const string& newSpecialization)
        : name(newName), specialization(newSpecialization) {}

    void display() const {
        cout << "Doctor Name: " << name << "\nSpecialization: " << specialization << endl;
    }

    string getName() const {
        return name;
    }

    string getSpecialization() const {
        return specialization;
    }
};

class Hospital {
private:
    vector<Patient> patients;
    vector<Doctor> doctors;

public:
    void admitPatient() {
        Patient newPatient;
        newPatient.admitPatient();
        patients.push_back(newPatient);
    }

    void addDoctor(const Doctor& doctor) {
        doctors.push_back(doctor);
    }

    void assignDoctor() {
        if (patients.empty()) {
            cout << "No patients available. Admitting a new patient.\n";
            admitPatient();  
        } else {
            cout << "Patients available:\n";
            for (const Patient& patient : patients) {
                cout << "- " << patient.getName() << endl;
            }

            cout << "Enter the name of the patient to assign a doctor: ";
            string patientName;
            getline(cin, patientName);

            auto itPatient = find_if(patients.begin(), patients.end(),
                                     [patientName](const Patient& patient) {
                                         return patient.getName() == patientName;
                                     });

            if (itPatient != patients.end()) {
                displayAvailableDoctors();

                cout << "Enter the number of the doctor to assign: ";
                int doctorChoice;
                cin >> doctorChoice;

                if (doctorChoice >= 1 && doctorChoice <= doctors.size()) {
                    Doctor& selectedDoctor = doctors[doctorChoice - 1];
                    selectedDoctor.display();

                    cout << "Assigned to Doctor " << selectedDoctor.getName() << " ("
                         << selectedDoctor.getSpecialization() << ")\n";
                } else {
                    cout << "Invalid doctor choice.\n";
                }
            } else {
                cout << "Patient not found. Please make sure to enter the correct patient name.\n";
            }
        }
    }

    void displayPatients() const {
        if (patients.empty()) {
            cout << "No patients available.\n";
        } else {
            cout << "Patients:\n";
            for (const Patient& patient : patients) {
                patient.display();
                cout << "--------------\n";
            }
        }
    }

    void displayDoctors() const {
        if (doctors.empty()) {
            cout << "No doctors available.\n";
        } else {
            cout << "Doctors:\n";
            for (size_t i = 0; i < doctors.size(); ++i) {
                cout << i + 1 << ". ";
                doctors[i].display();
                cout << "--------------\n";
            }
        }
    }

private:
    void displayAvailableDoctors() const {
        if (doctors.empty()) {
            cout << "No doctors available.\n";
        } else {
            cout << "Available Doctors:\n";
            for (size_t i = 0; i < doctors.size(); ++i) {
                cout << i + 1 << ". " << doctors[i].getName() << " ("
                     << doctors[i].getSpecialization() << ")\n";
            }
        }
    }
};

int main() {
    Hospital hospital;

    
    hospital.addDoctor(Doctor("Dr. Nitin", "Cardiologist"));
    hospital.addDoctor(Doctor("Dr. Aryan", "Orthopedist"));
    hospital.addDoctor(Doctor("Dr. Sunil", "Pediatrician"));

    int choice;
    do {
        cout << "\nHospital Management System Menu:\n";
        cout << "1. Admit a Patient\n";
        cout << "2. Assign a Doctor\n";
        cout << "3. Display Patients\n";
        cout << "4. Display Doctors\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  

        switch (choice) {
            case 1:
                hospital.admitPatient();
                break;
            case 2:
                hospital.assignDoctor();
                break;
            case 3:
                hospital.displayPatients();
                break;
            case 4:
                hospital.displayDoctors();
                break;
            case 0:
                cout << "Exiting the program. Thank you!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }

    } while (choice != 0);

    return 0;
}