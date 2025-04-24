#!/bin/bash

echo "---- MiniShell Grammar Parsing Test ----"

tests=(
  # ✅ Valid Commands
  "echo hello"                         # ✅
  "echo 'hello world'"                # ✅
  "echo \"hello \$USER\""             # ✅
  "ls -l | grep minishell"            # ✅
  "cat < infile > outfile"            # ✅
  "echo hi >> file"                   # ✅
  "cat << EOF\nhello\nEOF"            # ✅
  "echo hi | grep h | wc -l"          # ✅
  "export VAR=123"                    # ✅
  "export VAR+=456"                   # ✅
  "unset VAR"                         # ✅

  # ❌ Invalid Commands
  "|"                                 # ❌ starts with pipe
  "| ls"                              # ❌ starts with pipe
  "ls || grep minishell"              # ❌ double pipe not supported
  "echo > > file"                     # ❌ invalid redirection
  "echo < > file"                     # ❌ ambiguous redirection
  ">"                                 # ❌ just redirection without command
  "<"                                 # ❌ same here
  "echo hello |"                      # ❌ ends with pipe
  "cat <<EOF"                         # ❌ missing heredoc end
  "echo 'unclosed string"             # ❌ unclosed quote
  "export 1INVALID=42"                # ❌ invalid identifier
)

for test in "${tests[@]}"
do
  echo -e "\n🧪 Test: $test"
  echo "$test" | bash -c "$test" 2>/dev/null && echo "✅ Valid" || echo "❌ Invalid"
done

