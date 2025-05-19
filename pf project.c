#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct passenger{
	int id;
	char name[50];
	char flight[10];
	char nationality[20];
	char departure[20];
	char arrival[20];
	char seat[10];
};

void checkInPassenger(void);
void generateBoardingPass(void);
struct passenger *getPassengerById(int id);

void checkInPassenger(void){
	struct passenger passenger;
	
	printf("\nPassenger Check-in\n");
    printf("Enter Passenger ID: ");
    scanf("%d",&passenger.id);
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

	printf("Enter Departure City: ");
	fgets(passenger.departure, sizeof(passenger.departure), stdin);
	passenger.departure[strcspn(passenger.departure, "\n")] = 0;

	printf("Enter Arrival City: ");
	fgets(passenger.arrival, sizeof(passenger.arrival), stdin);
	passenger.arrival[strcspn(passenger.arrival, "\n")] = 0;

	printf("Enter Seat Number: ");
	fgets(passenger.seat, sizeof(passenger.seat), stdin);
	passenger.seat[strcspn(passenger.seat, "\n")] = 0;

	FILE *fp=fopen("passengers.dat", "ab");
	if(fp==NULL){
		printf("Unable to open file for writing");
		return;
	}
	if(fwrite(&passenger, sizeof(struct passenger), 1, fp)!= 1){
		printf("Error writing passenger record");
	}
	else{
		printf("Passenger check-in successfull.\n");
	}
	fclose(fp);

}
struct passenger *getPassengerById(int id){
	FILE *fp=fopen("passengers.dat", "rb");
	if(fp==NULL){
		printf("Unable to open file for reading");
		return NULL;
	}
	
	struct passenger *passenger = malloc(sizeof(struct passenger));
	if(passenger==NULL){
		printf("Memory allocation failed");
		fclose(fp);
		return NULL;
	}

	while(fread(passenger, sizeof(struct passenger), 1, fp)==1){
		if((*passenger).id==id){
			fclose(fp);
			return passenger;
		}
	}
	fclose(fp);
	free(passenger);
	return NULL;
}

void generateBoardingPass(void){
	int id;
	printf("\nBoarding Pass Generator\n");
	printf("Enter Passenger ID for boarding pass: ");
	scanf("%d", &id);
	getchar();

	struct passenger *p = getPassengerById(id);
	if(p!=NULL){
		printf("\nBOARDING PASS\n");
		printf("Passenger Id: %d\n", (*p).id);
		printf("Name        : %s\n", (*p).name);
		printf("Flight No   : %s\n", (*p).flight);
		printf("Nationality : %s\n", (*p).nationality);
		printf("Departure   : %s\n", (*p).departure);
		printf("Arrival     : %s\n", (*p).arrival);
		printf("Seat        : %s\n", (*p).seat);
		
		char bpFileName[100];
        sprintf(bpFileName, "boarding_pass_%d.txt",(*p).id);
        FILE *bpFile=fopen(bpFileName, "w");
        if(bpFile==NULL){
            perror("Error creating boarding pass file");
        }
		else{
            fprintf(bpFile, "BOARDING PASS\n");
            fprintf(bpFile, "Passenger ID: %d\n", (*p).id);
            fprintf(bpFile, "Name        : %s\n", (*p).name);
            fprintf(bpFile, "Flight No   : %s\n", (*p).flight);
            fprintf(bpFile, "Nationality : %s\n", (*p).nationality);
            fprintf(bpFile, "Origin      : %s\n", (*p).departure);
            fprintf(bpFile, "Destination : %s\n", (*p).arrival);
            fprintf(bpFile, "Seat        : %s\n", (*p).seat);
            fclose(bpFile);
            printf("Boarding pass saved as %s\n", bpFileName);
        }
		
		free(p);
	}
	else{
		printf("Passenger not found\n", id);
    }
	
}

int main(){
	int choice;
	while(1){
		printf("\nAirline Check-in. Welcome\n");
		printf("1. Passenger Check-in\n");
		printf("2. Generate Boarding Pass\n");
		printf("3. Exit\n");
		printf("Enter your choice: ");
		if(scanf("%d", &choice) != 1){
			while(getchar()!='\n');
			printf("Invalid input. Please enter a number 1-3\n");
			continue;
		}
		getchar();

		switch(choice){
			case 1:
				checkInPassenger();
				break;
			case 2:
				generateBoardingPass();
				break;
			case 3:
				printf("Exiting Program\n");
				exit(0);
			default:
				printf("Invalid input. Please enter a number 1-3\n");
		}
	}
	return 0;
}
