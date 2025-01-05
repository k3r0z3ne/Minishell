#!/bin/bash

# Test script for Minishell components: lexer, parser, and expander.

# Location of Minishell executable
MINISHELL="../minishell"

# Array of test cases
test_cases=(
    # Simple commands
    "echo hello world"
    "ls -l | grep .c"
    "pwd"

    # Quotes handling
    "echo 'single quotes test'"
    "echo \"double quotes test\""
    "echo \"nested 'single' in double\""
    "echo 'nested \"double\" in single'"

    # Environment variable expansion
    "echo \$HOME"
    "echo \$USER"
    "echo \$NOT_DEFINED"
    "export MY_VAR=42; echo \$MY_VAR"

    # Special cases
    "echo \$?"
    "echo \$\$" # If \$\$ expansion is supported in your shell

    # Pipes and redirections
    "ls -l | grep .c"
    "cat < input.txt | grep foo > output.txt"
    "echo foo > temp.txt"

    # Syntax errors
    "echo unclosed 'quote"
    "echo \"unclosed double quote"
    "ls | | grep foo"
    "cat <"
    "| echo invalid pipe start"
    "echo 'valid' |"
    "echo >"
    "echo > file > file2"

    # Redirections
    "echo hello > file"
    "cat < file"
    "echo hello >> file"
    "cat << EOF"

    # Advanced usage
    "echo \$HOME/\$USER"
    "echo middle || echo fallback"
    "echo 'testing \$HOME inside single quotes'"
)

# Function to run a single test
run_test() {
    local test_input="$1"
    echo "Running test: $test_input"
    echo "$test_input" | $MINISHELL
    echo "--------------------------"
}

# Run all tests
echo "Starting lexer, parser, and expander tests..."
for test in "${test_cases[@]}"; do
    run_test "$test"
done

echo "All tests completed."
