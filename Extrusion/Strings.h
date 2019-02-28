//-- Parse Unsigned Integer
//--
template<typename Type>
Type ParseIntU( 
  const char* bytes, uint8_t count, Type pass )
{
  if( count < 2 ) 
    return pass;
    
  Type value = 0;
  for( uint8_t index = 1; index < count; index++ )
  {
    Type digit = bytes[index] - '0';
    if( digit >= 0 
     && digit <= 9 )
     value = 10 * value + digit;  
  }
  return value;
}

//-- Parse Signed Integer
//--
template<typename Type>
Type ParseIntS( 
  const char* bytes, uint8_t count,Type pass )
{
  if( count < 2 ) 
    return pass;
    
  Type value = 0;
  Type sign  = 1;  
  for( uint8_t index = 1; index < count; index++ )
  {
    Type digit = bytes[index] - '0';
    if( digit >= 0 
     && digit <= 9 )
     value = 10 * value + digit;  
    else if( bytes[index] == '-' )
     sign *= -1;
  }
  return sign * value;
}