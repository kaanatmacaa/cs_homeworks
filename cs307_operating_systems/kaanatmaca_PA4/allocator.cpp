#include <algorithm>
#include <iostream>
#include <list>
#include <pthread.h>
#include <unistd.h>

using namespace std;

class HeapManager
{
public:
    int initHeap(int size)
    {
        myNode node;
        node.id = -1;
        node.size = size;
        node.idx = 0;
        list<myNode> newList;
        myList = newList;
        myList.push_back(node);
        print();
        return 1;
    }
    int myMalloc(int id, int size)
    {
        pthread_mutex_lock(&mut);
        int address;
        bool check = false;
        int idxNext;
        int sizeNext;
        for (auto it = myList.begin(); it != myList.end(); ++it)
        {
            if ((*it).id == -1 && ((*it).size > size || (*it).size == size))
            {
                check = true;
                if (it == myList.begin())
                {
                    int mySize = (*it).size;
                    myNode node;
                    node.id = id;
                    node.size = size;
                    node.idx = 0;
                    myList.insert(it, node); // new node before idx
                    it++;
                    myNode node2;
                    node2.id = -1;
                    node2.size = mySize - size;
                    node2.idx = size;
                    address = node.idx;
                    myList.pop_back();
                    myList.push_back(node2);
                    break;
                }
                else
                { // before.idx + before.size = after.idx
                    --it;
                    myNode beforeNode = (*it);
                    myNode node;
                    node.id = id;
                    node.size = size;
                    node.idx = beforeNode.idx + beforeNode.size;
                    it++;
                    myList.insert(it, node);
                    address = node.idx;
                    // it++;
                    myNode afterNode = (*it);
                    afterNode.id = (*it).id;
                    afterNode.idx = node.idx + node.size;
                    afterNode.size = (*it).size;
                    myList.insert(it, afterNode);
                    myList.remove(*it);
                    /*
                              it--;
                              int beforeIdx = (*it).idx;
                              int beforeSize = (*it).size;
                              it++;
                              for (auto it2 = it; it2 != myList.end(); ++it2)
                              {
                                (*it2).idx = beforeIdx + beforeSize;
                                beforeIdx = (*it2).idx;
                                beforeSize = (*it2).size;
                                break;
                              }
                              */
                }
                break;
            }
        }
        if (check)
        {
            cout << "Allocated for thread " << id << endl;
            print();
            myList = myList;
            pthread_mutex_unlock(&mut);
            return address;
        }
        else
        {
            cout << "Can not allocate, requested size " << size << " for thread " << id << " is bigger than remaining size" << endl;
            pthread_mutex_unlock(&mut);
            return -1;
        }
    }
    int myFree(int id, int idx)
    {
        pthread_mutex_lock(&mut);
        int index;
        bool check = false;
        for (auto it = myList.begin(); it != myList.end(); ++it)
        {
            if ((*it).id == id && (*it).idx == idx)
            {
                check = true;
                myNode node;
                myNode toBeRemoved = *it;
                node.id = -1;
                node.idx = (*it).idx;
                node.size = (*it).size;
                index = node.id;
                myList.insert(it, node);
                myList.remove(toBeRemoved);
                // now we will check left & right sides of the freed element
                auto itL = it, itR = it;
                int checkLeft, checkRight;
                bool ch3 = true, ch2 = true;
                for (auto it3 = myList.begin(); it3 != myList.end(); ++it3)
                {
                    if ((*it3).idx == (*it).idx && (*it3).size == (*it).size && (*it3).idx != -1)
                    {
                        if (ch3)
                        {
                            itL = --it3;
                            checkLeft = (*it3).id; // left
                        }
                        ch3 = false;
                    }
                }
                for (auto it2 = myList.begin(); it2 != myList.end(); ++it2)
                {
                    if ((*it2).idx == (*it).idx && (*it2).size == (*it).size && (*it2).idx != -1)
                    {
                        if (ch2)
                        {
                            itR = ++it2;
                            checkRight = (*it2).id;
                        }

                        ch2 = false;
                        // right
                    }
                }
                if (checkLeft == -1 && checkRight != -1)
                {
                    myNode nodeLeft = *itL;
                    myNode totalNode = node + nodeLeft;
                    myList.insert(itL, totalNode);
                    myList.remove(nodeLeft);
                    myList.remove(node);
                }
                else if (checkLeft != -1 && checkRight == -1)
                {
                    myNode nodeRight = *itR;
                    myNode totalNode = node + nodeRight;
                    myList.insert(itR, totalNode);
                    myList.remove(nodeRight);
                    myList.remove(node);
                }
                else if (checkLeft == -1 && checkRight == -1)
                {
                    myNode nodeLeft = *itL;
                    myNode totalNode = node + nodeLeft;
                    myList.insert(itL, totalNode);
                    myList.remove(nodeLeft);
                    myList.remove(node);
                    myNode nodeRight = *itR;
                    myNode totalNode2 = totalNode + nodeRight;
                    myList.insert(itR, totalNode2);
                    myList.remove(nodeRight);
                    myList.remove(totalNode);
                }
                break;
            }
        }
        if (check)
        {
            cout << "Freed for thread " << id << endl;
            print();
            pthread_mutex_unlock(&mut);
            return 1;
        }
        else
        {
            cout << "Can not free thread " << id << " with " << idx << endl;
            pthread_mutex_unlock(&mut);
            return -1;
        }
    }
    void print()
    {

        for (auto it = myList.begin(); it != myList.end(); ++it)
        {
            if (it == myList.begin())
                cout << "[" << (*it).id << "][" << (*it).size << "][" << (*it).idx << "]";
            else
                cout << "---[" << (*it).id << "][" << (*it).size << "][" << (*it).idx << "]";
        }
        cout << endl;
    }

private:
    struct myNode
    {
        int id;
        int size;
        int idx;

        bool operator==(myNode node)
        {
            if (id == node.id && size == node.size && idx == node.idx)
                return true;
            return false;
        }
        myNode operator+(myNode node)
        {
            myNode totalNode;
            totalNode.id = -1;
            totalNode.idx = node.idx > idx ? idx : node.idx;
            totalNode.size = node.size + size;
            return totalNode;
        }
    };
    list<myNode> myList;
    pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
};