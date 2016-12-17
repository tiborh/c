/*	Given a host address and the size of the prefix,  
	determine its network address.
	    Written by:
	    Date:
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main (void)
{
//	Local Declarations
	unsigned int comAddr[4];
	unsigned int mask[4];
	unsigned int netAddr[4];
	uint32_t     comAd  = 0;
	uint32_t     mask32 = 0;
	uint32_t     netAd  = 0;
	int          prefix;

//	Statements
	printf ("Enter host address <x.y.z.t>: ");
	scanf ("%d%*c%d%*c%d%*c%d", 
	      &comAddr[3], &comAddr[2], &comAddr[1], &comAddr[0]);

	printf ("Enter prefix: ");
	scanf ("%d", &prefix);

	// Convert address to a 32-bit computer address
	for (int i = 3; i >= 0; i--)
	     comAd = comAd * 256 + comAddr[i];

	// Create a 32-bit mask
	for (int i = 32 - prefix; i < 32; i++)
	     mask32 = mask32 | (1 << i);

	// AND to get a 32-bit Network Address
	netAd = comAd & mask32;

	// Change mask into the form x.y.z.t
	for (int i = 0; i < 4; i++)
	    {
	     mask[i] = mask32 % 256;
	     mask32  = mask32 / 256;
	    } // for

	// Change IP address into the form x.y.z.t
	for (int i = 0; i < 4; i++)
	    {
	     netAddr[i] = netAd % 256;
	     netAd      = netAd / 256;
	    } // for

	// Print Addresses
	printf ("\nAddresses:\n");
	printf ("Computer Address: ");
	printf ("%d.%d.%d.%d\n", 
	        comAddr[3], comAddr[2], comAddr[1],comAddr[0]);

	printf ("Mask:             ");
	printf ("%d.%d.%d.%d\n", 
	        mask[3], mask[2], mask[1], mask[0]);

	printf ("Net Address:      ");
	printf ("%d.%d.%d.%d\n", 
	        netAddr[3], netAddr[2], netAddr[1], netAddr[0]);
	return 0;
}	// main

/*	Results:
Enter host address <x.y.z.t>: 123.45.78.12
Enter prefix: 18

Addresses:
Computer Address: 123.45.78.12
Mask:             255.255.192.0
Net Address:      123.45.64.0
*/