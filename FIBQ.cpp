# include <iostream>
# include <stdio.h>
# include <math.h>
# define ll long long 
# define MOD 1000000007
using namespace std;
ll int F[2][2];
ll int st[500000][2][2],ans[2][2];
void multiply(ll int F[2][2], ll int M[2][2]);
 
void power(ll int F[2][2],ll int n);
 
void fib(ll int n)
{
  F[0][0]=1;
  F[0][1]=1;
  F[1][0]=1;
  F[1][1]=0;
  power(F, n);
}
void power(ll int F[2][2], ll int n)
{
  if( n == 0 || n == 1)
      return;
  ll int M[2][2] = {{1,1},{1,0}};
 
  power(F, n/2);
  multiply(F, F);
 
  if (n%2 != 0)
     multiply(F, M);
}
void multiply(ll int F[2][2], ll int M[2][2])
{
  ll int x =  ((F[0][0]*M[0][0])%MOD + (F[0][1]*M[1][0])%MOD)%MOD;
  ll int y =  ((F[0][0]*M[0][1])%MOD + (F[0][1]*M[1][1])%MOD)%MOD;
  ll int z =  ((F[1][0]*M[0][0])%MOD + (F[1][1]*M[1][0])%MOD)%MOD;
  ll int w =  ((F[1][0]*M[0][1])%MOD + (F[1][1]*M[1][1])%MOD)%MOD;
 
  F[0][0] = x;
  F[0][1] = y;
  F[1][0] = z;
  F[1][1] = w;
}



int getMid(int s, int e) {  return s + (e -s)/2;  }

void getSumUtil(int ss, int se, int qs, int qe, int si)
{
    
    if (qs <= ss && qe >= se)
    {
    	ans[0][0]=st[si][0][0];
    	ans[0][1]=st[si][0][1];
    	ans[1][0]=st[si][1][0];
		ans[1][1]=st[si][1][1];
		return;
    }
 
    // If segment of this node is outside the given range
    if (se < qs || ss > qe)
	{
		ans[0][0]=1;
		ans[0][1]=0;
		ans[1][0]=0;
		ans[1][1]=1;
		return;
	}
 
    int mid = getMid(ss, se);
    getSumUtil(ss, mid, qs, qe, 2*si+1); 
    ll int x[2][2];
	x[0][0]=ans[0][0];
    x[0][1]=ans[0][1];
    x[1][0]=ans[1][0];
	x[1][1]=ans[1][1];
	getSumUtil(mid+1, se, qs, qe, 2*si+2);
	multiply(x,ans);
	
	ans[0][0]=x[0][0];
    ans[0][1]=x[0][1];
    ans[1][0]=x[1][0];
	ans[1][1]=x[1][1];
	
}
 

void updateValueUtil(int arr[],int ss, int se, int i, int si)
{
    // Base Case: If the input index lies outside the range of 
    // this segment
    if (i < ss || i > se)
        return;
 
    // If the input index is in range of this node, then update 
    // the value of the node and its children
    if (se != ss)
    {
        int mid = getMid(ss, se);
        if(i<=mid)
        	updateValueUtil(arr,ss, mid, i, 2*si + 1);
        else
			updateValueUtil(arr,mid+1, se, i, 2*si + 2);
			
		st[si][0][0] = 1;
		st[si][0][1] = 0;
		st[si][1][0] = 0;
		st[si][1][1] = 1;
    	multiply(st[si],st[si*2+1]);
    	multiply(st[si],st[si*2+2]);
    }
    else
    {
    	fib(arr[ss]);
    
		st[si][0][0] = F[0][0]+1;
		st[si][0][1] = F[0][1];
		st[si][1][0] = F[1][0];
		st[si][1][1] = F[1][1]+1;
		return;	
    }
}
 
// The function to update a value in input array and segment tree.
// It uses updateValueUtil() to update the value in segment tree
void updateValue(int arr[], int n, int i)
{
    // Check for erroneous input index
    if (i < 0 || i > n-1)
    {
        printf("Invalid Input");
        return;
    }

 
    // Update the values of nodes in segment tree
    updateValueUtil(arr,0, n-1, i,  0);
}

// Return sum of elements in range from index qs (quey start)
// to qe (query end).  It mainly uses getSumUtil()
void getSum(int n, int qs, int qe)
{
    // Check for erroneous input values
    if (qs < 0 || qe > n-1 || qs > qe)
    {
        printf("Invalid Input");
    
    }
 
    getSumUtil(0, n-1, qs, qe, 0);
}
            

void constructSTUtil(int arr[], int ss, int se, int si)
{
    
    if (ss == se)
    {
        fib(arr[ss]);
    
		st[si][0][0] = F[0][0]+1;
		st[si][0][1] = F[0][1];
		st[si][1][0] = F[1][0];
		st[si][1][1] = F[1][1]+1;
		
		//cout << si << "\n";
		//cout << st[si][0][0] << " " << st[si][0][1] << endl;
    	//cout << st[si][1][0] << " " << st[si][1][1] << endl;
		return ;
    }
 
    int mid = getMid(ss, se);
    constructSTUtil(arr, ss, mid, si*2+1); 
    constructSTUtil(arr, mid+1, se, si*2+2);
   
  	st[si][0][0] = 1;
	st[si][0][1] = 0;
	st[si][1][0] = 0;
	st[si][1][1] = 1;
    multiply(st[si],st[si*2+1]);
    multiply(st[si],st[si*2+2]);
    	
	
	//cout << si << "\n";
	//	cout << st[si][0][0] << " " << st[si][0][1] << endl;
    //	cout << st[si][1][0] << " " << st[si][1][1] << endl;
    
}
 
/* Function to construct segment tree from given array. This function
   allocates memory for segment tree and calls constructSTUtil() to
   fill the allocated memory */
void constructST(int arr[], int n)
{

	int x = (int)(ceil(log2(n))); 
    int max_size = 2*(int)pow(2, x) - 1; 

    //int *st = new int[max_size][2][2];
    constructSTUtil(arr, 0, n-1, 0);
    return;
}
 
int main()
{
	int n,m,a[100000],i,x,y;	char ch;
	scanf("%d %d",&n,&m);
	for(i=0;i<n;i++)	scanf("%d",&a[i]);
	constructST(a,n);
	while(m--)
	{
		scanf(" %c %d %d",&ch,&x,&y);
		if(ch=='Q')
		{
			x--;	y--;
			getSum(n,x,y);
			printf("%lld\n",ans[0][1]);
			
			
		}
		else
		{
			x--;
			a[x]=y;
			updateValue(a,n,x);
		}
		
	}
	return 0;
	
}
