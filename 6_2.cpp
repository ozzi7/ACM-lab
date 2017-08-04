#include <iostream>
#include <algorithm>
using namespace std;

struct tree_node {
  int left,right;
  int maximum;
  tree_node* leftC;
  tree_node* rightC;
};

void fillTree(tree_node* node) {
  if(node->left != node->right) { // split tree   
    tree_node* leftNode;
    tree_node* rightNode;
    leftNode = (struct tree_node*)malloc(sizeof(struct tree_node));
    rightNode = (struct tree_node*)malloc(sizeof(struct tree_node));   
    leftNode->left = node->left; // 3,5 -> 3,4  5 5
    leftNode->right = (node->right + node->left)/2;
    rightNode->left = (node->right + node->left)/2+1;
    rightNode->right = node->right;
    
    node->leftC = leftNode;
    node->rightC = rightNode;
    fillTree(leftNode);
    fillTree(rightNode);
    node->maximum = std::max(node->leftC->maximum, node->rightC->maximum);
    //cout << node->left << " " << node->right << " " << node->maximum << endl;
  }
  else{   
    float f; cin >> f; f = f*100; node->maximum = f;
    node->leftC = NULL;
    node->rightC = NULL;
        //cout << node->left << " " << node->right << " " << node->maximum << endl;
  }
}

void treePrint(tree_node *node) {
  if(node->leftC == NULL) {
    cout << node->left << " / " << node->right << ": " <<node->maximum << endl; 
  }
  else {
        cout << node->left << " / " << node->right << ": " <<node->maximum << endl; 
    treePrint(node->leftC);
    treePrint(node->rightC);
  }
}

int findMax(tree_node *node) {
  if(node->leftC != NULL) {
    node->maximum = std::max(findMax(node->leftC),findMax(node->rightC));
    return node->maximum;
  }
  else {
    return node->maximum;
  }
}

void updateExam(int i, int g,tree_node *node) {
  if(node->left == node->right && node->left == i) { node->maximum = g;}
  else {
    if(node->leftC->right <  i) {// cout << node->right << " " << node->left << " " << i << endl;
      updateExam(i,g,node->rightC);}
    else {//cout << node->right << " " << node->left << " " << i << endl;
      updateExam(i,g,node->leftC);}
  }
}
int queryStudent(int min, int max, tree_node *node) { // returns maximum for student
  if(node->left >= min && node->right <= max) {return node->maximum;} // whole interval matches is contained
  else { // has 2 children
    if(node->leftC->right < min) {
      // student is only in right segment
      return queryStudent(min,max,node->rightC);
    }
    else {
      if(node->leftC->right >= max) { // only left segment
	return queryStudent(min,max,node->leftC);
      }
      else { // max of left and right
	return std::max(queryStudent(min,max,node->leftC),
		  queryStudent(min,max,node->rightC));
      }
    }
  }
}
int main() {
    ios_base::sync_with_stdio(false);
    int testcases;
    int temp1,temp2;
    cin >> testcases;
    while (testcases--) {
      int n,m,l;
      cin >> n >> m >> l;
      vector<pair<int,int> >student;
      vector<pair<int,int> >examUpdates;
      student.clear();
      examUpdates.clear();
      // construct initial tree
      tree_node* root;
      root = (struct tree_node*)malloc(sizeof(struct tree_node));
      root->right = m-1;
      root->left = 0;
      fillTree(root);
//       cout << "Initial tree: " << endl;
//       treePrint(root);
      //findMax(root); // redundant
      for(int i = 0 ; i <n; i++) { // load student intervals
	cin >> temp1; cin >> temp2;
	student.push_back(make_pair(temp1,temp2));
      }
      float f;
      for(int v = 0 ; v <l; v++) { // load exam updates
	cin >> temp1; cin >> f;
	examUpdates.push_back(make_pair(temp1,(f*100)));
      }
      
      // no updates
      long long sum = 0;
      for(int h = 0 ; h <student.size(); h++) { // go through students
	sum = sum + queryStudent(student[h].first, student[h].second,root);
	//cout << queryStudent(student[i].first, student[i].second,root)<< endl;
      }
      sum = sum/n;
      cout << ((float)sum)/100  << endl;
      // with updates
      for(int u = 0; u < examUpdates.size(); u++) {
	// update
	updateExam(examUpdates[u].first, examUpdates[u].second,root);
	// propagate maximum
// 		      cout << "No prop: "<< endl;
//       treePrint(root);
	findMax(root);
// 	      cout << "After update " << u+1 << ": "<< endl;
//       treePrint(root);
	sum = 0;
	for(int g = 0 ; g < student.size(); g++) { // go through students
	  sum += queryStudent(student[g].first, student[g].second,root);  
	}
// 	cout << sum << endl;
	sum = sum/n;
	cout << ((float)sum)/100  << endl;
      }
      free(root);
    }
    return 0;
}