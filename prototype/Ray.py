from Vector3 import Vector3

class Ray:
	def __init__(self, origin: Vector3, direction: Vector3):
		self.origin = origin
		self.direction = direction

	def at(self, t):
		return self.origin + t * self.direction
