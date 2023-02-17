
#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>


using namespace std;

template<class Value>
int hashF(Value & v ){
	const int p =31;
	const int e = 1e9+9;

	long long hash_value=0;
	long long p_pow= 1;

	for(unsigned char c : v){
		hash_value = (hash_value + c * p_pow) % e;
		p_pow= (p_pow*p) % e;;
	}
	return hash_value;
}

template <class Value, class Key>
    class HashTable{
        public:
			

			HashTable(const Key &,int size = 256); //Default
			HashTable(const HashTable & rhs) : array(rhs.array) {} //Copy


            Key find(const Value &);  //Find item in table

            void makeEmpty();  //Delete all items
            void insert(const Value & ,const Key &);
            void remove(const Value &);

            const HashTable & operator=(const HashTable &rhs);

            enum EntryType {ACTIVE, EMPTY, DELETED};
		

        private:
            struct HashEntry
            {
                Value value;
				Key code;
                EntryType info;
				

                HashEntry(Key k= Key() , const Value & v = Value(), EntryType i = EMPTY)
					: code(k) ,value(v), info (i){}
            };
			const Key ITEM_NOT_FOUND;
            vector<HashEntry> array;  //HashTable =dictionary
            int currentSize; 
 
            bool isActive(int) const;
            int findPos(const Value &) const;
            void rehash();

};


template <class Value, class Key>
HashTable<Value,Key>::HashTable(const Key & notFound, int size ) : array(size), ITEM_NOT_FOUND(notFound){
//postcondition : Construct table
	makeEmpty();
}




template <class Value, class Key>
int HashTable<Value,Key>::findPos(const Value & v) const {
//return position of value v 
    int p = hashF(v) % array.size();
    
    while (array[p].info != EMPTY && array[p].value != v) {
        p++;
    }

    return p;
}

template<class Value, class Key>
bool HashTable<Value,Key>::isActive(int currentPos) const{
//return true corresponded position info active or not
    return array[currentPos].info == ACTIVE;
}

template <class Value, class Key>
void HashTable< Value,Key>::remove(const Value & v){
//remove value v and corresponding code from table 
    int currentPos = findPos(v);

    if(isActive(currentPos)){
        array[currentPos].info = DELETED;
    }
}

template <class Value, class Key>
Key HashTable<Value,Key>::find(const Value & v) {
	//returns code of the value if it is exists in dictionary
    int currentPos = findPos(v);

    if(isActive(currentPos)){
        return array[currentPos].code;
    }

    return ITEM_NOT_FOUND;
}

template <class Value, class Key>
void HashTable<Value, Key>::insert(const Value & v ,const Key & c){
//If item is not in the table, insert it
    int currentPos = findPos(v);
    if(isActive(currentPos)){
        return;
    }

    array[currentPos] = HashEntry(c,v,ACTIVE);

    if(++currentSize >= array.size()/2){
        rehash();
    }
}

template <class Value, class Key>
void HashTable<Value, Key>::rehash(){
    vector<HashEntry> oldArray = array;

    array.resize(2* oldArray.size());

    for(int i = 0; i< array.size(); i++){
        array[i].info = EMPTY;
    }

    currentSize = 0;

    for(int i = 0; i < sizeof(oldArray) / sizeof(i);i++){
        if(oldArray[i].info == ACTIVE){
            insert(oldArray[i].value,oldArray[i].code);
        }
    }
}

template <class Value, class Key>
void HashTable<Value, Key>::makeEmpty(){
    for (int i = 0; i<array.size();i++){
        array[i].info = EMPTY;
    }
}

