#include<iostream>
using namespace std;
#include<stdlib.h>
#include<fstream>

void insertion_sort (int arr[], int length){
	 	int j, temp;

	for (int i = i; i < length; i++){
		j = i;

		while (j > 0 && arr[j] < arr[j-1]){
			  temp = arr[j];
			  arr[j] = arr[j-1];
			  arr[j-1] = temp;
			  j--;
			  }
		}
}
int main()
{
    long long int n;
    int k;
    int i;
    cin >> n;
    FILE *fp[10];
    string s,s1;
    s="f";
    s1="";
    char c1;
    for(i=0;i<10;i++) {
            s1="";
            c1 =(char)((i%10)+48);
            s1=s1+c1+".txt";
            s1=s+s1;
    fp[i]=fopen(s1.c_str(),"w");
    }

    for(i=0;i<n;i++) {
        k=rand()%10000;
       int p = k/1000;
       fprintf(fp[p],"%d,",k);
    }
   for(i=0;i<10;i++) fclose(fp[i]);
    int a[10000];
    int j;
    int u;

    s ="f";
    s1="";
    string s2="f11.txt";
    FILE *finall=fopen(s2.c_str(),"w");
    for(i=0;i<10;i++) {
        int c=-1;
        c1 =(char)((i%10)+48);
        s1="";
        s1=s1+c1;
        s1+=".txt";
        s1=s+s1;

        fp[i]=fopen(s1.c_str(),"r");
        do {
            c++;
            fscanf(fp[i],"%d,",&a[c]);
        }
        while(!feof(fp[i]));

        insertion_sort(a,c);
        fclose(fp[i]);

    for(j=0;j<c;j++) fprintf(finall,"%d,",a[j]);
        //fclose(fp[i]);

    }

return 0;

}








