/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:43:59 by jamendoe          #+#    #+#             */
/*   Updated: 2023/07/17 21:44:04 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# define GENERAL 1

# define WORD 0
# define TOKEN 1

# include <stdlib.h>

typedef struct s_token{
    char *token;
    int type;
    int id;
    struct s_token *next;
} t_token;

typedef struct s_arg{
    char *arg_i;
    struct s_arg *next;
}   t_arg;

typedef struct s_cmd{
    char *sim_cmd;
    t_arg *cmd_arg;
    struct s_cmd *next;
}   t_cmd;

typedef struct s_env{
    char *name;
    char *value;
    int status;
    struct s_env *next;
}   t_env;


/* typedef struct s_cmdlist{
    t_instr     *cmdinstr;
    int         cmd_nbr;
    struct s_cmdlist  *next;
}   t_cmdlist;

typedef struct s_instr{
    char            *l_cmd;
    int             type;
    struct s_instr  *next;
}   t_instr; */

t_token *ft_lexer(char *input);
void ft_clean_env_list(t_env *list);
t_env *ft_add_new_item(t_env *list, t_env *new);
t_env *ft_new_env_item(char *item);
t_cmd *ft_parser(char *prompt);

#endif

