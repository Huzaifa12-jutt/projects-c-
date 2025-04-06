#include <iostream>
#include <fstream>
#include <algorithm> // For transform()
using namespace std;

class Student {
protected:
    string name, university;
    float gpa;
    string projects[3];

public:
    void setData(string n, string u, float g, string* p) {
        name = n;
        university = u;
        gpa = g;
        for (int i = 0; i < 3; i++) {
            projects[i] = p[i];
        }
    }

    void display() {
        cout << "\n=== Student Profile ===" << endl;
        cout << "Name: " << name << endl;
        cout << "University: " << university << endl;
        cout << "GPA: " << gpa << endl;
        cout << "Projects: ";
        for (int i = 0; i < 3; i++) {
            cout << projects[i] << "  ";
        }
        cout << endl;
    }

    string getUniversity() { return university; }
    float getGpa() { return gpa; }
    string* getProjects() { return projects; }
};

class JobRecommendation : public Student {
public:
    void getInput() {
        string name, university;
        float gpa;
        string projects[3];

        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter University Name (FAST, NUST, AIR, LUMS): ";
        getline(cin, university);
        cout << "Enter GPA: ";
        cin >> gpa;
        cin.ignore(); // Clear input buffer

        cout << "Enter 3 Project Names: ";
        for (int i = 0; i < 3; i++) {
            getline(cin, projects[i]);
        }

        // Convert university name to uppercase to handle case sensitivity
        transform(university.begin(), university.end(), university.begin(), ::toupper);

        setData(name, university, gpa, projects);
    }

    void recommendJob() {
        string* projects = getProjects();
        string university = getUniversity();
        float gpa = getGpa();

        bool hasRelevantProject = false;
        for (int i = 0; i < 3; i++) {
            string project = projects[i];
            transform(project.begin(), project.end(), project.begin(), ::tolower);
            if (project == "ai" || project == "ml" || project == "data science" || project == "software") {
                hasRelevantProject = true;
                break;
            }
        }

        string job;
        if ((university == "FAST" || university == "NUST" || university == "AIR" || university == "LUMS") && gpa >= 3.0 && hasRelevantProject) {
            job = "Software Engineer at Google";
            cout << " Congratulations! You are eligible for: " << job << endl;
        } else if (gpa >= 2.5) {
            job = "Internship at Microsoft";
            cout << " You are eligible for: " << job << endl;
        } else {
            job = "No job recommendation available. Improve GPA and project skills!";
            cout << " Sorry! " << job << endl;
        }

        // Save to file
        saveResult(job);
    }

    void saveResult(string job) {
        ofstream file("JobResults.txt", ios::app);
        if (file) {
            file << name << " (" << university << ", GPA: " << gpa << ") --> " << job << endl;
            file.close();
            cout << " Result saved successfully!\n";
        } else {
            cout << " Error: Could not save results!\n";
        }
    }
};

int main() {
    JobRecommendation job;
    job.getInput();
    job.recommendJob();
    return 0;
}
