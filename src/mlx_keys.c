/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_keys.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-der <qvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 21:06:45 by W2Wizard      #+#    #+#                 */
/*   Updated: 2026/03/18 15:37:13 by qvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

static void mlx_key_callback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
{
	const mlx_t* mlx = glfwGetWindowUserPointer(window);
	const mlx_key_t key_hook = ((mlx_ctx_t*)mlx->context)->key_hook;
	const mlx_key_data_t callback_data = {
		key,
		action,
		scancode,
		mods,
	};

	key_hook.func(callback_data, key_hook.param);
}

static void mlx_char_callback(GLFWwindow* window, uint32_t codepoint)
{
	const mlx_t* mlx = glfwGetWindowUserPointer(window);
	const mlx_char_t char_hook = ((mlx_ctx_t*)mlx->context)->char_hook;

	if (char_hook.func)
		char_hook.func(codepoint, char_hook.param);
}

//= Public =//

void mlx_key_hook(mlx_t* mlx, mlx_keyfunc func, void* param)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(func);

	mlx_ctx_t* mlxctx = mlx->context;
	mlxctx->key_hook.func = func;
	mlxctx->key_hook.param = param;
	glfwSetKeyCallback(mlx->window, mlx_key_callback);
}

bool mlx_is_key_down(mlx_t* mlx, keys_t key)
{
	MLX_NONNULL(mlx);

	return (glfwGetKey(mlx->window, key) == GLFW_PRESS);
}

void mlx_char_hook(mlx_t* mlx, mlx_charfunc func, void* param)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(func);

	mlx_ctx_t* mlxctx = mlx->context;
	mlxctx->char_hook.func = func;
	mlxctx->char_hook.param = param;
	glfwSetCharCallback(mlx->window, mlx_char_callback);
}
