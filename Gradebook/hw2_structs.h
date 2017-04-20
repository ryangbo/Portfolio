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

struct Student
{
	char student_ID[6];		//Unique ID number given to each student (ex: ID001)
	char student_name[11];	//Name of student 
	char student_major[31];	//Major of student (ex: CSCE)
};

struct Course
{
	char course_ID[9];		//Course ID number (ex: CSCE1040)
	char course_name[31];	//Course Name	(ex: Computer Science II)
	char department[31];	//Department (ex: Computer Science and Engineering)
};

struct Enrolled
{
	char enrolled_student_name[11];	//Name of student currently enrolled
	char enrolled_course_ID[9];		//Name of course currently enrolled
	int grade[5];					//Grades for students enrolled in courses
};