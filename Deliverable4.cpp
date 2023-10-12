#include <iostream> 
#include <cmath>
using namespace std;

/**
 * @brief Point class definition 
 * Deliverable 3
 */
class Point{
    int x, y;
public:
//Default constructor 
Point(){
    x = 0; 
    y = 0;
}
//Constructure 
Point(int a, int b){
    x= a;
    y= b;
}
//Copy constructor 
Point(const Point & obj){
    this->x = obj.x;
    this->y = obj.y;
}
//Overload = operator - to assign an obj as another obj
void operator= (const Point &obj);
//Overload < operator - to compare an obj as another obj
bool operator<(const Point &obj);
//Overload > operator - to compare an obj as another obj
bool operator>(const Point &obj);
//Overload = operator - to compare an obj as another obj
bool operator==(const Point &obj){
    if (x==obj.x && y==obj.y) {return true;}
    else return false;
}
//Overload != operator - to compare an obj as another obj
bool operator!=(const Point &obj){
    if (x==obj.x && y==obj.y) {return false;}
    else return true;
}
//Overload string operator - turn obj to a string 
operator string(){
    string obj = "";
    obj = to_string(x) + " " + to_string(y);
    return obj;
}
//Overload the cout for easier print obj
friend ostream & operator<<(ostream& os, const Point& dt);
};

/**
 * @brief BinarySearchTree template class - array based implementation 
 * Deliverable 1
 * @tparam T 
 */
template <typename T> class BinarySearchTree{
private:  
    bool deleteSetUp (int i, T data){
        if(elementAt(i) == NULL_VAL) return false;
        if (data < array[i]){
            return deleteSetUp (2*i +1, data);
        }
        else if(data > array[i]){
            return deleteSetUp(2*i +2, data);
        }
        else {
            return deleteNode(i);
        }
    }
    T elementAt (int i) {
        if (i >= size) return NULL_VAL;
        else return array[i];
    }
    bool deleteNode (int i){
        int left = 2*i +1;
        int right = 2*i +2;
        //there are three cases - bottom level, has 1 child, and has 2 children 
        //I. bottom level 
        if ((elementAt(left) == NULL_VAL) && (elementAt(right) == NULL_VAL)){
            array[i] = NULL_VAL;
            return true;
        }
        //II. has 1 child 
        else if (elementAt(left) == NULL_VAL) { // has right child-> move right child up
        array[i] = elementAt(right); 
        return deleteNode(right);
        }
        else if (elementAt(right) == NULL_VAL) { // has left child-> move left child up
        array[i] = elementAt(left);
        return deleteNode(left);
        }
        else {//III. has 2 children 
        int preIndex = getPredecessor(left);
        array[i] = elementAt(preIndex);
        return deleteNode(preIndex);
        }
    return false;
    }
public: 
    int size, level; 
    T *array; 
    T NULL_VAL;
    int getPredecessor(int i);
    BinarySearchTree<T>(int l, T nullvalue){
        this->level = l;
        NULL_VAL= nullvalue;
        this->size = pow(2.0, (l+1)) -1;
        this->array = new T[this->size];
        for(int x =0; x < this->size; x++){
            array[x] = NULL_VAL;
        }
    }
    void reAllocate();
    void insert(T data){
        int currentIndex = 0;
        while (true){
            if( currentIndex >= this->size){
                reAllocate();
            }
            if (array[currentIndex] == NULL_VAL){
                array[currentIndex] = data;
                cout << "inserted item at " << currentIndex << " - "<< array[currentIndex] << endl;
                break;
            }
            else if (array[currentIndex] == data){
                cout << "there has been an error \n";
                break;
            }
            else if (array[currentIndex] < data){ // if data is larger than current node -> go right
                currentIndex = 2 * currentIndex +2;
            }
            else if (array[currentIndex] > data){ // if data is smaller than current node -> go left
                currentIndex = 2 * currentIndex +1;
            }
            }
    }
    void deleteElement (T data){
        if (this->isEmpty()){return;}
        deleteSetUp(0, data);
    }
    void ascending(){
       this->inOrder(0);
    }
    void descending(int index){
       if(index >= size) return;
       if(array[index] != NULL_VAL){
        descending(2*index+2);
        cout << array[index] << "\t";
        descending(2*index+1);
       }
    }
    void inOrder(int currentIndex){
        if (this->isEmpty()){return;}
        if (currentIndex >= size) return;
        if(array[currentIndex] != NULL_VAL){ //if index is not empty
            inOrder(2*currentIndex+1);
            cout << array[currentIndex] << "\t";
            inOrder(2*currentIndex+2);
        }
    }
    void preOrder(int currentIndex){
        if (this->isEmpty()){return;}
        if (currentIndex >= size) return;
        if(array[currentIndex] != NULL_VAL){
            cout << array[currentIndex] << "\t";
            preOrder(2*currentIndex+1);
            preOrder(2*currentIndex+2);
        }
    }
    void postOrder(int currentIndex){
        if (this->isEmpty()){return;}
        if (currentIndex >= size) return;
        if(array[currentIndex] != NULL_VAL){
            postOrder(2*currentIndex+1);
            postOrder(2*currentIndex+2);
            cout << array[currentIndex] << "\t";
        }
    }
    bool search(T data){
        if (this->isEmpty()){return false;}
        int index = 0;
        bool flag = false;
        while (index < size && flag == false){
           if (array[index] == data){
            flag = true;
           }
           else if (array[index] < data){
            index = 2*index+2;  // go right child
           }
           else if (array[index] > data){
            index = 2*index+1; // go left child
           }
        }
        return flag;
    }
    //this shows node counts. or shows taken spots. 
    int countNodes(int currentIndex){
        int count = 0;
        while(true){
        if (currentIndex >= size) {return count;}
        if(array[currentIndex] != NULL_VAL){
            count++;
        }
        currentIndex++;
        }
        return count;
    }
    T predecessor(int index){ // one step left and then right till null
    
        int right = 2* index +1;
        while (elementAt(right) != NULL_VAL){
            index = right;
            right = 2* index +2;
        }
        return array[index];
    }
    T successor(int index){ // one step right and then left till null
        int left = 2* index +2;
        while (elementAt(left) != NULL_VAL){
            index = left;
            left = 2* index +1;
        }
        return array[index];
    }
    T maximum(){
        int right = 0;
        int comp = 2* right +2;
        while (elementAt(comp) != NULL_VAL){
        right = comp;
        comp = 2* right +2;
    }
    return array[right];
    }
    T minimum(){
        int left = 0;
        int comp = 2* left +1;
        while (elementAt(comp) != NULL_VAL){
        left = comp;
        comp = 2* left +1;
    }
    return array[left];
    }
    int size_arr(){return this->size;}
    bool isEmpty(){
        int index = 0;
        if (array[index] == NULL_VAL) return true;
        return false;
    }
    BinarySearchTree(const BinarySearchTree &obj);
};

int main(){
    Point null(100045,100045);
    Point point1 (2,3);
    Point point2 (1,2);
    Point point3 (0,1);
    Point point4 (1,3);
    Point point5 (3,4);
    Point point6 (3,3);
    Point point7 (3,5);
    BinarySearchTree<Point> pointCollection(2, null);
    cout <<"\nDeliverable 4a\n";
    pointCollection.insert(point1);
    pointCollection.insert(point2);
    pointCollection.insert(point3);
    pointCollection.insert(point4);
    pointCollection.insert(point5);
    pointCollection.insert(point6);
    pointCollection.insert(point7);
    BinarySearchTree<Point> myPointCollection(pointCollection);
    cout << "\n\nDeliverable 4b\nIn order: ";
    pointCollection.inOrder(0);
    cout << "\n\nDeliverable 4c\nIn order - myPointCollection";
    myPointCollection.inOrder(0);
    cout << "\n\nDeliverable 4d";
    Point find_val1 (1,2);
    cout << "\nmyPointCollection does contain (1,2) - " << boolalpha<< myPointCollection.search(find_val1) << endl;
    Point find_val2 (7,2);
    cout << "myPointCollection does contain (7,2) - " << boolalpha<< myPointCollection.search(find_val2) << endl;
    myPointCollection.deleteElement(find_val1);
    cout << "\nDeliverable 4e\nAfter deleting (1,2) - ";
    myPointCollection.inOrder(0);
    cout << endl << "\nDeliverable 4f\n - predecessor & successor" <<myPointCollection.predecessor(0)  <<  myPointCollection.successor(0);
    cout << "\n\nDeliverable 4g\nCurrent node count is " <<pointCollection.countNodes(0) <<endl; 
    cout << "Node size is " <<pointCollection.size <<endl; 
    cout << "Max node is " <<pointCollection.maximum() <<endl; 
    cout << "Min node is " <<pointCollection.minimum() <<endl; 
    cout << "\nDeliverable 4h\n Ascending Order: \t ";
    pointCollection.ascending();
    cout << "\nDeliverable 4h\n Descending Order: \t";
    pointCollection.descending(0);

}
/**
 * @brief Function reAllocate in class BinarySearchTree 
 * Deliverable 2
 * @tparam T 
 */
template <typename T> 
void BinarySearchTree<T>::reAllocate(){
    this->level = this->level +1;
    int tempSize = pow(2.0, level+1) -1;
    T *tempArray = new T [tempSize];
    for (int i = 0; i< tempSize; i++){
        tempArray[i] = this->array[i];
    }
    for (int i = size; i< tempSize; i++){
        tempArray[i] = NULL_VAL;
    }
    delete [] (this->array);
    this->array = nullptr;
    this->array = tempArray;
    this->size = tempSize;
}
template <typename T> 
int BinarySearchTree<T>::getPredecessor(int i){ // one step left and then right till null
    int right = 2* i +1;
    while (elementAt(right) != NULL_VAL){
        i = right;
        right = 2* i +2;
    }
    return i;
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree &obj){
    this->size = obj.size;
    this->level = obj.level;
    this->NULL_VAL = obj.NULL_VAL;
    this->array = obj.array;
}
ostream& operator<<(ostream& os, const Point& dt){
    os << dt.x << " " << dt.y << "\t";
    return os;
}
void Point::operator= (const Point &obj){
    this->x = obj.x;
    this->y = obj.y;
}
bool Point::operator<(const Point &obj){
    if (x<obj.x) return true;
    else if (x ==obj.x){return y<obj.y;}
    else return false;
}
bool Point::operator>(const Point &obj){
    if (x>obj.x) return true;
    else if (x ==obj.x){return y>obj.y;}
    else return false;
}