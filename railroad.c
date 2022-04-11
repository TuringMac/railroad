
#include <stdio.h>                    /* C-stdio library.             */
#include <string.h>                   /* string functions.            */
#include <stdlib.h>                   /* stdlib functions.            */
#include <errno.h>                    /* errno values.                */
#include "/usr/include/postgresql/libpq-fe.h"
 
 
#define LINELEN  80                   /* Max length of line.          */
 
static void
exit_nicely(PGconn *conn)
{
    PQfinish(conn);
    exit(1);
} 
 
/**********************************************************************/
/*                                                                    */
/* Function Name: writeData()                                         */
/*                                                                    */
/* Descriptive Name: Function is used to print the data to the        */
/* browser.  The data is printed 80 characters/line to provide        */
/* a neat and readable output.                                        */
/*                                                                    */
/* HTTP Server Environment variables:                                 */
/* ----------------------------------                                 */
/*                                                                    */
/* Standard Input:                                                    */
/* ---------------                                                    */
/*                                                                    */
/* Standard Output:                                                   */
/* ----------------                                                   */
/* All data directed to Standard output is sent using printf() or     */
/* putchar().  Standard output is written with html text.             */
/*                                                                    */
/*                                                                    */
/* Input: ptrToData : A pointer to the data to write to stdout.       */
/*        dataLen   : Length of data buffer.                          */
/*                                                                    */
/* Output: Data buffer written to stdout.                             */
/*                                                                    */
/* Exit Normal:                                                       */
/*                                                                    */
/* Exit Error: None                                                   */
/*                                                                    */
/**********************************************************************/
void writeData(char* ptrToData, int dataLen)
{
 
  div_t  insertBreak;
  int    i;
 
  /*------------------------------------------------------------------*/
  /* Write dataLen bytes of data from ptrToData.                      */
  /*------------------------------------------------------------------*/
  for (i=1; i<= dataLen; i++) {
 
      putchar(*ptrToData);
      ptrToData++;
 
      /*--------------------------------------------------------------*/
      /* Print a break after every 80 characters.                     */
      /*--------------------------------------------------------------*/
      insertBreak = div(i, LINELEN);
      if ( insertBreak.rem == 0 )       
          ;//printf("<br>");
 
  }
 
  return;
 
}
 
char *getParam(char** data, char* name)
{
	
}
 
 
 
/**********************************************************************/
/*                                                                    */
/* Function Name: main()                                              */
/*                                                                    */
/* Descriptive Name: A sample of the method used for iSeries ILE/C to */
/* read standard input, write standard output and check environment   */
/* variables; SERVER_SOFTWARE, REQUEST_METHOD, CONTENT_LENGTH, etc.   */
/*                                                                    */
/* HTTP Server Environment variables:                                 */
/* ----------------------------------                                 */
/* The C function call, getenv, is used to read iSeries server        */
/* environment variables.  The value of the argument is a (char *)    */
/* pointer with the name of the environment variable. The value of    */
/* the environment variable is always returned as a string pointer.   */
/* The value may need to be converted to be used; that is             */
/* CONTENT_LENGTH needs to be converted to int using atoi().          */
/*                                                                    */
/* Standard Input:                                                    */
/* ---------------                                                    */
/* CONTENT_LENGTH is used to determine the amount of data to be       */
/* read from standard input with fread().  The standard input is      */
/* considered to be a stream of bytes up to CONTENT_LENGTH bytes. The */
/* standard input can be read with any file input stream function up  */
/* to and including CONTENT_LENGTH bytes.  Reading more than          */
/* CONTENT_LENGTH bytes is not defined.                               */
/*                                                                    */
/* Standard Output:                                                   */
/* ----------------                                                   */
/* All data directed to Standard output is using writeData().         */
/*                                                                    */
/* Standard output is written with html text which includes HTTP      */
/* header lines identifying the content type of the data written and  */
/* HTTP response headers.  This MUST be followed by a blank line(\n\n)*/
/* before writing any html text.  This indicates the end of the       */
/* header and the start of text that is served from the server.       */
/* This text is usually html but can be plain/text.                   */
/*                                                                    */
/* Input: Data read from standard input or QUERY_STRING that is       */
/*        entered in an HTML form.                                    */
/*                                                                    */
/* Output: The data read from standard input is written as is to      */
/*         standard output.  This information would then be served by */
/*         the HTTP server.                                           */
/*                                                                    */
/* Exit Normal:                                                       */
/*                                                                    */
/* Exit Error: None                                                   */
/*                                                                    */
/**********************************************************************/
int main()
{
 
  char   *stdInData;                   /* Input buffer.               */
  char   *queryString;                 /* Query String env variable   */
  char   *requestMethod;               /* Request method env variable */
  char   *serverSoftware;              /* Server Software env variable*/
  char   *contentLenString;            /* Character content length.   */
  int    contentLength;                /* int content length          */
  int    bytesRead;                    /* number of bytes read.       */
  int    queryStringLen;               /* Length of QUERY_STRING      */
  char	 **data;  // Parsed args
 
  /*------------------------------------------------------------------*/
  /* The "Content-type" is the minimum request header that must be    */
  /* written to standard output.  It describes the type of data that  */
  /* follows.                                                         */
  /*------------------------------------------------------------------*/
  printf("Content-type: text/html\n");
 
  /*------------------------------------------------------------------*/
  /* VERY IMPORTANT! An extra newline must be written                 */
  /* after the request header.  In this case the request header is    */
  /* only the Content-type.  This tells the HTTP server that the      */
  /* request header is ended and the data follows.                    */
  /*------------------------------------------------------------------*/
  printf("\n");
 
  /*------------------------------------------------------------------*/
  /* This html text consists of a head and body section.  The head    */
  /* section has a title for the document.  The body section will     */
  /* contain standard input, QUERY_STRING, CONTENT_LENGTH,            */
  /* SERVER_SOFTWARE and REQUEST_METHOD.                              */
  /*------------------------------------------------------------------*/
  printf("<html>\n");
  printf("<head>\n");
  printf("<title>\n");
  printf("Покупка билета\n");
  printf("</title>\n");
  printf("</head>\n");
  printf("<body>\n");
  //printf("<h1>Sample iSeries ILE/C program.</h1>\n");
  //printf("<br>This is sample output writing in iSeries ILE/C\n");
  //printf("<br>as a sample of CGI programming.  This program reads\n");
  //printf("<br>the input data from Query_String environment\n");
  //printf("<br>variable when the Request_Method is GET and reads\n");
  //printf("<br>standard input when the Request_Method is POST.\n");
 
  /*------------------------------------------------------------------*/
  /* Get and write the REQUEST_METHOD to stdout.                      */
  /*------------------------------------------------------------------*/
  requestMethod = getenv("REQUEST_METHOD");
  //if ( requestMethod )
  //    printf("<h4>REQUEST_METHOD:</h4>%s\n", requestMethod);
  //else
  //    printf("Error extracting environment variable REQUEST_METHOD.\n");
 
  /*------------------------------------------------------------------*/
  /* html form data can be provided to the CGI program either on      */
  /* stdin or in environment variable QUERY_STRING.  This can be      */
  /* determined by examining REQUEST_METHOD.                          */
  /*------------------------------------------------------------------*/
  if ( strcmp(requestMethod,"POST") == 0 ) {
 
      /*--------------------------------------------------------------*/
      /* The REQUEST_METHOD is "POST".  The environment variable      */
      /* CONTENT_LENGTH will tell us how many bytes of data to read   */
      /* from stdin.  Note: CONTENT_LENGTH must be convert to an int. */
      /*--------------------------------------------------------------*/
      contentLenString = getenv("CONTENT_LENGTH");
      contentLength = atoi(contentLenString);
 
      /*--------------------------------------------------------------*/
      /* Write CONTENT_LENGTH to stdout.                              */
      /*--------------------------------------------------------------*/
      //printf("<h4>CONTENT_LENGTH:</h4>%i<br><br>\n",contentLength);
 
      if ( contentLength ) {
 
          /*----------------------------------------------------------*/
          /* Allocate and set memory to read stdin data into.         */
          /*----------------------------------------------------------*/
          stdInData = (char *)malloc(contentLength);
          if ( stdInData )
              memset(stdInData, 0x00, contentLength);
          else
              printf("ERROR: Unable to allocate memory\n");
          /*----------------------------------------------------------*/
          /* A CGI program MUST read standard input as a stream       */
          /* file only up to and including CONTENT_LENGTH bytes.      */
          /* Never should a program read more than CONTENT_LENGTH     */
          /* bytes.  A CGI program that reads standard input must     */
          /* never depend on an end of file flag.  This will cause    */
          /* unpredictable results when the CGI program reads         */
          /* standard input.                                          */
          /*----------------------------------------------------------*/
          printf("<h4>Server standard input:</h4>\n");
          bytesRead = fread((char*)stdInData, 1, contentLength, stdin);
 
          /*----------------------------------------------------------*/
          /* If we successfully read all bytes from stdin, format and */
          /* write the data to stdout using the writeData function.   */
          /*----------------------------------------------------------*/
		  //Parse data
		  // 2 - paramName + value, 6 params at all
		  data = malloc(2*6*sizeof(char*)); // [ "firstName", "Igor", "lastName", "Baranov", "year"]
		  for(int i=0; i<2*6; i++)
		  {
			  data[i] = (char *)malloc(200*sizeof(char)); // each param or value could be 200 length
			  if (data[i])
				memset(data[i], 0x00, 200*sizeof(char)); // fill with \0
		  }
          if ( bytesRead == contentLength )
		  {
			  int index = 0;
			  int data_i = 0;
			  while(index<bytesRead)
			  {
				  char ch = stdInData[index];
				  if(ch == '=' || ch == '&')
				  {
					  data_i++;
				  }
				  else
				  {
					  strncat(data[data_i], &ch, 1);
				  }
				  
				  index++;
			  }
              for(int i=0; i<2*6; i++)
			  {
				writeData(data[i], strlen(data[i]));
				printf("<br/>\n");
			  }
		  }
          else
              printf("<br>Error reading standard input\n");
 
          /*----------------------------------------------------------*/
          /* Free the storage allocated to hold the stdin data.       */
          /*----------------------------------------------------------*/
          free(stdInData);
 
      } else
          printf("<br><br><b>There is no standard input data.</b>");
 
  } else if (strcmp(requestMethod, "GET") == 0 ) {
      /*--------------------------------------------------------------*/
      /* The REQUEST_METHOD is "GET".  The environment variable       */
      /* QUERY_STRING will contain the form data.                     */
      /*--------------------------------------------------------------*/
      queryString = getenv("QUERY_STRING");
      if ( queryString ) {
 
          /*----------------------------------------------------------*/
          /* Write the QUERY_STRING data to stdout.                   */
          /*----------------------------------------------------------*/
          printf("<h4>Server input read from QUERY_STRING:</h4>");
          queryStringLen = strlen(queryString);
          if ( queryStringLen )
              writeData(queryString, queryStringLen);
          else
              printf("<b>There is no data in QUERY_STRING.</b>");
 
      } else
          printf("<br>Error getting QUERY_STRING variable.");
 
  } else
      printf("<br><h2>ERROR: Invalid REQUEST_METHOD.</h2>");

  printf("<hr/>Database output");
  printf("<div>");
  const char *conninfo;
  PGconn     *conn;
  PGresult   *res;
  int         nFields;
  int         i,
              j;

  /*
   * If the user supplies a parameter on the command line, use it as the
   * conninfo string; otherwise default to setting dbname=postgres and using
   * environment variables or defaults for all other connection parameters.
   */
  conninfo = "dbname = railroaddb";

  /* Make a connection to the database */
  conn = PQconnectdb(conninfo);

  /* Check to see that the backend connection was successfully made */
  if (PQstatus(conn) != CONNECTION_OK)
  {
      fprintf(stderr, "Connection to database failed: %s",
              PQerrorMessage(conn));
      exit_nicely(conn);
  }

  /* Set always-secure search path, so malicious users can't take control. */
  res = PQexec(conn, "SELECT pg_catalog.set_config('search_path', '', false)");
  if (PQresultStatus(res) != PGRES_TUPLES_OK)
  {
      fprintf(stderr, "SET failed: %s", PQerrorMessage(conn));
      PQclear(res);
      exit_nicely(conn);
  }

  /*
   * Should PQclear PGresult whenever it is no longer needed to avoid memory
   * leaks
   */
  PQclear(res);

  /*
   * Our test case here involves using a cursor, for which we must be inside
   * a transaction block.  We could do the whole thing with a single
   * PQexec() of "select * from pg_database", but that's too trivial to make
   * a good example.
   */

  /* Start a transaction block */
  res = PQexec(conn, "BEGIN");
  if (PQresultStatus(res) != PGRES_COMMAND_OK)
  {
      fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
      PQclear(res);
      exit_nicely(conn);
  }
  PQclear(res);

  /*
   * Fetch rows from pg_database, the system catalog of databases
   */
  res = PQexec(conn, "DECLARE myportal CURSOR FOR select * from railroad.\"Tickets\"");
  if (PQresultStatus(res) != PGRES_COMMAND_OK)
  {
      fprintf(stderr, "DECLARE CURSOR failed: %s", PQerrorMessage(conn));
      PQclear(res);
      exit_nicely(conn);
  }
  PQclear(res);

  res = PQexec(conn, "FETCH ALL in myportal");
  if (PQresultStatus(res) != PGRES_TUPLES_OK)
  {
      fprintf(stderr, "FETCH ALL failed: %s", PQerrorMessage(conn));
      PQclear(res);
      exit_nicely(conn);
  }

    /* first, print out the attribute names */
    nFields = PQnfields(res);
    for (i = 0; i < nFields; i++)
        printf("%-15s", PQfname(res, i));
    printf("<br><br>");

    /* next, print out the rows */
    for (i = 0; i < PQntuples(res); i++)
    {
        for (j = 0; j < nFields; j++)
            printf("%-15s", PQgetvalue(res, i, j));
        printf("<br>");
    }

    PQclear(res);

    /* close the portal ... we don't bother to check for errors ... */
    res = PQexec(conn, "CLOSE myportal");
    PQclear(res);

    /* end the transaction */
    res = PQexec(conn, "END");
    PQclear(res);

    /* close the connection to the database and cleanup */
    PQfinish(conn);
  printf("</div>");
  printf("End database output<hr/>");

  /*------------------------------------------------------------------*/
  /* Write break and paragraph html tag to stdout.                    */
  /*------------------------------------------------------------------*/
  printf("<br><p>\n");
 
 /*------------------------------------------------------------------*/
  /* Write the SERVER_SOFTWARE environment variable to stdout.        */
  /*------------------------------------------------------------------*/
  serverSoftware = getenv("SERVER_SOFTWARE");
  if ( serverSoftware )
      printf("<h4>SERVER_SOFTWARE:</h4>%s\n", serverSoftware);
  else
      printf("<h4>Server Software is NULL</h4>");
 
  /*-----------------------------------------------------------------*/
  /* Write the closing tags on HTML document.                        */
  /*-----------------------------------------------------------------*/
  printf("</p>\n");
  printf("</body>\n");
  printf("</html>\n");
  
  for(int i=0; i<2*6; i++)
  {
    free(data[i]);
  }
  free(data);
 
  return 0;
}
