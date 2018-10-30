#include<bits/stdc++.h>
using namespace std;
// always n leave nodes (n-1) internal nodes
// take n+n-1 = 2*n-1 size array or 2*n size to start from 1 
// so build will take O(n) time

void buildTree(int* arr, int* tree, int start, int end, int treeNode){	
	if(start == end){
		tree[treeNode] = arr[start];
		return;
	}
	int mid = (start+end)/2;

	buildTree(arr,tree,start,mid,2*treeNode);
	buildTree(arr,tree,mid+1,end,2*treeNode+1);

	tree[treeNode] = tree[2*treeNode] + tree[2*treeNode+1];
}

void updateTree(int* arr, int* tree, int start, int end, int treeNode, int idx, int value){
	if(start == end){
		arr[idx] = value;
		tree[treeNode] = value;
		return;
	}

	int mid = (start+end)/2;
	if(idx > mid){
		updateTree(arr,tree,mid+1,end,2*treeNode+1,idx,value);
	}
	else{
		updateTree(arr,tree,start,mid,2*treeNode,idx,value);
	}
	tree[treeNode] = tree[2*treeNode] + tree[2*treeNode+1];
}

int query(int* tree, int start, int end, int treeNode, int left, int right){
	//completely outside given range
	if(start > right || end < left)
		return 0;

	//completely inside given range
	if(start>=left && end<=right)
		return tree[treeNode];

	//partially inside and partially outside
	int mid = (start+end)/2;
	int ans1 = query(tree,start,mid,2*treeNode,left,right);
	int ans2 = query(tree,mid+1,end,2*treeNode+1,left,right);

	return ans1+ans2;
}

int main(){
	int arr[] = {1,2,3,4,5};
	int* tree = new int[10];

	buildTree(arr,tree,0,4,1);
	for(int i=1;i<10;i++)
		cout<<tree[i]<<" ";

	updateTree(arr,tree,0,4,1,2,10);

	cout<<endl;
	for(int i=1;i<10;i++)
		cout<<tree[i]<<" ";

	int ans = query(tree,0,4,1,2,4);
	cout<<endl<<ans;
}
