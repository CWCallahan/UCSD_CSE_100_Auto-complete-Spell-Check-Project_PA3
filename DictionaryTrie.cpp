#include "util.h"
#include "DictionaryTrie.h"
#include <queue>
#include <string> 

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){}

Node::Node()
{
  //children = newChild;
  //for(const Node* &children : children)
  //  cout << "value of text: " << children << endl;
  for(int i =0; i< 27; i++)
     children[i] = nullptr;
    //std::cout << "Chil at letter: \t" << Chil[i] << std::endl;
  //}
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  if (!root){
    root = new Node();
    root->freq=0;
    for (int i=0; i<27; i++)
      root->children[i]=0;
    //reinit
  }
    
  //declare a current array at root
  Node* cLevel = root;

  //iterate through the word
  for (int i=0; i<word.length(); i++){
    int letter;
    if(word[i]==' '){
      //std::cout << "found a space" << std::endl;
      letter = 0;
    }else{ 
      letter = word[i]-96;
    }
    //check if there is a node at i
    //Node* newChild[27] = {0};
    std::cout << i << std::endl;
    
    if (!cLevel->children[letter]){ //problem here when in test, may be cLevel not dec
      //if not add the letter into the root
      std::cout << "in if at 48" << std::endl; //problem here when in test
      Node* next = new Node();
      //reinit
      next->freq = 0;//initialize
      for (int i=0; i<27; i++)
	next->children[i]=0;
      cLevel->children[letter] = next;
      
    }//else{//did this serve any purpose??
    //} 
    //if there is no next letter
    
    std::cout << "out of if at 57" << std::endl;
    if(i == word.length()-1){
      //and the word is not yet inserted
      if (cLevel->children[letter]->freq == 0){//now this
	//add the word and return true
	cLevel->children[letter]->freq = freq;
	return 1;
      //otherwise the word already is in the trie
      }else{
	return 0; //may need to update to new freq?
      }

    //if we're not at the end of the word then update for next iteration
    }else{
      //Move to the next letter to our Trie
      cLevel = cLevel->children[letter];//initialize next?
    }

  }//done or loop again
  std::cout << "returning false in DT after insert" << std::endl;
  return false;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  //Starting at the root
  const Node* cLevel = root;

  //add conditional if the next word does not exist
  
  //iterate through the word
  for (int i=0; i<word.length(); i++){
        int letter;
    if(word[i]==' '){
      //std::cout << "found a space" << std::endl;
      letter = 0;
    }else{ 
      letter = word[i]-96;
    }
    //if this is the last letter in the word check for freq
    //std::cout << "at: " <<i<< " letter is: " << letter << std::endl;
    if(i == word.length()-1){
      //std::cout << "in if 93... " <<  std::endl;
      //ensure that the entry exists
      if (!cLevel->children[letter]){
	return 0;
      //if it is zero return false 
      }else if (cLevel->children[letter]->freq == 0){
	//std::cout << "returning false in DTfind at 0freq" << std::endl;
	return 0;
      //if freq is not zero return true
      }else
	return 1;
    }

    //std::cout << "checking for cl: " << cLevel << std::endl;
    //if the trie continues move to the next level
    if (cLevel->children[letter]){
      //std::cout << "moving on to: " << cLevel->children[letter] << std::endl;
      cLevel = cLevel->children[letter];
    //else if the trie has a dead end then return false
    }else{
      //std::cout << "returning false in DTfind at dead end" << std::endl;
      return 0;
    }
  }

  //std::cout << "returning false in DTfind at end" << std::endl;
  return false;
}

void DictionaryTrie::print() {
  for(int i = 0; i<27; i++){
    //std::cout << root->children[3]->children[i] << std::endl;

  }
}

/* Return true if word is in the dictionary, and false otherwise */
Node* DictionaryTrie::findPrefix(std::string word) const{
  //Starting at the root
  Node* cLevel = root;

  //add conditional if the next word does not exist
  
  //iterate through the word
  for (int i=0; i<word.length(); i++){
    int letter;
    if(word[i]==' '){
      //std::cout << "found a space" << std::endl;
      letter = 0;
    }else{ 
      letter = word[i]-96;
    }
    //if this is the last letter in the word check for freq
    std::cout << "at: " <<i<< " letter is: " << letter << std::endl;
    if(i == word.length()-1){
      //std::cout << "in if 93... " <<  std::endl;
      //ensure that the entry exists
      if (!cLevel->children[letter]){
	return 0;
	//if it is zero return false 
	//}else if (cLevel->children[letter]->freq == 0){
	//std::cout << "returning false in DTfind at 0freq" << std::endl;
	//return 0;
	//if freq is not zero return true
      }else
	return cLevel->children[letter];
    }

    //std::cout << "checking for cl: " << cLevel << std::endl;
    //if the trie continues move to the next level
    if (cLevel->children[letter]){
      //std::cout << "moving on to: " << cLevel->children[letter] << std::endl;
      cLevel = cLevel->children[letter];
      //else if the trie has a dead end then return false
    }else{
      std::cout << "returning false in DTfind at dead end" << std::endl;
      return 0;
    }
  }
  return 0;
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)o
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
 //0) make a vector of words
  std::vector<std::string> words;
  typedef std::pair<int, std::string> ISPair;
  
  //I)   Find the prefix
  //--------------------------------------------
  std::cout << "finding pref..." << std::endl;
  Node* curr = findPrefix(prefix);
  if (curr==0)
    return words;
  std::cout << "found pref..." << std::endl;
  
  //II)  Make a priority queue of the completions
  //--------------------------------------------
  std::priority_queue< ISPair, std::vector<ISPair>, std::greater<ISPair> > pq;

  //1. Make the Q 
  std::queue<std::pair<std::string, Node* > > q;
  
  //2. add the "root"prefix
  q.push(std::pair<std::string, Node* >(prefix, curr));
   
  //3. for as long as Q isn't empty
  while (!q.empty()) {
    curr = q.front().second;
    
    //if the head was a word add that word to the PQ
    if (curr->freq){ 
      pq.push(ISPair(curr->freq, q.front().first));
    }
     
    //b. for all possible children
    for (int i=1; i<27; i++){
      //i. if that child exists add it to the Q
      char suffix = '`'+i;
      //std::cout << suffix << std::endl;
      if (curr->children[i]){
	std::cout << suffix << std::endl;
	q.push(std::pair<std::string, Node* >(q.front().first+suffix,curr->children[i]));
      }
    }
    //  consider the ' ' case 
    if (curr->children[0])
      q.push(std::pair<std::string, Node* >(q.front().first+' ',curr->children[0]));
    
    //remove C's first
    q.pop();		     
  }//END while
  
  //III) take the designated number of words from the queue
  //--------------------------------------------
  for (int i = 0; (i < num_completions)&&(!pq.empty()); i++){
    words.push_back(pq.top().second);
    std::cout << pq.top().second << std::endl;
    pq.pop();
  }
  //std::cout << "about to return words" << std::endl;
  return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){}
