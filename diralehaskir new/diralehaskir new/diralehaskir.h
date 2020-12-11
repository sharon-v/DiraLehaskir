#ifndef DIRALEHASKIR_H
#define DIRALEHASKIR_H
#include <iostream>
#include <stdlib.h>
//#include <cstdlib>
#include <stdio.h>
//#include <cstring>
#include <string>
//#include <string.h>
#include <fstream>
#include <ctime>
#include <ctype.h>

#define ADSBREAK "============================================================"
#define ZERO 0
#define MAX_EMAIL 8 //�� �������
#define GMAIL "@gmail.com"
#define WALLA "@walla.co.il"
#define MAX_ID 9
#define MAX_PHONE 10
#define MAX_NAME 15 //enough???
#define MAX_PASSWORD 10 //less???
#define MIN_PASSWORD 4
#define BUFFER 20
#define AMENITIES 9
#define NOT_FOUND -1
#define MINinput 1
#define MAX_DAY 31
#define MAX_MONTH 12
#define CURRENT_YEAR 2020
#define MAX_YEAR 2030

const string AMENITIES_NAMES[AMENITIES] = { "disabledAccess", "wifi", "kitchen", "tv", "balcony", "washingMachine", "airConditioning", "swimmingPool", "parkingLot" };


using namespace std;

void printToFile(int landlordSize, landlord* landlordArr, int travelerSize, traveler* travelerArr);
void printLandlordToFile(int size, landlord* landlordArr);
void printAdsToFile(int size, ad* adsArr);
void printTravelerToFile(int size, traveler* travelerArr);
void readFromFile(landlord* landlordArr, traveler* travelerArr);
void readLandlordFromFile(landlord* landlordArr);//read all landlord
void readAdsFromFile(int size, ad* adsArr);	//read ads for landlord
void readTravelerFromFile(traveler* travelerArr);
bool landlordSignIn(int size, landlord* landlordArr);
bool travelerSignIn(int size, traveler* travelerArr);
void travelerSignUp(traveler* travelerArr, int size);
void landlordSignUp(int size, landlord* landlordArr);
bool isStringAllDig(string str);//check id the string is all digits
int findLandlordById(int size, const landlord* const landlordArr, string id);
int findTravelerByName(int size, const traveler* const travelerArr, string name);
bool isStringAllLetters(string str);
int ValidInput(int min, int max);
bool ValidInput(char truevaluechar);
string ValidLocation();
amenities amenitiesCtor();
void EditAdMenu(ad* ad);
void PrintAd(ad obj);
void PrintAmenities(amenities obj);
int check_leap_year(int year);
int no_of_days_in_month(int month, int year);
int difference_of_days(int day1, int month1, int year1, int day2, int month2, int year2);
void deleteAllocatedData(int sizeL, landlord* landlordArr, int sizeT, traveler* travelerArr);
void deleteLandlordArr(int size, landlord* arr);
void deleteLandlordArr(int size, landlord* arr);
void deleteTravelerArr(int size, traveler* arr);
bool compareAmenities(amenities& filters, amenities obj);//true if equal
ad** filterAds(int size, landlord* arr);
bool iequals(const string& a, const string& b);//compare strings, insenstive to lower/upper case
bool ValidInput(int num, int min, int max);
bool isDateBiggerE(int d, int m, int y, int dd, int mm, int yy);
bool isDateAvailable(date d, const date& adDate);
bool legalInput(int day, int month, int year, int mode = 0);
date validDateInput();
void printDate(const date& t);


#endif // !DIRALEHASKIR_H