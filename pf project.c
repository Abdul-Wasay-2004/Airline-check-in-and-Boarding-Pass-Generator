#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FILE_NAME "passengers.dat"

typedef struct 
{
int id;
char name[50];
char flight[20];
char nationality[50];
char departure[50];
char arrival[50];
char seat[10];
} Passenger;

void checkInPassenger();
void generateBoardingPass();
Passenger* getPassengerById(int id);

int main(){
	int choice;
	while (1)
	{
		printf("Airline Check-in & Boarding Pass Generator\n");
		printf("1. Passenger Check-in\n");
		printf("2. Generate Boarding Pass\n");
		printf("3. Exit\n");
		printf("Enter your choice: ");
		if (scanf("%d", &choice) != 1)
		{
			while (getchar() != '\n');
			printf("Invalid Input. Please enter a number.\n");
			continue;
		}
		getchar();

		switch (choice)
		{
		case 1:
			checkInPassenger()
			break;
		
		case 2:
		generateBoardingPass();
		break;

		case 3:
		printf("Exiting program\n");
		break;

		default:
		printf("invalid choice. Please try again.\n");
			break;
		}
		
	}
	return 0;

}
void checkInPassenger(){

	Passenger passenger;

	 printf("\n--- Passenger Check-in ---\n");
    printf("Enter Passenger ID: ");
    scanf("%d", &passenger.id);
    getchar();  

	printf("Enter Passenger Name: ");
	fgets(passenger.name, sizeof(passenger.name), stdin);
	passenger.name[strcspn]
}