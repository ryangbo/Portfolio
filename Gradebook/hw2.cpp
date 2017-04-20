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

int main()
{
	struct Course course[10];		//Limit of 10 total courses
	struct Student student[25]; 	//Limit of 25 total students
	struct Enrolled enrolled[100];	//Limit of 100 total enrolled students

	int userSelection=0;		      //User selection for menu number
	int current_course_ID_num = 0;    //Keep track of course IDs
	int current_student_ID_num = 0;	  //Keep track of student IDs
	int current_enrolled_ID_num = 0;  //Keep track of enrollments
		
	char student_name_compare[11] = " "; //Temporary student name used for check, stored to enrolled.student_name once validated
	char course_compare[11] = " "; 		 //Temporary student name used for check, stored to enrolled.course_name once validated
	
	
	//INITIALIZE STRINGS TO BLANK SPACE
	initialize_strings(student, course, enrolled);
	
	printMenu(); //Print the menu once
			
	do
	{		
		cout << "\ncmd> ";
		cin  >> userSelection; //Usr input for switch statement
	
		switch(userSelection)
		{
			//Add new course
			case 1: add_course(current_course_ID_num, course); break;
			
			//Add new student
			case 2: add_student(student_name_compare, current_student_ID_num, student); break;
			
			//Add student to course
			case 3:	add_student_to_course(student_name_compare, course_compare, current_course_ID_num, current_student_ID_num, current_course_ID_num, current_enrolled_ID_num, student, course, enrolled); break;
				
			//Add grades for student in a course		
			case 4:	add_grades_for_student(student_name_compare, course_compare, current_course_ID_num, current_student_ID_num, current_course_ID_num, current_enrolled_ID_num, student, course, enrolled); break;
				
			//Print courses
			case 5: print_courses(current_course_ID_num, course); break;
					
			//Print a list of all students
			case 6: print_students(current_student_ID_num, student); break;
			
			//Print a list of all students in a course
			case 7: print_students_in_course(current_course_ID_num, course_compare, enrolled, course); break;
			
			//Compute the average for a student in a course			
			case 8: compute_average(course_compare, student_name_compare, enrolled, course, student); break;
			
			case 9: load_from_file(student, course, enrolled, current_student_ID_num, current_course_ID_num, current_enrolled_ID_num); break;
			
			case 10: write_to_file(student, course, enrolled, current_student_ID_num, current_course_ID_num, current_enrolled_ID_num); break;
		}		
	}while(userSelection != 11);

	return 0;
}