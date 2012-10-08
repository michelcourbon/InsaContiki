
# give your project name
CONTIKI_PROJECT = testsht15
 
all: $(CONTIKI_PROJECT)

# security if makefile.target don't exist
ifndef TARGET
	TARGET=wismote
endif

UIP_CONF_IPV6=1

# include the Contiki makefile, and so the others makefile
CONTIKI = ../../..
include $(CONTIKI)/Makefile.include
