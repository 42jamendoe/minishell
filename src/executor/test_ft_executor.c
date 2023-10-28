t_cmd *tmp_cmd = malloc(sizeof(t_cmd));
tmp_cmd->in = NULL;
tmp_cmd->out = NULL;
ft_deal_middle_command(tmp_cmd, 0, 1);
// Check that no input or output redirection was performed