﻿#define _CRT_SECURE_NO_WARNINGS
#include "structs.h"
#include "diralehaskir.h"
using namespace std;


//-------------print to file
void printToFile() {
	printLandlordToFile();//print all landlords
	printAdsToFile();//print all ads
	printTravelerToFile();//print all travelers
}

//-------------printLandlordToFile
void printLandlordToFile() {
	ofstream outFile;
	try {
		outFile.open("landlord.data");//open file in ios::out default mode
		if (!outFile)
			throw("couldn't open file");
	}
	catch (const char* const x) {
		cout << x << endl;
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if opening file succeeded
	outFile << landlord_arr_size << endl;//prints size of landlord array
	int i = 0;
	for (; i < landlord_arr_size; ++i) {
		outFile << landlord_arr[i].fullName << endl
			<< landlord_arr[i].phoneNumber << endl
			<< landlord_arr[i].password << endl
			<< landlord_arr[i].id << endl
			<< landlord_arr[i].email << endl
			<< landlord_arr[i].sumOfDeals << endl
			<< landlord_arr[i].adSize << endl;//num of ads for this landlord
	}
	outFile.close();//close file
}

//-------------printAdsToFile
void printAdsToFile() {
	ofstream outFile;
	try {
		outFile.open("properties.data");//open file in ios::out default mode
		if (!outFile)
			throw("couldn't open file");
	}
	catch (const char* const x) {
		cout << x << endl;
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if opening file succeeded
	outFile << numOfAds() << endl;//prints amount of all ads
	int i = 0;
	for (; i < landlord_arr_size; ++i) {
		for (int j = 0; j < landlord_arr[i].adSize; ++j) {
			outFile << landlord_arr[i].properties[j].available << endl
				<< landlord_arr[i].properties[j].description << endl
				<< landlord_arr[i].properties[j].price << endl
				<< landlord_arr[i].properties[j].discount << endl
				<< landlord_arr[i].properties[j].location << endl
				<< landlord_arr[i].properties[j].numOfPeople << endl
				<< landlord_arr[i].properties[j].numOfRooms << endl
				<< landlord_arr[i].properties[j].numOfBeds << endl;
			//print amenities
			outFile << landlord_arr[i].properties[j].ameNities.disabledAccess << endl
				<< landlord_arr[i].properties[j].ameNities.wifi << endl
				<< landlord_arr[i].properties[j].ameNities.kitchen << endl
				<< landlord_arr[i].properties[j].ameNities.tv << endl
				<< landlord_arr[i].properties[j].ameNities.balcony << endl
				<< landlord_arr[i].properties[j].ameNities.washingMachine << endl
				<< landlord_arr[i].properties[j].ameNities.airConditioning << endl
				<< landlord_arr[i].properties[j].ameNities.swimmingPool << endl
				<< landlord_arr[i].properties[j].ameNities.parkingLot << endl;
			//print rest
			outFile << landlord_arr[i].properties[j].attraction << endl
				<< landlord_arr[i].properties[j].rating << endl
				<< landlord_arr[i].properties[j].dateSize << endl;
			//print occupied dates
			for (int k = 0; k < landlord_arr[i].properties[j].dateSize; ++k) {
				outFile << landlord_arr[i].properties[j].occupied[k].fromDay << endl
					<< landlord_arr[i].properties[j].occupied[k].fromMonth << endl
					<< landlord_arr[i].properties[j].occupied[k].fromYear << endl
					<< landlord_arr[i].properties[j].occupied[k].toDay << endl
					<< landlord_arr[i].properties[j].occupied[k].toMonth << endl
					<< landlord_arr[i].properties[j].occupied[k].toYear << endl;
			}
		}
	}
	outFile.close();//close file
}

int numOfAds() {
	int sum = 0;
	for (int i = 0; i < landlord_arr_size; ++i)
		sum += landlord_arr[i].adSize;
	return sum;
}

//-------------printTravelerToFile
void printTravelerToFile() {
	ofstream outFile;
	try {
		outFile.open("traveler.data");//open file in ios::out default mode
		if (!outFile)
			throw("couldn't open file");
	}
	catch (const char* const x) {
		cout << x << endl;
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if opening file succeeded
	outFile << travelers_arr_size << endl;//prints size of landlord array
	int i = 0;
	for (; i < travelers_arr_size; ++i) {
		outFile << travelers_arr[i].fullName << endl
			<< travelers_arr[i].phoneNumber << endl
			<< travelers_arr[i].password << endl
			<< travelers_arr[i].order.fromDay << endl
			<< travelers_arr[i].order.fromMonth << endl
			<< travelers_arr[i].order.fromYear << endl
			<< travelers_arr[i].order.toDay << endl
			<< travelers_arr[i].order.toMonth << endl
			<< travelers_arr[i].order.toYear << endl;
	}
	outFile.close();//close file
}

//-------------read from file
void readFromFile() {
	//read all landlords
	readLandlordFromFile();//read all landlords
	//read all ads
	readAdsFromFile();//read all landlords
	//read all travelers
	readTravelerFromFile();
	//distribute ads to corresponding landlords
	splitAds();
}

//-------------readlandlordFromFile
void readLandlordFromFile() {//read all landlords
	ifstream inFile;
	try {
		inFile.open("landlord.data");//open in default mode
		if (!inFile)
			throw("can't open file");
	}
	catch (const char* const x) {
		cout << x << endl;
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if succeeded
	inFile >> landlord_arr_size;
	if (!landlord_arr_size)
		return;
	try {
		landlord_arr = new landlord[landlord_arr_size];
		if (!landlord_arr)
			throw("allocation failed in readFromFile-landlord");
	}
	catch (const char* const x) {
		cout << x << endl;
		inFile.close();
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if succeeded
	int i = 0;
	while (i < landlord_arr_size)
	{
		inFile.ignore();
		getline(inFile, landlord_arr[i].fullName);
		inFile >> landlord_arr[i].phoneNumber;
		inFile >> landlord_arr[i].password;
		inFile >> landlord_arr[i].id;
		inFile >> landlord_arr[i].email;
		inFile >> landlord_arr[i].sumOfDeals;
		inFile >> landlord_arr[i].adSize;
	}
	inFile.close();//close file
}

//-------------readAdsFromFile
void readAdsFromFile() {//read ads for landlord
	ifstream inFile;
	try {
		inFile.open("properties.data");//open file in ios::out default mode
		if (!inFile)
			throw("couldn't open file");
	}
	catch (const char* const x) {
		cout << x << endl;
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if opening file succeeded
	inFile >> ads_arr_size;
	if (!ads_arr_size)
		return;
	try {
		ads_arr = new ad[ads_arr_size];
		if (!ads_arr)
			throw("allocation failed in readFromFile-ads");
	}
	catch (const char* const x) {
		cout << x << endl;
		inFile.close();
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if succeeded

	int i = 0;
	for (; i < ads_arr_size; ++i) {
		inFile >> ads_arr[i].available;
		inFile.ignore();
		getline(inFile, ads_arr[i].description);
		inFile >> ads_arr[i].price;
		inFile >> ads_arr[i].discount;
		inFile.ignore();
		getline(inFile, ads_arr[i].location);
		inFile >> ads_arr[i].numOfPeople;
		inFile >> ads_arr[i].numOfRooms;
		inFile >> ads_arr[i].numOfBeds;
		//print amenities
		inFile >> ads_arr[i].ameNities.disabledAccess;
		inFile >> ads_arr[i].ameNities.wifi;
		inFile >> ads_arr[i].ameNities.kitchen;
		inFile >> ads_arr[i].ameNities.tv;
		inFile >> ads_arr[i].ameNities.balcony;
		inFile >> ads_arr[i].ameNities.washingMachine;
		inFile >> ads_arr[i].ameNities.airConditioning;
		inFile >> ads_arr[i].ameNities.swimmingPool;
		inFile >> ads_arr[i].ameNities.parkingLot;
		//read rest
		inFile.ignore();
		getline(inFile, ads_arr[i].attraction);
		inFile >> ads_arr[i].rating;
		inFile >> ads_arr[i].email;
		inFile >> ads_arr[i].dateSize;
		try {
			ads_arr[i].occupied = new date[ads_arr[i].dateSize];
			if (!ads_arr[i].occupied)
				throw("allocation failed in readFromFile-dates");
		}
		catch (const char* const x) {
			cout << x << endl;
			inFile.close();
			throw;
		}
		catch (...) {
			cout << "ERROR!" << endl;
			throw;
		}
		//read occupied dates
		for (int j = 0; j < ads_arr[i].dateSize; ++i) {
			inFile >> ads_arr[i].occupied[j].fromDay;
			inFile >> ads_arr[i].occupied[j].fromMonth;
			inFile >> ads_arr[i].occupied[j].fromYear;
			inFile >> ads_arr[i].occupied[j].toDay;
			inFile >> ads_arr[i].occupied[j].toMonth;
			inFile >> ads_arr[i].occupied[j].toYear;
		}
	}
	inFile.close();//close file
}

//-------------readTravelerFromFile
void readTravelerFromFile() {
	ifstream inFile;
	try {
		inFile.open("traveler.data");//open file in ios::out default mode
		if (!inFile)
			throw("couldn't open file");
	}
	catch (const char* const x) {
		cout << x << endl;
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if opening file succeeded
	inFile >> travelers_arr_size;//reads size of traveler array
	try {
		travelers_arr = new traveler[travelers_arr_size];
		if (!travelers_arr)
			throw("allocation failed in readFromFile-traveler");
	}
	catch (const char* const x) {
		cout << x << endl;
		inFile.close();
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if allocation succeeded
	int i = 0;
	for (; i < travelers_arr_size; ++i) {
		inFile.ignore();
		getline(inFile, travelers_arr[i].fullName);
		inFile >> travelers_arr[i].phoneNumber;
		inFile >> travelers_arr[i].password;
		inFile >> travelers_arr[i].order.fromDay;
		inFile >> travelers_arr[i].order.fromMonth;
		inFile >> travelers_arr[i].order.fromYear;
		inFile >> travelers_arr[i].order.toDay;
		inFile >> travelers_arr[i].order.toMonth;
		inFile >> travelers_arr[i].order.toYear;
	}
	inFile.close();//close file
}
void splitAds() {//assigns each landlord his ads
	allocateAdArrays();//allocates all landlords adArr and turns sizes to 0
	for (int i, k = 0; i < ads_arr_size; ++i) {
		for (int j = 0; j < landlord_arr_size; ++j) {
			k = landlord_arr[j].adSize;
			if (ads_arr[i].email == landlord_arr[j].email) {
				landlord_arr[j].properties[k] = ads_arr[i];
				++k;
			}
		}
	}
	delete[] ads_arr;//delete ad arr after distributing all ads to their landlords
	ads_arr_size = NOT_FOUND;
}

void allocateAdArrays() {//allocates all landlords adArr and turns sizes to 0
	for (int i = 0; i < landlord_arr_size; ++i) {
		try {
			landlord_arr[i].properties = new ad[landlord_arr[i].adSize];
			if (!landlord_arr[i].properties)
				throw("allocation failed in readFromFile-allocate ads array");
		}
		catch (const char* const x) {
			cout << x << endl;
			throw;
		}
		catch (...) {
			cout << "ERROR!" << endl;
			throw;
		}
		landlord_arr[i].adSize = 0;
	}
}
//-------------sort(display options in loop)
//------sort by low lo high*************************************************************
bool sortByLTH(ad* ad1, ad* ad2) {
	if (ad1->price - ad1->discount > ad2->price - ad2->discount)
		return true;
	return false;
}
//------sort by high to low*************************************************************
bool sortByHTL(ad* ad1, ad* ad2) {
	if (ad1->price - ad1->discount < ad2->price - ad2->discount)
		return true;
	return false;
}
//------sort by popularity(default)*****************************************************
bool sortByPopularity(ad* ad1, ad* ad2) {
	if (ad1->rating < ad2->rating)
		return true;
	return false;
}
// An optimized version of Bubble Sort**************************************************

void bubbleSort(int mode)
{
	int i, j;
	bool swapped;
	for (i = 0; i < ads_arr_size - 1; i++)
	{
		swapped = false;
		for (j = 0; j < ads_arr_size - i - 1; j++)
		{
			if (mode == 0) {//popularity(default)
				if (sortByPopularity(&ads_arr[j], &ads_arr[j + 1])) {
					swap(ads_arr[j], ads_arr[j + 1]);
					swapped = true;
				}
			}
			else if (mode == 1) {//low to high
				if (sortByLTH(&ads_arr[j], &ads_arr[j + 1])) {
					swap(ads_arr[j], ads_arr[j + 1]);
					swapped = true;
				}
			}
			else {//high to low
				if (sortByHTL(&ads_arr[j], &ads_arr[j + 1])) {
					swap(ads_arr[j], ads_arr[j + 1]);
					swapped = true;
				}
			}
		}
		// IF no two elements were swapped by inner loop, then break
		if (swapped == false)
			break;
	}
}

//------sort by dates***************************************************************

ad** sortAdsByDate(int& newSize, ad** adArr, int size, landlord* arr) {
	//get date
	date d = validDateInput();
	if (newSize == NOT_FOUND) {
		newSize = 0;
		//runs over landlors arr returns all ads available at the requested dates
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < arr[i].adSize; ++j) {
				for (int k = 0; k < arr[i].properties[j].dateSize; ++k) {
					//check if dates in ad are available
					if (isDateAvailable(d, arr[i].properties[j].occupied[k]))
						++newSize;//counts how many ads qualify
				}
			}
		}
		try {
			adArr = new ad * [newSize];
			if (!adArr)
				throw("allocation failed in sort ads by date");
		}
		catch (const char* const x) {
			cout << x << endl;
			throw;
		}
		catch (...) {
			cout << "ERROR!" << endl;
			throw;
		}
		//if allocation successfull
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < arr[i].adSize; ++j) {
				for (int k = 0; k < arr[i].properties[j].dateSize; ++k) {
					//check if dates in ad are available
					if (isDateAvailable(d, arr[i].properties[j].occupied[k]))
						adArr[i] = &(arr[i].properties[j]);//add ad to adArr if dates available
				}
			}
		}
	}
	else {
		int tempSize = 0;
		//run over existing adArr and return matching ads
		//runs over adArr returns all ads available at the requested dates
		for (int i = 0; i < newSize; ++i) {
			for (int j = 0; j < adArr[i]->dateSize; ++j) {
				//check if dates in ad are available
				if (isDateAvailable(d, adArr[i]->occupied[j]))
					++tempSize;//counts how many ads qualify
			}
		}
		if (!tempSize) {//found qualified ads in adArr
			int index = 0;
			for (int i = 0; i < newSize; ++i) {
				for (int j = 0; j < adArr[i]->dateSize; ++j) {
					//check if dates in ad are available
					if (isDateAvailable(d, adArr[i]->occupied[j])) {//if available
						adArr[i] = adArr[index];//enter to index's location in adArr
						++index;//inc index after assignment
					}
				}
			}
			newSize = tempSize;
		}
		else cout << "No ads with the previous filters match your description." << endl
			<< "Clear all filters and try again." << endl;
	}
	return adArr;//double pointer array of ads
}

//-------------filter(display options in loop)
void filterAds() {//***********************
	amenities filters = amenitiesCtor();//gets amenities from user
	if (ads_arr_size == NOT_FOUND) {
		ads_arr_size = 0;
		//runs over landlors arr returns all ads that has the requested filters
		cout << "please choose the filters you wish to apply" << endl;
		for (int i = 0; i < landlord_arr_size; ++i) {
			for (int j = 0; j < landlord_arr[i].adSize; ++j) {
				//check if amenities equal
				if (compareAmenities(filters, landlord_arr[i].properties[j].ameNities))
					++ads_arr_size;//counts how many ads qualify
			}
		}
		try {
			ads_arr = new ad[ads_arr_size];
			if (!ads_arr)
				throw("allocation failed in filter ads");
		}
		catch (const char* const x) {
			cout << x << endl;
			throw;
		}
		catch (...) {
			cout << "ERROR!" << endl;
			throw;
		}
		//if allocation successfull
		for (int i = 0; i < landlord_arr_size; ++i) {
			for (int j = 0; j < landlord_arr[i].adSize; ++j) {
				//check if amenities equal
				if (compareAmenities(filters, landlord_arr[i].properties[j].ameNities))
					ads_arr[i] = landlord_arr[i].properties[j];//add ad to adArr if filters are matching
			}
		}
	}
	else {
		int tempSize = 0;
		//run over existing adArr and return matching ads
		//runs over adArr returns all ads with matches
		for (int i = 0; i < ads_arr_size; ++i) {
			//check if amenities qualify
			if (compareAmenities(filters, ads_arr[i].ameNities))
				++tempSize;//counts how many ads qualify
		}
		if (!tempSize) {//found qualified ads in adArr
			int index = 0;
			for (int i = 0; i < ads_arr_size; ++i) {
				//check if amenities qualify
				if (compareAmenities(filters, ads_arr[i].ameNities)) {//if available
					ads_arr[i] = ads_arr[index];//enter to index's location in adArr
					++index;//inc index after assignment
				}
			}
			ads_arr_size = tempSize;
		}
		else cout << "No ads with the previous filters match your description." << endl
			<< "Clear all filters and try again." << endl;
	}
}

void travelerExplore(int& newSize, ad** adArr, int size, landlord* arr) {//**********************
	newSize = 0;
	//runs over landlors arr returns all ads that has the requested filters
	newSize = numOfAds();
	try {
		adArr = new ad * [newSize];
		if (!adArr)
			throw("allocation failed in traveler explore");
	}
	catch (const char* const x) {
		cout << x << endl;
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if allocation successfull
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < arr[i].adSize; ++j) {
			//check if amenities equal
			//if ()
			adArr[i] = &(arr[i].properties[j]);//add ad to adArr if filters are matching
		}
		for (int i, k = 0; i < size; ++i) {
			for (int j = 0; j < arr[i].adSize && k < newSize; ++j, ++k)
				adArr[k] = &(arr[i].properties[j]);//add ad to adArr if filters are matching
		}
	}
	printAndChooseFromAdArr(newSize, adArr);//prints all ads
}

bool compareAmenities(amenities& filters, amenities obj)//����� �����
{//true if has the filter amenities.
	//need to repair
	if (filters.airConditioning && !obj.airConditioning)
		return false;
	if (filters.balcony && !obj.balcony)
		return false;
	if (filters.disabledAccess && !obj.disabledAccess)
		return false;
	if (filters.kitchen && !obj.kitchen)
		return false;
	if (filters.parkingLot && !obj.parkingLot)
		return false;
	if (filters.swimmingPool && !obj.swimmingPool)
		return false;
	if (filters.tv && !obj.tv)
		return false;
	if (filters.washingMachine && !obj.washingMachine)
		return false;
	if (filters.wifi && !obj.wifi)
		return false;
	return true;
}
//-------------search*********************************************************************
ad** searchAds(int& newSize, ad** adArr, int size, landlord* arr) {
	cout << "please enter the required location:" << endl;
	string location = ValidLocation();//gets location from user
	if (newSize == NOT_FOUND) {
		newSize = 0;
		//runs over landlors arr returns all ads that has the requested filters
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < arr[i].adSize; ++j) {
				//check if amenities equal
				if (iequalsContain(arr[i].properties[j].location, location))//if equal/contains
					++newSize;//counts how many ads qualify
			}
		}
		try {
			adArr = new ad * [newSize];
			if (!adArr)
				throw("allocation failed in filter ads");
		}
		catch (const char* const x) {
			cout << x << endl;
			throw;
		}
		catch (...) {
			cout << "ERROR!" << endl;
			throw;
		}
		//if allocation successfull
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < arr[i].adSize; ++j) {
				//check if amenities equal
				if (iequalsContain(arr[i].properties[j].location, location))
					adArr[i] = &(arr[i].properties[j]);//add ad to adArr if locations are matching
			}
		}
	}
	else {
		int tempSize = 0;
		//run over existing adArr and return matching ads
		//runs over adArr returns all ads with sub string location
		for (int i = 0; i < newSize; ++i) {
			//check if ads qualify
			if (iequalsContain(adArr[i]->location, location))
				++tempSize;//counts how many ads qualify
		}
		if (!tempSize) {//found qualified ads in adArr
			int index = 0;
			for (int i = 0; i < newSize; ++i) {
				//check if ads qualify
				if (iequalsContain(adArr[i]->location, location)) {//if location is equal/contained
					adArr[i] = adArr[index];//enter to index's location in adArr
					++index;//inc index after assignment
				}
			}
			newSize = tempSize;
		}
		else cout << "No ads with the previous filters match your description." << endl
			<< "Clear all filters and try again." << endl;
	}

	return adArr;//double pointer array of ads
}

bool iequals(const string& a, const string& b)//compare strings, insenstive to lower/upper case
{
	unsigned int sz = a.size();
	if (b.size() != sz)
		return false;
	for (unsigned int i = 0; i < sz; ++i)
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	return true;
}
//-------------dates availability------------------------------------------------------ 
bool isDateAvailable(date d, const date& adDate)
{//doesn't check validity of dates, needs to happen prior

	//checkin= d.fromDate, checkout= d.toDate, beginning= adDate.fromDate, ending= adDate.toDate
	//(beginning >= checkin && checkout >= beginning)||(checkin >= beginning && ending >= checkin)
	if ((isDateBiggerE(adDate.fromDay, adDate.fromMonth, adDate.fromYear, d.fromDay, d.fromMonth, d.fromYear)
		&& isDateBiggerE(d.toDay, d.toMonth, d.toYear, adDate.fromDay, adDate.fromMonth, adDate.fromYear))
		|| (isDateBiggerE(d.fromDay, d.fromMonth, d.fromYear, adDate.fromDay, adDate.fromMonth, adDate.fromYear)
			&& isDateBiggerE(adDate.toDay, adDate.toMonth, adDate.toYear, d.fromDay, d.fromMonth, d.fromYear)))
		return false;
	return true;
}//checks if dated are overlapping, false if UNavailable

bool legalInput(int day, int month, int year, int mode) {//-------------------------------------------
	time_t t = time(ZERO);
	tm* now = localtime(&t);

	switch (month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (!mode) {
			return (ValidInput(day, MINinput, 31) &&
				isDateBiggerE(day, month, year, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900)
				&& ValidInput(year, CURRENT_YEAR, MAX_YEAR));
		}
		return (ValidInput(day, MINinput, 31) && ValidInput(year, CURRENT_YEAR, MAX_YEAR));
		break;
	case 2:
		if (!mode) {
			return (ValidInput(day, MINinput, isLeap(year) ? 29 : 28) &&
				isDateBiggerE(day, month, year, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900)
				&& ValidInput(year, CURRENT_YEAR, MAX_YEAR));
		}
		return (ValidInput(day, MINinput, isLeap(year) ? 29 : 28) && ValidInput(year, CURRENT_YEAR, MAX_YEAR));
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (!mode) {
			return (ValidInput(day, MINinput, 30) &&
				isDateBiggerE(day, month, year, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900)
				&& ValidInput(year, CURRENT_YEAR, MAX_YEAR));
		}
		return (ValidInput(day, MINinput, 30) && ValidInput(year, CURRENT_YEAR, MAX_YEAR));
		break;
	default:
		return false;
	}
	return false;
}
date validDateInput() {//----------------------------------------------------------------
	bool flag = true;
	bool valid = true;
	int d, m, y, dd, mm, yy;
	int confirm = 1;
	date dt;
	system("CLS");
	do {
		cout << "Enter values according to instructions." << endl;
		do {
			cout << "please enter date: " << endl;
			cout << "*************CHECK IN**************" << endl;

			//test if legal d/m/y
			cout << "Day (from " << MINinput << " to " << MAX_DAY << "): ";
			cin >> d;
			cout << endl << "Month (from " << MINinput << " to " << MAX_MONTH << "): ";
			cin >> m;
			cout << endl << "Year (from " << CURRENT_YEAR << " to " << MAX_YEAR << "): ";
			cin >> y;
			//bigger or equal to today
			valid = legalInput(d, m, y);
			if (valid)
				flag = false;
			else {
				cout << "invalid date, please try again." << endl;
			}
			cout << "***********************************" << endl;
		} while (flag);
		flag = true;
		dt.fromDay = d;
		dt.fromMonth = m;
		dt.fromYear = y;
		//same for check out
		do {
			cout << "please enter date: " << endl;
			cout << "************CHECK OUT**************" << endl;
			//test if legal d/m/y
			cout << "Day (from " << d << " to " << MAX_DAY << "): ";
			cin >> dd;
			cout << endl << "Month (from " << MINinput << " to " << MAX_MONTH << "): ";
			cin >> mm;
			cout << endl << "Year (from " << y << " to " << MAX_YEAR << "): ";
			cin >> yy;
			//bigger or equal to today
			valid = (legalInput(d, m, y, 1) && isDateBiggerE(dd, mm, yy, d, m, y));
			if (valid)
				flag = false;
			else {
				cout << "invalid date, please try again." << endl;
			}
			cout << "***********************************" << endl;
		} while (flag);
		flag = true;
		dt.toDay = dd;
		dt.toMonth = mm;
		dt.toYear = yy;
		printDate(dt);
		cout << "enter 0 to confirm dates, else to try again." << endl;
		cin >> confirm;
	} while (confirm);
	return dt;
}//returns date with valid input from user
void printDate(const date& t) {//---------------------------------------------------
	cout << "CHECK IN: ";
	cout << t.fromDay << "/" << t.fromMonth << "/" << t.fromYear << endl;
	cout << "CHECK OUT: ";
	cout << t.toDay << "/" << t.toMonth << "/" << t.toYear << endl;
}


void ReallococcupyDatesArr(ad* a)
{
	date* temp = new date[a->dateSize + 1];
	for (int i = 0; i < a->dateSize; i++) temp[i] = a->occupied[i];
	a->dateSize++;
	delete[] a->occupied;
	a->occupied = temp;
}

//-------------occupy dates
void occupyDates(date d, ad* a)
{
	ReallococcupyDatesArr(a);
	a->occupied[a->dateSize - 1] = d;
}


//-------------confirm credit card info
bool creditCardValidation(const string cardNumber, const string expirationMonth, const string expirationYear, const string cvv, const string ownerID)
{
	time_t t = time(0);
	tm* now = localtime(&t);

	if (!isStringAllDig(cardNumber) || cardNumber.length() != 16) return false;//check card number
	if (!isStringAllDig(expirationYear) || stoi(expirationYear) < (now->tm_year + 1900) || (stoi(expirationYear) + 1900) > 9999) return false;//check expiration year
	if ((stoi(expirationYear) == now->tm_year + 1900) && (!isStringAllDig(expirationMonth) || stoi(expirationMonth) < (now->tm_mon + 1) || stoi(expirationMonth) > 12)) return false;//check expiration month if expiration year is current year
	if (!isStringAllDig(expirationMonth) || stoi(expirationMonth) < 0 || stoi(expirationMonth) > 12) return false;//check expiration month otherwise
	if (!isStringAllDig(cvv) || cvv.length() != 3) return false;//check cvv
	if (!isStringAllDig(ownerID) || ownerID.length() != 9) return false;//check ID

	return true;//if nothing wrong was found
}

//-------------print deal confirmation(to screen)
void orderConfirmation(landlord* l, date* d)
{
	//generate random order number
	srand(time(NULL));
	int num = rand() % 100 + 1234;     // num in the range 1234 to 1334
	int total = difference_of_days(d->fromDay, d->fromMonth, d->fromYear, d->toDay, d->toMonth, d->toYear) * l->properties->price;
	cout << "Your order is complete!" << endl;
	cout << "Payment proccess has been successful" << endl;
	cout << "Order Number: " << num << endl;
	cout << "Dates From: " << d->fromDay << "/" << d->fromMonth << "/" << d->fromYear << " To:" << d->toDay << "/" << d->toMonth << "/" << d->toYear;
	cout << "Total price: " << difference_of_days(d->fromDay, d->fromMonth, d->fromYear, d->toDay, d->toMonth, d->toYear) * l->properties->price << "NIS" << endl;
	cout << "Total price: " << total << "NIS" << endl;
	cout << "Landlord Details:" << endl;
	cout << "NAME: " << l->fullName << endl;
	cout << "PHONE NUMBER: " << l->phoneNumber << endl;
	//call occupy dates
	//call sum of deals
}

//-------total rent sum

//-------------support(print only)
void printSupport()
{
	//generate random case number
	srand(time(NULL));
	int num = rand() % 100 + 2567;     // num in the range 2567 to 2667
	cout << "Your request has been sent!" << endl
		<< "Case number :" << num << endl
		<< "had been opened with your request for support" << endl;
}

//-------------faq(print only)
void printFaq()
{
	cout << "THE SOFTWARE IS NOT WORKING PROPERLY, HOW DO I FIX IT?" << endl
		<< "Please try using a different deviceand if there is no improvement try to reset your router." << endl << endl
		<< "IS THE SITE SECURE ?" << endl
		<< "Yes, the company uses a security company in order to secure all your personal information." << endl << endl
		<< "HOW DO I RATE MY STAY ?" << endl
		<< "At the end of rent time a rating screen will be available in which you can rate your stay." << endl;
}
//-------------travelers homepage
void travelerMenu(int trv_index)
{//NOT FINISHED*******
//NOTE- please change to switch/case!
	int newSize = NOT_FOUND;
	ad** adArr = NULL;
	bool support = false;//can't request support twice
	bool order = false;//if has one order can't order anymore
	int choice = 1;
	while (choice)
	{
		cout << "----WELCOME TRAVELER!----" << endl
			<< "Find the best place for your next vacation!" << endl
			<< "This is your basic menu-Please choose how you wish to proceed:" << endl
			<< "-------------------------------" << endl
			<< "1. Explore- displays all ads in default order." << endl
			<< "2. Enter specific dates to sort by." << endl
			<< "3. Search by location." << endl
			<< "4. Filter ads." << endl
			<< "5. Sort ads." << endl
			<< "6. Clear all my filters, searches and sorts." << endl
			<< "7. FAQ." << endl
			<< "8. Support." << endl
			<< "9. Rate." << endl
			<< "0. LOG OUT." << endl
			<< "-------------------------------" << endl;
		cout << "-> We recommend you first enter location and/or "
			<< "choose dates in order to maximize the filtering and sorting options." << endl;
		cout << "When printed the ads will be numbered and you could choose one and place," << endl
			<< "or you could return here and use different sorting options." << endl
			<< "-------------------------------" << endl
			<< "Please enter your choice:";
		cin >> choice;
		switch (choice)
		{
		case 1:
			deleteAdArr(adArr);
			adArr = NULL;
			newSize = -1;
			travelerExplore(newSize, adArr, landlord_arr_size, landlord_arr);
			int res = printAndChooseFromAdArr(newSize, adArr);
			// if (res != NOT_FOUND) //placeOrder()//then payment()//then orderConfirmation()
			break;
		case 2://sort by dates.
			if (!newSize) // no ads qualified previous filters
				cout << "No ads with the previous filters match your description." << endl
					<< "Clear all filters and try again." << endl;
			else adArr = sortAdsByDate(newSize, adArr, landlord_arr_size, landlord_arr);
			break;
		case 3://sort by location.
			if (!newSize) // no ads qualified previous filters
				cout << "No ads with the previous filters match your description." << endl
					<< "Clear all filters and try again." << endl;
			else adArr = searchAds(newSize, adArr, landlord_arr_size, landlord_arr);
			break;
		case 4://filter ads.
			
			break;
		case 5://sort ads.
			
			break;
		case 6://clear filters. 
			adArr = NULL;
			newSize = -1;
			break;
		case 7:

			break;
		case 8://Support.
			if (!support) 
			{
				printSupport();
				support = true;
			}
			else cout << "You can request support only once!" << endl;
			break;
		case 9://Rate.

			break;
		case 0://exit
			system("CLS");
			cout << "THANK YOU! Logging out..." << endl;
			break;
		}
	}
}
//-------------rate property(on last rent day)

//-------------calculate and update rates
void rateProperty(ad* a, traveler trav)
{
	time_t t = time(ZERO);
	tm* now = localtime(&t);//checks if date is right
	if (!isDateBiggerE(trav.order.toDay, trav.order.toMonth, trav.order.toYear, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900)) {
		cout << "Rating is available only from the last day of your stay..." << endl
			<< "We appreciate your opinion, try again when the time is right." << endl;
		return;
	}
	int temp;
	cout << "Welcome to the rating system!" << endl;
	do
	{
		cout << "Please rate the experience on a property by entering 1-5 " << endl
			<< "1 being the lowest and 5 the highest" << endl;
		cin >> temp;
	} while (temp < 1 || temp > 5);//updates ad rating
	a->rating = (a->rating + temp) / 2;
}

//-------------prints ad for traveler(to screen)
int printAndChooseFromAdArr(int newSize, ad** adArr) {//*********************************************
	//print for TRAVELER to choose from
	for (int i = 0; i < newSize; ++i) {
		cout << "\tNUMBER " << i + 1 << " :" << endl
			<< "**==============================**" << endl;
		cout << "Ad description: " << adArr[i]->description << endl;
		cout << "Price before discount: " << adArr[i]->price << endl;
		cout << "Price after discount:  " << adArr[i]->price - adArr[i]->discount << endl;
		cout << "Discount: " << "-" << adArr[i]->discount << "NIS" << endl;
		cout << "Location: " << adArr[i]->location << endl;
		cout << "Number of People: " << adArr[i]->numOfPeople << endl
			<< "Number of Rooms: " << adArr[i]->numOfRooms << endl
			<< "Number of Beds: " << adArr[i]->numOfBeds << endl;
		PrintAmenities(adArr[i]->ameNities);
		cout << "Atractions: " << adArr[i]->attraction << endl;
		cout << "Landlord Email: " << adArr[i]->email << endl;
		cout << "Rating: " << adArr[i]->rating << endl;
		cout << "**==============================**" << endl;
	}
	cout << "If you want to choose an ad and procced to order-" << endl
		<< "Please enter the number of the ad, if you wish to go back to menu press 0" << endl;
	cout << "enter your choice: ";
	int choice = 0;
	cin >> choice;
	if (!choice)
		return NOT_FOUND;//doesn't want to order yet
	return choice - 1;
}
//-------------3 funcs: isLeap, DaysCountFrom1900, DateDaysCount calculates the days from start date to end date.
bool isLeap(int Y)
{
	if (Y % 400 == 0) return true;
	else if (Y % 100 == 0) return false;
	else if (Y % 4 == 0) return true;
	else return false;
}
int DaysCountFrom1900(int year, int month, int day)
{
	int ans = 0;
	for (int i = 1900; i < year; ++i)
		if (isLeap(i))ans += 366;
		else ans += 365;
	for (int i = 1; i < month; ++i) {
		switch (i) {
		case 1: ans += 31; break;
		case 2: ans += isLeap(year) ? 29 : 28; break;
		case 3: ans += 31; break;
		case 4: ans += 30; break;
		case 5: ans += 31; break;
		case 6: ans += 30; break;
		case 7: ans += 31; break;
		case 8: ans += 31; break;
		case 9: ans += 30; break;
		case 10: ans += 31; break;
		case 11: ans += 30; break;
		case 12: ans += 31; break;
		}
	}
	return ans += day - 1;
}
int difference_of_days(int day1, int month1, int year1, int day2, int month2, int year2)
{
	return abs(DaysCountFrom1900(year1, month1, day1) - DaysCountFrom1900(year2, month2, day2));
}
//-------------total gainings for landlord
//-------------calculate the profit from an ad.
//-------------calculates landlords profit from all his ads.

//-------------Landlords menu : sub fuction- realloc the the ads array and adds 1 more ad.
//-------------landlord homescreen
//-------------Landlords menu : prints list of ads for landlord(to screen)


////***************also looped menus and instructions in each screen***************


//difference_of_days
bool isDateBiggerE(int d, int m, int y, int dd, int mm, int yy) {//--------------------------
	//gets two dates checks if the 1st is bigger or equal
	if (y == yy && m == mm && d == dd)
		return true;
	if (y > yy)
		return true;
	else if (y == yy) {
		if (m > mm)
			return true;
		else if (m == mm) {
			if (d > dd)
				return true;
		}
	}
	return false;//first date is not bigger or equal
}
string strToLower(string a) 
{	//converts entire string to lowerCase
	for (int i = 0; i < a.length(); ++i)
		a[i] = tolower(a[i]);
	return a;
}
bool iequalsContain(const string& a, const string& b)//*************************************
{//compare strings, insenstive to lower/upper case

	//a bigger
	//firstly check if equal
	if (iequals(a, b))
		return true;
	//else create new lowercase strings
	string a1, b1;
	a1 = strToLower(a);
	b1 = strToLower(b);
	//check if b1 is subtring of a1
	for (int i = 0; i < a1.length() && b1.length(); ++i)
		if (a1[i] != b1[i])
			return false;
	return true;
}
void swap(ad* ad1, ad* ad2)//***********************************************************
{
	//swap ads in adArr
	ad temp = *ad1;
	ad1 = ad2;
	*ad2 = temp;
}


//---------------------Checked and Work-------------------------
void deleteAllocatedData()
{
	for (int i = 0; i < landlord_arr_size; i++)
		delete[] landlord_arr[i].properties;//free each landlord's ad array
	delete[] landlord_arr;//free landlord array
	delete[] travelers_arr;//free traveler array
}
void deleteAdArr(ad** arr) {
	delete[] arr;
}
//Register:
void Register()
{
	system("CLS");
	int choise = 1;
	bool flag = true;
	cout << "***REGISTER - MENU***" << endl
		<< "1) Landlord." << endl
		<< "2) Traveler." << endl
		<< "3) Return to previous menu." << endl
		<< "Please enter your choice: ";
	cin >> choise;
	if (choise == 1)
	{
		RegisterLandlord();
		//update db
		system("CLS");
		cout << "Landlord successfuly added!" << endl;
	}
	else if (choise == 2)
	{
		RegisterTraveler();
		//update db
		system("CLS");
		cout << "Traveler added successfuly!" << endl;
	}
	else if (choise == 3) return;
	else cout << "Wrong choice!!" << endl;
}
traveler NewTraveler()
{
	traveler trv;
	trv.fullName = NameInput();
	trv.phoneNumber = PhoneInput();
	trv.password = PasswordInput();
	//cout << "NewTraveler: " << trv.fullName << endl;
	//cout << "NewTraveler: " << trv.phoneNumber << endl;
	//cout << "NewTraveler: " << trv.password << endl;;
	return trv;
}
void RegisterTraveler()
{
	RealloctravelersArr();
	travelers_arr[travelers_arr_size - 1] = NewTraveler();
	//cout <<endl<<"dd: "<< trv->password;
	//cout << travelersArr[size - 1].phoneNumber;
}
void RegisterLandlord()
{
	RegisterTraveler();
	landlord newLandlord;
	newLandlord.fullName = travelers_arr[travelers_arr_size - 1].fullName;
	newLandlord.phoneNumber = travelers_arr[travelers_arr_size - 1].phoneNumber;
	newLandlord.password = travelers_arr[travelers_arr_size - 1].password;
	newLandlord.id = ValidId();
	newLandlord.email = ValidEmail();
	newLandlord.sumOfDeals = 0;
	newLandlord.adSize = 0;
	ReallocLandlordsArr();
	landlord_arr[landlord_arr_size - 1] = newLandlord;
}
//Sing-in funcs:
int landlordSignIn() {//returns true if login successful
	string tempId, tempPass;
	cout << "***LANDLORD - LOG IN***" << endl << "Please enter details according to instructions" << endl;
	//get id input
	cout << "ID must be exactly " << MAX_ID << " digits, numbers only." << endl;
	cout << "Please enter your ID:" << endl;
	cin >> tempId;
	//check length and input correctness
	if (tempId.length() != MAX_ID) {
		cout << "No such ID..." << endl;
		return NOT_FOUND;
	}
	//find index for landlord in array by id- assuming no two identical id's
	int index = findLandlordById(tempId);
	if (index == NOT_FOUND) {//landlord not found
		cout << "No such ID..." << endl;
		return NOT_FOUND;
	}

	//get password
	cout << "Password must be minimum: " << MIN_PASSWORD
		<< " characters and maximum: " << MAX_PASSWORD << " characters," << endl
		<< "Can contain any characters you wish except 'enter'." << endl;
	cout << "Please enter your password:" << endl;
	cin >> tempPass;
	//check length and input correctness
	if (tempPass.length() > MAX_PASSWORD || tempPass.length() < MIN_PASSWORD) {
		cout << "Incorrect password...try again." << endl;
		return NOT_FOUND;
	}
	if (tempPass != landlord_arr[index].password) {//password equal
		cout << "Incorrect password...try again." << endl;
		return NOT_FOUND;
	}
	return index;
}
int findLandlordById(string id) {
	for (int i = 0; i < landlord_arr_size; ++i) {
		if (landlord_arr[i].id == id)//if equal
			return i;
	}
	return NOT_FOUND;
}
int travelerSignIn() {
	string tempName, tempPass;
	cout << "***TRAVELER - LOG IN***" << endl << "Please enter details according to instructions" << endl;
	//get name input
	cout << "Name must be up to: " << MAX_NAME << " letters only." << endl;
	cout << "Please enter your full name:" << endl;
	//cin >> tempName;
	cin.ignore();
	getline(cin, tempName);
	//check length and input correctness
	if (tempName.length() > MAX_NAME) {
		cout << "No such user..." << endl;
		return NOT_FOUND;
	}
	//find index for traveler in array by name- assuming no two identical names
	int index = findTravelerByName(tempName);
	if (index == NOT_FOUND) {//traveler not found
		cout << "No such user..." << endl;
		return NOT_FOUND;
	}

	//get password
	cout << "Password must be minimum: " << MIN_PASSWORD
		<< " characters and maximum: " << MAX_PASSWORD << " characters," << endl
		<< "Can contain any characters you wish except 'enter'." << endl;
	cout << "Please enter your password:" << endl;
	cin >> tempPass;
	//check length and input correctness
	if (tempPass.length() > MAX_PASSWORD || tempPass.length() < MIN_PASSWORD) {
		cout << "Incorrect password...try again." << endl;
		return NOT_FOUND;
	}
	if (tempPass != travelers_arr[index].password) {//password equal
		cout << "Incorrect password...try again." << endl;
		return not NOT_FOUND;
	}
	return index;
}
int findTravelerByName(string name)
{
	for (int i = 0; i < travelers_arr_size; ++i) {
		if (travelers_arr[i].fullName == name)//traveler found
			return i;
	}
	return NOT_FOUND;
}
//input validation:
bool isStringAllDig(string str) {//check id the string is all digits
	for (int i = 0; i < str.length(); ++i) {
		if (!isdigit(str[i]))//if false
			return false;
	}
	return true;
}
bool isStringAllLetters(string str)
{
	for (int i = 0; i < str.length(); ++i)
		if (!isalpha(str[i]) && str[i] != ' ')
			return false;
	return true;
}
string ValidLocation()
{
	//Location format <city>, <street> st.
	string location = "";
	string tmp;
	char answer;
	cout << "Please enter city: ";
	cin.ignore();
	getline(cin, tmp);
	location += tmp;
	cout << "Do you want to enter address?" << endl << "'y' for yes, else for no: ";
	cin >> answer;
	if (answer == 'y')
	{
		cout << "Please enter street name: ";
		cin.ignore();
		getline(cin, tmp);
		location += ", " + tmp + " st.";
	}
	else location += ".";
	return location;
}
int ValidInput(int min, int max)
{
	//gets int as input from user: (min <= USER_INPUT <= max)
	//if wrong gets another one and prints error message.
	int num;
	cin >> num;
	while (num < min || num >max)
	{
		cout << "Wrong number!\n Must be: " << min << " <= YOUR_NUMBER <= " << max << ": " << endl;
		cin >> num;
	}
	return num;
}
bool ValidInput(char truevaluechar)
{//returns true for 'truevaluechar' else return false.
	char tmp;
	cin >> tmp;
	if (tmp == truevaluechar) return true;
	else return false;
}
bool ValidInput(int num, int min, int max)//--------------------------------------------
{
	//gets int as input from user: (min <= USER_INPUT <= max)
	if (num < min || num >max) {
		cout << "Wrong input!\n Must be: " << min << " <= YOUR_INPUT <= " << max << ". " << endl;
		return false;
	}
	return true;
}
string NameInput()
{
	bool flag;
	string buffer;
	do {
		flag = false;
		cout << "Name must be up to  " << MAX_NAME << " letters only." << endl;
		cout << "Please enter your full name:";
		cin.ignore();
		getline(cin, buffer);
		if (!(buffer.length() <= MAX_NAME && buffer.length() > 0)) flag = true;
		if (!isStringAllLetters(buffer)) flag = true;
		if (flag) cout << "Incorrect input, try again." << endl;
	} while (flag);
	return buffer;
}
string PhoneInput()
{
	bool flag;
	string buffer;
	do {
		flag = false;
		cout << "Phone number must be exactly " << MAX_PHONE << " digits, no spaces, numbers only." << endl;
		cout << "Please enter your phone number:";
		getline(cin, buffer);
		if (buffer.length() != MAX_PHONE) flag = true;
		if (!isStringAllDig(buffer)) flag = true;
		if (flag) cout << "Incorrect length, try again." << endl;
	} while (flag);
	return buffer;
}
string PasswordInput()
{
	bool flag;
	string buffer;
	do {
		flag = false;
		cout << "Password can be minimum: " << MIN_PASSWORD
			<< " characters and maximum: " << MAX_PASSWORD << " characters," << endl
			<< "Can contain any characters you wish except 'enter'." << endl;
		cout << "Please enter your password:";
		getline(cin, buffer);
		//check length and input correctness
		if (buffer.length() < MIN_PASSWORD || buffer.length() > MAX_PASSWORD) flag = true;
		if (flag) cout << "Incorrect length, try again." << endl;
	} while (flag);
	return buffer;
}
string ValidId()
{
	string id;
	bool has_only_digits = false;
	while (!has_only_digits)
	{
		cout << "Please enter id(9 digits): ";
		cin >> id;
		has_only_digits = true;
		for (int i = 0; i < id.length(); i++)
			if (!isdigit(id[i])) has_only_digits = false;
		if (!has_only_digits) cout << "Wrong id! Please try again!" << endl;
	}
	return id;
}
string ValidEmail()
{
	/// gets a valid email form from user.
	string email;
	bool at = false, dot = false;
	while (!at || !dot)
	{
		at = false;
		dot = false;
		cout << "Please enter email: ";
		cin >> email;
		for (int i = 0; i < email.length(); i++)
		{
			if (email[i] == '@') at = true;
			if (at && email[i] == '.') dot = true;
		}
		if (!at || !dot) cout << "Wrong email! Please try again!" << endl;
	}
	return email;
}
amenities amenitiesCtor()
{//User input for each amenity.
	amenities obj;
	cout << "enter 'y' for yes, other for no" << endl;
	cout << AMENITIES_NAMES[0] << ": ";
	obj.disabledAccess = ValidInput('y');
	cout << AMENITIES_NAMES[1] << ": ";
	obj.wifi = ValidInput('y');
	cout << AMENITIES_NAMES[2] << ": ";
	obj.kitchen = ValidInput('y');
	cout << AMENITIES_NAMES[3] << ": ";
	obj.tv = ValidInput('y');
	cout << AMENITIES_NAMES[4] << ": ";
	obj.balcony = ValidInput('y');
	cout << AMENITIES_NAMES[5] << ": ";
	obj.washingMachine = ValidInput('y');
	cout << AMENITIES_NAMES[6] << ": ";
	obj.airConditioning = ValidInput('y');
	cout << AMENITIES_NAMES[7] << ": ";
	obj.swimmingPool = ValidInput('y');
	cout << AMENITIES_NAMES[8] << ": ";
	obj.parkingLot = ValidInput('y');
	return obj;
}
//Menus:
void MainPage()
{
	//system("CLS");
	int landlord_index = NOT_FOUND;
	int traveler_index = NOT_FOUND;
	int choise = 0;
	while (choise != 4)
	{
		cout << "***MAIN - MENU***:" << endl//need to be changed! add beutiful header.
			<< "1) Log in as traveler." << endl
			<< "2) Log in as landlord." << endl
			<< "3) Register." << endl
			<< "4) Exit." << endl
			<< "Please enter your choice:";
		cin >> choise;
		switch (choise)
		{
		case 1:
			traveler_index = travelerSignIn();
			break;
		case 2:
			landlord_index = landlordSignIn();
			traveler_index = findTravelerByName(travelers_arr[landlord_index].fullName);
			LandlordsLoginMenu(landlord_index, traveler_index);
			break;
		case 3:
			Register();
			break;
		case 4:
			cout << "Good bye!";
			//delete allocated memory.
			break;
		default:
			cout << "Wrong choice!!\nTry again: ";
			break;
		}

	}
}
void LandlordsLoginMenu(int ll_index, int trv_index)
{
	int choise = 1;
	while (choise != 3)
	{
		cout << "Please select user type:" << endl
			<< "1) Landlord." << endl
			<< "2) Traveler." << endl
			<< "3) Exit." << endl
			<< "Please enter your choice:" << endl;
		cin >> choise;
		switch (choise)
		{
		case 1:
			LandlordsMenu(ll_index);
			break;
		case 2:
			//TravelerMenu(trv_index);
			break;
		case 3:
			cout << "Good bye!";
			break;
		default:
			cout << "Wrong choice!!\nTry again: ";
			break;
		}

	}
}
void LandlordsMenu(int index)
{
	int choise = 1;
	int input;
	while (choise != 4)
	{
		system("CLS");
		cout << "***LANDLORD - MENU***" << endl;
		cout << "Total profit: " << landlord_arr[index].sumOfDeals << endl;
		if (landlord_arr[index].adSize)
			for (int i = 0; i < landlord_arr[index].adSize; i++)
			{
				cout << ADSBREAK << endl << "\tAd no: " << i + 1 << endl;
				PrintAd(landlord_arr[index].properties[i]);
			}
		cout << ADSBREAK << endl;

		cout << "Please select an option:" << endl
			<< "1) Edit an ad." << endl
			<< "2) Add new ad." << endl
			<< "3) Delete an ad." << endl
			<< "4) Exit." << endl
			<< "enter your choice: ";
		cin >> choise;
		switch (choise)
		{
		case 1:
			cout << "Please enter ad number: ";
			input = ValidInput(1, landlord_arr[index].adSize) - 1;
			EditAdMenu(index, input);
			//update db
			break;
		case 2:
			RealocateAdsPointer(index);
			landlord_arr[index].properties[landlord_arr[index].adSize - 1] = NewAd();
			landlord_arr[index].properties[landlord_arr[index].adSize - 1].email = landlord_arr[index].email;
			//update db
			break;
		case 3:
			cout << "Please enter ad number: ";
			input = ValidInput(1, landlord_arr[index].adSize) - 1;
			DeleteAd(index, input);
			//update db
			break;
		case 4:
			//exit
			system("CLS");
			cout << "Good bye!!" << endl;
			break;
		default:
			cout << "Wrong choice!!\nTry again!\n ";
			break;
		}
	}


}
void EditAdMenu(int ll_index, int ad_index)
{
	int choose = 1;
	while (choose)
	{
		system("CLS");
		cout << "EDIT AD MENU \nYour ad:" << endl;
		PrintAd(landlord_arr[ll_index].properties[ad_index]);
		cout << ADSBREAK << endl;
		cout << "What do you want to edit?" << endl;
		cout << "1) Change avilability (now: " << landlord_arr[ll_index].properties[ad_index].available << ")." << endl
			<< "2) Change Description." << endl
			<< "3) Change Price." << endl
			<< "4) Change Discount." << endl
			<< "5) Change num of people." << endl
			<< "6) Change num of rooms." << endl
			<< "7) Change num of beds." << endl
			<< "8) Edit amenities." << endl
			<< "9) Change attractions." << endl
			<< "0) Back to previous menu." << endl
			<< "Please enter your choice: ";
		cin >> choose;
		switch (choose)
		{
		case 1:
			landlord_arr[ll_index].properties[ad_index].available = !landlord_arr[ll_index].properties[ad_index].available;
			break;
		case 2:
			cout << "Enter new description:";
			cin.ignore();
			getline(cin, landlord_arr[ll_index].properties[ad_index].description);
			break;
		case 3:
			cout << "Enter new price: ";
			landlord_arr[ll_index].properties[ad_index].price = ValidInput(ZERO, INT_MAX);
			break;
		case 4:
			cout << "Enter new discount: ";
			landlord_arr[ll_index].properties[ad_index].discount = ValidInput(ZERO, landlord_arr[ll_index].properties[ad_index].price);
			break;
		case 5:
			cout << "Number of people(up to 30): ";
			landlord_arr[ll_index].properties[ad_index].numOfPeople = ValidInput(1, 30);
			break;
		case 6:
			cout << "Number of rooms(up to 15): ";
			landlord_arr[ll_index].properties[ad_index].numOfRooms = ValidInput(1, 15);
			break;
		case 7:
			cout << "Number of beds(up to 30): ";
			landlord_arr[ll_index].properties[ad_index].numOfBeds = ValidInput(1, 30);
			break;
		case 8:
			cout << "Select amenities: ";
			landlord_arr[ll_index].properties[ad_index].ameNities = amenitiesCtor();
			break;
		case 9:
			cout << "Enter a new attraction:";
			cin.ignore();
			getline(cin, landlord_arr[ll_index].properties[ad_index].attraction);
			break;
		case 0:
			return;
			break;
		default:
			cout << "You entered a wrong choice!!\n Try again: ";
			cin >> choose;
			break;
		}
	}
}
//Ads manipulations:
void DeleteAd(int landlord_index, int ad_index)
{
	//delete the ad at [index] location.
	if (!landlord_arr[landlord_index].adSize) cout << "No ads to delete!!!" << endl;
	else
	{
		ad* tmp = new ad[landlord_arr[landlord_index].adSize - 1];
		for (int i = 0, j = 0; i < landlord_arr[landlord_index].adSize - 1; j++, i++)
		{
			if (i == ad_index) j++;
			tmp[i] = landlord_arr[landlord_index].properties[j];
		}
		delete[] landlord_arr[landlord_index].properties;
		landlord_arr[landlord_index].properties = tmp;
		landlord_arr[landlord_index].adSize--;
	}

}
ad NewAd()
{//User input for new ad.
	ad newAd;
	newAd.available = true;
	cout << "New ad: " << endl;
	cout << "Ad description: ";
	cin.ignore();
	getline(cin, newAd.description);
	cout << "Price: ";
	newAd.price = ValidInput(ZERO, INT_MAX);
	cout << "Discount(0 ~ Price): ";
	newAd.discount = ValidInput(ZERO, newAd.price);
	newAd.location = ValidLocation();
	cout << "Number of people(up to 30): ";
	newAd.numOfPeople = ValidInput(1, 30);
	cout << "Number of rooms(up to 15): ";
	newAd.numOfRooms = ValidInput(1, 15);
	cout << "Number of beds(up to 30): ";
	newAd.numOfBeds = ValidInput(1, 30);
	cout << "Atraction: ";
	cin.ignore();
	getline(cin, newAd.attraction);
	cout << "Select amenities: ";
	newAd.ameNities = amenitiesCtor();
	newAd.rating = 5;
	return newAd;
}
//Realloc:
void RealloctravelersArr()
{
	travelers_arr_size++;
	traveler* tmp = new traveler[travelers_arr_size];
	if (!tmp) cout << "Memory allocation failed!" << endl;
	for (int i = 0; i < travelers_arr_size - 1; i++) tmp[i] = travelers_arr[i];
	if (travelers_arr) delete[] travelers_arr;
	travelers_arr = tmp;
}
void ReallocLandlordsArr()
{
	landlord_arr_size++;
	landlord* tmp = new landlord[landlord_arr_size];
	if (!tmp) cout << "Memory allocation failed!" << endl;
	for (int i = 0; i < landlord_arr_size - 1; i++) tmp[i] = landlord_arr[i];
	if (landlord_arr) delete[] landlord_arr;
	landlord_arr = tmp;
}
void RealocateAdsPointer(int landlord_index)
{
	//reallocates the pointer and changes the size:
	ad* tmp;
	tmp = new ad[landlord_arr[landlord_index].adSize + 1];
	for (int i = 0; i < landlord_arr[landlord_index].adSize; i++)
		tmp[i] = landlord_arr[landlord_index].properties[i];
	landlord_arr[landlord_index].adSize++;
	if (landlord_arr[landlord_index].properties) delete[] landlord_arr[landlord_index].properties;
	landlord_arr[landlord_index].properties = tmp;
}
//Output:
void PrintLandlordsAds(landlord ll)
{
	if (!ll.adSize)
	{
		cout << "No ads!" << endl;
		return;
	}
	for (int i = 0; i = ll.adSize; i++)
	{
		PrintAd(ll.properties[i]);
	}
	cout << ADSBREAK << endl;
}
void PrintAmenities(amenities obj)
{
	string str = "Amenities:";
	if (obj.disabledAccess) str += AMENITIES_NAMES[0] + ", ";
	if (obj.wifi) str += AMENITIES_NAMES[1] + ", ";
	if (obj.kitchen) str += AMENITIES_NAMES[2] + ", ";
	if (obj.tv) str += AMENITIES_NAMES[3] + ", ";
	if (obj.balcony) str += AMENITIES_NAMES[4] + ", ";
	if (obj.washingMachine) str += AMENITIES_NAMES[5] + ", ";
	if (obj.airConditioning) str += AMENITIES_NAMES[6] + ", ";
	if (obj.swimmingPool) str += AMENITIES_NAMES[7] + ", ";
	if (obj.parkingLot) str += AMENITIES_NAMES[8] + ", ";
	str[str.length() - 2] = '.';
	cout << str << endl;
}
void PrintAd(ad obj)
{
	cout << ADSBREAK << endl;
	cout << "Location: " << obj.location << endl;
	cout << "Ad description: " << obj.description << endl;
	cout << "Price before discount: " << obj.price << endl;
	cout << "Price after discount:  " << obj.price - obj.discount << endl;
	cout << "Discount: " << "-" << obj.discount << "NIS" << endl;
	cout << "Number of people: " << obj.numOfPeople << endl;
	cout << "Number of rooms: " << obj.numOfRooms << endl;
	cout << "Number of beds: " << obj.numOfBeds << endl;
	cout << "Atraction: " << obj.attraction << endl;
	PrintAmenities(obj.ameNities);
}

int main()
{
	readFromFile();//read from file.
	FilesCheck();
	MainPage();
	printToFile();//push to file.
}
















































void PrintTraveler(traveler trv)
{
	cout << ADSBREAK << endl;
	cout << "fullName: " << trv.fullName << "." << endl
		<< "phoneNumber: " << trv.phoneNumber << "." << endl
		<< "password: " << trv.password << "." << endl
		<< "order: ";
	printDate(trv.order);
	cout << ADSBREAK << endl;
}
void PrintLandlord(landlord ll)
{
	cout << ADSBREAK << endl;
	cout << "fullName: " << ll.fullName << "." << endl
		<< "phoneNumber: " << ll.phoneNumber << "." << endl
		<< "password: " << ll.password << "." << endl
		<< "id: " << ll.id << "." << endl
		<< "email: " << ll.email << "." << endl
		<< "sumOfDeals: " << ll.sumOfDeals << "." << endl
		<< "adSize: " << ll.adSize << "." << endl;
	for (int i = 0; i < ll.adSize; i++)
		PrintAd(ll.properties[i]);
	cout << ADSBREAK << endl;
}
void FilesCheck()
{
	cout << ADSBREAK << endl << "\tLandlords:" << endl << ADSBREAK << endl;
	for (int i = 0; i < landlord_arr_size; i++)
		PrintLandlord(landlord_arr[i]);
	cout << ADSBREAK << endl << "\tTravelers:" << endl << ADSBREAK << endl;
	for (int i = 0; i < travelers_arr_size; i++)
		PrintTraveler(travelers_arr[i]);
}

