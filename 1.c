#include <ctype.h> 
int main() 
{ 
	char ch; 
	// letter to convert to uppercase
	ch = 'a'; 
	printf("%c in uppercase is represented as %c", 
		ch, toupper(ch)); 
	return 0; 
} 