# Makefile for All Sorts + Evaluation

CXX = g++
CXXFLAGS = -Wall -std=c++23 -g
LDFLAGS =

# 정렬 알고리즘 cpp들
SORT_SOURCES = bubbleSort.cpp heapSort.cpp insertionSort.cpp \
               mergeSort.cpp quickSort.cpp selectionSort.cpp \
               combSort.cpp CSSort.cpp introSort.cpp \
               librarySort.cpp TimSort.cpp TSort.cpp

EVAL_SRC = Eval.cpp
HEADERS = Eval.h

# 실행파일 이름 추출 (확장자 제거)
BINARIES = $(patsubst %.cpp,%,$(SORT_SOURCES))

# === Default ===
all: $(BINARIES)

# === 각 정렬 소스 빌드: bubbleSort, heapSort 등 ===
%: %.cpp $(EVAL_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $< $(EVAL_SRC) -o $@ $(LDFLAGS)

# === 정리 ===
clean:
	@echo "🧹 Cleaning all binaries and object files..."
	@rm -f $(BINARIES) *.o *.out core

coreclean:
	@echo "🧼 Removing files matching '*Sort*' but not '*.cpp'..."
	@find . -type f -name '*Sort*' ! -name '*.cpp' -exec rm -v {} \;

