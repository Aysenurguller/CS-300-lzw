#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>


using namespace std;

template<class Value>
int hash(Value & v ){
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
			

			HashTable(const Key &,int size = 256);
			HashTable(const HashTable & rhs) : array(rhs.array) {}


            Key find(const Value &);

            void makeEmpty();
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
            vector<HashEntry> array;
            int currentSize;
 
            bool isActive(int) const;
            int findPos(const Value &) const;
            void rehash();

};




#endif