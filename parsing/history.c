/*

to save history:

rl_on_new_line
>to start new line
add_history
>once line is finished to add to history
rl_clear_history
>juste before exiting shell process, to free history

to use history

rl_replace_line
to set the variable 'rl_line_buffer' to the content of history line got
rl_redisplay
to change what's shown in terminal to the text in variable 'rl_line_buffer'

*/