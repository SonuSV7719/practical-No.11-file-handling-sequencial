#include<bits/stdc++.h>

using namespace std;

class Employee
{
    char name[50];
    int empId;
    int salary;
    char desig[70];
    public:
    Employee();
    void getData();
    void displayData();
    void storeData();
    void search(int id);
    void deletion(int id);
    void update(int id);
    void viewStoredRecord();
};

Employee::Employee()
{
    strcpy(name, "No name");
    empId = -1;
    salary = -1;
    strcpy(desig, "No designation");
}

void Employee::getData()
{
    cout << "Enter name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "Enter employee ID: ";
    cin >> empId;
    cout << "Enter salary: ";
    cin >> salary;
    cout << "Enter designation: ";
    cin.ignore();
    cin.getline(desig, 70);
}

void Employee::displayData()
{
    cout << "Name: " << name <<endl;
    cout << "Employee ID: " << empId << endl;
    cout << "Salary: " << salary << endl;
    cout << "Designation: " << desig << endl;   
}

void Employee::viewStoredRecord()
{
    fstream fin;
    fin.open("data.txt", ios::in);
    if(!fin)
        cout << "File not created!" << endl;
    else{
        fin.read((char*)this, sizeof(*this));
        cout << "***************************** Stored data is ****************************" << endl;
        while(!fin.eof())
        {
            displayData();
            cout << endl;
            fin.read((char*)this, sizeof(*this));
        }
    }
}

void Employee::storeData()
{
    fstream fout;
    fout.open("data.txt", ios::out | ios::app);
    if(empId != -1 && salary != -1)
        fout.write((char*)this, sizeof(*this));
    fout.close();
}

void Employee::search(int id)
{
    fstream fin;
    int cnt = 0;
    fin.open("data.txt", ios::in);
    if(!fin)
        cout << "File not created!" << endl;
    else
    {
        fin.read((char*)this, sizeof(*this));
        while (!fin.eof())
        {
             if(id == empId)
            {
                cout << "Record found and record is as follows: " << endl;
                displayData();
                cnt++;
            }
            fin.read((char*)this, sizeof(*this));
        }

        if(cnt == 0)
            cout << "Record not found!" << endl;
        fin.close();

    }

}

void Employee::deletion(int id)
{
    fstream fin;
    fstream fout;
    fin.open("data.txt", ios::in);
    if(!fin)
        cout << "File not exist!" << endl;
    else
    {
        fout.open("temp.txt", ios::out);
        fin.read((char*)this, sizeof(*this));
        while(!fin.eof())
        {
            if(id != empId)
                fout.write((char*)this, sizeof(*this));
            fin.read((char*)this, sizeof(*this));            
        }
    }
    fin.close();
    fout.close();
    remove("data.txt");
    rename("temp.txt", "data.txt");
}

void Employee::update(int id)
{
    fstream file;
    file.open("data.txt", ios::in | ios::out | ios::ate);
    file.seekg(0);
    file.read((char*)this, sizeof(*this));
    while(!file.eof())
    {
        if(id == empId)
        {
            getData();
            file.seekp(file.tellp()-sizeof(*this));
            file.write((char*)this, sizeof(this));
        }
        file.read((char*)this, sizeof(*this));
    }

}

int main()
{
    Employee e1;
    do
    {
        /* code */
        int choice;
        cout << "************************ Menu *******************" << endl;
        cout << "1.Insert\n2.Display\n3.Search\n4.Delete\n5.Update\n6.Exit\n";
        cout << "Select your option by pressing index of given menu: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            /* code */
            e1.getData();
            e1.storeData();
            break;
        case 2:
            /* code */
            e1.viewStoredRecord();
            break;
        case 3:
            /* code */
            int id;
            cout << "Enter which Employee ID you want to search: ";
            cin >> id;
            e1.search(id);
            break;
        case 4:
            /* code */
            int emp_id;
            cout << "Enter which Employee ID you want to Delete: ";
            cin >> emp_id;
            e1.deletion(emp_id);
            cout << "Record Deleted!!" << endl;
            break;
        case 5:
            /* code */
            cout << "Enter which Employee ID you want to update: ";
            cin >> emp_id;
            e1.update(emp_id);
            break;
        
        case 6:
            /* code */
            exit(0);
            break;
        
        default:
            cout << "You entered wrong option plz try again!!" << endl;
            break;
        }
    } while (1);
    

    return 0;
}