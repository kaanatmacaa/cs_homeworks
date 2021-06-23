#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ostream>
#include <stdlib.h>

//KAAN ATMACA 28239 - CS 300 - HW 1

using namespace std;

template <class myType>
class Stack {
public:
    Stack() {
        topOfStack = NULL;
    }

    ~Stack() {
        makeEmpty();
    }

    bool isEmpty() const {
        return topOfStack == nullptr;
    }

    void makeEmpty() {
        while (!isEmpty()) {
            pop();
        }
    }

    void pop() {
        if (!isEmpty()) {
            ListNode* old = topOfStack;
            topOfStack = topOfStack->next;
            delete old;
        }
    }

    void push(const myType& x) {
        topOfStack = new ListNode(x, topOfStack);
    }

    const myType& getTop() const {
        if (!isEmpty()) return topOfStack->object;
    }

    void changeTop(const myType& x) {
        topOfStack->object = x;
    }

private:
    struct ListNode {
        myType object;
        ListNode* next;
        friend class StackNode;
        ListNode(const myType& value, ListNode* n = NULL)
            : object(value), next(n) {}
    };

    ListNode* topOfStack;
};

struct StackNode {
public:
    int x_coordinate, y_coordinate;
    bool visited;
    bool has_pawn;
    vector<StackNode> alreadyVisited; //poplarken 
};

bool checkX(vector<vector<StackNode> >& matrix, int column, int row) { //checks if row has 3 pawns
    int count = 0;
    row--;
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[row][i].has_pawn == true) {
            count++;
        }
        if (count >= 3) {
            return false;
        }
    }
    return true;
}

bool checkY(vector<vector<StackNode> >& matrix, int column, int row) { //checks if column has 3 pawns
    int count = 0;
    column--;
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i][column].has_pawn == true) count++;

        if (count >= 3) {
            return false;
        }
    }
    return true;
}

bool checkZ1(vector<vector<StackNode> >& matrix, int column, int row) { //checks if first diagonal has 3 pawns
    int count = 0;
    int n = matrix.size();
    column--;
    row--;
    int tempR = row;
    int tempC = column;

    while (tempR > 0 && tempC < n - 1) {
        tempR--;
        tempC++;
        if (matrix[tempR][tempC].has_pawn == true)count++;
        if (count >= 3) {
            return false;
        }
    }
    tempR = row;
    tempC = column;
    while (tempR < n - 1 && tempC>0) {
        tempR++;
        tempC--;
        if (matrix[tempR][tempC].has_pawn == true)count++;
        if (count >= 3) {
            return false;
        }
    }
    return true;
}

bool checkZ2(vector<vector<StackNode> >& matrix, int column, int row) { //checks if second diagonal has 3 pawns
    int count = 0;
    int n = matrix.size();
    column--;
    row--;
    int tempR = row;
    int tempC = column;

    while (tempR > 0 && tempC > 0) {
        tempR--;
        tempC--;
        if (matrix[tempR][tempC].has_pawn == true) count++;
        if (count >= 3) return false;
    }
    tempR = row;
    tempC = column;
    while (tempR < n - 1 && tempC < n - 1) {
        tempR++;
        tempC++;
        if (matrix[tempR][tempC].has_pawn == true) count++;
        if (count >= 3) return false;
    }
    return true;
}

vector<StackNode> checkingList(vector<vector<StackNode> >& matrix, vector<StackNode>& myCoo, StackNode pawn) {//checks the list which has all the places the pawns can go but it checks if there are already 3 pawns on that axcess of if it is allready visited
    int n = myCoo.size();
    vector<StackNode> myList;
    int x, y;
    bool found = false;
    for (int i = 0; i < n; i++) {
        found = false;
        x = myCoo[i].x_coordinate;
        y = myCoo[i].y_coordinate;
        if (checkX(matrix, x, y) && checkY(matrix, x, y)) {
            if (checkZ1(matrix, x, y) && checkZ2(matrix, x, y)) {
                for (int j = 0; j < pawn.alreadyVisited.size(); j++) { // 2 2 - 2 1 -> 2 1    2 2 - 2 2 > x 
                    if (pawn.alreadyVisited[j].x_coordinate == myCoo[i].x_coordinate && pawn.alreadyVisited[j].y_coordinate == myCoo[i].y_coordinate) found = true;
                }
                if (!found) myList.push_back(myCoo[i]);
            }
        }
    }
    return myList;
}

vector<StackNode> checkAvaSquare(vector<vector<StackNode> >& matrix, int column, int row, StackNode pawn) { //checks the given sqaures if available or not
    int n = matrix.size();
    n--;
    column--;
    row--;
    StackNode coordinate;
    vector<StackNode> myCoo;
    if (column > 0) {
        if (matrix[row][column - 1].has_pawn == false) { //&& matrix[row][column - 1].visited == false
            coordinate.x_coordinate = column;
            coordinate.y_coordinate = row + 1;
            myCoo.push_back(coordinate);
        }
    }
    if (column < n) {
        if (matrix[row][column + 1].has_pawn == false) { //&& matrix[row][column + 1].visited == false
            coordinate.x_coordinate = column + 2;
            coordinate.y_coordinate = row + 1;
            myCoo.push_back(coordinate);
        }
    }
    if (row > 0) {
        if (matrix[row - 1][column].has_pawn == false) { //&& matrix[row - 1][column].visited == false
            coordinate.x_coordinate = column + 1;
            coordinate.y_coordinate = row;
            myCoo.push_back(coordinate);
        }
    }
    if (row < n) {
        if (matrix[row + 1][column].has_pawn == false) { //&& matrix[row + 1][column].visited == false
            coordinate.x_coordinate = column + 1;
            coordinate.y_coordinate = row + 2;
            myCoo.push_back(coordinate);
        }
    }
    if (row > 0 && column > 0) {
        if (matrix[row - 1][column - 1].has_pawn == false) { //&& matrix[row - 1][column - 1].visited == false
            coordinate.x_coordinate = column;
            coordinate.y_coordinate = row;
            myCoo.push_back(coordinate);
        }
    }
    if (row < n && column < n) {
        if (matrix[row + 1][column + 1].has_pawn == false) { //&& matrix[row + 1][column + 1].visited == false
            coordinate.x_coordinate = column + 2;
            coordinate.y_coordinate = row + 2;
            myCoo.push_back(coordinate);
        }
    }
    if (row > 0 && column < n) {
        if (matrix[row - 1][column + 1].has_pawn == false) { //&& matrix[row - 1][column + 1].visited == false
            coordinate.x_coordinate = column + 2;
            coordinate.y_coordinate = row;
            myCoo.push_back(coordinate);
        }
    }
    if (row < n && column > 0) {
        if (matrix[row + 1][column - 1].has_pawn == false) { //&& matrix[row + 1][column - 1].visited == false
            coordinate.x_coordinate = column;
            coordinate.y_coordinate = row + 2;
            myCoo.push_back(coordinate);
        }
    }
    vector<StackNode> myList;
    myList = checkingList(matrix, myCoo, pawn);
    return myList;
}

void selectSquare(vector<vector<StackNode> >& matrix, Stack<StackNode>& pawns, int& numOfPawns) { //selects a square and places the pawn on that randomly
    vector<StackNode> list = checkAvaSquare(matrix, pawns.getTop().x_coordinate, pawns.getTop().y_coordinate, pawns.getTop());
    StackNode prev, pawn;
    pawn = pawns.getTop();
    prev = pawn;
    while (list.size() == 0) { //if no place to go 
        numOfPawns++;
        prev = pawns.getTop();
        pawns.pop();
        prev.alreadyVisited.clear();
        prev.alreadyVisited.resize(0);
        pawn = pawns.getTop();
        pawn.alreadyVisited.push_back(prev);
        pawns.changeTop(pawn);
        list = checkAvaSquare(matrix, pawn.x_coordinate, pawn.y_coordinate, pawn);
        matrix[prev.y_coordinate - 1][prev.x_coordinate - 1].has_pawn = false;
    }
    int n = rand() % list.size(); 
    StackNode nxt = list[n];
    pawns.push(nxt);
    matrix[nxt.y_coordinate - 1][nxt.x_coordinate - 1].has_pawn = true;
}

void placePawns(int numOfPawns, vector<vector<StackNode> >& matrix, Stack<StackNode>& pawns) { //places the pawns
    StackNode pawn;
    matrix[0][0].has_pawn = true;
    matrix[0][0].visited = true; //so that knight doesnt come here
    matrix[0][0].x_coordinate = 1;
    matrix[0][0].y_coordinate = 1;
    pawns.push(matrix[0][0]);
    numOfPawns--;

    while (numOfPawns > 0) {
        selectSquare(matrix, pawns, numOfPawns);
        numOfPawns--;
    }
}

vector<StackNode> selectSquareKnight(vector<vector<StackNode> >& matrix, StackNode& knight, int n, int col2, int row2) { //8 different places the knight can go
    //and then if it doesnt have pawn and is not visited then we add to list and at end we check its vector and if it was already used
    vector<StackNode> myCoo;
    StackNode coo;
    int row = knight.y_coordinate;
    int col = knight.x_coordinate;
    row--;
    col--;
    n--;
    if (n > row && 1 < col) {
        if (matrix[row + 1][col - 2].has_pawn == false && matrix[row + 1][col - 2].visited == false) {
            coo.x_coordinate = col - 1;
            coo.y_coordinate = row + 2;
            myCoo.push_back(coo);
        }
    }
    if (n - 1 > row && 0 < col) {
        if (matrix[row + 2][col - 1].has_pawn == false && matrix[row + 2][col - 1].visited == false) {
            coo.x_coordinate = col;
            coo.y_coordinate = row + 3;
            myCoo.push_back(coo);
        }
    }
    if (n > row && n - 1 > col) {
        if (matrix[row + 1][col + 2].has_pawn == false && matrix[row + 1][col + 2].visited == false) {
            coo.x_coordinate = col + 3;
            coo.y_coordinate = row + 2;
            myCoo.push_back(coo);
        }
    }
    if (n - 1 > row && n > col) {
        if (matrix[row + 2][col + 1].has_pawn == false && matrix[row + 2][col + 1].visited == false) {
            coo.x_coordinate = col + 2;
            coo.y_coordinate = row + 3;
            myCoo.push_back(coo);
        }
    }

    if (0 < row && 0 < col - 1) {
        if (matrix[row - 1][col - 2].has_pawn == false && matrix[row - 1][col - 2].visited == false) {
            coo.x_coordinate = col - 1;
            coo.y_coordinate = row;
            myCoo.push_back(coo);
        }
    }
    if (1 < row && 0 < col) {
        if (matrix[row - 2][col - 1].has_pawn == false && matrix[row - 2][col - 1].visited == false) {
            coo.x_coordinate = col;
            coo.y_coordinate = row - 1;
            myCoo.push_back(coo);
        }
    }
    if (0 < row && n - 1 > col) {
        if (matrix[row - 1][col + 2].has_pawn == false && matrix[row - 1][col + 2].visited == false) {
            coo.x_coordinate = col + 3;
            coo.y_coordinate = row;
            myCoo.push_back(coo);
        }
    }
    if (1 < row && n > col) {
        if (matrix[row - 2][col + 1].has_pawn == false && matrix[row - 2][col + 1].visited == false) {
            coo.x_coordinate = col + 2;
            coo.y_coordinate = row - 1;
            myCoo.push_back(coo);
        }
    }

    vector<StackNode> myList;
    bool found = false;
    int x, y;
    n = myCoo.size();
    for (int i = 0; i < n; i++) {
        found = false;
        x = myCoo[i].x_coordinate;
        y = myCoo[i].y_coordinate;
        for (int j = 0; j < knight.alreadyVisited.size(); j++) { // 2 2 - 2 1 -> 2 1    2 2 - 2 2 > x 
            if (knight.alreadyVisited[j].x_coordinate == myCoo[i].x_coordinate && knight.alreadyVisited[j].y_coordinate == myCoo[i].y_coordinate) found = true;
        }
        if (!found) myList.push_back(myCoo[i]);
    }

    for (int i = 0; i < myList.size(); i++) {
        if (myList[i].y_coordinate == row2 && myList[i].x_coordinate == col2) {
            myList.clear();
            myList.resize(0);
            StackNode nxt;
            nxt.x_coordinate = col2;
            nxt.y_coordinate = row2;
            myList.push_back(nxt);
            break;
        }
    }

    return myList;
}

bool placeKnight(vector<vector<StackNode> >& matrix, Stack<StackNode>& knights, int column, int row, int column2, int row2) { //returns true if path found to king
    StackNode knight;
    StackNode prev;
    knight.x_coordinate = column;
    knight.y_coordinate = row;
    matrix[knight.y_coordinate - 1][knight.x_coordinate - 1].visited = true;
    knights.push(knight);
    int n = matrix.size();
    int r;

    vector<StackNode> list = selectSquareKnight(matrix, knight, n, column2, row2); //list is where knight can go
    int myListSize = list.size();
    if (myListSize == 0) return false;
     
    knight = knights.getTop();
    prev = knight;

    while (true) { //this breaks if we find the king or if we have no other place to and at knights first location
        list = selectSquareKnight(matrix, knight, n, column2, row2); 
        while (list.size() == 0) {
            if (knights.getTop().x_coordinate == column && knights.getTop().y_coordinate == row) return false;
            prev = knights.getTop();
            knights.pop();
            prev.alreadyVisited.clear();
            prev.alreadyVisited.resize(0);
            knight = knights.getTop();
            knight.alreadyVisited.push_back(prev);
            knights.changeTop(knight);
            list = selectSquareKnight(matrix, knight, n, column2, row2);
            matrix[prev.y_coordinate - 1][prev.x_coordinate - 1].visited = false;
        }
        int r = rand() % list.size();
        StackNode nxt = list[r];
        knights.push(nxt);
        matrix[nxt.y_coordinate - 1][nxt.x_coordinate - 1].visited = true;
        knight = nxt;
        if (knights.getTop().y_coordinate == row2 && knights.getTop().x_coordinate == column2) return true;
        if (knights.getTop().x_coordinate == column && knights.getTop().y_coordinate == row) return false;
    }
}

void createMatrix(int n, vector<vector<StackNode> >& matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j].has_pawn = false;
            matrix[i][j].x_coordinate = j + 1; //matrix[1][2] = x-> 3 y -> 2
            matrix[i][j].y_coordinate = i + 1;
            matrix[i][j].visited = false;
        }
    }
}

void printMatrix(vector<vector<StackNode> > matrix, int n) {
   cout << "The matrix:" << endl;
    int count = 0;
    for (int i = n - 1; i > -1; i--) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j].has_pawn == true) cout << "1";
            else cout << "0";
            cout << " ";
        }     
        if(count != n) cout << endl;
       count++;
    }
}

void reSizeMatrix(vector<vector<StackNode> >& matrix, int n) { //resizes the matrixs rows and columns
    matrix.resize(n);
    for (int i = 0; i < n; i++) {
        matrix[i].resize(n);
    }
}

void outputFunc(int &n, int &pnum, Stack<StackNode> &pawns, Stack<StackNode> &knights, vector<vector<StackNode> > &matrix, int x1, int y1, int x2, int y2, bool check) {
    //this function writes on the file each time
    ofstream out;
    string fileName = "output_" + to_string(n) + "_" + to_string(pnum) + ".txt";
    out.open(fileName.c_str()); 
    out << "N = " << n << endl;
    out << "P = " << pnum << endl;
    out << endl; 
    out << "Pawn Locations" << endl;
    
    while (!pawns.isEmpty()) {
        out << pawns.getTop().x_coordinate << " " << pawns.getTop().y_coordinate << endl;
        pawns.pop();
    }
    out << endl; 
    out << "Knight = " << x1 << " " << y1 << endl;
    out << "King = " << x2 << " " << y2 << endl;
    out << endl;
    if (check) { 
        Stack<StackNode> knightsRow;
        while (!knights.isEmpty()) {
            // out << knights.getTop().x_coordinate << " " << knights.getTop().y_coordinate << endl;
            if (knights.getTop().x_coordinate == x1 && knights.getTop().y_coordinate == y1) {
                knightsRow.push(knights.getTop());
                break;
            }
            knightsRow.push(knights.getTop());
            knights.pop();
        }
        while (!knightsRow.isEmpty()) {
            out << knightsRow.getTop().x_coordinate << " " << knightsRow.getTop().y_coordinate << endl;
            //if (knightsRow.getTop().x_coordinate == x2 && knightsRow.getTop().y_coordinate == y2) break;
            knightsRow.pop();
        }
    }
    else {
       out  << "No Way!" << endl;
    }
    out << endl; 
    out << "Matrix" << endl;
    int count = 0;
    for (int i = n - 1; i > -1; i--) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j].has_pawn == true) out << "1";
            else out << "0";
            out << " ";
        }
        count++;
        if (count != matrix.size()) out << endl;    
    }
    out.close();
}

int main() { 
    do {
        int n, pnum;
        cout << "Please enter the size of the board (n): ";
        cin >> n;
        while (n < 5 || n > 10) { //if invalid input
            cout << "Invalid Input" << endl;  
            cout << "Please enter the size of the board (n): ";
            cin >> n;
        } 
        cout << "Please enter the number of the pawns (p): ";
        cin >> pnum;
        while (pnum > 3 * n) { //if invalid input
            cout << "Invalid Input" << endl;
            cout << "Please enter the number of the pawns (p): ";
            cin >> pnum;
        }

        Stack<StackNode> pawns;
        vector<vector<StackNode> > matrix;
        reSizeMatrix(matrix, n); //resizein matrix
        createMatrix(n, matrix); //creating the matrixs coordinates, visited, has_pawn
        placePawns(pnum, matrix, pawns); //placing all pawns randomly and by rule 
        printMatrix(matrix, n); //prints the matrix as wanted

        int x1, x2, y1, y2;
        cout << "Enter the position of knight(x,y): ";
        cin >> x1 >> y1; //////////////if on pawn
        cout << "Enter the position of king(x,y): ";
        cin >> x2 >> y2; //////////////////if on pawn+		

        Stack<StackNode> knights;
        bool check = placeKnight(matrix, knights, x1, y1, x2, y2); //randomly makes knight move to find the king if found it returns true

        if (check) {
            cout << "Path found, see the output file!" << endl;
            outputFunc(n, pnum, pawns, knights, matrix, x1, y1, x2, y2, true);
        }
        else {
            cout << "No Way!" << endl;
            outputFunc(n, pnum, pawns, knights, matrix, x1, y1, x2, y2, false);
        }
       break; 
    } while (true);
    return 0;
}
