#pragma once

// 8-bit unsigned integer
typedef unsigned char 		uint8;
	
// 16-bit unsigned integer
typedef unsigned short int	uint16;
	
// 32-bit unsigned integer
typedef unsigned int		uint32;
	
// 64-bit unsigned integer
typedef unsigned long long	uint64;

//~ Signed base types.
	
// 8-bit signed integer
typedef	signed char			int8;
	
// 16-bit signed integer
typedef signed short int	int16;
// 32-bit signed integer
typedef signed int	 		int32;
// 64-bit signed integer
typedef signed long long	int64;

inline uint32 GetTypeHash( const uint64 A )
{
	return (uint32)A+((uint32)(A>>32) * 23);
}