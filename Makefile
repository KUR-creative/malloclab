#
# Students' Makefile for the Malloc Lab
#
TEAM = bovik
VERSION = 1
HANDINDIR = /afs/cs.cmu.edu/academic/class/15213-f01/malloclab/handin

CC = gcc
CFLAGS = -Wall -O0 -m32 -g
#CFLAGS = -Wall -O2 -m32

LIB = -lcmocka 

OBJS = mdriver.o mm.o memlib.o fsecs.o fcyc.o clock.o ftimer.o

#mdriver: $(OBJS)
	#$(CC) $(CFLAGS) -o mdriver $(OBJS)

ta: $(OBJS)
	$(CC) $(CFLAGS) -o mdriver $(OBJS) 
	python auto-grader.py
t:
	#-- screen s1 --
	screen -S s1 -X stuff "clear"
	screen -S s1 -X stuff "$(CC) $(CFLAGS) -c memlib.c memlib.h 2>&1 "
	screen -S s1 -X stuff "$(CC) $(CFLAGS) -o mm-test memlib.c memlib.h mm.c mm.h mm-test.c $(LIB) 2>&1 | python printer.py"
	screen -S s1 -X stuff "./mm-test 2>&1 | python printer.py"
	#-- here --
	$(CC) $(CFLAGS) -c memlib.c memlib.h 
	$(CC) $(CFLAGS) -o mm-test memlib.c memlib.h mm.c mm.h mm-test.c $(LIB)
	./mm-test 2>&1 | python printer.py		#stderr to stdout.

# ^ screen s1 session must be initailaized.
# gnome-terminal 폰트 크기 조절 arg를 알아야 함.
# 나중에 빔 초기화 단축키 등록: 스크린을 자동생성함.
# 지금은 컴파일을 두번(...)하고 있음. 결과를 카피하는 법을 알아내라.
# :make를 응용하는 방법도 알아내라.

		    	
full: $(OBJS)
	$(CC) $(CFLAGS) -o mdriver $(OBJS)
	#----------------------------------------------------------------
	./mdriver -vlga -f traces/short1.rep
	#----------------------------------------------------------------
	./mdriver -vlga -f traces/short2.rep
	#----------------------------------------------------------------
	./mdriver -vlga -f traces/amptjp-bal.rep
	#----------------------------------------------------------------
	./mdriver -vlga -f traces/binary-bal.rep
	#----------------------------------------------------------------
	./mdriver -vlga -f traces/binary2-bal.rep
	#----------------------------------------------------------------
	./mdriver -vlga -f traces/cccp-bal.rep
	#----------------------------------------------------------------
	./mdriver -vlga -f traces/coalescing-bal.rep
	#----------------------------------------------------------------
	./mdriver -vlga -f traces/cp-decl-bal.rep
	#----------------------------------------------------------------
	./mdriver -vlga -f traces/expr-bal.rep
	#----------------------------------------------------------------
	./mdriver -vlga -f traces/random-bal.rep
	#----------------------------------------------------------------
	./mdriver -vlga -f traces/random2-bal.rep
	#----------------------------------------------------------------
	./mdriver -vlga -f traces/realloc-bal.rep
	#----------------------------------------------------------------
	./mdriver -vga -f traces/realloc2-bal.rep

mdriver.o: mdriver.c fsecs.h fcyc.h clock.h memlib.h config.h mm.h
memlib.o: memlib.c memlib.h
	#$(CC) $(CFLAGS) -o memlib.o memlib.c memlib.h
mm.o: mm.c mm.h memlib.h
fsecs.o: fsecs.c fsecs.h config.h
fcyc.o: fcyc.c fcyc.h
ftimer.o: ftimer.c ftimer.h config.h
clock.o: clock.c clock.h

handin:
	cp mm.c $(HANDINDIR)/$(TEAM)-$(VERSION)-mm.c

clean:
	rm -f *~ *.o mdriver


