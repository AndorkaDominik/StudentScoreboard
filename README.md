# Student Management System

This project was created as a university homework task. The program is written in C and is designed to manage student data, including calculating scores and identifying students who need to retake exams or assignments.

## Project Overview

The project consists of a C program that reads student data from a file, processes the data to calculate various scores, and then provides several functionalities such as listing students, generating retake lists, and displaying rankings.

## Files

- `main.c`: The main program file containing all the functions and logic.
- `mintafajl2.txt`: The input file containing student data.
- `zhPot.txt`: The output file listing students who need to retake exams.
- `hfPot.txt`: The output file listing students who need to retake assignments.
- `debugmalloc.h`: Header file for custom memory allocation functions.

## Functionality

### Structures

- `Csoport`: Structure to hold group data.
- `Hallgato`: Structure to hold student data, including personal details, scores, and retake requirements.

### Functions

- `hozzaadHallgato(Hallgato *head, Hallgato *uj)`: Adds a new student to the list.
- `adatokBeolvasasa(Hallgato **head)`: Reads student data from the input file.
- `adatokFelszabaditasa(Hallgato *head)`: Frees allocated memory for student data.
- `kiirLista(Hallgato *head)`: Prints the list of students.
- `pontszamokSzamolasa(Hallgato *head)`: Calculates the scores for each student.
- `compare`, `compareK`, `compareN`, `compareHF`: Comparison functions for sorting.
- `listaTombbe`, `listaTombbeN`, `listaTombbeK`, `listaTombbeHF`: Functions to copy list data to arrays for sorting.
- `kiirTomb`, `kiirTombN`, `kiirTombK`, `kiirTombHF`: Functions to print sorted rankings.
- `potlasEllenorzes(Hallgato *head)`: Checks which students need to retake exams or assignments.
- `zhPotlasKiiras(Hallgato *head)`: Writes the list of students who need to retake exams to a file.
- `hfPotlasKiiras(Hallgato *head)`: Writes the list of students who need to retake assignments to a file.

### Main Program

The main program reads the student data from the input file, calculates the necessary scores, and then provides a menu for the user to interact with. The menu allows the user to:

1. Print the list of students.
2. Generate a list of students who need to retake exams.
3. Generate a list of students who need to retake assignments.
4. Display rankings based on different criteria.
5. Exit the program.

## Notes
- Ensure that the input file mintafajl2.txt is present in the same directory as the executable.
- The program dynamically allocates memory for student data and frees it at the end of the execution to prevent memory leaks.

> [!Warning]
> ## License
> This project is for educational purposes and is licensed under the AGPL-3.0 License.
