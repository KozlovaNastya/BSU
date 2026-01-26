.SUFFIXES: .class .java
PACK=Program4
TARG=MatrixApp

JC=javac -g -encoding utf8
JM=java -ea
JR=jar -cfe

run: build
	$(JM) -cp bin $(PACK).MatrixTest

build: 
	$(JC) -d bin src/$(PACK)/*.java

jar: build
	$(JR) $(TARG).jar $(PACK).MatrixTest -C bin .

clean:
	rm -rf bin
	rm -f $(TARG).jar

.PHONY: clean build run jar