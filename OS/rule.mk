VPATH = TARGET_DIR

$(TARGET): $(DEPEND)
%.o : %.c
	$(CC) -c -I $(INCLUDE_DIR) $(CFLAGS) $< -o $@