#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <locale>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

struct Students
{
    char firstName[50];
    char lastName[50];
    char date[30];
    char sex[20];
    char phoneNumber[30];
    char address[200];
    char reiting[10];
};

void menu();
void guest();
void admin();

void createBD();
void returnUser();
void replaceBD();
void addStudent();
void listStudents();
void speedSearch();
void sumRainting();
void deleteBD();
void advancedSearch();
void editStudentBD();
void sortStudents();

void clear();
void error_value();
void print_exit();
void password();
void studentPrint(const Students &student);
void error_openBD(ifstream &file);
void Enter();
void forDelete(bool &found, string &name, string &lastName);

void error_space_line(string &name);
string error_input(int n);
string error_input_date(int n);
string error_input_phone(int n);
string error_input_address(int n);
