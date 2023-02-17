#include <iostream>
#include <typeinfo>
#include <vector>
#include <string>

using namespace std;



template <class Key, class Value>
class Hash
{
public:
	Hash(const Value &, int size = 256);  //Default
	Hash(const Hash & rhs):array(rhs.array){} //Copy


	void remove(const Key &);
	void makeEmpty();
	void insert(const Key&, const Value&);

	Value find(const Key&);

	enum EntryType{ACTIVE, EMPTY, DELETED};
	const Hash & operator=(const Hash & rhs);

private:
	struct HashEntry{
		Key code;
		Value value;
		EntryType info;

		HashEntry(Key c = Key(), const Value & v = Value(), EntryType i = EMPTY )
			:code(c), value(v),info(i){}
	
	};



	const Value ITEM_NOT_FOUND;
	vector<HashEntry> array;
	bool isActive(int) const;
	int findPos(const Key&) const;
};


template<class Key, class Value>
Hash<Key,Value>::Hash(const Value & notFound, int size) : ITEM_NOT_FOUND(notFound), array(size){
	makeEmpty();
}

template <class Key, class Value>
void Hash<Key,Value>::makeEmpty() {
	for(int i =0; i<array.size();i++){
		array[i].info = EMPTY;
	}
}

template <class Key, class Value>
int Hash<Key,Value>::findPos(const Key & pos)const {
	int p = pos % array.size();

	while(array[p].info != EMPTY && array[p].code != pos ){
		p++;
	}
	return p;
}

template <class Key, class Value>
bool Hash<Key,Value>::isActive(int pos) const
{
	return array[pos].info ==ACTIVE;
}

template <class Key, class Value>
Value Hash<Key,Value>::find(const Key & code){
	int pos = findPos(code);

	if(isActive(pos))
	{
		array[pos].info = DELETED;
	}
	return ITEM_NOT_FOUND;
}

template <class Key, class Value>
void Hash<Key, Value>::insert(const Key & code, const Value & value)
{

	int pos = findPos(code);

	if(isActive(pos))
	{
		return;
	}
	array[pos] = HashEntry(code, value, ACTIVE);
}
