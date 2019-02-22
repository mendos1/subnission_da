#include <iostream>

using namespace std;

int main(){   
 
int sum1 = 0;
int sum2 = 0;
int counter = 11;
 
	for (int i=0; i <= 98; i++){              
 
		 if ((counter%3) == 0 ){   
			 sum1 = sum1 + counter;           
		 }     
		 else{    
			 sum2 = sum2 + counter;        
		 }  
	 counter++;   
	}  
	cout << sum1 << " " << sum2 << endl;
}