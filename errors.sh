# error: syntax error near unexpected token `|, &&, ||, ) or (`
    - echo hello > |
    - ( echo hi > | cat )
    - echo hello > &&
    - echo hello > ||
    - echo hello > )
    - ( echo hello > )
    - echo hello > (

# error: syntax error near unexpected token `newline`
    - echo hello >
    - echo hello >>
    - echo hello <
    - cat <<
    - echo hi &&
    - echo hi ||

# error: syntax error near unexpected token `>>`
    echo hello >>> file

# error: syntax error near unexpected token `<<`
    - cat <<<< file
