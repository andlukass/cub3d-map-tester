SRCS = src/main.c                     \
		src/change_dir.c              \
		src/add_map.c                 \
		src/get_maps.c                \
		src/add_result.c              \
		src/run_tester.c              \

NAME = tester

all: $(NAME)

$(NAME): 
	@$(CC) $(SRCS) -o $(NAME)
	@echo "tester compiled!"

clean:
	@rm -rf $(NAME)

re: clean all

run: re
	@./$(NAME)

.PHONY: all clean re run