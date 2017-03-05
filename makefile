#############################################################################
#  COSC2138/CPT220 - Programming Principles 2A
# SP2 2015 Assignment #2 - word link program
# Full Name        : CALLUM MICHAEL SULLIVAN
# Student Number   : s3506523
# 
# Start up code provided by the C Teaching Team
#############################################################################

#The commented out lines are what the makefile would look like with list.h and list.c.

wordlink: wordlink_utility.o wordlink_options.o wordlink.o
	gcc -o wordlink wordlink_utility.o wordlink_options.o wordlink.o


#wordlink: wordlink_utility.o wordlink_options.o wordlink.o list.o
#	gcc -o wordlink list.o wordlink_utility.o wordlink_options.o wordlink.o


#list.o: list.c list.h wordlink_utility.h wordlink_options.h wordlink.h
#	gcc -c -ansi -pedantic -Wall list.c


wordlink_utility.o: wordlink_utility.c wordlink_utility.h wordlink_options.h wordlink.h
	gcc -c -ansi -pedantic -Wall wordlink_utility.c

#wordlink_utility.o: wordlink_utility.c wordlink_utility.h list.h wordlink_options.h wordlink.h
#	gcc -c -ansi -pedantic -Wall wordlink_utility.c


wordlink_options.o: wordlink_options.c wordlink_options.h wordlink_utility.h wordlink.h
	gcc -c -ansi -pedantic -Wall wordlink_options.c


#wordlink_options.o: wordlink_options.c wordlink_options.h list.h wordlink_utility.h wordlink.h
#	gcc -c -ansi -pedantic -Wall wordlink_options.c


wordlink.o: wordlink.c wordlink.h wordlink_utility.h wordlink_options.h
	gcc -c -ansi -pedantic -Wall wordlink.c


#wordlink.o: wordlink.c wordlink.h list.h wordlink_utility.h wordlink_options.h
#	gcc -c -ansi -pedantic -Wall wordlink.c

archive:
	zip $(USER)-a2.zip wordlink.c wordlink.h wordlink_options.c \
	wordlink_options.h wordlink_utility.c wordlink_utility.h \
	makefile readme.txt

