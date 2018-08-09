#ifndef I_CONTAINER_BASE_H
#define I_CONTAINER_BASE_H

#define DC_ERR			0x0
#define DC_INT			0x1	
#define DC_FLOAT		0x2	
#define DC_STRING		0x4
#define DC_CHARARR		0x8
#define DC_TIME     	0x10
#define DC_BOOL		    0x20
#define DC_DC			0x40
#define DC_VAR			0x80
#define DC_END			(0x1 << 15)
#define DC_ARRAY		(0x1 << 16)	

#define DCMemType		unsigned int

#endif