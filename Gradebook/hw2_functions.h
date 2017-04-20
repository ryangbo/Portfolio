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

void printMenu();										  //Print main menu
void initialize_strings(Student[], Course[], Enrolled[]); //Initialize variables
void add_course(int &, Course[]);						  //Add new course
void add_student(char[], int &, Student[]);       		  //Add new student
void add_student_to_course(char[], char[], int &, int &, int &, int &, Student[], Course[], Enrolled[]); // Add student to course
void add_grades_for_student(char[], char[], int &, int &, int &, int &, Student[], Course[], Enrolled[]); //Add grades for student
void print_courses(int &, Course[]);					  //Print courses
void print_students(int &, Student[]);				  	  //Print students
void print_students_in_course(int &, char[], Enrolled[], Course[]);		  //Prints students in a course
void compute_average(char[] , char [], Enrolled[], Course[], Student[]);  //Computes the average for a student in a class
bool student_exists(char[], Student[]);				  //Compare user input names with stored names to validate input
bool course_exists(char[], Course[]); 				  //Compare user input names with stored courses to validate input
int student_exists_enrolled(char[], Enrolled[]); 	  //Checks if student is enrolled in a course
int num_students_in_course(char[], Enrolled[]);		  //Checks number of students enrolled in a course
void load_from_file(Student[], Course[], Enrolled[], int &, int &, int &);	//load file to course
void write_to_file(Student[], Course[], Enrolled[], int &, int &, int &);	//load file to course