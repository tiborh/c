//	Function Declaration
void bin16 (uint16_t num, char* bitStr);

/*	======================= bin16 =======================
	Convert fixed 16-bit integer to binary digit string.
	   Pre  num contains integral value to be converted
	        bitStr is pointer to variable for bit string
	   Post bit string stored in str
*/
void bin16 (uint16_t num, char* bitStr)
{
//	Statements
	for (int i = 0; i < 16; i++)
	     bitStr[i] = (char) ((num >> 15 - i) & 0X0001) + 48;
	return;
 }	// bin16
