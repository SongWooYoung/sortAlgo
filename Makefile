#Makefile

SANFLAGS = -fsanitize=address
CXXFLAGS += -Wall -std=c++23 -g $(SANFLAGS)
LDFLAGS += $(SANFLAGS)

clean:
	rm -f all *.out *.o main EvalRespect coreclean:
	@echo "Cleaning up files containing 'Sort' (except .cpp files)..."
	@find . -type f -name '*Sort*' ! -name '*.cpp' -exec rm -v {} \;

	
