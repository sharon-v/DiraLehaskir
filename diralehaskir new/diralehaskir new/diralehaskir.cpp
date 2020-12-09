#define _CRT_SECURE_NO_WARNINGS
#include "structs.h"
#include "diralehaskir.h"
//#include <datetimeapi.h>// or another maybe??? 
using namespace std;


//-------------print to file
void printToFile(int landlordSize, landlord* landlordArr, int travelerSize, traveler* travelerArr) {
	printLandlordToFile(landlordSize, landlordArr);//print all landlords
	printTravelerToFile(travelerSize, travelerArr);//print all travelers
}

//-------------printLandlordToFile
void printLandlordToFile(int size, landlord* landlordArr) {
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
	outFile << size << endl;//prints size of landlord array
	int i = 0;
	for (; i < size; ++i) {
		outFile << landlordArr[i].fullName << endl
			<< landlordArr[i].phoneNumber << endl
			<< landlordArr[i].password << endl
			<< landlordArr[i].id << endl
			<< landlordArr[i].email << endl
			<< landlordArr[i].sumOfDeals << endl
			<< landlordArr[i].adSize << endl;
		printAdsToFile(landlordArr[i].adSize, landlordArr[i].properties);//print ads for landlord
	}
	outFile.close();//close file
}
//-------------printAdsToFile
void printAdsToFile(int size, ad* adsArr) {
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
	outFile << size << endl;//prints size of landlord array
	int i = 0;
	for (; i < size; ++i) {
		outFile << adsArr[i].available << endl
			<< adsArr[i].description << endl
			<< adsArr[i].price << endl
			<< adsArr[i].discount << endl
			<< adsArr[i].location << endl
			<< adsArr[i].numOfPeople << endl
			<< adsArr[i].numOfRooms << endl
			<< adsArr[i].numOfBeds << endl;
		//print amenities
		outFile << adsArr[i].ameNities.disabledAccess << endl
			<< adsArr[i].ameNities.wifi << endl
			<< adsArr[i].ameNities.kitchen << endl
			<< adsArr[i].ameNities.tv << endl
			<< adsArr[i].ameNities.balcony << endl
			<< adsArr[i].ameNities.washingMachine << endl
			<< adsArr[i].ameNities.airConditioning << endl
			<< adsArr[i].ameNities.swimmingPool << endl
			<< adsArr[i].ameNities.parkingLot << endl;
		//print rest
		outFile << adsArr[i].attraction << endl
			<< adsArr[i].rating << endl
			<< adsArr[i].dateSize << endl;
		//print occupied dates
		for (int j = 0; j < adsArr[i].dateSize; ++i) {
			outFile << adsArr[i].occupied[j].fromDay << endl
				<< adsArr[i].occupied[j].fromMonth << endl
				<< adsArr[i].occupied[j].fromYear << endl
				<< adsArr[i].occupied[j].toDay << endl
				<< adsArr[i].occupied[j].toMonth << endl
				<< adsArr[i].occupied[j].toYear << endl;
		}
	}
	outFile.close();//close file
}

//-------------printTravelerToFile
void printTravelerToFile(int size, traveler* travelerArr) {
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
	outFile << size << endl;//prints size of landlord array
	int i = 0;
	for (; i < size; ++i) {
		outFile << travelerArr[i].fullName << endl
			<< travelerArr[i].phoneNumber << endl
			<< travelerArr[i].password << endl;
	}
	outFile.close();//close file
}

//-------------read from file
void readFromFile(landlord* landlordArr, traveler* travelerArr) {
	//read all landlords
	readLandlordFromFile(landlordArr);//read all landlords
	//read all travelers
	readTravelerFromFile(travelerArr);
}//return value???

 //-------------readlandlordFromFile
void readLandlordFromFile(landlord* landlordArr) {//read all landlord
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
	int arrSize = 0;
	inFile >> arrSize;
	if (!arrSize)
		return;
	try {
		landlordArr = new landlord[arrSize];
		if (!landlordArr)
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
	string a, b;
	while (i < arrSize)
	{
		inFile.ignore();
		getline(inFile, landlordArr[i].fullName);
		//inFile >> a >> b;
		//landlordArr[i].fullName = a + ' ' + b;
		inFile >> landlordArr[i].phoneNumber;
		inFile >> landlordArr[i].password;
		inFile >> landlordArr[i].id;
		inFile >> landlordArr[i].email;
		inFile >> landlordArr[i].sumOfDeals;
		inFile >> landlordArr[i].adSize;
		try {
			landlordArr[i].properties = new ad[landlordArr[i].adSize];
			if (!landlordArr)
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
		//call read ads
		readAdsFromFile(landlordArr[i].adSize, landlordArr[i].properties);//read ads for landlord
		++i;
	}
	inFile.close();//close file
}//return value???

 //-------------readAdsFromFile
void readAdsFromFile(int size, ad* adsArr) {//read ads for landlord
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
	int i = 0;
	for (; i < size; ++i) {
		inFile >> adsArr[i].available;
		inFile.ignore();
		getline(inFile, adsArr[i].description);
		inFile >> adsArr[i].price;
		inFile >> adsArr[i].discount;
		inFile.ignore();
		getline(inFile, adsArr[i].location);
		inFile >> adsArr[i].numOfPeople;
		inFile >> adsArr[i].numOfRooms;
		inFile >> adsArr[i].numOfBeds;
		//print amenities
		inFile >> adsArr[i].ameNities.disabledAccess;
		inFile >> adsArr[i].ameNities.wifi;
		inFile >> adsArr[i].ameNities.kitchen;
		inFile >> adsArr[i].ameNities.tv;
		inFile >> adsArr[i].ameNities.balcony;
		inFile >> adsArr[i].ameNities.washingMachine;
		inFile >> adsArr[i].ameNities.airConditioning;
		inFile >> adsArr[i].ameNities.swimmingPool;
		inFile >> adsArr[i].ameNities.parkingLot;
		//read rest
		inFile.ignore();
		getline(inFile, adsArr[i].attraction);
		inFile >> adsArr[i].rating;
		inFile >> adsArr[i].dateSize;
		try {
			adsArr[i].occupied = new date[adsArr[i].dateSize];
			if (!adsArr[i].occupied)
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
		//print occupied dates
		for (int j = 0; j < adsArr[i].dateSize; ++i) {
			inFile >> adsArr[i].occupied[j].fromDay;
			inFile >> adsArr[i].occupied[j].fromMonth;
			inFile >> adsArr[i].occupied[j].fromYear;
			inFile >> adsArr[i].occupied[j].toDay;
			inFile >> adsArr[i].occupied[j].toMonth;
			inFile >> adsArr[i].occupied[j].toYear;
		}
	}
	inFile.close();//close file
}
//-------------readTravelerFromFile
void readTravelerFromFile(traveler* travelerArr) {
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
	int size = 0;
	inFile >> size;//reads size of traveler array
	try {
		travelerArr = new traveler[size];
		if (!travelerArr)
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
	for (; i < size; ++i) {
		inFile.ignore();
		getline(inFile, travelerArr[i].fullName);
		inFile >> travelerArr[i].phoneNumber;
		inFile >> travelerArr[i].password;
	}
	inFile.close();//close file
}//return value???

 //-------------sign in
bool landlordSignIn(int size, landlord* landlordArr) {//returns true if login successful
	string tempId, tempPass;
	cout << "***LANDLORD - LOG IN***" << endl << "Please enter details according to instructions" << endl;
	//get id input
	cout << "ID must be exactly " << MAX_ID << " digits, numbers only." << endl;
	cout << "Please enter your ID:" << endl;
	cin >> tempId;
	//check length and input correctness
	if (tempId.length() != MAX_ID) {
		cout << "No such ID..." << endl;
		return false;
	}
	//find index for landlord in array by id- assuming no two identical id's
	int index = findLandlordById(size, landlordArr, tempId);
	if (index == NOT_FOUND) {//landlord not found
		cout << "No such ID..." << endl;
		return false;
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
		return false;
	}
	if (tempPass != landlordArr[index].password) {//password equal
		cout << "Incorrect password...try again." << endl;
		return false;
	}
	return true;
}

bool isStringAllDig(string str) {//check id the string is all digits
	for (int i = 0; i < str.length(); ++i) {
		if (!isdigit(str[i]))//if false
			return false;
	}
	return true;
}
//-------------find landlord by id
int findLandlordById(int size,const landlord* const landlordArr, string id) {
	int i = 0;
	for (; i < size; ++i) {
		if (landlordArr[i].id == id)//if equal
			return i;
	}
	return NOT_FOUND;
}

bool travelerSignIn(int size, traveler* travelerArr){
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
		return false;
	}
	//find index for traveler in array by name- assuming no two identical names
	int index = findTravelerByName(size, travelerArr, tempName);
	if (index == NOT_FOUND) {//traveler not found
		cout << "No such user..." << endl;
		return false;
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
		return false;
	}
	if (tempPass != travelerArr[index].password) {//password equal
		cout << "Incorrect password...try again." << endl;
		return false;
	}
	return true;
}

//-------------find traveler by full name
int findTravelerByName(int size, const traveler* const travelerArr, string name)
{
	int i = 0;
	for (; i < size; ++i) {
		if (travelerArr[i].fullName == name)//traveler found
			return i;
	}
	return NOT_FOUND;
}

//-------------sign up(after successful signup redirect to signin)-add new user to db
void landlordSignUp(int size, landlord* landlordArr) {
	//string fullName;
	//string phoneNumber;
	//string password;
	//string id;
	//string email;
	
	bool flag = true;
	landlord tempL;
	string buffer;
	cout << "***LANDLORD - SIGN UP***" << endl << "Please enter details according to instrctions" << endl;
	//get name input
	do {
		cout << "Name must be up to: " << MAX_NAME << " letters only." << endl;
		cout << "Please enter your full name:" << endl;
		cin.ignore();
		getline(cin, buffer);
		if (buffer.length() <= MAX_NAME && buffer.length() > 0) {
			if (isStringAllLetters(buffer))
				break;
			cout << "Incorrect input, try again." << endl;
		}
		cout << "Incorrect length, try again." << endl;
	} while (flag);
	tempL.fullName = buffer;
	
	//get phone number
	do {
		cout << "PhoneNumber must be exactly " << MAX_PHONE << " digits, no spaces, numbers only." << endl;
		cout << "Please enter your phoneNumber:" << endl;
		cin.ignore();
		getline(cin, buffer);
		//check length and input correctness
		if (buffer.length() == MAX_PHONE) {
			if (isStringAllDig(buffer))
				break;
			cout << "Incorrect input, try again." << endl;
		}
		cout << "Incorrect length, try again." << endl;
	} while (flag);
	tempL.phoneNumber = buffer;

	//get password
	do {
		cout << "Password can be minimum: " << MIN_PASSWORD
			<< " characters and maximum: " << MAX_PASSWORD << " characters," << endl
			<< "Can contain any characters you wish except 'enter'." << endl;
		cout << "Please enter your password:" << endl;
		cin.ignore();
		getline(cin, buffer);
		//check length and input correctness
		if (buffer.length() <= MAX_PASSWORD && buffer.length() >= MIN_PASSWORD) {
			break;
		}
		cout << "Incorrect length, try again." << endl;
	} while (flag);
	tempL.password = buffer;

	//get id
	do {
		cout << "PhoneNumber must be exactly " << MAX_ID << " digits, no spaces, numbers only." << endl;
		cout << "Please enter your phoneNumber:" << endl;
		cin.ignore();
		getline(cin, buffer);
		//check length and input correctness
		if (buffer.length() == MAX_ID) {
			if (isStringAllDig(buffer))
				break;
			cout << "Incorrect input, try again." << endl;
		}
		cout << "Incorrect length, try again." << endl;
	} while (flag);
	tempL.id = buffer;

	//get mail
	int choice = 0;
	do {
		cout << "Choose your mail type:" << endl
			<< "1. " << GMAIL << endl
			<< "2. " << WALLA << endl;
		cin >> choice;
		cout << "Your mail prefix can be maximum: " << MAX_EMAIL << " characters," << endl
			<< "Can contain any characters you wish except 'enter'." << endl;
		cout << "Please enter your email:" << endl;
		cin.ignore();
		getline(cin, buffer);
		//check length and input correctness
		if (buffer.length() <= MAX_EMAIL && buffer.length() > 0) {
			break;
		}
		cout << "Incorrect length, try again." << endl;
	} while (flag);
	if (choice == 1)
		tempL.email = buffer + GMAIL;
	else
		tempL.email = buffer + WALLA;

}//return value???

bool isStringAllLetters(string str) {
	for (int i = 0; i < str.length(); ++i) {
		if (!isalpha(str[i]))//if false
			return false;
	}
	return true;
}
void travelerSignUp(traveler* travelerArr, int size)
{
	//string fullName;
	//string phoneNumber;
	//string password;

	bool flag = true;
	traveler tempT;
	string buffer;
	cout << "***TRAVELER - SIGN UP***" << endl << "Please enter details according to instrctions" << endl;
	//get name input
	do {
		cout << "Name must be up to: " << MAX_NAME << " letters only." << endl;
		cout << "Please enter your full name:" << endl;
		cin.ignore();
		getline(cin, buffer);
		if (buffer.length() <= MAX_NAME && buffer.length() > 0) {
			if (isStringAllLetters(buffer))
				break;
			cout << "Incorrect input, try again." << endl;
		}
		cout << "Incorrect length, try again." << endl;
	} while (flag);
	tempT.fullName = buffer;

	//get phone number
	do {
		cout << "PhoneNumber must be exactly " << MAX_PHONE << " digits, no spaces, numbers only." << endl;
		cout << "Please enter your phoneNumber:" << endl;
		cin.ignore();
		getline(cin, buffer);
		//check length and input correctness
		if (buffer.length() == MAX_PHONE) {
			if (isStringAllDig(buffer))
				break;
			cout << "Incorrect input, try again." << endl;
		}
		cout << "Incorrect length, try again." << endl;
	} while (flag);
	tempT.phoneNumber = buffer;

	//get password
	do {
		cout << "Password can be minimum: " << MIN_PASSWORD
			<< " characters and maximum: " << MAX_PASSWORD << " characters," << endl
			<< "Can contain any characters you wish except 'enter'." << endl;
		cout << "Please enter your password:" << endl;
		cin.ignore();
		getline(cin, buffer);
		//check length and input correctness
		if (buffer.length() <= MAX_PASSWORD && buffer.length() >= MIN_PASSWORD) {
			break;
		}
		cout << "Incorrect length, try again." << endl;
	} while (flag);
	tempT.password = buffer;
}


string ValidLocation()
{
	//Location format <city>, <street> st.
	string location = "";
	string tmp;
	cout << "Please enter city: ";
	cin.ignore();
	getline(cin, tmp);
	location += tmp + ", ";
	cout << "Please enter street name: ";
	cin.ignore();
	getline(cin, tmp);
	location += tmp + " st.";
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
ad NewAd()
{//User input for new ad.
	ad newAd;
	newAd.available = true;
	cout << "New ad: " << endl;
	cout << "Ad discription: ";
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
	cout << "Atractions: ";
	cin.ignore();
	getline(cin, newAd.attraction);
	cout << "Select amenities: ";
	newAd.ameNities = amenitiesCtor();
	newAd.rating = 0;
	return newAd;
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
	cout << "Ad discription: " << obj.description << endl;
	cout << "Price before discount: " << obj.price << endl;
	cout << "Price after discount:  " << obj.price - obj.discount << endl;
	cout << "Discount: " << "-" << obj.discount << "$" << endl;
	cout << "Number of people: " << obj.numOfPeople << "\trooms: " << obj.numOfRooms << "\tbeds: " << obj.numOfBeds << endl;
	cout << "Atractions: " << obj.attraction << endl;
	PrintAmenities(obj.ameNities);
}
void EditAdMenu(ad* ad)
{
	int choose = 1;
	while (choose)
	{
		system("CLS");
		cout << "Edit ad menu.\nYour ad:" << endl;
		PrintAd(*ad);
		cout << ADSBREAK << endl;
		cout << "What you want to edit?" << endl;
		cout << "1)Change avilability (now: " << ad->available << ")." << endl
			<< "2)Change Discription." << endl
			<< "3)Change Price." << endl
			<< "4)Change Discount." << endl
			<< "5)Change num of people." << endl
			<< "6)Change num of rooms." << endl
			<< "7)Change num of beds." << endl
			<< "8)Edit amenities." << endl
			<< "9)Change attractions." << endl
			<< "0)Back to previous menu." << endl
			<< "Please enter your choise: ";
		cin >> choose;
		switch (choose)
		{
		case 1:
			ad->available = !ad->available;
			break;
		case 2:
			cout << "Enter new discription:";
			cin.ignore();
			getline(cin, ad->description);
			break;
		case 3:
			cout << "Enter new price: ";
			ad->price = ValidInput(ZERO, INT_MAX);
			break;
		case 4:
			cout << "Enter new discount: ";
			ad->discount = ValidInput(ZERO, 100);
			break;
		case 5:
			cout << "People amount(up to 30): ";
			ad->numOfPeople = ValidInput(1, 30);
			break;
		case 6:
			cout << "Amount of rooms(up to 15): ";
			ad->numOfRooms = ValidInput(1, 15);
			break;
		case 7:
			cout << "Number of beds(up to 30): ";
			ad->numOfBeds = ValidInput(1, 30);
			break;
		case 8:
			cout << "Select amenities: ";
			ad->ameNities = amenitiesCtor();
			break;
		case 9:
			cout << "Enter new attractions:";
			cin.ignore();
			getline(cin, ad->attraction);
			break;
		case 0:
			return;
			break;
		default:
			cout << "You entered wrong choise!!\n Try again: ";
			cin >> choose;
			break;
		}
	}
}



//-------------sort(display options in loop)

//-------------filter(display options in loop)

//-------------search

//-------------dates availability

//-------------occupy dates

//-------------confirm credit card info

//-------------total rent sum

//-------------support(print only)
void printSupport()
{
	cout<< "Your request has been sent!"<<endl
		<<"Case number :"<<'1234'<<endl
		<<"had been opened with your request for support"<<endl;
}

//-------------faq(print only)
void printFaq()
{
	cout << "THE SOFTWARE IS NOT WORKING PROPERLY, HOW DO I FIX IT?" << endl
		<< "Please try using a different deviceand if there is no improvement try to reset your router." << endl
		<< "IS THE SITE SECURE ?" << endl
		<< "Yes, the payment is secured by the payment platform you will use." << endl
		<< "HOW DO I RATE MY STAY ?" << endl
		<< "At the end of rent time a rating screen will be displayed in which you can rate your stay." << endl;
}
//-------------travelers homepage

//-------------landlord menu

//-------------landlord homescreen

//-------------new ad

//-------------edit ad

//-------------delete ad

//-------------total gainings for landlord

//-------------rate property(on last rent day)

//-------------calculate and update rates

//-------------prints ad for traveler(to screen)

//-------------prints list of ads for landlord(to screen)- also print ad for landlord???

//-------------print deal confirmation(to screen)

////***************also looped menus and instructions in each screen***************

//-------------delete all allocated data

int main() {
	landlord* arr = NULL;
	readLandlordFromFile(arr);
	return 0;
}