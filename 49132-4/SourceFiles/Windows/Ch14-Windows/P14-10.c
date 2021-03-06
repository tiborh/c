/*	Determine the last address in a broadcast network.
	   Written by:
	   Date:
*/
#include <stdio.h>
#include <math.h>
#include <stdint.h>

int main (void)
{
//	Local Declarations
	unsigned int  comAddr[4];
	unsigned int  mask[4];
	unsigned int  broadAddr[4];

	uint32_t comAd   = 0;
	uint32_t mask32  = 0;
	uint32_t broadAd = 0;
	int      prefix;

//	Statements
	printf ("Enter host address <x.y.z.t>: ");
	scanf ("%d%*c%d%*c%d%*c%d", 
	        &comAddr[3], &comAddr[2], 
	        &comAddr[1], &comAddr[0]);
	printf("Enter prefix: ");
	scanf ("%d", &prefix);

	// Convert address to 32- bit computer address
	for (int i = 3; i >= 0; i--)
	     comAd = comAd * 256 + comAddr[i];

	// Create 32-bit prefix mask
	for (int i = 32-prefix; i < 32; i++)
	     mask32 = mask32 | (0x0001 << i);

	// And to get a 32-bit Network Address
	broadAd = comAd | (~mask32);

	// Change the mask into the form x.y.z.t
	for (int i= 0; i < 4; i++)
	    {
	     mask[i]= mask32 % 256;
	     mask32 = mask32 / 256;
	    } // for

	// Chanage the IP address to the form x.y.z.t
	for (int i= 0; i < 4; i++)
	    {
	     broadAddr[i] = broadAd % 256;
	     broadAd      = broadAd / 256;
	    } // for

	printf ("\nPrinting Addresses\n");
	printf ("Computer Address:  ");
	printf ("%d.%d.%d.%d\n", 
	        comAddr[3], comAddr[2], comAddr[1],comAddr[0]);
	printf ("Mask:              ");
	printf ("%d.%d.%d.%d\n", 
	        mask[3], mask[2], mask[1], mask[0]);

	printf ("Broadcast Address: ");
	printf ("%d.%d.%d.%d\n",
	        broadAddr[3], broadAddr[2], 
	        broadAddr[1], broadAddr[0]);
	return 0;
}	// main

/*	Results:
Enter host address <x.y.z.t>: 123.45.78.12
Enter prefix: 18

Printing Addresses
Computer Address:  123.45.78.12
Mask:              255.255.192.0
Last Address:      123.45.127.255
*/