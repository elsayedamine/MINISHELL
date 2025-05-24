#!/bin/bash

MINISHELL=./minishell  # Update if needed

run_test() {
	echo "➤ $1"
	echo "$1" | $MINISHELL
	echo "---------------------------"
}

echo "===== Minishell Syntax Tests ====="

# Pipes
run_test "| ls"
run_test "ls |"
run_test "ls || wc"
run_test "ls | | wc"

# Redirections
run_test "ls >"
run_test "cat <"
run_test "echo hi >>"
run_test "cat <<"
run_test ">>> file"
run_test "< > file"

# Quotes
run_test "echo 'hello"
run_test 'echo "hello'
run_test "echo \"hello'"

# Logical operators (if supported)
run_test "&& ls"
run_test "ls &&"
run_test "ls &&& echo hi"

# Parentheses (if supported)
run_test "( ls"
run_test "ls )"
run_test "()"
run_test "((ls))"

# Here-document
run_test "cat <<"
run_test "cat << | wc"

# Valid commands (should work!)
run_test "echo hello"
run_test "ls | wc"
run_test "echo hi > out.txt"

# Cleanup
rm -f out.txt
