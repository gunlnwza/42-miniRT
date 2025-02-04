from Vector3 import Vector3

class Camera:
	def __init__(self, center, dir, image_size):
		image_width, image_height = image_size
		self.center = Vector3(center)
		self.dir = Vector3(dir).normalize()

		viewport_height = 2
		viewport_width = viewport_height * (image_width / image_height)

		viewport_u = Vector3(viewport_width, 0, 0)
		viewport_v = Vector3(0, viewport_height, 0)
		viewport_center = self.center - self.dir
		viewport_upper_left = viewport_center - viewport_u / 2 - viewport_v / 2

		self.pixel_delta_u = viewport_u / image_width
		self.pixel_delta_v = viewport_v / image_height
		self.pixel00_loc = viewport_upper_left + 0.5 * (self.pixel_delta_u + self.pixel_delta_v)
