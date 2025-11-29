NAME := cub3D

SRC_DIR := ./src
BUILD_DIR := ./build
LIBS_DIR := ./libs

LIBMLX := /usr/local/lib/libmlx42.a

FTLIBC_DIR := $(LIBS_DIR)/ftlibc
FTLIBC := $(FTLIBC_DIR)/ftlibc.a

MLX_AUX_DIR := $(LIBS_DIR)/mlx_aux
MLX_AUX := $(MLX_AUX_DIR)/mlx_aux.a

HEADERS := $(shell find $(SRC_DIR) -type f -name "*.h")
SRCS := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

INCLUDES := -I$(SRC_DIR)/include

CFLAGS := -Wall -Wextra -Werror -Ofast
LDFLAGS := -ldl -lglfw -pthread -lm

all: $(NAME)

$(NAME): $(FTLIBC) $(MLX_AUX) $(OBJS) | $(BUILD_DIR)
	$(CC) $(OBJS) $(CFLAGS) -Wl,--start-group $(LIBMLX) $(MLX_AUX) $(FTLIBC) -Wl,--end-group -o $(NAME) $(LDFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(FTLIBC): $(shell find -L $(FTLIBC_DIR) -name '*.[ch]')
	make -C $(FTLIBC_DIR) "CFLAGS := $(CFLAGS)"

$(MLX_AUX): $(shell find -L $(MLX_AUX_DIR) -name '*.[ch]')
	make -C $(MLX_AUX_DIR) "CFLAGS := $(CFLAGS)"

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	make -C $(FTLIBC_DIR) clean
	make -C $(MLX_AUX_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(FTLIBC_DIR) fclean
	make -C $(MLX_AUX_DIR) fclean

re: fclean all

print-%:
	@echo $($*)
