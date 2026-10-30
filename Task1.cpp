#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cctype>
using namespace std;

struct Course{
	string name;
	string grade;
	double creditHours;
	double gradePoint;
};

double getGradePoint(string grade){
	for(int i = 0; i < (int) grade.length(); i++){
		grade[i] = toupper(grade[i]);
	}
	
	if(grade == "A" || grade == "A+") return 4.0;
	if(grade == "A-") return 3.7;
	if(grade == "B+") return 3.3;
	if (grade == "B") return 3.0;
	if(grade == "B-") return 2.7;
	if(grade == "C+") return 2.3;
	if(grade == "C") return 2.0;
	if(grade == "C-") return 1.7;
	if(grade == "D+") return 1.3;	
	if(grade == "D") return 1.0;
	if(grade == "F") return 0.0;
	
	return -1.0;
}

int main(){
	
	int n;
	vector<Course> courses;
	
	double totalCredits = 0;
	double totalPoint = 0;
	
	cout << "====  CGPA CALCULATOR  =====\n";
		cout << "Enter Number OF Courses : ";
		if(!(cin >> n) || n <= 0){
			cout << "Invalid Number of Courses!\n";
			return 1;
		}
		
	for(int i = 0; i < n; i++){
		Course c;
		
		cout << "\nCourse " << i +1 << endl;
		
		cout << "Enter Course Name : ";
		cin >> ws;
		getline(cin, c.name);
		
		
		cout << "Enter Credit Hours : ";
		if(!(cin >> c.creditHours) || c.creditHours <= 0){
			cout << " Invalid Credit Hours!\n";
			return 1;
		}
		
		cout << "Enter Grade (A, A-, B+, B, etc.): ";
		cin >> c.grade;
		
		c.gradePoint = getGradePoint(c.grade);
		
		if(c.gradePoint < 0){
			cout << "Invalid Grade  Entered!\n";
			return 1;
		}
		
	double qualityPoints =
		c.gradePoint * c.creditHours;
		
	totalCredits += c.creditHours;
	totalPoint +=qualityPoints;
	
	courses.push_back(c);			
	}
	
	cout << fixed << setprecision(2);
	
	cout << "\n===== COURSE RESULT =====\n";
	cout << left<< setw(22) << "COURSE"
		 << setw(12) << "Grade"
		 << setw(12) << "Credits"
		 << setw(12) << "Points" << endl;
		 
	for(int i = 0; i < (int)courses.size(); i++){
		double points = courses[i].gradePoint
					   *courses[i].creditHours;
					   
		cout << left << setw(22) << courses[i].name
					 << setw(12) << courses[i].grade
					 << setw(12) << courses[i].creditHours
					 << setw(12) << points << endl;
	}
	
	
	double semesterGPA = totalPoint  / totalCredits;
	
	cout << "\nTotal Credit Hours : " << totalCredits;
	cout << "\nTotal Quality Points : " << totalPoint;
	cout << "\nSemester GPA : " << semesterGPA << endl;
	
	char answer;
	cout <<"\nDo you have previous semester (y/n) : ";
	cin >> answer;
	
	if(answer == 'y' || answer == 'Y'){
		double previousCGPA, previousCredits;
		
		cout << "Enter previous CGPA : ";
		if(!(cin >> previousCGPA) || previousCGPA < 0 || previousCGPA > 4.0){
			cout << "Invalid previous CGPA!\n";
			return 1;
		}
		
		double previousPoint =
			previousCGPA * previousCredits;
			
		double overallCGPA = 
				(previousPoint + totalPoint) /
				(previousCredits + totalCredits);
		
		cout << "Overall CGPA : " << overallCGPA << endl;
	}
	else if(answer == 'n' || answer == 'N'){
		cout << "Overall CGPA : " << semesterGPA << endl; 
	}
	else{
		cout << "Invalid Choice!\n";
		return 1;
	}
	
	cout << "\nCalcultion Completed Successfully!\n";
	return 0;
	
	
//	float g1, g2, g3;
//	
//	
//	float c1, c2, c3;\
//	float credetpoints, credethours, GPA;
//	
//	cout <<"Enter grade point of Course 1 : ";
//	cin >> g1;
//	cout <<"Enter credethours of Course 1 : ";
//	cin >> c1;
//	
//	cout <<"Enter grade point of Course 2 : ";
//	cin >> g2;
//    cout <<"Enter credethours of Course 2 : ";
//	cin >> g2;
//	
//	cout << "Enter grade point of Course 3 : ";
//	cin >> g3;
//	cout << "Enter credethours of Course 3 : ";
//	cin >> g3;
//	
//	credetpoints = (g1 * c1) + (g2 * c2) + (g3 * c2);
//	credethours = c1 + c2 + c3;
//	
//	GPA = credetpoints / credethours;
//	
//	cout << "GPA is : " << GPA;
	
//	return 0;
	
	
}  
