all: test-sequitur sequitur
test-sequitur:
	g++  -o TestSequitur TestSequitur.cpp SequiturGrammar.cpp Dictionary.cpp Rule.cpp Node.cpp
sequitur:
	g++ -o Sequitur Sequitur.cpp SequiturGrammar.cpp Dictionary.cpp Rule.cpp Node.cpp
clean:
	rm -f Sequitur TestSequitur
