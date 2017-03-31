
void get_ini_dataType(char title[],char value[],char symbol){
    if (symbol == 'f')
        float value = 0.0f;
    
    int ini_no;
    if (number_ini <= 0) return (NULL);
    ini_no =  find_ini_title(title);
    if ( ini_no < 0 ) return( NULL );
    value = atof ( &ini_value[ini_no][0] );
    return( value );

}




bool get_ini_str ( char title[], char value[]  )/* calls find_ini_title, ini_value */
{
  int ini_no,i,len;
  value[0] = NULL;
  if ( number_ini <= 0  ) return( false  );
  ini_no = find_ini_title ( title  );
  if ( ini_no < 0  ) return( false  );
  len = (int)strlen( &ini_value[ini_no][0]  );
  if ( len <= 0  )  return( false  );
  i = -1;
  do
  {
    i = i + 1; 
    value[i] = ini_value[ini_no][i];
  } while ( ini_value[ini_no][i] != NULL  );
  return( true  );
  } /* get_ini_str */
        

float get_ini_float ( char title[] )
/*
   calls find_ini_title, ini_value
*/
{
    float value = 0.0f;
    int ini_no;
    if ( number_ini <= 0 ) return( NULL );
    ini_no = find_ini_title ( title );
    if ( ini_no < 0 ) return( NULL );
    value = atof ( &ini_value[ini_no][0] );
    return( value );
} /* get_ini_float */
/************************************************/

double get_ini_double ( char title[] )
/*
   calls find_ini_title, ini_value
*/
{
    double value = 0.0;
    int ini_no;
    if ( number_ini <= 0 ) return( NULL );
    ini_no = find_ini_title ( title );
    if ( ini_no < 0 ) return( NULL );
    value = strtod ( &ini_value[ini_no][0], NULL );
    return( value );
} /* get_ini_double */

char* get_ini_char ( char title[] )
/*
   calls find_ini_title, ini_value
*/
{
    char* value;
    int ini_no;
    value = NULL;
    if ( number_ini <= 0 ) return( NULL );
    ini_no = find_ini_title ( title );
    if ( ini_no < 0 ) return( NULL );
    return( &ini_value[ini_no][0] );

} /* get_ini_char */
/************************************************/

int get_ini_int ( char title[] )
/*
   calls find_ini_title, ini_value
*/
{
    int value = 0;
    int ini_no;
    if ( number_ini <= 0 ) return( NULL );
    ini_no = find_ini_title ( title );
    if ( ini_no < 0 ) return( NULL );
    value = atoi ( &ini_value[ini_no][0] );
    //printf ( " ini_no %d value %d\n", ini_no, value );
    return( value );

} /* get_ini_int */
bool get_ini_bool ( char title[] )
{
    bool value;
    int ini_no;
    value = -1;NULL;
    if ( number_ini <= 0 ) return( NULL );
    ini_no = find_ini_title ( title );
    if ( ini_no < 0 ) return( NULL );
    if ( toupper( ini_value[ini_no][0] ) == 'T' )
        return( true );
    if ( toupper( ini_value[ini_no][0] ) == 'F' )
        return( false );
    return( NULL );

} /* get_ini_bool */
/************************************************/


void get_ini_dump ( void )
{
    int ini_no;
    printf ( "  number ini %d\n", number_ini );
    if ( number_ini <= 0 ) return;
    for ( ini_no = 0; ini_no < number_ini; ini_no++ )
    {
        printf ( " ini_no %2d title %s value %s\n",
            ini_no, &ini_title[ini_no][0], &ini_value[ini_no][0] );
    }
} /* get_ini_dump */
/************************************************/

bool get_if_ini ( void )
{
    if ( number_ini > 0 ) return( true );
    return( false );
} /* get_if_ini */
/************************************************/


