//============================================================================
// Name        : MSKGown.cpp
// Author      : Willard Joseph
// Version     : 1.00
// Copyright   : JazMel 2017
// Description : A console application that will read a log entry. It would parse through the list
//				 and return the user with a print out for the monthly expense for lab members using
//				 the facility.
//============================================================================

// I will be turning many of these files into classes.
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

const string HospitalName = "Memorial Sloan Kettering Cancer Center";
const string FacilityName = "Cell Therapy and Cell Engineering Facility";
const string ProgramName = "MSKGown Version 1.00";
const string directorInfo =
		"Director: Isabelle Riviere, PhD.\nEmail: riviere@mskcc.org\nPhone: 212-639-7600.";
const string QAMangerInfo =
		"Quality Assurance Manager: Yongzeng Wang, PhD.\nEmail: wangy3@mskcc.org.\nExt. 122-3182";
const string FacilityManagerInfo =
		"cGMP Facility Manager: Brent Safford.\nEmail: saffordb@mskcc.org\nExt. 125-3678";
const double currentGownPrice = 29.42;

int totalEntries;
// This will be the total successful entries into the facility.
string currentMonth;
// User defined string holding the Month.

struct Group {
	string orgName;
	// Holds the name of the group using the CTCEF Facility.
	string orgABR;
	// Holds the Abbreviation for the group using the CTCEF Facility.
	int memberCount;
	// Holds the total number of members in the group.
	int memberEntry = 0;
	// Holds the number of entries for the month.
	double labExpense = memberEntry * currentGownPrice;
	// Holds the Monthly Expense for the group.
	string memberFileName;
	// Holds the Name of the Text File storing the group's members names

};

void MemberCount(Group& rhs);
// MemberCount will calculate the amount of Members in a current group;

void invoicePrint(Group& rhs, string& MonthFile);
// Will Print out an invoice for the Groups`

int main() {
	// Gene Therapy Facility Lab Information
	Group GTF;
	GTF.orgName = "Gene Therapy Facility";
	GTF.orgABR = "GTF";
	GTF.memberFileName = "GTF-Members.txt";
	// C:\\Users\\Willard Joseph\\Documents\\  The Location and Method of using a file in a different location

	// Center For Immune Cell Therapy Lab Information
	Group CICT;
	CICT.orgName = "Center For Immune Cell Therapy";
	CICT.orgABR = "CICT";
	CICT.memberFileName = "CICT-Members.txt";

	// Stem Cell Research Facility Lab Information
	Group STEM;
	STEM.orgName = "Stem Cell Research Facility";
	STEM.orgABR = "SCRF";
	STEM.memberFileName = "StemCell-Members.txt";

	// The James Young Lab Information
	Group YOUNG;
	YOUNG.orgName = "The James Young Lab";
	YOUNG.orgABR = "TJYL";
	YOUNG.memberFileName = "Young-Members.txt";


	cout << "*****Welcome To MSKGown*****" << endl;
	cout << ProgramName << endl; // prints Project Gown Version 1.0

	MemberCount(GTF);
	MemberCount(CICT);
	MemberCount(STEM);
	MemberCount(YOUNG);

	string file;

	cout << "Please follow all instructions." << endl;
	cout << "Please Enter The Month : (Allow Users to Enter Month) " << endl << "Month: ";
	cin >> currentMonth;
	cout << "Please Enter The Room Log's file name with its proper extension: (Allow Users to Enter File Name) " << endl << "FileName: ";
	cin >> file;



	// Temporary Place Holder
	invoicePrint(GTF, file);
	invoicePrint(CICT, file);
	invoicePrint(STEM, file);
	invoicePrint(YOUNG, file);

	cout << "Logs are located in the specified locations." << endl;

	return 0;
}

// Method Definitions Below
void MemberCount(Group& rhs) {
	ifstream memberLog; // the stream to read the members log file.

	string firstName, lastName;
	rhs.memberCount = 0;

// Add a check to make sure file opens up.
	memberLog.open(rhs.memberFileName.c_str());
	if (memberLog.fail()) {
		cout << rhs.orgName << " members File has not loaded properly." << endl;
		cout
				<< "Please ensure file is in proper location and it's name has not been altered."
				<< endl;

		cout << "Closing " << ProgramName << endl;
		exit(1);
	} else {
		while (memberLog >> firstName >> lastName) {

			rhs.memberCount += 1;
		}
	}
	//cout << rhs.orgName << " " << rhs.memberCount << endl;

	memberLog.close();

}

void invoicePrint(Group& rhs, string& MonthFile) {
	ifstream monthLog, memberLog;
// monthLog is the stream for the month txt file.
// memberLog is the stream for the Group member list.
	int totalEntries;
// Stores the total entries for the month being checked.
	string FirstName, LastName, FNameMLog, LNameMLog;
// FirstName holds the first Name from the Group Members List.
// LastName holds the last Name from the Group Memberes List.
// FNameMLog holds the first Name from the Month Log.
// LNameMLog holds the last Name from the Month Log.
	ofstream invoiceLog;
// The stream that creates the monthly log.

	time_t now = time(0);
	char* dt = ctime(&now);

	totalEntries = 0;

	monthLog.open(MonthFile.c_str());
	if (monthLog.fail()) {
		cout << MonthFile << " has not loaded properly or doesn't exist." << endl;
		cout << "Please email josephw@mskcc.org for troubleshooting instructions." << endl ;
		cout << "Closing " << ProgramName << endl;
		exit(1);
	} else {
		while (monthLog >> LNameMLog >> FNameMLog) {
			totalEntries += 1;
		}
	}
	monthLog.close();
	string extension = "C:\\Users\\Willard Joseph\\Computer Science\\C++ Language\\MSK Projects\\MSKGown\\Monthly Logs\\";
	string extension1 = currentMonth + rhs.orgABR;
	string newFile = extension + extension1 + ".doc";
	invoiceLog.open(newFile.c_str());

	invoiceLog << HospitalName << endl;
	invoiceLog << FacilityName << endl;
	invoiceLog << "\n" << endl;
	invoiceLog << "Invoice Date:\n" << dt << endl;
	invoiceLog << directorInfo << endl << endl;
//invoiceLog << QAMangerInfo << endl;
//invoiceLog << FacilityManagerInfo << endl;

	string invoiceTitle = currentMonth + " Gowning Invoice: " + rhs.orgName;

	int x = invoiceTitle.length();
	for (int i = 0; i < 120; i++) { // Centers invoiceTitle
		if (i < ((74 - x) / 2)) {
			invoiceLog << " ";
		} else if (i == ((74 - x) / 2)) {
			invoiceLog << invoiceTitle << endl;
		}
	}

	invoiceLog << "\n\n";
	invoiceLog << "Group Members" << setw(54) << "Facility Entries" << endl;

	memberLog.open(rhs.memberFileName.c_str());
	for (int i = 0; i < rhs.memberCount; i++) {
		int sum = 0;
		memberLog >> FirstName >> LastName;
		monthLog.open(MonthFile.c_str());
		for (int j = 0; j < totalEntries; j++) {
			monthLog >> LNameMLog >> FNameMLog;
			if (FirstName == FNameMLog && LastName == LNameMLog) {
				sum++;
				rhs.memberEntry++;
			}
		}
		monthLog.close();
		if (sum > 0) {
			string fullName = FirstName + " " + LastName;

			int nameLength = fullName.length();
			invoiceLog << fullName << setw(60 - nameLength) << sum << endl;
		}
	}
	memberLog.close();
	invoiceLog << endl << endl << endl << setw(60 - 3) << "Total Entries: "
			<< rhs.memberEntry << endl << endl;

	// Ensures that the price has 2 decimal digits.
	invoiceLog.setf(ios::fixed);
	invoiceLog.setf(ios::showpoint);
	invoiceLog.precision(2);

	invoiceLog << "Pricing for Full Gowning: $" << currentGownPrice << endl

			<< endl;
	invoiceLog << "The total cost for the month of " << currentMonth << " is $"
			<< rhs.memberEntry * currentGownPrice << endl;
	invoiceLog <<"\n\n\n\n";
			invoiceLog << "Approved by:______________________________" << endl << endl;
	invoiceLog <<"       Date:______________________________" << endl << endl;
	invoiceLog <<"  Signature:______________________________" << endl << endl;

	invoiceLog.close();

}
