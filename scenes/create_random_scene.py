#!/usr/bin/python3

import random

MIN_POS = -10
MAX_POS = 10

MIN_FOV = 50
MAX_FOV = 100

MAX_LENGTH = 5

ROUND_N_DIGITS = 3


# cast to int, if n_digits == 0
def ft_round(x, n_digits):
	return (round(x, n_digits) if n_digits > 0 else int(round(x)))

def rand():
	return (ft_round(random.random(), ROUND_N_DIGITS))

def random_color():
	r, g, b = [random.randint(0, 255) for _ in range(3)]
	return f"{r},{g},{b}"

def random_position():
	x, y, z = [ft_round((random.random() - 0.5) * MAX_POS, ROUND_N_DIGITS) for _ in range(3)]
	return f"{x},{y},{z}"

def random_direction():
	nx, ny, nz = [ft_round((random.random() - 0.5) * 2, ROUND_N_DIGITS) for _ in range(3)]
	return f"{nx},{ny},{nz}"

def random_fov():
	return random.randint(MIN_FOV, MAX_FOV)

def random_light_ratio():
	return ft_round(random.random(), max(ROUND_N_DIGITS, 2))

def random_length():
	return ft_round(random.random() * MAX_LENGTH, ROUND_N_DIGITS)


def print_line(*arg):
	print(*arg, sep="    ")

def print_ambient_lighting():
	print_line("A", random_light_ratio(), random_color())

def print_camera():
	print_line("C", random_position(), random_direction(), random_fov())

def print_light():
	print_line("L", random_position(), random_light_ratio(), '255,255,255')

def print_sphere():
	print_line("sp", random_position(), random_length(), random_color())

def print_plane():
	print_line("pl", random_position(), random_direction(), random_color())

def print_cylinder():
	print_line("cy", random_position(), random_direction(), random_length(), random_length(), random_color())


if __name__ == "__main__":
	print_ambient_lighting()
	print_camera()
	print_light()

	number_of_objects = random.randint(1, 8)
	for _ in range(number_of_objects):
		choice = random.choice(["sp", "pl", "cy"])
		if choice == "sp":
			print_sphere()
		elif choice == "pl":
			print_plane()
		elif choice == "cy":
			print_cylinder()
