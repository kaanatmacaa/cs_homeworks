#include <iostream>
#include <string>
#include <fstream>  // to read input files 
#include <vector>   // to create matrixs

//Kaan ATMACA's program

using namespace std; 

void createMatrix(ifstream & in, vector<vector<string> > &matrix) { //creates matrix for board
	string s; //will get cin words
	int n; // integer n which tells how many rows there are
	int count = 0; //this will count number of values except the empty lines
	
	in >> n; 
	vector<string> row; 

	while(!in.eof()) {	 //counting lines
		in >> s;
		count++; 
	}

	in.clear(); 
	in.seekg(0);
	in >>n;

	int countOfMatrixColumns = (count/n); //calculating how much columns there are

	while(!in.eof()) {
		for(int i =0; i < n ; i++){ //for loop for entering words into empty row vector
			row.clear();
			for(int j =0; j < countOfMatrixColumns ; j++){
				in >> s; 
				row.push_back(s); 
			}
			matrix.push_back(row); 
			if(in.eof())
				break;
		}
	}
	matrix.pop_back() ; //pops last useless row ASK POPBACK ASK ASK ASK ASK

	in.clear(); 
	in.seekg(0); // so that we can read file again if needed
}

bool checkNumOfLinesBoard(ifstream & in){ //checking if lines of board are correct with the given integer n
	int n, numOfLines=0; //n gets first integer on file which tells num of lines 
	string s; //s will be used in getline 
	in >> n ; 
	while(getline(in, s)) { 
		if (s!= "")
		numOfLines++;
	}

	in.clear();
	in.seekg(0);  //so that the file could be read again

	if (numOfLines == n) {
		return true; 
	}
	else if(numOfLines > n) {
		cout << "File contains more lines than size" << endl;
		return false;
	}
	else {
		cout << "File contains less lines than size" << endl;
		return false;
	}	
}

bool checkValuesOfBoard(ifstream & in) { //checking values of board 
	vector<string> integers; //this will get each integer value
	string s; // gets each 
	int n;
	in >> n ; //so we learn how many lines there will be n+1 = numoflines
	
	while(in >> s){ //puting all ints into one vector no x's
		if( s != "X") 
		integers.push_back(s);
	}

	in.clear();
	in.seekg(0); //so that file can be read later

	int len = integers.size(); 
	int num; 
	for(int i =0 ; i < len ; i++) {
		num = stoi(integers[i]);  //converting all string numbers into int with stoi 
		if ( !(0 < num && num < n+1)) { //checking the value of the int 
			cout << "Value " << num << " is out of the matrix size" << endl;
			return false; 
		}
	}
	return true;
}

bool checkRowsOfBoard(vector<vector<string> > &matrix){ //this function checks rows in boardMatrix and if they have same num return false
	vector<string> row;  //will get rows seperately
	string integersOfRow = ""; 
	int len = matrix.size(); 
	int lenOfRow; 

	for(int i = 0; i < len ; i++) {  //for each row
		integersOfRow = "";
		row = matrix[i]; //row gets values vector
		lenOfRow = row.size(); 

		for(int j =0 ; j < lenOfRow; j++){ //there may be xs in row so we elimanete them 
			if (row[j] != "X") {
				integersOfRow += row[j] + " " ; 
			}
		}
		for(int j = 0; j < lenOfRow; j++) {
			if( integersOfRow.find(row[j]) != integersOfRow.rfind(row[j])) { //uses find and rfind so if there are two same nums the finds will give different ints
				cout << "There is a value repeating in same row" << endl;
				return false; 
			}		
		}
	}
	return true;
}

bool checkColumnsOfBoard(vector<vector<string> > &matrix){ //first transpose x-y and then use the same algorithm on function checkRowsOfBoard
	/////////////////////until next comment matrix is being transposed x and ys to transposedmatrix

	int lenX = matrix.size(); 
	int lenY = matrix[1].size();
	vector<vector<string> > transposedMatrix = matrix; 
	for(int i=0; i < lenX; i++){
		for(int j =0; j < lenX ; j++){
			transposedMatrix[j][i] = matrix[i][j]; 
		}
	}
	////////matrix is transposed
	///////now we will use the same function checkRowsOfBoard
	/////// the only difference will be on cout

	vector<string> row;  //will get rows seperately
	string integersOfRow = ""; 
	int len = transposedMatrix.size(); 
	int lenOfRow; 
	for(int i = 0; i < len ; i++) { 

		integersOfRow = "";
		row = transposedMatrix[i]; //row gets values vector
		lenOfRow = row.size(); 

		for(int j =0 ; j < lenOfRow; j++){ //there may be xs in row so we elimanete them 
			if (row[j] != "X") {
				integersOfRow += row[j] + " " ; 
			}
		}
		for(int j = 0; j < lenOfRow; j++) {
			if( integersOfRow.find(row[j]) != integersOfRow.rfind(row[j])) {
				cout << "There is a value repeating in same column" << endl;
				return false; 
			}		
		}
	}
	return true;
	


}

bool checkNumOfLinesConst(ifstream & in) { //checks num of row in Const if not correct return false

	int n, numOfLines=0; //n gets first integer on const which tells num of lines 
	string s; //s will be used in getline 
	in >> n ; 
	while(getline(in, s)) {
		if(s!="")
		numOfLines++;
	}

	in.clear();
	in.seekg(0);  //so that the file could be read again

	if (numOfLines == n) {
		return true; 
	}
	else if(numOfLines > n) {
		cout << "There are more constraints then previously stated" << endl;
		return false;
	}
	else {
		cout << "There are less constraints then previously stated" << endl;
		return false;
	}	
}

vector<vector<int> > changeValueOfX(vector<vector<string> > &matrix){ //create new matrix board where all are int also x become 0 
	int lenX = matrix.size();
	int lenY = matrix[0].size();
	vector<vector<int> > myMatrix(lenX, vector<int>(lenY)); //new vector created with rowsize lenx and column size leny

	for(int i = 0; i <lenX; i++){
		for (int j = 0; j < lenY ; j++){
			if (matrix[i][j] == "X"){
				myMatrix[i][j] = 0; 
			}
			else {
				myMatrix[i][j] = stoi(matrix[i][j]);
			}
		}
	}
	return myMatrix; //new vector is returned 
}

bool checkXexist(vector<vector<int> > &matrix){ //checks if the matrix contains any zeros(0) which are in the places of X's 
	//if 0 found returns true
	int lenX = matrix.size();
	int lenY = matrix[0].size();

	for(int i = 0; i <lenX; i++){
		for (int j = 0; j < lenY ; j++){
			if ( matrix[i][j] == 0){
				return true; 
			}
		}
	}
	return false;
}

bool boardAndConstPair(vector<vector<int> > &boardMatrix, vector<vector<int> > &constMatrix){ //trying to find only value of 0(X) if found return true
	//newBoardMatrix and newConstMatrix are used to compare
	//uses the fact of boardMatrixs x1y1 > x2y2

	int lenOfConstantX = constMatrix.size(); 
	int lenOfConstantY = constMatrix[0].size();

	int min, max;
	int lenOfBoard = boardMatrix.size(); 
	vector<int> valuesForX; //vector to pushback values which 0 can get

	int x1,y1, x2,y2; //coordinates for constMatrix -> X1 Y1 X2 Y2 each row is like this in const matrix

	for(int i =0; i <lenOfConstantX; i++){
		valuesForX.clear();

		x1 = constMatrix[i][0];
		y1 = constMatrix[i][1]; 
		x2 = constMatrix[i][2];
		y2 = constMatrix[i][3]; 

		if(boardMatrix[x1][y1] == 0){
			min = boardMatrix[x2][y2]; //if x1y1 is x then the value of board matrix must be bigger then board[x2][y2]
			for(int j =min+1; j < lenOfBoard+1 ; j++){ //loop to enter all posible values for x
				valuesForX.push_back(j); 
			}
			if(valuesForX.size() == 1) { //if only one value give the correct value to X and return true
				boardMatrix[x1][y1] = valuesForX[0]; 
				return true; 
			}
		}

		else if(boardMatrix[x2][y2] == 0){
			max = boardMatrix[x1][y1]; //if x2y2 is x then the value of board matrix must be smaller then board[x1][y1]
			for(int j =0; j < max; j++){//loop to enter all posible values for x
				valuesForX.push_back(j);
			}
			if(valuesForX.size() == 1){//if only one value give the correct value to X and return true
				boardMatrix[x2][y2] = valuesForX[0]; 
				return true; 
			}
		}
	}
	return false; 
}

bool insertingValues(vector<vector<int> > &matrix, vector<vector<int> > &constMatrix){ //functions tries to insert all values for 0(X) if cant do it return false
	
	bool check =  checkXexist(matrix); //true if X exists
	int lenX = matrix.size() ; 
	int lenY = matrix[0].size(); 
	int totalInRorC=0; //the must total sum in a row or column
	bool checkCandBoardPair; 

	for(int i =0; i < lenX;i++){//to calculate the total of what a row should have
		totalInRorC += (i+1); 
	}
	int count;
	int totalRow;
	int index; 
	bool checkIfEntered = false; //if this bool stays false until end of while loop X can have more then one values
	while (check) {
		checkIfEntered= false;

		//first check rows if 1 x in row then place its value 
		for (int i =0; i < lenX; i++){
			count = 0; 
			totalRow=0;
			for(int j = 0; j < lenY; j++){
				totalRow += matrix[i][j]; 
				if(matrix[i][j] == 0) {
					count++;
					index = j;
				}
			}
			if (count == 1) {
				checkIfEntered = true; 
				matrix[i][index] = (totalInRorC-totalRow) ; 
			}
		}

		if (false == checkXexist(matrix))
			break;

		//second part check columns if x alone in column place its value
		for (int i =0; i < lenY; i++){
			count = 0; 
			totalRow =0 ;
			for(int j =0; j <lenX; j++){
				totalRow += matrix[j][i];
				if(matrix[j][i] == 0) {
					count++;
					index = j ;
				}
			}
			if(count == 1) {
				checkIfEntered = true; 
				matrix[index][i] =  (totalInRorC-totalRow);
			}
		}


		bool checkForNewInt = boardAndConstPair(matrix, constMatrix); //does comparism with matrix[x1][y1]>matrix[x2][y2] if no val found return false

					
		if(checkForNewInt == false && checkIfEntered == false) {
			cout << "X's can have more then 1 value" << endl; 
			return false; 
		}

		check = checkXexist(matrix); //always check if 0 is left so that while loop can end once all values are written
	}
	return true;
}

vector<vector<int> > changeConstMatrix(vector<vector<string> > &matrix){ //new int matrix and all strings values will turn into int while -1 for all since they are indexs
	int lenX = matrix.size();
	int lenY = matrix[0].size();
	vector<vector<int> > myMatrix(lenX, vector<int>(lenY)); //newmatrix for const row size is lenx and column siz is leny
	
	for(int i =0 ; i < lenX; i++){
		for(int j =0; j <lenY; j++){
			myMatrix[i][j] = (stoi(matrix[i][j])-1) ; //const values are subtracted by 1 since index counting starts from 0 and before myMatrix's first row was deleted since it was only one int 
		}
	}
	return myMatrix;
}

bool checkMatch(vector<vector<int> > &boardMatrix, vector<vector<int> > &constMatrix){ //checks if const and board are matching if not return false
	int lenOfConstantX = constMatrix.size(); 
	int lenOfConstantY = constMatrix[0].size();

	int x1,y1, x2,y2; //coordinates for boardMatrix indexs

	for(int i =0; i <lenOfConstantX; i++){
		x1 = constMatrix[i][0]; 
		y1 = constMatrix[i][1]; 
		x2 = constMatrix[i][2];
		y2 = constMatrix[i][3]; 
		if(boardMatrix[x1][y1] <= boardMatrix[x2][y2]) {
			cout << "Constraints do not match board" << endl;
			return false; 
		}
	}
	return true;
}


	int main() {
	string boardCin, constCin; 
	ifstream boardInput, constInput; 
	cout << "Enter the board file: ";
	cin >> boardCin;
	cout << "Enter the constraint file: ";
	cin >> constCin;

	boardInput.open(boardCin.c_str()) ; //opening first input file  which is board file
	constInput.open(constCin.c_str());  //opening second input file which is constaint file

	vector<vector<string> > boardMatrix; //empty matrix to put in board values without the first row in input which is an integer
	vector<vector<string> > constMatrix;//empty matrix to put in const values without the first row in input which is an integer

	createMatrix(boardInput, boardMatrix) ; //this function updates boardMatrix into the board with xs included

	createMatrix(constInput, constMatrix);

	do{ // dowhile loop will terminate in the end of the project or if error occurs it will directly terminate with break statement
		if(!checkNumOfLinesBoard(boardInput)){
			break; 
		}
		if(!checkValuesOfBoard(boardInput)){
			break;
		}
		if(!checkRowsOfBoard(boardMatrix)) {
			break;
		}
		if(!checkColumnsOfBoard(boardMatrix)) {
			break;
		}
		if(!checkNumOfLinesConst(constInput)){
			break;
		}

		vector<vector<int> > newBoardMatrix; //string matrixs created will before change to int matrixs and the X values will become 0
		newBoardMatrix = changeValueOfX(boardMatrix); 
		
		vector<vector<int> > newConstMatrix; //string matrix created before will change into int matrix with all values subtracted by 1 because of the index to match
		newConstMatrix = changeConstMatrix(constMatrix); 


		bool check = insertingValues(newBoardMatrix, newConstMatrix); 
		if (!check) {
			break;
		}

		else{ 
			check = checkMatch(newBoardMatrix, newConstMatrix); //lastly checking the const and board comparism
			if (check){ //if all are true then board will be printed
				cout << "Files are in correct format" << endl;
				for(int i =0; i < newBoardMatrix.size(); i++){

					for(int j =0; j < newBoardMatrix[0].size(); j++){
						cout << newBoardMatrix[i][j] << " " ;
					}
					cout << endl;
				}
			}
		}
		break;

	}while(true);

	boardInput.close(); 
	constInput.close();
	return 0;
}