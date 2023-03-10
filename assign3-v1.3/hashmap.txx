//
// - Implementation -
//

// constructor
template <class HashMapElemType>
HashMap<HashMapElemType>::HashMap(unsigned int c) 
{
	// ToDo
	mapsize = 0;
	capacity = c;

	int num = 1;

	for(int i = capacity; i >= 2; i--){
		bool prime_check = true;
		for(int j = 2; j < i; j++){
			if(i % j == 0){
				prime_check = false;
				break;
			}
		}
		if(prime_check){
			num = i;
			break;
		}
	}
	divisor = num;
	ht = new HashMapElemType*[c];
	
	for(int i=0;i<c;i++){
		ht[i] = new HashMapElemType;
		ht[i] = NULL;
	}
}

// destructor
template <class HashMapElemType>
HashMap<HashMapElemType>::~HashMap() 
{
	// ToDo
	HashMapElemType* p = NULL;
	HashMapElemType* next = NULL;
	for(int i=0;i<capacity;i++){
		p = ht[hashfunction(i)];
		do{
			next = p->link;
			delete p;
			ht[hashfunction(i)] = NULL;
			p = next;
		}while(p != NULL);
	}

	delete[] ht;
}

template <class HashMapElemType>
HashMapElemType* 
HashMap<HashMapElemType>::find(const KeyType k) 
{
	HashMapElemType* p = ht[hashfunction(k)];
	
	while(p != NULL){
		if(p->key == k){
			return p;
		}
		p = p->link;
	}

	return NULL;
}

template <class HashMapElemType>
void 
HashMap<HashMapElemType>::insert(const KeyType k, const ValType v) 
{
	if(find(k) != NULL){
		find(k)->val = v;
		return;
	}
	mapsize++;
	// ToDo
	HashMapElemType* p = new HashMapElemType;
	p->key = k;
	p->val = v;

	p->link = ht[hashfunction(k)];
	ht[hashfunction(k)] = p;
}

template <class HashMapElemType>
bool 
HashMap<HashMapElemType>::remove(const KeyType k) 
{
	 // ToDo
	int hashk = hashfunction(k);

	HashMapElemType* p = ht[hashk];
	HashMapElemType* prev = p;

	if(p == NULL){
		return false;
	}

	if(p->key == k){
		ht[hashk] = p->link;
		delete p;
		p = NULL;
		mapsize--;
		return true;
	}
	p = p->link;

	while(p != NULL){
		if(p->key == k){
			prev->link = p->link;
			delete p;
			p = NULL;
			mapsize--;
			return true;
		}
		prev = p;
		p = p->link;
	}
	
	return false;
}

template <class HashMapElemType>
unsigned int 
HashMap<HashMapElemType>::hashfunction(const KeyType k)
{
	int i = 0;
	int number = 0;

	//make prime number smaller than capacity
	
	int p = 53, pp = 1;

	while(k[i])
	{
		number = (number + (int)(k[i] - 'a' + 1) * pp ) % divisor;
		pp = (p * pp) % divisor;
		i++;
	}

	return number;
}

template <class HashMapElemType>
void 
HashMap<HashMapElemType>::print()
{
	// ToDo
	int i;
	HashMapElemType* p = NULL;
	for(i=0;i<capacity;i++){
		p = ht[i];
		while(p != NULL){
			std::cout << p->key << ":" << p->val << std::endl;
			p = p->link;
		}
	}
}