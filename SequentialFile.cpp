#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

class Student{
    public:
        int rollNo;
        char name[50];
        char address[50];
};

class Files{
    public:

        void addData(){
            Student student;
            ofstream outFile("student.txt", ios::binary | ios::app);
            if(!outFile){
                cout<<"Error opening file";
                return;
            }

            cout<<"Enter roll no";
            cin>>student.rollNo;
            cin.ignore();
            cout<<"Enter name";
            cin.getline(student.name, 50);
            cout<<"Enter address";
            cin.getline(student.address, 50);

            outFile.write(reinterpret_cast<char *>(&student), sizeof(Student));
            outFile.close();

            cout<<"Student information added successfully"<<endl;
        }

        void deleteStudent(){
            int roll;
            cout<<"Enter rollno to delete ";
            cin>>roll;

            ifstream inFile("student.txt", ios::binary);
            if(!inFile){
                cout<<"Error";
                return;
            }

            ofstream tempFile("temp.txt", ios::binary);
            if(!tempFile){
                cout<<"Error"<<endl;
                return;
            }

            bool found = false;
            Student student;

            while(inFile.read(reinterpret_cast<char *>(&student), sizeof(Student))){
                if(student.rollNo != roll){
                    tempFile.write(reinterpret_cast<char *>(&student),sizeof(Student));
                }else{
                    found = true;
                }
            }

            inFile.close();
            tempFile.close();

            if(found){
                remove("student.txt");
                rename("temp.txt", "student.txt");
                cout<<"Student info deleted";
            }else{
                remove("temp.txt");
                cout<<"Student not found"<<endl;
            }
        }

        void display(){
            int rollNumber;
            cout<<"Enter roll no to display";
            cin>>rollNumber;    

            ifstream inFile("student.txt", ios::binary);
            if(!inFile){
                cout<<"Error"<<endl;
                return;
            }

            bool found = false;
            Student student;

            while(inFile.read(reinterpret_cast<char *> (&student), sizeof(Student))){
                if (student.rollNo == rollNumber) {
                    cout << "Roll Number: " << student.rollNo  << endl;
                    cout << "Name: " << student.name << endl;
                    cout << "Address: " << student.address << endl;
                    found = true;
                    break;
                }
            }

            inFile.close();
            if(!found){
                cout<<"Student not fouund"<<endl;
            }
        }
};

int main(){
    Files f;
    f.addData();
    f.display();
    return 0;
}