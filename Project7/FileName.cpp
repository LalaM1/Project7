#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
using namespace std;

#pragma region Tekrar
//
//void main() {
//	stringstream ss;
//	ss << "Mahmud 45 Leyla 41";
//
//	string name1, name2;
//	int age1, age2;
//
//	ss >> name1;
//	ss >> age1;
//
//	ss >> name2;
//	ss >> age2;
//
//	cout << "Name: " << name1 << endl;
//	cout << "Age: " << age1 << endl;
//	cout << "Name: " << name2 << endl;
//	cout << "Age: " << age2 << endl;
//
//}
#pragma endregion


#pragma region File with object



class Person {
public:
	string name;
	int age;
	Person() = default;
	Person(string name, int age) {
		this->name = name;
		this->age = age;
	}
	void Show() const {
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl;
	}
};



class Database {
public:
	vector<Person> people;

	void AddPerson(Person person) {
		people.push_back(person);		
	}

	void ShowPeople() {
		for (Person p: people) //hazir vectorlarda iterator var deye islede bildik
		{
			cout << "__________________________" << endl;
			p.Show();
		}
	}

	void DeleteLastPerson() {
		people.pop_back();		
	}
};

void WriteToFile(const vector<Person>& people,string path="people.txt") {
	ofstream fs(path, ios::out); //default olaarq outdur yani write mode
	if (fs.is_open()) {
		for (Person p : people) {  //(int i; i<people.size(); i++) pythondaki for
			fs << p.name << "#" << p.age << "\n"; //Li Ming#76\n
		}
	}
	else {
		throw string("File couldn't open...");
	}
	fs.close();

}




void ReadFromFile(vector<Person>& people, string path = "people.txt") {
	ifstream fs(path);
	if (fs.is_open()) {
		while (!fs.eof()) { //tam olaraq faylin sonun qeder gedir
			string row; //1 setrdir setrin sonunu \n gorende basa dusur
			getline(fs, row);
			int counter = 0; //#-lern sayi (fiedleri bir birinden ayirir)

			Person p;
			string str_age; //butun datalar str tipinde gelir

			for (char character : row) { //goturduyu setrdeki her bir simvolun uzerinde tek-tek gezecek
				if (character != '#' && counter == 0) {
					p.name += character;
				}
				else if (character != '#' && counter == 1) {
					str_age += character;
				}
				else { //character == '#' olarsa
					counter++;
				}
			}
			if (str_age.size() != 0) { //yas olan yer bos deyilse  casting edilir
				p.age = stoi(str_age); //string to int methodu stringi inte casting edir
				people.push_back(p);
			}
		}
	}
	else {
		//eger fayl yoxdursa
		throw string("File not found...");
	}
	fs.close();
}


void main() {
	Database db;
	try
	{	
		ReadFromFile(db.people);
	}
	catch (string ex)
	{
		cout << ex << endl;
		WriteToFile(db.people); //ilk defe acanda fayli yartasin deye
	}	

	int choice;
	do
	{
		cout << "\n\n1. Show people \n2. Add Person  \n3. Delete last person \n0.Exit \nChoose: ";
		cin >> choice;
		if (choice == 1) {
			db.ShowPeople();
		}
		else if (choice == 2) {
			Person newPerson;
			cin.ignore();
			cout << "Name: ";
			getline(cin, newPerson.name);
			cout << "Age: ";
			cin >> newPerson.age;
			db.AddPerson(newPerson);
			WriteToFile(db.people);
		}
		else if (choice == 3) {
			db.DeleteLastPerson();
			WriteToFile(db.people);
		}
		else {
			if (choice == 0) {
				cout << "Goodbye..." << endl;
			}
			else {
				cout << "Wrong input..." << endl;
			}
		}
	} while (choice!=0);

	cout << "ushgtjnhikyhntikly" << endl;
}

#pragma endregion

