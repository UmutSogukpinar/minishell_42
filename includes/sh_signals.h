#ifndef SH_SIGNALS_H
# define SH_SIGNALS_H

# include "structs.h"
# include <signal.h>

// * =======================================================>>>>> Signal Handling

void	handle_sigint_output(void);
void	handle_signals(t_status status);

int		setup_termios(t_shell *shell, t_termios_action action);

#endif
