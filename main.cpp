/* Alunos: Lucas da Silva Lima, Nicolas Fernandes de Lima */
#include <iostream>
using namespace std;
template <typename Type>
class Node{
private:
  Type item;
  Node<Type> * left , * right;
  int balanceFactor, counter;
public:
  Node(){
    left = right = NULL;
  }
  Node(Type item){
    this->item = item;
    left = right = NULL;
  }

  Type getItem(){
    return item;
  }
  void setItem(Type item){
    this->item = item;
  }
  Node<Type> *& getLeft(){
    return left;
  }
  void setLeft(Node<Type> * left){
    this->left = left;
  }
  Node<Type> *& getRight(){
    return right;
  }
  void setRight(Node<Type> * right){
    this->right = right;
  }
  int getBalanceFactor(){
    return balanceFactor;
  }
  void setBalanceFactor(int balanceFactor){
    this->balanceFactor = balanceFactor;
  }
  int getCounter(){
    return counter;
  }
  void setCounter(int counter){
    this->counter = counter;
  }
};

template<typename Type>
class AVLTree{
private:
  Node<Type> * root;
  bool height;
  void insert(Type &, Node<Type> *&, bool);
  void remove(Type &, Node<Type> *&);
  void removeAux(Node<Type> *&, Node<Type> *&);
  Type search(Type &, Node<Type> *&);
  void inOrderTreeWalk(Node<Type> *&);
  void rightrightRotation(Node<Type> *&,Node<Type> *&);
  void leftleftRotation(Node<Type> *&,Node<Type> *&);
  void doubleRightLeftRotation(Node<Type> *&,Node<Type> *&,Node<Type> *&);
  void doubleLeftRightRotation(Node<Type> *&,Node<Type> *&,Node<Type> *&);
  void insertObject(Type &, Node<Type> *&, bool);
  void removeObject(Type &, Node<Type> *&);
  Type searchObject(string &, Node<Type> *&);

public:
  AVLTree(){
    root = NULL;
  }
  Node<Type> * getRoot(){
    return root;
  }
  void setRoot(Node<Type> * root){
    this->root = root;
  }
  void insert(Type);
  void remove(Type);
  Type search(Type);
  void inOrderTreeWalk();
  bool emptyTree();
  Type rootItem();

  void insertObject(Type);
  void removeObject(Type);
  Type searchObject(string);

};

template<typename Type>
Type AVLTree<Type>::rootItem(){
  return getRoot()->getItem();
}

template<typename Type>
bool AVLTree<Type>::emptyTree(){
  return root == NULL;
}

template<typename Type>
Type AVLTree<Type>::search(Type item){
  return search(item,root);
}

template<typename Type>
Type AVLTree<Type>::search(Type & item, Node<Type> *& pointer){
  if(pointer == NULL){
    return "";
  }
  else if((item) > (pointer->getItem())){
    return search(item, pointer->getRight());
  }
  else if((item) < (pointer->getItem())){
    return search(item, pointer->getLeft());
  }
  return pointer->getItem();
}

template<typename Type>
void AVLTree<Type>::inOrderTreeWalk(){
  inOrderTreeWalk(root);
  cout << endl;
}


template<typename Type>
void AVLTree<Type>::inOrderTreeWalk(Node<Type> *& pointer){
  if(pointer != NULL){
    inOrderTreeWalk(pointer->getLeft());
    cout << pointer->getItem() << " ";
    inOrderTreeWalk(pointer->getRight());
  }
}

template<typename Type>
void AVLTree<Type>::insert(Type item){
  insert(item, root, height);
}

template<typename Type>
void AVLTree<Type>::insert(Type & item, Node<Type> *& pointer, bool height){
  Node<Type> * pointer1, * pointer2;
  if(pointer == NULL){
    pointer = new Node<Type>(item);
    height = true;
    pointer->setBalanceFactor(0);
    pointer->setCounter(1);
  }
  else if(pointer->getItem() > item){
    insert(item,pointer->getLeft(),height);
    if(height){
      if(pointer->getBalanceFactor() == 1){
        pointer->setBalanceFactor(0);
        height = false;
      }
      else if(pointer->getBalanceFactor() == 0){
        pointer->setBalanceFactor(-1);
      }
      else{
        pointer1 = pointer->getLeft();
        if(pointer1->getBalanceFactor() == -1){
          leftleftRotation(pointer,pointer1);
        }
        else{
          pointer2 = pointer1->getRight();
          doubleLeftRightRotation(pointer,pointer1,pointer2);
        }
        pointer->setBalanceFactor(0);
        height = false;
      }
    }
  }
  else if(pointer->getItem() < item){
    insert(item,pointer->getRight(),height);
    if(height){
      if(pointer->getBalanceFactor() == -1){
        pointer->setBalanceFactor(0);
        height = false;
      }
      else if(pointer->getBalanceFactor() == 0){
        pointer->setBalanceFactor(1);
      }
      else{
        pointer1 = pointer->getRight();
        if(pointer1->getBalanceFactor() == 1){
          rightrightRotation(pointer,pointer1);
        }
        else{
          pointer2 = pointer1->getLeft();
          doubleRightLeftRotation(pointer,pointer1,pointer2);
        }
        pointer->setBalanceFactor(0);
        height = false;
      }
    }
  }
  else{
    pointer->setCounter(pointer->getCounter() + 1);
  }
}

template<typename Type>
void AVLTree<Type>::remove(Type item){
  remove(item, root);
}

template<typename Type>
void AVLTree<Type>::remove(Type & item, Node<Type> *& pointer){
  Node<Type> * aux = pointer;
  if(pointer == NULL){
    cout << "Error: item aren't in tree !" << endl;
  }
  else if((item) < (pointer->getItem())){
    remove(item, pointer->getLeft());
  }
  else if((item) > (pointer->getItem())){
    remove(item, pointer->getRight());
  }
  else if(pointer->getRight() == NULL){
    pointer = pointer->getLeft();
    delete aux;
  }
  else if(pointer->getLeft() == NULL){
    pointer = pointer->getRight();
    delete aux;
  }
  else{
    removeAux(pointer, pointer->getLeft());
  }
}

template<typename Type>
void AVLTree<Type>::removeAux(Node<Type> *& pointer, Node<Type> *& pointerLeft){
  if(pointerLeft->getRight() != NULL){
    removeAux(pointer, pointerLeft->getRight());
  }
  else{
    pointer->setItem(pointerLeft->getItem());
    pointerLeft = pointerLeft->getLeft();
  }
}

template<typename Type>
void AVLTree<Type>::leftleftRotation(Node<Type> *& pointer, Node<Type> *& pointer1){
  pointer->setLeft(pointer1->getRight());
  pointer1->setRight(pointer);
  pointer->setBalanceFactor(0);
  pointer = pointer1;
}
template<typename Type>
void AVLTree<Type>::rightrightRotation(Node<Type> *& pointer, Node<Type> *& pointer1){
  pointer->setRight(pointer1->getLeft());
  pointer1->setLeft(pointer);
  pointer->setBalanceFactor(0);
  pointer = pointer1;
}
template<typename Type>
void AVLTree<Type>::doubleLeftRightRotation(Node<Type> *& pointer, Node<Type> *& pointer1 , Node<Type> *& pointer2){
  pointer1->setRight(pointer2->getLeft());
  pointer2->setLeft(pointer1);
  pointer->setLeft(pointer2->getRight());
  pointer2->setRight(pointer);
  if(pointer2->getBalanceFactor() == -1){
    pointer->setBalanceFactor(1);
  }
  else{
    pointer->setBalanceFactor(0);
  }
  if(pointer2->getBalanceFactor() == 1){
    pointer1->setBalanceFactor(-1);
  }
  else{
    pointer1->setBalanceFactor(0);
  }
  pointer = pointer2;
}
template<typename Type>
void AVLTree<Type>::doubleRightLeftRotation(Node<Type> *& pointer, Node<Type> *& pointer1, Node<Type> *& pointer2){
  pointer1->setLeft(pointer2->getRight());
  pointer2->setRight(pointer1);
  pointer->setRight(pointer2->getLeft());
  pointer2->setLeft(pointer);
  if(pointer2->getBalanceFactor() == 1){
    pointer->setBalanceFactor(-1);
  }
  else{
    pointer->setBalanceFactor(0);
  }
  if(pointer2->getBalanceFactor() == -1){
    pointer1->setBalanceFactor(1);
  }
  else{
    pointer1->setBalanceFactor(0);
  }
  pointer = pointer2;
}

template<typename Type>
Type AVLTree<Type>::searchObject(string item){
  return searchObject(item,root);
}

template<typename Type>
Type AVLTree<Type>::searchObject(string & item, Node<Type> *& pointer){
  if(pointer == NULL){
    return 0;
  }
  else if((item) > (pointer->getItem().getNameTable())){
    return searchObject(item, pointer->getRight());
  }
  else if((item) < (pointer->getItem().getNameTable())){
    return searchObject(item, pointer->getLeft());
  }
  return pointer->getItem();
}


template<typename Type>
void AVLTree<Type>::insertObject(Type item){
  insertObject(item, root, height);
}
template<typename Type>
void AVLTree<Type>::insertObject(Type & item, Node<Type> *& pointer, bool height){
  Node<Type> * pointer1, * pointer2;
  if(pointer == NULL){
    pointer = new Node<Type>(item);
    height = true;
    pointer->setBalanceFactor(0);
    pointer->setCounter(1);
  }
  else if(pointer->getItem().getNameTable() > item.getNameTable()){
    insertObject(item,pointer->getLeft(),height);
    if(height){
      if(pointer->getBalanceFactor() == 1){
        pointer->setBalanceFactor(0);
        height = false;
      }
      else if(pointer->getBalanceFactor() == 0){
        pointer->setBalanceFactor(-1);
      }
      else{
        pointer1 = pointer->getLeft();
        if(pointer1->getBalanceFactor() == -1){
          leftleftRotation(pointer,pointer1);
        }
        else{
          pointer2 = pointer1->getRight();
          doubleLeftRightRotation(pointer,pointer1,pointer2);
        }
        pointer->setBalanceFactor(0);
        height = false;
      }
    }
  }
  else if(pointer->getItem().getNameTable() < item.getNameTable()){
    insertObject(item,pointer->getRight(),height);
    if(height){
      if(pointer->getBalanceFactor() == -1){
        pointer->setBalanceFactor(0);
        height = false;
      }
      else if(pointer->getBalanceFactor() == 0){
        pointer->setBalanceFactor(1);
      }
      else{
        pointer1 = pointer->getRight();
        if(pointer1->getBalanceFactor() == 1){
          rightrightRotation(pointer,pointer1);
        }
        else{
          pointer2 = pointer1->getLeft();
          doubleRightLeftRotation(pointer,pointer1,pointer2);
        }
        pointer->setBalanceFactor(0);
        height = false;
      }
    }
  }
  else{
    pointer->setCounter(pointer->getCounter() + 1);
  }
}

template<typename Type>
void AVLTree<Type>::removeObject(Type item){
  removeObject(item, root);
}

template<typename Type>
void AVLTree<Type>::removeObject(Type & item, Node<Type> *& pointer){
  Node<Type> * aux = pointer;
  if(pointer == NULL){
    cout << "Error: item aren't in tree !" << endl;
  }
  else if((item.getNameTable()) < (pointer->getItem().getNameTable())){
    removeObject(item, pointer->getLeft());
  }
  else if((item.getNameTable()) > (pointer->getItem().getNameTable())){
    removeObject(item, pointer->getRight());
  }
  else if(pointer->getRight() == NULL){
    pointer = pointer->getLeft();
    delete aux;
  }
  else if(pointer->getLeft() == NULL){
    pointer = pointer->getRight();
    delete aux;
  }
  else{
    removeAux(pointer, pointer->getLeft());
  }
}

template<typename Type>
class HashTable{
private:
  unsigned long int extent;
  AVLTree<Type> * collisionTree;
  string nameTable;
public:
  unsigned long int getExtent(){
    return extent;
  }
  void setExtent(unsigned long int extent){
    this->extent = extent;
  }
  AVLTree<Type> *getCollisionTree(){
    return collisionTree;
  }
  void setCollisionTree(AVLTree<Type> * collisionTree){
    this->collisionTree = collisionTree;
  }
  string getNameTable(){
    return nameTable;
  }
  void setNameTable(string nameTable){
    this->nameTable = nameTable;
  }
  HashTable(){
    extent = 0;
    nameTable = "";
    collisionTree = new AVLTree<Type>[getExtent()];
  }
  HashTable(int);
  void insertTable(Type);
  unsigned long int searchTable(Type);
  void removeTable(Type);
  void printTable();
  unsigned long int powerTable(unsigned long int, int);
  unsigned long int hashing(string);
  bool emptyHashTable();
};

template<typename Type>
bool HashTable<Type>::emptyHashTable(){
  int verifyEmptyStrings = 0;
  for(int i = 0 ; i < (int)getExtent(); i++){
    if(!collisionTree[i].emptyTree()){
      verifyEmptyStrings = 1;
    }
  }
  return ((verifyEmptyStrings == 0)? true : false);
}

template<typename Type>
HashTable<Type>::HashTable(int extent){
  this->extent = extent;
  collisionTree = new AVLTree<Type>[extent];
}

template<typename Type>
unsigned long int HashTable<Type>::powerTable(unsigned long int base, int exponent){
  unsigned long int acumulator = 1;
  for(int i = 0; i < exponent; i ++){
    acumulator *= base;
    acumulator %= getExtent();
  }
  return acumulator;
}

template<typename Type>
unsigned long int HashTable<Type>::hashing(string key){
  int extentKey = 0, exponent;
  unsigned long int saveHashValue = 0;
  extentKey = (int)(key.size());
  exponent = extentKey;
  const unsigned long int BASE = powerTable(10,9)+7;
  for(int i = 0; i < extentKey; i++){
    exponent--;
    saveHashValue += ((int)(tolower(key[i])) * powerTable(BASE,exponent))%getExtent();
  }
  return saveHashValue%getExtent();
}

template<typename Type>
void HashTable<Type>::insertTable(Type item){
  unsigned long int position;
  position = hashing(item);
  collisionTree[position].insert(item);
}

template<typename Type>
unsigned long int HashTable<Type>::searchTable(Type item){
  unsigned long int position;
  position = hashing(item);
  return position;
}

template<typename Type>
void HashTable<Type>::removeTable(Type item){
  int positionItem = searchTable(item);
  collisionTree[positionItem].remove(item);
}

template<typename Type>
void HashTable<Type>::printTable(){
    cout << "TABELA" << endl;
    for (int i = 0; i < getExtent(); i ++){
      cout << "item " << i << endl;
      collisionTree[i].inOrderTreeWalk();
      cout << endl;
    }
}

bool cousin(int number){
  int counter = 0;
  for(int i = 2; i * i <= number; i++){
    if(number % i == 0){
      counter++;
    }
  }
  return (counter==0)? true : false;
}

int biggerCousin(int number){
  int saveCousin;
  for(int i = number; i > 0; i--){
    if(cousin(i)){
      saveCousin = i;
      break;
    }
  }
  return saveCousin;
}
void createHashTables(AVLTree<HashTable<string>> * kinojoTree){
  string nameTable, equalsSymbol, dot;
  int amountKey;
  cin >> nameTable >> equalsSymbol >> amountKey;
  int saveCousin = biggerCousin((int)amountKey/4);
  HashTable<string> * kinojoTable = new HashTable<string>(saveCousin);
  kinojoTable->setNameTable(nameTable);
  for(int i = 0 ; i < amountKey; i++){
    string key;
    cin >> key;
    kinojoTable->insertTable(key);
  }
  cin >> dot;
  kinojoTree->insertObject(*kinojoTable);
}

HashTable<string> * boothEmptyTable(HashTable<string> * table1, HashTable<string> * table2){
  return ((table1->getExtent() <= table2->getExtent())? table1 : table2);
}

HashTable<string> * resultUnionTable(AVLTree<HashTable<string>> * kinojoTree, HashTable<string> * table1, HashTable<string> * table2){
  int resultExtent = biggerCousin(table1->getExtent() + table2->getExtent());
  HashTable<string> * aux1 = new HashTable<string>(table1->getExtent());
  HashTable<string> * aux2 = new HashTable<string>(table2->getExtent());
  aux1->setNameTable(table1->getNameTable());
  aux2->setNameTable(table2->getNameTable());
  HashTable<string> * unionTable = new HashTable<string>(resultExtent);
  for(int i = 0; i < (int)table1->getExtent(); i++){
    if(!table1->getCollisionTree()[i].emptyTree()){
      while(!table1->getCollisionTree()[i].emptyTree()){
        string saveKey;
        saveKey = table1->getCollisionTree()[i].rootItem();
        unionTable->insertTable(saveKey);
        aux1->insertTable(saveKey);
        table1->getCollisionTree()[i].remove(saveKey);
      }
    }
  }
  for(int i = 0; i < (int)table2->getExtent(); i++){
    if(!table2->getCollisionTree()[i].emptyTree()){
      while(!table2->getCollisionTree()[i].emptyTree()){
        string saveKey;
        saveKey = table2->getCollisionTree()[i].rootItem();
        unionTable->insertTable(saveKey);
        aux2->insertTable(saveKey);
        table2->getCollisionTree()[i].remove(saveKey);
      }
    }
  }
  kinojoTree->removeObject(*table1);
  kinojoTree->removeObject(*table2);
  kinojoTree->insertObject(*aux1);
  kinojoTree->insertObject(*aux2);
  delete table1;
  delete table2;
  delete aux1;
  delete aux2;
  return unionTable;
}

void unionHashTables(AVLTree<HashTable<string>> * kinojoTree){
  string newName, equalsSymbol, nameTable1, nameTable2;
  cin >> newName >> equalsSymbol >> nameTable1 >> nameTable2;
  HashTable<string> * aux1 = new HashTable<string>();
  HashTable<string> * aux2 = new HashTable<string>();
  *aux1 = kinojoTree->searchObject(nameTable1);
  *aux2 = kinojoTree->searchObject(nameTable2);
  HashTable<string> * unionTable = new HashTable<string>();

  if(!aux1->emptyHashTable() && aux2->emptyHashTable()){
    unionTable = aux1;
    unionTable->setNameTable(newName);
    kinojoTree->insertObject(*unionTable);
  }
  else if(!aux2->emptyHashTable() && aux1->emptyHashTable()){
    unionTable = aux2;
    unionTable->setNameTable(newName);
    kinojoTree->insertObject(*unionTable);
  }
  else if(!aux1->emptyHashTable() && !aux2->emptyHashTable()){
    unionTable = resultUnionTable(kinojoTree,aux1,aux2);
    unionTable->setNameTable(newName);
    kinojoTree->insertObject(*unionTable);
  }
  else if (aux2->emptyHashTable() && aux1->emptyHashTable()){
    unionTable = boothEmptyTable(aux1, aux2);
    unionTable->setNameTable(newName);
    kinojoTree->insertObject(*unionTable);
  }
}

int smallerSize(HashTable<string> * table1, HashTable<string> * table2){
  return ((table1->getExtent() <= table2->getExtent())? table1->getExtent() : table2->getExtent());
}

HashTable<string> * resultIntersectionTable(AVLTree<HashTable<string>> * kinojoTree, HashTable<string> * table1, HashTable<string> * table2){
  HashTable<string> * intersectionTable = new HashTable<string>(smallerSize(table1,table2));
  HashTable<string> * aux1 = new HashTable<string>(table1->getExtent());
  aux1->setNameTable(table1->getNameTable());
  for(int i = 0; i < (int)table1->getExtent(); i++){
    if(!table1->getCollisionTree()[i].emptyTree()){
      while(!table1->getCollisionTree()[i].emptyTree()){
        string saveKey = table1->getCollisionTree()[i].rootItem();
        int savePositionKey = table2->searchTable(saveKey);
        aux1->insertTable(saveKey);
        table1->getCollisionTree()[i].remove(saveKey);
        if(saveKey == table2->getCollisionTree()[savePositionKey].search(saveKey)){
          intersectionTable->insertTable(saveKey);
        }
      }
    }
  }
  kinojoTree->removeObject(*table1);
  kinojoTree->insertObject(*aux1);
  delete aux1;
  delete table1;
  return intersectionTable;
}

void interHashTables(AVLTree<HashTable<string>> * kinojoTree){
  string newName, equalsSymbol, nameTable1, nameTable2;
  cin >> newName >> equalsSymbol >> nameTable1 >> nameTable2;
  HashTable<string> * aux1 = new HashTable<string>();
  HashTable<string> * aux2 = new HashTable<string>();
  *aux1 = kinojoTree->searchObject(nameTable1);
  *aux2 = kinojoTree->searchObject(nameTable2);
  HashTable<string> * intersectionTable = new HashTable<string>(smallerSize(aux1,aux2));

  if(!aux1->emptyHashTable() && aux2->emptyHashTable()){
    intersectionTable->setExtent(smallerSize(aux1,aux2));
    intersectionTable->setNameTable(newName);
    kinojoTree->insertObject(*intersectionTable);
  }
  else if(!aux2->emptyHashTable() && aux1->emptyHashTable()){
    intersectionTable->setExtent(smallerSize(aux1,aux2));
    intersectionTable->setNameTable(newName);
    kinojoTree->insertObject(*intersectionTable);
  }
  else if(!aux1->emptyHashTable() && !aux2->emptyHashTable()){
    intersectionTable = resultIntersectionTable(kinojoTree,aux1,aux2);
    intersectionTable->setNameTable(newName);
    kinojoTree->insertObject(*intersectionTable);
  }
  else if (aux2->emptyHashTable() && aux1->emptyHashTable()){
    intersectionTable = boothEmptyTable(aux1, aux2);
    intersectionTable->setNameTable(newName);
    kinojoTree->insertObject(*intersectionTable);
  }
}

HashTable<string> * copyMinusTable(AVLTree<HashTable<string>> * kinojoTree, HashTable<string> * table, int newExtent){
  HashTable<string> * minusTable = new HashTable<string>(newExtent);
  HashTable<string> * aux = new HashTable<string>(table->getExtent());
  aux->setNameTable(table->getNameTable());
  for(int i = 0 ; i < (int)table->getExtent(); i++){
    if(!table->getCollisionTree()[i].emptyTree()){
      while(!table->getCollisionTree()[i].emptyTree()){
        string saveKey = table->getCollisionTree()[i].rootItem();
        minusTable->insertTable(saveKey);
        aux->insertTable(saveKey);
        table->getCollisionTree()[i].remove(saveKey);
      }
    }
  }
  kinojoTree->removeObject(*table);
  kinojoTree->insertObject(*aux);
  delete table;
  delete aux;
  return minusTable;
}

HashTable<string> * resultMinusTable(AVLTree<HashTable<string>> * kinojoTree, HashTable<string> * table1, HashTable<string> * table2, int newExtent){
  HashTable<string> * aux1 = new HashTable<string>(table1->getExtent());
  aux1->setNameTable(table1->getNameTable());
  HashTable<string> * minusTable = new HashTable<string>(newExtent);
  for(int i = 0; i < (int)table1->getExtent(); i++){
    if(!table1->getCollisionTree()[i].emptyTree()){
      while(!table1->getCollisionTree()[i].emptyTree()){
        string saveKey = table1->getCollisionTree()[i].rootItem();
        int savePositionKey = table2->searchTable(saveKey);
        aux1->insertTable(saveKey);
        table1->getCollisionTree()[i].remove(saveKey);
        if(saveKey != table2->getCollisionTree()[savePositionKey].search(saveKey)){
          minusTable->insertTable(saveKey);
        }
      }
    }
  }
  kinojoTree->removeObject(*table1);
  kinojoTree->insertObject(*aux1);
  delete aux1;
  delete table1;
  return minusTable;
}

int subtraction(int number1, int number2){
  return (number1-number2);
}

void minusHashTable(AVLTree<HashTable<string>> * kinojoTree){
  string nameTable, equalsSymbol, nameTable1, nameTable2, dot;
  cin >> nameTable >> equalsSymbol >> nameTable1 >> nameTable2 >> dot;
  HashTable<string> * aux1 = new HashTable<string>();
  HashTable<string> * aux2 = new HashTable<string>();
  *aux1 = kinojoTree->searchObject(nameTable1);
  *aux2 = kinojoTree->searchObject(nameTable2);
  int mathOperation = subtraction(aux1->getExtent(),aux2->getExtent());
  int resultExtent = biggerCousin(mathOperation);
  HashTable<string> * minusTable = new HashTable<string>();
  if(mathOperation < 2){
    cout << "Operacao invalida" << endl;
  }
  else{
    if(!aux1->emptyHashTable() && aux2->emptyHashTable()){
      minusTable = copyMinusTable(kinojoTree, aux1, resultExtent);
      minusTable->setNameTable(nameTable);
      kinojoTree->insertObject(*minusTable);
    }
    else if(aux1->emptyHashTable() && !aux2->emptyHashTable()){
      minusTable = copyMinusTable(kinojoTree,aux1,resultExtent);
      minusTable->setNameTable(nameTable);
      kinojoTree->insertObject(*minusTable);
    }
    else if(!aux1->emptyHashTable() && !aux2->emptyHashTable()){
      minusTable = resultMinusTable(kinojoTree,aux1,aux2, resultExtent);
      minusTable->setNameTable(nameTable);
      kinojoTree->insertObject(*minusTable);
    }
    else if (aux2->emptyHashTable() && aux1->emptyHashTable()){
      minusTable = new HashTable<string>();
      minusTable->setNameTable(nameTable);
      kinojoTree->insertObject(*minusTable);
    }
  }
}

void printCommand(AVLTree<HashTable<string>> * kinojoTree){
  string nameTable, keyCaracter, key, dot;
  int savePositionKey = 0;
  cin >> nameTable >> keyCaracter >> key >> dot;
  HashTable<string> * aux = new HashTable<string>();
  *aux = kinojoTree->searchObject(nameTable);
  if(!aux->emptyHashTable()){
    savePositionKey = aux->searchTable(key);
    string saveName = aux->getCollisionTree()[savePositionKey].search(key);
    if(saveName == key){
      aux->getCollisionTree()[savePositionKey].inOrderTreeWalk();
    }
    else{
      cout << "Chave " << key << " nao encontrada em Tabela " << nameTable << endl;
    }
  }
  else if(aux->emptyHashTable()){
    cout << "Tabela " << nameTable << " vazia" << endl;
  }
  delete aux;
}

class Input{
private:
  string in;
  AVLTree<HashTable<string>> * kinojoTree = new AVLTree<HashTable<string>>();
public:
  void finalInput();
};
void Input::finalInput(){
  while((cin >> in) && (in != "FIM")){
    if(in == "TH"){
      createHashTables(kinojoTree);
    }
    else if(in == "UNION"){
      unionHashTables(kinojoTree);
    }
    else if(in == "INTER"){
      interHashTables(kinojoTree);
    }
    else if(in == "MINUS"){
      minusHashTable(kinojoTree);
    }
    else if(in == "PRINT"){
      printCommand(kinojoTree);
    }
  }
}

int main(){
  Input in;
  in.finalInput();
  return 0;
}
