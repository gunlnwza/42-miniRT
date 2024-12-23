import numpy as np
import math

class Vector3:
	def __init__(self, *args):
		if (len(args) != 1 and len(args) != 3):
			raise ValueError("arguments is not 1 item ,or 3 items")
		
		if (len(args) == 1):
			xyz = args[0]
			if (isinstance(xyz, np.ndarray)):
				self.arr = xyz
			else:
				x, y, z = xyz
				self.arr = np.array([x, y, z], dtype=np.float16) 
		else:
			x, y, z = args
			self.arr = np.array([x, y, z], dtype=np.float16) 

	def __repr__(self):
		return f"Vector3({self.arr[0]} {self.arr[1]} {self.arr[2]})"
	
	def __iter__(self):
		return iter(self.arr)

	def __add__(self, other: "Vector3"):
		return Vector3(self.arr + other.arr)
	
	def __iadd__(self, other: "Vector3"):
		self.arr += other.arr
		return self

	def __sub__(self, other: "Vector3"):
		return Vector3(self.arr - other.arr)
	
	def __isub__(self, other: "Vector3"):
		self.arr -= other.arr
		return self

	def __mul__(self, other):
		if isinstance(other, Vector3):
			return self.arr * other.arr
		return Vector3(self.arr * other)

	def __rmul__(self, other: float):
		return Vector3(other * self.arr)

	def __imul__(self, other):
		self.arr = self.arr * other
		return self

	def __truediv__(self, other: float):
		return Vector3(self.arr / other)
	
	def __itruediv__(self, other: float):
		self.arr = self.arr / other
		return self

	def dot(self, other: "Vector3"):
		return self.arr.dot(other.arr)

	def cross(self, other: "Vector3"):
		return np.linalg.cross(self.arr, other.arr)

	def normalize(self):
		# normalizing 0-vector will result in error
		norm = self.norm()
		return self.arr / norm

	def norm2(self):
		return self.dot(self)

	def norm(self):
		return math.sqrt(self.norm2())

if __name__ == "__main__":
	u = Vector3((1, 2, 3))
	v = Vector3((0, 3, 7))
	w = Vector3((1, 1, 1))

	print("u =", u)
	print("v =", v)
	print("w =", w)

	print("u + v =", u + v)
	print("u - v =", u - v)

	u += w
	print("u += w ; u =", u)
	u -= w
	print("u -= w ; u = ", u)

	print("u.dot(v) =", u.dot(v))
	print("u.cross(v) =", u.cross(v))

	print("w.norm() =", w.norm())
	print("w.norm2() =", w.norm2())
	print("w.normalize() =", w.normalize())

	print("u * v =", u * v)
	print("u * 2 =", u * 2)
