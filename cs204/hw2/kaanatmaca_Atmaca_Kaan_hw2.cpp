#include <iostream>
#include <string>
#include <vector>
#include <fstream> //to read files
#include <sstream> //to get words by one 
#include <chrono> //for time
#include <algorithm> 

//Kaan ATMACA CS204 TH2 
//IT WORKS SLOW IN LARGE HOPS BUT IT WORKS.

using namespace std; 

struct metroStop {
  string metroStopName;
  metroStop *left;
  metroStop *right;

  metroStop::metroStop() {}

  metroStop::metroStop(string s, metroStop* left, metroStop* right) 
	  : metroStopName(s), left(left), right(right)
  {};
};
  
struct metroLine {
  string metroNumber;
  metroLine *next;  
  metroStop *metroStops;
  vector<double>costs;
  metroLine::metroLine() {}

  metroLine::metroLine(string num, metroLine* next, metroStop* stop, vector<double> &cost)
	  : metroNumber(num), next(next), metroStops(stop), costs(cost)
  {};
};

bool consistencyCheck(metroLine* head) { //checking if doubly linked lists are always correct
  metroLine* currBL = head;
  while(currBL) {
    metroStop* currBS = currBL->metroStops;
    while(currBS) {
      metroStop* rightBS = currBS->right;
      if(rightBS && rightBS->left != currBS) {
	cout << "Inconsistency for " 
	     << currBL->metroNumber 
	     << " " 
	     << currBS->metroStopName << endl;
	return false;
      }
      currBS = currBS->right;
    }
    currBL = currBL->next;
  }
  return true;
}

void printMainMenu() { //prints main menu
  cout << endl;
  cout <<"I***********************************************I"<<endl
       <<"I               0 - EXIT PROGRAM                I"<<endl
       <<"I               1 - PRINT LINES                 I"<<endl
       <<"I               2 - ADD METRO STOP              I"<<endl
       <<"I               3 - DELETE METRO STOP           I"<<endl
       <<"I               4 - PATH FINDER                 I"<<endl
       <<"I***********************************************I"<<endl
       <<">>";
  cout << endl;
}  

void printmetroLinesDetailed(metroLine* head) { //prints all metroLines one by one
	metroLine* curr = head;
	
	int count = 0; 
	while(curr != nullptr){
		metroStop* temp = curr->metroStops;
		count = 0;
		while(temp != nullptr){ //counting how much stops there are
		count++; 
		temp = temp->right; 
		}
		temp = curr->metroStops; 
		cout << curr->metroNumber << ": " ; //M1A: 
		for(int i = 0; i < count-1 ; i++){ //printing all stops in line
			cout << temp->metroStopName ;
			cout << "<-" << curr->costs[i] << "->"; 
			temp = temp->right; 
		}
		cout << temp->metroStopName;  //prints last stop
		cout << endl; 
		curr = curr->next;
	}
}

void printOneMetroLine(metroLine* head) { //prints the chosen line only
	metroLine* curr = head; 
	metroStop* stops = curr->metroStops; 
	metroStop* temp = stops; 
	int count = 0; 
	while(temp->right !=nullptr){
		count++; 
		temp = temp->right; 
	}

	cout << curr->metroNumber <<": " ; //the line name 
	for(int i = 0; i < count ; i++){  //the stop names on that line are being printed
			cout << stops->metroStopName ;
			cout << "<-" << curr->costs[i] << "->"; 
			stops = stops->right; 
		}
		cout << stops->metroStopName; 
		cout << endl; 


}

bool checkLineIfExist(string nameOfLine, metroLine* head){ //true if metroLine exists for instance M1A exists its true
	metroLine* curr = head; 
	if(nameOfLine=="0") return false;
	while(curr != nullptr){
		if (curr->metroNumber == nameOfLine){ 
			cout << "The metro line information is shown below" << endl;
			printOneMetroLine(curr); 
			return true; 
		}
		curr = curr->next; 
	}
	cout << "Metro line cannot be found. Going back to previous menu." << endl;
	return false; 
}

bool checkNotMetroStopExist(string nameOfLine, string nameOfStopp, metroLine* head){ //check if metrostop exists in metroline if it does not exist then return true 
	metroLine* curr = head;
	metroStop* currInStops; 
	while(curr!= nullptr){
		if(curr->metroNumber == nameOfLine){
			currInStops = curr->metroStops; 
			while(currInStops->right != nullptr){
				if(currInStops->metroStopName == nameOfStopp){
					cout << nameOfStopp << " Metro stop already exists. Going back to previous menu." << endl;
					return false; 
				}
				currInStops = currInStops->right; 
			}
		}
		curr = curr->next; 
	}

	return true;
}

vector<string> splitingCosts(string s) {  //????????????????????????????????
	vector<string> words ;
	string word; 
	char ch = ',';
	int count = 0; 
	int len = s.length(); 
	for(int i =0; i < len; i++){
		if (ch== s[i]) 
			count++;
	}
	int j =0;
	int lastPlace; 
	while(j != count){
		lastPlace = s.find(","); 
		word = s.substr(0,lastPlace) ; 
		words.push_back(word); 
		len = s.length();
		s = s.substr(lastPlace+1,len-lastPlace) ; 
		j++;
	}
	len = s.length(); 
	word = s.substr(0, len); 
	words.push_back(word);
	return words; 
}

vector<double> createCosts(ifstream &inCosts){ //creates a vector<double> for all the costs in one metro line and then returns it 
	string line; 
	vector<double> allCosts;
	vector<string> words; 
	int len, count = 0 ;
	while(getline(inCosts, line)){
		allCosts.clear(); 
		count = 0;
		words = splitingCosts(line); 
		len = words.size(); 
		for (int i = 1; i <len ; i++){
			allCosts.push_back(stod(words[i])); 
		}
		return allCosts;
		
	}

}

bool checkForPrevStop(metroLine* head, string prevMetroStopName, string nameOfLine){ //it checks if there is a prevStop name existing in that line if exists it returns true
	metroLine* hh = head; 
	metroStop* curr; 
	while (hh != nullptr) {
		if(hh->metroNumber == nameOfLine) {
			curr = hh->metroStops; 
			while(curr->right != nullptr){
				if(curr->metroStopName == prevMetroStopName){
					return true;
				}
				curr = curr->right; 
			}

			if(curr->metroStopName == prevMetroStopName){ //to check if the prevstop is in the last one
					return true;
				}

		}
		hh = hh->next;
	}
	return false; 
}

void addNewMetroStop(string nameOfLine, string nameOfStopp, metroLine* head, double cost1, double cost2, string prevMetroStopName) { //adds new metroStop 
	bool check; 	
	do { //this func will checkForPrevStop and will give error until stop exists
		if(prevMetroStopName=="0") {
			break; //if exists and it will be the first part of line
		}
		
		check = checkForPrevStop(head, prevMetroStopName, nameOfLine); //checks if prevStop exists
		if (check) {
			break; //if exists 
		}
		else{
			cout << "Metro stop does not exist. Typo? Enter again (0 for main menu)" << endl; //if it doesnt exists ask again
			cin >> prevMetroStopName; 
		}
	}while(true); 
	
	if(prevMetroStopName=="0") { //adding metrostop to the beggining of the line 
		metroLine* line = head;
		metroStop* willBeAdded = nullptr; 
		metroStop* right = nullptr; 

		while(line->next != nullptr){
			if(line->metroNumber == nameOfLine){ //first find the line
				right = line->metroStops;
				willBeAdded = new metroStop(nameOfStopp, nullptr, right); //creates new metrostop with constructer
				line->metroStops = willBeAdded; 
				right->left = willBeAdded; 
				vector<double> costsList; 
				costsList = line->costs; 
				double temp, cost11=cost1; 
				costsList.push_back(cost1); //only cost1 will be added since it is the first stop
				int len = costsList.size(); 

				for(int i =0; i <len-1; i++){ //all the costs index will increase by one 
					temp = costsList[len-2-i];
					costsList[len-1-i] = temp; 
				} 
				costsList[0] = cost11; //cost1 is added with index 0 
				line->costs = costsList; 
				printOneMetroLine(line); 
				break;
			}
			line = line->next; 
		}
	}

	else { //adding metrostop to somewhere else but not the first place in line
		metroLine* line = head; 
		metroStop* rigg = nullptr; //right node to the added new one
		metroStop* nxt = nullptr;  //will be the left node
		metroStop* n = nullptr;  //the new node which will be added
		bool checkIfPrevIsLast = true; 
		while(line->next != nullptr){
			checkIfPrevIsLast = true; 
			if(line->metroNumber == nameOfLine){ //if line found
				int countStops = 0; 
				nxt = line->metroStops; 
				while(nxt->right != nullptr) {

					countStops++; //this is used since while adding cost we must know the index of where it should be added
					if(nxt->metroStopName == prevMetroStopName) {
						checkIfPrevIsLast = false; 
						n = new metroStop(nameOfStopp, nxt, nxt->right); //creates new metrostop with constrocter
						rigg = n->right;
						nxt->right = n; 
						rigg->left = n; 

						vector<double> costsList; //creating new cost list since new line is added
						costsList = line->costs; 
						costsList.push_back(cost1);
						costsList.push_back(cost2); 
						int len = costsList.size();

						costsList[countStops-1] = costsList[len-2]; //cost1 goes to the place to the cost which shoud be deleted
						costsList[len-2] = costsList[len-1] ; //now cost2 gets out of the end since we will pop the one cost
						costsList.pop_back() ;
						len = costsList.size() ;
						double temp; 
						for(int j = 0; j< len-countStops-1; j++) { //puts cost1 and cost2 into the places they should be with replacing the others 
							for (int i = countStops; i<len-1 ; i++) {
								temp = costsList[i+1] ;
								costsList[i+1]= costsList[i] ; 
								costsList[i]= temp; 
							
						}
					}
						line->costs = costsList; 
						printOneMetroLine(line); 
						break; 
					}
					nxt = nxt->right; 
				}
				if (checkIfPrevIsLast==true) { // add metrostop here if its in the last place of metroline
					n = new metroStop(nameOfStopp, nxt, nullptr); 
					nxt->right = n ; 
					vector<double> costsList; 
					costsList = line->costs; 
					costsList.push_back(cost1); //last index will be cost1 
					line->costs = costsList;
					printOneMetroLine(line); 
				}
				break; 
			}
			line = line->next;
		}
	}
}

void addmetroStop(metroLine* head){ //adding metrostop to the given metroline
	string metroLineName, metroStopName;
	double cost1, cost2; 
	string prevMetroStopName;
	cout << "Enter the name of the metro line to insert a new metro stop (0 for main menu)" << endl; 
	cin >> metroLineName;
	if(checkLineIfExist(metroLineName, head)) {//true if metroLine exists for instance M1A exists its true
		cout << "Enter the name of the new metro stop" << endl;
		cin >> metroStopName; 
		if(checkNotMetroStopExist(metroLineName, metroStopName, head)){ //check if metrostop exists in metroline if it does not exist then return true 
			cout << "Enter the name of the previous metro stop for the new one (0 to put the new one as the first metro stop)" << endl;
			cin >> prevMetroStopName; 
			cout << "Enter new cost 1"<< endl;
			cin >> cost1; 
			cout << "Enter new cost 2" << endl; 
			cin>>cost2; 
			addNewMetroStop(metroLineName, metroStopName, head, cost1, cost2, prevMetroStopName); //adding new metrostop
		}
	}
	else if(metroLineName=="0") {
		return;
	}

}

void deletemetroStop(metroLine* head){ //deleting metrostop from metroline also if all stops are deleted it deletes the line too
	metroLine* curr = head; 
	string metroLineName, metroStopName;
	double cost1, cost2; 
	string delMetroStopName;
	bool check; 
	cout << "Enter the name of the metro line to delete a new metro stop (0 for main menu)" << endl; 
	cin >> metroLineName;
	if(checkLineIfExist(metroLineName, head)) {
		cout << "Enter the name of the metro line to delete a new metro stop (0 for main menu)" << endl; 
		cin >> delMetroStopName; 
		do{ //loop to check to find the right stop to be deleted 
			check = checkForPrevStop(head, delMetroStopName, metroLineName); 
			if (check == true) {
				break; 
			}
			else if(delMetroStopName == "0") {
				break; 
			}
			else {
				cout << "Metro stop cannot be found. Enter the name of the metro stop to delete (0 for main menu)" << endl; 
				cin >> delMetroStopName; 
			}
		}while(true); 
		
		if (!(delMetroStopName == "0")) { //if prevstop not 0 then continue else the function will end
			metroStop* lft = nullptr; 
			metroStop* rght = nullptr; 
			metroStop* toBeDeleted = nullptr; 
			int countStops = 0; 

			while(curr != nullptr) {

				if (curr->metroNumber == metroLineName) {
					toBeDeleted = curr->metroStops; 

					do { 
						countStops++; 
						if (toBeDeleted->metroStopName == delMetroStopName) {
							
								if (countStops==1){ // this part will delete the first metrostop if wanted	
									if(toBeDeleted->right !=nullptr){
										rght = toBeDeleted->right; 
										curr->metroStops = rght; 
										delete toBeDeleted; 
										//now first stop has been deleted now we need to delete the first cost in list
										vector<double> allCosts = curr->costs; 
										int len = allCosts.size(); 
										for(int i=0; i <len-1; i++) {
											allCosts[i] = allCosts[i+1]; 
										}
										allCosts.pop_back(); 
										curr->costs = allCosts; 
										printOneMetroLine(curr); 
									
									}
									else{ //to delete if the chosen metro stop is the only one left
										
										delete toBeDeleted; //deletes metro stop
										metroLine* before = head; 
										int countLines = 0; 
										while(before->metroNumber != curr->metroNumber) {
											countLines++; 
											before = before->next;
										}
								
										before = head; 
										for(int k = 0; k < countLines-1; k++) {
											before = before->next;
										}
										metroLine* deleteMetroLine = curr; 
										before->next = curr->next; 
										delete deleteMetroLine; 
										curr = before->next;
									}
									break;
								}

								else{ //this part will delete the metrostop if its not the beginning or the end of the doubly linked lists			
										lft = toBeDeleted->left; 
										rght = toBeDeleted->right; 
										lft->right = rght; 
										rght->left = lft; 
										delete toBeDeleted; 
										///metroStop deleted now we need to delete the cost of it 
										countStops--;
										vector<double> allCosts = curr->costs; 
										int len = allCosts.size(); 
										double temp=0;

										temp = allCosts[countStops] + allCosts[countStops-1] ; 
										allCosts[countStops-1]= temp; 

										for(int i = countStops; i < len-1; i++) { //wrong
											allCosts[i] = allCosts[i+1];
										}
										allCosts.pop_back(); 
										curr->costs = allCosts;
										printOneMetroLine(curr); 
										break;	
							}	
						}
						toBeDeleted = toBeDeleted->right; 	
					}while(toBeDeleted->right != nullptr);

					if (toBeDeleted->right == nullptr) { //to delete last index metro stop 
								lft = toBeDeleted->left; 
								lft->right = nullptr; 
								delete toBeDeleted; 
								//last node deleted now delete last cost 
								vector<double> allCosts = curr->costs; 
								allCosts.pop_back();
								curr->costs = allCosts; 
								printOneMetroLine(curr); 
								break;
					}
				}
					curr = curr->next; 					
			}
		}

		else if (delMetroStopName == "0"){
			while (curr!= nullptr) {
				if(curr->metroNumber == metroLineName) {
					printOneMetroLine(curr); 
					break; 
				}
				curr = curr->next; 
			}
		}
		//count how many stops there are if no stops left return



	}



}

bool checkMetroStop(string nameOfStop, metroLine* head) { //checks if metrostop already exist
	metroLine* currLine = head; 
	metroStop* currStop = nullptr; 
	while(currLine != nullptr) {
		currStop = currLine->metroStops; 
		while(currStop->right != nullptr) {
			if(currStop->metroStopName == nameOfStop) {
				return true; 
			}
			currStop = currStop->right; 
		}
		if(currStop->metroStopName == nameOfStop) { //to check last stop of line  
				return true; 
			}
		currLine = currLine->next; 
	}
	return false; 
}

string createStringOfTransitionStops(metroLine* head) { //function to create and return a string of all the transition stops a,b,c,d, for instance
	metroLine* currLine = head; 
	metroStop* currStop = head->metroStops; 
	string myTransitionStops = ""; 
	string nameOfStop = ""; 
	int f; 
	metroLine* currLine2 = nullptr; // this will be the lines after currLine 
	metroStop* currStop2 = nullptr;  //this will be the stops after currStop
	bool checkForAnotherStop = false; 

	while(currLine != nullptr) { //while checking each line 
		currStop = currLine->metroStops; 
		while(currStop->right != nullptr) { // while checking each stop
			
			nameOfStop = currStop->metroStopName; 
			f = myTransitionStops.find(nameOfStop); //checking if nameOfStop exists in myTransitionStops 

			if((f <= 0)){ //if there is no string of nameofstop in mytransitionstop
				checkForAnotherStop = false; 
				currLine2 = currLine->next; 
				
				
				while(currLine2 != nullptr) {
					currStop2 = currLine2->metroStops; 
					while(currStop2->right != nullptr) {
						if(currStop2->metroStopName == nameOfStop){ //if name found somewhere else then the first stopplace
							myTransitionStops = myTransitionStops + nameOfStop + "," ; 
							checkForAnotherStop = true; 
							currStop2 = currStop2->right;
							break; 
						}
					currStop2 = currStop2->right;
					}	
					
					f = myTransitionStops.find(nameOfStop);
					if ((currStop2->metroStopName == nameOfStop) && (f<=0)) { //this if is to check eachlines last metrostop 
						myTransitionStops = myTransitionStops + nameOfStop + "," ; 
						checkForAnotherStop = true; 
					}					
					if (checkForAnotherStop) { //if another stop found break
							break; 
					}
					currLine2 = currLine2->next; 
				}
			}

			currStop = currStop->right; 
		}

		currLine = currLine->next;
	}
	
	return myTransitionStops; 
}

vector<metroStop*> findAllWantedPoints(metroLine* head, string pointName) { //finds all wanted points for instance startingMetroStops or endingMetroStops and returns them in a vector
	metroLine* currLine = head; 
	metroStop* currStop = nullptr;
	vector<metroStop*> allPoints; 
	allPoints.clear(); 
	while(currLine != nullptr) {
		currStop = currLine->metroStops; 
		while(currStop->right != nullptr) {
			if(currStop->metroStopName == pointName) { //if found then pushback into vector its place and name
				allPoints.push_back(currStop); 
				currStop = currStop->right;
				break; 
			}
			currStop  = currStop->right; 
		}
		if (currStop->metroStopName == pointName) {
			allPoints.push_back(currStop); 
		}
		currLine = currLine->next;
	}
	return allPoints; 

}

bool findInVector(vector<metroStop*> myPath, metroStop* curr) { //true if curr is already in path
	int len = myPath.size(); 
	for(int i = 0 ;  i <len ; i++) {
		if (myPath[i] == curr) {
			return true; 
		}
	}
	return false; 
}

vector<metroStop*> doTransition(string stopName, metroLine* head, metroStop* transitionStop) { //does transition from one stop to another with returning all the metrostops it can do transition
	metroLine* curr = head;
	metroStop* currStop =nullptr;
	vector<metroStop*> stops; 

	while(curr!=nullptr){
		currStop = curr->metroStops;
		while(currStop->right != nullptr) {
			if(currStop->metroStopName == stopName && currStop!=transitionStop) {
				stops.push_back(currStop);
			}
			currStop = currStop->right;
		}
		if(currStop->metroStopName == stopName && currStop!=transitionStop) {
			stops.push_back(currStop);
		}
		curr = curr->next;
	}
	return stops; 
}

double findCostFromOnePointToAnother(metroLine* head, metroStop* currStop, metroStop* nextStop) { //finds the cost it takes from one stop to the next stop in path
	if(currStop->metroStopName == nextStop->metroStopName) return 0; //since it is a transition stop  
	else{
		metroLine* currLine = head; 
		while(currLine!= nullptr){
			double cost = 0; 
			int count = -1; //to find which cost to get from vector it will be the index 
			metroStop* tempStop = currLine->metroStops;
			while(tempStop->right != nullptr){
				count++;
				if(tempStop == currStop) { //once currstop is found
					if(tempStop->right == nextStop){ //next stop is in the right side 
						vector<double> allCosts = currLine->costs;
						cost = allCosts[count]; 
						return cost;
					}
					else { //next stop is in the left side
						vector<double> allCosts = currLine->costs;
						cost = allCosts[count-1]; 
						return cost;
					}
				}
				tempStop = tempStop->right;
			}
			if(tempStop == currStop && currStop->left->left!=nullptr) { //it is in the end of the line so next must be on the left side
				vector<double> allCosts = currLine->costs;
				cost = allCosts[count-1]; 
				return cost;
			}
			else if(tempStop == currStop){
				vector<double> allCosts = currLine->costs;
				cost = allCosts[count]; 
				return cost;
			}
			currLine = currLine->next;
		}
	}

}

void calculateBestCostOfPath(metroLine* head, vector<vector<metroStop*>> solutions, vector<metroStop*> &bestPath, double &minCost) { // 0 < numOfPath < solutions.size() so -> num of path will give the index of which solution we are looking right now
	int numOfPath = solutions.size()-1;
	double cost =0;
	metroStop* currStop = nullptr;
	metroStop* nextStop = nullptr;
	int lenOfSolutions = solutions.size();

	for(int i = 0; i<lenOfSolutions; i++) {
		cost = 0;
		for(int j=0; j<solutions[i].size()-1; j++) {
			if(i==0) { //firstly we say that the cheapest way is the first path
				currStop = solutions[i][j];
				nextStop = solutions[i][j+1];
				cost += findCostFromOnePointToAnother(head, currStop, nextStop);
				minCost = cost;
				bestPath = solutions[i]; 
			}
			else{
				if(minCost<cost) break;  //this is a break statement if the cost from i>0 passes mincost then it cant be min and it will break no need to continue
				currStop = solutions[i][j];
				nextStop = solutions[i][j+1];
				cost += findCostFromOnePointToAnother(head, currStop, nextStop);
			}
			if(nextStop == solutions[i][solutions[i].size()-1] && cost < minCost){  //changes the mincost and bestpath
				minCost = cost;
				bestPath.clear();
				bestPath = solutions[i]; 
			}
		}
	}

}

vector<metroStop*> pathRecursion(int hopsLeft, metroLine* head,  metroStop* firstStop, metroStop* currStop, metroStop* target, vector<metroStop*> myPath, bool isTransition,   vector<vector<metroStop*>> &solutions) { //DOES RECURSION
	
    if(currStop == target) //if at target stop
		return myPath;
    
	if(currStop->metroStopName==target->metroStopName) { //if same name but in different locations 
		myPath.clear();
		return myPath;
	}
  
	if(hopsLeft > 0 && myPath.size() > 1  && !isTransition){ //if hops left,first move and our last move wasn't a hop
		string currStopName = currStop->metroStopName; //find all same name metrostop
		vector<metroStop*> allTransitions = doTransition(currStopName, head, currStop);
        for(int i = 0; i < allTransitions.size(); i++) {
            metroStop* nextStop = allTransitions[i];          
            myPath.push_back(nextStop);
			vector<metroStop*> newPath = pathRecursion(hopsLeft - 1, head, firstStop, nextStop, target, myPath, true, solutions); //recursion with hop being done
			if(newPath.size() > 0) { //if wrong the size is 0
			solutions.push_back(newPath);
		}  
            myPath.pop_back();   //if hop was wrong pop the last hop
        }
    }

	if(currStop->right != nullptr && (myPath.size() < 2 || myPath[myPath.size() - 2] != currStop->right)) { //move right if last step was not left and right is not nullptr
		metroStop* nextStop = currStop->right;
        myPath.push_back(nextStop);
		vector<metroStop*> newPath = pathRecursion(hopsLeft, head, firstStop, nextStop, target, myPath, false, solutions); //recursion
		if(newPath.size() > 0) { //if wrong the size is 0
			solutions.push_back(newPath);
		}
        myPath.pop_back(); //if last right was wrong pop it
    }

    
    if(currStop->left != nullptr && (myPath.size() < 2 || myPath[myPath.size() - 2] != currStop->left)) { //move left if last step was not right and left is not nullptr

		metroStop* nextStop = currStop->left;
        myPath.push_back(nextStop);
		vector<metroStop*> newPath = pathRecursion(hopsLeft, head, firstStop, nextStop, target, myPath, false, solutions);
		if(newPath.size() > 0) {
			solutions.push_back(newPath);
		}
        myPath.pop_back();
    }
	myPath.clear();
	return myPath;
}

bool printStopName(metroLine* head, metroStop* stopName) { //prints only one stop its name 
	metroLine* currLine = head; 
	metroStop* currStop = nullptr;
	while(currLine!=nullptr){
		currStop = currLine->metroStops;
		while(currStop->right!=nullptr) {
			if(currStop==stopName) {
				cout << currStop->metroStopName << " " ;
				return true;
			}
			currStop = currStop->right;
		}
		if(currStop==stopName) {
			cout << currStop->metroStopName << " " ;
			return true;
		}
		currLine = currLine->next;
	}

}

bool printMetroLineName(metroLine* head, metroStop* stopName){ //prints only the metroline name with :
	metroLine* currLine = head; 
	metroStop* currStop = nullptr;
	while(currLine!=nullptr){
		currStop = currLine->metroStops;
		while(currStop->right!=nullptr) {
			if(currStop==stopName) {
				cout << currLine->metroNumber<< ": " ;
				return true;
			}
			currStop = currStop->right;
		}
		if(currStop==stopName) {
			cout << currLine->metroNumber<< ": " ;
			return true;
		}
		currLine = currLine->next;
	}

}

void printBestPath(metroLine* head, vector<metroStop*> myPath, double cost) { //will print the best path which was found with metroline metrostops endl costs and hop count
	metroStop* currStop = nullptr; 
	metroStop* nextStop = nullptr;
	
	cout << "Best cost path:" << endl;

	vector<int> indexsOfTransitions; 
	int countHops = 0; 
	for(int i=0; i<myPath.size()-1;i++) { //finding on which index there is a transition and also counting number of hops
		currStop = myPath[i] ;
		nextStop = myPath[i+1]; 
		if(currStop->metroStopName == nextStop->metroStopName) {
			indexsOfTransitions.push_back(i+1);
			countHops++;
		}
	}

	printMetroLineName(head, myPath[0]); //prints the first metroline 
	int count =0;
	for(int i =0; i<myPath.size(); i++) {
		if(indexsOfTransitions.size()>0 && i==indexsOfTransitions[count]) { //for evry transition again a metroline is being printed
			printMetroLineName(head, myPath[i]);
			count++;
			if(count>=indexsOfTransitions.size()) count = indexsOfTransitions.size()-1;
		}
		printStopName(head, myPath[i]); //prints all the stops in mypath in order
		if(indexsOfTransitions.size()>0 && i+1==indexsOfTransitions[count]) {
			cout << endl;
		}	
	}
	cout << endl;
	cout << "Hops: " << countHops << endl; //hops and then cost is printed
	cout << "Cost: " << cost << endl;

}

void pathfinder(metroLine* head, int hops){ //path finder function
	metroStop* startingStop = nullptr; 
	metroStop* endingStop = nullptr; 
	string startPointName, endPointName; 
	bool checkIfExistPoint1 = true, checkIfExistPoint2 = true; 
	string transitionStops; 

	cout << "Where are you now?" << endl; 
	cin >> startPointName; 
	cout << "Where do you want to go?" << endl; 
	cin >> endPointName; 
	checkIfExistPoint1 = checkMetroStop(startPointName, head); //checks if sstop exists 
	checkIfExistPoint2 = checkMetroStop(endPointName, head) ;  //check if endingstop exists
	if (checkIfExistPoint1==true && checkIfExistPoint2 == true) {
		chrono::steady_clock::time_point begin = chrono::steady_clock::now();
		transitionStops = createStringOfTransitionStops(head);  //creates a string containint all transition stops
		vector<metroStop*> path; 
		vector<metroStop*> startingPoints = findAllWantedPoints(head, startPointName); //finds all startingpoint stops and stores in vector
		vector<metroStop*> endingPoints = findAllWantedPoints(head, endPointName); //finds all endingpoint stops and stores in vector
		int lenOfStarts = startingPoints.size(); 
		int lenOfEnds = endingPoints.size(); 
		int hopsRemaining = hops; 
		bool canItRecursive;  
		bool checkIfTransitionDone = false;

		vector<vector<metroStop*>> solutions;
		vector<double> allCosts; 
		for (int i=0; i <lenOfStarts; i++) { //for all starting points
			for(int j=0; j<lenOfEnds; j++) { //for all ending points
				hopsRemaining = hops;
				path.clear(); 
				path.push_back(startingPoints[i]);  
				checkIfTransitionDone = false;
				
				pathRecursion(hopsRemaining, head, startingPoints[i], startingPoints[i], endingPoints[j], path, false, solutions); 
				//at the end the vector<vector<metroStop*>> solutions will have all the paths to reach from one stop to another
			}
		}
		
		vector<metroStop*> bestPath; 
		double bestCost = 0;

		calculateBestCostOfPath(head, solutions,bestPath, bestCost); //calculates best best path and cost and returns it with &
		int lenOfPaths = solutions.size(); 
		if(lenOfPaths > 0){
			printBestPath(head, bestPath, bestCost);
		}
		else{
			cout << "No path found between " << startPointName << " and " << endPointName << endl;
		}
		chrono::steady_clock::time_point end = chrono::steady_clock::now();

		double time = chrono::duration_cast<chrono::microseconds> (end - begin).count();
		time = time/1000000;

		cout << "Elapsed time: " << time << " seconds" << endl;
		
	}
	else { //if stop does not exist
		cout << "Metro stop does not exist in the table. Going back to previous menu." << endl; 
	}

}

vector<string> splitingLine(string s) { //gets files string and then returns a vector with splitting its lines
	vector<string> words ;
	string word; 
	char ch = ',';
	int count = 0; 
	int len = s.length(); 
	for(int i =0; i < len; i++){
		if (ch== s[i]) 
			count++;
	}
	int j =0;
	int lastPlace; 
	while(j != count){
		lastPlace = s.find(","); 
		word = s.substr(0,lastPlace) ; 
		words.push_back(word); 
		len = s.length();
		s = s.substr(lastPlace+1,len-lastPlace) ; 
		j++;
	}
	len = s.length(); 
	word = s.substr(0, len-1); 
	words.push_back(word);
	return words; 
}

void processMainMenu(metroLine* head, int hops) {
  char input;
  do{
    if(!consistencyCheck(head)) {
      cout << "There are inconsistencies. Exit." << endl; 
      return;
    }
    printMainMenu();
    cout << "Please enter your option " << endl;
    cin >> input;
    switch (input) {
    case '0':
      cout << "Thanks for using our software" << endl;
      return;
    case '1':
      printmetroLinesDetailed(head);
      break;
    case '2':
		addmetroStop(head);
      break;
    case '3':
		deletemetroStop(head);
      break;
    case '4':
      pathfinder(head, hops);
      break;
    default:
      cout << "Invalid option: please enter again" << endl;
    }
  } while(true);
}

void createDoublyList(ifstream &inLines,vector<metroStop*> &metros ) { //creates double sided list 
	string line, word, metroLineName; 
	bool checkIfFirstEntered = false; 
	int count = 0, len; 
	vector<string> words; 

	while(getline(inLines,line)){
		count = 0; 
		checkIfFirstEntered = false;
		words = splitingLine(line);
		len = words.size(); 
		metroStop* nxt = nullptr; 
		metroStop* tail = nullptr; 
		metroStop* head = nullptr;  


		for(int i = 0; i <len;i++){
			
			if (!checkIfFirstEntered){
				metroLineName = words[i]; 
				checkIfFirstEntered = true; 
			}
			else {
				if (count == 0){ 
				nxt = new metroStop(words[i], nullptr, nullptr);
				tail = nxt; 
				head = nxt; 
				metros.push_back(head); 
				count++; 
				}

				else {
					nxt = new metroStop(words[i], tail, nullptr); 
					tail->right=nxt; 
					tail = nxt; 
				}	
			}
		}

	}
	inLines.clear();
	inLines.seekg(0);

}

void createLinkedList(ifstream &inLines, ifstream &inCosts , vector<metroStop*> metros, metroLine* &headOfMetroLine){ //creates linked list
	string line, word, metroLineName; 
	bool checkIfFirstEntered = false; 
	vector<double> allCosts;
	int count = 0, len; 
	vector<string> words;
	vector<double> costs;
	int i = 0, otherCount=0; 
	bool checkIfNextEntered = false;
	metroLine* nxt = nullptr; 
	metroLine* tail = nullptr; 
	metroLine* head = nullptr; 

	while(getline(inLines,line)){
			allCosts = createCosts(inCosts);
			words = splitingLine(line);

			metroLineName = words[0]; 
			checkIfFirstEntered = true; 
		
			if (count == 0){ 
						nxt = new metroLine(metroLineName, nullptr, metros[i], allCosts);
						head = nxt; 
						if(otherCount==0){
						headOfMetroLine = head; 
						otherCount++;
						}
						tail = nxt; 
						count++;
						i++; 
					}
			else {
					nxt = new metroLine(metroLineName, nullptr, metros[i], allCosts); 
					tail->next = nxt; 
					tail = nxt; 
					i++; 	
				
				}
		}
	inLines.clear();
	inLines.seekg(0); 
	inCosts.clear();
	inCosts.seekg(0);
}

int main() {

	ifstream inLines, inCosts; 
	string lines, costs; 
	string hops; 
	int numOfHops; 
	cout << "Enter the name of the metro line data file:" << endl; 
	cin >> lines; 
	cout << "Enter the name of costs file:" << endl; 
	cin >> costs; 
	cout << "Enter maximum number of hops:" << endl; 
	cin >> hops; 
	numOfHops = stoi(hops); 

	inLines.open(lines.c_str()); 
	inCosts.open(costs.c_str());

	metroLine* headOfMetroLine; //will be head
	vector<metroStop*> metroStopPointers;  
	createDoublyList(inLines, metroStopPointers); 
	vector<double> allCosts; 
	createLinkedList(inLines, inCosts, metroStopPointers, headOfMetroLine); 
	processMainMenu(headOfMetroLine, numOfHops); 
	
	inLines.close();
	inCosts.close();

	return 0; 
}