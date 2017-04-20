//						 +-----------------------------------------------------------------------------------------------+
//						 |	Name: Ryan Gibeault 																		 |
//						 |	Email: Ryangibeault@my.unt.edu																 |
//						 |  Lecture section: CSCE 1040.002															     |
//						 |  Lab section: 1040.302															             |
//						 |  Date Due: 02/45/16	@ 11:59pm												 				 |
//						 |  Program Name: Homework 1																	 |
//						 |  Description: In this program, a student gradebook is created from user inputs to allow for   |
//						 |  adding courses, students, and grades.														 |
//						 +-----------------------------------------------------------------------------------------------+

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include "hw2_structs.h"
#include "hw2_functions.h"

using namespace std;

void printMenu()
{
	cout << endl;
	cout << "Welcome to the Student Grade Book!" << endl;
	cout << "Select a number between 1-9: " << endl;
	cout << "1. Add a new course" << endl;
	cout << "2. Add a new student" << endl;
	cout << "3. Add a student to a course" << endl;
	cout << "4. Add grades for a student in a course" << endl;
	cout << "5. Print a list of all courses" << endl;
	cout << "6. Print a list of all students" << endl;
	cout << "7. Print a list of all students in a course" << endl;
	cout << "8. Compute the average for a student in a course" << endl;
	cout << "9. Load grade book (from a user-specified file)" << endl;
	cout << "10. Save grade book (to a user-specified file)" << endl;
	cout << "11. Exit" << endl;
	return;
}

void initialize_strings(Student student_arr[], Course course_arr[], Enrolled enrolled_arr[])
{
	int i=0;
	int j=0;
	
	//Initialize struct variables
	for(i = 0; i < 100; i++)
	{
		strcpy(enrolled_arr[i].enrolled_student_name, " ");
		strcpy(enrolled_arr[i].enrolled_course_ID, " ");
		
		for(j = 0 ; j < 5 ; j++)
		{
			enrolled_arr[i].grade[j] = -1;
		}
		
		if(i<10)
		{
			strcpy(course_arr[i].course_ID, " ");
			strcpy(course_arr[i].department, " ");
			strcpy(course_arr[i].course_name, " ");
		}
		
		if(i<25)
		{
			strcpy(student_arr[i].student_name," ");
			strcpy(student_arr[i].student_major," ");
			strcpy(student_arr[i].student_ID," ");
		}
	}
	return;
}

void add_course(int &current_course_ID_num, Course course_arr[])
{
	//check for number of courses existing. Deny adding class if 10 already exist.
	if(current_course_ID_num == 9)
	{
		cout << "Error: Maximum number of courses already exist. Please choose another menu item." << endl;
	}
	else
	{
		cout << "ENTER COURSE ID> ";
		cin  >> course_arr[current_course_ID_num].course_ID; //Create course ID
		cout << "ENTER COURSE NAME> ";
		
		cin.ignore(); //terminate newline character for each getline
		
		cin.getline(course_arr[current_course_ID_num].course_name, 31);
		
		cout << "ENTER DEPARTMENT NAME> ";
		cin.getline(course_arr[current_course_ID_num].department, 31); //Create department name						
		
		cout << course_arr[current_course_ID_num].course_ID << " has been added." << endl;
		current_course_ID_num++; //increment course ID number to store more classes.
	}
}

void add_student(char student_name_compare[], int &current_student_ID_num, Student student[])
{
	bool check_for_name = false; 	  //check for same name
	
	//Check for current number of students, deny adding more if 25 already exist.
	if(current_student_ID_num == 25)
	{
		cout << "Error: Maximum number of students already exist. Please choose another menu item." << endl;
	}
	else
	{
		cout << "ENTER STUDENT NAME> ";
		
		check_for_name = false;
		
		cin  >> student_name_compare; //User input for name
	
		check_for_name = student_exists(student_name_compare, student);
		
		if(check_for_name == true)
		{
				cout << "Error: " << student_name_compare << " already exists. Please select another menu option. " << endl;
		}
		else
		{
			cout << "ENTER STUDENT MAJOR> ";
			cin  >> student[current_student_ID_num].student_major;
			
			strcpy (student[current_student_ID_num].student_name,student_name_compare); 
	
			//convert integer to string, format to "IDxxx"
			snprintf(student[current_student_ID_num].student_ID, sizeof(student[current_student_ID_num].student_ID), "ID%03d", current_student_ID_num+1); 
			
			cout << "Added: " << student[current_student_ID_num].student_name << " " << student[current_student_ID_num].student_ID << endl;
			current_student_ID_num++;
		}
	}
}

void add_student_to_course(char student_name_compare[], char course_compare[], int &current_course_ID_num, int &current_student_ID_num, int &enrolled_course_ID, int &current_enrolled_ID_num, Student student[], Course course[], Enrolled enrolled[])
{
	int count = 0;
	int i = 0;
	bool check_for_name;
	bool validate_name;
	bool validate_course;
	bool check_for_course;
	bool validate_enrollment;
					
	cout << "Please select a student to enroll: " << endl;
	//Print list of student names
	for(i = 0; i < current_student_ID_num; i++)
	{
		cout << student[i].student_ID << " : " << student[i].student_name << endl;
	}
	
	cout << "\ncmd> ";
	cin  >> student_name_compare;
	
	do
	{
		check_for_name = false;
		
		//Check to make sure student exists. Give error message if name is not found and take input until valid name is entered
		while(!check_for_name)
		{						
			check_for_name = student_exists(student_name_compare, student);
			
			if(check_for_name == false)
			{
				cout << "Error: " << student_name_compare << " does not exist. Please enter an existing name: " << endl;
				cout << "\ncmd> ";
				cin >> student_name_compare;
			}
		}
		
		//check for number of courses student is enrolled in
		count = student_exists_enrolled(student_name_compare, enrolled);
		
		if(count >= 4)
		{
			cout << "Error: " << student_name_compare << " is already enrolled in 4 classes. Please select another menu option." << endl;
		}
		else
		{
			validate_name = true;
		}
	}while(!validate_name);
		
	//Add student to course
	cout << "Please select a course to add " << student_name_compare << " to:" << endl;
	for(i = 0; i < current_course_ID_num; i++)
	{
		cout << course[i].course_ID << endl;
	}
	
	//CHECK IF CLASS IS FULL
	do
	{				
		validate_course = false;
		
		//Check to make sure course exists. Give error and return to menu if invalid entry
		do
		{						
			cout << "\ncmd> ";
			cin  >> course_compare;
			
			check_for_course = course_exists(course_compare, course);
			
			if(!check_for_course)
			{
				cout << "Error: " << course_compare << " does not exist. Please enter an existing name: " << endl;
			}
		}while(!check_for_course);
		
		count = num_students_in_course(course_compare, enrolled); //Find number of students enrolled in course
		
		if(count >= 10)
		{
			cout << "Error: Maximum number of students are already enrolled in " << course_compare << ". Please select a new menu option." << endl;
		}
		else
		{
			do
			{	
				validate_enrollment = false;
			
				for(int i = 0 ; i <= 100 ; i++)
				{
					if((strcmp(course_compare,  enrolled[i].enrolled_course_ID) == 0) && (strcmp(student_name_compare,  enrolled[i].enrolled_student_name) == 0))
					{
						cout << "Error: " << student_name_compare << " is already enrolled in " << course_compare << ". Please select a new menu option." << endl;
						validate_enrollment = true;
						validate_course = true;
					}
				}
				
				if(!validate_enrollment)
				{
					validate_course = true;
					validate_enrollment = true;
					
					strcpy(enrolled[current_enrolled_ID_num].enrolled_course_ID, course_compare);
					strcpy(enrolled[current_enrolled_ID_num].enrolled_student_name, student_name_compare);
					
					cout << enrolled[current_enrolled_ID_num].enrolled_student_name << " has been added to " << enrolled[current_enrolled_ID_num].enrolled_course_ID << "." << endl;
				}
				
			}while(!validate_enrollment);
		}
		current_enrolled_ID_num++;
	}while(!validate_course);
}

void add_grades_for_student(char student_name_compare[], char course_compare[], int &current_course_ID_num, int &current_student_ID_num, int &enrolled_course_ID, int &current_enrolled_ID_num, Student student[], Course course[], Enrolled enrolled[])
{
	int count = 0;
	int i = 0;
	int enrolled_index = 0;
	int enter_grade = 0;
	bool check_for_name;
	bool validate_name;
	bool validate_course;
	bool check_for_course;
	bool validate_enrollment;
	
	cout << "Please select a student to add grades for: " << endl;
	//Print list of student names
	for(i = 0; i < current_student_ID_num; i++)
	{
		cout << student[i].student_ID << " : " << student[i].student_name << endl;
	}
	
	cout << "\ncmd> ";
	cin  >> student_name_compare;
	
	do
	{
		//Check to make sure student exists. Give error message if name is not found and take input until valid name is entered
		while(!check_for_name)
		{						
			check_for_name = student_exists(student_name_compare, student);
			
			if(check_for_name == false)
			{
				cout << "Error: " << student_name_compare << " does not exist. Please enter an existing name: " << endl;
				cout << "\ncmd> ";
				cin >> student_name_compare;
			}
			else
			{
				validate_name = true;
			}
		}
	}while(!validate_name);	
	
	cout << "Please select a course to add grades for " << student_name_compare << endl;
	for(i = 0; i < current_course_ID_num; i++)
	{
		cout << course[i].course_ID << endl;
	}
	
	//Check to make sure course exists. Give error and return to menu if invalid entry
	do
	{	
		validate_course = false;
		do
		{			
			cout << "\ncmd> ";
			cin >> course_compare;
		
			check_for_course = course_exists(course_compare, course);
			
			if(check_for_course == false)
			{
				cout << "Error: " << course_compare << " does not exist. Please enter an existing name: " << endl;
			}
			else
			{
				validate_course = true;
			}
		}while(!check_for_course);
	}while(!validate_course);
	
	do
	{
		validate_enrollment = false;
		
		for(int i = 0 ; i <= 100 ; i++)
		{
			if((strcmp(course_compare,  enrolled[i].enrolled_course_ID) == 0) && (strcmp(student_name_compare,  enrolled[i].enrolled_student_name) == 0))
			{
				enrolled_index = i;
				validate_enrollment = true;
			}
		}
		
		if(!validate_enrollment)
		{
						cout << "Error: " << student_name_compare << " is not enrolled in " << course_compare << ". Please select a new menu option." << endl;
					}
					
		}while(!validate_enrollment);
	
		cout << "Enter in grade(s) for " << enrolled[enrolled_index].enrolled_student_name << " in " << enrolled[enrolled_index].enrolled_course_ID << ".\n";
		cout << "Enter in 5 separate grades using \"Enter/Return\" after each grade, or type \"-1\" to stop.\n";
		
		count=0;
		
		do
		{	
			cin  >> enter_grade;
			
			if(enter_grade >= 0)
			{
				enrolled[enrolled_index].grade[count] = enter_grade;
				count++;
			}
			
		}while((enter_grade != -1) && (count < 5));
}

void print_courses(int &current_course_ID_num, Course course_arr[])
{
	int i = 0;
	
	cout << "\nCourses" << endl;
	cout << "-------" << endl;
	for(i = 0; i < current_course_ID_num; i++)
	{
		cout << course_arr[i].course_ID << "\t";
		cout << course_arr[i].course_name << "\t";
		cout << course_arr[i].department << endl;
	}
}

void print_students(int &current_student_ID_num, Student student_arr[])
{
	int i = 0;
	
	cout << "\nStudents" << endl;
	cout << "--------" << endl;
	for(i = 0; i < current_student_ID_num; i++)
	{
		cout << student_arr[i].student_ID << "\t";
		cout << student_arr[i].student_name << "\t";
		cout << student_arr[i].student_major << endl;
	}
}

void print_students_in_course(int &current_course_ID_num, char course_compare[], Enrolled enrolled[], Course course[])
{
	bool check_for_course = false;
	int i = 0;
	
	cout << "Please select a course: " << endl;
	for(i = 0; i < current_course_ID_num; i++)
	{
		cout << course[i].course_ID << endl;
	}
	
	do
	{						
		cout << "\ncmd> ";
		cin  >> course_compare;
		
		check_for_course = course_exists(course_compare, course);
		
		if(!check_for_course)
		{
			cout << "Error: " << course_compare << " does not exist. Please enter an existing name: " << endl;
		}
		else
		{
			cout << "Students in " << course_compare << ":" << endl;
			for(int i = 0 ; i <= 100 ; i++)
			{
				if((strcmp(course_compare,  enrolled[i].enrolled_course_ID) == 0))
				{
					cout << enrolled[i].enrolled_student_name << endl;
				}
			}
		}
	}while(!check_for_course);	
}

void compute_average(char course_compare[], char student_name_compare[], Enrolled enrolled[], Course course[], Student student[])
{
	int i = 0;
	int j = 0;
	int count = 0;
	float avg = 0;
	int sum = 0;
	
	bool check_for_course = false;
	bool check_for_name = false;
	
	cout << "ENTER COURSE ID> ";
	do
	{	
		cin  >> course_compare;
		
		check_for_course = course_exists(course_compare, course);
		
		if(!check_for_course)
		{
			cout << "Error: " << course_compare << " does not exist. Please enter an existing course: " << endl;
		}
	}while(!check_for_course);

	cout << "ENTER STUDENT NAME> ";
	do
	{	
		cin  >> student_name_compare;
		
		check_for_name = student_exists(student_name_compare, student);
		
		if(!check_for_name)
		{
			cout << "Error: " << student_name_compare << " does not exist. Please enter an existing name: " << endl;
		}
	}while(!check_for_name);
	
	for(int i = 0 ; i < 100 ; i++)
	{
		if((strcmp(course_compare,  enrolled[i].enrolled_course_ID) == 0) && (strcmp(student_name_compare,  enrolled[i].enrolled_student_name) == 0))
		{
			for(int j = 0 ; j < 5 ; j++)
			{
				if(enrolled[i].grade[j] >= 0)
				{
					count++;
					sum += enrolled[i].grade[j];
					cout << enrolled[i].grade[j] << " ";
				}
			}
		}
	}
	
	avg = sum/count; //calculate average
	
	printf("= %05.2f", avg); //format average to the nearest tenth
}

bool student_exists(char student_name_compare[], Student student_arr[])
{
	for(int i=0 ; i <= 25 ; i++)
	{	
		if(strcmp (student_name_compare, student_arr[i].student_name) == 0)
		{
			return true;
		}
	}
	return false;
}

int student_exists_enrolled(char student_name_compare[], Enrolled enrolled_arr[])
{
	int count = 0; //Number of classes student is enrolled in
	
	for(int i=0 ; i <= 100 ; i++)
	{	
		if(strcmp (student_name_compare, enrolled_arr[i].enrolled_student_name) == 0)
		{
			count++;
		}
	}
	return count;
}

bool course_exists(char course_compare[], Course course_arr[])
{
	for(int i=0 ; i <= 10 ; i++)
	{	
		if(strcmp (course_compare, course_arr[i].course_ID) == 0)
		{
			return true;
		}
	}
	return false;
}

int num_students_in_course(char course_compare[], Enrolled enrolled_arr[])
{
	int count = 0;
	
	for(int i = 0 ; i <= 100 ; i++)
	{
		if(strcmp(course_compare, enrolled_arr[i].enrolled_course_ID) == 0)
		{
			count++;
		}
	}
	return count;
}

//http://stackoverflow.com/questions/7868936/read-file-line-by-line - Information regarding string tokenizing adjusted from answer in question.
void load_from_file(Student student_arr[], Course course_arr[], Enrolled enrolled_arr[], int &current_student_ID_num, int &current_course_ID_num, int &current_enrolled_ID_num)
{
	char file_name[100];
	
	cout << "Enter file name: ";
	
	cin  >> file_name;
	
	ifstream infile(file_name); //open file
	
	//check for file opening errors
	if (infile.fail())
	{
		 cout << "Unable to open " << file_name;
		 return;
	}
	else
	{
		cout << "Data input successfully initialized from: " << file_name << endl;
	}

	
	string line; //read each line
	
	//Strings used to declare new data (student/course/enrollment)
	string student_string = "STUDENTS";
	string end_of_students = "END OF STUDENTS";
	
	string course_string = "COURSES";
	string end_of_courses = "END OF COURSES";
	
	string student_course_string = "STUDENTS IN COURSES";
	string end_of_student_course = "END OF STUDENTS IN COURSES";
	
	char tab[1024];
	int position = 0;
	int i = 0;
	current_student_ID_num = 0;
	current_course_ID_num = 0;
	current_enrolled_ID_num = 0;
	
	//read lines from file
	while (getline(infile, line))
	{
		istringstream iss(line);
		
		//LOAD STUDENTS FROM FILE
		if(line == student_string)
		{
			getline(infile, line);
			
			do
			{			
				strncpy(tab, line.c_str(), sizeof(tab));
				tab[sizeof(tab) - 1] = 0;
				
				position = 0;
				
				char *p = strtok(tab, ","); //comma delimiter is used to separate names and values
				
				while (p) 
				{
					if(position == 0)
					{
						strcpy(student_arr[current_student_ID_num].student_ID, p);
					}
					else if(position == 1)
					{
						strcpy(student_arr[current_student_ID_num].student_name, p);
					}
					else if(position == 2)
					{
						strcpy(student_arr[current_student_ID_num].student_major, p);
					}
					p = strtok(NULL, ",");	//When a comma (delimiter) is read in, tokenize
					position++;
				}
				
				current_student_ID_num++;
				
				getline(infile, line);
			}while(line != end_of_students);			
		}
		
		//LOAD COURSES FROM FILE
		if(line == course_string)
		{
			getline(infile, line);
			
			do
			{			
				strncpy(tab, line.c_str(), sizeof(tab));
				tab[sizeof(tab) - 1] = 0;
				
				position = 0;
				
				char *p = strtok(tab, ","); 
				
				while (p) 
				{
					if(position == 0)
					{
						strcpy(course_arr[current_course_ID_num].course_ID, p);
					}
					else if(position == 1)
					{
						strcpy(course_arr[current_course_ID_num].course_name, p);
					}
					else if(position == 2)
					{
						strcpy(course_arr[current_course_ID_num].department, p);
					}
					p = strtok(NULL, ",");	//When a comma (delimiter) is read in, tokenize
					position++;
				}
				
				current_course_ID_num++;
				
				getline(infile, line);
			}while(line != end_of_courses);	
		}
		
		//LOAD STUDENTS IN COURSES
		if(line == student_course_string)
		{
			getline(infile, line);
			
			do
			{			
				strncpy(tab, line.c_str(), sizeof(tab));
				tab[sizeof(tab) - 1] = 0;
				
				position = 0;
				i = 0;
				
				char *p = strtok(tab, ","); 
				
				while (p) 
				{
					if(position == 0)
					{
						strcpy(enrolled_arr[current_enrolled_ID_num].enrolled_student_name, p);
					}
					else if(position == 1)
					{
						strcpy(enrolled_arr[current_enrolled_ID_num].enrolled_course_ID, p);
					}
					else if(position >= 2)
					{
						enrolled_arr[current_enrolled_ID_num].grade[position-2] = atoi(p);
					}
					p = strtok(NULL, ",");	//When a comma (delimiter) is read in, tokenize
					position++;
				}
				
				current_enrolled_ID_num++;
				
				getline(infile, line);
			}while(line != end_of_student_course);	
		}
	}
	
	infile.close(); //close file
	
	cout << "Input file closed: " << file_name << endl;
}

void write_to_file(Student student_arr[], Course course_arr[], Enrolled enrolled_arr[], int &current_student_ID_num, int &current_course_ID_num, int &current_enrolled_ID_num)
{
	

	char file_name[100];
	
	cout << "Enter output file name: ";
	
	cin  >> file_name;
	
	ofstream outFile(file_name); //open output file location
	
	if (outFile.fail())
	{
		 cout << "Unable to open " << file_name;
		 return;
	}
	else
	{
		cout << "Data input successfully written to: " << file_name << endl;
	}
	
	
	//Ouput strings to declare new struct and print each string with the comma delimeter to separate names and values
	outFile << "STUDENTS" << endl;
	
	for(int i = 0; i < current_student_ID_num; i++)
	{
		outFile << student_arr[i].student_ID << ",";
		outFile << student_arr[i].student_name << ",";
		outFile << student_arr[i].student_major << endl;
	}
	
	outFile << "END OF STUDENTS" << endl;
	
	outFile << "COURSES" << endl;
	
	for(int i = 0; i < current_course_ID_num; i++)
	{
		outFile << course_arr[i].course_ID << ",";
		outFile << course_arr[i].course_name << ",";
		outFile << course_arr[i].department << endl;
	}
	
	outFile << "END OF COURSES" << endl;
	
	outFile << "STUDENTS IN COURSES" << endl;
	
	for(int i = 0; i < current_course_ID_num; i++)
	{
		outFile << enrolled_arr[i].enrolled_student_name << ",";
		outFile << enrolled_arr[i].enrolled_course_ID << ",";
		
		for(int j = 0; j < 5 ; j++)
		{
			outFile << enrolled_arr[i].grade[j];
			if(j < 4)
			{
				outFile << ",";
			}
		}
		
		outFile << endl;
	}
	
	outFile << "END OF STUDENTS IN COURSES" << endl;
	
	outFile.close(); //close file
	
	cout << "Output file closed: " << file_name << endl;
	
}