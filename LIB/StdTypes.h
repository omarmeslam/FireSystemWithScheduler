

#ifndef STDTYPES_H_
#define STDTYPES_H_


typedef unsigned char u8;
typedef signed char s8;
typedef  char c8;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned long u32;
typedef signed long s32;

typedef enum{
	FALSE,
	TRUE
}Bool_t;

typedef enum{
	OK,
	NOK,
	DONE,
	NULL_PTR,
	OUTOFRANGE
}Error_t;

#define  NULLPTR  ((void*)0)




#endif /* STDTYPES_H_ */
