/*	Reads a binary file of student data, and prints it.
	   Written by: 
	   Date: 
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES_PER_PAGE  50
#define BUFFER_SIZE        133
#define FORM_FEED          '\f'

//	Type Declarations
typedef struct stuData
	{
	 char  name[26];
	 char  id[5];
	 int   exams[3];
	 int   problems[8];
	 char  grade;
	} STU_DATA;

//	Function Declarations
STU_DATA getData      (FILE* binFile);
void     writeReport  (STU_DATA aStudent,
                       FILE* prtFile);
void     pageHeaders  (FILE* prtFile);

int main (void)
{
//	Local Declarations
	char      stuFileID[]  = "P13-stu.bin";
	char      prtFileID[]  = "P13-stu.prt";
	STU_DATA  aStudent;
	FILE*     stuFile;
	FILE*     prtFile;

//	Statements
	printf("\nBegin Student Report Creation\n ");

	if(!(stuFile = fopen(stuFileID, "rb")))
	   {
	    printf("\nCannot open %s\n", stuFileID);
	    exit (100);
	   } // if stuFile
	if (!(prtFile = fopen(prtFileID, "w"))) 
	   {
	    printf("\nCannot open %s\n", prtFileID);
	    exit (200);
	   } // if prtFile
	
	aStudent = getData (stuFile);
	while (!feof(stuFile))
	   {
	    writeReport (aStudent, prtFile);
	    aStudent = getData (stuFile);
	   } // while

	fprintf(prtFile, "\nEnd of Report\n"); 
	fclose(stuFile);
	fclose(prtFile);
	printf("\n\nEnd Student Report Creation\n");
	return 0;
}	// main

/*	==================== getData ====================
	This function reads the student binary file.
	   Pre   stuFile is opened for reading 
	   Post  one student record read and returned 
*/
STU_DATA getData (FILE* stuFile) 
{
//	Local Declarations
	int       ioResult;
	STU_DATA  aStu;

//	Statements
	ioResult = fread(&aStu, 
	                 sizeof(STU_DATA), 1, stuFile);
	if (!ioResult)
	   if (!feof(stuFile))
	      {
	       printf("\n\nError reading student file\n");
	       exit (100);
	      } // if !feof
	return aStu;
} // getData

/*	=================== writeReport ====================
	Write student report to a text file.
	   Pre   prtFile is opened as a text output file
	         aStudent is complete
	   Post  Report line written 
*/
void writeReport (STU_DATA  aStu, FILE* prtFile)
{
//	Local Declarations
	static int lineCount = MAX_LINES_PER_PAGE + 1;
	char   buffer[BUFFER_SIZE];

//	Statements
	if (++lineCount > MAX_LINES_PER_PAGE)
	   {
	    pageHeaders  (prtFile);
	    lineCount = 1;
	   } // if

	sprintf (buffer, 
	  "%-25s %4s %4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d %c\n", 
	  aStu.name, aStu.id, 
	  aStu.exams[0],    aStu.exams[1],    aStu.exams[2],
	  aStu.problems[0], aStu.problems[1], aStu.problems[2], 
	  aStu.problems[3], aStu.problems[4], aStu.problems[5], 
	  aStu.problems[6], aStu.problems[7], 
	  aStu.grade);
	fputs (buffer, prtFile);
	return;
} // writeReport

/*	================== pageHeaders ==================
	Writes the page headers for the student report.
	   Pre   prtFile is opened as a text output file
	   Post  Report headers and captions written
*/
void pageHeaders (FILE* prtFile) 
{
//	Local Declarations
	static int pageNo = 0;

//	Statements
	pageNo++;
	fprintf(prtFile, "%c", FORM_FEED);
	fprintf(prtFile, "%-66s  Page %4d\n",
	        "Student Report ", pageNo);
	fprintf(prtFile, "%-25s %-6s %-10s %-27s Grade\n\n",
	        "Student Name", "ID", "Exams", "Problems");
	return;
}	// pageHeaders
//	================= End of Program =================

/*	Results:

Begin Student Report Creation
 

End Student Report Creation

P13-stu.prt contains:
Student Report                                                      Page    1
Student Name              ID     Exams      Problems                    Grade

First                     1111   11  12  13 111 112 113 114 115 116 117 118 A
Second                    2222   21  22  23 221 222 223 224 225 226 227 228 B
Third                     3333   31  32  33 331 332 333 334 335 336 337 338 C
Fourth                    4444   41  42  43 441 442 443 444 445 446 447 448 D
Last                      5555   51  52  53 551 552 553 554 555 556 557 558 F

End of Report
*/