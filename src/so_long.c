#include "includes/so_long.h"

int    main(int argc, char **argv)
{
    t_game	game;

    if (argc != 2)
    {
        ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
        return (1);
    }
    if (init_game(&game, argv[1]))
    {
        ft_putstr_fd("Error\nFailed to initialize game\n", 2);
        return (1);
    }
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    mlx_hook(game.win, 17, 1L << 17, close_game, &game);
    mlx_loop(game.mlx);
    return (0);
}

