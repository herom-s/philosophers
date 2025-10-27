#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
42 School C Project Template Generator
"""

import os
import subprocess
import sys


def run_command(cmd, cwd=None, interactive=False):
    """Run a shell command and return success status"""
    try:
        if interactive:
            # For interactive commands (like git that may need passphrase)
            result = subprocess.run(cmd, shell=True, cwd=cwd, check=True)
            return True, ""
        else:
            result = subprocess.run(cmd, shell=True, cwd=cwd, check=True, 
                                  capture_output=True, text=True)
            return True, result.stdout
    except subprocess.CalledProcessError as e:
        if interactive:
            return False, "Command failed"
        return False, e.stderr


def get_yes_no(prompt):
    """Get yes/no input from user"""
    while True:
        response = input(f"{prompt} (y/n): ").lower().strip()
        if response in ['y', 'yes']:
            return True
        elif response in ['n', 'no']:
            return False
        print("Please answer 'y' or 'n'")


def create_directory_structure(has_bonus=False):
    """Create the basic project directory structure"""
    dirs = [
        "src",
        "inc",
        "obj"
    ]
    
    if has_bonus:
        dirs.append("src_bonus")
    
    for d in dirs:
        os.makedirs(d, exist_ok=True)
        print(f"[OK] Created directory: {d}")

def create_makefile(project_name, has_bonus=False, has_libft=False, has_minilibx=False):
    """Create a basic Makefile"""
    # Library sections
    lib_vars = ""
    lib_rules = ""
    lib_clean_rules = ""
    lib_fclean_rules = ""
    lib_deps = ""
    lib_links = ""

    if has_libft:
        lib_vars += "\n# Libft\nLIBFT_DIR = libft\nLIBFT = $(LIBFT_DIR)/libft.a"
        lib_deps += " $(LIBFT)"
        lib_links += " -L$(LIBFT_DIR) -lft"
        lib_rules += "\n$(LIBFT):\n\t@make -C $(LIBFT_DIR)\n"
        lib_clean_rules += "\t@make -C $(LIBFT_DIR) clean\n"
        lib_fclean_rules += "\t@make -C $(LIBFT_DIR) fclean\n"

    if has_minilibx:
        lib_vars += "\n# Minilibx\nMLX_DIR = minilibx\nMLX = $(MLX_DIR)/libmlx.a"
        lib_deps += " $(MLX)"
        lib_links += " -L$(MLX_DIR) -lmlx"
        lib_rules += "\n$(MLX):\n\t@make -C $(MLX_DIR)\n"
        lib_clean_rules += "\t@make -C $(MLX_DIR) clean\n"
        lib_fclean_rules += "\t@make -C $(MLX_DIR) fclean\n"

    # Includes
    includes = "-I./inc"
    if has_libft:
        includes += " -I$(LIBFT_DIR)"
    if has_minilibx:
        includes += " -I$(MLX_DIR)"

    # Bonus section - only variables here
    bonus_vars = ""
    bonus_section = ""
    bonus_clean = ""
    if has_bonus:
        bonus_vars = "\nBONUS_DIR = src_bonus\nBONUS_OBJ_DIR = obj_bonus\nBONUS_FILES = main_bonus.c\nBONUS_SRC = $(addprefix $(BONUS_DIR)/, $(BONUS_FILES))\nBONUS_OBJ = $(BONUS_SRC:$(BONUS_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)\n"
        # Rules will be added after the main rules
        bonus_rule = "\nbonus:" + lib_deps + " $(BONUS_OBJ)\n\t$(CC) $(CFLAGS) $(BONUS_OBJ)" + lib_links + " -o $(NAME)\n\t@echo \"[OK] $(NAME) bonus compiled successfully\"\n"
        bonus_obj_rule = "\n$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c\n\t@mkdir -p $(BONUS_OBJ_DIR)\n\t$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@\n"
        bonus_section = bonus_rule + bonus_obj_rule
        bonus_clean = "\t@rm -rf $(BONUS_OBJ_DIR)\n"

    phony_targets = "all clean fclean re"
    if has_bonus:
        phony_targets += " bonus"

    makefile_content = f"""
NAME = {project_name}

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = {includes}

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

SRC_FILES = main.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o){lib_vars}{bonus_vars}
all: $(NAME)
{lib_rules}$(NAME):{lib_deps} $(OBJ)
\t$(CC) $(CFLAGS) $(OBJ){lib_links} -o $(NAME)
\t@echo "[OK] $(NAME) compiled successfully"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
\t@mkdir -p $(OBJ_DIR)
\t$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
{bonus_section}
clean:
\t@rm -rf $(OBJ_DIR)
{bonus_clean}{lib_clean_rules}\t@echo "[OK] Object files removed"

fclean: clean
\t@rm -f $(NAME)
{lib_fclean_rules}\t@echo "[OK] $(NAME) removed"

re: fclean all

.PHONY: {phony_targets}
"""

    with open("Makefile", 'w') as f:
        f.write(makefile_content)
    print(f"[OK] Created Makefile")

def create_main_c():
    """Create a basic main.c file"""
    main_content = """

#include <stdio.h>

int main(int argc, char **argv)
{
    printf("Hello, 42!\\n");
    return (0);
}
"""
    
    with open("src/main.c", 'w') as f:
        f.write(main_content)
    print(f"[OK] Created src/main.c")


def create_bonus_main_c():
    """Create a basic main_bonus.c file"""
    bonus_main_content = """

#include <stdio.h>

int main(int argc, char **argv)
{
    printf("Hello, 42 Bonus!\\n");
    return (0);
}
"""
    
    with open("src_bonus/main_bonus.c", 'w') as f:
        f.write(bonus_main_content)
    print(f"[OK] Created src_bonus/main_bonus.c")


def create_gitignore(project_name):
    """Create .gitignore file"""
    gitignore_content = """# Object files
*.o
obj/

# Executable
{name}

# Libraries
*.a

# System files
.DS_Store
*~
*.swp

# Editor files
.vscode/
.idea/
"""
    
    with open(".gitignore", 'w') as f:
        f.write(gitignore_content.format(name=project_name))
    print(f"[OK] Created .gitignore")


def init_git_repo():
    """Initialize git repository"""
    # Check if already a git repo
    if os.path.exists(".git"):
        print(f"[OK] Git repository already initialized")
        return True
    
    success, output = run_command("git init")
    if success:
        print(f"[OK] Initialized git repository")
        return True
    else:
        print(f"[ERROR] Failed to initialize git repository: {output}")
        return False


def add_submodule(submodule_name):
    """Add a git submodule"""
    print(f"\n--- Adding {submodule_name} submodule ---")
    url = input(f"Enter the git URL for {submodule_name}: ").strip()
    
    if not url:
        print(f"[ERROR] URL cannot be empty, skipping {submodule_name}")
        return False
    
    # First, try to detect the default branch
    print(f"Detecting default branch for {submodule_name}...")
    detect_cmd = f"git ls-remote --symref {url} HEAD"
    success, output = run_command(detect_cmd)
    
    default_branch = "main"
    if success and output:
        # Parse the output to find the default branch
        for line in output.split('\n'):
            if 'ref: refs/heads/' in line:
                default_branch = line.split('ref: refs/heads/')[1].split()[0]
                print(f"Detected default branch: {default_branch}")
                break
    
    branch = input(f"Enter the branch name (default: {default_branch}): ").strip() or default_branch
    
    # Try adding the submodule with the specified branch
    cmd = f"git submodule add -b {branch} {url} {submodule_name}"
    success, output = run_command(cmd)
    
    if success:
        print(f"[OK] Added {submodule_name} submodule from {url} (branch: {branch})")
        return True
    else:
        # If it failed, try without specifying a branch (use repo default)
        print(f"[WARNING] Failed with branch '{branch}', trying without branch specification...")
        cmd = f"git submodule add {url} {submodule_name}"
        success, output = run_command(cmd)
        
        if success:
            print(f"[OK] Added {submodule_name} submodule from {url} (using repository default branch)")
            return True
        else:
            print(f"[ERROR] Failed to add {submodule_name} submodule: {output}")
            return False


def main():
    print("=" * 60)
    print("42 School C Project Template Generator")
    print("=" * 60)
    
    project_name = input("\nEnter project name: ").strip()
    
    if not project_name:
        print("Error: Project name cannot be empty")
        sys.exit(1)
    
    print(f"\nSetting up project in current directory: {os.getcwd()}")
    print("-" * 60)
    
    # Ask about bonus before creating structure
    has_bonus = get_yes_no("\nDoes this project have bonus?")
    
    # Ask about libraries
    has_libft = get_yes_no("\nDoes this project need libft?")
    has_minilibx = get_yes_no("\nDoes this project need minilibx?")
    
    # Create basic structure
    create_directory_structure(has_bonus)
    create_makefile(project_name, has_bonus, has_libft, has_minilibx)
    create_main_c()
    if has_bonus:
        create_bonus_main_c()
    create_gitignore(project_name)
    
    # Initialize git
    if not init_git_repo():
        print("Warning: Git repository not initialized. Skipping submodules.")
        sys.exit(0)
    
    # Add submodules
    if has_libft:
        add_submodule("libft")
    
    if has_minilibx:
        add_submodule("minilibx")
    
    print("\n" + "=" * 60)
    print(f"[OK] Project '{project_name}' created successfully!")
    print("=" * 60)
    print(f"\nNext steps:")
    print(f"  make")
    if has_bonus:
        print(f"  make bonus")
    print(f"\nDon't forget to update the Makefile header with your information!")


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n\nOperation cancelled by user")
        sys.exit(1)
    except Exception as e:
        print(f"\nError: {e}")
        sys.exit(1)
