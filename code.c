# include <stdio.h> 
# include <string.h> 
int main( ) 
{ 
	FILE *filePointer ;
	int i=3;
	int j=4; 
	int k=i+j; 
	char dataToBeWritten[10];//= (char) a;

        dataToBeWritten[0] = k + '0'; 

	filePointer = fopen("output.txt", "w") ; 
		if ( strlen ( dataToBeWritten ) > 0 ) 
		{ 
			fputs(dataToBeWritten, filePointer) ; 
			fputs("\n", filePointer) ; 
		} 

		fclose(filePointer) ;  
	return 0;		 
}
