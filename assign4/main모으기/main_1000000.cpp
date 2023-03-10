/** 
  * Assignment 4 for COSE213 Data Structures
  *
  * Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  * 2021. 11. 21
  *
  */
  
#include "LinkedBinaryTree.h"
#include "SearchTree.h" 
#include "AVLTree.h"

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
 
#include <iostream>
 
using namespace std;

int main()
{
	typedef Entry<int, float> EntryType;

	LinkedBinaryTree<EntryType> t;
	
	SearchTree<EntryType>	st;
	AVLTree<EntryType>	avl;
	
	int nElem = 1000000 ;
	printf("Number of Elem = %d\n\n",nElem);
	
	int *key = new int[nElem*2];
	int *keyindex = new int[nElem*2];
	float *val = new float[nElem*2];
	int randn;
	
	std::srand(std::time(0)); // use current time as seed for random generator

   
	for(int i=0; i<nElem*2; i++)
	{ 
		while(1){
			randn = std::rand() % (nElem*2);
			if(keyindex[randn] == 0){
				keyindex[randn]++;
				break;
			}
		}
		key[i] = randn;
		val[i] = (float) std::rand()/RAND_MAX * 20000; 
	}
	delete [] keyindex;	


	std::cout << "------random order------" << std::endl;
	std::cout << std::endl;
	std::cout << "------SearchTree------" << std::endl;
  //
  // BST Insert test     
  //	
	clock_t tm;
    tm = clock();
	for(int i=0; i<nElem; i++)
	{
		st.insert(key[i], val[i]);
	}
	tm = clock() - tm; 
	printf ("Insertion took me %f seconds.\n",((float)tm)/(float)CLOCKS_PER_SEC);
	
  //
  // BST tree Find test
  //	
	tm = clock();
	for(int i=nElem; i<nElem*2; i++)
	{
		st.find(key[i]);
	}   
	tm = clock() - tm;
	printf ("Finding took me %f seconds.\n",((float)tm)/(float)CLOCKS_PER_SEC);


	std::cout << "------AVL Tree------" << std::endl;
  //
  // AVL tree Insert test 
  //	 
    tm = clock();
	for(int i=0; i<nElem; i++)
	{
		avl.insert(key[i], val[i]);
	}
	tm = clock() - tm; 
	printf ("Insertion took me %f seconds.\n",((float)tm)/(float)CLOCKS_PER_SEC);
	
  //
  // AVL tree Find test
  //	
	tm = clock(); 
	for(int i=nElem; i<nElem*2; i++)
	{
		avl.find(key[i]);
	}
	tm = clock() - tm;
	printf ("Finding took me %f seconds.\n",((float)tm)/(float)CLOCKS_PER_SEC);

//
//
//
//skewed order
//
//
//

	std::cout << std::endl;
	std::cout << std::endl;
	
	SearchTree<EntryType>	st2;
	AVLTree<EntryType>	avl2;

	std::cout << "------skewed order------" << std::endl;
	std::cout << std::endl;
	std::cout << "------Skip SearchTree because of Segmentation Fault------" << std::endl;
/* 
  //
  // BST Insert test     
  //	
    tm = clock();
	for(int i=0; i<nElem; i++) 
	{
		st2.insert(i, val[i]);
	}
	tm = clock() - tm; 
	printf ("Insertion took me %f seconds.\n",((float)tm)/(float)CLOCKS_PER_SEC);
	
  //
  // BST tree Find test
  //	
	tm = clock();
	for(int i=nElem; i<nElem*2; i++)
	{
		st2.find(i);
	}   
	tm = clock() - tm;
	printf ("Finding took me %f seconds.\n",((float)tm)/(float)CLOCKS_PER_SEC);
*/

	std::cout << "------AVL Tree------" << std::endl;
  //
  // AVL tree Insert test 
  //	 
    tm = clock();
	for(int i=0; i<nElem; i++)
	{
		avl2.insert(i, val[i]);
	}
	tm = clock() - tm; 
	printf ("Insertion took me %f seconds.\n",((float)tm)/(float)CLOCKS_PER_SEC);
	
  //
  // AVL tree Find test
  //	
	tm = clock(); 
	for(int i=nElem; i<nElem*2; i++)
	{
		avl2.find(i);
	}
	tm = clock() - tm;
	printf ("Finding took me %f seconds.\n",((float)tm)/(float)CLOCKS_PER_SEC);
	

	delete [] key;
	delete [] val;

	
	return 0;
}
