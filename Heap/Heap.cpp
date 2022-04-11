//Adam Elkhanoufi
//Programing assignment 1
//02/14/2022

#include <iostream>
#include <fstream>
using namespace std;

const int MAX_ARRAY_SIZE = 100;
int arr[MAX_ARRAY_SIZE];
int heapSize = -1;

void sinkDown(int, int, int);  // function that moves a node down the tree until it satisifies heap properties
void insert(int, int);  // insert a node to the heap
void decreaseKey(int, int, int); // Decrease Key of the element at array position x to value y
void floatUp(int, int); // function that moves a node up the tree until it satisifies heap properties
void extractMin(int); // //If extractMin is the last instruction remove and print the root node if its not the last then just remove root node


int main()
{
    ifstream f("inputFile.txt");
    string instruction;

    int k = 3;
    int index;
    int val;
    int numOfInstructions;
    int currentInstruction = 0;
    
    //Reads in the value of total instructions in the first line of inputFile
    f >> numOfInstructions;

    //Looping through each line of the inputFile while reading the command
    while (f >> instruction)
    {
        //With every loop increment currentInstruction
        currentInstruction++;

        //Check for each possible instruction and read the next value or values to use as parameters to their appropriate functions
        if (instruction == "IN")
        {
            f >> val;
            insert(val, k);
        }

        if (instruction == "DK")
        {
            f >> index;
            f >> val;
            decreaseKey(index, val, k);
        }

        ////Once the counter has counted to the totalNumber of lines so make sure to output the root element before "EM"
        //if (currentInstruction == numOfInstructions)
        //{
        //    cout << arr[0] << endl;
        //}

        if (instruction == "EM" && currentInstruction == numOfInstructions)
        {
            cout << arr[0] << endl;
            extractMin(k);
        }
        else if (instruction == "EM")
        {
            extractMin(k);
        }
    }
    return 0;
}

void sinkDown(int root, int bottom, int k)
{
    //Initialize all children node variables and their positions 
    int minChild = 0;
    int leftNode = root * k + 1;
    int midNode = root * k + 2;
    int rightNode = root * k + 3;

    if (leftNode > bottom)
    {
        return;
    }
    else if (leftNode <= bottom)
    {
        //Checking all possible scenarios with a 3-ary heap and its children inf order to find minChild
        minChild = (arr[midNode] < arr[rightNode]) ? midNode : rightNode;
        minChild = (arr[leftNode] < arr[minChild]) ? leftNode : minChild;
    }

    swap(arr[root], arr[minChild]);

    //If minChild is not the root you recurisvely call SinkDown
    if (root != minChild)
    {
        sinkDown(minChild, bottom, k);
    }
}

void heapify(int k)
{
    for (int i = heapSize / k; i >= 0; i--)
    {
        sinkDown(i, heapSize - 1, k);
    }
    //Code for heapify
}

void printArr()
{
    for (int i = 0; i <= heapSize; i++)
    {
        cout << arr[i] << " ";
    }
}

void heapSort(int k)
{
    heapify(k);

    for (int end = heapSize - 1; end > 0; end--)
    {
        swap(arr[end], arr[0]);
        sinkDown(0, end - 1, k);
    }
}

void floatUp(int index, int k)
{
    //Initialize the parents position compared to the index's position
    int parent = (index - 1) / k;
    
    //Check to see if index reached the root position
    if (index == 0)
    {
        return;
    }
    else if(arr[index] < arr[parent])
    {
        //Swap if the index's value is less than the parent's value and recursively call float up
        swap(arr[index], arr[parent]);
        floatUp(parent, k);
    }
}

void insert(int newElement, int k)
{
    //Set the new added element to the bottom of the heap 
    arr[++heapSize] = newElement;

    //Float the newValue up until it's position obeys heap properties
    floatUp(heapSize, k);
}

void decreaseKey(int index, int newValue, int k)
{
    //Set the element at the given index to the value we decrease to
    arr[index] = newValue;

    //Float the newValue up until it's position obeys heap properties
    floatUp(index, k);

    //Decrease the key
}

void extractMin(int k)
{
    //Set root to the last element in the heap and decrementing heapsize after
    arr[0] = arr[heapSize--];

    //Sink the new root element down until it's position obeys all heap properties
    sinkDown(0, heapSize - 1, k);
}