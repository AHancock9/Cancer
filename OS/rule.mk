VPATH += $(RULE_TARGET_DIR)
#PRIVATES UNEXPORT
unexport RULE_TARGET_DIR
unexport RULE_SUB_SYSTEM
unexport RULE_TARGET_DEPEND
unexport RULE_TARGET

all: make_dir subsystem $(RULE_TARGET)

#MAKE TARGET DIRECTORIES
make_dir:
	@if not exist $(RULE_TARGET_DIR) $(MKDIR) $(RULE_TARGET_DIR) 
	
#MAKE THE MAKEFILES OF SUB SYSTEM IN SUB DIRECTORY
subsystem:
ifneq ($(strip $(RULE_SUB_SYSTEM)),)
	$(foreach tmp,$(RULE_SUB_SYSTEM),$(MAKE) -C ./$(tmp) &))
endif

$(RULE_TARGET):$(RULE_TARGET_DEPEND)

clean:
	@if exist $(RULE_TARGET_DIR)\*.o $(DELETE) $(RULE_TARGET_DIR)\*.o
	@if exist $(RULE_TARGET_DIR)\*.bin $(DELETE) $(RULE_TARGET_DIR)\*.bin
	@if exist $(RULE_TARGET_DIR)\*.elf $(DELETE) $(RULE_TARGET_DIR)\*.elf
ifneq ($(strip $(RULE_SUB_SYSTEM)),)
	$(foreach tmp,$(RULE_SUB_SYSTEM),$(MAKE) clean -C ./$(tmp) &))
endif

%.o : %.c
	$(GCC) -c $< $(INCLUDES) $(OPTION)  -o $(RULE_TARGET_DIR)\$@
%.o : %.s
	$(GCC) -c $< $(INCLUDES) $(OPTION)  -o $(RULE_TARGET_DIR)\$@
%.elf : %.o
	$(GCC) $(OPTION) -o $(RULE_TARGET_DIR)\$@ -e $(RULE_ENTRY) \
		-T$(LDS_FILE) $(RULE_LINK_FILE) $(PLATFORM_LIB) 
%.bin : %.elf
	$(OBYCOPY) -O binary -S $(RULE_TARGET_DIR)\$< $(RULE_TARGET_DIR)\$@	
	
	
	