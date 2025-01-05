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
    "echo \"mixed 'single and \$HOME'\""

    # Environment variable expansion
    "echo \$HOME"
    "echo \$USER"
    "echo \$NOT_DEFINED"
    "echo \"My home is \$HOME\""
    "export MY_VAR=42; echo \$MY_VAR"

    # Special characters
    "echo \$?"
    "echo \\$HOME"
    "echo \$\$"
    "echo \"Escaped \\\"quotes\\\" and \$HOME\""

    # Pipes and redirections
    "ls -l | grep .c"
    "cat < input.txt | grep foo > output.txt"
    "echo foo > temp.txt && cat temp.txt"

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

    # Logical operators (if supported)
    "true && echo success"
    "false || echo failure"
    "echo start && false || echo fallback"

    # Advanced variable expansion
    "echo \${USER:-default}"
    "echo \${HOME:?Error: HOME is not set}"
    "echo \"\$HOME/\$USER\""
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
