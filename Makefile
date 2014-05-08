CXXFLAGS=-Wall -std=c++11

deal: final_project.o
	${CXX} -o $@ $^

.PHONY: clean
clean:
	rm -f *.o deal
