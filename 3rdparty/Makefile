.PHONY: fcgi libghttp spawn-fcgi clean

include ../header.mk

all:fcgi libghttp spawn-fcgi

fcgi:	
	$(MAKE) -C fcgi-2.4.0
libghttp:
	$(MAKE) -C libghttp-1.0.9
spawn-fcgi:
	$(MAKE) -C spawn-fcgi-1.6.4	


clean:
	$(MAKE) -C fcgi-2.4.0 clean 
	$(MAKE) -C libghttp-1.0.9 clean 
	$(MAKE) -C spawn-fcgi-1.6.4	clean 

