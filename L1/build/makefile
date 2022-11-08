.PHONY: all clean

DIRS = $(L1PATH)/source/PCB/src \
	$(L1PATH)/source/cpu/src \
	$(L1PATH)/source/main/src

RM = rm
RMFLAGS = -rf
RMS = $(L1PATH)/build/exes $(L1PATH)/build/libs 

all:
	
	@set -e ; \
	for dir in $(DIRS) ; \
		do \
		cd $$dir && $(MAKE) gdb; \
	done
	@echo ""
	@echo ":-) Completed"
	@echo ""
clean:
	@set -e ; \
	for dir in $(DIRS) ; \
		do \
		cd $$dir && $(MAKE) clean ; \
	done
	$(RM) $(RMFLAGS) $(RMS)
	@echo ""
	@echo ":-) Completed"
	@echo ""