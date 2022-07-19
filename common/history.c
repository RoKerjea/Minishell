/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:50:03 by rokerjea          #+#    #+#             */
/*   Updated: 2022/07/19 12:17:35 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
/*

if up or down, replace_line to change buffer content
rl_redisplay to put content of buffer on shell prompt
rl_on_new_line, to say we're on a new line, to be added at end of history



clear history in cleanup step before exit
*/
/* A static variable for holding the line. */
static char *line_read = (char *)NULL;

/* Read a string, and return a pointer to it.
   Returns NULL on EOF. */
char *rl_gets (void)
{
  /* If the buffer has already been allocated,
     return the memory to the free pool. */
  if (line_read)
    {
      free (line_read);
      line_read = (char *)NULL;
    }

  /* Get a line from the user. */
  line_read = readline ("");

  /* If the line has any text in it,
     save it on the history. */
  if (line_read && *line_read)
    add_history (line_read);

  return (line_read);
}
