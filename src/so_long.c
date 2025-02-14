#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (!ft_arg_check(argc, argv))
		return (1);
	if (init_game(&game, argv[1]) != 0)
	{
		write(2, "Error\nFailed to initialize game\n", 34);
		return (1);
	}
	mlx_hook(game.window, 2, 1L << 0, ft_key_press, &game);
	mlx_hook(game.window, 17, 1L << 17, ft_close_game, &game);
	mlx_loop(game.mlx);
	return (0);
}

