#ifndef STRUCTS_H
#define STRUCTS_H
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;
typedef struct {
	bool disabledAccess,
		wifi,
		kitchen,
		tv,
		balcony,
		washingMachine,
		airConditioning,
		swimmingPool,
		parkingLot;
}amenities;

typedef struct {
	//start rent:
	int fromDay,
		fromMonth,
		fromYear,
		//end rent:
		toDay,
		toMonth,
		toYear;
}date;

typedef struct {
	bool available;
	string description;
	int price;
	int discount = 0;
	string location;
	int numOfPeople;
	int numOfRooms;
	int numOfBeds;
	amenities ameNities;
	string attraction;
	int rating;
	int dateSize = 0;
	date* occupied = NULL;//contains occupied dates
}ad;

typedef struct {
	string fullName;
	string phoneNumber;
	string password;
	string id;
	string email;
	int sumOfDeals;
	int adSize;
	ad* properties = NULL;
}landlord;



typedef struct {
	string fullName;
	string phoneNumber;
	string password;
	date order = { 0,0,0,0,0,0 };
}traveler;


#endif // !STRUCTS_H