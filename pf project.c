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
	passenger.name[strcspn(passenger.name, "\n")] = 0;

	printf("Enter Flight Number: ");
	fgets(passenger.flight, sizeof(passenger.flight), stdin);
	passenger.flight[strcspn(passenger.flight, "\n")] = 0;

	printf("Enter Nationality: ");
	fgets(passenger.nationality, sizeof(passenger.nationality), stdin);
	passenger.nationality[strcspn(passenger.nationality, "\n")] = 0;

	printf("Enter Origin City: ");
	fgets(passenger.departure, sizeof(passenger.departure), stdin);
	passenger.departure[strcspn(passenger.departure, "\n")] = 0;

	printf("Enter Destination: ");
	fgets(passenger.arrival, sizeof(passenger.arrival), stdin);
	passenger.arrival[strcspn(passenger.arrival, "\n")] = 0;

	printf("Enter Seat Number: ");
	fgets(passenger.seat, sizeof(passenger.seat), stdin);
	passenger.seat[strcspn(passenger.seat, "\n")] = 0;

	File *fp = fopen(FILE_NAME, "ab");
	if (fp == Null) {
		perror("unable to open file for writing");
		return;
	}
	if (fwrite(&passenger, sizeof(Passenger), 1, fp)!= 1){
		perror("Error writing passenger recoed");
	}else{
		printf("passenger checked in successfully. Details saved to file.\n");

	}
	fclose(fp);

}
Passenger* getPassengerById(int id){
	FILE *fp =fopen(FILE_NAME, "rb");
	if(fp == NULL){
		perror("unable to open file for reading");
		return NULL;
	}

	Passenger *passenger = malloc(sizeof(passenger));
	if (passenger ==NULL){
		perror("Memory Aloocated failed");
		fclose(fp);
		return NULL;
	}

	while (fread(passenger, sizeof(Passenger), 1, fp))
	{
		if (passenger->id ==id)
		{
			fclode(fp);
			return passenger;

		}
		
	}
	fclose(fp);
	free(passenger);
	return NULL;
}

void generateBoardingPass() {
	int id;
	printf("\n--- Boarding Pass Generator ---\n");
	printf("Enter Passenger ID for boarding pass: ");
	scanf("%d", &id);
	getchar();


	Passenger *passengerPtr = getPassengerById(id);
	if (passengerPtr != NULL){
		printf("BOARDING PASS\n");
		printf("Passenger Id: %d\n", passengerPtr->id);
		printf("Name: %s\n", passengerPtr->name);
		printf("Flight No: %s\n", passengerPtr->flight);
		printf("Nationality: %s\n", passengerPtr->nationality);
		printf("Origin: %s\n", passengerPtr->departure);
		printf("Destination: %s\n", passengerPtr->arrival);
		printf("Seat: %s\n",passengerPtr->seat);
		free(passengerPtr);
	} else {
		printf("passenger with ID %d Not found.\n", id);
	}
	
	return 1;
}