
#include "utilities.h"
#include <list>
#include "stdlib.h"

using namespace std;

bool readFileIntoVector(ifstream &file, vector<studentData> &myData) {
	bool retValue = true;	//assume best

	std::string line;
	std::string token;
	studentData myStudentData;
	stringstream ss;
	const char CHAR_TO_SEARCH_FOR = ' ';

	while (!file.eof()) {
		getline(file, line); //get a line from the file Name, Midterm,Final
		ss.str(line);

		//get rid of the old values
		myStudentData.clear();

		//!!!!!! NO ERROR CHECK HERE DONT ASSUMME PERFECT DATA 		!!!!!!
		//!!!!!! if any of the following fail retValue should		!!!!!!
		//!!!!!! be set to false, break out of loop, then return;	!!!!!!

		//get the name
		getline(ss, myStudentData.name, CHAR_TO_SEARCH_FOR);

		//get midterm
		getline(ss, token, CHAR_TO_SEARCH_FOR);
		myStudentData.midterm = stringToInt(token.c_str());

		//get final
		getline(ss, token, CHAR_TO_SEARCH_FOR);
		myStudentData.final = stringToInt(token.c_str());

		//finally add to array
		myData.push_back(myStudentData);

		//clear stream so it will work for next read
		ss.clear();
	}
	return retValue;
}
void dontModifyReferenceORcopyVector(const vector<studentData> &myData){
	//if pass by value (no &) original vector will not be modified by
	//this function. But you have to copy it, potentially very expensive
	//If you pass as a const & then you get best of both worlds
	//compiler enforced gurantee that myData will not change and
	//you do not have to pay for the copy
}

void calculateFinalGrade(vector<studentData> &myData) {
	//using the [] way
	for (int var = 0; var < myData.size(); ++var) {
		myData[var].classgrade = 0.4 * myData[var].midterm 	+ 0.6 * myData[var].final;
	}

	//using [] way
	for ( int i = 0; i != myData.size()-1; ++i ){
		myData[i].classgrade = 0.4 * myData[i].midterm 	+ 0.6 * myData[i].final;
	}

	//iterator for list
	std::vector<studentData>::iterator itr;

	//using the iterator way
	//vector
	for ( itr = myData.begin(); itr != myData.end(); ++itr ){
		(*itr).classgrade = 0.4 * (*itr).midterm 	+ 0.6 * (*itr).final;
	}
}

  //void extractFailingStudents(vector<studentData> &allstudentData, list<studentData> &failstudentData){
  void extractFailingStudents(vector<studentData> &allstudentData, vector<studentData> &failstudentData){
	const double FAILGRADE = 60.0;

	//iterate over allstudentData
    //std::list<studentData>::iterator 	itr = allstudentData.begin();	//list
    std::vector<studentData>::iterator 	itr = allstudentData.begin();	//vector

	while (itr != allstudentData.end()){
		if ((*itr).classgrade<FAILGRADE){
			failstudentData.push_back(*itr);
			itr = allstudentData.erase(itr);	//erase returns updated iter pointing to next element
		}
		else
			++itr;
	}
}


ofstream myfile;
bool writeDataToFile(const string& outfilename, vector<studentData> &studentData) {
	myfile.open(outfilename.c_str());
	if (!myfile.is_open())
		return false;

//	TODO: sortArray();

	string mydata;
	for (int var = 0; var < studentData.size(); ++var) {
		mydata = studentData[var].name + "  " +
				DoubleToString(studentData[var].midterm) + "  " +
				DoubleToString(studentData[var].final) + "  " +
				DoubleToString(studentData[var].classgrade);
		myfile<<mydata<<std::endl;
	}

	if (myfile.is_open())
		myfile.close();

	return true;
}


//if you are debugging the file must be in the project parent directory
//in this case Project2 with the .project and .cProject files
std::string DoubleToString ( double Number ){
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}